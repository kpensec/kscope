#pragma once

#include <memory>
#include <iostream>


struct ASTNode;
struct FunctionNode;
struct PrototypeNode;


class ASTree {
    ASTree(ASTree &&other);
    ASTree &operator =(ASTree other);

public:
  ASTree();
  ~ASTree();

  std::unique_ptr<ASTNode> root;

  void parse(std::istream &input);

  void set_root(FunctionNode *node);
  void set_root(PrototypeNode *node);
};