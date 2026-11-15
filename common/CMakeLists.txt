# 全章で使う共通ヘルパー（ヘッダオンリー）
#
# 使い方: #include <compendium/section.hpp>

add_library(compendium_common INTERFACE)
add_library(compendium::common ALIAS compendium_common)

target_include_directories(compendium_common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)