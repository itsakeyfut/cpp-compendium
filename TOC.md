# cpp-compendium 目次

このファイルが目次の唯一の情報源です。章の追加・並べ替え・改名はこのファイルを編集し、`just sync` で `content/SUMMARY.md`・各Partの `README.md`・`content/STATUS.md` に反映します。

## 凡例

| 記号 | 意味 |
|---|---|
| ★☆☆☆ | 入門 |
| ★★☆☆ | 基礎 |
| ★★★☆ | 実務 |
| ★★★★ | 専門 |
| 🎮 | UE開発・ゲームエンジン開発に直結する章 |
| `C++23` などのバッジ | 基準（C++20）より新しい規格の機能を扱う |
| `予定` | C++26の機能。規格の発行状況が決まるまで「予定」として扱う |

## 規模

| Part | 章数 |
|---|---|
| 0 プログラミング入門 | 11 |
| 1 ツールチェーンとビルド | 13 |
| 2 言語の基礎 | 15 |
| 3 オブジェクトと所有権 | 13 |
| 4 標準ライブラリ | 17 |
| 5 ジェネリックプログラミング | 15 |
| 6 設計とイディオム | 14 |
| 7 並行・並列 | 14 |
| 8 メモリとパフォーマンス | 16 |
| 9 SIMDと低レイヤ最適化 | 14 |
| 10 バイナリ解析とセキュリティ | 11 |
| 11 大規模開発 | 14 |
| 12 Unreal Engine C++ | 18 |
| 付録 | 9 |
| **合計** | **194** |

---

## Part 0　プログラミング入門　`p00-programming-intro`

プログラミング未経験の人が、C++で最初の一歩を踏み出すためのPartです。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-what-is-programming` | プログラムとは何か | ★☆☆☆ | CPU・メモリ・ファイルの役割、ソースコードが実行されるまで |
| 02 | `02-hello-world` | 開発環境とHello World | ★☆☆☆ | 開発環境の準備、最初のプログラム、コンパイルエラーの読み方 |
| 03 | `03-variables-and-types` | 変数と型 | ★☆☆☆ | 整数・小数・文字・真偽値、代入、算術演算 |
| 04 | `04-input-output` | 入力と出力 | ★☆☆☆ | `std::cin`、`std::cout`、`std::print` `C++23` |
| 05 | `05-conditionals` | 条件分岐 | ★☆☆☆ | `if` / `else`、`switch`、比較演算と論理演算 |
| 06 | `06-loops` | 繰り返し | ★☆☆☆ | `while`、`for`、範囲for、`break` / `continue` |
| 07 | `07-functions` | 関数 | ★☆☆☆ | 引数、戻り値、スコープ、関数に分ける理由 |
| 08 | `08-arrays-and-strings` | 配列と文字列 | ★☆☆☆ | `std::vector`、`std::array`、`std::string` の基本 |
| 09 | `09-structs` | 構造体でデータをまとめる | ★☆☆☆ | `struct`、メンバ、構造体の配列 |
| 10 | `10-debugging-basics` | バグの見つけ方 | ★☆☆☆ | printデバッグ、デバッガの基本操作、問題の切り分け |
| 11 | `11-first-game` | 総まとめ：テキストゲームを作る | ★☆☆☆ | ここまでの知識で小さなゲームを完成させる 🎮 |

**実装課題**：数当てゲーム、じゃんけん、ターン制のテキストバトル

---

## Part 1　ツールチェーンとビルド　`p01-toolchain`

C++のコードが実行ファイルになる仕組みと、日々使う道具を理解します。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-compilation-model` | コンパイルの仕組み | ★★☆☆ | プリプロセス→コンパイル→アセンブル→リンク、翻訳単位 |
| 02 | `02-headers-and-odr` | ヘッダとODR | ★★☆☆ | インクルードガード、`#pragma once`、宣言と定義、ODR、`inline` |
| 03 | `03-linking` | リンクとライブラリ | ★★☆☆ | 静的・動的ライブラリ、シンボル、名前マングリング、リンクエラーの読み方 |
| 04 | `04-preprocessor` | プリプロセッサ | ★★☆☆ | マクロ、条件コンパイル、X-macro、マクロの落とし穴 🎮 |
| 05 | `05-compilers-and-flags` | コンパイラとオプション | ★★☆☆ | GCC / Clang / MSVC、最適化レベル、警告、規格の指定 |
| 06 | `06-cmake-basics` | CMake入門 | ★★☆☆ | ターゲット、プロパティ、依存関係、CMakePresets |
| 07 | `07-vcpkg` | vcpkgで依存を管理する | ★★☆☆ | マニフェストモード、トリプレット、バージョン固定 |
| 08 | `08-debugger` | デバッガを使いこなす | ★★☆☆ | ブレークポイント、ウォッチ、コールスタック、条件付きブレーク、コアダンプ |
| 09 | `09-sanitizers` | Sanitizer | ★★☆☆ | ASan、UBSan、TSan、MSan、出力の読み方 |
| 10 | `10-static-analysis` | 静的解析と整形 | ★★☆☆ | clang-tidy、clang-format、警告をエラーとして扱う |
| 11 | `11-googletest` | GoogleTestでテストを書く | ★★☆☆ | TEST / TEST_F、アサーション、パラメータ化テスト |
| 12 | `12-compiler-explorer` | Compiler Explorerでアセンブリを見る | ★★☆☆ | Godboltの使い方、コンパイラ間の比較、最適化の確認 |
| 13 | `13-build-times` | ビルド時間を短くする | ★★★☆ | 前方宣言、PCH、unity build、ccache、include-what-you-use 🎮 |

**実装課題**：ヘッダとライブラリに分けた小さなプロジェクトをCMakeとvcpkgで構成し、テストとSanitizerをCIで回す

---

## Part 2　言語の基礎　`p02-language-basics`

C++の文法と、他言語と違う点を押さえます。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-fundamental-types` | 基本型 | ★★☆☆ | 整数の幅と符号、浮動小数点、固定幅整数型、整数昇格、暗黙の型変換 |
| 02 | `02-initialization` | 初期化 | ★★☆☆ | デフォルト・値・リスト・集成体・指示付き初期化、`auto`、narrowing |
| 03 | `03-references-and-pointers` | 参照とポインタ | ★★☆☆ | 参照、ポインタ、`nullptr`、ポインタ演算、使い分け |
| 04 | `04-const` | constとconstexpr入門 | ★★☆☆ | `const`、`constexpr` の基本、const正しさの入口 |
| 05 | `05-functions` | 関数の詳細 | ★★☆☆ | 引数の渡し方（値・参照・const参照）、オーバーロード、デフォルト引数 |
| 06 | `06-scope-and-storage` | スコープと記憶域期間 | ★★☆☆ | 自動・静的・スレッド・動的記憶域、`static` 変数、初期化順序の問題 |
| 07 | `07-namespaces` | 名前空間 | ★★☆☆ | 名前空間、無名名前空間、`using` の使いどころ |
| 08 | `08-enums` | 列挙型 | ★★☆☆ | `enum` と `enum class`、基底型、ビットフラグ 🎮 |
| 09 | `09-classes` | クラス | ★★☆☆ | メンバ関数、アクセス制御、`this`、`struct` と `class` |
| 10 | `10-operator-overloading` | 演算子オーバーロード | ★★☆☆ | 算術・比較・添字演算子、三方比較 `<=>` 🎮 |
| 11 | `11-casts` | キャスト | ★★☆☆ | `static_cast` / `reinterpret_cast` / `const_cast` / `dynamic_cast`、`std::bit_cast` |
| 12 | `12-c-arrays-and-strings` | C配列とC文字列 | ★★☆☆ | 配列の減衰、C文字列、避けるべき理由と出会う場面 |
| 13 | `13-lambdas` | ラムダ式 | ★★☆☆ | キャプチャ、ジェネリックラムダ、ラムダの正体 |
| 14 | `14-exceptions-basics` | 例外の基本 | ★★☆☆ | `throw` / `try` / `catch`、`noexcept`、例外の型 |
| 15 | `15-inheritance-and-virtual` | 継承と仮想関数 | ★★☆☆ | 継承、`virtual`、`override` / `final`、抽象クラス、仮想デストラクタ、vtable入門 |

**実装課題**：2D/3Dベクトル型（演算子オーバーロード付き）、図形クラス階層と面積計算

---

## Part 3　オブジェクトと所有権　`p03-ownership`

C++の核心です。オブジェクトがいつ作られ、誰が所有し、いつ壊されるかを理解します。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-constructors-and-destructors` | コンストラクタとデストラクタ | ★★☆☆ | 特殊メンバ関数、メンバ初期化子リスト、`explicit`、初期化の順序 |
| 02 | `02-raii` | RAII | ★★☆☆ | リソース管理の原則、スコープガード |
| 03 | `03-copy-semantics` | コピー | ★★☆☆ | コピーコンストラクタとコピー代入、浅いコピーと深いコピー |
| 04 | `04-value-categories` | 値カテゴリ | ★★★☆ | lvalue / prvalue / xvalue、一時オブジェクト |
| 05 | `05-move-semantics` | ムーブセマンティクス | ★★★☆ | 右辺値参照、`std::move`、ムーブ後の状態 🦀 |
| 06 | `06-rule-of-zero-three-five` | Rule of 0 / 3 / 5 | ★★★☆ | 特殊メンバ関数の暗黙生成ルール、`= default` / `= delete` |
| 07 | `07-smart-pointers` | スマートポインタ | ★★☆☆ | `unique_ptr`、`shared_ptr`、`weak_ptr`、`make_*`、カスタムデリータ |
| 08 | `08-ownership-design` | 所有と借用の表現 | ★★★☆ | 非所有ポインタ、`span` / `string_view`、循環参照、Rustとの比較 🦀 |
| 09 | `09-lifetime-and-ub` | 寿命と未定義動作 | ★★★☆ | ダングリング、一時オブジェクトの寿命延長、placement new、`std::launder` |
| 10 | `10-exception-safety` | 例外安全性 | ★★★☆ | 基本・強い・nothrow保証、copy-and-swap |
| 11 | `11-copy-elision` | コピー省略とRVO | ★★★☆ | 保証されたコピー省略、NRVO、返り値の書き方 |
| 12 | `12-perfect-forwarding` | 完全転送 | ★★★☆ | 転送参照、`std::forward`、参照の折りたたみ |
| 13 | `13-object-layout` | オブジェクトのメモリ配置 | ★★★☆ | `sizeof`、パディング、空基底最適化、`[[no_unique_address]]` 🎮 |

**実装課題**：`unique_ptr` の自作、強い例外安全保証を満たす `vector` の自作

---

## Part 4　標準ライブラリ　`p04-standard-library`

標準ライブラリを、選べる・組み合わせられる・落とし穴を避けられる状態にします。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-overview` | 標準ライブラリの全体像 | ★★☆☆ | ヘッダの構成、何がどこにあるか |
| 02 | `02-sequence-containers` | シーケンスコンテナ | ★★☆☆ | `vector`、`array`、`deque`、`list`、`forward_list` |
| 03 | `03-associative-containers` | 連想コンテナ | ★★☆☆ | `map` / `set`、`unordered_*`、ハッシュ、`flat_map` `C++23` |
| 04 | `04-container-choice` | コンテナの選び方 | ★★★☆ | 計算量、メモリ配置、イテレータの無効化 🎮 |
| 05 | `05-iterators` | イテレータ | ★★☆☆ | イテレータの種類、範囲、自作イテレータ |
| 06 | `06-algorithms` | アルゴリズム | ★★☆☆ | 検索・ソート・変換・集計、erase-removeイディオム |
| 07 | `07-ranges` | Ranges | ★★★☆ | viewとadaptor、パイプライン、遅延評価 |
| 08 | `08-strings` | 文字列 | ★★☆☆ | `string`、`string_view`、文字コード、`char8_t` 🎮 |
| 09 | `09-span-and-mdspan` | spanとmdspan | ★★★☆ | `span`、`mdspan` `C++23` |
| 10 | `10-optional-variant-any` | optional / variant / any | ★★★☆ | 使い分け、`std::visit` |
| 11 | `11-expected` | expectedによるエラー処理 | ★★★☆ | `std::expected` `C++23`、モナド的な操作 |
| 12 | `12-function-wrappers` | 関数ラッパー | ★★★☆ | `std::function`、`move_only_function` `C++23`、`function_ref` `予定` |
| 13 | `13-format-and-print` | 書式化と出力 | ★★☆☆ | `std::format`、`std::print` `C++23`、カスタムフォーマッタ |
| 14 | `14-chrono` | 時間 | ★★☆☆ | duration、time_point、時計の種類、フレーム時間の計測 🎮 |
| 15 | `15-random` | 乱数 | ★★☆☆ | エンジンと分布、シード、再現性 🎮 |
| 16 | `16-filesystem-and-io` | ファイルと入出力 | ★★☆☆ | `filesystem`、ストリーム、バイナリI/O |
| 17 | `17-utilities` | ユーティリティ | ★★☆☆ | `pair` / `tuple`、構造化束縛、`<bit>`、`<numeric>` |

**実装課題**：LRUキャッシュ、ログファイル解析ツール

---

## Part 5　ジェネリックプログラミング　`p05-generic-programming`

テンプレートで、再利用でき、型安全で、速いコードを書きます。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-function-templates` | 関数テンプレート | ★★☆☆ | 定義、インスタンス化、ヘッダに書く理由 |
| 02 | `02-class-templates` | クラステンプレート | ★★★☆ | メンバ関数、非型テンプレート引数、エイリアステンプレート |
| 03 | `03-deduction` | 型推論 | ★★★☆ | テンプレート引数推論、CTAD、`auto` / `decltype` / `decltype(auto)` |
| 04 | `04-specialization` | 特殊化 | ★★★☆ | 完全特殊化、部分特殊化、オーバーロードとの関係 |
| 05 | `05-variadic-templates` | 可変長テンプレート | ★★★☆ | パラメータパック、fold式 |
| 06 | `06-type-traits` | 型特性 | ★★★☆ | `<type_traits>`、自作の型特性 |
| 07 | `07-sfinae` | SFINAE | ★★★★ | `enable_if`、detectionイディオム、既存コードを読むための知識 |
| 08 | `08-concepts` | Concepts | ★★★☆ | `requires`、標準コンセプト、自作コンセプト、エラーメッセージの改善 |
| 09 | `09-constexpr` | コンパイル時実行 | ★★★☆ | `constexpr` / `consteval` / `constinit`、`if constexpr` |
| 10 | `10-compile-time-computation` | コンパイル時計算の活用 | ★★★★ | テーブルの事前生成、コンパイル時の文字列ハッシュ 🎮 |
| 11 | `11-crtp` | CRTP | ★★★★ | 静的ポリモーフィズム、Mixin、deducing this `C++23` |
| 12 | `12-type-erasure` | 型消去 | ★★★★ | `std::function` の仕組み、自作の型消去、Small Buffer Optimization |
| 13 | `13-metaprogramming` | テンプレートメタプログラミング | ★★★★ | 型リスト、型の計算 |
| 14 | `14-name-lookup` | 名前探索 | ★★★★ | 2段階名前探索、ADL、`typename` / `template` キーワード |
| 15 | `15-reflection` | 静的リフレクション | ★★★★ | C++26のリフレクション `予定`、UEのUHTとの比較 🎮 |

**実装課題**：型安全な単位系ライブラリ、`std::function` の自作、コンパイル時文字列ハッシュ

---

## Part 6　設計とイディオム　`p06-design`

読みやすく、変更に強く、チームで扱えるコードを設計します。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-api-design` | API設計とconst正しさ | ★★★☆ | 引数と戻り値の型の選び方、const正しさ、`[[nodiscard]]` |
| 02 | `02-value-vs-reference-semantics` | 値セマンティクスと参照セマンティクス | ★★★☆ | どちらで設計するか、正則型 |
| 03 | `03-pimpl` | PImpl | ★★★☆ | コンパイル依存の分離、ABIの安定化 |
| 04 | `04-nvi` | NVIとテンプレートメソッド | ★★★☆ | 非仮想インターフェース、拡張ポイントの設計 |
| 05 | `05-strong-types` | 強い型 | ★★★☆ | 取り違えを型で防ぐ、ID型・単位型 🎮 |
| 06 | `06-policy-based-design` | ポリシーベース設計 | ★★★★ | テンプレート引数で振る舞いを差し替える |
| 07 | `07-error-handling-strategy` | エラー処理の戦略 | ★★★☆ | 例外・エラーコード・`expected` の使い分け、例外を無効にする現場 🎮 |
| 08 | `08-interfaces-and-di` | インターフェースと依存性注入 | ★★★☆ | 抽象への依存、テスト可能な設計 |
| 09 | `09-callbacks-and-events` | コールバックとイベント | ★★★☆ | オブザーバー、シグナル/スロット、寿命の問題 🎮 |
| 10 | `10-state-machines` | ステートマシン | ★★★☆ | enum・variant・Stateパターンによる実装 🎮 |
| 11 | `11-composition-and-ecs` | コンポジションとECS | ★★★☆ | 継承より合成、コンポーネント指向、ECS入門 🎮 |
| 12 | `12-modules` | モジュール | ★★★☆ | C++20 modules、ヘッダとの違い、現状の対応状況 |
| 13 | `13-header-design` | ヘッダの設計 | ★★★☆ | 公開ヘッダと内部ヘッダ、インクルードの最小化 |
| 14 | `14-coding-standards` | コーディング規約 | ★★★☆ | C++ Core Guidelines、Google、LLVM、Epicの規約の比較 🎮 |

**実装課題**：キャラクターの状態遷移、型安全なイベントシステム、最小構成のECS

---

## Part 7　並行・並列　`p07-concurrency`

マルチコアを安全に、速く使います。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-threads` | スレッドの基本 | ★★★☆ | `std::thread`、`std::jthread`、データ競合 |
| 02 | `02-mutex-and-locks` | ミューテックスとロック | ★★★☆ | `mutex`、`scoped_lock`、`shared_mutex`、デッドロックの回避 |
| 03 | `03-condition-variables` | 条件変数 | ★★★☆ | 待機と通知、spurious wakeup |
| 04 | `04-futures-and-async` | futureとasync | ★★★☆ | `future` / `promise`、`std::async` の注意点 |
| 05 | `05-atomics` | アトミック | ★★★★ | `std::atomic`、CAS、`atomic_ref` |
| 06 | `06-memory-model` | メモリモデル | ★★★★ | happens-before、`memory_order`、acquire/release |
| 07 | `07-lock-free` | ロックフリー | ★★★★ | SPSC/MPMCキュー、ABA問題、ハザードポインタとRCU `予定` |
| 08 | `08-false-sharing` | フォルスシェアリング | ★★★★ | キャッシュコヒーレンス、`hardware_destructive_interference_size` 🎮 |
| 09 | `09-thread-pool` | スレッドプール | ★★★☆ | 設計と実装、タスクキュー |
| 10 | `10-job-system` | ジョブシステムとタスクグラフ | ★★★★ | ワークスティーリング、依存関係の表現、ファイバー 🎮 |
| 11 | `11-parallel-algorithms` | 並列アルゴリズム | ★★★☆ | 実行ポリシー |
| 12 | `12-coroutines` | コルーチン | ★★★★ | `co_await` / `co_yield`、promise型、ジェネレータ `C++23` |
| 13 | `13-std-execution` | std::execution | ★★★★ | sender/receiver `予定` |
| 14 | `14-game-threading` | ゲームのスレッドモデル | ★★★★ | ゲームスレッドとレンダースレッド、フレームのパイプライン化 🎮 |

**実装課題**：SPSCリングバッファ、ワークスティーリング型ジョブシステム

---

## Part 8　メモリとパフォーマンス　`p08-performance`

測って、理解して、速くします。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-performance-mindset` | 性能を考える姿勢 | ★★★☆ | 測ってから直す、フレーム予算（16.6ms / 33.3ms） 🎮 |
| 02 | `02-benchmarking` | ベンチマークの書き方 | ★★★☆ | Google Benchmark、ノイズ対策、最適化による消去の防止 |
| 03 | `03-profiling` | プロファイリング | ★★★☆ | perf、VTune、Tracy、Superluminal、Unreal Insights 🎮 |
| 04 | `04-cpu-architecture` | CPUの仕組み | ★★★★ | パイプライン、アウトオブオーダー実行、分岐予測 |
| 05 | `05-memory-hierarchy` | メモリ階層とキャッシュ | ★★★★ | キャッシュライン、局所性、プリフェッチ、TLB |
| 06 | `06-alignment` | アラインメント | ★★★★ | `alignas` / `alignof`、アラインメント付き確保 |
| 07 | `07-allocation-cost` | 動的確保のコスト | ★★★★ | mallocの内部、断片化、確保を減らす工夫 |
| 08 | `08-custom-allocators` | カスタムアロケータ | ★★★★ | リニア・スタック・プール・フレームアロケータ 🎮 |
| 09 | `09-pmr` | pmr | ★★★★ | `std::pmr`、メモリリソースの差し替え |
| 10 | `10-data-oriented-design` | データ指向設計 | ★★★★ | AoSとSoA、ホット/コールド分割 🎮 |
| 11 | `11-game-containers` | ゲーム向けのコンテナ | ★★★★ | small_vector、slot map、sparse set、リングバッファ 🎮 |
| 12 | `12-branches` | 分岐の最適化 | ★★★★ | 分岐なしコード、`[[likely]]` / `[[unlikely]]` |
| 13 | `13-call-overhead` | 関数呼び出しのコスト | ★★★★ | インライン化、仮想関数呼び出しのコスト、脱仮想化 |
| 14 | `14-compiler-optimizations` | コンパイラの最適化 | ★★★★ | エイリアシング、strict aliasing、LTO、PGO |
| 15 | `15-floating-point` | 浮動小数点 | ★★★★ | IEEE 754、誤差、fast-math、決定論的な計算 🎮 |
| 16 | `16-memory-tracking` | メモリの追跡と予算 | ★★★★ | リーク検出、メモリ予算、確保の計測 🎮 |

**実装課題**：フレームアロケータ、slot map、SoA化したパーティクルシステムとAoS版の比較

---

## Part 9　SIMDと低レイヤ最適化　`p09-simd`

1命令で複数のデータを処理し、ハードウェアの性能を引き出します。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-simd-concepts` | SIMDとは | ★★★★ | レジスタ幅、レーン、SIMDが効く処理・効かない処理 |
| 02 | `02-reading-assembly` | x86-64アセンブリの読み方 | ★★★★ | レジスタ、主要命令、最適化されたコードの読み方 |
| 03 | `03-auto-vectorization` | 自動ベクトル化 | ★★★★ | 成立する条件、阻害要因、最適化レポートの読み方 |
| 04 | `04-sse-avx` | SSE / AVX2 intrinsics | ★★★★ | 型と命令の命名規則、ロード/ストア、算術 |
| 05 | `05-avx512` | AVX-512 | ★★★★ | マスクレジスタ、周波数の問題、使いどころ |
| 06 | `06-neon` | ARM NEON | ★★★★ | x86との違い、モバイルや携帯機での重要性 🎮 |
| 07 | `07-data-layout-for-simd` | SIMDのためのデータ配置 | ★★★★ | SoA、AoSoA、アラインメント 🎮 |
| 08 | `08-masking-and-tails` | マスクと端数処理 | ★★★★ | 条件分岐のベクトル化、ループの端数 |
| 09 | `09-shuffles` | シャッフルと並べ替え | ★★★★ | shuffle / permute / blend、転置 |
| 10 | `10-runtime-dispatch` | 実行時ディスパッチ | ★★★★ | CPUID、関数のマルチバージョン化 |
| 11 | `11-simd-libraries` | SIMDライブラリ | ★★★★ | `std::simd` `予定`、Highway、xsimd |
| 12 | `12-game-math-simd` | ゲーム数学のSIMD化 | ★★★★ | ベクトル・行列・クォータニオン、UEの `VectorRegister` 🎮 |
| 13 | `13-culling-and-collision` | カリングと衝突判定 | ★★★★ | 視錐台カリング、AABB判定のSIMD化 🎮 |
| 14 | `14-case-studies` | 事例研究 | ★★★★ | 画像処理、文字列検索、パーサ（simdjsonの手法） |

**実装課題**：4x4行列積のSIMD化、SIMD視錐台カリング、SIMD画像フィルタ（スカラー版・自動ベクトル化版・intrinsics版の比較）

---

## Part 10　バイナリ解析とセキュリティ　`p10-binary-and-security`

実行ファイルを読み解き、脆弱性を見つけて防ぎます。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-executable-formats` | 実行ファイルの形式 | ★★★★ | ELF / PE、セクション、シンボル、デバッグ情報 |
| 02 | `02-calling-conventions` | 呼び出し規約とスタックフレーム | ★★★★ | System V ABIとWindows x64 ABI、プロローグとエピローグ |
| 03 | `03-disassembly-tools` | 逆アセンブルの道具 | ★★★★ | objdump、Ghidra、x64dbg、WinDbg |
| 04 | `04-cpp-in-binary` | バイナリから見たC++ | ★★★★ | vtable、RTTI、例外テーブル、テンプレートの実体化の痕跡 |
| 05 | `05-memory-safety-bugs` | メモリ安全性の脆弱性 | ★★★★ | バッファオーバーフロー、UAF、二重解放、未初期化、整数オーバーフロー、型の取り違え |
| 06 | `06-attack-concepts` | 攻撃の仕組み（概念） | ★★★★ | スタック破壊、制御フローの乗っ取り、ROPの考え方 |
| 07 | `07-mitigations` | 緩和策 | ★★★★ | スタックカナリア、ASLR、DEP、CFI、CET、`_FORTIFY_SOURCE`、標準ライブラリのハードニング |
| 08 | `08-fuzzing` | ファジング | ★★★★ | libFuzzer、AFL++、Sanitizerとの組み合わせ |
| 09 | `09-secure-coding` | セキュアコーディング | ★★★★ | SEI CERT C++、Core Guidelinesの安全性プロファイル |
| 10 | `10-crash-analysis` | クラッシュ解析 | ★★★★ | ミニダンプ、シンボルサーバ、リリースビルドの不具合調査 🎮 |
| 11 | `11-game-security` | ゲームとセキュリティ | ★★★★ | チートの手口（メモリ改ざん等）の概要、サーバ権威、セーブデータの改ざん対策 🎮 |

**実装課題**：意図的に脆弱なパーサをファジングで壊し、原因を逆アセンブルとSanitizerで特定して修正する

---

## Part 11　大規模開発　`p11-large-scale`

大きなコードベースとチームで、C++を扱います。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-cmake-advanced` | CMake応用 | ★★★☆ | ジェネレータ式、install / export、ツールチェーンファイル |
| 02 | `02-package-management` | パッケージ管理の詳細 | ★★★☆ | vcpkgのカスタムポートとレジストリ、Conanとの比較 |
| 03 | `03-abi` | ABIとバイナリ互換性 | ★★★★ | ABIが壊れる変更、標準ライブラリのABI、互換性の保ち方 |
| 04 | `04-cross-platform` | クロスプラットフォーム | ★★★☆ | OS差の吸収、エンディアン、コンパイラ差 🎮 |
| 05 | `05-shared-libraries-and-plugins` | 共有ライブラリとプラグイン | ★★★★ | DLL / so、シンボルの公開、ホットリロード 🎮 |
| 06 | `06-build-at-scale` | 大規模ビルド | ★★★★ | Ninja、分散ビルド、キャッシュ、UBTの設計思想 🎮 |
| 07 | `07-testing-strategy` | テスト戦略 | ★★★☆ | 単体・結合テスト、gMockによるモック、テスト可能な設計 |
| 08 | `08-ci-and-quality` | CIと品質管理 | ★★★☆ | CIの設計、カバレッジ、静的解析の継続運用 |
| 09 | `09-logging-and-assertions` | ログとアサーション | ★★★☆ | ログ設計、assertの種類と使い分け（UEの `check` / `ensure` との対応） 🎮 |
| 10 | `10-documentation` | ドキュメント | ★★★☆ | Doxygen、コードコメントの書き方 |
| 11 | `11-reading-large-codebases` | 巨大なコードベースの読み方 | ★★★★ | LLVM、Chromium、Abseil、UEのソースの歩き方 🎮 |
| 12 | `12-code-review` | コードレビュー | ★★★☆ | C++特有のレビュー観点 |
| 13 | `13-modernizing-legacy-code` | 古いコードの近代化 | ★★★☆ | 段階的な移行、clang-tidyによる自動修正 |
| 14 | `14-c-and-ffi` | CとのFFI | ★★★☆ | `extern "C"`、C APIの設計、Rustとの連携 🦀 |

**実装課題**：ライブラリをvcpkgのポートとして公開する、ホットリロード可能なプラグイン機構

---

## Part 12　Unreal Engine C++　`p12-unreal-cpp`

UE C++の方言を、標準C++との違いとして理解します。コードは `ue/CompendiumLab/` で検証します。

| # | ディレクトリ | タイトル | レベル | 主な項目 |
|---|---|---|---|---|
| 01 | `01-overview` | UE C++とは | ★★★☆ | 標準C++との違いの全体像、なぜ方言があるのか 🎮 |
| 02 | `02-build-system` | ビルドシステム | ★★★☆ | UBT、`.Build.cs` / `.Target.cs`、モジュール、プラグイン 🎮 |
| 03 | `03-uobject-and-reflection` | UObjectとリフレクション | ★★★☆ | `UCLASS` / `UPROPERTY` / `UFUNCTION`、UHT、`generated.h` 🎮 |
| 04 | `04-garbage-collection` | ガベージコレクション | ★★★☆ | UObjectのGC、`TObjectPtr`、参照の保持 🎮 |
| 05 | `05-smart-pointers` | UEのスマートポインタ | ★★★☆ | `TSharedPtr` / `TUniquePtr` / `TWeakObjectPtr` と標準との比較 🎮 |
| 06 | `06-containers` | UEのコンテナ | ★★★☆ | `TArray` / `TMap` / `TSet` と標準との比較 🎮 |
| 07 | `07-strings` | UEの文字列 | ★★★☆ | `FString` / `FName` / `FText`、`TCHAR` 🎮 |
| 08 | `08-delegates` | デリゲート | ★★★☆ | シングル・マルチキャスト・ダイナミックデリゲート 🎮 |
| 09 | `09-actors-and-components` | ActorとComponent | ★★★☆ | ライフサイクル、Tick、コンポーネント設計 🎮 |
| 10 | `10-gameplay-framework` | ゲームプレイフレームワーク | ★★★☆ | GameMode、PlayerController、Pawn、GameState 🎮 |
| 11 | `11-blueprint-integration` | Blueprintとの連携 | ★★★☆ | Blueprintに公開する設計、C++とBlueprintの役割分担 🎮 |
| 12 | `12-async-and-tasks` | 非同期処理とタスク | ★★★★ | `UE::Tasks`、TaskGraph、スレッドの制約 🎮 |
| 13 | `13-math` | UEの数学ライブラリ | ★★★☆ | `FVector` / `FQuat` / `FTransform`、内部のSIMD 🎮 |
| 14 | `14-memory` | UEのメモリ管理 | ★★★★ | `FMalloc`、LLM（Low Level Memory Tracker） 🎮 |
| 15 | `15-debugging-and-profiling` | デバッグとプロファイリング | ★★★☆ | Unreal Insights、statコマンド、Visual Studioとの連携 🎮 |
| 16 | `16-networking` | ネットワークとレプリケーション | ★★★☆ | レプリケーションの基本、RPC 🎮 |
| 17 | `17-coding-standard` | Epicのコーディング規約 | ★★★☆ | 命名規則、標準ライブラリを使う場面と使わない場面 🎮 |
| 18 | `18-reading-engine-source` | エンジンソースを読む | ★★★★ | ソースの構成、読み進め方、学びどころ 🎮 |

**実装課題**：標準C++で作った最小ECSやジョブシステムを、UEのモジュールとして組み込む

---

## 付録　`appendix`

| # | ディレクトリ | タイトル | 主な項目 |
|---|---|---|---|
| 01 | `01-syntax-cheatsheet` | 文法早見表 | よく使う構文の一覧 |
| 02 | `02-stl-cheatsheet` | 標準ライブラリ早見表 | コンテナ・アルゴリズムの計算量と選び方 |
| 03 | `03-ub-catalog` | 未定義動作カタログ | 代表的なUBと、検出できるツール |
| 04 | `04-version-features` | バージョン別の機能一覧 | C++11〜C++26、コンパイラとUEの対応状況 |
| 05 | `05-glossary` | 用語集 | 日本語と英語の対応、関連する章へのリンク |
| 06 | `06-rust-mapping` | Rust対照表 | 概念・構文・ライブラリの対応表 🦀 |
| 07 | `07-review-checklist` | レビュー観点集 | 寿命・例外安全・性能・並行性のチェックリスト |
| 08 | `08-std-vs-ue` | 標準C++とUEの対応表 | 型・コンテナ・機能の対応表 🎮 |
| 09 | `09-references` | 参考文献 | 書籍、講演、ブログ、規格書 |
