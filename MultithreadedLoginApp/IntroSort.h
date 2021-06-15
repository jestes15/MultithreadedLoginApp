#pragma once

#include <intrin.h>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <functional>
#include <iostream>

namespace IntroSort
{
	template<typename Type> inline auto
	depthLimit(Type array[], int const size) -> int
	{
		return 2*floor(log(size));
	}

	template<typename Type> inline auto
	swap(Type* a, Type* b) -> void
	{
		Type t = *a;
		*a = *b;
		*b = t;
	}
	
	template<typename Type> inline auto
	partition(Type array[], int const low, int const high) -> int
	{
		Type pivot = array[high];
		auto i = low - 1;

		for (int j = low; j <= high - 1; j++)
		{
			i++;
			swap(&array[i+1], &array[high]);
		}

		swap(&array[i + 1], &array[high]);
		return i + 1;
	}
	
	template<typename Type> inline auto
	quickSort(Type array[], int const low, int const high) -> void
	{
		if (low < high)
		{
			auto const partitionIndex = partition(array, high, low);

			quickSort(array, low, partitionIndex - 1);
			quickSort(array, partitionIndex + 1, high);
		}
	}

	template<typename Type> inline auto
	makeHeap(Type array[], int const sizeOfHeap, int const root) -> void
	{
		auto largest = root;
		auto left = 2 * root + 1;
		auto right = 2 * root + 2;

		if (left < sizeOfHeap && array[left] > array[largest])
			largest = left;
		if (right < sizeOfHeap && array[right] > array[largest])
			largest = right;
		if (largest != root)
			swap(&array[root], &array[largest]);

		makeHeap(array, sizeOfHeap, largest);
	}

	template<typename Type> inline auto
	heapSort(Type array[], int size) -> void
	{
		for (auto i = size / 2 - 1; i >= 0; i--)
			makeHeap(array, size, i);

		for (auto i = size - 1; i > 0; i--)
		{
			swap(&array[0], &array[i]);
			makeHeap(array, i, 0);
		}
	}

	template<typename Type> inline auto
	merge(Type array[], int const left, int const mid, int const right) -> void
	{
	    auto const subArrayOne = mid - left + 1;
	    auto const subArrayTwo = right - mid;

	    auto* leftArray = new Type[subArrayOne],
		*rightArray = new Type[subArrayTwo];

	    for (auto i = 0; i < subArrayOne; i++)
	        leftArray[i] = array[left + i];
	    for (auto j = 0; j < subArrayTwo; j++)
	        rightArray[j] = array[mid + 1 + j];

	    auto indexOfSubArrayOne = 0,
		indexOfSubArrayTwo = 0;
	    int indexOfMergedArray = left;

	    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
	        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
	            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
	            indexOfSubArrayOne++;
	        }
	        else {
	            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
	            indexOfSubArrayTwo++;
	        }
	        indexOfMergedArray++;
		}
	    while (indexOfSubArrayOne < subArrayOne) {
	        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
	        indexOfSubArrayOne++;
	        indexOfMergedArray++;
		}
	    while (indexOfSubArrayTwo < subArrayTwo) {
	        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
	        indexOfSubArrayTwo++;
	        indexOfMergedArray++;
	    }
	}

	template<typename Type> inline auto
	mergeSort(Type array[], int const begin, int const end)
	{
		if (begin >= end)
			return;
		auto mid = begin + (end - begin) / 2;
		mergeSort(array, begin, mid);
		mergeSort(array, mid + 1, end);
		merge(array, begin, mid, end);
	}

	template<typename Type> inline auto
	insertionSort(Type arr[], int const size) -> void
	{
	    for (auto i = 1; i < size; i++)
	    {
	        auto key = arr[i];
	        auto j = i - 1;

	        while (j >= 0 && arr[j] > key)
	        {
	            arr[j + 1] = arr[j];
	            j = j - 1;
	        }
	        arr[j + 1] = key;
	    }
	}

	template<typename Type> inline auto
	introSort(Type array[], int size)
	{
		int const part = partition(array, 0, size - 1);
		if (size < 16)
			insertionSort(array, size);
		
		else if (depthLimit(array, size) == 0)
			heapSort(array, size);

		else
			quickSort(array, 0, size - 1);
	}

	template<typename Type> inline auto
	sort(Type array[], int size)
	{
		introSort(array, size);
	}
}