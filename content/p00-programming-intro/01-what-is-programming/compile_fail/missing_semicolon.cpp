// 文の終わりのセミコロン（;）を忘れると、コンパイルできない
//
// EXPECT-ERROR(gcc): expected ',' or ';' before
// EXPECT-ERROR(clang): expected ';'
// EXPECT-ERROR(msvc): C214[36]

int main() {
    int hp = 100 // ここにセミコロンがない
    return hp;
}
