// ムーブ専用の型を使う
//
// Buffer はコピーできず、ムーブだけができる（buffer.hpp を参照）。

#include <iostream>
#include <utility>
#include <vector>

#include <compendium/section.hpp>

#include "buffer.hpp"

int main() {
    compendium::section("ムーブで所有権を移す");
    // ANCHOR: transfer
    Buffer a(16);
    Buffer b = std::move(a); // ムーブコンストラクタが呼ばれる

    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move): ムーブ後の状態を示すため、わざと使っている
    std::cout << "a.size() = " << a.size() << ", b.size() = " << b.size() << '\n';
    // ANCHOR_END: transfer

    compendium::section("コンテナにムーブ専用の型を入れる");
    // ANCHOR: container
    std::vector<Buffer> buffers;
    // NOLINTNEXTLINE(modernize-use-emplace): push_back と emplace_back の違いを示すため
    buffers.push_back(Buffer(8));  // 一時オブジェクトは自動でムーブされる
    buffers.push_back(std::move(b)); // 名前のある変数は std::move が必要
    buffers.emplace_back(32);      // その場で構築すればムーブすら不要

    for (const auto& buffer : buffers) {
        std::cout << "size = " << buffer.size() << '\n';
    }
    // ANCHOR_END: container
}
