// コピーとムーブの違い
//
// コピーは中身を複製し、ムーブは中身（バッファの所有権）を引き渡す。

#include <iostream>
#include <utility>
#include <vector>

#include <compendium/section.hpp>

int main() {
    std::cout << std::boolalpha;

    compendium::section("コピー：中身を複製する");
    // ANCHOR: copy
    std::vector<int> a(1'000'000, 42);
    std::vector<int> b = a; // 100万個の要素をすべて複製する

    std::cout << "a.size() = " << a.size() << ", b.size() = " << b.size() << '\n';
    std::cout << "同じバッファを指しているか: " << (a.data() == b.data()) << '\n';
    // ANCHOR_END: copy

    compendium::section("ムーブ：中身を引き渡す");
    // ANCHOR: move
    const int* before = a.data();
    std::vector<int> c = std::move(a); // バッファの所有権だけを移す（要素は複製しない）

    std::cout << "c は a のバッファを引き継いだか: " << (c.data() == before) << '\n';
    // ムーブコンストラクトされた後の vector は空であることが保証されている
    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move): ムーブ後の状態を示すため、わざと使っている
    std::cout << "ムーブ後の a.size() = " << a.size() << '\n';
    // ANCHOR_END: move
}
