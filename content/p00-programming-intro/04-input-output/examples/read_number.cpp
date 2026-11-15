// キーボードから数値を1つ受け取る
//
// テストでは examples/read_number.input の内容が入力として渡される。

#include <iostream>

// ANCHOR: read_number
int main() {
    std::cout << "今のレベルを入力してください: ";

    int level = 0;
    std::cin >> level; // キーボードから入力された数値を level に入れる

    std::cout << "\n次のレベルは " << level + 1 << " です\n";
}
// ANCHOR_END: read_number
