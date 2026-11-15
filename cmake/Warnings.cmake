# 全ターゲット共通の警告設定
#
# compendium::warnings をリンクしたターゲットに警告オプションを付ける。

add_library(compendium_warnings INTERFACE)
add_library(compendium::warnings ALIAS compendium_warnings)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC（cl.exe）
    target_compile_options(compendium_warnings INTERFACE
        /W4
        /permissive-        # 規格に厳密に従う
        /utf-8              # ソースと実行文字セットをUTF-8にする（日本語コメント対策）
        /Zc:__cplusplus     # __cplusplus マクロを正しい値にする
        $<$<BOOL:${COMPENDIUM_WARNINGS_AS_ERRORS}>:/WX>
    )
elseif(MSVC)
    # clang-cl（MSVC互換のオプションを受け付けるClang）
    target_compile_options(compendium_warnings INTERFACE
        /W4
        /utf-8
        -Wshadow
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        $<$<BOOL:${COMPENDIUM_WARNINGS_AS_ERRORS}>:/WX>
    )
else()
    # GCC / Clang
    target_compile_options(compendium_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        $<$<BOOL:${COMPENDIUM_WARNINGS_AS_ERRORS}>:-Werror>
    )
endif()
