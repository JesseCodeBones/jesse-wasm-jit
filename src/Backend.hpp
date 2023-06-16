#ifndef __JC_BACKEND__
#define __JC_BACKEND__
#include <cstdint>
#include <stack>
namespace jc {
class Backend{
  public:
  void I32Const(uint32_t value);
  void I32Add();
  void Drop();
  private:
  std::stack<uint64_t> runningStack;
};
}
#endif