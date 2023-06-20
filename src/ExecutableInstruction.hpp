#ifndef __JC_EXECUTABLE_INSTRUCTION__
#define __JC_EXECUTABLE_INSTRUCTION__
#include <cstdint>
#include <stack>
class ExecutableInstruction {
public:
  virtual void execute() = 0;
};

class I32_Const : public ExecutableInstruction {
public:
  I32_Const(uint32_t value, std::stack<uint64_t> &stack) noexcept : _value(value), _stack(stack) {
  }
  virtual void execute() override {
    _stack.push(static_cast<uint64_t>(_value));
  }

private:
  uint32_t _value;
  std::stack<uint64_t> &_stack;
};

class I32_Add : public ExecutableInstruction {
public:
  I32_Add(std::stack<uint64_t> &stack) noexcept : _stack(stack) {
  }
  virtual void execute() override {
    uint64_t operand1 = _stack.top();
    _stack.pop();
    uint64_t operand2 = _stack.top();
    _stack.pop();
    uint32_t result = static_cast<uint32_t>(operand1 + operand2);
    _stack.push(static_cast<uint64_t>(result));
  }

private:
  std::stack<uint64_t> &_stack;
};

class Drop : public ExecutableInstruction {
public:
  Drop(std::stack<uint64_t> &stack) noexcept : _stack(stack) {
  }
  virtual void execute() override {
    _stack.pop();
  }

private:
  std::stack<uint64_t> &_stack;
};

class End : public ExecutableInstruction {
public:
  End() noexcept {
  }
  virtual void execute() override {
  }
};

#endif