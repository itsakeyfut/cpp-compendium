// {} で初期化すると、情報が失われる変換（縮小変換）はコンパイルエラーになる
//
// int x = 2.9; は黙って 2 に切り捨てられるが、int x{2.9}; はエラーになる。
//
// EXPECT-ERROR(gcc): narrowing conversion
// EXPECT-ERROR(clang): cannot be narrowed
// EXPECT-ERROR(msvc): C2397

int main() {
    int damage{2.9};
    return damage;
}
