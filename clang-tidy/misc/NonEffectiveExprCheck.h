//===--- NonEffectiveExprCheck.h - clang-tidy--------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NON_EFFECTIVE_EXPR_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NON_EFFECTIVE_EXPR_H

#include "../ClangTidy.h"
#include <iostream>

namespace clang {
namespace tidy {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc-non-effective-expr.html
class NonEffectiveExprCheck : public ClangTidyCheck {
private:
  void boolLiteralCheck(std::string NodeString, std::string LeftExpr,
                        std::string RightExpr, std::string Error,
                        const ast_matchers::MatchFinder::MatchResult &Result);
  void
  integerLiteralCheck(std::string NodeString, std::string LeftExpr,
                      std::string RightExpr, std::string Error,
                      const ast_matchers::MatchFinder::MatchResult &Result);
  void registerMatchersBoolOperator(ast_matchers::MatchFinder *Finder,
                                    std::string operatorName,
                                    std::string leftExpression, bool value,
                                    std::string bindString,
                                    std::string rightExpression);
  void registerMatchersBitOperator(ast_matchers::MatchFinder *Finder,
                                   std::string operatorName,
                                   std::string leftExpression, int value,
                                   std::string bindString,
                                   std::string rightExpression);

public:
  NonEffectiveExprCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NON_EFFECTIVE_EXPR_H
