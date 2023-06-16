#include "Backend.hpp"
#include <cstdint>

using namespace jc;

void Backend::I32Const(uint32_t value) {
  runningStack.push(static_cast<uint64_t>(value));
}

void Backend::I32Add() {
  uint64_t operand1 = runningStack.top();
  runningStack.pop();
  uint64_t operand2 = runningStack.top();
  runningStack.pop();
  uint32_t result = static_cast<uint32_t>(operand1 + operand2);
  runningStack.push(static_cast<uint64_t>(result));
}

void Backend::Drop(){
  runningStack.pop();
}
