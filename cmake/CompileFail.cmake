# compile_fail テスト
#
# 「このコードはコンパイルできない」ことをテストで保証する。
# ファイルの先頭付近に、期待するエラーメッセージを正規表現で書く。
#
#   // EXPECT-ERROR(gcc,clang): use of deleted function
#   // EXPECT-ERROR(msvc): attempting to reference a deleted function
#
# 今のコンパイラ向けの EXPECT-ERROR があれば、その正規表現に一致するエラーで
# 失敗したときだけ合格にする。タイポなど別の理由で失敗しても合格にならない。
#
# 注意:
#   - 正規表現に「;」は書けない（CMake ではリストの区切りになり、パターンが分割される）。
#     「;」に一致させたいときは「.」で代用する。
#   - テストは LC_ALL=C で実行するので、GCC のメッセージは英語・ASCII の引用符（'）になる。
#     （UTF-8 ロケールの GCC は ‘ ’ を使い、日本語ロケールではメッセージ自体が翻訳される）

# 今のコンパイラを EXPECT-ERROR で使う名前（gcc / clang / msvc）に変換する
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPENDIUM_COMPILER_TAG "gcc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMPENDIUM_COMPILER_TAG "clang")
elseif(MSVC)
    set(COMPENDIUM_COMPILER_TAG "msvc")
else()
    set(COMPENDIUM_COMPILER_TAG "unknown")
endif()

# ソースファイルから、今のコンパイラ向けの期待エラーを取り出す
#   src     : 対象のソースファイル
#   out_var : 正規表現を受け取る変数（見つからなければ空）
function(compendium_expected_error src out_var)
    set(result "")
    file(STRINGS "${src}" lines REGEX "^// EXPECT-ERROR\\(")
    foreach(line IN LISTS lines)
        if(line MATCHES "^// EXPECT-ERROR\\(([^)]*)\\): (.+)$")
            set(tags "${CMAKE_MATCH_1}")
            set(pattern "${CMAKE_MATCH_2}")
            string(REPLACE "," ";" tags "${tags}")
            list(TRANSFORM tags STRIP)
            if(COMPENDIUM_COMPILER_TAG IN_LIST tags)
                set(result "${pattern}")
            endif()
        endif()
    endforeach()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

# compile_fail テストを1つ登録する
#   name : テスト名とターゲット名
#   src  : ソースファイル
function(compendium_add_compile_fail name src)
    # 通常のビルドには含めない（含めるとビルド自体が失敗する）
    add_library(${name} OBJECT EXCLUDE_FROM_ALL "${src}")
    target_link_libraries(${name} PRIVATE compendium::warnings compendium::common)

    # テスト実行時にこのターゲットだけをビルドし、失敗することを確かめる
    add_test(
        NAME ${name}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${name} --config $<CONFIG>
    )

    compendium_expected_error("${src}" pattern)
    if(pattern)
        # 期待するエラーメッセージが出力に含まれていれば合格
        set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${pattern}")
    else()
        # 期待するエラーが書かれていなければ、失敗したことだけを確かめる
        set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
    endif()

    # 同じビルドディレクトリで同時にビルドすると衝突するため、1つずつ実行する
    # コンパイラのメッセージをロケールに左右されない形（英語・ASCII の引用符）にする
    set_tests_properties(${name} PROPERTIES
        ENVIRONMENT "LC_ALL=C"
        RESOURCE_LOCK compendium_build_dir
        LABELS "compile_fail"
    )
endfunction()