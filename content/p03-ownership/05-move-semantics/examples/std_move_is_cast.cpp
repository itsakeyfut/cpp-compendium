// std::move は何も動かさない。右辺値参照へのキャストにすぎない
//
// そのため const オブジェクトを std::move しても、ムーブではなくコピーになる。

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include <compendium/section.hpp>

// ANCHOR: my_move
// std::move の中身は、ほぼこれだけ
template <typename T>
constexpr std::remove_reference_t<T>&& my_move(T&& value) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(value);
}
// ANCHOR_END: my_move

int main() {
    compendium::section("std::move の結果の型");
    // ANCHOR: types
    std::string text = "text";
    const std::string fixed = "fixed";

    static_assert(std::is_same_v<decltype(std::move(text)), std::string&&>);
    // NOLINTNEXTLINE(performance-move-const-arg): 型を調べるだけ（評価されない）
    static_assert(std::is_same_v<decltype(std::move(fixed)), const std::string&&>);
    static_assert(std::is_same_v<decltype(my_move(text)), std::string&&>);
    std::cout << "std::move(text) の型は std::string&&、std::move(fixed) の型は const std::string&&\n";
    // ANCHOR_END: types

    compendium::section("const オブジェクトはムーブできない");
    // ANCHOR: const_move
    const std::string name = "この文字列は短い文字列最適化（SSO）に収まらない長さにしてある";

    // const std::string&& はムーブコンストラクタ（std::string&&）に渡せないので、
    // コピーコンストラクタ（const std::string&）が選ばれる
    // NOLINTNEXTLINE(performance-move-const-arg): const をムーブしてもコピーになることを示す
    std::string copied = std::move(name);

    // NOLINTNEXTLINE(bugprone-use-after-move): コピーされたので name は無傷であることを示す
    std::cout << "name は変わらず残っている: " << name << '\n';
    std::cout << "copied: " << copied << '\n';
    // ANCHOR_END: const_move
}
