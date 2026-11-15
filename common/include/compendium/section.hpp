#pragma once

// コード例の出力を読みやすくするためのヘルパー
//
//   compendium::section("ムーブ後のオブジェクト");
//
// 出力:
//   === ムーブ後のオブジェクト ===

#include <iostream>
#include <string_view>

namespace compendium {

inline void section(std::string_view title) {
    std::cout << "\n=== " << title << " ===\n";
}

} // namespace compendium