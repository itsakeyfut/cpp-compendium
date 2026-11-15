// はじめてのプログラム
//
// プログラムは「コンピュータへの命令」を並べたもの。
// main の中の命令が、上から順に1つずつ実行される。

#include <iostream>

// ANCHOR: first_program
int main() {
    std::cout << "ゲームを開始します\n"; // 画面に文字を表示する

    int hp = 100;    // 体力を覚えておく
    int damage = 30; // 受けるダメージを覚えておく

    hp = hp - damage; // 体力からダメージを引いて、体力を更新する

    std::cout << "敵の攻撃を受けた！\n";
    std::cout << "残りの体力: " << hp << '\n';
}
// ANCHOR_END: first_program
