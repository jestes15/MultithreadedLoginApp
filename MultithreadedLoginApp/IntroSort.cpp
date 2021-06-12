#include "IntroSort.h"

inline auto constexpr
IntroSort::lg(int n) -> int
{
	return (int)sizeof(int) * __CHAR_BIT__  - 1 - BuiltIn::builtin_clz(n);
}

inline auto constexpr
IntroSort::lg(unsigned n) -> unsigned
{
	return (int)sizeof(int) * __CHAR_BIT__  - 1 - BuiltIn::builtin_clz(n);
}

inline auto constexpr
IntroSort::lg(long n) -> long
{
	return (int)sizeof(long) * __CHAR_BIT__ - 1 - BuiltIn::builtin_clzls(n);
}

inline auto constexpr
IntroSort::lg(unsigned long n) -> unsigned long
{
	return (int)sizeof(long) * __CHAR_BIT__ - 1 - BuiltIn::builtin_clzl(n);
}

inline auto constexpr
IntroSort::lg(long long n) -> long long
{
	return (int)sizeof(long) * __CHAR_BIT__ - 1 - BuiltIn::builtin_clzll(n);
}

inline auto constexpr
IntroSort::lg(unsigned long long n) -> unsigned long long
{
	return (int)sizeof(long) * __CHAR_BIT__ - 1 - BuiltIn::builtin_clzl(n);
}