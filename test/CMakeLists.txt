find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ${test_sources} ./*.cpp)
add_executable(
  jesse-wasm-jit-test
  ${test_sources}
)

target_link_libraries(
  jesse-wasm-jit-test
  GTest::gtest_main
)

file(GLOB sources CONFIGURE_DEPENDS ../src/*.cpp ../src/*.hpp)
target_sources(jesse-wasm-jit-test PUBLIC ${sources})
include(GoogleTest)
gtest_discover_tests(jesse-wasm-jit-test)

