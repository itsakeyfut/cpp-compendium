// >> で数値を読んだ直後に std::getline を使うと、空の行が読み取られてしまう

#include <iostream>
#include <string>

#include <compendium/section.hpp>

int main() {
    compendium::section("問題：名前が空になる");
    // ANCHOR: problem
    {
        int party_size = 0;
        std::string leader;

        std::cin >> party_size;          // 「3」だけを読み、その後ろの改行は残る
        std::getline(std::cin, leader);  // 残っていた改行までを読むので、空になる

        std::cout << "人数: " << party_size << ", リーダー: [" << leader << "]\n";
    }
    // ANCHOR_END: problem

    // 問題の例で読まれずに残った「Hero」の行を読み飛ばす
    std::string skipped;
    std::getline(std::cin, skipped);

    compendium::section("解決：std::ws で空白と改行を読み飛ばす");
    // ANCHOR: solution
    {
        int party_size = 0;
        std::string leader;

        std::cin >> party_size;
        std::getline(std::cin >> std::ws, leader); // std::ws が先頭の空白と改行を読み飛ばす

        std::cout << "人数: " << party_size << ", リーダー: [" << leader << "]\n";
    }
    // ANCHOR_END: solution
}
