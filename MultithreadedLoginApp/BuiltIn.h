#pragma once

#include <intrin0.h>
#include <cstdint>

namespace BuiltIn
{
	static inline auto builtin_ctz(unsigned x) -> int;
	static inline auto builtin_ctzll(unsigned long long x) -> int;
	static inline auto builtin_ctzl(unsigned long x) -> int;
	static inline auto builtin_clz(unsigned x) -> int;
	static inline auto builtin_clzll(unsigned long long x) -> int;
	static inline auto builtin_clzls(unsigned long x) -> int;
	static inline auto builtin_ctzl(unsigned long long x) -> int;
	static inline auto builtin_clzl(unsigned long long x) -> int;
}
