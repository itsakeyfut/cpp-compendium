#pragma once

// ムーブ専用の型を自作する例
//
// ヒープ上の配列を所有するクラス。コピーは禁止し、ムーブだけを許可する。
// 実務では std::unique_ptr<int[]> や std::vector<int> をメンバに持てば
// 特殊メンバ関数を書かずに済む（Rule of Zero）。ここでは仕組みを学ぶために手で書く。

#include <cstddef>
#include <utility>

// ANCHOR: buffer
class Buffer {
public:
    explicit Buffer(std::size_t size) : size_(size), data_(new int[size]{}) {}

    ~Buffer() { delete[] data_; }

    // コピーは禁止する（所有権を1人に保つ）
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    // ムーブコンストラクタ：相手の中身を奪い、相手を空にする
    Buffer(Buffer&& other) noexcept
        : size_(std::exchange(other.size_, 0)), data_(std::exchange(other.data_, nullptr)) {}

    // ムーブ代入演算子：自分の中身を解放してから相手の中身を奪う
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) { // 自己ムーブ代入への備え
            delete[] data_;
            size_ = std::exchange(other.size_, 0);
            data_ = std::exchange(other.data_, nullptr);
        }
        return *this;
    }

    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] const int* data() const noexcept { return data_; }

private:
    std::size_t size_;
    int* data_;
};
// ANCHOR_END: buffer
