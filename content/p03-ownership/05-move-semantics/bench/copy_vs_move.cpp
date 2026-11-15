// コピーとムーブのコスト比較
//
// 64文字の std::string を N 個持つ vector を、コピーした場合とムーブした場合で比べる。
// コピーは要素数に比例して遅くなり、ムーブは要素数に関係なくほぼ一定になる。
//
// 実行例:
//   cmake --build --preset msvc-release --target p03_05_bench_copy_vs_move
//   .\build\msvc-release\bin\p03_05_bench_copy_vs_move.exe

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

namespace {

std::vector<std::string> make_strings(std::size_t count) {
    return std::vector<std::string>(count, std::string(64, 'x'));
}

void BM_Copy(benchmark::State& state) {
    const auto source = make_strings(static_cast<std::size_t>(state.range(0)));
    for (auto _ : state) {
        auto copied = source; // 全要素の文字列を複製する
        benchmark::DoNotOptimize(copied.data());
    }
}

void BM_Move(benchmark::State& state) {
    auto source = make_strings(static_cast<std::size_t>(state.range(0)));
    for (auto _ : state) {
        auto moved = std::move(source); // バッファの所有権を移すだけ
        benchmark::DoNotOptimize(moved.data());
        source = std::move(moved); // 次の反復のために戻す（これもムーブ）
    }
}

} // namespace

BENCHMARK(BM_Copy)->RangeMultiplier(10)->Range(10, 100'000);
BENCHMARK(BM_Move)->RangeMultiplier(10)->Range(10, 100'000);
