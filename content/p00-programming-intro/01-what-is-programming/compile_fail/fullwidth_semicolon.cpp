// 全角のセミコロン（；）は、半角のセミコロン（;）とは別の文字なので、コンパイルできない
//
// 日本語入力のまま記号を打つと起きやすい。
// どのコンパイラも「100；」を「100 に ； という接尾辞が付いた数値」と解釈しようとして失敗する。
//
// EXPECT-ERROR(gcc): numeric literal operator
// EXPECT-ERROR(clang): not allowed in an identifier|invalid suffix
// EXPECT-ERROR(msvc): C3688

int main() {
    int hp = 100；
    return hp;
}
