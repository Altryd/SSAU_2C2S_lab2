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
	size_t size = data.size();
	TCompare less;
	Stats stats;
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; i += step)
		{
			for (int j = i - step; j >= 0; j -= step)
			{
				if (less(data[j+step], data[j]))
				{
					auto temp = data[j];
					data[j] = data[j + step];
					data[j + step] = temp;
				}
			}
		}
	}
	return stats;
}

template<typename T, typename TCompare = std::less<T>>
void Heapify(std::vector<T>& data, size_t root_index, size_t size)
{
	size_t root_left = 2 * root_index + 1;
	size_t root_right = 2 * root_index + 2;
	size_t largest = root_index;
	TCompare less;
	if (root_left < size && less(data[largest], data[root_left]))
	{
		largest = root_left;
	}
	if (root_right < size && less(data[largest], data[root_right]))
	{
		largest = root_right;
	}
	if (largest != root_index)
	{
		auto tmp = data[root_index];
		data[root_index] = data[largest];
		data[largest] = tmp;
		Heapify(data, largest, size);
	}
}

template<typename T, typename TCompare = std::less<T>>
Stats HeapSort(std::vector<T>& data)
{
	size_t size = data.size();
	TCompare less;
	Stats stats;
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		Heapify(data, i, size);
	}
	for (int i = size - 1; i > 0; i--)
	{
		auto tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		Heapify(data, 0, i);
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
int main()
{
	std::vector<int> vec;
	for (size_t i = 0; i < 10000; ++i)
	{
		vec.push_back(rand() % 100-50);
	}
#ifdef DEBUG
	for (auto it : vec)
	{
		std::cout << it << " ";
	}
	std::cout << std::endl << std::endl;
#endif
	auto stats = BubbleSort(vec);
#ifdef DEBUG
	for (auto it : vec)
	{
		std::cout << it << " ";
	}
#endif
	if (!IsSorted(vec)) std::cout << "error";
}