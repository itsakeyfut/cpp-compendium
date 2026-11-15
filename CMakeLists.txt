cmake_minimum_required(VERSION 3.28)

project(cpp_compendium
    DESCRIPTION "C++で一生食べていくための、動くコード付きリファレンス"
    LANGUAGES CXX
)

# ----------------------------------------------------------------
# 言語設定：C++20を基準にする（拡張は使わない）
# ----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# C++20 モジュールはまだ使わないので、モジュールの依存スキャンを止める
# （有効のままだと、ビルド前の clang-tidy が存在しない .modmap を探して失敗する）
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# 実行ファイルはすべて build/<presets>/bin/ に集める
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------------------------------------------
# オプション
# ----------------------------------------------------------------
option(COMPENDIUM_BUILD_BENCHMARKS "ベンチマークをビルドする" ON)
option(COMPENDIUM_BUILD_VULNERABLE "Part 10の意図的に脆弱なサンプルをビルドする" OFF)
option(COMPENDIUM_WARNINGS_AS_ERRORS "警告をエラーとして扱う" ON)

# ----------------------------------------------------------------
# 共通のCMake関数
# ----------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(Warnings)
include(Sanitizers)
include(CompileFail)
include(Chapter)

# ----------------------------------------------------------------
# 依存ライブラリ（vcpkg.json で管理）
# ----------------------------------------------------------------
find_package(GTest CONFIG REQUIRED)
if(COMPENDIUM_BUILD_BENCHMARKS)
    find_package(benchmark CONFIG REQUIRED)
endif()

enable_testing()
include(GoogleTest)

add_subdirectory(common)
add_subdirectory(content)
