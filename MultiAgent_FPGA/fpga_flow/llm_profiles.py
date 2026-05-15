"""Pinned DeepSeek official LLM profiles for the AES MVP runtime.

The runtime uses DeepSeek's official OpenAI-compatible API. The stable build
path stays on ``deepseek-chat`` for both logical profiles because OpenHands'
tool and delegate flow depends on function-calling support, while the official
``deepseek-reasoner`` path does not support function calling.
"""

from __future__ import annotations

import os
from dataclasses import dataclass
from typing import Any, Mapping

import requests
from pydantic import SecretStr

DEEPSEEK_API_KEY_ENV = 'DEEPSEEK_API_KEY'
LEGACY_CHATFIRE_API_KEY_ENV = 'CHATFIRE_API_KEY'
DEEPSEEK_BASE_URL = 'https://api.deepseek.com'
DEEPSEEK_CHAT_MODEL = 'deepseek-chat'
DEEPSEEK_REASONER_MODEL = 'deepseek-v4-flash'
DEEPSEEK_RESOLVED_MODEL = DEEPSEEK_CHAT_MODEL
SDK_DEEPSEEK_MODEL = f'openai/{DEEPSEEK_CHAT_MODEL}'
SDK_REASONING_EFFORT_THINKING = 'medium'
SDK_REASONING_EFFORT_FAST = 'none'


@dataclass(frozen=True)
class ParsedDeepSeekResponse:
    content: str
    resolved_model: str | None
    reasoning_content: str | None
    reasoning_tokens: int | None


@dataclass(frozen=True)
class DeepSeekPreflightResult:
    thinking_enabled: bool
    request_model: str
    status_code: int
    ok: bool
    resolved_model: str | None
    content: str | None
    reasoning_content: str | None
    reasoning_tokens: int | None
    error: str | None


def _lookup_api_key(env_var: str = DEEPSEEK_API_KEY_ENV) -> str | None:
    return os.environ.get(env_var) or os.environ.get(LEGACY_CHATFIRE_API_KEY_ENV)


def _require_api_key(env_var: str = DEEPSEEK_API_KEY_ENV) -> SecretStr:
    value = _lookup_api_key(env_var)
    if not value:
        raise RuntimeError(
            f'Set {env_var} before constructing the pinned DeepSeek AES MVP profiles.'
        )
    return SecretStr(value)


def _resolve_api_key(
    env_var: str = DEEPSEEK_API_KEY_ENV,
    *,
    allow_placeholder: bool = False,
) -> SecretStr:
    value = _lookup_api_key(env_var)
    if value:
        return SecretStr(value)
    if allow_placeholder:
        return SecretStr('missing-deepseek-api-key')
    return _require_api_key(env_var)


def build_sdk_deepseek_official_thinking_kwargs(
    env_var: str = DEEPSEEK_API_KEY_ENV,
    *,
    allow_placeholder_api_key: bool = False,
) -> dict[str, Any]:
    """Build OpenHands SDK LLM kwargs for the thinking (orchestrator) profile.

    Uses ``reasoning_effort='medium'`` so that escalation from fast workers to
    the thinking orchestrator enables deeper reasoning.
    """
    return {
        'model': SDK_DEEPSEEK_MODEL,
        'model_canonical_name': DEEPSEEK_RESOLVED_MODEL,
        'api_key': _resolve_api_key(
            env_var, allow_placeholder=allow_placeholder_api_key
        ),
        'base_url': DEEPSEEK_BASE_URL,
        'reasoning_effort': SDK_REASONING_EFFORT_THINKING,
    }


def build_sdk_deepseek_official_fast_kwargs(
    env_var: str = DEEPSEEK_API_KEY_ENV,
    *,
    allow_placeholder_api_key: bool = False,
) -> dict[str, Any]:
    """Build OpenHands SDK LLM kwargs for the fast (worker) profile.

    Uses ``reasoning_effort='none'`` for maximum throughput on node-local tasks.
    """
    return {
        'model': SDK_DEEPSEEK_MODEL,
        'model_canonical_name': DEEPSEEK_RESOLVED_MODEL,
        'api_key': _resolve_api_key(
            env_var, allow_placeholder=allow_placeholder_api_key
        ),
        'base_url': DEEPSEEK_BASE_URL,
        'reasoning_effort': SDK_REASONING_EFFORT_FAST,
    }


def parse_deepseek_response(payload: Mapping[str, Any]) -> ParsedDeepSeekResponse:
    choices = payload.get('choices', [])
    if not choices:
        raise ValueError('DeepSeek response does not contain choices')

    message = choices[0].get('message', {})
    content = message.get('content')
    if content is None:
        raise ValueError('DeepSeek response is missing choices[0].message.content')

    reasoning_tokens = None
    usage = payload.get('usage', {})
    if isinstance(usage, Mapping):
        completion_details = usage.get('completion_tokens_details', {})
        if isinstance(completion_details, Mapping):
            raw_reasoning_tokens = completion_details.get('reasoning_tokens')
            if isinstance(raw_reasoning_tokens, int):
                reasoning_tokens = raw_reasoning_tokens

    raw_reasoning = message.get('reasoning_content')
    reasoning_content = raw_reasoning if isinstance(raw_reasoning, str) else None
    resolved_model = payload.get('model')
    return ParsedDeepSeekResponse(
        content=content,
        resolved_model=resolved_model if isinstance(resolved_model, str) else None,
        reasoning_content=reasoning_content,
        reasoning_tokens=reasoning_tokens,
    )


def _build_preflight_payload(*, thinking_enabled: bool) -> dict[str, Any]:
    return {
        'model': DEEPSEEK_CHAT_MODEL,
        'messages': [
            {
                'role': 'user',
                'content': (
                    'Reply with exactly: ok'
                    if not thinking_enabled
                    else 'Reply with exactly: ok after a brief internal deliberation.'
                ),
            }
        ],
        'stream': False,
    }


def run_deepseek_preflight(
    *,
    thinking_enabled: bool,
    timeout: int = 60,
) -> DeepSeekPreflightResult:
    response = requests.post(
        f'{DEEPSEEK_BASE_URL}/chat/completions',
        headers={
            'Authorization': (f'Bearer {_require_api_key().get_secret_value()}'),
            'Content-Type': 'application/json',
        },
        json=_build_preflight_payload(thinking_enabled=thinking_enabled),
        timeout=timeout,
    )
    try:
        payload = response.json()
    except Exception:
        payload = None

    if not response.ok:
        error_message = None
        if isinstance(payload, Mapping):
            raw_error = payload.get('error')
            if isinstance(raw_error, Mapping):
                raw_message = raw_error.get('message')
                if isinstance(raw_message, str):
                    error_message = raw_message
            elif isinstance(raw_error, str):
                error_message = raw_error
        if error_message is None:
            error_message = response.text.strip() or f'HTTP {response.status_code}'
        return DeepSeekPreflightResult(
            thinking_enabled=thinking_enabled,
            request_model=DEEPSEEK_CHAT_MODEL,
            status_code=response.status_code,
            ok=False,
            resolved_model=None,
            content=None,
            reasoning_content=None,
            reasoning_tokens=None,
            error=error_message,
        )

    if not isinstance(payload, Mapping):
        raise ValueError('DeepSeek preflight returned a non-JSON response payload')

    parsed = parse_deepseek_response(payload)
    return DeepSeekPreflightResult(
        thinking_enabled=thinking_enabled,
        request_model=DEEPSEEK_CHAT_MODEL,
        status_code=response.status_code,
        ok=True,
        resolved_model=parsed.resolved_model,
        content=parsed.content,
        reasoning_content=parsed.reasoning_content,
        reasoning_tokens=parsed.reasoning_tokens,
        error=None,
    )


def run_deepseek_preflight_suite(*, timeout: int = 60) -> dict[str, Any]:
    fast = run_deepseek_preflight(
        thinking_enabled=False,
        timeout=timeout,
    )
    thinking = run_deepseek_preflight(
        thinking_enabled=True,
        timeout=timeout,
    )
    return {
        'base_url': DEEPSEEK_BASE_URL,
        'request_model': DEEPSEEK_CHAT_MODEL,
        'resolved_model': thinking.resolved_model or fast.resolved_model,
        'fast': fast,
        'thinking': thinking,
    }
