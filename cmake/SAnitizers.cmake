# Sanitizerの設定
#
# COMPENDIUM_SANITIZERS にカンマ区切りで指定する。
#   例: address,undefined / thread
# 指定するとプロジェクト内の全ターゲットに適用される。

set(COMPENDIUM_SANITIZERS "" CACHE STRING "有効にするSanitizer（例: address,undefined / thread）")

if(COMPENDIUM_SANITIZERS)
    if(MSVC)
        if(NOT COMPENDIUM_SANITIZERS STREQUAL "address")
            message(FATAL_ERROR "MSVCで使えるSanitizerは address のみです: ${COMPENDIUM_SANITIZERS}")
        endif()
        add_compile_options(/fsanitize=address /Zi)
    else()
        add_compile_options(
            -fsanitize=${COMPENDIUM_SANITIZERS}
            -fno-omit-frame-pointer     # スタックトレースを読みやすくする
            -fno-sanitize-recover=all   # 問題を検出したら即座に止める
        )
        add_link_options(-fsanitize=${COMPENDIUM_SANITIZERS})
    endif()
    message(STATUS "Sanitizer: ${COMPENDIUM_SANITIZERS}")
endif()