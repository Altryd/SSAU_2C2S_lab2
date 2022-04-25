#include <iostream>
#include <vector>

struct Stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

template<typename T, typename TCompare = std::less<T>>
Stats BubbleSort(std::vector<T>& data)
{
	TCompare less;
	Stats stats;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		bool swapped = false;
		size_t j_wall = size - 1 - i;
		for (size_t j = 0; j < j_wall; ++j)
		{
			stats.comparison_count += 1;
			if (less(data[j+1], data[j]))
			{
				auto tmp = data[j+1];
				data[j+1] = data[j];
				data[j] = tmp;
				stats.copy_count += 3;
				swapped = true;
			}
		}
		if (!swapped) return stats;
	}
	return stats;
}

template<typename T, typename TCompare = std::less<T>>
Stats ShellSort(std::vector<T>& data)
{
	int size = int(data.size());
	TCompare less;
	Stats stats;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; i += step)
		{
			for (int j = i - step; j >= 0; j -= step)
			{
				stats.comparison_count += 1;
				if (less(data[j+step], data[j]))
				{
					auto temp = data[j];
					data[j] = data[j + step];
					data[j + step] = temp;
					stats.copy_count += 3;
				}
			}
		}
	}
	return stats;
}

template<typename T, typename TCompare = std::less<T>>
void Heapify(std::vector<T>& data, size_t root_index, size_t size, Stats& stats)
{
	size_t root_left = 2 * root_index + 1;
	size_t root_right = 2 * root_index + 2;
	size_t largest = root_index;
	TCompare less;
	if (root_left < size && less(data[largest], data[root_left]) && (++stats.comparison_count) )
	{
		largest = root_left;
	}
	if (root_right < size && less(data[largest], data[root_right]) && (++stats.comparison_count))
	{
		largest = root_right;
	}
	if (largest != root_index)
	{
		auto tmp = data[root_index];
		data[root_index] = data[largest];
		data[largest] = tmp;
		stats.copy_count += 3;
		Heapify(data, largest, size, stats);
	}
}

template<typename T, typename TCompare = std::less<T>>
Stats HeapSort(std::vector<T>& data)
{
	int size = int(data.size());
	TCompare less;
	Stats stats;
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		Heapify(data, i, size, stats);
	}
	for (int i = size - 1; i > 0; i--)
	{
		auto tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		stats.copy_count += 3;
		Heapify(data, 0, i, stats);
	}
	return stats;
}




template<typename T, typename TCompare = std::less<T>>
bool IsSorted(std::vector<T>& data)
{
	size_t size = data.size();
	if (!size) return true;
	TCompare less;
	for (size_t i = 0; i < size - 1; ++i) 
	{
		if (less(data[i + 1], data[i])) return false; 
	}
	return true;
}

//#define DEBUG
//#define SORTED_VECTOR
//#define SORTED_BACKWARDS_VECTOR
int main()
{
	/*std::vector<int> vec;
	for (size_t i = 0; i < 10000; ++i)
	{
		vec.push_back(rand() % 100-50);
	}*/

	setlocale(LC_ALL, "Ru");
	//ѕосчитать число сравнений и копирований объекта дл€ полностью отсортированного массива
	//n = 1 000, 2 000, ... 10 000.
#ifdef SORTED_VECTOR
	std::cout << "„исло сравнений и копирований при полностью отсортированном массиве:" << std::endl;
	for (size_t i = 1000; i <= 10000; i += 1000)
	{
		size_t bubble_sum_comparison = 0;
		size_t bubble_sum_copy = 0;

		size_t shell_sum_comparison = 0;
		size_t shell_sum_copy = 0;

		size_t heap_sum_comparison = 0;
		size_t heap_sum_copy = 0;

		for (size_t number_of_try = 0; number_of_try < 100; ++number_of_try)
		{
			std::vector<int> vec_sorted;
			for (size_t j = 0; j <= i; ++j)
			{
				vec_sorted.push_back(j);
			}
			auto stats_bubble = BubbleSort(vec_sorted);
			bubble_sum_comparison += stats_bubble.comparison_count;
			bubble_sum_copy += stats_bubble.copy_count;

			auto stats_shell = ShellSort(vec_sorted);
			shell_sum_comparison += stats_shell.comparison_count;
			shell_sum_copy += stats_shell.copy_count;

			auto stats_heap = HeapSort(vec_sorted);
			heap_sum_comparison += stats_heap.comparison_count;
			heap_sum_copy += stats_heap.copy_count;
		}

		std::cout << "—татистика при размере: " << i << std::endl;
		std::cout << "—ортировка пузырьком, среднее количество сравнений: " << bubble_sum_comparison / 100 << " ; копирований: " << bubble_sum_copy / 100 << std::endl;
		std::cout << "—ортировка Ўелла, среднее количество сравнений: " << shell_sum_comparison / 100 << " ; копирований: " << shell_sum_copy / 100 << std::endl;
		std::cout << "—ортировка кучей, среднее количество сравнений: " << heap_sum_comparison / 100 << " ; копирований: " << heap_sum_copy / 100 << std::endl;
	}
#endif


#ifdef SORTED_BACKWARDS_VECTOR
	std::cout << "„исло сравнений и копирований при обратно отсортированном массиве:" << std::endl;
	for (size_t i = 1000; i <= 10000; i += 1000)
	{
		size_t bubble_sum_comparison = 0;
		size_t bubble_sum_copy = 0;

		size_t shell_sum_comparison = 0;
		size_t shell_sum_copy = 0;

		size_t heap_sum_comparison = 0;
		size_t heap_sum_copy = 0;

		for (size_t number_of_try = 0; number_of_try < 100; ++number_of_try)
		{
			std::vector<int> vec_sorted_backwards;
			for (int j = i+1; j > 0; --j)
			{
				vec_sorted_backwards.push_back(j);
			}
			auto stats_bubble = BubbleSort(vec_sorted_backwards);
			if (!IsSorted(vec_sorted_backwards)) std::cout << "CRITICAL ERROR BUBBLE SORT" << std::endl;
			bubble_sum_comparison += stats_bubble.comparison_count;
			bubble_sum_copy += stats_bubble.copy_count;
			vec_sorted_backwards.clear();

			for (int j = i+1; j > 0; --j)
			{
				vec_sorted_backwards.push_back(j);
			}
			auto stats_shell = ShellSort(vec_sorted_backwards);
			if (!IsSorted(vec_sorted_backwards)) std::cout << "CRITICAL ERROR SHELL SORT" << std::endl;
			shell_sum_comparison += stats_shell.comparison_count;
			shell_sum_copy += stats_shell.copy_count;
			vec_sorted_backwards.clear();

			for (int j = i+1; j > 0; --j)
			{
				vec_sorted_backwards.push_back(j);
			}
			auto stats_heap = HeapSort(vec_sorted_backwards);
			if (!IsSorted(vec_sorted_backwards)) std::cout << "CRITICAL ERROR HEAP SORT" << std::endl;
			heap_sum_comparison += stats_heap.comparison_count;
			heap_sum_copy += stats_heap.copy_count;
			vec_sorted_backwards.clear();
		}

		std::cout << "—татистика при размере: " << i << std::endl;
		std::cout << "—ортировка пузырьком, среднее количество сравнений: " << bubble_sum_comparison / 100 << " ; копирований: " << bubble_sum_copy / 100 << std::endl;
		std::cout << "—ортировка Ўелла, среднее количество сравнений: " << shell_sum_comparison / 100 << " ; копирований: " << shell_sum_copy / 100 << std::endl;
		std::cout << "—ортировка кучей, среднее количество сравнений: " << heap_sum_comparison / 100 << " ; копирований: " << heap_sum_copy / 100 << std::endl;
	}
#endif










/*
#ifdef DEBUG
	for (auto it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl << std::endl;
#endif
	// auto stats = BubbleSort(vec);
#ifdef DEBUG
	for (auto it : vec)
	{
		std::cout << it << " ";
	}
#endif
	// if (!IsSorted(vec)) std::cout << "error";
	*/
}