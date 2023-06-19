#ifndef __JC_WASM_BINARY__
#define __JC_WASM_BINARY__
#include <cstdint>
namespace jc {
enum OPCode : uint8_t {
  i32_const = 0x41,
  i32_add = 0x6a,
  drop = 0x1a,
  end = 0x0b,
};
enum SectionCode : uint8_t {
  Type = 1U,     ///< Type: 1U
  Function = 3U, ///< Function: 3U
  Memory = 5U,   ///< Memory: 5U
  Global = 6U,   ///< Global: 6U
  Export = 7U,   ///< Export: 7U
  Code = 10U,    ///< Code: 10U
  Data = 11U,    ///< Data: 11U
};
enum Type : uint8_t {
  f64 = 0x7c,
  f32 = 0x7d,
  i64 = 0x7e,
  i32 = 0x7f,
  wasm_void = 0x40,
  wasm_invalid = 0x00
};
} // namespace jc
#endif