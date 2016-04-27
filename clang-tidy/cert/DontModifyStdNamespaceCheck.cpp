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

  Finder->addMatcher(namespaceDecl(allOf(unless(isExpansionInSystemHeader()),
                                         hasName("posix")))
                         .bind("posix"),
                     this);
}

void DontModifyStdNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Std = Result.Nodes.getNodeAs<NamespaceDecl>("std");
  const auto *Posix = Result.Nodes.getNodeAs<NamespaceDecl>("posix");

  if (Std != nullptr)
    diag(Std->getLocation(),
         "Modification of std namespace can result to undefined behavior");

  if (Posix != nullptr)
    diag(Posix->getLocation(),
         "Modification of posix namespace can result to undefined behavior");
}

} // namespace cert
} // namespace tidy
} // namespace clang

