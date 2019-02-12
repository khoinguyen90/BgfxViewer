#ifndef BASE_H_
#define BASE_H_

// C/C++
#include <new>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cwchar>
#include <cwctype>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>
#include <functional>
#include <bitset>
#include <typeinfo>
#include <thread>
#include <mutex>
#include <chrono>
#include "Logger.h"
#include "bgfx/bgfx.h"
#include "bx/bx.h"
#include "bx/math.h"

#ifdef __ANDROID__
    #define GP_PLATFORM_ANDROID		1
#elif _WIN32
    #define GP_PLATFORM_WINDOWS		1
#elif __linux__
    #define GP_PLATFORM_LINUX		1
#endif


// Common
#ifndef NULL
#define NULL     0
#endif

namespace MimicViewer
{
/**
 * Print logging (implemented per platform).
 * @script{ignore}
 */
extern void print(const char* format, ...);

// Define a platform-independent case-insensitive ASCII string comparison function.
extern int strcmpnocase(const char* s1, const char* s2);
}

// Current function macro.
#ifdef _WIN32
#define __current__func__ __FUNCTION__
#else
#define __current__func__ __func__
#endif

// Assert macros.
#ifdef _DEBUG
#define MV_ASSERT(expression) assert(expression)
#else
#define MV_ASSERT(expression)
#endif

#if defined(_WIN32) && defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif

// Error macro.
#ifdef MV_ERRORS_AS_WARNINGS
#define MV_ERROR MV_WARN
#else
#define MV_ERROR(...) do \
    { \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_ERROR, "%s -- ", __current__func__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_ERROR, __VA_ARGS__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_ERROR, "\n"); \
        DEBUG_BREAK(); \
        assert(0); \
        std::exit(-1); \
    } while (0)
#endif

// Warning macro.
#define MV_WARN(...) do \
    { \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_WARN, "%s -- ", __current__func__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_WARN, __VA_ARGS__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_WARN, "\n"); \
    } while (0)

// Info macro.
#define MV_INFO(...) do \
    { \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_INFO, "%s -- ", __current__func__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_INFO, __VA_ARGS__); \
        MimicViewer::Logger::log(MimicViewer::Logger::LEVEL_INFO, "\n"); \
    } while (0)

#if defined(_WIN32)
    #pragma warning( disable : 4005 )
    #pragma warning( disable : 4172 )
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4311 )
    #pragma warning( disable : 4316 )
    #pragma warning( disable : 4390 )
    #pragma warning( disable : 4800 )
    #pragma warning( disable : 4996 )
#endif


// Object deletion macro
#define SAFE_DELETE(x) \
    { \
        delete x; \
        x = NULL; \
    }

// Array deletion macro
#define SAFE_DELETE_ARRAY(x) \
    { \
        delete[] x; \
        x = NULL; \
    }

// Ref cleanup macro
#define SAFE_RELEASE(x) \
    if (x) \
    { \
        (x)->release(); \
        x = NULL; \
    }

// Math
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIOVER360              0.008726646259971647884f
#define MATH_PIOVER180              0.0174532924f
#define MATH_180OVERPI              57.29578f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif

// Hardware buffer
namespace MimicViewer
{

/** Gamepad handle */
#ifdef __ANDROID__
typedef unsigned int GamepadHandle;
#else
typedef unsigned long GamepadHandle;
#endif
}

#endif
