// int で表せる値には限りがある

#include <iostream>
#include <limits>

int main() {
    // ANCHOR: limits
    std::cout << "int の最大値: " << std::numeric_limits<int>::max() << '\n';
    std::cout << "int の最小値: " << std::numeric_limits<int>::min() << '\n';
    std::cout << "long long の最大値: " << std::numeric_limits<long long>::max() << '\n';
    // ANCHOR_END: limits
}
