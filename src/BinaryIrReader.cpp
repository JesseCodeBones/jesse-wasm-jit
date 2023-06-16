#include "./BinaryIrReader.hpp"
#include <cstdint>
#include <iostream>
using namespace jc;

void BinaryIrReader::read() {
  skipHeader();
  while (pos <= (input.size() - 1)) {
    uint8_t sectionCode = readU8();
    switch (sectionCode) {
    case 01U: // type section
    {
      uint32_t size = readLEB128<uint32_t>();
      skipN(size);
      break;
    }
    case 03U: // function section
    {
      uint32_t size = readLEB128<uint32_t>();
      skipN(size);
      break;
    }
    case 07U: // export section
    {
      uint32_t size = readLEB128<uint32_t>();
      skipN(size);
      break;
    }
    case 10U: // data section
    {
      uint32_t codeSize = readLEB128<uint32_t>();
      uint32_t functionIndex = readLEB128<uint32_t>();
      uint32_t functionSize = readLEB128<uint32_t>();
      uint32_t functionStartPos = pos;
      uint32_t localSize = readLEB128<uint32_t>();
      skipN(localSize);
      while (pos < functionSize + functionStartPos) {
        // read instruction
        uint8_t opCode = readU8();
        switch (opCode) {
        case 0x41: // i32.const
        {
          uint32_t value = readLEB128<uint32_t>();
          std::cout << "i32.const=" << value << std::endl;
          break;
        }
        case 0x6A: {
          std::cout << "i32.add" << std::endl;
          break;
        }
        case 0x1a: {
          std::cout << "drop" << std::endl;
          break;
        }
        case 0x0b: {
          std::cout << "end" << std::endl;
          break;
        }
        default: {
          std::cout << "find unkown instruction" << std::endl;
          break;
        }
        }
      }
      break;
    }
    }
  }

  std::cout << "read file finished\n";
}
