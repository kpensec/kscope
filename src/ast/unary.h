#ifndef __UNARY_H_INCLUDED__
#define __UNARY_H_INCLUDED__

#include "llvm/IR/Value.h"

#include "node.h"

class UnaryNode : public ASTNode {
  char opcode;
  ASTNode *operand;

public:
  UnaryNode(char opcode, ASTNode *operand);
  virtual llvm::Value *codegen();
};

#endif