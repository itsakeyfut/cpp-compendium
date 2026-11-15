<!-- status: draft -->

# 変数と型

★☆☆☆ 入門　`C++98〜`

> 変数は、値に名前を付けて覚えておく箱。型は、その箱に何を入れられるかを決める。

---

## ⚡ 30秒で思い出す

- 変数は `型 名前 = 初期値;` で作る。例：`int hp = 100;`
- 基本的な型は、`int`（整数）、`double`（小数）、`char`（1文字）、`bool`（`true` / `false`）。
- `const` を付けた変数は、後から変更できない。
- **整数どうしの割り算は、小数点以下が切り捨てられる。** `5 / 2` は `2`。小数の結果がほしければ、どちらかを小数にする（`5.0 / 2`）。
- `%` は割り算の余り。`5 % 2` は `1`。
- **小数には誤差がある。** `0.1 + 0.2 == 0.3` は `false`。小数は `==` ではなく、差が十分に小さいかで比べる。
- `int` で表せるのは約±21億まで。超えたときの動作は**未定義動作**（何が起きても文句を言えない）。
- `{}` で初期化すると、`int x{2.9};` のような情報が失われる変換をコンパイルエラーにしてくれる。
- 初期化していない変数の値を読むのは未定義動作。変数は必ず初期化する。

---

## 📘 基本

### 変数：名前の付いた箱

ゲームでは、体力、所持金、レベルなど、たくさんの値を覚えておく必要があります。プログラムでは、値を**変数**に入れて覚えておきます。変数は「名前の付いた箱」だと考えてください。

```cpp
{{#include examples/variables.cpp:declare}}
```

`int hp = 100;` は、「`int`（整数）を入れる箱を作って `hp` という名前を付け、最初に `100` を入れる」という意味です。変数を作ることを**宣言**、最初に値を入れることを**初期化**と呼びます。

箱の中身は、後から入れ替えられます。これを**代入**と呼びます。

```cpp
{{#include examples/variables.cpp:assign}}
```

📄 [examples/variables.cpp](examples/variables.cpp)

```text
=== 宣言と初期化 ===
体力: 100 / 120

=== 代入 ===
体力: 95
```

`hp = hp + 15;` は数学の式としては成り立ちませんが、プログラムでは「右側を計算してから、その結果を左側の箱に入れる」という意味です。`=` は「等しい」ではなく「入れる」と読んでください。

### 名前の付け方

変数の名前には、次のルールがあります。

- 使える文字は、英字、数字、`_`（アンダースコア）
- 数字から始めることはできない（`1st_player` は不可）
- 大文字と小文字は区別される（`hp` と `HP` は別の変数）
- `int` や `return` など、C++が予約している言葉（**キーワード**）は使えない

ルールを守るだけでなく、**何の値かがわかる名前**を付けることが大切です。`x` や `a` より、`hp`、`max_hp`、`enemy_count` の方が、後から読んだときに意味がすぐわかります。

### 定数：変えてはいけない値

最大レベルのように、プログラムの途中で変わってはいけない値には `const` を付けます。

```cpp
{{#include examples/variables.cpp:constant}}
```

`const` を付けた変数に代入しようとすると、コンパイルエラーになります。うっかり書き換えてしまう間違いを、コンパイラが防いでくれます。

📄 [compile_fail/assign_to_const.cpp](compile_fail/assign_to_const.cpp)

### 基本的な型

C++では、変数ごとに何を入れるか（**型**）を決めます。よく使う型は次の4つです。

```cpp
{{#include examples/basic_types.cpp:types}}
```

📄 [examples/basic_types.cpp](examples/basic_types.cpp)

```text
所持金: 1500
移動速度: 3.5
ランク: S
ボスか: true
```

| 型 | 入れられるもの | 例 | ゲームでの使い道 |
|---|---|---|---|
| `int` | 整数 | `100`、`-5` | 体力、所持金、個数 |
| `double` | 小数 | `3.5`、`-0.25` | 位置、速度、角度 |
| `char` | 1文字 | `'A'`、`'7'` | ランク、記号 |
| `bool` | 真偽値 | `true`、`false` | フラグ（ボスか、死んでいるか） |

`char` の値は `'`（シングルクォート）で囲みます。`"`（ダブルクォート）で囲むと文字列になり、別の扱いになります。文字列は [配列と文字列](../08-arrays-and-strings/)の章で扱います。

小数の型には `float` もあります。`double` の半分の大きさで、精度も低くなります。普段は `double` を使い、メモリや速度が厳しい場面（大量のデータを扱うゲームのグラフィックスなど）で `float` を選びます。

### 計算

```cpp
{{#include examples/arithmetic.cpp:operators}}
```

```text
a + b = 22
a - b = 12
a * b = 85
a / b = 3
a % b = 2
```

掛け算と割り算は、足し算と引き算より先に計算されます。順番を変えたいときは `()` を使います。

```cpp
{{#include examples/arithmetic.cpp:precedence}}
```

「変数に何かを足して、その変数に入れ直す」計算はよく使うので、短い書き方が用意されています。

```cpp
{{#include examples/arithmetic.cpp:compound}}
```

📄 [examples/arithmetic.cpp](examples/arithmetic.cpp)

| 短い書き方 | 意味 |
|---|---|
| `x += 5;` | `x = x + 5;` |
| `x -= 5;` | `x = x - 5;` |
| `x *= 2;` | `x = x * 2;` |
| `x /= 2;` | `x = x / 2;` |
| `++x;` | `x = x + 1;` |
| `--x;` | `x = x - 1;` |

### 整数の割り算は切り捨てられる

**入門者が最もつまずきやすいポイントの1つです。** 整数どうしの割り算は、小数点以下が切り捨てられます。

```cpp
{{#include examples/integer_division.cpp:division}}
```

```text
5 / 2   = 2
5 % 2   = 1
5.0 / 2 = 2.5
```

計算する値のどちらかが小数なら、小数で計算されます。平均を求めるときに、この違いがバグにつながります。

```cpp
{{#include examples/integer_division.cpp:average}}
```

📄 [examples/integer_division.cpp](examples/integer_division.cpp)

```text
間違い: 83
正しい: 83.3333
人数の変数を使う場合: 83.3333
```

`double wrong = total_score / players;` は、結果を `double` に入れているので小数になりそうに見えます。しかし、右側の割り算は整数どうしなので、先に `83` まで切り捨てられ、その後で `double` に変換されます。

両方が整数の変数の場合は、`static_cast<double>(値)` で一方を小数に変換してから割ります。`static_cast` は「型を変換する」ための書き方です。詳しくは [Part 2 キャスト](../../p02-language-basics/11-casts/)で扱います。

### 小数には誤差がある

コンピュータは小数を2進数で表すので、`0.1` のような数をぴったりには表せません。そのため、計算するとわずかな誤差が出ます。

```cpp
{{#include examples/floating_point_error.cpp:error}}
```

```text
sum = 0.3
sum = 0.30000000000000004
sum == 0.3 : false
```

普通に表示すると `0.3` に見えますが、17桁まで表示すると誤差が見えます。そのため、小数を `==` で比べると、思った結果にならないことがあります。小数は、**差が十分に小さいか**で比べます。

```cpp
{{#include examples/floating_point_error.cpp:compare}}
```

📄 [examples/floating_point_error.cpp](examples/floating_point_error.cpp)

```text
差: 5.5511151231257827e-17
十分に近いか: true
```

`std::abs` は絶対値（マイナスを取った値）を求める関数です。`1e-9` は `0.000000001` を表す書き方です。

---

## 🔬 深掘り

### 型の大きさと表せる範囲

型ごとに、メモリ上で使う大きさ（バイト数）が決まっています。`sizeof` で調べられます。

```cpp
{{#include examples/basic_types.cpp:sizeof}}
```

```text
int:    4 バイト
double: 8 バイト
char:   1 バイト
bool:   1 バイト
```

C++の規格は、`char` が1バイトであることは保証していますが、`int` については「最低16ビット」としか決めていません。ただし、現在のWindowsとLinuxの64ビット環境では、`int` はすべて32ビット（4バイト）です。

```cpp
{{#include examples/int_limits.cpp:limits}}
```

📄 [examples/int_limits.cpp](examples/int_limits.cpp)

```text
int の最大値: 2147483647
int の最小値: -2147483648
long long の最大値: 9223372036854775807
```

`int` で表せるのは約±21億です。それより大きな値には `long long`（64ビット）を使います。大きさがはっきり決まった型がほしいときは、`std::int32_t` や `std::int64_t`（`<cstdint>`）を使います。詳しくは [Part 2 基本型](../../p02-language-basics/01-fundamental-types/)で扱います。

### オーバーフローは未定義動作

`int` の最大値に1を足すと、どうなるでしょうか。C++では、符号付き整数（`int` など）が表せる範囲を超えることを**オーバーフロー**と呼び、その動作は**未定義動作**（Undefined Behavior、UB）とされています。

未定義動作とは、「規格が何も保証しない」という意味です。最小値に折り返すかもしれないし、コンパイラの最適化によって予想外の動作をするかもしれません。テストでたまたま正しく動いても、別のコンパイラや最適化の設定で壊れることがあります。**未定義動作はバグそのもの**だと考えてください。

未定義動作は、このリポジトリ全体を通じて繰り返し出てくる重要な概念です。代表的なものは [付録 未定義動作カタログ](../../appendix/03-ub-catalog/)にまとめます。

### 初期化を忘れると未定義動作

関数の中で作った変数は、初期化しないと中身が決まっていません。その値を読むことも未定義動作です。

```cpp
int hp;                // 初期化していない
std::cout << hp;       // ✗ 未定義動作。何が表示されるかわからない
```

**変数は、作るときに必ず初期化します。** 適切な初期値がまだわからない場合でも、`0` などで初期化しておくのが安全です。

### `{}` による初期化

変数は `=` の代わりに `{}` でも初期化できます。

```cpp
int hp{100};      // int hp = 100; と同じ
int damage{2.9};  // ✗ コンパイルエラー
int damage = 2.9; // △ コンパイルは通るが、黙って 2 に切り捨てられる
```

`{}` を使うと、小数を整数に入れるような**情報が失われる変換**（縮小変換）をコンパイルエラーにしてくれます。

📄 [compile_fail/narrowing_brace_init.cpp](compile_fail/narrowing_brace_init.cpp)

このときのGCCのエラーメッセージを見ると、`2.9` が `2.8999999999999999` と表示されます。

```text
error: narrowing conversion of '2.8999999999999999e+0' from 'double' to 'int'
```

`2.9` も、コンピュータの中ではぴったり表せていないことがわかります。初期化の書き方の違いは [Part 2 初期化](../../p02-language-basics/02-initialization/)で詳しく扱います。

### 小数を整数に変換すると、四捨五入ではなく切り捨て

小数を整数に変換すると、小数点以下は**0に近い方へ切り捨て**られます。`2.9` は `2`、`-2.9` は `-2` になります。四捨五入したい場合は、`std::lround`（`<cmath>`）を使います。

この章の主張は、テストでも確かめています。

📄 [tests/variables_and_types_test.cpp](tests/variables_and_types_test.cpp)

---

## ⚠️ 落とし穴とUB

### 1. 整数の割り算で結果が切り捨てられる

平均、割合、比率を計算するときに起きやすいバグです。`double` の変数に入れても、右側の割り算が整数どうしなら、先に切り捨てられます。clang-tidyの `bugprone-integer-division` で検出できます。このリポジトリのCIでも有効にしています。

### 2. 小数を `==` で比べる

`0.1 + 0.2 == 0.3` は `false` です。小数は、差が十分に小さいかで比べます。どのくらい小さければよいかは、扱う値の大きさによって変わります。

### 3. 宣言する前に変数を使う

プログラムは上から順に実行されるので、変数は宣言した行より後でしか使えません。

```text
error: 'hp' was not declared in this scope
```

📄 [compile_fail/use_before_declaration.cpp](compile_fail/use_before_declaration.cpp)

### 4. 変数を初期化しない（UB）

「深掘り」で説明したとおり、初期化していない変数を読むと未定義動作になります。必ず初期化してください。

### 5. `int` のオーバーフロー（UB）

ダメージやスコアの計算で、`int` の範囲（約±21億）を超えることがあります。超える可能性がある値には `long long` を使います。

---

## 🏭 実務・OSSではこう使われる

### Unreal Engine 5 は位置を `float` から `double` に変えた

ゲームでは、キャラクターの位置を小数で表します。Unreal Engine 4までは位置に `float` を使っていましたが、Unreal Engine 5では **Large World Coordinates** という仕組みで `double` に切り替えました。

`float` の精度は有効数字で約7桁しかありません。原点から何キロも離れた場所では、1センチ未満の細かい位置を表せなくなります。その結果、キャラクターがガタガタ震えたり、物理演算が不安定になったりしていました。広大なオープンワールドを扱えるように、より精度の高い `double` に変えたのです。小数の精度が、ゲームの品質に直接影響する例です。

### 整数か小数か

ゲームでは、どちらの型を使うかを意識して決めます。

- **整数を使うもの**：体力、所持金、アイテムの個数など、誤差があっては困る値。小数で持つと、`0.1` ずつ増やしたときに誤差が積み重なります。
- **小数を使うもの**：位置、速度、回転など、連続的に変化する値。誤差は避けられないので、比べるときは「十分に近いか」で判定します。

---

## 🦀 Rustとの対応

| 観点 | C++ | Rust |
|---|---|---|
| 変数の宣言 | `int hp = 100;` | `let mut hp: i32 = 100;` |
| 変更できない変数 | `const` を付ける | 既定で変更できない（`mut` を付けると変更できる） |
| 整数の型 | `int`（大きさは環境依存）、`std::int32_t` | `i32`、`i64` など（大きさが名前に入っている） |
| 小数の型 | `double`、`float` | `f64`、`f32` |
| 文字の型 | `char`（1バイト） | `char`（4バイト。Unicodeの1文字） |
| 整数の割り算 | 切り捨て | 切り捨て（同じ） |
| 符号付き整数のオーバーフロー | **未定義動作** | デバッグビルドではパニック、リリースビルドでは折り返し |
| 小数を整数に入れる | 暗黙に変換される（`{}` ならエラー） | `as` で明示的に変換しないとエラー |
| 初期化していない変数の読み取り | **未定義動作** | コンパイルエラー |

**Rustの知識が罠になる点：** C++では、変数は既定で**変更できます**。変更しない変数には自分で `const` を付ける必要があります。また、オーバーフローや初期化忘れは、Rustのように止めてくれず、未定義動作になります。

---

## ❓ 思い出しクイズ

**Q1.** 次のコードを実行すると、`hp` はいくつになりますか？

```cpp
int hp = 100;
hp = hp - 30;
hp += 10;
```

<details>
<summary>答え</summary>

`80` です。`100 - 30 = 70`、次に `70 + 10 = 80` になります。

</details>

**Q2.** `7 / 2` と `7 % 2` と `7.0 / 2` の結果を答えてください。

<details>
<summary>答え</summary>

`7 / 2` は `3`（整数どうしの割り算は切り捨て）、`7 % 2` は `1`（余り）、`7.0 / 2` は `3.5`（一方が小数なので小数で計算される）です。

</details>

**Q3.** 次のコードで、`average` が `83` になってしまうのはなぜですか？ どう直せばよいですか？

```cpp
int total = 250;
int count = 3;
double average = total / count;
```

<details>
<summary>答え</summary>

右側の `total / count` が整数どうしの割り算なので、`double` に入れる前に `83` へ切り捨てられるためです。`static_cast<double>(total) / count` のように、一方を小数に変換してから割ります。

</details>

**Q4.** `0.1 + 0.2 == 0.3` が `false` になるのはなぜですか？ 小数はどう比べればよいですか？

<details>
<summary>答え</summary>

コンピュータは小数を2進数で表すため、`0.1` や `0.2` をぴったりには表せず、計算結果にわずかな誤差が出るためです。小数は `==` ではなく、`std::abs(a - b) < 1e-9` のように、差が十分に小さいかで比べます。

</details>

**Q5.** 次の2行の違いは何ですか？

```cpp
int a = 2.9;
int b{2.9};
```

<details>
<summary>答え</summary>

`int a = 2.9;` はコンパイルが通り、黙って `2` に切り捨てられます。`int b{2.9};` は、情報が失われる変換（縮小変換）なのでコンパイルエラーになります。

</details>

**Q6.** `int` の最大値に1を足すと、どうなりますか？

<details>
<summary>答え</summary>

符号付き整数のオーバーフローなので、未定義動作です。結果は保証されず、コンパイラの最適化によって予想外の動作をすることもあります。

</details>

---

## 📎 参照

### このリポジトリ内

- コード例：[variables.cpp](examples/variables.cpp)、[basic_types.cpp](examples/basic_types.cpp)、[arithmetic.cpp](examples/arithmetic.cpp)、[integer_division.cpp](examples/integer_division.cpp)、[floating_point_error.cpp](examples/floating_point_error.cpp)、[int_limits.cpp](examples/int_limits.cpp)
- テスト：[variables_and_types_test.cpp](tests/variables_and_types_test.cpp)
- compile_fail：[narrowing_brace_init.cpp](compile_fail/narrowing_brace_init.cpp)、[assign_to_const.cpp](compile_fail/assign_to_const.cpp)、[use_before_declaration.cpp](compile_fail/use_before_declaration.cpp)
- 前の章：[開発環境とHello World](../02-hello-world/)
- 次の章：[入力と出力](../04-input-output/)
- 関連する章：[Part 2 基本型](../../p02-language-basics/01-fundamental-types/)、[Part 2 初期化](../../p02-language-basics/02-initialization/)、[Part 2 キャスト](../../p02-language-basics/11-casts/)、[Part 8 浮動小数点](../../p08-performance/15-floating-point/)、[付録 未定義動作カタログ](../../appendix/03-ub-catalog/)

### 外部

- [cppreference: Fundamental types](https://en.cppreference.com/w/cpp/language/types)
- [cppreference: Arithmetic operators](https://en.cppreference.com/w/cpp/language/operator_arithmetic)
- [cppreference: std::numeric_limits](https://en.cppreference.com/w/cpp/types/numeric_limits)
- [Large World Coordinates（Unreal Engine ドキュメント）](https://dev.epicgames.com/documentation/en-us/unreal-engine/large-world-coordinates-in-unreal-engine-5)
