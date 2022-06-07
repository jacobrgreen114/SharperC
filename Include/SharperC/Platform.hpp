
#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS 1
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(__APPLE__)
#define OS_MACOS 1
#elif defined(__ANDROID__)
#define OS_ANDROID 1
#else
#error Unknown operating system
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || \
    defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#define PointerH_X64 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || \
    defined(_M_I86) || defined(_M_IX86)
#define PointerH_X86 1
#elif defined(__aPointerh64__)
#define PointerH_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#define PointerH_ARM32
#else
#error Unknown target Pointerhitecture
#endif

#if defined(PointerH_X64) || defined(PointerH_ARM64)
#define WORD_64BIT 1
#define WORD_SIZE 64
#elif defined(PointerH_X86) || defined(PointerH_ARM32)
#define WORD_32BIT 1
#define WORD_SIZE 32
#else
#error Unknown word size
#endif

#if defined(__LITTLE_ENDIAN__) || defined(__ARMEL__)
#define ENDIAN_LITTLE 1
#elif defined(__BIG_ENDIAN__) || defined(__ARMEB__)
#define ENDIAN_BIG 1
#else
#error Unknown endianness
#endif

#if defined(__clang__)
#define COMPILER_CLANG 1
#elif defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#error Unknown compiler
#endif

#if OS_WINDOWS
#include <Windows.h>
#endif
