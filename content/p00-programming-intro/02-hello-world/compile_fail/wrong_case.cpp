// C++ は大文字と小文字を区別する。cout を Cout と書くとコンパイルできない
//
// EXPECT-ERROR(gcc): 'Cout' is not a member of 'std'
// EXPECT-ERROR(clang): no member named 'Cout' in namespace 'std'
// EXPECT-ERROR(msvc): C2039

#include <iostream>

int main() {
    std::Cout << "Hello, World!\n";
}
