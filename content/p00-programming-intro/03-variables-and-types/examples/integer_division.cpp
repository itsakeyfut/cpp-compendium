// 整数どうしの割り算は、小数点以下が切り捨てられる

#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("整数の割り算");
    // ANCHOR: division
    std::cout << "5 / 2   = " << 5 / 2 << '\n';   // 2（2.5 にはならない）
    std::cout << "5 % 2   = " << 5 % 2 << '\n';   // 1（余り）
    std::cout << "5.0 / 2 = " << 5.0 / 2 << '\n'; // 2.5（どちらかが小数なら、小数で計算される）
    // ANCHOR_END: division

    compendium::section("平均の計算");
    // ANCHOR: average
    int total_score = 250;
    int players = 3;

    // NOLINTNEXTLINE(bugprone-integer-division): よくある間違いを示すため、わざと書いている
    double wrong = total_score / players;       // 整数で割ってから double にするので 83
    double right = total_score / 3.0;           // 小数で割るので 83.333...
    std::cout << "間違い: " << wrong << '\n';
    std::cout << "正しい: " << right << '\n';
    std::cout << "人数の変数を使う場合: " << static_cast<double>(total_score) / players << '\n';
    // ANCHOR_END: average
}
