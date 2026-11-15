// #include <iostream> を書かずに std::cout を使うと、コンパイルできない
//
// std::cout は <iostream> の中で宣言されているので、
// インクルードしないとコンパイラは std::cout が何なのかわからない。
//
// EXPECT-ERROR(gcc): 'cout' is not a member of 'std'
// EXPECT-ERROR(clang): use of undeclared identifier 'std'
// EXPECT-ERROR(msvc): C2039

int main() {
    std::cout << "Hello, World!\n";
}
