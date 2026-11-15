// 基本的な型：整数・小数・文字・真偽値

#include <iostream>

#include <compendium/section.hpp>

int main() {
    std::cout << std::boolalpha; // bool を true / false で表示する

    compendium::section("基本的な型");
    // ANCHOR: types
    int gold = 1500;          // 整数
    double speed = 3.5;       // 小数（浮動小数点数）
    char rank = 'S';          // 1文字（シングルクォートで囲む）
    bool is_boss = true;      // 真偽値（true か false）

    std::cout << "所持金: " << gold << '\n';
    std::cout << "移動速度: " << speed << '\n';
    std::cout << "ランク: " << rank << '\n';
    std::cout << "ボスか: " << is_boss << '\n';
    // ANCHOR_END: types

    compendium::section("型の大きさ（バイト数）");
    // ANCHOR: sizeof
    std::cout << "int:    " << sizeof(int) << " バイト\n";
    std::cout << "double: " << sizeof(double) << " バイト\n";
    std::cout << "char:   " << sizeof(char) << " バイト\n";
    std::cout << "bool:   " << sizeof(bool) << " バイト\n";
    // ANCHOR_END: sizeof
}
