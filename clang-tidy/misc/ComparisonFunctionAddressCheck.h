//===--- ComparisonFunctionAddressCheck.h - clang-tidy-----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_FUNCTION_ADDRESS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_FUNCTION_ADDRESS_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace misc {

/// This Checker gives a warning if address of a function is compared.
/// For example: the programmer wants to write getc()==0 but writes getc==0
///
/// as a general rule, function pointers can be compared to other function
/// pointers, function, 0, nullptr
/// functions can be compared only against function pointers
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc-Comparison-Function-Address.html
class ComparisonFunctionAddressCheck : public ClangTidyCheck {
public:
  ComparisonFunctionAddressCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace misc
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_COMPARISON_FUNCTION_ADDRESS_H

