"""Filesystem paths for the FPGA flow framework."""

from __future__ import annotations

from pathlib import Path

PACKAGE_ROOT = Path(__file__).resolve().parent
PROJECT_ROOT = PACKAGE_ROOT.parent
REPO_ROOT = PROJECT_ROOT.parent
DESIGNS_DIR = PROJECT_ROOT / 'designs'

REPORTS_DIR = PACKAGE_ROOT / 'reports'
OLD_AUTOGEN_DIR = PROJECT_ROOT / 'old_code_autogen'
