#include "./Frontend.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "BinaryIrReader.hpp"

using namespace jc;

uint32_t Frontend::run() noexcept {

  std::ifstream file(wasmPath.string(), std::ios::binary);
  auto fileSize = std::filesystem::file_size(wasmPath);
  std::vector<uint8_t> dataVector(fileSize);
  file.read(reinterpret_cast<char *>(dataVector.data()), fileSize);
  Module module;
  BinaryIrReader reader(dataVector, module);
  reader.read();
  return 0;
}