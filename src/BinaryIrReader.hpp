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

  template <class Dest, class Source>
  constexpr Dest bit_cast(Source const &source) noexcept {
    static_assert(std::is_trivially_copyable<Source>::value,
                  "bit_cast requires the source type to be copyable");
    static_assert(std::is_trivially_copyable<Dest>::value,
                  "bit_cast requires the destination type to be copyable");
    static_assert(sizeof(Dest) == sizeof(Source),
                  "bit_cast requires source and destination to be the same size");
    Dest dest;
    static_cast<void>(std::memcpy(&dest, &source, static_cast<size_t>(sizeof(dest))));
    return dest;
  }

  template <class Type>
  Type readLEB128() {
    using IntermediateType =
        typename std::conditional<std::is_signed<Type>::value, int64_t, uint64_t>::type;
    return static_cast<Type>(
        bit_cast<IntermediateType>(readLEB128(std::is_signed<Type>::value, sizeof(Type) * 8U)));
  }

  uint64_t readLEB128(bool const signedInt, uint32_t const maxBits) {
    uint64_t result = 0U;
    uint32_t bitsWritten = 0U;
    uint8_t byte = 0xFFU;
    while ((static_cast<uint32_t>(byte) & 0x80U) != 0U) {
      byte = readU8();
      if (bitsWritten >= maxBits) {
        throw std::runtime_error("Malformed LEB128 integer (Out of bounds)\n");
      }
      uint32_t const lowByte = static_cast<uint32_t>(byte) & static_cast<uint32_t>(0x7FU);
      result |= static_cast<uint64_t>(lowByte) << static_cast<uint64_t>(bitsWritten);
      bitsWritten = bitsWritten + 7U;
      if (bitsWritten > maxBits) {
        if (signedInt && ((static_cast<uint32_t>(byte) &
                           static_cast<uint32_t>(
                               static_cast<uint32_t>(1)
                               << (static_cast<uint32_t>(6) - (bitsWritten - maxBits)))) != 0U)) {
          uint32_t const bitMask =
              (static_cast<uint32_t>(0xff) << ((6U - (bitsWritten - maxBits)) + 1U)) & 0b01111111U;
          if ((static_cast<uint32_t>(byte) & bitMask) != bitMask) {
            throw std::runtime_error("Malformed LEB128 signed integer (Wrong padding)\n");
          }
        } else {
          uint32_t const bitMask =
              (static_cast<uint32_t>(0xff) << ((6U - (bitsWritten - maxBits)) + 1U)) & 0b01111111U;
          if ((static_cast<uint32_t>(byte) & bitMask) != 0U) {
            throw std::runtime_error("Malformed LEB128 unsigned integer (Wrong padding)\n");
          }
        }
      }
    }

    if ((signedInt && ((static_cast<uint32_t>(byte) & 0x40U) != 0U)) && (bitsWritten < 64U)) {
      uint64_t const signExtensionMask = 0xFFFF'FFFF'FFFF'FFFFLLU << bitsWritten;
      result |= signExtensionMask;
    }
    return result;
  }
};
} // namespace jc
#endif