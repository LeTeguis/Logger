#ifndef __TYPES_H_HEADER__
#define __TYPES_H_HEADER__

#pragma once

#include "Platform.h"

namespace nkentsuu
{
    // Unsigned int types.
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef unsigned long uintl32;
    typedef unsigned long long uint64;

    // Signed int types.
    typedef signed char int8;
    typedef signed short int16;
    typedef signed int int32;
    typedef signed long long int64;

    // Floating point types
    typedef float float32;
    typedef double float64;

    // Boolean types
    typedef int bool32;

    typedef struct NKENTSUU_API range {
        uint64 offset;
        uint64 size;
    } range;

    #define INVALID_ID_UINT64 18446744073709551615UL
    #define INVALID_ID 4294967295U
    #define INVALID_ID_UINT16 65535U
    #define INVALID_ID_UINT8 255U

    #define GIBIBYTES(amount) ((amount) * 1024ULL * 1024ULL * 1024ULL)
    #define MEBIBYTES(amount) ((amount) * 1024ULL * 1024ULL)
    #define KIBIBYTES(amount) ((amount) * 1024ULL)

    #define GIGABYTES(amount) ((amount) * 1000ULL * 1000ULL * 1000ULL)
    #define MEGABYTES(amount) ((amount) * 1000ULL * 1000ULL)
    #define KILOBYTES(amount) ((amount) * 1000ULL)

    #define KCLAMP(value, min, max) ((value <= min) ? min : (value >= max) ? max \
                                                                       : value)

    NKENTSUU_INLINE uint64 NKENTSUU_API get_aligned(uint64 operand, uint64 granularity) {
        return ((operand + (granularity - 1)) & ~(granularity - 1));
    }

    NKENTSUU_INLINE range NKENTSUU_API get_aligned_range(uint64 offset, uint64 size, uint64 granularity) {
        return {get_aligned(offset, granularity), get_aligned(size, granularity)};
    }

    #define MIN(x, y) ((x) < (y) ? (x) : (y))
    #define MAX(x, y) ((x) > (y) ? (x) : (y))
    #define ABS(x) ((x) >= (0) ? (x) : (-x))

} // namespace nkentsuu


#endif /* __TYPES_H_HEADER__ */
