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
                     hasEitherOperand(hasType(pointsTo(isAnyCharacter()))))
          .bind("charToLiteral"),
      this);

  Finder->addMatcher(
      stmt(binaryOperator(
               hasEitherOperand(ignoringImpCasts(callExpr(callee(
                   functionDecl(anyOf(hasName("strcmp"), hasName("strncmp"),
                                      hasName("memcmp"))))))),
               hasRHS(unless(integerLiteral(equals(0)))),
               hasLHS(unless(integerLiteral(equals(0))))))
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
  if (CharToLiteral)
    diag(CharToLiteral->getOperatorLoc(),
         "char* is compared to a string literal");

  const auto *FunctionToLiteral =
      Result.Nodes.getNodeAs<BinaryOperator>("funcToLiteral");
  if (FunctionToLiteral)
    diag(FunctionToLiteral->getOperatorLoc(),
         "function should be compared only to 0");

  const auto *CompareToNull =
      Result.Nodes.getNodeAs<BinaryOperator>("compareToNull");
  if (CompareToNull)
    diag(CompareToNull->getOperatorLoc(), "comparison to nullptr");
}

} // namespace misc
} // namespace tidy
} // namespace clang

