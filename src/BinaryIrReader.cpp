#include "./BinaryIrReader.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "WasmBinary.hpp"
using namespace jc;

#define WASM_MEMORY_ONE_PAGE_SIZE (1 << 16)

void BinaryIrReader::read() {
  skipHeader();
  while (pos <= (input.size() - 1)) {
    uint8_t sectionCode = readU8();
    switch (sectionCode) {
    case SectionCode::Type: // type section
    {
      uint32_t size = readLEB128();
      skipN(size);
      break;
    }
    case SectionCode::Function: // function section
    {
      uint32_t size = readLEB128();
      uint32_t functionSize = readLEB128();
      while (functionSize > 0) {
        functionSize--;
        uint32_t typeID = readLEB128();
        backend.functions.push_back(typeID);
      }
      break;
    }
    case SectionCode::Memory: { // memory section
      uint32_t size = readLEB128();
      uint32_t oldPos = pos;
      uint32_t memoryCount = readLEB128();
      uint8_t initPage = readU8();
      uint8_t maxPage = readU8();
      if (oldPos + size > pos) { // only support one memory, skip others
        skipN(oldPos + size - pos);
      }
      while (maxPage > 0) {
        maxPage--;
        backend.memory.push_back(std::vector<uint8_t>(WASM_MEMORY_ONE_PAGE_SIZE));
      }
      break;
    }
    case SectionCode::Global: {
      uint32_t size = readLEB128();
      uint32_t globalSize = readLEB128();
      uint32_t index = 0;
      while (globalSize > 0) {
        globalSize--;
        uint8_t globalType = readU8();
        if (globalType >= Type::f64 && globalType <= Type::i32) {
          uint8_t isMutable = readU8();
          uint8_t opcode = readU8();
          switch (opcode) {
          case OPCode::i32_const: {
            uint32_t value = readLEB128();
            backend.globals.push_back({static_cast<bool>(isMutable), index, value});
            break;
          }
          }
          opcode = readU8();
          index++;
        } else {
          throw std::runtime_error("invalid global type");
        }
      }
      break;
    }
    case SectionCode::Export: // export section
    {
      uint32_t size = readLEB128();
      skipN(size);
      break;
    }

    case SectionCode::Code: // code section
    {
      uint32_t codeSize = readLEB128();
      uint32_t functionIndex = readLEB128();
      uint32_t functionSize = readLEB128();
      uint32_t functionStartPos = pos;
      uint32_t localSize = readLEB128();
      backend.acquireNewFunction();
      skipN(localSize);
      while (pos < functionSize + functionStartPos) {
        // read instruction
        uint8_t opCode = readU8();
        switch (opCode) {
        case OPCode::i32_const: // i32.const
        {
          uint32_t value = readLEB128();
          std::cout << "i32.const=" << value << std::endl;
          backend.I32Const(value);
          break;
        }
        case OPCode::i32_add: {
          std::cout << "i32.add" << std::endl;
          backend.I32Add();
          break;
        }
        case OPCode::drop: {
          std::cout << "drop" << std::endl;
          backend.Ins_Drop();
          break;
        }
        case OPCode::end: {
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
    case SectionCode::Data: { // data section
      uint32_t size = readLEB128();
      uint32_t dataCount = readLEB128();
      while (dataCount > 0) {
        dataCount--;
        uint32_t memoryIndex = readLEB128();
        uint8_t opcode = readU8();
        if (opcode != OPCode::i32_const) { // i32.const
          throw std::runtime_error("unsupported opcode");
        }
        uint32_t offset = readLEB128();
        uint8_t endOpcode = readU8();
        if (endOpcode != OPCode::end) { // end
          throw std::runtime_error("unsupported opcode");
        }
        uint32_t dataSize = readLEB128();
        uint32_t targetPage = static_cast<uint32_t>(offset / WASM_MEMORY_ONE_PAGE_SIZE);
        bool fromBegin = false;
        do {
          uint32_t realOffset = 0U;
          if (!fromBegin) {
            realOffset = offset - (targetPage * WASM_MEMORY_ONE_PAGE_SIZE);
          }
          uint32_t willCopySize = dataSize;
          if (dataSize > (WASM_MEMORY_ONE_PAGE_SIZE - realOffset)) { // split page
            willCopySize = WASM_MEMORY_ONE_PAGE_SIZE - realOffset;
            fromBegin = true;
          }
          std::string_view contentView(reinterpret_cast<char *>(input.data() + pos),
                                       reinterpret_cast<char *>(input.data() + pos + willCopySize));
          std::cout << "data section:" << contentView << std::endl;
          std::memcpy(backend.memory[targetPage].data() + realOffset, input.data() + pos,
                      willCopySize);
          dataSize -= willCopySize;
          skipN(willCopySize);
        } while (dataSize > 0);
      }
      break;
    }
    }
  }

  std::cout << "read file finished\n";
}
