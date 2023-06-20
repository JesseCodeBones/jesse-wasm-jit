#ifndef __JC_BINARY_IR_READER__
#define __JC_BINARY_IR_READER__

#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "Backend.hpp"
namespace jc {
class Module {};

class BinaryIrReader {
public:
  BinaryIrReader(std::vector<uint8_t> &input_, Module &module_) noexcept
      : input(input_), module(module_), backend() {
  }
  void read();

private:
  uint32_t pos = 0U;
  std::vector<uint8_t> &input;
  Module &module;
  Backend backend;

  void skipHeader() {
    if (pos == 0U) {
      pos += 8U;
    }
  };
  uint8_t readU8() {
    pos++;
    return input[pos - 1];
  }
  void skipN(uint32_t n) {
    pos += n;
  }
  uint32_t readLEB128() {
    uint32_t result = 0;
    uint32_t shift = 0;
    uint8_t byte;
    do {
      byte = readU8();
      result |= (byte & 0x7F) << shift;
      shift += 7;
    } while (byte & 0x80);
    return result;
  }
};
} // namespace jc
#endif