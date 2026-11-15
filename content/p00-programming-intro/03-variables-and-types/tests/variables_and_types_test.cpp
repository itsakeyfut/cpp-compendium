// 本文の主張をテストで確かめる

#include <cmath>
#include <limits>

#include <gtest/gtest.h>

TEST(IntegerDivision, TruncatesTowardZero) {
    EXPECT_EQ(5 / 2, 2);
    EXPECT_EQ(5 % 2, 1);
    EXPECT_EQ(17 / 5, 3);
    EXPECT_EQ(17 % 5, 2);

    // 負の数の割り算も「0 に近い方」へ切り捨てられる（C++11 以降で保証）
    EXPECT_EQ(-7 / 2, -3);
    EXPECT_EQ(-7 % 2, -1);
}

TEST(IntegerDivision, MixedWithDoubleIsFloatingPoint) {
    EXPECT_DOUBLE_EQ(5.0 / 2, 2.5);
    EXPECT_DOUBLE_EQ(5 / 2.0, 2.5);

    const int total = 250;
    const int players = 3;
    // NOLINTNEXTLINE(bugprone-integer-division)
    const double wrong = total / players;
    EXPECT_DOUBLE_EQ(wrong, 83.0); // 整数で割ってから double になる
}

TEST(FloatingPoint, PointOnePlusPointTwoIsNotPointThree) {
    const double sum = 0.1 + 0.2;
    EXPECT_NE(sum, 0.3);
    EXPECT_LT(std::abs(sum - 0.3), 1e-9);
}

TEST(Types, CharIsOneByte) {
    static_assert(sizeof(char) == 1); // 規格で保証されている
}

TEST(Types, IntIs32BitOnSupportedPlatforms) {
    // 規格は「最低 16 ビット」としか決めていないが、
    // このリポジトリが対象とする Windows / Linux の 64 ビット環境ではすべて 32 ビット
    static_assert(sizeof(int) == 4);
    EXPECT_EQ(std::numeric_limits<int>::max(), 2'147'483'647);
    EXPECT_EQ(std::numeric_limits<int>::min(), -2'147'483'647 - 1);
}

TEST(Types, IntToDoubleConversionTruncates) {
    const double value = 2.9;
    EXPECT_EQ(static_cast<int>(value), 2);    // 切り捨て（四捨五入ではない）
    EXPECT_EQ(static_cast<int>(-2.9), -2);    // 負の数も 0 に近い方へ
    EXPECT_EQ(std::lround(value), 3);         // 四捨五入したいときは std::lround
}
