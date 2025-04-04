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
    using const_iterator = const char*;
    using iterator = const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type npos = static_cast<size_type>(-1);

    constexpr document_view() noexcept
        : data_(nullptr), size_(0), source_start_(nullptr), source_end_(nullptr) {}

    constexpr document_view(const char* str) noexcept
        : data_(str), size_(traits_type::length(str)),
          source_start_(str), source_end_(str + size_) {}

    constexpr document_view(const char* str, size_type len) noexcept
        : data_(str), size_(len), source_start_(str), source_end_(str + len) {}

    constexpr document_view(const std::string& str) noexcept
        : data_(str.c_str()), size_(str.size()),
          source_start_(str.c_str()), source_end_(str.c_str() + str.size()) {}

    constexpr document_view(const char* data, size_type size,
                        const char* source_start, const char* source_end) noexcept
        : data_(data), size_(size),
          source_start_(source_start), source_end_(source_end) {}

    constexpr iterator begin() const noexcept { return data_; }
    constexpr iterator end() const noexcept { return data_ + size_; }
    constexpr const_iterator cbegin() const noexcept { return begin(); }
    constexpr const_iterator cend() const noexcept { return end(); }
    constexpr reverse_iterator rbegin() const noexcept { return std::reverse_iterator(end()); }
    constexpr reverse_iterator rend() const noexcept { return std::reverse_iterator(begin()); }
    constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    constexpr const_reverse_iterator crend() const noexcept { return rend(); }

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
        std::swap(source_start_, other.source_start_);
        std::swap(source_end_, other.source_end_);
    }

    constexpr document_view substr(size_type pos = 0, size_type count = npos) const {
        pos = pos > size_ ? throw std::out_of_range("document_view::substr") : pos;
        // alternative: pos = std::min(pos, size_);
        count = std::min(count, size_ - pos);
        return {data_ + pos, count, source_start_, source_end_};
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

    constexpr size_type find_first_not_of(char ch, size_type pos = 0) const noexcept {
        for (; pos < size_; ++pos) {
            if (!traits_type::eq(data_[pos], ch))
                return pos;
        }
        return npos;
    }

    constexpr size_type find_first_not_of(document_view str, size_type pos = 0) const noexcept {
        for (; pos < size_; ++pos) {
            bool found = false;
            for (size_type i = 0; i < str.size_; ++i) {
                if (traits_type::eq(data_[pos], str.data_[i])) {
                    found = true;
                    break;
                }
            }
            if (!found) return pos;
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

    [[nodiscard]] constexpr bool contains(char ch) const noexcept {
        return find(ch) != npos;
    }

    [[nodiscard]] constexpr bool contains(document_view str) const noexcept {
        return find(str) != npos;
    }

    [[nodiscard]] constexpr bool contains(const char* s) const noexcept {
        return find(document_view(s)) != npos;
    }

    constexpr bool is_same_source(const document_view& other) const noexcept {
        return source_start_ == other.source_start_ &&
               source_end_ == other.source_end_;
    }

    constexpr bool is_subview_of(const document_view& potential_parent) const noexcept {
        return data_ >= potential_parent.data_ &&
               data_ + size_ <= potential_parent.data_ + potential_parent.size_ &&
               is_same_source(potential_parent);
    }

    constexpr std::string to_string() const noexcept {
        return std::string(data_, size_);
    }

    constexpr std::string_view to_string_view() const noexcept {
        return std::string_view(data_, size_);
    }

    template <typename Sink>
    friend void AbslStringify(Sink& sink, const document_view& p) {
        sink.append(p.data_, p.size_);
    }

private:
    const char* data_;
    size_type size_;
    // the following pointers could be controlled by NDEBUG
    const char* source_start_;
    const char* source_end_;
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
