// std::format の {} の数と、渡す値の数が合わないとコンパイルできない
//
// 書式の文字列はコンパイル時に検査される（C++20）。
//
// EXPECT-ERROR(gcc): invalid_arg_id_in_format_string
// EXPECT-ERROR(clang): call to consteval function
// EXPECT-ERROR(msvc): C7595

#include <format>
#include <string>

int main() {
    std::string text = std::format("体力: {} / {}", 100); // {} は2つあるのに、値は1つ
    return static_cast<int>(text.size());
}
