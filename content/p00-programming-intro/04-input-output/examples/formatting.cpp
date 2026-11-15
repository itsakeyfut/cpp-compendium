// 出力の見た目を整える

#include <format>
#include <iomanip>
#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("桁をそろえる（<iomanip>）");
    // ANCHOR: iomanip
    std::cout << std::setw(6) << 7 << '\n';    // 6文字分の幅で右寄せ
    std::cout << std::setw(6) << 1500 << '\n';
    std::cout << std::setfill('0') << std::setw(3) << 7 << '\n'; // 0 で埋めて 007
    std::cout << std::setfill(' ');            // 埋める文字を元に戻す

    std::cout << std::fixed << std::setprecision(2) << 12.3456 << '\n'; // 小数点以下2桁（四捨五入される）
    // ANCHOR_END: iomanip

    compendium::section("std::format で文字列を組み立てる（C++20）");
    // ANCHOR: format
    int hp = 85;
    int max_hp = 120;
    double rate = 100.0 * hp / max_hp;

    std::cout << std::format("体力: {} / {}\n", hp, max_hp);     // {} の位置に値が入る
    std::cout << std::format("割合: {:.1f}%\n", rate);           // 小数点以下1桁
    std::cout << std::format("ID: {:03}\n", 7);                  // 3桁になるよう0で埋める
    std::cout << std::format("[{:>6}] [{:<6}]\n", "right", "left"); // 右寄せ・左寄せ
    // ANCHOR_END: format
}
