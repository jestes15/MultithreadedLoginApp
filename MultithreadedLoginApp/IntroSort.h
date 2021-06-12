#pragma once

#ifndef CHAR_BIT
#define __CHAR_BIT__ 8
#endif

#include <intrin.h>
#include <cstdint>
#include <climits>

#include "BuiltIn.h"
namespace IntroSort
{
	template<typename RandomAccessIterator, typename Compare> inline
	auto sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) -> void;
	
	// Sorting algorithms, Quick Sort, Insertion Sort, and Heap Sort
	template<typename RandomAccessIterator, typename Compare> inline
	auto qsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) -> void;

	template<typename RandomAccessIterator, typename Compare> inline
	auto insertion_sort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) -> void;

	template<typename RandomAccessIterator, typename Compare> inline
	auto heap_sort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) -> void;

	// Functions needed for the local implementation of Introspective Sort, or IntroSort
	// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_algo.h#L1900
	template<typename RandomAccessIterator, typename Compare> inline
	auto ungaurded_partition_pivot(RandomAccessIterator first, RandomAccessIterator last, Compare comp) -> RandomAccessIterator;

	// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_algo.h#L1912
	template<typename RandomAccessIterator, typename Compare> inline
	auto partial_sort(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last, Compare comp) -> void;

	// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_algo.h#L1925
	template<typename RandomAccessIterator, typename Size, typename Compare>
	auto introsort_loop(RandomAccessIterator first, RandomAccessIterator last, Size depthLimit, Compare comp) -> void;

	inline auto constexpr lg(int n) -> int;
	inline auto constexpr lg(unsigned n) -> unsigned;
	inline auto constexpr lg(long n) -> long;
	inline auto constexpr lg(unsigned long n) -> unsigned long;
	inline auto constexpr lg(long long n) -> long long;
	inline auto constexpr lg(unsigned long long n) -> unsigned long long;
}