<!-- status: draft -->

# ムーブセマンティクス

★★★☆ 実務　`C++11〜`

> コピーせずに「中身を引き渡す」仕組み。C++の性能と所有権の表現を支える中心的な機能。

---

## ⚡ 30秒で思い出す

- **`std::move(x)` は何も動かさない。** `x` を右辺値参照（`T&&`）にキャストするだけ。
- 実際に中身を移すのは、**ムーブコンストラクタ**と**ムーブ代入演算子**。
- ムーブ後のオブジェクトは**「有効だが未規定の状態」**。破棄・再代入はしてよいが、特定の値を前提にしてはいけない。
- ムーブ操作には **`noexcept` を付ける**。付けないと、`std::vector` の再確保でコピーされる。
- **`const` オブジェクトは `std::move` してもコピーになる。**
- **`return std::move(local);` とは書かない。** コピー省略（RVO）を妨げる。
- 自作クラスでは、ムーブを手で書かずに済む **Rule of Zero** が第一選択。

---

## 📘 基本

### なぜムーブが必要なのか

引っ越しにたとえると、**コピーは家具を全部作り直して新居に置くこと**、**ムーブは新居の鍵を渡すこと**です。

`std::vector<int>` の中身はヒープ上のバッファにあり、`vector` 本体はそのバッファへのポインタとサイズを持っているだけです。コピーするとバッファ全体を複製しますが、ムーブならポインタを付け替えるだけで済みます。

```cpp
{{#include examples/basic_move.cpp:copy}}
```

```cpp
{{#include examples/basic_move.cpp:move}}
```

📄 [examples/basic_move.cpp](examples/basic_move.cpp)

実行結果：

```text
=== コピー：中身を複製する ===
a.size() = 1000000, b.size() = 1000000
同じバッファを指しているか: false

=== ムーブ：中身を引き渡す ===
c は a のバッファを引き継いだか: true
ムーブ後の a.size() = 0
```

### 左辺値と右辺値

ムーブを理解するには、式を2種類に分けて考えます（正確な分類は「深掘り」で扱います）。

| 種類 | 例 | 特徴 |
|---|---|---|
| **左辺値**（lvalue） | `a`、`*p`、`v[0]` | 名前や場所があり、この先も使われる可能性がある |
| **右辺値**（rvalue） | `42`、`a + b`、`std::string("x")` | 一時的な値で、この式が終わると消える |

右辺値はこの先誰も使わないので、**中身を奪っても困る人がいません**。C++11は、右辺値だけを受け取る**右辺値参照 `T&&`** を導入し、「奪ってよい相手」を型で区別できるようにしました。

```cpp
void take(std::string&& s); // 右辺値だけを受け取る

std::string name = "Alice";
take(std::string("Bob"));   // OK：一時オブジェクトは右辺値
take(name);                 // エラー：name は左辺値
take(std::move(name));      // OK：std::move で右辺値として扱う
```

名前のある変数を右辺値参照に直接束縛できないことは、compile_failテストで確かめています。

📄 [compile_fail/bind_rvalue_ref_to_lvalue.cpp](compile_fail/bind_rvalue_ref_to_lvalue.cpp)

### std::move は「もう使わない」という宣言

`std::move(x)` は、「`x` はもう使わないので、中身を奪ってよい」とコンパイラに伝える印です。それ自体は何も移動しません。印を受け取ったムーブコンストラクタやムーブ代入演算子が、実際に中身を移します。

### ムーブが起きる場面

| 場面 | 例 |
|---|---|
| 一時オブジェクトから初期化・代入する | `std::string s = make_name();` |
| `std::move` で明示する | `v.push_back(std::move(s));` |
| 関数がローカル変数を返す | `return result;`（ムーブか、それより速いコピー省略が起きる） |

### ムーブ専用の型を自作する

ヒープ上の配列を所有するクラスに、ムーブコンストラクタとムーブ代入演算子を書いてみます。

```cpp
{{#include examples/buffer.hpp:buffer}}
```

📄 [examples/buffer.hpp](examples/buffer.hpp)

ポイントは3つです。

1. **相手の中身を奪い、相手を空にする。** `std::exchange(other.data_, nullptr)` は「`other.data_` の値を取り出し、`nullptr` を代入する」を1行で行います。相手を空にしないと、相手のデストラクタが同じ配列を `delete[]` してしまいます（二重解放）。
2. **`noexcept` を付ける。** ポインタの付け替えだけなので例外は起きません。理由は「深掘り」で説明します。
3. **コピーを `delete` する。** 所有者を常に1人に保ちます。`std::unique_ptr` と同じ設計です。

```cpp
{{#include examples/move_only_type.cpp:container}}
```

📄 [examples/move_only_type.cpp](examples/move_only_type.cpp)

> **実務では手で書かない。** メンバを `std::unique_ptr<int[]>` や `std::vector<int>` にすれば、コンパイラが正しいムーブを自動で生成します。これを **Rule of Zero** と呼びます（[Rule of 0 / 3 / 5](../06-rule-of-zero-three-five/README.md)）。

---

## 🔬 深掘り

### std::move の正体

`std::move` の実装は、ほぼ次のキャストだけです。

```cpp
{{#include examples/std_move_is_cast.cpp:my_move}}
```

📄 [examples/std_move_is_cast.cpp](examples/std_move_is_cast.cpp)

`T&&` は転送参照なので左辺値も右辺値も受け取れます。`std::remove_reference_t<T>&&` で、どちらであっても必ず右辺値参照にして返します。名前が誤解を招くため、`rvalue_cast` という名前の方が正確だったとよく言われます。

### 値カテゴリの正確な分類

C++11以降、式は次の3つの基本カテゴリに分類されます（[値カテゴリ](../04-value-categories/README.md)で詳しく扱います）。

| カテゴリ | 意味 | 例 |
|---|---|---|
| lvalue | 識別できる場所があり、ムーブ元にならない | `x`、`*p` |
| xvalue | 識別できる場所があるが、中身を奪ってよい | `std::move(x)`、`static_cast<T&&>(x)` |
| prvalue | 純粋な一時値 | `42`、`f()`（値を返す関数呼び出し） |

`std::move(x)` の結果は **xvalue** です。lvalueとxvalueをまとめて glvalue、xvalueとprvalueをまとめて rvalue と呼びます。

### ムーブ操作が暗黙に生成される条件

コンパイラは、次の**いずれも**ユーザーが宣言していない場合に限り、ムーブコンストラクタとムーブ代入演算子を暗黙に生成します。

- コピーコンストラクタ
- コピー代入演算子
- ムーブ操作のもう一方
- デストラクタ

つまり、**デストラクタを書いただけでムーブは生成されなくなり、ムーブのつもりのコードがすべてコピーになります。** コンパイルエラーにはならないので気づきにくい罠です。

### noexcept と強い例外安全保証

`std::vector` は容量が足りなくなると、新しいバッファを確保して要素を移し替えます。このとき、移し替えの途中で例外が起きても**元の状態に戻せること**（強い例外安全保証）を約束しています。

- ムーブは元の要素を壊すので、途中で例外が起きると元に戻せません。
- コピーなら元の要素は無傷なので、新しいバッファを捨てれば元に戻せます。

そのため `std::vector` は、ムーブコンストラクタが `noexcept` のときだけムーブし、そうでなければコピーを選びます（`std::move_if_noexcept`）。

```cpp
{{#include examples/tracked.hpp:tracked}}
```

```cpp
{{#include examples/noexcept_and_vector.cpp:reallocate}}
```

📄 [examples/noexcept_and_vector.cpp](examples/noexcept_and_vector.cpp)

実行結果：

```text
=== ムーブコンストラクタが noexcept の場合 ===
コピー: 0 回, ムーブ: 4 回

=== ムーブコンストラクタが noexcept でない場合 ===
コピー: 4 回, ムーブ: 0 回
```

コピーできない型（ムーブ専用の型）の場合は、`noexcept` でなくてもムーブが使われます。ただし、そのときは強い例外安全保証が失われます。

### return 文での暗黙のムーブ

関数がローカル変数を返すとき、コンパイラはまず**コピー省略**（NRVO：呼び出し側の領域に直接構築する）を試み、できなければ**暗黙にムーブ**します。どちらも、ソースコードに `std::move` を書く必要はありません。

暗黙のムーブが適用される範囲は、規格の改訂のたびに広がってきました。

| 規格 | 変更 |
|---|---|
| C++11 | ローカル変数をそのまま返すときに暗黙のムーブ |
| C++20 | 右辺値参照の引数を返す場合などにも拡大（P1825） |
| C++23 | 規則を単純化し、さらに範囲を拡大（P2266） |

コピー省略の詳細は[コピー省略とRVO](../11-copy-elision/README.md)で扱います。

### 標準ライブラリの型のムーブ後の状態

規格は、標準ライブラリの型について、ムーブ後は「有効だが未規定の状態」になるとだけ定めています（[lib.types.movedfrom]）。ただし、型によってはより強い保証があります。

| 型 | ムーブ後の状態 |
|---|---|
| `std::unique_ptr` / `std::shared_ptr` | `nullptr` になることが保証されている |
| `std::vector`（ムーブコンストラクタの場合） | 空になることが保証されている |
| `std::string` | 未規定（実装上は空になることが多いが、前提にしてはいけない） |

```cpp
{{#include examples/moved_from_state.cpp:moved_from}}
```

```cpp
{{#include examples/moved_from_state.cpp:reuse}}
```

📄 [examples/moved_from_state.cpp](examples/moved_from_state.cpp)

---

## ⚠️ 落とし穴とUB

### 1. const オブジェクトを std::move してもコピーになる

```cpp
{{#include examples/std_move_is_cast.cpp:const_move}}
```

`std::move(name)` の型は `const std::string&&` です。これはムーブコンストラクタ（`std::string&&`）には渡せませんが、コピーコンストラクタ（`const std::string&`）には渡せるので、**エラーにならずに黙ってコピーされます**。clang-tidyの `performance-move-const-arg` で検出できます。

### 2. return std::move(local) はかえって遅くなる

```cpp
std::vector<int> make() {
    std::vector<int> result(1000);
    return std::move(result); // ✗ コピー省略（NRVO）ができなくなる
    // return result;         // ○ コピー省略か、暗黙のムーブが起きる
}
```

GCCとClangは `-Wpessimizing-move` で警告します。このプロジェクトでは `-Wall` と `-Werror` によりエラーになります。

### 3. ムーブ後のオブジェクトを使う

```cpp
std::string s = "hello";
consume(std::move(s));
std::cout << s.size(); // コンパイルは通るが、値は未規定
```

未定義動作ではありませんが、バグです。Rustと違ってコンパイラは止めてくれないので、clang-tidyの `bugprone-use-after-move` に頼ります。

### 4. デストラクタを書いたら、ムーブが消えていた

「深掘り」で説明したとおり、デストラクタ（ログ出力用の空のものでも）を宣言すると、ムーブ操作は暗黙に生成されなくなります。必要なら `= default` で明示します。

```cpp
struct Widget {
    ~Widget() { log("destroyed"); }
    Widget(Widget&&) noexcept = default;            // 明示しないとムーブが消える
    Widget& operator=(Widget&&) noexcept = default;
    Widget(const Widget&) = default;                // ムーブを宣言するとコピーが消えるので、こちらも明示する
    Widget& operator=(const Widget&) = default;
};
```

### 5. ムーブコンストラクタに noexcept を付け忘れる

例外を投げないのに `noexcept` を付け忘れると、`std::vector` の再確保ですべてコピーになります。clang-tidyの `performance-noexcept-move-constructor` で検出できます。

### 6. 自己ムーブ代入

`a = std::move(a);` は通常は書きませんが、`v[i] = std::move(v[j]);` のように、添字が一致したときに起こりえます。自作のムーブ代入演算子では、`this != &other` を確認するか、自己代入でも壊れない書き方にします。

---

## 🏭 実務・OSSではこう使われる

### Unreal Engine：std::move の代わりに MoveTemp を使う

UEのコーディング規約では、`std::move` ではなく `MoveTemp` を使います。`MoveTemp` は、**`const` オブジェクトや右辺値に対して使うとコンパイルエラーになる**ように作られています。上の落とし穴1を、コンパイル時に防ぐ設計です。

```cpp
TArray<FString> Names = LoadNames();
TArray<FString> Moved = MoveTemp(Names); // UEではこちらを使う
```

`TArray` をはじめとするUEのコンテナも、標準ライブラリと同じくムーブに対応しています。大きな配列を関数間で受け渡すとき、ムーブを意識するかどうかで性能が大きく変わります。詳しくは [Part 12 UEのコンテナ](../../p12-unreal-cpp/06-containers/README.md)で扱います。

### clang-tidy による機械的なチェック

LLVMやChromiumなどの大規模プロジェクトでは、ムーブに関する誤りを人の目だけに頼らず、clang-tidyで機械的に検出しています。

| チェック | 検出するもの |
|---|---|
| `bugprone-use-after-move` | ムーブ後のオブジェクトの使用 |
| `performance-move-const-arg` | `const` オブジェクトへの `std::move` |
| `performance-noexcept-move-constructor` | `noexcept` のないムーブ操作 |
| `performance-unnecessary-value-param` | 値渡しの引数による不要なコピー |

このプロジェクトの `.clang-tidy` でも有効にしています。

### ゲームでの使いどころ

- **リソースハンドル**：テクスチャ、メッシュ、GPUバッファなど、二重に解放してはいけないものはムーブ専用の型にします。所有者が1人であることを型で保証できます。
- **フレームごとのデータ受け渡し**：ゲームスレッドで作ったデータをレンダースレッドへ渡すとき、コピーせずにムーブで引き渡します。

---

## 🦀 Rustとの対応

| 観点 | C++ | Rust |
|---|---|---|
| 既定の動作 | コピー（コピーできる型の場合） | ムーブ（`Copy` 型を除く） |
| ムーブの実体 | ユーザー定義の関数（ムーブコンストラクタ） | 常にビット単位のコピー（memcpy） |
| ムーブ元 | 生きている。後でデストラクタも呼ばれる | 使えなくなる。`Drop` も呼ばれない |
| ムーブ後の使用 | コンパイルが通る（clang-tidyで検出） | コンパイルエラー |
| 明示的なコピー | 不要（暗黙にコピーされる） | `.clone()` が必要 |

**Rustの知識が罠になる点：** C++のムーブ元は「抜け殻」として生き続け、スコープの終わりでデストラクタが呼ばれます。そのため、ムーブコンストラクタでは**ムーブ元を「破棄しても安全な状態」にしておく責任**があります（`Buffer` で `data_` を `nullptr` にしたのはこのためです）。Rustではコンパイラがムーブ元を無効にするので、この責任はありません。

---

## ❓ 思い出しクイズ

**Q1.** `std::move(x)` を呼んだ時点で、`x` の中身は移動していますか？

<details>
<summary>答え</summary>

移動していません。`std::move` は右辺値参照へのキャストにすぎず、実際に中身を移すのは、その結果を受け取ったムーブコンストラクタやムーブ代入演算子です。

</details>

**Q2.** 次のコードで、`copied` の初期化はコピーとムーブのどちらですか？

```cpp
const std::string name = "Alice";
std::string copied = std::move(name);
```

<details>
<summary>答え</summary>

コピーです。`std::move(name)` の型は `const std::string&&` で、ムーブコンストラクタ（`std::string&&`）には渡せないため、コピーコンストラクタが選ばれます。

</details>

**Q3.** ムーブコンストラクタに `noexcept` を付けないと、`std::vector` の再確保で何が起きますか？ それはなぜですか？

<details>
<summary>答え</summary>

要素がムーブではなくコピーされます。`std::vector` は強い例外安全保証（途中で例外が起きても元に戻せること）を守るため、ムーブが例外を投げうる場合は、元の要素を壊さないコピーを選びます。

</details>

**Q4.** 自作クラスにログ出力用のデストラクタを追加しました。ムーブにはどんな影響がありますか？

<details>
<summary>答え</summary>

ムーブコンストラクタとムーブ代入演算子が暗黙に生成されなくなり、ムーブしようとしたコードがすべてコピーになります。必要であれば `= default` で明示します。

</details>

**Q5.** `return std::move(result);` と書くべきではないのはなぜですか？

<details>
<summary>答え</summary>

コピー省略（NRVO）が適用されなくなるためです。`return result;` と書けば、コンパイラはコピー省略を試み、できなければ暗黙にムーブします。

</details>

---

## 📎 参照

### このリポジトリ内

- テスト：[tests/move_semantics_test.cpp](tests/move_semantics_test.cpp)
- compile_fail：[compile_fail/](compile_fail/)
- ベンチマーク：[bench/copy_vs_move.cpp](bench/copy_vs_move.cpp)
- 関連する章：[値カテゴリ](../04-value-categories/README.md)、[Rule of 0 / 3 / 5](../06-rule-of-zero-three-five/README.md)、[例外安全性](../10-exception-safety/README.md)、[コピー省略とRVO](../11-copy-elision/README.md)、[完全転送](../12-perfect-forwarding/README.md)

### cppreference

- [std::move](https://en.cppreference.com/w/cpp/utility/move)
- [Move constructors](https://en.cppreference.com/w/cpp/language/move_constructor)
- [Move assignment operator](https://en.cppreference.com/w/cpp/language/move_assignment)
- [Value categories](https://en.cppreference.com/w/cpp/language/value_category)
- [std::move_if_noexcept](https://en.cppreference.com/w/cpp/utility/move_if_noexcept)

### 規格

- [class.copy.ctor]、[class.copy.assign]：特殊メンバ関数の暗黙の宣言
- [lib.types.movedfrom]：標準ライブラリの型のムーブ後の状態
- P1825R0「Merged wording for P0527R1 and P1155R3」（C++20の暗黙のムーブの拡大）
- P2266R3「Simpler implicit move」（C++23）

### 書籍・講演

- Nicolai M. Josuttis『C++ Move Semantics - The Complete Guide』
- Scott Meyers『Effective Modern C++』項目23〜30
