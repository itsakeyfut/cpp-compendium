<!-- status: draft -->

# 入力と出力

★☆☆☆ 入門　`C++98〜`　`std::format は C++20〜`

> `std::cin` でキーボードから値を受け取り、`std::cout` と `std::format` で見やすく表示する。

---

## ⚡ 30秒で思い出す

- `std::cin >> x;` でキーボードから値を受け取る。`>>` は空白（スペース・タブ・改行）で区切られた値を1つずつ読む。
- `std::cin >> a >> b;` で複数の値をまとめて読める。
- 空白を含む1行を読むには `std::getline(std::cin, line);` を使う。
- **`>>` の直後に `std::getline` を使うと、空の行が読まれる。** 残った改行を読むため。`std::getline(std::cin >> std::ws, line);` で防ぐ。
- 数値を読むところに文字を入力すると、読み取りは失敗する。変数には `0` が入り、それ以降の読み取りもすべて無視される。
- 表示を整えるには、`<iomanip>` の `std::setw`・`std::setfill`・`std::setprecision`、または C++20 の `std::format` を使う。
- `std::format` は、`{}` の数と値の数が合わないと**コンパイルエラー**にしてくれる。
- エラーや警告は `std::cerr` に出力する。

---

## 📘 基本

### キーボードから数値を受け取る

これまでのプログラムは、毎回同じ結果を表示していました。入力を受け取れるようにすると、使う人に合わせて動くプログラムが書けます。

```cpp
{{#include examples/read_number.cpp:read_number}}
```

📄 [examples/read_number.cpp](examples/read_number.cpp)

実行すると、入力を待って止まります。`7` と入力して Enter キーを押すと、次のように表示されます。

```text
今のレベルを入力してください: 7
次のレベルは 8 です
```

`std::cin` はキーボード（標準入力）を表します。`>>` は、`std::cin` から読み取った値を右側の変数へ入れる、という向きを表しています。`std::cout <<` と矢印の向きが逆なのは、値の流れる向きが逆だからです。

| 書き方 | 値の流れ |
|---|---|
| `std::cout << hp;` | `hp` の値 → 画面 |
| `std::cin >> hp;` | キーボード → `hp` |

### 複数の値を受け取る

`>>` はつなげて使えます。値は空白（スペース、タブ、改行）で区切って入力します。

```cpp
{{#include examples/read_multiple.cpp:read_multiple}}
```

📄 [examples/read_multiple.cpp](examples/read_multiple.cpp)

```text
名前・体力・移動速度を、スペースで区切って入力してください: Hero 100 3.5
名前: Hero
体力: 100
移動速度: 3.5
```

`std::string` は文字列を入れる型です。詳しくは [配列と文字列](../08-arrays-and-strings/)の章で扱います。

### 空白を含む1行を受け取る

`>>` は空白で区切って読むので、`Dark Knight` と入力すると `Dark` だけが読まれます。空白を含めて1行まるごと読みたいときは、`std::getline` を使います。

```cpp
{{#include examples/read_line.cpp:read_line}}
```

📄 [examples/read_line.cpp](examples/read_line.cpp)

```text
ギルドの名前を入力してください: Knights of the Round Table
ギルド「Knights of the Round Table」を作成しました
```

### 表示を整える：`<iomanip>`

数値の桁をそろえたり、小数の桁数を決めたりするには、`<iomanip>` の機能を使います。

```cpp
{{#include examples/formatting.cpp:iomanip}}
```

```text
     7
  1500
007
12.35
```

| 書き方 | 意味 |
|---|---|
| `std::setw(6)` | 次の値を6文字分の幅で表示する（右寄せ） |
| `std::setfill('0')` | 幅の余った部分を `0` で埋める |
| `std::fixed` と `std::setprecision(2)` | 小数点以下を2桁で表示する（四捨五入される） |

`std::setw` は**直後の1つの値にだけ**効きます。一方、`std::setfill`・`std::fixed`・`std::setprecision` は、元に戻すまでずっと効き続けます。

### 表示を整える：`std::format`（C++20）

C++20からは、`std::format` で文字列を組み立てられます。`{}` の位置に値が順番に入るので、`<<` をたくさんつなげるより読みやすくなります。

```cpp
{{#include examples/formatting.cpp:format}}
```

📄 [examples/formatting.cpp](examples/formatting.cpp)

```text
体力: 85 / 120
割合: 70.8%
ID: 007
[ right] [left  ]
```

| 書き方 | 意味 |
|---|---|
| `{}` | 値をそのまま入れる |
| `{:.1f}` | 小数点以下1桁で表示する |
| `{:03}` | 3桁になるよう `0` で埋める |
| `{:>6}` / `{:<6}` | 6文字分の幅で右寄せ / 左寄せ |

### エラーメッセージは `std::cerr` へ

画面への出力には、`std::cout` のほかに `std::cerr` があります。エラーや警告は `std::cerr` に出力するのが決まりです。

```cpp
{{#include examples/error_output.cpp:cerr}}
```

📄 [examples/error_output.cpp](examples/error_output.cpp)

どちらも同じ画面に表示されますが、出力先が別々に管理されています。そのため、「通常の結果だけをファイルに保存し、エラーは画面に出す」といった使い分けができます。

---

## 🔬 深掘り

### ストリームという考え方

`std::cin`、`std::cout`、`std::cerr` は、どれも**ストリーム**（データの流れ）を表すオブジェクトです。ストリームは「どこから来て、どこへ行くか」を抽象化しているので、入力元や出力先が変わっても同じ書き方で扱えます。

| ストリーム | 入出力 | つながっている先 |
|---|---|---|
| `std::cin` | 入力 | 標準入力（ふつうはキーボード） |
| `std::cout` | 出力 | 標準出力（ふつうは画面） |
| `std::cerr` | 出力 | 標準エラー出力（ふつうは画面） |
| `std::istringstream` | 入力 | 文字列 |
| `std::ostringstream` | 出力 | 文字列 |
| `std::ifstream` / `std::ofstream` | 入力 / 出力 | ファイル |

この章のテストでは、`std::istringstream` を使って、キーボードの代わりに文字列から入力しています。`std::cin` と同じ書き方で、入力の動きを確かめられます。

📄 [tests/input_output_test.cpp](tests/input_output_test.cpp)

ファイルの読み書きは [Part 4 ファイルと入出力](../../p04-standard-library/16-filesystem-and-io/)で扱います。

### `>>` の直後の `std::getline` が空になる理由

入力は、ストリームの中に文字の列としてたまっています。`3` と入力して Enter を押すと、ストリームには `3` と改行（`\n`）が入ります。

```text
入力されたもの:  3 \n H e r o \n
                 ↑
>> で読むと、3 だけを読んで、改行の手前で止まる
```

この状態で `std::getline` を呼ぶと、「改行までの1行」を読むので、残っていた改行だけを読んで空の文字列を返します。

```cpp
{{#include examples/getline_after_number.cpp:problem}}
```

`std::ws` は、ストリームの先頭にある空白と改行を読み飛ばします。`std::cin >> std::ws` で読み飛ばしてから `std::getline` を呼べば、意図どおりに次の行を読めます。

```cpp
{{#include examples/getline_after_number.cpp:solution}}
```

📄 [examples/getline_after_number.cpp](examples/getline_after_number.cpp)

```text
=== 問題：名前が空になる ===
人数: 3, リーダー: []

=== 解決：std::ws で空白と改行を読み飛ばす ===
人数: 5, リーダー: [Mage]
```

### 入力に失敗したとき

`int` を読むところで `abc` と入力すると、読み取りは失敗します。このとき次のことが起きます。

1. 変数には `0` が入る（C++11以降）
2. ストリームが「失敗した状態」になる
3. 失敗した状態のままでは、**それ以降の `>>` はすべて何もしない**

3つ目が特に厄介です。1回の入力ミスで、後に続く入力がすべて無視されてしまいます。入力が成功したかを確かめて、失敗したら入力をやり直させるには、次の章で学ぶ `if` が必要です。

```cpp
if (!(std::cin >> level)) {   // 読み取りに失敗したら
    std::cin.clear();          // 失敗した状態を元に戻す
    std::cin.ignore(1000, '\n'); // 間違った入力を、改行まで読み捨てる
}
```

失敗したときの動きは、テストでも確かめています（`FailedExtractionSetsZeroAndFailState`、`FailedStreamIgnoresFurtherInput`）。

### 改行なしの質問文が、入力の前に表示される理由

`std::cout` は、効率のために出力をため込んでから、まとめて画面に書き出します（**バッファリング**）。そのため、`"入力してください: "` のように改行を含まない文字列は、すぐには表示されないことがあります。

それでも入力の前に質問文が表示されるのは、`std::cin` が `std::cout` と**結び付けられて**いるからです。`std::cin` で読む前に、`std::cout` にたまっている出力が自動的に書き出されます。この仕組みのおかげで、質問文を出してから入力を待つ、という自然な動きになります。

### `std::format` の書式はコンパイル時に検査される

`std::format` の書式の文字列は、**コンパイル時**に検査されます。`{}` の数と値の数が合わない場合や、値の型に合わない書式を指定した場合は、コンパイルエラーになります。

```cpp
std::format("体力: {} / {}", 100);   // ✗ {} は2つあるのに、値は1つ
```

📄 [compile_fail/format_argument_count.cpp](compile_fail/format_argument_count.cpp)

実行するまで間違いに気づけない C言語の `printf` と比べて、大きな改善です。`std::format` は、広く使われていたオープンソースのライブラリ **{fmt}** をもとに標準化されました。詳しくは [Part 4 書式化と出力](../../p04-standard-library/13-format-and-print/)で扱います。

### テストでの入力の渡し方

このリポジトリでは、`examples/<名前>.input` というファイルを置くと、テストのときにその内容が入力として渡されます。たとえば `read_number.cpp` には `read_number.input`（中身は `7`）があります。入力を待つコード例でも、テストが止まらずに最後まで実行されます。

手元で同じことをするには、**リダイレクト**を使います。

```bash
# Git Bash / Linux
./build/gcc-debug/bin/p00_04_read_number < content/p00-programming-intro/04-input-output/examples/read_number.input
```

```powershell
# PowerShell（< が使えないので、ファイルの内容をパイプで渡す）
Get-Content content\p00-programming-intro\04-input-output\examples\read_number.input | .\build\msvc-debug\bin\p00_04_read_number.exe
```

---

## ⚠️ 落とし穴とUB

### 1. `std::cin` に `<<` を使う

矢印の向きを間違えると、コンパイルエラーになります。値が「キーボードから変数へ」流れるので `>>` です。

```text
error: no match for 'operator<<' (operand types are 'std::istream' {aka 'std::basic_istream<char>'} and 'int')
```

📄 [compile_fail/cin_wrong_arrow.cpp](compile_fail/cin_wrong_arrow.cpp)

### 2. `>>` の直後に `std::getline` を使う

「深掘り」で説明したとおり、空の行が読まれます。`std::getline(std::cin >> std::ws, line);` を使います。

### 3. 数値を読むところに文字を入力する

読み取りに失敗し、変数には `0` が入ります。さらに、それ以降の入力がすべて無視されます。入力が成功したかの確認は、次の章で学ぶ `if` を使って行います。

### 4. `std::setfill` や `std::setprecision` が効き続ける

`std::setw` 以外の設定は、元に戻すまで効き続けます。一部だけ書式を変えたいときは、後で元に戻すか、`std::format` を使うと安全です。

### 5. Windowsのコンソールで日本語を入力する

Windowsのコンソールでは、日本語の入力を正しく受け取るのに追加の設定が必要になることがあります。この章のコード例では、入力に英数字だけを使っています。日本語の扱いは [Part 4 文字列](../../p04-standard-library/08-strings/)で扱います。

---

## 🏭 実務・OSSではこう使われる

### ゲームでは `std::cin` をほとんど使わない

ゲームの入力は、キーボード、マウス、ゲームパッドのボタンの状態を、毎フレーム調べる形で受け取ります。Unreal Engineでは **Enhanced Input** という仕組みを使います。`std::cin` のように「入力されるまで止まって待つ」方法は、毎秒60回画面を描き直すゲームには使えません。

一方、ここで学んだ「ストリーム」や「書式化」の考え方は、ゲーム開発でもそのまま使います。

- **ログ出力**：開発中のゲームは、大量のログを出力します。Unreal Engineでは `UE_LOG` マクロを使い、C言語の `printf` と同じ形式（`%d` など）で書式を指定します。新しいバージョンには、`std::format` のように `{}` を使う `UE_LOGFMT` もあります。
- **設定ファイルやデータの読み込み**：テキスト形式の設定やセーブデータを読むときに、ストリームから値を読み取ります。
- **開発用のコンソールコマンド**：Unreal Engineのコンソールで `stat fps` のようなコマンドを入力すると、文字列を解析して処理します。

### ゲーム業界と {fmt}

`std::format` のもとになった **{fmt}** ライブラリは、ゲームを含む多くのC++プロジェクトで使われています。C++20が使えない古い環境でも、{fmt}を入れれば同じ書き方ができます。

---

## 🦀 Rustとの対応

| 観点 | C++ | Rust |
|---|---|---|
| 1行読む | `std::getline(std::cin, line);` | `std::io::stdin().read_line(&mut line)?;` |
| 数値として読む | `std::cin >> level;` | `line.trim().parse::<i32>()` |
| 読み取りの失敗 | ストリームが失敗した状態になり、変数は `0` | `Result` の `Err` が返る |
| 書式付きの文字列 | `std::format("{}", x)` | `format!("{}", x)` |
| 書式の検査 | コンパイル時（C++20） | コンパイル時 |
| エラー出力 | `std::cerr << ...;` | `eprintln!(...);` |

**Rustの知識が罠になる点：** Rustでは、読み取りの失敗は `Result` で返るので、無視しにくい設計です。C++の `std::cin` は、失敗しても黙って `0` を入れ、その後の読み取りを無視するだけです。失敗を確かめるのは、書く人の責任です。

---

## ❓ 思い出しクイズ

**Q1.** `std::cin >> a >> b;` に対して `10 20` と入力すると、`a` と `b` はそれぞれいくつになりますか？

<details>
<summary>答え</summary>

`a` は `10`、`b` は `20` です。`>>` は空白で区切られた値を1つずつ順番に読み取ります。

</details>

**Q2.** `std::string name; std::cin >> name;` に対して `Dark Knight` と入力すると、`name` には何が入りますか？ 全体を読むにはどうすればよいですか？

<details>
<summary>答え</summary>

`Dark` だけが入ります。`>>` は空白の手前で止まるためです。空白を含めて1行まるごと読むには `std::getline(std::cin, name);` を使います。

</details>

**Q3.** 次のコードで、`name` が空になってしまうのはなぜですか？

```cpp
int count = 0;
std::string name;
std::cin >> count;
std::getline(std::cin, name);
```

<details>
<summary>答え</summary>

`std::cin >> count;` は数値だけを読み、Enter キーの改行がストリームに残ります。`std::getline` はその改行までを読むので、空の文字列になります。`std::getline(std::cin >> std::ws, name);` のように、先に空白と改行を読み飛ばします。

</details>

**Q4.** `int level; std::cin >> level;` に対して `abc` と入力すると、どうなりますか？

<details>
<summary>答え</summary>

読み取りに失敗し、`level` には `0` が入ります。ストリームが失敗した状態になり、それ以降の `>>` はすべて何もしなくなります。

</details>

**Q5.** `std::format("{:.2f}", 12.3456)` と `std::format("{:03}", 7)` の結果は何ですか？

<details>
<summary>答え</summary>

`"12.35"`（小数点以下2桁。四捨五入される）と `"007"`（3桁になるよう0で埋める）です。

</details>

**Q6.** `std::format("{} / {}", 100)` がコンパイルエラーになるのはなぜですか？

<details>
<summary>答え</summary>

`{}` が2つあるのに、渡している値が1つしかないためです。`std::format` の書式の文字列はコンパイル時に検査されます。

</details>

---

## 📎 参照

### このリポジトリ内

- コード例：[read_number.cpp](examples/read_number.cpp)、[read_multiple.cpp](examples/read_multiple.cpp)、[read_line.cpp](examples/read_line.cpp)、[getline_after_number.cpp](examples/getline_after_number.cpp)、[formatting.cpp](examples/formatting.cpp)、[error_output.cpp](examples/error_output.cpp)
- テスト：[input_output_test.cpp](tests/input_output_test.cpp)
- compile_fail：[cin_wrong_arrow.cpp](compile_fail/cin_wrong_arrow.cpp)、[format_argument_count.cpp](compile_fail/format_argument_count.cpp)
- 前の章：[変数と型](../03-variables-and-types/)
- 次の章：[条件分岐](../05-conditionals/)
- 関連する章：[Part 4 文字列](../../p04-standard-library/08-strings/)、[Part 4 書式化と出力](../../p04-standard-library/13-format-and-print/)、[Part 4 ファイルと入出力](../../p04-standard-library/16-filesystem-and-io/)

### 外部

- [cppreference: std::cin](https://en.cppreference.com/w/cpp/io/cin)
- [cppreference: std::getline](https://en.cppreference.com/w/cpp/string/basic_string/getline)
- [cppreference: std::format](https://en.cppreference.com/w/cpp/utility/format/format)
- [cppreference: Standard format specification](https://en.cppreference.com/w/cpp/utility/format/spec)
- [{fmt}](https://github.com/fmtlib/fmt)
