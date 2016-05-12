//===--- ComparisonMisuseCheck.h - clang-tidy--------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_MISUSE_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_MISUSE_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace misc {

/// This checker reports errors related to the misuse of the comparison operator.
/// It should warn for the following cases:
///   - strcmp,strncmp,memcmp misuse.
///   - char* is compared to a string literal
///   - inequality operator usage for NULL
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc-comparison-misuse.html
class ComparisonMisuseCheck : public ClangTidyCheck {
public:
  ComparisonMisuseCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace misc
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_MISUSE_H
