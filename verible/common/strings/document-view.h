//
// Created by gianluca on 01/04/2025.
//

#pragma once

#include <absl/strings/str_split.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

namespace verible {

class document_view_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = std::ptrdiff_t;
    using pointer = const char*;
    using reference = const char&;

    constexpr document_view_iterator() noexcept = default;

    constexpr document_view_iterator(pointer current,
                                     pointer source_start,
                                     pointer source_end) noexcept
        : current_(current),
          source_start_(source_start),
          source_end_(source_end) {}

    constexpr reference operator*() const noexcept {
        return *current_;
    }

    constexpr document_view_iterator& operator++() noexcept {
        ++current_;
        return *this;
    }

    constexpr document_view_iterator operator++(int) noexcept {
        auto tmp = *this;
        ++current_;
        return tmp;
    }

    constexpr document_view_iterator& operator--() noexcept {
        --current_;
        return *this;
    }

    constexpr document_view_iterator operator--(int) noexcept {
        auto tmp = *this;
        --current_;
        return tmp;
    }

    constexpr document_view_iterator& operator+=(difference_type n) noexcept {
        current_ += n;
        return *this;
    }

    constexpr document_view_iterator operator+(difference_type n) const noexcept {
        return {current_ + n, source_start_, source_end_};
    }

    constexpr document_view_iterator& operator-=(difference_type n) noexcept {
        current_ -= n;
        return *this;
    }

    constexpr document_view_iterator operator-(difference_type n) const noexcept {
        return {current_ - n, source_start_, source_end_};
    }

    constexpr difference_type operator-(const document_view_iterator& other) const {
        validate_source(other);
        return current_ - other.current_;
    }

    constexpr bool operator==(const document_view_iterator& other) const {
        validate_source(other);
        return current_ == other.current_;
    }

    constexpr bool operator!=(const document_view_iterator& other) const {
        return !(*this == other);
    }

    constexpr bool operator<(const document_view_iterator& other) const {
        validate_source(other);
        return current_ < other.current_;
    }

    constexpr bool operator<=(const document_view_iterator& other) const {
        validate_source(other);
        return current_ <= other.current_;
    }

    constexpr bool operator>(const document_view_iterator& other) const {
        validate_source(other);
        return current_ > other.current_;
    }

    constexpr bool operator>=(const document_view_iterator& other) const {
        validate_source(other);
        return current_ >= other.current_;
    }

private:
    pointer current_ = nullptr;
    pointer source_start_ = nullptr;
    pointer source_end_ = nullptr;

    constexpr void validate_source(const document_view_iterator& other) const {
        // optionally a no-op controlled by NDEBUG
        if (source_start_ != other.source_start_ || source_end_ != other.source_end_) {
            // std::cout << "Iterator comparison between different source documents" << std::endl;
            // throw std::logic_error("Iterator comparison between different source documents");
        }
    }
};

constexpr document_view_iterator operator+(document_view_iterator::difference_type n,
                                          const document_view_iterator& it) noexcept {
    return it + n;
}

class document_view {
public:
    using traits_type = std::char_traits<char>;
    using size_type = std::size_t;
    static constexpr size_type npos = static_cast<size_type>(-1);
    using iterator = document_view_iterator;
    using const_iterator = iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using value_type = traits_type::char_type;
    using reference = value_type&;
    using const_reference = const value_type&;

    constexpr document_view() noexcept = default;

    constexpr document_view(const char* str) noexcept
        : data_(str),
          size_(traits_type::length(str)),
          source_start_(str),
          source_end_(str + size_) {}

    constexpr document_view(const std::string& str) noexcept
        : data_(str.c_str()),
          size_(str.size()),
          source_start_(str.c_str()),
          source_end_(str.c_str() + str.size()) {}

    constexpr document_view(const char* data,
                            size_type size,
                            const char* source_start,
                            const char* source_end) noexcept
        : data_(data),
          size_(size),
          source_start_(source_start),
          source_end_(source_end) {}

    constexpr document_view(const char* data,
                            size_type size) noexcept
    : data_(data),
      size_(size),
      source_start_(data),
      source_end_(data + size) {}

    constexpr document_view(const char* data,
                        size_type size,
                        document_view copy_source_of) noexcept
        : data_(data),
          size_(size),
          source_start_(copy_source_of.source_start_),
          source_end_(copy_source_of.source_end_) {}

    constexpr iterator begin() const noexcept { return {data_, source_start_, source_end_}; }
    constexpr iterator end() const noexcept { return {data_ + size_, source_start_, source_end_}; }
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

    constexpr bool consume_prefix(document_view str) noexcept {
        if (!starts_with(str)) return false;
        remove_prefix(str.size());
        return true;
    }

    constexpr void remove_suffix(size_type n) noexcept {
        size_ -= n;
    }

    constexpr bool consume_suffix(document_view str) noexcept {
        if (!ends_with(str)) return false;
        remove_suffix(str.size());
        return true;
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

    constexpr void set_source_of(const document_view& str) noexcept {
        source_start_ = str.source_start_;
        source_end_ = str.source_end_;
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

    template <typename Delimiter>
    constexpr std::vector<document_view> str_split(Delimiter delimiter) const noexcept {
        std::vector<std::string_view> result = absl::StrSplit(to_string_view(), delimiter);
        std::vector<document_view> lines(result.size());
        std::transform(result.begin(), result.end(), lines.begin(),
            [source_start = source_start_, source_end = source_end_](std::string_view line) {
                return document_view(line.data(), line.size(), source_start, source_end);
            });
        return lines;
    }

    template <typename Delimiter, typename Predicate>
    std::vector<document_view> str_split(Delimiter delimiter, Predicate predicate) const {
        std::vector<std::string_view> result = absl::StrSplit(to_string_view(), delimiter, predicate);
        std::vector<document_view> lines(result.size());
        std::transform(result.begin(), result.end(), lines.begin(),
            [source_start = source_start_, source_end = source_end_](std::string_view line) {
                return document_view(line.data(), line.size(), source_start, source_end);
            });
        return lines;
    }

    template <typename Sink>
    friend void AbslStringify(Sink& sink, const document_view& p) {
        sink.Append(std::string_view(p.data_, p.size_));
    }

private:
    const char* data_ = nullptr;
    size_type size_ = 0;
    // the following pointers could be controlled by NDEBUG
    const char* source_start_ = nullptr;
    const char* source_end_ = nullptr;
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
