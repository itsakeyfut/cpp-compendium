// main の戻り値は、プログラムの「終了コード」になる
//
// 0 は「正常に終了した」という意味。0 以外は「何か問題があった」ことを表す。
// このリポジトリのテストは、コード例が 0 で終了することを確かめている。

#include <iostream>

// ANCHOR: return_value
int main() {
    std::cout << "処理が完了しました\n";
    return 0; // 正常に終了したことを、プログラムを起動した側に伝える
}
// ANCHOR_END: return_value
