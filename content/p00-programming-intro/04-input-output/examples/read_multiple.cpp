// 複数の値をまとめて受け取る
//
// >> は空白（スペース・タブ・改行）で区切られた値を、1つずつ順番に読み取る。

#include <iostream>
#include <string>

// ANCHOR: read_multiple
int main() {
    std::cout << "名前・体力・移動速度を、スペースで区切って入力してください: ";

    std::string name;  // 文字列（詳しくは「配列と文字列」の章で扱う）
    int hp = 0;
    double speed = 0.0;
    std::cin >> name >> hp >> speed; // 3つの値を順番に読み取る

    std::cout << "\n名前: " << name << '\n';
    std::cout << "体力: " << hp << '\n';
    std::cout << "移動速度: " << speed << '\n';
}
// ANCHOR_END: read_multiple
