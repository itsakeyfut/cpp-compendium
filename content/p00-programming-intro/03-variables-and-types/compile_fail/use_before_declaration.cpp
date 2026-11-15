// 変数は、宣言するより前の行では使えない
//
// EXPECT-ERROR(gcc): 'hp' was not declared in this scope
// EXPECT-ERROR(clang): use of undeclared identifier 'hp'
// EXPECT-ERROR(msvc): C2065

int main() {
    hp = 10; // この時点では hp はまだ存在しない
    int hp = 0;
    return hp;
}
