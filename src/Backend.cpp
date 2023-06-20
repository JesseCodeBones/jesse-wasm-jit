#include "Backend.hpp"
#include <cstdint>
#include <memory>
#include "ExecutableInstruction.hpp"

using namespace jc;

void Backend::I32Const(uint32_t value) {
  functionBodies.back().push_back(std::make_shared<I32_Const>(value, runningStack));
}

void Backend::I32Add() {
  functionBodies.back().push_back(std::make_shared<I32_Add>(runningStack));
}

void Backend::Ins_Drop() {
  functionBodies.back().push_back(std::make_shared<Drop>(runningStack));
}
