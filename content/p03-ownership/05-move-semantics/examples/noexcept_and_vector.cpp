// ムーブコンストラクタに noexcept がないと、vector の再確保でコピーされる
//
// std::vector は再確保のとき、要素の移し替えで例外が起きても元の状態に戻せるように
// （強い例外安全保証）、ムーブが例外を投げうるならコピーを選ぶ。

#include <iostream>
#include <vector>

#include <compendium/section.hpp>

#include "tracked.hpp"

// ANCHOR: reallocate
template <bool NoexceptMove>
void reallocate() {
    using Item = Tracked<NoexceptMove>;

    std::vector<Item> items(4);
    items.shrink_to_fit(); // 容量を要素数ぴったりにして、次の追加で再確保が起きるようにする

    Item::counter = {};
    items.emplace_back(); // 再確保が起き、既存の4要素が新しいバッファへ移される

    std::cout << "コピー: " << Item::counter.copies << " 回, ムーブ: " << Item::counter.moves
              << " 回\n";
}
// ANCHOR_END: reallocate

int main() {
    compendium::section("ムーブコンストラクタが noexcept の場合");
    reallocate<true>();

    compendium::section("ムーブコンストラクタが noexcept でない場合");
    reallocate<false>();
}
