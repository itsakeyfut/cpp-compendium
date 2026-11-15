// unique_ptr はコピーできない（所有者は常に1人）
//
// EXPECT-ERROR(gcc): use of deleted function
// EXPECT-ERROR(clang): call to (implicitly-)?deleted
// EXPECT-ERROR(msvc): C2280

#include <memory>

void copy_unique_ptr() {
    auto a = std::make_unique<int>(42);
    auto b = a; // コピーコンストラクタは delete されている
}
