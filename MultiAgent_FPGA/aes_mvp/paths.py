"""Filesystem paths for the AES MVP framework."""

from __future__ import annotations

from pathlib import Path

PACKAGE_ROOT = Path(__file__).resolve().parent
PROJECT_ROOT = PACKAGE_ROOT.parent
REPO_ROOT = PROJECT_ROOT.parent

RTL_DIR = PACKAGE_ROOT / 'rtl'
TB_DIR = PACKAGE_ROOT / 'tb'
VECTORS_DIR = PACKAGE_ROOT / 'vectors' / 'aes128'
REPORTS_DIR = PACKAGE_ROOT / 'reports'
OLD_AUTOGEN_DIR = PROJECT_ROOT / 'old_code_autogen'
