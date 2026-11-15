// std::cin には >> を使う。<< を使うとコンパイルできない
//
// >> と << は「値が流れる向き」を表す。入力は std::cin から変数へ（>>）、
// 出力は値から std::cout へ（<<）流れる。
//
// EXPECT-ERROR(gcc): no match for 'operator<<'
// EXPECT-ERROR(clang): invalid operands to binary expression
// EXPECT-ERROR(msvc): C267[68]

#include <iostream>

int main() {
    int hp = 0;
    std::cin << hp;
}
