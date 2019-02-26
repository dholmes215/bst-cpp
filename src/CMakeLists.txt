add_executable(demo demo.cpp bst.hpp)

set_target_properties(demo
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANARD_REQUIRED ON
    CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*"
  )

target_link_libraries(demo ${CONAN_LIBS})
