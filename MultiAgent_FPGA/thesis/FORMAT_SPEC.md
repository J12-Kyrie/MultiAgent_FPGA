# Shanghai University Undergraduate Thesis Format Specification

Extracted from template file: `上海大学本科毕业论文（设计）撰写格式模板.docx`

## 1. Page Setup

| Property | Value |
|----------|-------|
| Paper size | A4 (21.00 cm x 29.70 cm) |
| Top margin | 2.50 cm |
| Bottom margin | 2.50 cm |
| Left margin | 3.00 cm |
| Right margin | 2.50 cm |
| Header distance | 1.50 cm |
| Footer distance | 1.50 cm |
| Gutter | 0 |

## 2. Sections (5 total)

| Section | Content | Header | Footer/Page# |
|---------|---------|--------|-------------|
| 0 | Cover page | No text | None |
| 1 | Declaration (原创性声明 + 使用授权) | "上海大学本科毕业论文（设计）" | None |
| 2 | Abstract + TOC | "上海大学本科毕业论文（设计）" | Roman numerals (I, II, ...) |
| 3 | Body chapters | "上海大学本科毕业论文（设计）" | Arabic numerals (1, 2, ...) |
| 4 | References / Appendix / Acknowledgement | "上海大学本科毕业论文（设计）" | Arabic (continued) |

Section break between cover and declaration is `nextPage` (default).
Page numbering restarts at 1 (Arabic) for the body section.

## 3. Default Style (Normal / a1)

| Property | Value |
|----------|-------|
| Western font | Times New Roman (ascii + hAnsi) |
| East-Asian font | Song Ti (宋体) |
| Font size | 12 pt (xiao si / small four) — `<w:sz w:val="24"/>` (24 half-points) |
| Complex script size | 11 pt — `<w:szCs w:val="22"/>` |
| Kerning | 2 pt — `<w:kern w:val="2"/>` |
| Alignment | Justify (both sides) — `<w:jc w:val="both"/>` |
| Line spacing | 20 pt, EXACTLY rule — `<w:spacing w:line="400" w:lineRule="exact"/>` |
| First-line indent | None (default) |
| Widow control | Off — `<w:widowControl w:val="0"/>` |

Note: Many paragraph-level overrides in the template body content (sample text,
annotations) use the Normal style rather than 论文正文1. The annotation text
states the intended body format is: "宋体，Times New Roman小四号字，两边对齐，
首行缩进2个字符，行距23磅". Actual thesis content paragraphs should use
论文正文1 or equivalent formatting.

## 4. Cover Page

### Title line
- Text: "本科毕业论文（设计）"
- Font: Fang Zheng Cu Song (方正粗宋简体) for both ascii and eastAsia
- Size: 42 pt (533400 EMU)
- Alignment: Center
- Line spacing: 2.0 (DOUBLE rule)
- Color: #000000

### English subtitle
- Text: "UNDERGRADUATE  THESIS (PROJECT)"
- Font: Fang Zheng Cu Song (方正粗宋简体)
- Size: 18 pt (228600 EMU)
- Alignment: Center
- Line spacing: 2.0 (DOUBLE rule)

### Field: 题 目 (Title)
- Label font: Fang Zheng Cu Song, 18 pt
- Value font: Fang Zheng Cu Song, 18 pt
- Alignment: Left
- First-line indent: 1.90 cm (685800 EMU)
- Line spacing: 2.0 (DOUBLE rule)

### Fields: 学院 / 专业 / 学号 / 学生姓名 / 指导教师 / 起讫日期
- Label font: Fang Zheng Cu Song, 16 pt (203200 EMU)
- Value font: Fang Zheng Cu Song, 18 pt (228600 EMU)
- Alignment: Left
- First-line indent: 1.69 cm (609600 EMU)
- Line spacing: 2.0 (DOUBLE rule)

## 5. Declaration Page (原创性声明)

### Section title: "原 创 性 声 明"
- Font: Song Ti (宋体)
- Size: 22 pt (279400 EMU)
- Bold: Yes
- Alignment: Center
- Line spacing: 1.5 (ONE_POINT_FIVE rule)

### Body text
- Font: Song Ti (宋体), 14 pt (177800 EMU)
- First-line indent: 0.99 cm (355600 EMU)
- Line spacing: 1.5

### "本论文使用授权说明"
- Font: Song Ti (宋体), 22 pt (279400 EMU), Bold
- Alignment: Center
- Line spacing: 1.5

## 6. Abstract (Chinese)

### Title: "摘  要"
- Font: Hei Ti (黑体) for eastAsia, 18 pt (228600 EMU)
- Alignment: Center
- Space before: 158115 EMU (~4.39 cm) — paragraph-level override on Normal style
- Space after: 99060 EMU (~2.75 cm) — paragraph-level override on Normal style

### Body text
- Inherit Normal style (Song Ti + Times New Roman, 12 pt)
- First-line indent: 0.85 cm (304800 EMU = 24 pt = 2 chars at 12pt)
- Line spacing: 20 pt (from Normal style, not explicitly set on paragraphs)
- Alignment: inherits Normal (Justify)

### Keywords line
- "关键词：" in bold
- Rest in normal weight
- Space before: 1.76 cm (63500 EMU)

## 7. Abstract (English / ABSTRACT)

### Title: "ABSTRACT"
- Size: 18 pt (228600 EMU)
- Alignment: Center

### Body text
- Times New Roman, 12 pt (xiao si)
- First-line indent: 0.85 cm (304800 EMU)
- Line spacing: 20 pt (from Normal style)

### Keywords
- "Keywords:" bold
- Rest normal

## 8. Table of Contents

### Title: "目  录"
- Style: TOC 标题1 (custom style, based on Heading 1 / styleId "1")
- Font: Deng Xian Light (等线 Light) for ascii/eastAsia/hAnsi — **not** Hei Ti
- Size: 16 pt — `<w:sz w:val="32"/>` (32 half-points)
- Bold: Yes
- Color: #2F5496 (dark blue)
- Alignment: Center (paragraph-level override; style defines LEFT)
- Space before: 158115 EMU (~4.39 cm) — paragraph-level override
- Space after: 99060 EMU (~2.75 cm) — paragraph-level override
- Style-level spacing: `<w:spacing w:before="240" w:after="0" w:line="259" w:lineRule="auto"/>`

### TOC Level 1 (Chapter entries)
- Style: toc 1 (styleId "11")
- **Style-level** font: Hei Ti (黑体) eastAsia, 14 pt — `<w:sz w:val="28"/>`
- **Run-level** font: Hei Ti (黑体), 12 pt (152400 EMU), Bold — actual rendered formatting overrides style
- Space after: 100 twips (style-level: `<w:spacing w:after="100"/>`) = ~1.76 cm in rendered output
- Line spacing: 1.5x (MULTIPLE/auto) — `<w:spacing w:line="360" w:lineRule="auto"/>`
- No left indent (style-level)
- Tab stops: left at 440 twips, right with dot leader at 8777 twips

### TOC Level 2 (Section entries)
- Style: toc 2 (styleId "21")
- **Font: inherits from base (Normal) — no explicit font in style or runs**
- **Should be: Hei Ti (黑体), 12 pt, Bold per template annotation**
- Indent left: 220 twips = 0.35 cm — `<w:ind w:left="220"/>`
  (FORMAT_SPEC previously stated 0.39 cm / 139700 EMU; actual XML value is 220 twips)
- Space after: 100 twips (style-level)
- Line spacing: 1.079x (MULTIPLE/auto) — `<w:spacing w:line="259" w:lineRule="auto"/>`
- Tab stops: left at 840 twips, right with dot leader at 8777 twips

### TOC Level 3 (Subsection entries)
- Style: toc 3 (styleId "31")
- Font: Deng Xian (等线) — `<w:rFonts w:ascii="等线" w:eastAsia="等线" w:hAnsi="等线"/>`
- Size: 11 pt — `<w:sz w:val="22"/>`
- Indent left: 440 twips = 0.77 cm — `<w:ind w:left="440"/>`
  (FORMAT_SPEC previously stated 0.78 cm / 279400 EMU; actual XML value is 440 twips)
- Space after: 100 twips (style-level)
- Line spacing: 1.079x (MULTIPLE/auto) — `<w:spacing w:line="259" w:lineRule="auto"/>`
- Tab stops: left at 1260 twips, right with dot leader at 8777 twips

## 9. Heading Styles

### Heading 1 (Chapter: 1, 2, 3, ...)
- Style name: "Heading 1" (styleId "1", based on Normal / a1)
- Font: Hei Ti (黑体) eastAsia — `<w:rFonts w:eastAsia="黑体"/>`
- Size: 18 pt — `<w:sz w:val="36"/>` (36 half-points)
- Complex script size: 22 pt — `<w:szCs w:val="44"/>`
- Bold: `<w:bCs/>` (complex script bold); run-level paragraphs apply bold explicitly
- Alignment: Center (paragraph-level override)
- Space before: 158115 EMU (~4.39 cm) — **paragraph-level override** (style defines 80 twips = ~4pt)
- Space after: 99060 EMU (~2.75 cm) — **paragraph-level override** (style defines 50 twips = ~2.5pt)
- Line spacing: 1.0x (MULTIPLE/auto) — `<w:spacing w:line="240" w:lineRule="auto"/>`
- Kerning: 44 pt — `<w:kern w:val="44"/>`
- keepNext + keepLines: Yes
- Outline level: 0

### Heading 2 (Section: 1.1, 1.2, ...)
- Style name: "Heading 2" (styleId "2", based on Normal / a1)
- Font: Hei Ti (黑体) eastAsia
- Size: 14 pt — `<w:sz w:val="28"/>` (28 half-points)
- Complex script size: 16 pt — `<w:szCs w:val="32"/>`
- Bold: run-level paragraphs apply bold explicitly
- Alignment: Left (paragraph-level override)
- Space before: 99060 EMU (~2.75 cm) — **paragraph-level override** (style defines 50 twips = ~2.5pt)
- Space after: 99060 EMU (~2.75 cm) — **paragraph-level override** (style defines 50 twips = ~2.5pt)
- Line spacing: 1.0x (MULTIPLE/auto)
- keepNext + keepLines: Yes
- Outline level: 1

### Heading 3 (Subsection: 1.2.1, 1.2.2, ...)
- Style name: "Heading 3" (styleId "3", based on Normal / a1)
- Font: Hei Ti (黑体) eastAsia
- Size: 12 pt — **inherited from Normal style** (no `<w:sz>` in style; only `<w:szCs w:val="32"/>`)
- Complex script size: 16 pt — `<w:szCs w:val="32"/>`
- Bold: run-level paragraphs apply bold explicitly
- Alignment: Left (paragraph-level override)
- Space before: 99060 EMU (~2.75 cm) — **paragraph-level override** (style defines 50 twips = ~2.5pt)
- Space after: 99060 EMU (~2.75 cm) — **paragraph-level override** (style defines 50 twips = ~2.5pt)
- Line spacing: 1.0x (MULTIPLE/auto)
- keepNext + keepLines: Yes
- Outline level: 2

### Important note on heading spacing
The heading style XML defines small spacing values (beforeLines/afterLines in twips),
but the template applies much larger **paragraph-level overrides** (in EMU). When
generating headings programmatically, use the paragraph-level override values listed
above (158115/99060 for H1, 99060/99060 for H2/H3), not the style-level values.

## 10. Body Text (论文正文1 style)

| Property | Value |
|----------|-------|
| Style name | 论文正文1 (styleId "13", custom style) |
| Based on | Normal (a1) |
| Linked character style | 论文正文1 字符 (styleId "14") |
| Western font | Times New Roman (via linked character style) |
| East-Asian font | Song Ti / 宋体 (via linked character style) |
| Font size | 12 pt (xiao si) — `<w:sz w:val="24"/>` in linked char style |
| Complex script size | 10 pt — `<w:szCs w:val="20"/>` in paragraph style |
| Alignment | Left — `<w:jc w:val="left"/>` |
| First-line indent | 2 characters — `<w:ind w:firstLineChars="200" w:firstLine="200"/>` |
| | (firstLineChars=200 means 2 chars; firstLine=200 twips = 10pt fallback) |
| | (At 12pt font: 2 chars = 24pt = 304800 EMU = 0.85 cm) |
| Line spacing | 23 pt, EXACTLY rule — `<w:spacing w:line="460" w:lineRule="exact"/>` |
| | (460 twips = 23 pt = 292100 EMU) |
| Character spacing | Standard |

Note: The template red annotation text explicitly states:
"宋体，Times New Roman小四号字，两边对齐，首行缩进2个字符，行距23磅"

**Discrepancy**: The annotation says "两边对齐" (Justify), but the style XML defines
`<w:jc w:val="left"/>` (Left). The actual rendered body paragraphs in the template
show `align=None` (inheriting Justify from Normal) for most content paragraphs.
The generate_docx.py uses Justify for body text, which matches the annotation intent.

### "论文正文" style (base variant, styleId "a")
- Line spacing: 23 pt EXACTLY (460 twips / 292100 EMU) — same as 论文正文1
- First-line indent: 0 — `<w:ind w:left="0" w:firstLine="0"/>`
- No explicit alignment (inherits Normal = Justify)
- Linked character style: 论文正文 字符 — Times New Roman / 宋体, 12 pt
- Has numbering: `<w:numPr><w:numId w:val="3"/></w:numPr>`

## 11. Table Formatting

### Cell text
- Font size: 10.5 pt (133350 EMU) - xiao wu (small five)
- Alignment: Center (for all cells)
- No bold on data cells
- Header row: no special bold or background in template (just centered)

### Table borders
- Top/bottom: single, sz=4, color=auto
- Inside horizontal: single, sz=4, color=auto
- No left/right/outside vertical borders visible (only top, bottom, insideH)

### Table alignment: Center

## 12. Figure/Table Captions

### Table captions (e.g., "表2.1 ...")
- Alignment: Center
- "表" prefix: Hei Ti (黑体) eastAsia
- Number (e.g., "2.1"): Deng Xian (等线) eastAsia, Bold
- Description text: Hei Ti (黑体) eastAsia

### Figure captions (e.g., "图2.7 ...")
- Alignment: Center
- "图" prefix: Hei Ti (黑体) eastAsia
- Number (e.g., "2.7"): Deng Xian (等线) eastAsia, Bold
- Description text: Hei Ti (黑体) eastAsia

## 13. Page Header

### Sections 1-4 (all except cover)
- Text: "上海大学本科毕业论文（设计）"
- Font: Song Ti (宋体), 10.5 pt (133350 EMU)
- Alignment: Center
- Bottom border: single, sz=4 (0.5pt), space=1, color=000000
- Linked to previous: False (each section has its own header)

### Section 0 (cover)
- No header text (blank)

## 14. Page Footer / Page Numbers

### Section 2 (Abstract + TOC)
- Roman numerals (I, II, III, ...)
- Restart at 1

### Sections 3-4 (Body + References)
- Arabic numerals (1, 2, 3, ...)
- Continue from previous section

### Section 0-1 (Cover + Declaration)
- No page numbers

## 15. Reference / Bibliography Style

### Section heading: "参考文献"
- Style: Heading 1 (same as chapter headings)
- Font: Hei Ti (黑体), 18 pt, center

### Reference entries
- Style: "List Paragraph" (styleId "af6", based on Normal / a1)
- Left indent: 457200 EMU (~1.27 cm / 18 pt)
- Hanging indent: -457200 EMU (first_line_indent, creates hanging effect)
- **Note**: The template annotation says "悬挂缩进1.27 cm", confirming 1.27 cm hanging indent
- Line spacing: 23 pt EXACTLY (from body text formatting)
- This creates a hanging indent where the number [1] hangs left

### List Paragraph style definition
- Based on: Normal (a1)
- First-line indent: 2 chars, fallback 420 twips (21pt / 0.74cm)
  `<w:ind w:firstLineChars="200" w:firstLine="420"/>`
- No explicit font overrides (inherits Normal: Song Ti + Times New Roman, 12pt)

### Reference entry format
- "[序号] Author. Title[J/M/C/D]..."
- No special font overrides inherit from Normal (Song Ti + Times New Roman, 12 pt)

## 16. List Styles

### Bullet lists
- Style: "List Bullet" (built-in)
- First-line indent: 0.74 cm (266700 EMU) from List Paragraph style

### Numbered lists
- Style: "List Number" (built-in)

## 17. Code Blocks

### Inline code
- Font: Courier New, 10.5 pt
- Background shading: #F0F0F0

### Block code
- Font: Courier New, 10 pt
- Background shading: #F5F5F5
- Line spacing: 1.15

## 18. Special Custom Styles

### "论文正文" (styleId "a")
- Line spacing: 23 pt EXACTLY (460 twips / 292100 EMU)
- First-line indent: 0
- Left indent: 0
- Has numbering definition (numId=3)

### "论文正文1" (styleId "13")
- Line spacing: 23 pt EXACTLY (460 twips / 292100 EMU)
- First-line indent: 2 chars (firstLineChars=200), fallback 200 twips (10pt)
- Alignment: Left (`<w:jc w:val="left"/>`)
- Note: Template annotation says Justify; actual style says Left.
  Body content paragraphs in the template inherit Justify from Normal.

### "论文正文 字符" / "论文正文1 字符" (character styles)
- Font: Times New Roman (ascii/hAnsi/cs), 宋体 (eastAsia)
- Size: 12 pt (24 half-points) — `<w:sz w:val="24"/>`
- These are the linked character styles for 论文正文 and 论文正文1

### "List Paragraph" (styleId "af6")
- Based on: Normal (a1)
- First-line indent: 2 chars, fallback 420 twips (21pt / 0.74cm)

## 19. Font Size Reference (Chinese Typography)

| Chinese Name | Point Size | EMU |
|-------------|-----------|-----|
| chu (initial) | 42 pt | 533400 |
| xiao chu (small initial) | 36 pt | - |
| yi (one) | 26 pt | - |
| xiao yi (small one) | 24 pt | - |
| er (two) | 22 pt | 279400 |
| xiao er (small two) | 18 pt | 228600 |
| san (three) | 16 pt | 203200 |
| xiao san (small three) | 15 pt | - |
| si (four) | 14 pt | 177800 |
| xiao si (small four) | 12 pt | 152400 |
| wu (five) | 10.5 pt | 133350 |
| xiao wu (small five) | 9 pt | - |
| liu (six) | 7.5 pt | - |
| qi (seven) | 5.5 pt | - |
| ba (eight) | 5 pt | - |

## 20. Template XML Quick Reference

Key XML values for programmatic generation (all in OOXML units):

| Element | XML Attribute | Value | Meaning |
|---------|--------------|-------|---------|
| Normal line spacing | `w:line` | 400 | 20 pt (twips) |
| Body line spacing | `w:line` | 460 | 23 pt (twips) |
| Body first-line indent | `w:firstLineChars` | 200 | 2 characters (1/100th) |
| Body first-line indent | `w:firstLine` | 200 | 10 pt fallback (twips) |
| H1 spacing before | paragraph override | 158115 | EMU (~4.39 cm) |
| H1 spacing after | paragraph override | 99060 | EMU (~2.75 cm) |
| H2/H3 spacing | paragraph override | 99060 | EMU (~2.75 cm) |
| Ref hanging indent | `w:firstLine` | -457200 | EMU (~-1.27 cm) |
| Ref left indent | `w:left` | 457200 | EMU (~1.27 cm) |
| Heading 1 size | `w:sz` | 36 | 18 pt (half-points) |
| Heading 2 size | `w:sz` | 28 | 14 pt (half-points) |
| Normal size | `w:sz` | 24 | 12 pt (half-points) |
| TOC 1 line spacing | `w:line` | 360 | 1.5x (auto rule) |
| TOC 2/3 line spacing | `w:line` | 259 | ~1.079x (auto rule) |
