// 右辺値参照（T&&）は、名前のある変数（左辺値）を直接受け取れない
//
// 受け取るには std::move で右辺値にキャストする必要がある。
//
// EXPECT-ERROR(gcc): cannot bind rvalue reference
// EXPECT-ERROR(clang): rvalue reference to type .* cannot bind to lvalue
// EXPECT-ERROR(msvc): C2440

void bind_rvalue_ref() {
    int value = 0;
    int&& ref = value; // 左辺値は右辺値参照に束縛できない
    (void)ref;
}
