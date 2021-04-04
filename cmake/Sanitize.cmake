#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Address Sanitizer
# https://clang.llvm.org/docs/AddressSanitizer.html

set(ASAN_COMPILE_FLAGS -fsanitize=address,undefined -fno-sanitize-recover=all)
set(ASAN_LINK_FLAGS -fsanitize=address,undefined)

if(ASAN)
    message(STATUS "Sanitize with Address Sanitizer (ASAN)")
    add_compile_options(${ASAN_COMPILE_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ASAN_LINK_FLAGS}")
endif()

