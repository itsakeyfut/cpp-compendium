// 変数：値に名前を付けて覚えておく箱

#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("宣言と初期化");
    // ANCHOR: declare
    int hp = 100;     // int 型の変数 hp を作り、100 で初期化する
    int max_hp = 120; // 名前は意味がわかるように付ける

    std::cout << "体力: " << hp << " / " << max_hp << '\n';
    // ANCHOR_END: declare

    compendium::section("代入");
    // ANCHOR: assign
    hp = 80;      // 新しい値を代入する（前の値 100 は上書きされて消える）
    hp = hp + 15; // 今の hp に 15 を足した値を、hp に入れ直す

    std::cout << "体力: " << hp << '\n';
    // ANCHOR_END: assign

    compendium::section("定数");
    // ANCHOR: constant
    const int level_cap = 99; // const を付けると、後から変更できない

    std::cout << "最大レベル: " << level_cap << '\n';
    // ANCHOR_END: constant
}
