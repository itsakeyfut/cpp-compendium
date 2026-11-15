#pragma once

// コピーとムーブの回数を数える型
//
// NoexceptMove が true ならムーブコンストラクタを noexcept にする。
// std::vector の再確保で、どちらが使われるかを確かめるために使う。

// ANCHOR: tracked
struct Counter {
    int copies = 0;
    int moves = 0;
};

template <bool NoexceptMove>
struct Tracked {
    static inline Counter counter{};

    Tracked() = default;
    Tracked(const Tracked&) { ++counter.copies; }
    Tracked(Tracked&&) noexcept(NoexceptMove) { ++counter.moves; }
};
// ANCHOR_END: tracked
