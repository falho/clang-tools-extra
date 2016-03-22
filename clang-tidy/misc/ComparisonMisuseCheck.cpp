//===--- ComparisonMisuseCheck.cpp - clang-tidy----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ComparisonMisuseCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ComparisonMisuseCheck::registerMatchers(MatchFinder *Finder) {

  Finder->addMatcher(
      binaryOperator(hasEitherOperand(ignoringImpCasts(stringLiteral())),
                     hasEitherOperand(ignoringImpCasts(
                         declRefExpr(hasType(asString("const char *"))))))
          .bind("charToLiteral"),
      this);

  Finder->addMatcher(
      binaryOperator(
          hasEitherOperand(ignoringImpCasts(callExpr(callee(functionDecl(anyOf(
              hasName("strcmp"), hasName("strncmp"), hasName("memcmp"))))))),
          hasEitherOperand(ignoringImpCasts(integerLiteral(unless(equals(0))))))
          .bind("funcToLiteral"),
      this);

  Finder->addMatcher(
      binaryOperator(
          unless(anyOf(hasOperatorName("=="), hasOperatorName("!="))),
          hasEitherOperand(ignoringImpCasts(gnuNullExpr())))
          .bind("compareToNull"),
      this);
}

void ComparisonMisuseCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *CharToLiteral =
      Result.Nodes.getNodeAs<BinaryOperator>("charToLiteral");
  if (CharToLiteral != NULL) {
    diag(CharToLiteral->getOperatorLoc(),
         "char* is compared to a string literal");
  }

  const auto *FunctionToLiteral =
      Result.Nodes.getNodeAs<BinaryOperator>("funcToLiteral");
  if (FunctionToLiteral != NULL) {
    diag(FunctionToLiteral->getOperatorLoc(),
         "function is compared to literal different than 0");
  }

  const auto *CompareToNull =
      Result.Nodes.getNodeAs<BinaryOperator>("compareToNull");
  if (CompareToNull != NULL) {
    diag(CompareToNull->getOperatorLoc(), "comparison to NULL");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
