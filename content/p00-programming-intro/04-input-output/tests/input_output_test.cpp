// 本文の主張をテストで確かめる
//
// std::istringstream / std::ostringstream は、文字列を入力元・出力先にするストリーム。
// std::cin / std::cout と同じ使い方ができるので、キーボードを使わずに入出力の動きを確かめられる。

#include <format>
#include <iomanip>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

TEST(Input, ExtractionSkipsWhitespace) {
    std::istringstream input("   42 \n\t 7\n");
    int a = 0;
    int b = 0;
    input >> a >> b;
    EXPECT_EQ(a, 42);
    EXPECT_EQ(b, 7);
}

TEST(Input, StringExtractionStopsAtWhitespace) {
    std::istringstream input("Dark Knight\n");
    std::string name;
    input >> name;
    EXPECT_EQ(name, "Dark"); // 空白の手前で止まる
}

TEST(Input, GetlineReadsWholeLine) {
    std::istringstream input("Dark Knight\n");
    std::string name;
    std::getline(input, name);
    EXPECT_EQ(name, "Dark Knight");
}

TEST(Input, GetlineAfterExtractionReadsEmptyLine) {
    std::istringstream input("3\nHero\n");
    int size = 0;
    std::string leader;

    input >> size;
    std::getline(input, leader);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(leader, ""); // 残っていた改行までを読むので空になる

    std::getline(input, leader);
    EXPECT_EQ(leader, "Hero");
}

TEST(Input, WsSkipsLeftoverNewline) {
    std::istringstream input("3\nHero\n");
    int size = 0;
    std::string leader;

    input >> size;
    std::getline(input >> std::ws, leader);
    EXPECT_EQ(leader, "Hero");
}

TEST(Input, FailedExtractionSetsZeroAndFailState) {
    std::istringstream input("abc");
    int level = 99;
    input >> level;
    EXPECT_TRUE(input.fail()); // 読み取りに失敗した状態になる
    EXPECT_EQ(level, 0);       // C++11 以降、失敗すると 0 が入る
}

TEST(Input, FailedStreamIgnoresFurtherInput) {
    std::istringstream input("abc 42");
    int a = 1;
    int b = 1;
    input >> a >> b;
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1); // 失敗した状態のままでは、それ以降の読み取りは何もしない
}

TEST(Output, SetwAndSetfill) {
    std::ostringstream out;
    out << std::setw(6) << 7 << '|' << std::setfill('0') << std::setw(3) << 7;
    EXPECT_EQ(out.str(), "     7|007");
}

TEST(Output, FixedAndSetprecision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << 12.3456;
    EXPECT_EQ(out.str(), "12.35"); // 四捨五入される
}

TEST(Output, Format) {
    EXPECT_EQ(std::format("体力: {} / {}", 85, 120), "体力: 85 / 120");
    EXPECT_EQ(std::format("{:.1f}", 70.8333), "70.8");
    EXPECT_EQ(std::format("{:03}", 7), "007");
    EXPECT_EQ(std::format("[{:>6}]", "right"), "[ right]");
    EXPECT_EQ(std::format("[{:<6}]", "left"), "[left  ]");
}
