# Windows では PowerShell でレシピを実行する
set windows-shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-ExecutionPolicy", "Bypass", "-Command"]

# 各コマンドの前に MSVC 開発者環境と VCPKG_ROOT を整える (Windows のみ)
devenv := if os() == "windows" { ". '" + justfile_directory() / "scripts" / "vsdev.ps1" + "';" } else { "" }

# 既定のビルド構成 (debug / release / asan)
config := "debug"

# Python (Windows は python、それ以外は python3)
python := if os() == "windows" { "python" } else { "python3" }

# レシピ一覧を表示
default:
    @just --list

# ---------------------------------------------------------------------------
# 汎用 (任意のプリセット名を指定)
# ---------------------------------------------------------------------------

# 構成: just configure msvc-debug [--fresh]
configure preset *flags:
    @{{devenv}} echo '> cmake --preset {{preset}} {{flags}}'; cmake --preset {{preset}} {{flags}}

# ビルド: just build msvc-debug
build preset:
    @{{devenv}} echo '> cmake --build --preset {{preset}}'; cmake --build --preset {{preset}}

# テスト: just test msvc-debug [-R p03_05]
test preset *args:
    @{{devenv}} echo '> ctest --preset {{preset}} {{args}}'; ctest --preset {{preset}} {{args}}

# 構成 → ビルド → テスト
all preset: (configure preset) (build preset) (test preset)

# 特定のターゲットだけビルド: just target msvc-debug p00_02_cf_wrong_case
target preset name:
    @{{devenv}} echo '> cmake --build --preset {{preset}} --target {{name}}'; cmake --build --preset {{preset}} --target {{name}}

# ---------------------------------------------------------------------------
# コンパイラ別のショートカット
# ---------------------------------------------------------------------------

# MSVC: 構成 → ビルド → テスト (例: just msvc / just msvc release)
msvc cfg=config: (all "msvc-" + cfg)

# clang-cl: 構成 → ビルド → テスト (例: just clang / just clang release)
clang cfg=config: (all "clang-cl-" + cfg)

# MSVC と clang-cl の両方で 構成 → ビルド → テスト
both cfg=config: (msvc cfg) (clang cfg)

# ---------------------------------------------------------------------------
# 目次・雛形・教科書
# ---------------------------------------------------------------------------

# TOC.md から目次・進捗・Part の README を更新する
sync:
    {{python}} scripts/compendium.py sync

# 生成物が TOC.md と一致しているか確かめる (CI 用)
sync-check:
    {{python}} scripts/compendium.py sync --check

# 章の雛形を作る: just new p03 06
new part number:
    {{python}} scripts/compendium.py new {{part}} {{number}}

# 教科書をブラウザで読む (編集すると自動で再読み込み)
book:
    mdbook serve --open

# 教科書を build/book に出力する
book-build:
    mdbook build
