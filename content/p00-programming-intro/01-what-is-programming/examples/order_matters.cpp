// 命令は書いた順番に実行される
//
// 同じ命令でも、順番を入れ替えると結果が変わる。

#include <iostream>

#include <compendium/section.hpp>

int main() {
    compendium::section("攻撃力を上げてから攻撃する");
    // ANCHOR: power_up_first
    {
        int attack = 10;   // 攻撃力
        int enemy_hp = 100; // 敵の体力

        attack = attack * 2;          // 攻撃力を2倍にする
        enemy_hp = enemy_hp - attack; // 攻撃する

        std::cout << "敵の残りの体力: " << enemy_hp << '\n';
    }
    // ANCHOR_END: power_up_first

    compendium::section("攻撃してから攻撃力を上げる");
    // ANCHOR: attack_first
    {
        int attack = 10;
        int enemy_hp = 100;

        enemy_hp = enemy_hp - attack; // 攻撃する
        attack = attack * 2;          // 攻撃力を2倍にする（もう攻撃した後）

        std::cout << "敵の残りの体力: " << enemy_hp << '\n';
    }
    // ANCHOR_END: attack_first
}
