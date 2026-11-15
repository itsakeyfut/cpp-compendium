// エラーメッセージは std::cerr に出力する

#include <iostream>

// ANCHOR: cerr
int main() {
    std::cout << "セーブデータを読み込みます\n";       // 通常の出力
    std::cerr << "警告: セーブデータが見つかりません\n"; // エラーや警告の出力
    std::cout << "新しいゲームを開始します\n";
}
// ANCHOR_END: cerr
