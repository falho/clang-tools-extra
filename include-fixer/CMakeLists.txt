set(LLVM_LINK_COMPONENTS
  support
  )

add_clang_library(clangIncludeFixer
  IncludeFixer.cpp
  InMemoryXrefsDB.cpp

  LINK_LIBS
  clangAST
  clangBasic
  clangFrontend
  clangLex
  clangParse
  clangSema
  clangTooling
  clangToolingCore
  )

add_subdirectory(tool)
