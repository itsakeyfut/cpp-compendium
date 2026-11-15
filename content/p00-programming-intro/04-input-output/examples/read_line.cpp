// 空白を含む1行をまるごと受け取る

#include <iostream>
#include <string>

// ANCHOR: read_line
int main() {
    std::cout << "ギルドの名前を入力してください: ";

    std::string guild_name;
    std::getline(std::cin, guild_name); // 改行までの1行を、空白も含めて読み取る

    std::cout << "\nギルド「" << guild_name << "」を作成しました\n";
}
// ANCHOR_END: read_line
