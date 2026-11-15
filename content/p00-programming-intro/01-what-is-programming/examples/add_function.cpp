// コンパイラが作る機械語を覗くための、小さな関数
//
// add 関数がどんな機械語になるかは、asm/add_gcc13_O2.s と本文の「深掘り」を参照。

#include <iostream>

// ANCHOR: add
int add(int a, int b) {
    return a + b;
}
// ANCHOR_END: add

int main() {
    std::cout << "2 + 3 = " << add(2, 3) << '\n';
}
