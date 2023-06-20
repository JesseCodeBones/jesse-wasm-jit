#ifndef __JC_BACKEND__
#define __JC_BACKEND__
#include <cstdint>
#include <memory>
#include <stack>
#include <vector>
#include "ExecutableInstruction.hpp"
namespace jc {

struct GlobalItem {
  bool isMutable;
  uint32_t index;
  union {
    uint32_t intValue;
    uint64_t longValue;
  } data;
};
class Backend {
public:
  void acquireNewFunction() {
    functionBodies.push_back(std::vector<std::shared_ptr<ExecutableInstruction>>());
  }
  void I32Const(uint32_t value);
  void I32Add();
  void Ins_Drop();
  std::vector<std::vector<uint8_t>> memory;
  std::vector<GlobalItem> globals;
  std::vector<uint32_t> functions;

private:
  std::stack<uint64_t> runningStack;
  std::vector<std::vector<std::shared_ptr<ExecutableInstruction>>> functionBodies;
};
} // namespace jc
#endif