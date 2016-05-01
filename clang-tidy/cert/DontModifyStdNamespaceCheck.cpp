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
      namespaceDecl(unless(isExpansionInSystemHeader()), anyOf(hasName("std"), hasName("posix")))
          .bind("nmspc"),
      this);
}

void DontModifyStdNamespaceCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Nmspc = Result.Nodes.getNodeAs<NamespaceDecl>("nmspc");
 
  std::string namespaceName = Nmspc->getName();
 
  diag(Nmspc->getLocation(),
       "Modification of " + namespaceName +" namespace can result to undefined behavior");
}

} // namespace cert
} // namespace tidy
} // namespace clang

