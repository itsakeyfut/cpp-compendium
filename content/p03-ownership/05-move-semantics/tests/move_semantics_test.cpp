// 本文の主張をテストで確かめる

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "../examples/buffer.hpp"
#include "../examples/tracked.hpp"

// ------------------------------------------------------------
// std::move はキャストにすぎない
// ------------------------------------------------------------
TEST(StdMove, IsJustACast) {
    std::string text = "text";
    const std::string fixed = "fixed";

    static_assert(std::is_same_v<decltype(std::move(text)), std::string&&>);
    // NOLINTNEXTLINE(performance-move-const-arg)
    static_assert(std::is_same_v<decltype(std::move(fixed)), const std::string&&>);

    // std::move を呼んだだけでは何も起きない
    [[maybe_unused]] auto&& ref = std::move(text);
    EXPECT_EQ(text, "text");
}

TEST(StdMove, ConstObjectIsCopiedNotMoved) {
    const std::string name(100, 'x');
    // NOLINTNEXTLINE(performance-move-const-arg)
    std::string copied = std::move(name);

    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
    EXPECT_EQ(name, std::string(100, 'x')); // 元の値が残っている = コピーされた
    EXPECT_EQ(copied, name);
}

// ------------------------------------------------------------
// 標準ライブラリの型のムーブ
// ------------------------------------------------------------
TEST(StandardTypes, VectorMoveConstructionStealsBuffer) {
    std::vector<int> a(1000, 42);
    const int* before = a.data();

    std::vector<int> b = std::move(a);

    EXPECT_EQ(b.data(), before); // バッファがそのまま引き継がれる
    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
    EXPECT_TRUE(a.empty()); // ムーブコンストラクタの後は空が保証される
}

TEST(StandardTypes, MovedFromStringCanBeReused) {
    std::string s(100, 'x');
    std::string t = std::move(s);

    s = "reused"; // 代入すれば再び普通に使える
    EXPECT_EQ(s, "reused");
    EXPECT_EQ(t, std::string(100, 'x'));
}

TEST(StandardTypes, UniquePtrIsMoveOnly) {
    static_assert(!std::is_copy_constructible_v<std::unique_ptr<int>>);
    static_assert(std::is_nothrow_move_constructible_v<std::unique_ptr<int>>);

    auto a = std::make_unique<int>(42);
    auto b = std::move(a);

    // unique_ptr はムーブ後に nullptr になることが保証されている
    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(*b, 42);
}

// ------------------------------------------------------------
// 自作のムーブ専用型 Buffer
// ------------------------------------------------------------
TEST(Buffer, IsMoveOnly) {
    static_assert(!std::is_copy_constructible_v<Buffer>);
    static_assert(!std::is_copy_assignable_v<Buffer>);
    static_assert(std::is_nothrow_move_constructible_v<Buffer>);
    static_assert(std::is_nothrow_move_assignable_v<Buffer>);
}

TEST(Buffer, MoveConstructionTransfersOwnership) {
    Buffer a(16);
    const int* before = a.data();

    Buffer b = std::move(a);

    EXPECT_EQ(b.size(), 16U);
    EXPECT_EQ(b.data(), before);
    // NOLINTBEGIN(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
    EXPECT_EQ(a.size(), 0U);
    EXPECT_EQ(a.data(), nullptr);
    // NOLINTEND(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
}

TEST(Buffer, MoveAssignmentReleasesOldResource) {
    Buffer a(16);
    Buffer b(8);

    b = std::move(a);

    EXPECT_EQ(b.size(), 16U);
    // NOLINTNEXTLINE(bugprone-use-after-move,clang-analyzer-cplusplus.Move)
    EXPECT_EQ(a.size(), 0U);
    // b が元々持っていた8要素の配列は解放されている（リークはASanで検出される）
}

TEST(Buffer, SelfMoveAssignmentIsSafe) {
    Buffer a(16);
    Buffer& alias = a; // 同じ変数への直接の自己ムーブはコンパイラが警告するため、参照を経由する

    a = std::move(alias);

    EXPECT_EQ(a.size(), 16U);
    EXPECT_NE(a.data(), nullptr);
}

// ------------------------------------------------------------
// noexcept と std::vector の再確保
// ------------------------------------------------------------
template <bool NoexceptMove>
Counter count_on_reallocation() {
    using Item = Tracked<NoexceptMove>;

    std::vector<Item> items(4);
    items.shrink_to_fit();

    Item::counter = {};
    items.emplace_back();
    return Item::counter;
}

TEST(NoexceptMove, VectorMovesElementsWhenMoveIsNoexcept) {
    const Counter counter = count_on_reallocation<true>();
    EXPECT_EQ(counter.copies, 0);
    EXPECT_EQ(counter.moves, 4);
}

TEST(NoexceptMove, VectorCopiesElementsWhenMoveMayThrow) {
    const Counter counter = count_on_reallocation<false>();
    EXPECT_EQ(counter.copies, 4);
    EXPECT_EQ(counter.moves, 0);
}
