---
name: openhands-sdk-skill-authoring
description: Guidance for writing and maintaining OpenHands SDK skills, including SKILL.md structure, triggers, always-loaded repository skills, and concise progressive disclosure.
type: knowledge
version: 1.0.0
agent: CodeActAgent
triggers:
  - skill.md
  - agents.md
  - repository skill
  - knowledge microagent
  - trigger-loaded skill
  - repo skill authoring
---

# Purpose And Scope

Use this skill when creating or updating skills for OpenHands SDK workflows.

This skill covers:

- `SKILL.md` structure
- frontmatter fields
- always-loaded vs trigger-loaded skills
- concise progressive disclosure
- where to place large references and bundled resources

It does not cover SDK runtime bootstrapping, MCP wiring, sub-agent delegation details, or task execution outside the skill format.

# Write Skills As Reusable Workflows

Keep each skill focused on one stable use case. Prefer small skills that answer one of these questions:

- How do I start?
- How do I add a tool?
- How do I delegate work?
- How do I debug?
- How do I maintain repo rules?

Use only the minimum context needed to make the workflow reliable.

# Required Structure

For most skills, keep this structure:

1. `Purpose And Scope`
2. `Core Workflow`
3. `Stable Rules`
4. `References`

Use frontmatter fields that Codex actually uses:

- `name`
- `description`
- `type`
- `version`
- `agent`
- `triggers` when the skill should be keyword-loaded

# Loading Strategy

- Use a repo skill when the guidance should always load for this repository.
- Use a knowledge skill when the guidance should load only on matching topics.
- Keep triggers specific to user phrases, not to every related noun.
- If the skill gets too large, move detail into a reference file and keep the main `SKILL.md` short.

# Quality Rules

- Prefer concrete examples over abstract prose.
- Avoid duplicating the same rule in multiple skills.
- Keep the skill body short enough that the model can read it in one pass.
- Validate the skill against realistic prompts before treating it as stable.
- Keep domain-specific runtime details in dedicated skills instead of widening this one.

# References

- Skill authoring guide: [skill-creator](/Users/kyrie/.codex/skills/.system/skill-creator/SKILL.md)
- OpenHands skills guide: [Agent Skills & Context](https://docs.openhands.dev/sdk/guides/skill)
- Existing repo examples: [chatfire_deepseek_sdk.md](/Users/kyrie/Downloads/OpenHands-1.5.0/.openhands/skills/chatfire_deepseek_sdk.md)
- Existing repo examples: [verilog_verilator.md](/Users/kyrie/Downloads/OpenHands-1.5.0/.openhands/skills/verilog_verilator.md)
