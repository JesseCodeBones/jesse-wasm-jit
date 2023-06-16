#ifndef __JC_FRONTEND__
#define __JC_FRONTEND__

#include <filesystem>
namespace jc {
class Frontend {
public:
  Frontend(const char *const pathCharPtr) noexcept : wasmPath(pathCharPtr) {
  }
  Frontend(const std::filesystem::path path) noexcept : wasmPath(path) {
  }

  uint32_t run() noexcept;

private:
  std::filesystem::path wasmPath;
};
} // namespace jc

#endif