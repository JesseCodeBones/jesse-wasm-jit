#include <filesystem>
#include <gtest/gtest.h>
#include "../src/Frontend.hpp"
static constexpr std::string_view PROJECT_NAME("jesse-wasm-jit");
static const std::filesystem::path getProjectPath() noexcept {
  const std::filesystem::path currentFile(__FILE__);
  const std::string currentPath(currentFile.c_str());
  const std::filesystem::path project_path(
      currentPath.substr(0U, currentPath.rfind(PROJECT_NAME) + PROJECT_NAME.size()));
  return project_path;
}
TEST(jesse_wasm_jit_test, e2e) {
  auto wasmPath = getProjectPath() / "test" / "wasm" / "addTwo.wasm";
  jc::Frontend frontend(wasmPath);
  uint32_t returnCode = frontend.run();
}