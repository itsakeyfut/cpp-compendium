// std::cout で、いろいろなものを表示する

#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("<< でつなげて表示する");
    // ANCHOR: chain
    std::cout << "体力: " << 100 << " / " << 120 << '\n';
    // ANCHOR_END: chain

    compendium::section("改行");
    // ANCHOR: newline
    std::cout << "1行目\n";
    std::cout << "2行目\n";
    std::cout << "同じ行に"; // \n がないと改行されない
    std::cout << "続けて表示される\n";
    // ANCHOR_END: newline

    compendium::section("エスケープシーケンス");
    // ANCHOR: escape
    std::cout << "名前\t体力\n";               // \t はタブ（列をそろえる）
    std::cout << "勇者\t100\n";
    std::cout << "セリフ: \"こんにちは\"\n";   // \" は文字としてのダブルクォート
    std::cout << "パス: C:\\Games\\save.dat\n"; // \\ は文字としてのバックスラッシュ
    // ANCHOR_END: escape
}
