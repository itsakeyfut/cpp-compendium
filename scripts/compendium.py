#!/usr/bin/env python3
"""cpp-compendium の目次と雛形を管理するスクリプト

TOC.md を唯一の情報源として、次のファイルを生成・更新する。

  content/SUMMARY.md          mdBook の目次（全体を生成）
  content/STATUS.md           進捗表（全体を生成）
  content/pNN-xxx/README.md   Part の概要（章の表の部分だけを更新）
  content/pNN-xxx/exercises.md 実装課題（存在しないときだけ作成）

使い方:
  python scripts/compendium.py sync            # 生成・更新する
  python scripts/compendium.py sync --check    # 更新が必要なら終了コード1（CI用）
  python scripts/compendium.py new p03 06      # 章の雛形を作ってから sync する

標準ライブラリだけで動く（Python 3.9 以降）。
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TOC_PATH = ROOT / "TOC.md"
CONTENT = ROOT / "content"

LEVEL_NAMES = {1: "入門", 2: "基礎", 3: "実務", 4: "専門"}
STATUS_NAMES = {"todo": "未着手", "draft": "下書き", "done": "完成"}

BEGIN_MARK = "<!-- BEGIN chapters: scripts/compendium.py sync が自動生成するので手で編集しない -->"
END_MARK = "<!-- END chapters -->"
GENERATED_NOTE = "<!-- scripts/compendium.py sync が自動生成するので手で編集しない -->"


# ----------------------------------------------------------------------------
# データ構造
# ----------------------------------------------------------------------------


@dataclass
class Chapter:
    number: str  # "05"
    dir: str  # "05-move-semantics"
    title: str  # "ムーブセマンティクス"
    level: int  # 0（付録）〜 4
    topics: str
    part: Part = field(repr=False)

    @property
    def path(self) -> Path:
        return CONTENT / self.part.dir / self.dir

    @property
    def readme(self) -> Path:
        return self.path / "README.md"

    @property
    def exists(self) -> bool:
        return self.readme.exists()

    @property
    def status(self) -> str:
        if not self.exists:
            return "todo"
        head = self.readme.read_text(encoding="utf-8")[:200]
        match = re.search(r"<!--\s*status:\s*(\w+)\s*-->", head)
        if not match:
            return "draft"
        status = match.group(1)
        if status not in STATUS_NAMES:
            warn(f"{self.readme.relative_to(ROOT)}: 不明な status '{status}'")
        return status


@dataclass
class Part:
    title: str  # "Part 3　オブジェクトと所有権" / "付録"
    dir: str  # "p03-ownership" / "appendix"
    description: str = ""
    exercises: list[str] = field(default_factory=list)
    chapters: list[Chapter] = field(default_factory=list)

    @property
    def is_appendix(self) -> bool:
        return not re.match(r"^p\d\d-", self.dir)

    @property
    def id(self) -> str:
        return self.dir.split("-")[0]  # "p03" / "appendix"

    @property
    def path(self) -> Path:
        return CONTENT / self.dir


# ----------------------------------------------------------------------------
# TOC.md の読み込み
# ----------------------------------------------------------------------------

PART_HEADING = re.compile(r"^## (.+?)\s*`([^`]+)`\s*$")
TABLE_ROW = re.compile(r"^\|\s*(\d\d)\s*\|\s*`([^`]+)`\s*\|(.*)\|\s*$")
EXERCISES = re.compile(r"^\*\*実装課題\*\*[:：]\s*(.+)$")


def load_toc() -> list[Part]:
    parts: list[Part] = []
    current: Part | None = None

    for line in TOC_PATH.read_text(encoding="utf-8").splitlines():
        line = line.rstrip()

        if match := PART_HEADING.match(line):
            current = Part(title=match.group(1).strip(), dir=match.group(2))
            parts.append(current)
            continue
        if current is None:
            continue  # 凡例や規模の表は読み飛ばす

        if match := TABLE_ROW.match(line):
            cells = [cell.strip() for cell in match.group(3).split("|")]
            if current.is_appendix:  # | # | ディレクトリ | タイトル | 主な項目 |
                title, level, topics = cells[0], 0, cells[1]
            else:  # | # | ディレクトリ | タイトル | レベル | 主な項目 |
                title, level, topics = cells[0], cells[1].count("★"), cells[2]
            current.chapters.append(
                Chapter(match.group(1), match.group(2), title, level, topics, current)
            )
        elif match := EXERCISES.match(line):
            current.exercises = [item.strip() for item in match.group(1).split("、")]
        elif line and not line.startswith(("|", "#", "-")) and not current.description:
            current.description = line

    validate(parts)
    return parts


def validate(parts: list[Part]) -> None:
    for part in parts:
        for index, chapter in enumerate(part.chapters, start=1):
            expected = f"{index:02d}"
            if chapter.number != expected or not chapter.dir.startswith(expected + "-"):
                warn(f"TOC.md: {part.title} の章番号が連番になっていません: "
                     f"{chapter.number} `{chapter.dir}`（期待値 {expected}）")

    # TOC.md にない章ディレクトリが content/ にあれば知らせる
    known = {(p.dir, c.dir) for p in parts for c in p.chapters}
    for readme in CONTENT.glob("*/*/README.md"):
        key = (readme.parent.parent.name, readme.parent.name)
        if key not in known:
            warn(f"TOC.md にない章があります: content/{key[0]}/{key[1]}")


# ----------------------------------------------------------------------------
# 生成
# ----------------------------------------------------------------------------


def level_label(level: int) -> str:
    if level == 0:
        return ""
    return "★" * level + "☆" * (4 - level) + " " + LEVEL_NAMES[level]


def render_summary(parts: list[Part]) -> str:
    lines = [
        "# Summary",
        "",
        GENERATED_NOTE,
        "",
        "[はじめに](introduction.md)",
        "[進捗](STATUS.md)",
    ]
    for part in parts:
        lines += ["", f"# {part.title}", ""]
        lines.append(f"- [概要]({part.dir}/README.md)")
        for chapter in part.chapters:
            label = f"{chapter.number} {chapter.title}"
            if chapter.exists:
                lines.append(f"- [{label}]({part.dir}/{chapter.dir}/README.md)")
            else:
                lines.append(f"- [{label}]()")  # mdBook の下書き扱い（グレー表示）
        if part.exercises:
            lines.append(f"- [実装課題]({part.dir}/exercises.md)")
    return "\n".join(lines) + "\n"


def render_chapter_table(part: Part) -> str:
    if part.is_appendix:
        lines = ["| # | 項目 | 状態 |", "|---|---|---|"]
    else:
        lines = ["| # | 章 | レベル | 状態 |", "|---|---|---|---|"]
    for chapter in part.chapters:
        title = f"[{chapter.title}]({chapter.dir}/)" if chapter.exists else chapter.title
        status = STATUS_NAMES.get(chapter.status, chapter.status)
        if part.is_appendix:
            lines.append(f"| {chapter.number} | {title} | {status} |")
        else:
            lines.append(f"| {chapter.number} | {title} | {level_label(chapter.level)} | {status} |")
    return "\n".join([BEGIN_MARK, ""] + lines + ["", END_MARK])


def render_part_readme(part: Part) -> str:
    """Part の README.md を新しく作るときの雛形"""
    sections = [f"# {part.title}", ""]
    if part.description:
        sections += [part.description, ""]
    if not part.is_appendix:
        sections += [
            "## 到達目標",
            "",
            "<!-- このPartを読み終えたときにできるようになることを書く -->",
            "",
        ]
    sections += ["## 章", "", render_chapter_table(part), ""]
    if part.exercises:
        sections += ["## 実装課題", "", "[実装課題](exercises.md)を参照してください。", ""]
    return "\n".join(sections)


def update_part_readme(part: Part, current: str) -> str | None:
    """既存の README.md の章の表だけを差し替える。マーカーがなければ None"""
    pattern = re.compile(re.escape(BEGIN_MARK) + r".*?" + re.escape(END_MARK), re.DOTALL)
    if not pattern.search(current):
        return None
    return pattern.sub(lambda _: render_chapter_table(part), current)


def render_exercises(part: Part) -> str:
    lines = [
        f"# 実装課題：{part.title}",
        "",
        "課題文のみを示します。解答は用意しません。実装は別のリポジトリで自由に行ってください。",
        "",
    ]
    for index, exercise in enumerate(part.exercises, start=1):
        lines += [f"## 課題{index}：{exercise}", "", "<!-- 課題の詳細（要件、ヒント、発展）を書く -->", ""]
    return "\n".join(lines)


def render_status(parts: list[Part]) -> str:
    lines = ["# 進捗", "", GENERATED_NOTE, ""]
    lines += ["| Part | 章数 | 完成 | 下書き | 未着手 |", "|---|---|---|---|---|"]
    totals = {"all": 0, "done": 0, "draft": 0, "todo": 0}
    drafts: list[Chapter] = []

    for part in parts:
        counts = {"done": 0, "draft": 0, "todo": 0}
        for chapter in part.chapters:
            counts[chapter.status if chapter.status in counts else "draft"] += 1
            if chapter.status == "draft":
                drafts.append(chapter)
        lines.append(f"| [{part.title}]({part.dir}/) | {len(part.chapters)} | "
                     f"{counts['done']} | {counts['draft']} | {counts['todo']} |")
        totals["all"] += len(part.chapters)
        for key in counts:
            totals[key] += counts[key]

    lines.append(f"| **合計** | **{totals['all']}** | **{totals['done']}** | "
                 f"**{totals['draft']}** | **{totals['todo']}** |")

    lines += ["", "## 下書きの章", ""]
    if drafts:
        for chapter in drafts:
            lines.append(f"- [{chapter.part.title} / {chapter.number} {chapter.title}]"
                         f"({chapter.part.dir}/{chapter.dir}/)")
    else:
        lines.append("なし")
    return "\n".join(lines) + "\n"


def render_chapter_readme(chapter: Chapter) -> str:
    """新しい章の README.md の雛形（章テンプレート）"""
    level = level_label(chapter.level)
    header = f"{level}　`C++XX〜`" if level else ""
    return f"""<!-- status: draft -->

# {chapter.title}

{header}

> この章の内容を一文で表す。

---

## ⚡ 30秒で思い出す

-

---

## 📘 基本

---

## 🔬 深掘り

---

## ⚠️ 落とし穴とUB

---

## 🏭 実務・OSSではこう使われる

---

## 🦀 Rustとの対応

---

## ❓ 思い出しクイズ

**Q1.**

<details>
<summary>答え</summary>

</details>

---

## 📎 参照
"""


# ----------------------------------------------------------------------------
# コマンド
# ----------------------------------------------------------------------------


def warn(message: str) -> None:
    print(f"警告: {message}", file=sys.stderr)


def write_if_changed(path: Path, content: str, check: bool, changed: list[Path]) -> None:
    old = path.read_text(encoding="utf-8") if path.exists() else None
    if old == content:
        return
    changed.append(path)
    if not check:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8", newline="\n")


def sync(check: bool = False) -> int:
    parts = load_toc()
    changed: list[Path] = []

    write_if_changed(CONTENT / "SUMMARY.md", render_summary(parts), check, changed)
    write_if_changed(CONTENT / "STATUS.md", render_status(parts), check, changed)

    for part in parts:
        readme = part.path / "README.md"
        if readme.exists():
            updated = update_part_readme(part, readme.read_text(encoding="utf-8"))
            if updated is None:
                warn(f"{readme.relative_to(ROOT)}: 章の表のマーカーがないため更新しませんでした")
            else:
                write_if_changed(readme, updated, check, changed)
        else:
            write_if_changed(readme, render_part_readme(part), check, changed)

        exercises = part.path / "exercises.md"
        if part.exercises and not exercises.exists():
            write_if_changed(exercises, render_exercises(part), check, changed)

    for path in changed:
        verb = "更新が必要" if check else "更新"
        print(f"{verb}: {path.relative_to(ROOT).as_posix()}")
    if check and changed:
        print("`just sync` を実行してからコミットしてください。", file=sys.stderr)
        return 1
    if not changed:
        print("すべて最新です。")
    return 0


def new_chapter(part_id: str, number: str) -> int:
    parts = load_toc()
    number = f"{int(number):02d}"
    for part in parts:
        if part.id != part_id:
            continue
        for chapter in part.chapters:
            if chapter.number != number:
                continue
            if chapter.path.exists():
                print(f"既に存在します: {chapter.path.relative_to(ROOT).as_posix()}", file=sys.stderr)
                return 1
            chapter.path.mkdir(parents=True)
            chapter.readme.write_text(render_chapter_readme(chapter), encoding="utf-8", newline="\n")
            if not part.is_appendix:
                (chapter.path / "CMakeLists.txt").write_text(
                    "compendium_chapter()\n", encoding="utf-8", newline="\n")
            print(f"作成: {chapter.path.relative_to(ROOT).as_posix()}")
            return sync()
    print(f"TOC.md に見つかりません: {part_id} の {number} 章", file=sys.stderr)
    return 1


def main() -> int:
    # Windows のコンソールでも日本語を出力できるようにする
    for stream in (sys.stdout, sys.stderr):
        if hasattr(stream, "reconfigure"):
            stream.reconfigure(encoding="utf-8")

    parser = argparse.ArgumentParser(description="cpp-compendium の目次と雛形を管理する")
    sub = parser.add_subparsers(dest="command", required=True)

    sync_parser = sub.add_parser("sync", help="TOC.md から目次・進捗・Part の README を生成する")
    sync_parser.add_argument("--check", action="store_true", help="書き込まずに差分の有無だけを確かめる")

    new_parser = sub.add_parser("new", help="章の雛形を作る")
    new_parser.add_argument("part", help="Part の ID（例: p03、appendix）")
    new_parser.add_argument("number", help="章番号（例: 06）")

    args = parser.parse_args()
    if args.command == "sync":
        return sync(check=args.check)
    return new_chapter(args.part, args.number)


if __name__ == "__main__":
    sys.exit(main())
