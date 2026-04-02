"""Filesystem paths for the AES MVP framework."""

from __future__ import annotations

from pathlib import Path

PACKAGE_ROOT = Path(__file__).resolve().parent
PROJECT_ROOT = PACKAGE_ROOT.parent
REPO_ROOT = PROJECT_ROOT.parent

ASSETS_DIR = PACKAGE_ROOT / 'assets'
RTL_DIR = PACKAGE_ROOT / 'rtl'
TB_DIR = PACKAGE_ROOT / 'tb'
VECTORS_DIR = PACKAGE_ROOT / 'vectors' / 'aes128'
REPORTS_DIR = PACKAGE_ROOT / 'reports'
OLD_AUTOGEN_DIR = PROJECT_ROOT / 'old_code_autogen'

SPEC_IR_PATH = ASSETS_DIR / 'spec_ir.json'
PLAN_DAG_PATH = ASSETS_DIR / 'plan_dag.json'
AGENT_EXECUTION_POLICY_PATH = ASSETS_DIR / 'agent_execution_policy.json'
INTEGRATION_MANIFEST_PATH = ASSETS_DIR / 'integration_regression_manifest.json'
