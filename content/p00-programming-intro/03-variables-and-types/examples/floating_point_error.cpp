// 小数（浮動小数点数）には誤差がある

#include <cmath>
#include <iomanip>
#include <iostream>

#include <compendium/section.hpp>

int main() {
    std::cout << std::boolalpha;

    compendium::section("0.1 + 0.2 は 0.3 にならない");
    // ANCHOR: error
    double sum = 0.1 + 0.2;

    std::cout << "sum = " << sum << '\n'; // 普通に表示すると 0.3 に見える
    std::cout << "sum = " << std::setprecision(17) << sum << '\n'; // 17桁で表示すると誤差が見える
    std::cout << "sum == 0.3 : " << (sum == 0.3) << '\n';
    // ANCHOR_END: error

    compendium::section("小数は「十分に近いか」で比べる");
    // ANCHOR: compare
    double diff = std::abs(sum - 0.3);
    std::cout << "差: " << diff << '\n';
    std::cout << "十分に近いか: " << (diff < 1e-9) << '\n'; // 1e-9 は 0.000000001
    // ANCHOR_END: compare
}
