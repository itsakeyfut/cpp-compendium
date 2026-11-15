# コード例を実行するテスト用のスクリプト
#
# ctest から次の形で呼ばれる。
#   cmake -DEXAMPLE=<実行ファイル> -DINPUT=<入力ファイル> -P RunExample.cmake
#
# INPUT の内容を標準入力として流し込んでからコード例を実行し、終了コードが 0 なら合格にする。
# 入力を待つコード例（std::cin を使うもの）が、テスト中にキー入力待ちで止まらないようにするため。

if(NOT EXAMPLE)
    message(FATAL_ERROR "EXAMPLE が指定されていません")
endif()

execute_process(
    COMMAND "${EXAMPLE}"
    INPUT_FILE "${INPUT}"
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "コード例が正常に終了しませんでした（終了コード: ${result}）: ${EXAMPLE}")
endif()
