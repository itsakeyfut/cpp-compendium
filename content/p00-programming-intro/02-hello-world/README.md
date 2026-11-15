<!-- status: draft -->

# 開発環境とHello World

★☆☆☆ 入門　`C++98〜`

> C++のプログラムを書いて動かすための道具をそろえ、最初のプログラム「Hello World」を実行する。

---

## ⚡ 30秒で思い出す

- 必要な道具は、**コンパイラ**（MSVC / GCC / Clang）、**ビルドツール**（CMake + Ninja）、**エディタ**（Visual Studio / VS Code）。このリポジトリでは、さらに **vcpkg**、**just**、**Python** を使う。
- Windowsでは、Visual Studio 2026の「**C++ によるデスクトップ開発**」ワークロードを入れれば、MSVC・CMake・Ninjaがそろう。
- このリポジトリでは `just msvc` で、構成・ビルド・テストをまとめて実行できる。実行ファイルは `build\msvc-debug\bin\` にできる。
- Hello Worldの骨格は、`#include <iostream>`、`int main() { ... }`、`std::cout << "...";` の3つ。
- `\n` は改行、`\t` はタブ。`"` や `\` を文字として表示するには `\"`、`\\` と書く。
- `main` の戻り値は**終了コード**になる。`0` は正常終了。`main` だけは `return 0;` を省略できる。
- 日本語が文字化けしたら、PowerShellで `[Console]::OutputEncoding = [System.Text.Encoding]::UTF8` を実行する。

---

## 📘 基本

### 必要な道具

C++でプログラムを作るには、次の道具が必要です。

| 道具 | 役割 | このリポジトリで使うもの |
|---|---|---|
| エディタ / IDE | ソースコードを書く | Visual Studio 2026 または VS Code |
| コンパイラ | ソースコードを機械語に翻訳する | MSVC（Windows）、GCC / Clang（Linux） |
| ビルドツール | どのファイルをどの順番でコンパイルするかを管理する | CMake と Ninja |
| パッケージ管理 | 他の人が作ったライブラリを取り込む | vcpkg |
| タスクランナー | よく使うコマンドを短い名前で実行する | just |
| Python | 目次や章の雛形を生成する | Python 3.9以降 |
| Git | ソースコードの変更履歴を管理する | Git |

道具が多く見えますが、C++のプロジェクトでは一般的な構成です。1つずつ準備していきます。

### Windowsでの準備

#### 1. Visual Studio 2026 Community

[Visual Studio](https://visualstudio.microsoft.com/ja/) の公式サイトから、無料の **Community** 版をダウンロードしてインストールします。インストーラーの「ワークロード」タブで **「C++ によるデスクトップ開発」** にチェックを入れてください。右側の「インストールの詳細」で、次の項目が選ばれていることを確認します。

- MSVC のビルドツール（x64/x86 向け、最新版）
- Windows 11 SDK
- Windows 用 C++ CMake ツール（CMake と Ninja が含まれる）
- Windows 用 C++ Clang コンパイラ（任意。Clangでも試したい場合）

#### 2. Git・just・Python

PowerShellを開いて、Windows標準のパッケージ管理ツール `winget` でインストールします。

```powershell
winget install --id Git.Git --exact
winget install --id Casey.Just --exact
winget install --id Python.Python.3.13 --exact
```

インストールが終わったら、PowerShellを開き直してください。開き直さないと、新しく入れたコマンドが見つかりません。

#### 3. vcpkg

vcpkgは、Gitで取得してから準備用のスクリプトを実行します。ここでは `C:\dev\vcpkg` に置く例を示します。

```powershell
git clone https://github.com/microsoft/vcpkg.git C:\dev\vcpkg
C:\dev\vcpkg\bootstrap-vcpkg.bat -disableMetrics

# vcpkg の場所を、ユーザー環境変数 VCPKG_ROOT に登録する（このユーザーだけに設定される）
[Environment]::SetEnvironmentVariable('VCPKG_ROOT', 'C:\dev\vcpkg', 'User')
```

#### 4. リポジトリを取得してビルドする

```powershell
git clone https://github.com/itsakeyfut/cpp-compendium.git
cd cpp-compendium
just msvc
```

初回は、vcpkgがテスト用のライブラリをビルドするので数分かかります。最後に `100% tests passed` と表示されれば準備完了です。

### Hello World

画面に「Hello, World!」と表示するだけのプログラムです。新しい言語を学ぶとき、最初に書くプログラムとして昔から定番になっています。

```cpp
{{#include examples/hello_world.cpp:hello_world}}
```

📄 [examples/hello_world.cpp](examples/hello_world.cpp)

実行するには、ビルドしてから実行ファイルを起動します。

```powershell
just msvc
.\build\msvc-debug\bin\p00_02_hello_world.exe
```

```text
Hello, World!
```

1行ずつ見ていきます。

| コード | 意味 |
|---|---|
| `#include <iostream>` | 画面への入出力の機能（`std::cout` など）を使えるようにする |
| `int main()` | プログラムの開始位置。プログラムを実行すると、ここから始まる |
| `{` と `}` | `main` の中身の始まりと終わり |
| `std::cout` | 画面（標準出力）を表す。「シー・アウト」と読む |
| `<<` | 右側のものを、左側（画面）に送る |
| `"Hello, World!\n"` | 表示する文字列。`"` で囲む。`\n` は改行 |
| `;` | 文の終わり |

`std::` は「標準ライブラリ（C++に最初から付いてくる機能）の」という意味です。`std::cout` で「標準ライブラリの `cout`」を指します。

### いろいろなものを表示する

`<<` は何度でもつなげられます。文字列だけでなく、数値もそのまま表示できます。

```cpp
{{#include examples/printing.cpp:chain}}
```

```text
体力: 100 / 120
```

`\n` を書かない限り、改行はされません。

```cpp
{{#include examples/printing.cpp:newline}}
```

```text
1行目
2行目
同じ行に続けて表示される
```

文字列の中で `\` から始まる組み合わせを**エスケープシーケンス**と呼び、特別な文字を表します。

```cpp
{{#include examples/printing.cpp:escape}}
```

📄 [examples/printing.cpp](examples/printing.cpp)

```text
名前	体力
勇者	100
セリフ: "こんにちは"
パス: C:\Games\save.dat
```

| 書き方 | 意味 |
|---|---|
| `\n` | 改行 |
| `\t` | タブ（表示位置をそろえる） |
| `\"` | 文字としての `"`（書かないと、文字列の終わりと解釈される） |
| `\\` | 文字としての `\`（Windowsのパスを書くときに必要） |

### main の戻り値

`int main()` の `int` は、`main` が整数を返すことを表します。この値は**終了コード**と呼ばれ、プログラムを起動した側（PowerShellやテストの仕組み）に「正常に終わったかどうか」を伝えます。

```cpp
{{#include examples/return_value.cpp:return_value}}
```

📄 [examples/return_value.cpp](examples/return_value.cpp)

`0` は「正常に終了した」、それ以外は「何か問題があった」という意味です。PowerShellでは、直前に実行したプログラムの終了コードを `$LASTEXITCODE` で確認できます。

```powershell
.\build\msvc-debug\bin\p00_02_return_value.exe
$LASTEXITCODE   # 0 と表示される
```

`main` だけは特別に、`return` を書かずに最後まで進むと `return 0;` と同じ扱いになります。Hello Worldで `return` を書いていないのはそのためです。

### 日本語が文字化けする場合

このリポジトリのプログラムは、日本語をUTF-8という形式で出力します。PowerShellの初期設定は別の形式を想定しているので、日本語が「縺薙ｓ縺ｫ縺｡縺ｯ」のように化けることがあります。

その場合は、次のコマンドを実行してから、もう一度プログラムを実行してください。

```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
```

毎回入力するのが面倒であれば、PowerShellのプロファイル（`notepad $PROFILE` で開けます）にこの1行を書いておくと、起動するたびに自動で設定されます。Git Bashは最初からUTF-8を扱えるので、この設定は不要です。

---

## 🔬 深掘り

### `just msvc` の中で起きていること

`just msvc` は、次の4つの処理をまとめて実行しています。

| 順番 | 処理 | 内容 |
|---|---|---|
| 1 | 開発者用シェルの準備 | `scripts/vsdev.ps1` が、MSVCを使うための環境変数（`PATH`、`INCLUDE`、`LIB`）を設定する |
| 2 | 構成（`cmake --preset msvc-debug`） | CMakeがプロジェクトを読み、vcpkgで必要なライブラリを用意し、Ninja用のビルド手順を作る |
| 3 | ビルド（`cmake --build --preset msvc-debug`） | NinjaがMSVCを呼び出して、すべての `.cpp` をコンパイル・リンクする |
| 4 | テスト（`ctest --preset msvc-debug`） | コード例を実行し、テストと compile_fail を確かめる |

1の「開発者用シェル」が必要なのは、MSVCがどこにインストールされていて、標準ライブラリのヘッダやライブラリがどこにあるかを、環境変数で教える必要があるためです。Visual Studioの中から操作するときはIDEが自動で設定しますが、コマンドラインから使うときは自分で設定する必要があります。`scripts/vsdev.ps1` は、その作業を自動化しています。

### `std::endl` と `\n`

改行には `std::endl` も使えます。

```cpp
std::cout << "Hello, World!" << std::endl;
```

`std::endl` は、改行に加えて**フラッシュ**（出力をため込んでいる場所から、実際に画面へ書き出す処理）も行います。フラッシュは比較的重い処理なので、大量に出力するときに毎行 `std::endl` を使うと遅くなります。普段は `\n` を使い、すぐに画面に出したい場面（クラッシュ直前のログなど）でだけ明示的にフラッシュするのが一般的です。

### `std::print`（C++23）

C++23では、より簡潔に書ける `std::print` と `std::println` が追加されました。

```cpp
#include <print>

int main() {
    std::println("Hello, World!");          // 改行付きで表示する
    std::println("体力: {} / {}", 100, 120); // {} の位置に値が入る
}
```

このリポジトリはC++20を基準にしているため、`std::print` はコード例では使っていません。詳しくは [Part 4 書式化と出力](../../p04-standard-library/13-format-and-print/)で扱います。

### Linux（WSL2）での準備

Ubuntuの場合は、次のコマンドで主な道具がそろいます。vcpkgの準備は、Windowsと同様にGitで取得して `bootstrap-vcpkg.sh` を実行し、`VCPKG_ROOT` を `~/.bashrc` で設定します。

```bash
sudo apt update
sudo apt install -y build-essential clang clang-tidy cmake ninja-build git python3 curl zip unzip tar pkg-config
```

Linuxでは `just` の代わりに、プリセットを直接指定して実行できます。

```bash
cmake --preset gcc-debug
cmake --build --preset gcc-debug
ctest --preset gcc-debug
```

---

## ⚠️ 落とし穴とUB

### 1. `#include` を忘れる

`std::cout` は `<iostream>` の中で用意されているので、`#include <iostream>` を書かないとコンパイラは `std::cout` が何なのかわかりません。

```text
error: 'cout' is not a member of 'std'
note: 'std::cout' is defined in header '<iostream>'; did you forget to '#include <iostream>'?
```

GCCは、どのヘッダを忘れたかまで教えてくれます。

📄 [compile_fail/missing_include.cpp](compile_fail/missing_include.cpp)

### 2. 大文字と小文字を間違える

C++は大文字と小文字を区別します。`cout` と `Cout` は別の名前です。

```text
error: 'Cout' is not a member of 'std'; did you mean 'cout'?
```

📄 [compile_fail/wrong_case.cpp](compile_fail/wrong_case.cpp)

### 3. `main` を打ち間違える

`main` を `Main` や `mian` と書くと、コンパイルは通りますが、その後の**リンク**で失敗します。コンパイラにとっては「`Main` という普通の関数」があるだけで、文法の誤りではないからです。リンクの段階で、プログラムの開始位置である `main` が見つからずにエラーになります。

```text
undefined reference to `main'
```

MSVCでは `LNK` から始まる番号のエラー（`LNK2019` など）になります。エラーの番号が `C` ではなく `LNK` で始まっていたら、コンパイルではなくリンクの問題です。リンクについては [Part 1 リンクとライブラリ](../../p01-toolchain/03-linking/)で扱います。

### 4. 開発者用シェルの外でビルドする

Visual Studioの開発者用シェルを使わずに `cmake --preset msvc-debug` を直接実行すると、MSVCが見つからずに失敗します。

```text
The CMAKE_CXX_COMPILER:
    cl
is not a full path and was not found in the PATH.
```

`just msvc` を使えば、`scripts/vsdev.ps1` が自動で準備するので、このエラーは起きません。

---

## 🏭 実務・OSSではこう使われる

### ゲーム会社の開発環境

ゲーム会社のクライアント開発は、Windows、Visual Studio、MSVCの組み合わせが一般的です。家庭用ゲーム機の開発キットもWindowsで使うものが多く、ゲーム機ごとのコンパイラ（多くはClangを基にしたもの）を、Visual Studioから呼び出して使います。

Unreal Engineで開発する場合は、「C++ によるデスクトップ開発」に加えて、Visual Studioの **「C++ によるゲーム開発」** ワークロードも入れておきます。Unreal Engineのバージョンごとに、推奨されるVisual StudioとMSVCのバージョンが決まっているので、Epic Gamesの公式ドキュメントで確認してから準備します。

### 環境構築の自動化

大きなプロジェクトでは、新しく参加した人が同じ環境を再現できるように、環境構築をスクリプトやドキュメントで自動化します。このリポジトリの `scripts/vsdev.ps1` と `justfile` も同じ考え方です。「自分のPCでは動く」をなくすことが、チーム開発の基本になります。

---

## 🦀 Rustとの対応

| 観点 | C++（このリポジトリ） | Rust |
|---|---|---|
| 道具の導入 | Visual Studio、vcpkg、just などを個別に入れる | rustup でまとめて入る |
| ビルドと実行 | `just msvc` → 実行ファイルを起動 | `cargo run` |
| 画面への出力 | `std::cout << "...";` | `println!("...");` |
| 書式付きの出力 | `std::print("{}", x);`（C++23） | `println!("{}", x);` |
| 終了コード | `main` の戻り値（`int`） | `std::process::exit` や `main` の `Result` |

Rustでは `rustup` を入れれば、コンパイラ、ビルドツール、パッケージ管理（Cargo）がすべてそろいます。C++にはそのような公式の統一された道具がないため、プロジェクトごとに道具の組み合わせを決める必要があります。

---

## ❓ 思い出しクイズ

**Q1.** Windowsで、C++の開発に必要なMSVC・CMake・Ninjaをまとめて入れるには、Visual Studioのどのワークロードを選びますか？

<details>
<summary>答え</summary>

「C++ によるデスクトップ開発」です。インストールの詳細で、MSVCのビルドツール、Windows SDK、Windows用 C++ CMake ツールが選ばれていることを確認します。

</details>

**Q2.** Hello Worldで、`#include <iostream>` を書かないとどうなりますか？

<details>
<summary>答え</summary>

`std::cout` が何なのかコンパイラにわからず、コンパイルエラーになります。

</details>

**Q3.** `std::cout << "名前\t体力\n";` を実行すると、どのように表示されますか？

<details>
<summary>答え</summary>

「名前」と「体力」の間にタブが入り、最後に改行されます。`\t` はタブ、`\n` は改行を表すエスケープシーケンスです。

</details>

**Q4.** `main` の戻り値の `0` は何を意味しますか？ また、`return 0;` を書かなかった場合はどうなりますか？

<details>
<summary>答え</summary>

`0` は「正常に終了した」ことを、プログラムを起動した側に伝える終了コードです。`main` だけは、`return` を書かずに最後まで進むと `return 0;` と同じ扱いになります。

</details>

**Q5.** `main` を `Main` と打ち間違えると、コンパイルとリンクのどちらで失敗しますか？ それはなぜですか？

<details>
<summary>答え</summary>

リンクで失敗します。`Main` という名前の関数を作ること自体は文法的に正しいので、コンパイルは通ります。しかし、プログラムの開始位置である `main` がどこにもないため、実行ファイルを組み立てるリンクの段階でエラーになります。

</details>

---

## 📎 参照

### このリポジトリ内

- コード例：[hello_world.cpp](examples/hello_world.cpp)、[printing.cpp](examples/printing.cpp)、[return_value.cpp](examples/return_value.cpp)
- compile_fail：[missing_include.cpp](compile_fail/missing_include.cpp)、[wrong_case.cpp](compile_fail/wrong_case.cpp)
- 前の章：[プログラムとは何か](../01-what-is-programming/)
- 次の章：[変数と型](../03-variables-and-types/)
- 関連する章：[Part 1 リンクとライブラリ](../../p01-toolchain/03-linking/)、[Part 1 CMake入門](../../p01-toolchain/06-cmake-basics/)、[Part 4 書式化と出力](../../p04-standard-library/13-format-and-print/)

### 外部

- [Visual Studio で C および C++ のサポートをインストールする（Microsoft Learn）](https://learn.microsoft.com/ja-jp/cpp/build/vscpp-step-0-installation)
- [vcpkg のドキュメント](https://learn.microsoft.com/ja-jp/vcpkg/)
- [just のマニュアル](https://just.systems/man/en/)
- [cppreference: std::cout](https://en.cppreference.com/w/cpp/io/cout)
