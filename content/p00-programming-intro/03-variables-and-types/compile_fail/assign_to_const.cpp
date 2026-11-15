// const を付けた変数には、後から代入できない
//
// EXPECT-ERROR(gcc): assignment of read-only variable
// EXPECT-ERROR(clang): cannot assign to variable 'max_hp' with const-qualified type
// EXPECT-ERROR(msvc): C3892

int main() {
    const int max_hp = 100;
    max_hp = 120;
    return max_hp;
}
