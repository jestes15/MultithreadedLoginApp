#include "BuiltIn.h"
#pragma warning(disable )

static inline auto
BuiltIn::builtin_ctz(unsigned x) -> int
{
	unsigned long ret;
    _BitScanForward(&ret, x);
    return (int)ret;
}

static inline auto
BuiltIn::builtin_ctzll(unsigned long long x) -> int
{
    unsigned long ret;
    _BitScanForward64(&ret, x);
    return (int)ret;
}

static inline auto
BuiltIn::builtin_ctzl(unsigned long x) -> int
{
    return BuiltIn::builtin_ctz((uint32_t)x);
}

static inline auto
BuiltIn::builtin_clz(unsigned x) -> int
{
    return (int)__lzcnt(x);
}

static inline auto
BuiltIn::builtin_clzll(unsigned long long x) -> int
{
    return (int)__lzcnt64(x);
}

static inline auto
BuiltIn::builtin_clzls(unsigned long x) -> int
{
    return BuiltIn::builtin_clz((uint32_t)x);
}

static inline auto
BuiltIn::builtin_ctzl(unsigned long long x) -> int
{
    return BuiltIn::builtin_ctzll(x);
}

static inline auto
BuiltIn::builtin_clzl(unsigned long long x) -> int
{
    return BuiltIn::builtin_clzll(x);
}