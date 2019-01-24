add_executable(tests test.cpp ../src/bst.hpp)

set_target_properties(tests
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANARD_REQUIRED ON
    CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*"
  )

target_include_directories(tests PRIVATE ../src)

target_link_libraries(tests ${CONAN_LIBS})
