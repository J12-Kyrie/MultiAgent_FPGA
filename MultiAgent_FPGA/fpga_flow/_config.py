"""Shared process-level configuration for the fpga_flow package.

This module exists to avoid the Python double-import problem with __main__.
When running ``python -m MultiAgent_FPGA.fpga_flow``, the __main__.py file is
loaded as the ``__main__`` module.  Other modules that import from
``MultiAgent_FPGA.fpga_flow.__main__`` get a *second* copy with its own
module-level globals.  Storing mutable state here ensures all code paths
(including execution_tools.py's deferred import) see the same value.
"""

from __future__ import annotations

ACTIVE_BLUEPRINT_PATH: str | None = None
