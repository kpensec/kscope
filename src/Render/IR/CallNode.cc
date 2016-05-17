#include "IRRenderer.h"

#include "kscope/AST/CallNode.h"
#include "kscope/Errors/Error.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"

#include <vector>


llvm::Value *
IRRenderer::visit_node(CallNode *node) {
  auto &context = get_render_context();
  auto &module = context.get_module();
  auto &builder = context.get_builder();

  auto callee_func = module.getFunction(node->callee);

  if ( callee_func == nullptr ) {
    auto callee = get_prototype(node->callee);
    if ( callee == nullptr ) {
      return Error<llvm::Value>::handle("Unknown function referenced");
    }
    callee_func = static_cast<llvm::Function*>(visit(callee));
  }

  if ( callee_func->arg_size() != node->args.size() ) {
    return Error<llvm::Value>::handle("Incorrect number of arguments passed");
  }

  std::vector<llvm::Value*> arg_values;
  for ( auto &arg : node->args ) {
    arg_values.push_back(visit(arg));
    if ( arg_values.back() == 0 ) { return nullptr; }
  }

  return builder.CreateCall(callee_func, arg_values);
}