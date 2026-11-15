// ムーブ後のオブジェクトは「有効だが未規定の状態」
//
// 破棄・再代入・事前条件のない操作はしてよい。
// 「空になっているはず」のように、特定の値を前提にしてはいけない。

#include <iostream>
#include <string>
#include <utility>

#include <compendium/section.hpp>

int main() {
    compendium::section("ムーブ後の std::string");
    // ANCHOR: moved_from
    std::string s = "この文字列は短い文字列最適化（SSO）に収まらない長さにしてある";
    std::string t = std::move(s);

    // s はまだ生きているオブジェクト。ただし中身が何かは規定されていない。
    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move): ムーブ後の状態を示すため、わざと使っている
    std::cout << "s.size() = " << s.size() << "（実装によって変わりうる）\n";
    std::cout << "t = " << t << '\n';
    // ANCHOR_END: moved_from

    compendium::section("ムーブ後のオブジェクトを再利用する");
    // ANCHOR: reuse
    s = "新しい値を代入すれば、再び普通に使える";
    std::cout << s << '\n';

    s.clear(); // clear() も事前条件がないので呼んでよい
    s += "clear() してから追記";
    std::cout << s << '\n';
    // ANCHOR_END: reuse
}
