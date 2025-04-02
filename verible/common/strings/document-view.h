//
// Created by gianluca on 01/04/2025.
//

#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>

namespace verible {

class document_view {
public:
    using traits_type = std::char_traits<char>;
    using size_type = std::size_t;
    static constexpr size_type npos = static_cast<size_type>(-1);

    constexpr document_view() noexcept : data_(nullptr), size_(0) {}

    constexpr document_view(const char* str) noexcept
        : data_(str), size_(traits_type::length(str)) {}

    constexpr document_view(const char* str, size_type len) noexcept
        : data_(str), size_(len) {}

    constexpr document_view(const std::string& str) noexcept
        : data_(str.c_str()), size_(str.size()) {}

    constexpr const char* begin() const noexcept { return data_; }
    constexpr const char* end() const noexcept { return data_ + size_; }
    constexpr const char* cbegin() const noexcept { return data_; }
    constexpr const char* cend() const noexcept { return data_ + size_; }

    constexpr size_type size() const noexcept { return size_; }
    constexpr size_type length() const noexcept { return size_; }
    constexpr bool empty() const noexcept { return size_ == 0; }
    constexpr size_type max_size() const noexcept { return npos - 1; }

    constexpr char operator[](size_type pos) const noexcept {
        return data_[pos];
    }

    constexpr char at(size_type pos) const {
        return pos < size_ ? data_[pos] : throw std::out_of_range("document_view::at");
    }

    constexpr char front() const noexcept { return data_[0]; }
    constexpr char back() const noexcept { return data_[size_ - 1]; }
    constexpr const char* data() const noexcept { return data_; }

    constexpr void remove_prefix(size_type n) noexcept {
        data_ += n;
        size_ -= n;
    }

    constexpr void remove_suffix(size_type n) noexcept {
        size_ -= n;
    }

    constexpr void swap(document_view& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    constexpr document_view substr(size_type pos = 0, size_type count = npos) const {
        pos = pos > size_ ? throw std::out_of_range("document_view::substr") : pos;
        count = std::min(count, size_ - pos);
        return {data_ + pos, count};
    }

    constexpr int compare(document_view other) const noexcept {
        const size_type rlen = std::min(size_, other.size_);
        for (size_type i = 0; i < rlen; ++i) {
            if (const int cmp = traits_type::compare(data_ + i, other.data_ + i, 1))
                return cmp;
        }
        return size_ == other.size_ ? 0 : (size_ < other.size_ ? -1 : 1);
    }

    constexpr size_type find(char ch, size_type pos = 0) const noexcept {
        for (; pos < size_; ++pos) {
            if (traits_type::eq(data_[pos], ch)) return pos;
        }
        return npos;
    }

    constexpr size_type find(document_view str, size_type pos = 0) const noexcept {
        if (str.empty()) return pos <= size_ ? pos : npos;
        if (size_ - pos < str.size_) return npos;
        for (; pos <= size_ - str.size_; ++pos) {
            if (traits_type::compare(data_ + pos, str.data_, str.size_) == 0)
                return pos;
        }
        return npos;
    }

    constexpr bool starts_with(document_view str) const noexcept {
        return size_ >= str.size_
            && traits_type::compare(data_, str.data_, str.size_) == 0;
    }

    constexpr bool ends_with(document_view str) const noexcept {
        return size_ >= str.size_
            && traits_type::compare(data_ + size_ - str.size_, str.data_, str.size_) == 0;
    }

private:
    const char* data_;
    size_type size_;
};

constexpr bool operator==(document_view lhs, document_view rhs) noexcept {
    return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

constexpr bool operator!=(document_view lhs, document_view rhs) noexcept {
    return !(lhs == rhs);
}

constexpr bool operator<(document_view lhs, document_view rhs) noexcept {
  return lhs.compare(rhs) < 0;
}

inline std::ostream& operator<<(std::ostream& os, const document_view& str) noexcept {
  os << std::string_view(str.data(), str.size());
  return os;
}

}

template<> struct std::hash<verible::document_view> {
  size_t operator()(const verible::document_view& dv) const noexcept {
    return std::hash<std::string_view>{}(std::string_view(dv.data(), dv.size()));
  }
};
