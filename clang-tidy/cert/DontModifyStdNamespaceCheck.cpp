//===--- DontModifyStdNamespaceCheck.cpp - clang-tidy----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "DontModifyStdNamespaceCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace cert {

void DontModifyStdNamespaceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      namespaceDecl(allOf(unless(isExpansionInSystemHeader()), hasName("std")))
          .bind("std"),
      this);
}

void DontModifyStdNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<NamespaceDecl>("std");
  diag(MatchedDecl->getLocation(),
       "Modification of std namespace can give unexpected result");
}

} // namespace cert
} // namespace tidy
} // namespace clang

