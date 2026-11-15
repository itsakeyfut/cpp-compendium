# add 関数（examples/add_function.cpp）を GCC 13 で最適化（-O2）したときの機械語
#
# 生成コマンド:
#   g++ -std=c++20 -O2 -S -masm=intel -fno-asynchronous-unwind-tables add_function.cpp
#
# 読みやすくするため、関数の本体以外の行（アセンブラへの指示など）は省いている。
# Ubuntu の GCC では、関数の先頭にセキュリティ機能のための endbr64 命令が付く。

_Z3addii:                   # add(int, int) の名前（名前マングリング後）
        endbr64             # 不正なジャンプ先でないことを示す目印（CET）
        lea     eax, [rdi+rsi]  # 1つ目の引数（rdi）と2つ目の引数（rsi）を足し、結果を eax に入れる
        ret                     # 呼び出し元に戻る（戻り値は eax）
