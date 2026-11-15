// 計算：四則演算と、よく使う書き方

#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("四則演算");
    // ANCHOR: operators
    int a = 17;
    int b = 5;

    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "a * b = " << a * b << '\n';
    std::cout << "a / b = " << a / b << '\n'; // 整数どうしの割り算は、小数点以下が切り捨てられる
    std::cout << "a % b = " << a % b << '\n'; // % は割り算の余り
    // ANCHOR_END: operators

    compendium::section("計算の順番");
    // ANCHOR: precedence
    std::cout << "2 + 3 * 4   = " << 2 + 3 * 4 << '\n';   // 掛け算が先
    std::cout << "(2 + 3) * 4 = " << (2 + 3) * 4 << '\n'; // かっこの中が先
    // ANCHOR_END: precedence

    compendium::section("短い書き方");
    // ANCHOR: compound
    int exp = 0;
    exp += 50; // exp = exp + 50; と同じ
    exp *= 2;  // exp = exp * 2; と同じ
    std::cout << "経験値: " << exp << '\n';

    int level = 1;
    ++level; // level = level + 1; と同じ
    std::cout << "レベル: " << level << '\n';
    // ANCHOR_END: compound
}
