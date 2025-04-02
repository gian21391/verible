// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Unit tests for RebaseDocumentView

#include "verible/common/strings/rebase.h"

#include <string>

#include "gtest/gtest.h"
#include "verible/common/util/range.h"

namespace verible {
namespace {

// Test that empty string token rebases correctly.
TEST(RebaseDocumentViewTest, EmptyStringsZeroOffset) {
  const std::string text;
  // We want another empty string, but we need to trick too smart compilers
  // to give us a different memory address.
  std::string substr = "foo";
  substr.resize(0);  // Force empty string such as 'text' but memory space
  ASSERT_NE(text.c_str(), substr.c_str()) << "Mismatch in memory assumption";

  document_view text_view(text);
  const document_view substr_view(substr);
  EXPECT_FALSE(BoundsEqual(text_view, substr_view));
  RebaseDocumentView(&text_view, substr);
  EXPECT_TRUE(BoundsEqual(text_view, substr_view));
}

// Test that non-empty whole-string copy rebases correctly.
TEST(RebaseDocumentViewTest, IdenticalCopy) {
  const std::string text = "hello";
  const std::string substr = "hello";  // different memory space
  document_view text_view(text);
  const document_view substr_view(substr);
  EXPECT_FALSE(BoundsEqual(text_view, substr_view));
  RebaseDocumentView(&text_view, substr);
  EXPECT_TRUE(BoundsEqual(text_view, substr_view));
}

// Test that substring mismatch between new and old is checked.
TEST(RebaseDocumentViewDeathTest, SubstringMismatch) {
  const document_view text = "hell0";
  const document_view substr = "hello";
  document_view text_view(text);
  EXPECT_DEATH(RebaseDocumentView(&text_view, substr),
               "only valid when the new text referenced matches the old text");
}

TEST(RebaseDocumentViewDeathTest, SubstringMismatch2) {
  const document_view text = "hello";
  const document_view substr = "Hello";
  document_view text_view(text);
  EXPECT_DEATH(RebaseDocumentView(&text_view, substr),
               "only valid when the new text referenced matches the old text");
}

// Test that substring in the middle of old string is rebased correctly.
TEST(RebaseDocumentViewTest, NewSubstringNotAtFront) {
  const document_view text = "hello";
  const document_view new_base = "xxxhelloyyy";
  const document_view new_view(new_base.substr(3, 5));
  document_view text_view(text);
  EXPECT_FALSE(BoundsEqual(text_view, new_view));
  RebaseDocumentView(&text_view, new_view);
  EXPECT_TRUE(BoundsEqual(text_view, new_view));
}

// Test that substring in the middle of old string is rebased correctly.
TEST(RebaseDocumentViewTest, UsingCharPointer) {
  const document_view text = "hello";
  const char *new_base = "xxxhelloyyy";
  const char *new_view_offset = new_base + 3;
  document_view text_view(text);
  RebaseDocumentView(&text_view, new_view_offset);  // assume original length
  const document_view new_base_view(new_base);
  EXPECT_TRUE(BoundsEqual(text_view, new_base_view.substr(3, 5)));
}

// Test integration with substr() function rebases correctly.
TEST(RebaseDocumentViewTest, RelativeToOldBase) {
  const document_view full_text = "xxxxxxhelloyyyyy";
  document_view substr = full_text.substr(6, 5);
  EXPECT_EQ(substr, "hello");
  const document_view new_base = "aahellobbb";
  const document_view new_view(new_base.substr(2, substr.length()));
  RebaseDocumentView(&substr, new_view);
  EXPECT_TRUE(BoundsEqual(substr, new_view));
}

// Test rebasing into middle of superstring.
TEST(RebaseDocumentViewTest, MiddleOfSuperstring) {
  const document_view dest_text = "xxxxxxhell0yyyyy";
  const document_view src_text = "ccchell0ddd";
  const int dest_offset = 6;
  document_view src_substr(src_text.substr(3, 5));
  EXPECT_EQ(src_substr, "hell0");
  // src_text[3] lines up with dest_text[6].
  const document_view dest_view(
      dest_text.substr(dest_offset, src_substr.length()));
  RebaseDocumentView(&src_substr, dest_view);
  EXPECT_TRUE(BoundsEqual(src_substr, dest_view));
}

// Test rebasing into prefix superstring.
TEST(RebaseDocumentViewTest, PrefixSuperstring) {
  const document_view dest_text = "xxxhell0yyyyyzzzzzzz";
  const document_view src_text = "ccchell0ddd";
  const int dest_offset = 3;
  document_view src_substr = src_text.substr(3, 5);
  EXPECT_EQ(src_substr, "hell0");
  // src_text[3] lines up with dest_text[3].
  const document_view dest_view(
      dest_text.substr(dest_offset, src_substr.length()));
  RebaseDocumentView(&src_substr, dest_view);
  EXPECT_TRUE(BoundsEqual(src_substr, dest_view));
}

}  // namespace
}  // namespace verible
