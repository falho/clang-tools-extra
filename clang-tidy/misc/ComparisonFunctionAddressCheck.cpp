//===--- ComparisonFunctionAddressCheck.cpp - clang-tidy-------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ComparisonFunctionAddressCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ComparisonFunctionAddressCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      binaryOperator(
          hasEitherOperand(hasType(pointerType(pointee(functionType())))),
          unless(hasEitherOperand(ignoringImpCasts(
              declRefExpr(hasDeclaration(varDecl(hasType(pointerType()))))))))
          .bind("funcAdd"),
      this);
}

void ComparisonFunctionAddressCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<BinaryOperator>("funcAdd");
  diag(MatchedDecl->getOperatorLoc(), "Address of function is compared");
}

} // namespace misc
} // namespace tidy
} // namespace clang

