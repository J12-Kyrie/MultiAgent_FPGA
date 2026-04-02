---
name: deepseek-official-sdk
description: Guidance for using DeepSeek's official OpenAI-compatible API from OpenHands, including the stable deepseek-chat runtime path, the reasoning-model boundary, and integration rules for tool-using agents.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - deepseek official
  - deepseek api
  - deepseek-chat
  - deepseek-reasoner
  - openhands sdk deepseek
---

# Purpose And When To Use

Use this skill when the task is about connecting DeepSeek's official API to OpenHands, choosing between `deepseek-chat` and `deepseek-reasoner`, or explaining the stable request and response contract for later SDK use.

This skill captures the verified DeepSeek official API path from April 1, 2026. It is not a general model-selection skill.

# Stable Endpoint And Authentication

Use DeepSeek's official API as an OpenAI-compatible provider.

- Base URL: `https://api.deepseek.com`
- Stable endpoint: `POST /chat/completions`
- Auth: `Authorization: Bearer <DEEPSEEK_API_KEY>`
- Stable runtime request model: `deepseek-chat`
- Official reasoning model boundary: `deepseek-reasoner`
- Stable resolved model recording for the AES runtime: `deepseek-chat`

Hard rules:

- Never hardcode the API key in repository files.
- Read the API key from an environment variable or a secrets store.
- Use `DEEPSEEK_API_KEY` as the primary environment variable. `CHATFIRE_API_KEY` may be treated as a legacy fallback only while migrating old local scripts.
- Use `deepseek-chat` as the stable runtime request model in OpenHands and raw API calls.
- Record the response `model` field for experiment logs.
- Do not route the AES multi-agent runtime through `deepseek-reasoner`, because the official reasoning model does not support function calling.

# OpenHands Integration Contract

In OpenHands, configure DeepSeek through the normal `model`, `api_key`, and `base_url` fields.

Stable runtime profile:

```python
import os

from pydantic import SecretStr

from openhands.core.config.llm_config import LLMConfig

llm_config = LLMConfig(
    model="deepseek-chat",
    api_key=SecretStr(os.environ["DEEPSEEK_API_KEY"]),
    base_url="https://api.deepseek.com",
)
```

Guidance:

- Use `deepseek-chat` for both logical fast and logical thinking profiles in the AES runtime, so OpenHands keeps delegate/tool support.
- Do not rely on `reasoning_effort` for the `deepseek-chat` runtime path.
- Treat `deepseek-reasoner` as a separate official reasoning-only boundary, not the main runtime path for tool-using agents.
- The verified stable path uses `stream=false`. Do not assume streaming semantics until they are tested separately.

# Verified Raw Request Shapes

Stable raw request:

```json
{
  "model": "deepseek-chat",
  "messages": [
    {
      "role": "user",
      "content": "Reply with exactly: ok"
    }
  ],
  "stream": false
}
```

Reasoning-only raw request boundary:

```json
{
  "model": "deepseek-reasoner",
  "messages": [
    {
      "role": "user",
      "content": "What is 2+2? Reply briefly."
    }
  ],
  "stream": false
}
```

Do not use the reasoning-only request shape as the stable OpenHands AES runtime path because function calling is not supported there.

# Response Parsing Rules

Always parse the normal assistant answer from:

- `choices[0].message.content`

When the response comes from `deepseek-reasoner`, also expect provider-specific reasoning output in:

- `choices[0].message.reasoning_content`
- `usage.completion_tokens_details.reasoning_tokens`

Practical rules:

- Treat `content` as the user-visible answer.
- Treat `reasoning_content` as optional reasoning trace data.
- If `reasoning_content` is absent, do not fail the request unless the caller explicitly required thinking output.
- Record the response `model` field if you need to pin later runs to the exact resolved backend model.

# Stable Boundaries

Use this as the stable DeepSeek official path for this repository:

- `base_url="https://api.deepseek.com"`
- `model="deepseek-chat"`
- record resolved `model` values from responses
- non-thinking and logical-thinking runtime profiles both stay on `deepseek-chat`
- keep `deepseek-reasoner` outside the tool-using AES runtime path

Do not treat these as stable assumptions:

- that `deepseek-reasoner` can be dropped into the current OpenHands delegate flow
- provider-specific hidden reasoning flags on `deepseek-chat`
- streaming behavior that has not been separately verified

If DeepSeek returns provider or quota errors for a model, treat that as a provider availability problem, not as a payload-shape problem.
