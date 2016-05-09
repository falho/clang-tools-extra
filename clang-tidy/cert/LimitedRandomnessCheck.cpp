//===--- LimitedRandomnessCheck.cpp - clang-tidy---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LimitedRandomnessCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace cert {

void LimitedRandomnessCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      declRefExpr(hasDeclaration(functionDecl(namedDecl(hasName("::rand")),
                                              parameterCountIs(0))))
          .bind("randomGenerator"),
      this);
}

void LimitedRandomnessCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl =
      Result.Nodes.getNodeAs<DeclRefExpr>("randomGenerator");
  diag(MatchedDecl->getLocation(), "rand() function has limited randomness, "
                                   "use C++11 random library instead");
}

} // namespace cert
} // namespace tidy
} // namespace clang
