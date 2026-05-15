#!/usr/bin/env python3
"""Generate a Word (.docx) thesis document from markdown chapters.

Shanghai University Undergraduate Thesis format.
Reads chapters from chapters/ directory and outputs thesis_output.docx.
"""

import re
import sys
from pathlib import Path

try:
    from docx import Document
    from docx.enum.section import WD_ORIENT  # noqa: F401
    from docx.enum.table import WD_TABLE_ALIGNMENT
    from docx.enum.text import WD_ALIGN_PARAGRAPH
    from docx.oxml import parse_xml
    from docx.oxml.ns import nsdecls, qn
    from docx.shared import Cm, Emu, Inches, Pt, RGBColor
except ImportError:
    print('ERROR: python-docx is required. Install with: pip install python-docx')
    sys.exit(1)

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------
THESIS_DIR = Path(__file__).resolve().parent
CHAPTERS = [
    THESIS_DIR / 'chapters' / 'ch1_introduction.md',
    THESIS_DIR / 'chapters' / 'ch2_background.md',
    THESIS_DIR / 'chapters' / 'ch3_system_design.md',
    THESIS_DIR / 'chapters' / 'ch4_state_machine.md',
    THESIS_DIR / 'chapters' / 'ch5_verification.md',
    THESIS_DIR / 'chapters' / 'ch6_harnessing_engine.md',
    THESIS_DIR / 'chapters' / 'ch7_experiments.md',
    THESIS_DIR / 'chapters' / 'ch8_conclusion.md',
    THESIS_DIR / 'chapters' / 'ch_references.md',
]
OUTPUT_PATH = THESIS_DIR / 'thesis_output.docx'
DIAGRAMS_DIR = THESIS_DIR.parent / 'fpga_flow' / 'diagrams'

# Track images already inserted to avoid duplicates
_inserted_images: set[str] = set()

# Track whether we've inserted the body section break yet
_body_section_started: bool = False

# ---------------------------------------------------------------------------
# Font constants (from template analysis)
# ---------------------------------------------------------------------------
FONT_COVER = '方正粗宋简体'  # Cover page title/fields
FONT_HEADING_CN = '黑体'  # All headings east-asia
FONT_BODY_CN = '宋体'  # Body text east-asia
FONT_BODY_EN = 'Times New Roman'  # Body text western
FONT_TABLE = '宋体'  # Table cell east-asia
FONT_TABLE_EN = 'Times New Roman'  # Table cell western
FONT_HEADER = '宋体'  # Page header
FONT_CODE = 'Courier New'  # Code blocks
FONT_CAPTION_NUM = '等线'  # Caption number font (deng xian)

# Size constants (from template)
SZ_COVER_TITLE = Pt(42)  # "本科毕业论文（设计）"
SZ_COVER_SUBTITLE = Pt(18)  # English subtitle + 题目 label
SZ_COVER_FIELD = Pt(16)  # 学院/专业/etc. labels
SZ_COVER_FIELD_VALUE = Pt(18)  # Field value underlines
SZ_H1 = Pt(18)  # Heading 1 = xiao er (小二)
SZ_H2 = Pt(14)  # Heading 2 = si hao (四号)
SZ_H3 = Pt(12)  # Heading 3 = xiao si (小四)
SZ_BODY = Pt(12)  # Body text = xiao si (小四)
SZ_TABLE = Pt(10.5)  # Table cells = xiao wu (小五)
SZ_HEADER = Pt(10.5)  # Page header = xiao wu (小五)
SZ_CODE = Pt(10)  # Code blocks

# Spacing constants (EMU values from template)
SP_H1_BEFORE = Emu(158115)  # ~4.39 cm
SP_H1_AFTER = Emu(99060)  # ~2.75 cm
SP_H2_BEFORE = Emu(99060)
SP_H2_AFTER = Emu(99060)
SP_H3_BEFORE = Emu(99060)
SP_H3_AFTER = Emu(99060)
SP_CAPTION_BEFORE = Pt(12)
SP_CAPTION_AFTER = Pt(12)
SP_IMAGE_BEFORE = Pt(18)
SP_IMAGE_AFTER = Pt(6)
SP_TABLE_AFTER = Pt(12)

# Line spacing for body text: 23 pt EXACTLY
LINE_SPACING_BODY = Pt(23)
# First-line indent: 2 characters at 12pt = 24pt
FIRST_LINE_INDENT = Pt(24)


# ---------------------------------------------------------------------------
# Helpers: font / paragraph setup
# ---------------------------------------------------------------------------
def set_chinese_font(
    run, font_name_cn=FONT_BODY_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
):
    """Set both western and east-asian fonts on a run."""
    run.font.name = font_name_en
    run.font.size = size
    rpr = run.font.element.get_or_add_rPr()
    rfonts = rpr.find(qn('w:rFonts'))
    if rfonts is None:
        rfonts = parse_xml(f'<w:rFonts {nsdecls("w")} />')
        rpr.insert(0, rfonts)
    rfonts.set(qn('w:eastAsia'), font_name_cn)
    rfonts.set(qn('w:ascii'), font_name_en)
    rfonts.set(qn('w:hAnsi'), font_name_en)


def set_paragraph_format(
    paragraph,
    alignment=None,
    first_line_indent=None,
    space_before=None,
    space_after=None,
    line_spacing=None,
    line_spacing_rule=None,
):
    """Configure paragraph formatting."""
    pf = paragraph.paragraph_format
    if line_spacing is not None:
        pf.line_spacing = line_spacing
    if line_spacing_rule is not None:
        pf.line_spacing_rule = line_spacing_rule
    if alignment is not None:
        pf.alignment = alignment
    if first_line_indent is not None:
        pf.first_line_indent = first_line_indent
    if space_before is not None:
        pf.space_before = space_before
    if space_after is not None:
        pf.space_after = space_after


def add_body_paragraph(doc, text='', bold=False):
    """Add a body-text paragraph with standard formatting."""
    p = doc.add_paragraph()
    set_paragraph_format(
        p,
        first_line_indent=FIRST_LINE_INDENT,
        line_spacing=LINE_SPACING_BODY,
        line_spacing_rule=4,
    )  # EXACTLY
    if text:
        run = p.add_run(text)
        set_chinese_font(
            run, font_name_cn=FONT_BODY_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )
        run.bold = bold
    return p


# ---------------------------------------------------------------------------
# Cover page
# ---------------------------------------------------------------------------
def create_cover_page(doc):
    """Create the thesis cover page matching template exactly."""
    # Add blank paragraphs for vertical spacing
    for _ in range(3):
        p = doc.add_paragraph()
        set_paragraph_format(p, line_spacing=2.0, line_spacing_rule=2)  # DOUBLE

    # Title: "本科毕业论文（设计）" - 42pt Fang Zheng Cu Song, centered, double spacing
    p = doc.add_paragraph()
    set_paragraph_format(
        p, alignment=WD_ALIGN_PARAGRAPH.CENTER, line_spacing=2.0, line_spacing_rule=2
    )  # DOUBLE
    run = p.add_run('本科毕业论文（设计）')
    set_chinese_font(
        run, font_name_cn=FONT_COVER, font_name_en=FONT_COVER, size=SZ_COVER_TITLE
    )
    run.font.color.rgb = RGBColor(0, 0, 0)

    # English subtitle: "UNDERGRADUATE  THESIS (PROJECT)" - 18pt
    p = doc.add_paragraph()
    set_paragraph_format(
        p, alignment=WD_ALIGN_PARAGRAPH.CENTER, line_spacing=2.0, line_spacing_rule=2
    )
    run = p.add_run('UNDERGRADUATE  THESIS (PROJECT)')
    set_chinese_font(
        run, font_name_cn=FONT_COVER, font_name_en=FONT_COVER, size=SZ_COVER_SUBTITLE
    )
    run.font.color.rgb = RGBColor(0, 0, 0)

    # Blank separator
    for _ in range(3):
        p = doc.add_paragraph()
        set_paragraph_format(p, line_spacing=2.0, line_spacing_rule=2)

    # 题目 field: label 18pt, indent 1.90cm
    p = doc.add_paragraph()
    set_paragraph_format(
        p,
        alignment=WD_ALIGN_PARAGRAPH.LEFT,
        first_line_indent=Cm(1.90),
        line_spacing=2.0,
        line_spacing_rule=2,
    )
    run = p.add_run('题   目：')
    set_chinese_font(
        run, font_name_cn=FONT_COVER, font_name_en=FONT_COVER, size=SZ_COVER_SUBTITLE
    )
    run.font.color.rgb = RGBColor(0, 0, 0)
    run2 = p.add_run('基于多智能体的 FPGA 设计全流程自动化框架')
    set_chinese_font(
        run2, font_name_cn=FONT_COVER, font_name_en=FONT_COVER, size=SZ_COVER_SUBTITLE
    )
    run2.font.color.rgb = RGBColor(0, 0, 0)

    # Other fields: label 16pt, value 18pt, indent 1.69cm
    fields_rest = [
        ('学    院', ''),
        ('专    业', ''),
        ('学    号', ''),
        ('学生姓名', ''),
        ('指导教师', ''),
        ('起讫日期', ''),
    ]

    for label, value in fields_rest:
        p = doc.add_paragraph()
        set_paragraph_format(
            p,
            alignment=WD_ALIGN_PARAGRAPH.LEFT,
            first_line_indent=Cm(1.69),
            line_spacing=2.0,
            line_spacing_rule=2,
        )
        run = p.add_run(f'{label}：')
        set_chinese_font(
            run, font_name_cn=FONT_COVER, font_name_en=FONT_COVER, size=SZ_COVER_FIELD
        )
        run.font.color.rgb = RGBColor(0, 0, 0)
        run2 = p.add_run(value)
        set_chinese_font(
            run2,
            font_name_cn=FONT_COVER,
            font_name_en=FONT_COVER,
            size=SZ_COVER_FIELD_VALUE,
        )
        run2.font.color.rgb = RGBColor(0, 0, 0)

    # Section break after cover
    doc.add_section()


# ---------------------------------------------------------------------------
# Markdown parsing
# ---------------------------------------------------------------------------
def resolve_image_path(raw_path: str) -> Path | None:
    """Resolve an image path from markdown to an absolute filesystem path."""
    raw_path = raw_path.replace('\\', '/')
    candidate = (THESIS_DIR / raw_path).resolve()
    if candidate.exists():
        return candidate
    while raw_path.startswith('../'):
        raw_path = raw_path[3:]
    candidate = (THESIS_DIR.parent / raw_path).resolve()
    if candidate.exists():
        return candidate
    p = Path(raw_path).resolve()
    if p.exists():
        return p
    return None


def add_image(doc, raw_path: str, alt_text: str = ''):
    """Insert an image, scaled to fit within page width, centered."""
    global _inserted_images

    key = raw_path.replace('\\', '/')
    if key in _inserted_images:
        return
    _inserted_images.add(key)

    img_path = resolve_image_path(raw_path)
    if img_path is None:
        p = add_body_paragraph(doc, f'[图片未找到: {raw_path}]')
        p.runs[0].italic = True
        return

    p = doc.add_paragraph()
    set_paragraph_format(
        p,
        alignment=WD_ALIGN_PARAGRAPH.CENTER,
        space_before=SP_IMAGE_BEFORE,
        space_after=SP_IMAGE_AFTER,
        line_spacing=LINE_SPACING_BODY,
        line_spacing_rule=3,
    )  # AT_LEAST

    try:
        from PIL import Image as PILImage

        with PILImage.open(img_path) as pil_img:
            orig_w, orig_h = pil_img.size
    except Exception:
        orig_w, orig_h = 800, 600

    max_width = Inches(5.5)
    max_height = Inches(5.0)
    img_w = orig_w / 96.0
    img_h = orig_h / 96.0

    scale = min(
        max_width / Inches(img_w) if img_w > 0 else 1,
        max_height / Inches(img_h) if img_h > 0 else 1,
        1.0,
    )
    final_w = Inches(img_w * scale)
    final_h = Inches(img_h * scale)

    run = p.add_run()
    run.add_picture(str(img_path), width=final_w, height=final_h)

    # Figure caption: centered, 黑体 east-asia font
    if alt_text:
        cap = doc.add_paragraph()
        set_paragraph_format(
            cap,
            alignment=WD_ALIGN_PARAGRAPH.CENTER,
            space_before=Pt(2),
            space_after=SP_CAPTION_AFTER,
            line_spacing=LINE_SPACING_BODY,
            line_spacing_rule=4,
        )
        run = cap.add_run(alt_text)
        set_chinese_font(
            run, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )


def add_table(doc, headers: list[str], rows: list[list[str]]):
    """Add a Word table from parsed markdown table data.
    Matches template: 10.5pt centered text, top/bottom/insideH borders only."""
    num_cols = len(headers)
    table = doc.add_table(rows=1 + len(rows), cols=num_cols)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = True

    # Style: borders (top, bottom, insideH only - matching template)
    tbl = table._tbl
    tblPr = (
        tbl.tblPr if tbl.tblPr is not None else parse_xml(f'<w:tblPr {nsdecls("w")}/>')
    )
    borders = parse_xml(
        f'<w:tblBorders {nsdecls("w")}>'
        '  <w:top w:val="single" w:sz="4" w:space="0" w:color="auto"/>'
        '  <w:bottom w:val="single" w:sz="4" w:space="0" w:color="auto"/>'
        '  <w:insideH w:val="single" w:sz="4" w:space="0" w:color="auto"/>'
        '</w:tblBorders>'
    )
    tblPr.append(borders)

    # Header row: centered, 10.5pt, no bold, no background
    for j, header in enumerate(headers):
        cell = table.cell(0, j)
        cell.text = ''
        p = cell.paragraphs[0]
        set_paragraph_format(
            p,
            alignment=WD_ALIGN_PARAGRAPH.CENTER,
            line_spacing=LINE_SPACING_BODY,
            line_spacing_rule=4,
        )
        run = p.add_run(header.strip())
        set_chinese_font(
            run, font_name_cn=FONT_TABLE, font_name_en=FONT_TABLE_EN, size=SZ_TABLE
        )

    # Data rows: centered, 10.5pt
    for i, row in enumerate(rows):
        for j in range(min(len(row), num_cols)):
            cell = table.cell(i + 1, j)
            cell.text = ''
            p = cell.paragraphs[0]
            set_paragraph_format(
                p,
                alignment=WD_ALIGN_PARAGRAPH.CENTER,
                line_spacing=LINE_SPACING_BODY,
                line_spacing_rule=4,
            )
            run = p.add_run(row[j].strip())
            set_chinese_font(
                run, font_name_cn=FONT_TABLE, font_name_en=FONT_TABLE_EN, size=SZ_TABLE
            )

    # Spacing after table
    p = doc.add_paragraph()
    set_paragraph_format(p, line_spacing=LINE_SPACING_BODY, line_spacing_rule=4)
    return table


def add_table_caption(doc, text: str):
    """Add a table caption: centered, 黑体 east-asia, number bold."""
    p = doc.add_paragraph()
    set_paragraph_format(
        p,
        alignment=WD_ALIGN_PARAGRAPH.CENTER,
        space_before=SP_CAPTION_BEFORE,
        space_after=SP_CAPTION_AFTER,
        line_spacing=LINE_SPACING_BODY,
        line_spacing_rule=4,
    )
    m = re.match(r'(表\s*)(\d+\.?\d*)(\s*)(.*)', text)
    if m:
        run1 = p.add_run(m.group(1))
        set_chinese_font(
            run1, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )
        run2 = p.add_run(m.group(2))
        set_chinese_font(
            run2, font_name_cn=FONT_CAPTION_NUM, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )
        run2.bold = True
        run3 = p.add_run(m.group(3))
        set_chinese_font(
            run3, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )
        run4 = p.add_run(m.group(4))
        set_chinese_font(
            run4, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )
    else:
        run = p.add_run(text)
        set_chinese_font(
            run, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_BODY
        )


def parse_inline(
    paragraph, text: str, font_cn=FONT_BODY_CN, font_en=FONT_BODY_EN, size=SZ_BODY
):
    """Parse inline markdown (bold, code, plain) and add runs to paragraph."""
    pattern = re.compile(r'(\*\*(.+?)\*\*|`([^`]+)`|([^*`]+))')
    for m in pattern.finditer(text):
        if m.group(2) is not None:
            run = paragraph.add_run(m.group(2))
            set_chinese_font(run, font_name_cn=font_cn, font_name_en=font_en, size=size)
            run.bold = True
        elif m.group(3) is not None:
            run = paragraph.add_run(m.group(3))
            run.font.name = FONT_CODE
            run.font.size = Pt(10.5)
            rpr = run.font.element.get_or_add_rPr()
            shd = parse_xml(f'<w:shd {nsdecls("w")} w:fill="F0F0F0" w:val="clear"/>')
            rpr.append(shd)
        elif m.group(4) is not None:
            run = paragraph.add_run(m.group(4))
            set_chinese_font(run, font_name_cn=font_cn, font_name_en=font_en, size=size)


def add_code_block(doc, code_text: str):
    """Add a code block as a monospace paragraph with gray background."""
    p = doc.add_paragraph()
    set_paragraph_format(
        p,
        first_line_indent=None,
        line_spacing=1.15,
        space_before=Pt(4),
        space_after=Pt(4),
    )
    pPr = p._p.get_or_add_pPr()
    shd = parse_xml(f'<w:shd {nsdecls("w")} w:fill="F5F5F5" w:val="clear"/>')
    pPr.append(shd)

    run = p.add_run(code_text)
    run.font.name = FONT_CODE
    run.font.size = SZ_CODE


def add_bullet_list(doc, items: list[str], ordered: bool = False):
    """Add bullet or numbered list items."""
    style_name = 'List Number' if ordered else 'List Bullet'
    for idx, item in enumerate(items):
        p = doc.add_paragraph(style=style_name)
        parse_inline(p, item)


def process_chapter(doc, md_path: Path):
    """Parse a markdown chapter and add content to the document."""
    print(f'  Processing: {md_path.name}')
    text = md_path.read_text(encoding='utf-8')
    lines = text.split('\n')

    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        stripped = line.strip()

        if not stripped:
            i += 1
            continue

        if stripped in ('---', '***', '___'):
            i += 1
            continue

        # Code block
        if stripped.startswith('```'):
            code_lines = []
            i += 1
            while i < n and not lines[i].strip().startswith('```'):
                code_lines.append(lines[i])
                i += 1
            i += 1
            add_code_block(doc, '\n'.join(code_lines))
            continue

        # Heading 1: # 第X章 - 黑体 18pt centered bold
        if stripped.startswith('# ') and not stripped.startswith('## '):
            global _body_section_started
            if not _body_section_started:
                _body_section_started = True
                doc.add_section()
            title = stripped[2:].strip()
            p = doc.add_paragraph(style='Heading 1')
            set_paragraph_format(
                p,
                alignment=WD_ALIGN_PARAGRAPH.CENTER,
                space_before=SP_H1_BEFORE,
                space_after=SP_H1_AFTER,
                line_spacing=1.0,
                line_spacing_rule=0,
            )  # SINGLE
            run = p.add_run(title)
            set_chinese_font(
                run, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_H1
            )
            run.bold = True
            i += 1
            continue

        # Heading 2: ## X.X - 黑体 14pt left-aligned
        if stripped.startswith('## ') and not stripped.startswith('### '):
            title = stripped[3:].strip()
            p = doc.add_paragraph(style='Heading 2')
            set_paragraph_format(
                p,
                alignment=WD_ALIGN_PARAGRAPH.LEFT,
                space_before=SP_H2_BEFORE,
                space_after=SP_H2_AFTER,
                line_spacing=1.0,
                line_spacing_rule=0,
            )
            run = p.add_run(title)
            set_chinese_font(
                run, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_H2
            )
            run.bold = True
            i += 1
            continue

        # Heading 3: ### X.X.X - 黑体 12pt left-aligned
        if stripped.startswith('### ') and not stripped.startswith('#### '):
            title = stripped[4:].strip()
            p = doc.add_paragraph(style='Heading 3')
            set_paragraph_format(
                p,
                alignment=WD_ALIGN_PARAGRAPH.LEFT,
                space_before=SP_H3_BEFORE,
                space_after=SP_H3_AFTER,
                line_spacing=1.0,
                line_spacing_rule=0,
            )
            run = p.add_run(title)
            set_chinese_font(
                run, font_name_cn=FONT_HEADING_CN, font_name_en=FONT_BODY_EN, size=SZ_H3
            )
            run.bold = True
            i += 1
            continue

        # Image: ![alt](path)
        img_match = re.match(r'!\[([^\]]*)\]\(([^)]+)\)', stripped)
        if img_match:
            alt_text = img_match.group(1)
            img_path = img_match.group(2)
            add_image(doc, img_path, alt_text)
            i += 1
            continue

        # Table caption: 表X.X description
        if re.match(r'^表\s*\d+', stripped) and len(stripped) < 80:
            add_table_caption(doc, stripped)
            i += 1
            continue

        # Figure caption: 图X.X description
        if re.match(r'^图\s*\d+', stripped) and len(stripped) < 80:
            cap = doc.add_paragraph()
            set_paragraph_format(
                cap,
                alignment=WD_ALIGN_PARAGRAPH.CENTER,
                space_before=Pt(2),
                space_after=SP_CAPTION_AFTER,
                line_spacing=LINE_SPACING_BODY,
                line_spacing_rule=4,
            )
            m = re.match(r'(图\s*)(\d+\.?\d*)(\s*)(.*)', stripped)
            if m:
                run1 = cap.add_run(m.group(1))
                set_chinese_font(
                    run1,
                    font_name_cn=FONT_HEADING_CN,
                    font_name_en=FONT_BODY_EN,
                    size=SZ_BODY,
                )
                run2 = cap.add_run(m.group(2))
                set_chinese_font(
                    run2,
                    font_name_cn=FONT_CAPTION_NUM,
                    font_name_en=FONT_BODY_EN,
                    size=SZ_BODY,
                )
                run2.bold = True
                run3 = cap.add_run(m.group(3))
                set_chinese_font(
                    run3,
                    font_name_cn=FONT_HEADING_CN,
                    font_name_en=FONT_BODY_EN,
                    size=SZ_BODY,
                )
                run4 = cap.add_run(m.group(4))
                set_chinese_font(
                    run4,
                    font_name_cn=FONT_HEADING_CN,
                    font_name_en=FONT_BODY_EN,
                    size=SZ_BODY,
                )
            else:
                run = cap.add_run(stripped)
                set_chinese_font(
                    run,
                    font_name_cn=FONT_HEADING_CN,
                    font_name_en=FONT_BODY_EN,
                    size=SZ_BODY,
                )
            i += 1
            continue

        # Table: detect header row with pipes
        if '|' in stripped and stripped.startswith('|'):
            table_lines = []
            while (
                i < n and '|' in lines[i].strip() and lines[i].strip().startswith('|')
            ):
                table_lines.append(lines[i].strip())
                i += 1

            if len(table_lines) >= 2:
                headers = [c.strip() for c in table_lines[0].split('|')[1:-1]]
                data_start = 1
                if len(table_lines) > 1 and re.match(r'^[\s|:-]+$', table_lines[1]):
                    data_start = 2

                rows = []
                for tl in table_lines[data_start:]:
                    cells = [c.strip() for c in tl.split('|')[1:-1]]
                    rows.append(cells)

                add_table(doc, headers, rows)
            continue

        # Bullet list: - item
        if re.match(r'^[-*]\s+', stripped):
            items = []
            while i < n and re.match(r'^[-*]\s+', lines[i].strip()):
                items.append(re.sub(r'^[-*]\s+', '', lines[i].strip()))
                i += 1
            add_bullet_list(doc, items, ordered=False)
            continue

        # Numbered list: 1. item — preserve as body paragraphs with inline numbers
        # (Word's List Number style continues numbering globally, which is incorrect for thesis)
        if re.match(r'^\d+\.\s+', stripped):
            items = []
            while i < n and re.match(r'^\d+\.\s+', lines[i].strip()):
                items.append(lines[i].strip())
                i += 1
            for item in items:
                p = doc.add_paragraph()
                set_paragraph_format(
                    p,
                    first_line_indent=FIRST_LINE_INDENT,
                    line_spacing=LINE_SPACING_BODY,
                    line_spacing_rule=4,
                )
                parse_inline(p, item)
                if not p.runs:
                    run = p.add_run(item)
                    set_chinese_font(run)
            continue

        # Block quote: > text
        if stripped.startswith('> '):
            quote_text = stripped[2:].strip()
            p = doc.add_paragraph()
            set_paragraph_format(
                p,
                first_line_indent=FIRST_LINE_INDENT,
                line_spacing=LINE_SPACING_BODY,
                line_spacing_rule=4,
            )
            pPr = p._p.get_or_add_pPr()
            pBdr = parse_xml(
                f'<w:pBdr {nsdecls("w")}>'
                '  <w:left w:val="single" w:sz="12" w:space="4" w:color="CCCCCC"/>'
                '</w:pBdr>'
            )
            pPr.append(pBdr)
            run = p.add_run(quote_text)
            set_chinese_font(run)
            run.italic = True
            i += 1
            continue

        # Reference-style table placeholders like [表X-X: description]
        if re.match(r'^\[表\d+', stripped):
            p = add_body_paragraph(doc, stripped)
            p.runs[0].italic = True
            i += 1
            continue

        # Regular body paragraph - 宋体+Times New Roman 12pt, 23pt EXACTLY, 2-char indent
        p = doc.add_paragraph()
        set_paragraph_format(
            p,
            first_line_indent=FIRST_LINE_INDENT,
            line_spacing=LINE_SPACING_BODY,
            line_spacing_rule=4,
        )
        parse_inline(p, stripped)
        if not p.runs:
            run = p.add_run(stripped)
            set_chinese_font(run)
        i += 1


# ---------------------------------------------------------------------------
# Page header / footer
# ---------------------------------------------------------------------------
def setup_headers_footers(doc):
    """Add header text matching template.

    Template layout:
    - Section 0 (cover): no header text
    - Sections 1+: "上海大学本科毕业论文（设计）" in 宋体 10.5pt centered, bottom border
    """
    for idx, section in enumerate(doc.sections):
        # Section 0 (cover): blank header
        if idx == 0:
            header = section.header
            header.is_linked_to_previous = False
            if header.paragraphs:
                hp = header.paragraphs[0]
            else:
                hp = header.add_paragraph()
            hp.text = ''
            continue

        # Sections 1+: header with text
        header = section.header
        header.is_linked_to_previous = False
        if not header.paragraphs:
            hp = header.add_paragraph()
        else:
            hp = header.paragraphs[0]
        hp.text = ''
        set_paragraph_format(hp, alignment=WD_ALIGN_PARAGRAPH.CENTER)
        run = hp.add_run('上海大学本科毕业论文（设计）')
        set_chinese_font(
            run, font_name_cn=FONT_HEADER, font_name_en=FONT_BODY_EN, size=SZ_HEADER
        )

        # Bottom border on header paragraph
        pPr = hp._p.get_or_add_pPr()
        pBdr = parse_xml(
            f'<w:pBdr {nsdecls("w")}>'
            '  <w:bottom w:val="single" w:sz="4" w:space="1" w:color="000000"/>'
            '</w:pBdr>'
        )
        pPr.append(pBdr)


def _add_page_number_field(paragraph):
    """Add a PAGE field to a paragraph for automatic page numbering."""
    run1 = paragraph.add_run()
    fldChar1 = parse_xml(f'<w:fldChar {nsdecls("w")} w:fldCharType="begin"/>')
    run1._r.append(fldChar1)
    run2 = paragraph.add_run()
    instrText = parse_xml(
        f'<w:instrText {nsdecls("w")} xml:space="preserve"> PAGE </w:instrText>'
    )
    run2._r.append(instrText)
    run3 = paragraph.add_run()
    fldChar2 = parse_xml(f'<w:fldChar {nsdecls("w")} w:fldCharType="end"/>')
    run3._r.append(fldChar2)


def add_page_numbers(doc):
    """Set up page numbering per template:
    - Section 0 (cover): no page number
    - Section 1 (abstract/TOC): Roman numerals, restart at 1
    - Section 2+ (body/refs): Arabic numerals, continue
    """
    for idx, section in enumerate(doc.sections):
        footer = section.footer

        if idx == 0:
            # Cover: no page numbers
            footer.is_linked_to_previous = False
            if footer.paragraphs:
                footer.paragraphs[0].text = ''
            continue

        footer.is_linked_to_previous = False
        if not footer.paragraphs:
            fp = footer.add_paragraph()
        else:
            fp = footer.paragraphs[0]
        fp.text = ''
        set_paragraph_format(fp, alignment=WD_ALIGN_PARAGRAPH.CENTER)

        if idx == 1:
            # Abstract/TOC: Roman numerals, restart at 1
            sectPr = section._sectPr
            pgNumType = sectPr.find(qn('w:pgNumType'))
            if pgNumType is None:
                pgNumType = parse_xml(f'<w:pgNumType {nsdecls("w")}/>')
                sectPr.append(pgNumType)
            pgNumType.set(qn('w:fmt'), 'upperRoman')
            pgNumType.set(qn('w:start'), '1')
        else:
            # Body+: Arabic numerals, continue from previous
            sectPr = section._sectPr
            pgNumType = sectPr.find(qn('w:pgNumType'))
            if pgNumType is not None:
                sectPr.remove(pgNumType)

        _add_page_number_field(fp)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
def main():
    print('=' * 60)
    print('Thesis DOCX Generator')
    print('=' * 60)

    doc = Document()

    # -- Page setup: A4, margins matching template exactly --
    section = doc.sections[0]
    section.page_width = Cm(21.00)
    section.page_height = Cm(29.70)
    section.top_margin = Cm(2.50)
    section.bottom_margin = Cm(2.50)
    section.left_margin = Cm(3.00)
    section.right_margin = Cm(2.50)
    section.header_distance = Cm(1.50)
    section.footer_distance = Cm(1.50)

    # -- Default paragraph style (Normal) --
    style = doc.styles['Normal']
    style.font.name = FONT_BODY_EN
    style.font.size = SZ_BODY
    style.paragraph_format.line_spacing = Pt(20)
    style.paragraph_format.line_spacing_rule = 4  # EXACTLY
    style.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.JUSTIFY
    rpr = style.font.element.get_or_add_rPr()
    rfonts = rpr.find(qn('w:rFonts'))
    if rfonts is None:
        rfonts = parse_xml(f'<w:rFonts {nsdecls("w")} />')
        rpr.insert(0, rfonts)
    rfonts.set(qn('w:eastAsia'), FONT_BODY_CN)
    rfonts.set(qn('w:ascii'), FONT_BODY_EN)
    rfonts.set(qn('w:hAnsi'), FONT_BODY_EN)

    # -- Heading 1 style: 黑体, 18pt, centered, bold --
    h1_style = doc.styles['Heading 1']
    h1_style.font.size = SZ_H1
    h1_style.font.bold = True
    h1_style.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.CENTER
    h1_style.paragraph_format.space_before = SP_H1_BEFORE
    h1_style.paragraph_format.space_after = SP_H1_AFTER
    h1_rpr = h1_style.font.element.get_or_add_rPr()
    h1_rf = h1_rpr.find(qn('w:rFonts'))
    if h1_rf is None:
        h1_rf = parse_xml(f'<w:rFonts {nsdecls("w")} />')
        h1_rpr.insert(0, h1_rf)
    h1_rf.set(qn('w:eastAsia'), FONT_HEADING_CN)

    # -- Heading 2 style: 黑体, 14pt, left --
    h2_style = doc.styles['Heading 2']
    h2_style.font.size = SZ_H2
    h2_style.font.bold = True
    h2_style.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.LEFT
    h2_style.paragraph_format.space_before = SP_H2_BEFORE
    h2_style.paragraph_format.space_after = SP_H2_AFTER
    h2_rpr = h2_style.font.element.get_or_add_rPr()
    h2_rf = h2_rpr.find(qn('w:rFonts'))
    if h2_rf is None:
        h2_rf = parse_xml(f'<w:rFonts {nsdecls("w")} />')
        h2_rpr.insert(0, h2_rf)
    h2_rf.set(qn('w:eastAsia'), FONT_HEADING_CN)

    # -- Heading 3 style: 黑体, 12pt, left --
    h3_style = doc.styles['Heading 3']
    h3_style.font.size = SZ_H3
    h3_style.font.bold = True
    h3_style.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.LEFT
    h3_style.paragraph_format.space_before = SP_H3_BEFORE
    h3_style.paragraph_format.space_after = SP_H3_AFTER
    h3_rpr = h3_style.font.element.get_or_add_rPr()
    h3_rf = h3_rpr.find(qn('w:rFonts'))
    if h3_rf is None:
        h3_rf = parse_xml(f'<w:rFonts {nsdecls("w")} />')
        h3_rpr.insert(0, h3_rf)
    h3_rf.set(qn('w:eastAsia'), FONT_HEADING_CN)

    # -- Cover page --
    print('Creating cover page...')
    create_cover_page(doc)

    # -- Process chapters --
    for ch_path in CHAPTERS:
        if not ch_path.exists():
            print(f'  WARNING: Chapter not found: {ch_path.name}')
            continue
        process_chapter(doc, ch_path)

    # -- Headers and footers --
    print('Setting up headers and footers...')
    setup_headers_footers(doc)
    add_page_numbers(doc)

    # -- Save --
    doc.save(str(OUTPUT_PATH))
    print(f'\nDone! Output saved to: {OUTPUT_PATH}')


if __name__ == '__main__':
    main()
