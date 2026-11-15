// 自作のムーブ専用型 Buffer もコピーできない
//
// EXPECT-ERROR(gcc): use of deleted function
// EXPECT-ERROR(clang): call to (implicitly-)?deleted
// EXPECT-ERROR(msvc): C2280

#include "../examples/buffer.hpp"

void copy_buffer() {
    Buffer a(16);
    Buffer b = a; // Buffer(const Buffer&) = delete
}
