# 章の登録
#
# 章ディレクトリの CMakeLists.txt で次の1行を書くだけで、
# examples / tests / compile_fail / bench を自動で登録する。
#
#   compendium_chapter()
#
# ターゲット名は「p{Part番号}_{章番号}_{ファイル名}」になる。
#   例: content/p03-ownership/05-move-semantics/examples/basic_move.cpp
#       → p03_05_basic_move

# コード例を実行するテスト用のスクリプトと、入力がないときに流し込む空のファイル
set(COMPENDIUM_RUN_EXAMPLE "${CMAKE_CURRENT_LIST_DIR}/RunExample.cmake")
set(COMPENDIUM_EMPTY_INPUT "${CMAKE_BINARY_DIR}/compendium_empty.input")
file(WRITE "${COMPENDIUM_EMPTY_INPUT}" "")

# 章のターゲットに共通の設定を付ける
function(compendium_configure_target target)
    target_link_libraries(${target} PRIVATE compendium::warnings compendium::common)
endfunction()

function(compendium_chapter)
    # ディレクトリ名から Part番号 と 章番号 を取り出す
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME chapter_dir)
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH part_path)
    cmake_path(GET part_path FILENAME part_dir)

    string(REGEX MATCH "^p[0-9][0-9]" part_id "${part_dir}")
    string(REGEX MATCH "^[0-9][0-9]" chapter_id "${chapter_dir}")
    if(NOT part_id OR NOT chapter_id)
        message(FATAL_ERROR
            "章ディレクトリの名前が規則に合っていません: ${part_dir}/${chapter_dir}\n"
            "Partは pNN-xxx、章は NN-xxx の形式にしてください。")
    endif()
    set(prefix "${part_id}_${chapter_id}")

    # --------------------------------------------------------
    # examples/ : 1ファイル = 1実行ファイル
    #   正常終了すること（終了コード0）をテストとして登録する
    #   examples/<名前>.input があれば、その内容を標準入力として流し込む
    #   （ない場合は空の入力を流し込むので、入力待ちで止まることはない）
    # --------------------------------------------------------
    file(GLOB examples CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    # .input を追加・削除したときにも構成し直されるよう、監視対象に加える
    file(GLOB example_inputs CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.input")
    foreach(src IN LISTS examples)
        cmake_path(GET src STEM name)
        set(target "${prefix}_${name}")
        add_executable(${target} "${src}")
        compendium_configure_target(${target})
        set(input "${CMAKE_CURRENT_SOURCE_DIR}/examples/${name}.input")
        if(NOT EXISTS "${input}")
            set(input "${COMPENDIUM_EMPTY_INPUT}")
        endif()
        add_test(
            NAME ${target}
            COMMAND ${CMAKE_COMMAND}
                -DEXAMPLE=$<TARGET_FILE:${target}>
                -DINPUT=${input}
                -P ${COMPENDIUM_RUN_EXAMPLE}
        )
        set_tests_properties(${target} PROPERTIES LABELS "example")
    endforeach()

    # --------------------------------------------------------
    # tests/ : 章ごとに1つのGoogleTest実行ファイルにまとめる
    # --------------------------------------------------------
    file(GLOB tests CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    if(tests)
        set(target "${prefix}_tests")
        add_executable(${target} ${tests})
        compendium_configure_target(${target})
        target_link_libraries(${target} PRIVATE GTest::gtest_main)
        gtest_discover_tests(${target}
            TEST_PREFIX "${prefix}."
            PROPERTIES LABELS "unit"
        )
    endif()

    # --------------------------------------------------------
    # compile_fail/ : コンパイルが失敗することを確かめる
    # --------------------------------------------------------
    file(GLOB compile_fails CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/compile_fail/*.cpp")
    foreach(src IN LISTS compile_fails)
        cmake_path(GET src STEM name)
        compendium_add_compile_fail("${prefix}_cf_${name}" "${src}")
    endforeach()

    # --------------------------------------------------------
    # bench/ : 1ファイル = 1ベンチマーク実行ファイル
    #   CIではビルドだけを確認し、計測は手元で行う
    # --------------------------------------------------------
    if(COMPENDIUM_BUILD_BENCHMARKS)
        file(GLOB benches CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/bench/*.cpp")
        foreach(src IN LISTS benches)
            cmake_path(GET src STEM name)
            set(target "${prefix}_bench_${name}")
            add_executable(${target} "${src}")
            compendium_configure_target(${target})
            target_link_libraries(${target} PRIVATE benchmark::benchmark_main)
        endforeach()
    endif()
endfunction()
