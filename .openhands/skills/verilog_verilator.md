---
name: verilog-verilator
description: Repository skill for Verilog .v plus .v/.cpp TB via Verilator MCP, compile-then-simulate, and include search paths for .vh headers.
type: knowledge
version: 1.0.1
agent: CodeActAgent
---

# Purpose And Scope

Use this skill when working on Verilog `.v` designs in this repository through the Verilator MCP server.

This skill only supports:

- Verilog design files ending in `.v`
- An existing testbench ending in `.v` or `.cpp`
- A fixed two-step flow: `verilator_compile` first, then `verilator_simulate`

This skill does not cover SystemVerilog `.sv` testbenches, generated testbenches, or MCP resource reads.

# Hard Rules

- Require an existing testbench before running Verilator.
- Support only `.v` design files plus an existing `.v` or `.cpp` testbench.
- If no existing testbench is available, stop and ask the user to provide one.
- If the user asks to use a `.sv` testbench, reject that path and ask for a supported `.v` or `.cpp` testbench.
- If `topModule`, `files`, or `outputDir` is missing, stop and ask instead of guessing.
- Only use `verilator_compile` and `verilator_simulate`.
- Do not use `verilator_testbenchgenerator`.
- Do not use `verilator_naturallanguage`.
- Do not rely on `simulation://...` MCP resources.

# Required Arguments

Always require these explicit inputs before calling MCP tools:

- `topModule`
- `files`
- `outputDir`

For compile calls:

- `files` must include the `.v` RTL file and the existing `.v` or `.cpp` testbench file.
- Always pass `language: "verilog"` for `.v` workflows.
- Prefer an explicit build output directory such as `build/obj_dir`.

# Include Files (`.vh`) And Search Path

- A Verilog file that references a header such as `aes_sbox_lut.vh` needs that file on Verilator’s include path. Use **include directories** (`-I<dir>`) where `<dir>` is the folder that **contains** the header (for example `MultiAgent_FPGA/aes_mvp/rtl/`).

- **`files` must list only source files** (`.v`, `.sv`, `.cpp`, …), not directories. Passing a directory path as if it were a Verilog file leads to errors such as `Cannot find file containing module: '<path>/rtl'` because Verilator treats unknown path tokens as module lookup targets.

- **AES MVP framework path**: Node validation uses the internal `VerilatorMCPAdapter`, which adds `-I<resolved_rtl_parent>` for each compiled `.v` parent directory and filters non-files out of `files`. When **manually** invoking `verilator_compile` through MCP, mirror that contract: ensure every directory that holds included headers is covered by `-I`, and never append bare include directories to the `files` array.

- Prefer a **single-argument** include flag form (`-I/path/to/rtl`) when assembling extra flags, so the compile argv stays unambiguous across toolchains.

For simulate calls:

- Always pass `topModule`.
- Always pass an explicit simulation output directory such as `sim_output`.
- Set `design` to the compiled build directory from the compile step.

# Fixed Two-Step Workflow

1. Call `verilator_compile` first.
2. Call `verilator_simulate` second with the build output from step 1.

Compile contract:

```json
{
  "name": "verilator_compile",
  "arguments": {
    "files": ["rtl/<top>.v", "tb/<existing_testbench>.v_or_cpp"],
    "topModule": "<topModule>",
    "outputDir": "build/obj_dir",
    "language": "verilog"
  }
}
```

Simulate contract:

```json
{
  "name": "verilator_simulate",
  "arguments": {
    "design": "build/obj_dir",
    "topModule": "<topModule>",
    "outputDir": "sim_output",
    "useExistingBuild": true,
    "autoGenerateTestbench": false,
    "enableWaveform": true
  }
}
```

# Failure Handling And Artifact Reading

- If compile fails, inspect the `verilator_compile` output and fix the RTL or the existing testbench, then rerun compile.
- If simulate fails, inspect the `verilator_simulate` output and the generated artifacts, then fix the RTL or the existing testbench and rerun compile and simulate.
- Read the generated `simulation.log` file directly from the filesystem.
- Read the generated `simulation.vcd` file directly from the filesystem.
- Do not replace direct file inspection with `simulation://...` resource reads.
