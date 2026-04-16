# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

OpenHands is an AI-driven software engineering platform with a Python backend (`openhands/`) and React frontend (`frontend/`). It uses LLM agents that can edit files, run commands, browse the web, and execute code in sandboxed environments. The system is undergoing a V0-to-V1 migration: the legacy server lives in `openhands/server/`, while the new V1 app server is in `openhands/app_server/`.

## Requirements

- Python 3.12, Poetry >= 1.8, Node.js >= 22.x, Docker

## Build & Run

```bash
make build                # Full setup: Python deps, frontend deps, pre-commit hooks, frontend build
make run                  # Start backend (port 3000) + frontend dev server (port 3001)
make start-backend        # Backend only (uvicorn with --reload)
make start-frontend       # Frontend dev server only
```

## Linting (MANDATORY before committing)

```bash
make install-pre-commit-hooks                                              # First-time setup
pre-commit run --config ./dev_config/python/.pre-commit-config.yaml        # Backend (runs on staged files)
make lint-backend                                                          # Backend (all files)
cd frontend && npm run lint:fix && npm run build                           # Frontend
```

Pre-commit hooks run: trailing-whitespace, end-of-file-fixer, ruff (lint + format), mypy, pyproject-fmt. Config lives in `dev_config/python/` (ruff.toml, mypy.ini, .pre-commit-config.yaml).

Key style rules: single quotes for Python strings, no line-length enforcement (E501 ignored). Never use `AppMode.OSS` — use `AppMode.OPENHANDS` instead (enforced by a pre-commit hook).

## Testing

```bash
# Python unit tests
poetry run pytest tests/unit/test_foo.py              # Single test file
poetry run pytest tests/unit/test_foo.py -k "test_bar" # Single test function

# Frontend tests
cd frontend && npm run test                            # All tests (vitest)
cd frontend && npm run test -- -t "TestName"           # Specific test

# Runtime integration tests (requires Docker)
TEST_RUNTIME=cli poetry run pytest -s tests/runtime/test_bash.py

# Enterprise tests
PYTHONPATH=".:$PYTHONPATH" poetry run --project=enterprise pytest --forked -n auto -s ./enterprise/tests/unit
```

pytest config: `asyncio_mode = auto` (pytest.ini). CI runs with `--forked -n auto --cov=openhands`.

## Architecture

### Backend (`openhands/`)

- **agenthub/**: Agent implementations (CodeActAgent is the primary agent)
- **app_server/**: New V1 FastAPI server — conversations, events, sandbox, services
- **server/**: Legacy V0 FastAPI + Socket.IO server (deprecated, removal planned)
- **controller/**: AgentController orchestrates agent execution and state management
- **events/**: Event system — Actions (agent outputs) and Observations (environment feedback)
- **runtime/impl/**: Execution environments — Docker (default), CLI, Kubernetes, local, remote
- **llm/**: LLM abstraction layer built on litellm; supports Claude, GPT-4, Gemini, etc.
- **memory/**: Conversation memory and condensers (history summarization)
- **mcp/**: Model Context Protocol integration
- **microagent/**: Skill/microagent loading system (from `microagents/` and `.openhands/microagents/`)
- **integrations/**: GitHub, GitLab, Jira, Bitbucket, Azure DevOps, Forgejo integrations
- **resolver/**: GitHub issue resolver
- **core/main.py**: `run_controller()` — headless/CLI entry point for running agents programmatically

### Frontend (`frontend/`)

React 19 + React Router v7 + Vite + Zustand (state) + TanStack Query (data fetching) + Tailwind CSS.

Data fetching pattern: UI components -> TanStack Query hooks -> Data Access Layer (`frontend/src/api/`) -> API endpoints. Query hooks in `frontend/src/hooks/query/` (pattern: `use[Resource]`), mutation hooks in `frontend/src/hooks/mutation/` (pattern: `use[Action]`).

### Enterprise (`enterprise/`)

Source-available (Polyform Free Trial License). Auth via Keycloak, DB migrations via Alembic, billing via Stripe. Has its own `pyproject.toml`. Use relative imports (no `enterprise.` prefix). Use `sqlite:///:memory:` for unit tests.

## Git Practices

- Use `git add <filename>` for specific files, never `git add .`
- Microagents: public in `microagents/`, repo-specific in `.openhands/microagents/`. Files without frontmatter are always loaded; files with `triggers:` frontmatter load on keyword match.

## Adding LLM Models

Update all of these:
1. `frontend/src/utils/verified-models.ts` — `VERIFIED_MODELS` and provider arrays
2. `openhands/cli/utils.py` — `VERIFIED_*_MODELS` arrays
3. `openhands/utils/llm.py` — `openhands_models` list
4. `openhands/llm/llm.py` — feature arrays (`FUNCTION_CALLING_SUPPORTED_MODELS`, etc.)

## Debugging

```bash
export DEBUG=1    # Then restart backend; LLM logs go to logs/llm/CURRENT_DATE/
```
