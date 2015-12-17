//===--- NonEffectiveExprCheck.cpp - clang-tidy----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "NonEffectiveExprCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {

void NonEffectiveExprCheck::registerMatchers(MatchFinder *Finder) {
  registerMatchersBoolOperator(Finder, "&&", "left-expression", false,
                               "bool-operator-expression-and-expression",
                               "right-expression");
  registerMatchersBoolOperator(Finder, "||", "left-expression", true,
                               "bool-operator-expression-or-expression",
                               "right-expression");
  registerMatchersBitOperator(Finder, "&", "left-expression", 0,
                              "bit-operator-expression-and-expression",
                              "right-expression");

  Finder->addMatcher(
      binaryOperator(hasOperatorName("&&"),
                     hasLHS(ignoringImpCasts(integerLiteral(equals(0)).bind(
                         "bool-operator-integer-and-expression"))),
                     hasRHS(expr())),
      this);
}

void NonEffectiveExprCheck::registerMatchersBoolOperator(
    MatchFinder *Finder, std::string operatorName, std::string leftExpression,
    bool value, std::string bindString, std::string rightExpression) {
  Finder->addMatcher(
      binaryOperator(
          isExpansionInMainFile(), hasOperatorName(operatorName),
          hasLHS(allOf(expr().bind(leftExpression),
                       cxxBoolLiteral(equals(value)).bind(bindString))),
          hasRHS(expr().bind(rightExpression)),
          unless(hasRHS(hasDescendant(cxxBoolLiteral())))),
      this);
}

void NonEffectiveExprCheck::registerMatchersBitOperator(
    MatchFinder *Finder, std::string operatorName, std::string leftExpression,
    int value, std::string bindString, std::string rightExpression) {
  Finder->addMatcher(
      binaryOperator(
          isExpansionInMainFile(), hasOperatorName(operatorName),
          hasLHS(allOf(expr().bind(leftExpression),
                       integerLiteral(equals(value)).bind(bindString))),
          hasRHS(expr().bind(rightExpression)),
          unless(hasRHS(hasDescendant(integerLiteral())))),
      this);
}

void NonEffectiveExprCheck::boolLiteralCheck(
    std::string NodeString, std::string LeftExpr, std::string RightExpr,
    std::string Error, const MatchFinder::MatchResult &Result) {
  const auto *Literal = Result.Nodes.getNodeAs<CXXBoolLiteralExpr>(NodeString);
  const CXXBoolLiteralExpr *LeftRemoved =
      (Literal &&
       Result.SourceManager->isMacroBodyExpansion(Literal->getLocStart()))
          ? nullptr
          : Literal;
  if (LeftRemoved) {
    diag(LeftRemoved->getLocStart(), Error);
  }
}

void NonEffectiveExprCheck::integerLiteralCheck(
    std::string NodeString, std::string LeftExpr, std::string RightExpr,
    std::string Error, const MatchFinder::MatchResult &Result) {
  const auto *Literal = Result.Nodes.getNodeAs<IntegerLiteral>(NodeString);
  const IntegerLiteral *LeftRemoved =
      (Literal &&
       Result.SourceManager->isMacroBodyExpansion(Literal->getLocStart()))
          ? nullptr
          : Literal;
  if (LeftRemoved) {
    diag(LeftRemoved->getLocStart(), Error);
  }
}

void NonEffectiveExprCheck::check(const MatchFinder::MatchResult &Result) {
  boolLiteralCheck("bool-operator-expression-and-expression", "left-expression",
                   "right-expression", "error: always evaluates to false",
                   Result);
  boolLiteralCheck("bool-operator-expression-or-expression", "left-expression",
                   "right-expression", "error: always evaluates to true",
                   Result);
  integerLiteralCheck("bit-operator-expression-and-expression",
                      "left-expression", "right-expression",
                      "error: always evaluates to 0", Result);

  const auto *Literal3 = Result.Nodes.getNodeAs<IntegerLiteral>(
      "bool-operator-integer-and-expression");
  if (Literal3) {
    diag(Literal3->getLocStart(), "error: always evaluates to false");
  }
}

} // namespace tidy
} // namespace clang
