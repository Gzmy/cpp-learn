#include "sort.h"

void insertSort(std::vector<int>& vec){
	if(vec.empty()){
		return;
	}

	size_t i, j;
	for(i = 1; i < vec.size(); i++) {
		int tmp = vec[i];
		for(j = i; j > 0 && vec[j-1] > tmp; j--) {
			vec[j] = vec[j-1];
		}
		vec[j] = tmp;
	}
	/*
	int i = 1;
	for(; i < size; i++) {
		int key = array[i];
		int end = i - 1;
		while(end >= 0 && array[end] > key) {
			array[end+1] = array[end];
			end--;
		}
		array[end+1] = key;
	}
	*/
}

void shellSort(std::vector<int>& vec) {
	if(vec.empty()) {
		return;
	}

	for(int gap = vec.size()/2; gap > 0; gap /= 2) {
		for(size_t i = gap; i < vec.size(); i++) {
			int tmp = vec[i];
			int j;
			for(j = i; j >= gap && vec[j-gap] > tmp; j -= gap){
				vec[j] = vec[j-gap];
			}
			vec[j] = tmp;
		}
	}
	/*
	int gap = 3;
	while(gap--) {
		int i = gap;
		for(; i < size; i++) {
			int key = array[i];
			int end = i - gap;
			while(end >= 0 && array[end] > key) {
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end+gap] = key;
		}
	}
	*/
}

void bubbleSort(std::vector<int>& vec) {
	if(vec.empty()) {
		return;
	}

	bool is_swap = true;
	while(is_swap) {
		is_swap = false;
		for(size_t i = 0; i < vec.size()-1; i++) {
			if(vec[i] > vec[i+1]) {
				vec[i] += vec[i+1];
				vec[i+1] = vec[i] - vec[i+1];
				vec[i] -= vec[i+1];
				is_swap = true;
			}
		}
	}
	/*
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j < size; j++){
			if(array[i] > array[j]) {
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	*/
}

static void swap(int *left, int *right) {
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

static void heapAdJust(int array[], int size, int par) {
	int child = par*2 + 1;

	while(child < size) {
		if(child+1 < size && array[child+1] > array[child]) {
			child += 1;
		}

		if(array[par] >= array[child]) {
			break;
		} else {
			swap(&array[par], &array[child]);
			par = child;
			child = par*2 + 1;
		}
	}
}

void heapSort(int array[], int size) {
	if(array == NULL || size <= 0) {
		return;
	}

	for(int root = (size-2)/2; root >= 0; root--) {
		heapAdJust(array, size, root);
	}

	int end = size-1;
	while(end) {
		swap(&array[0], &array[end]);
		heapAdJust(array, end, 0);
		end--;
	}
}

void selectSort(std::vector<int>& vec) {
	if(vec.empty()) {
		return;
	}

	size_t minSpace = 0, maxSpace = vec.size()-1;
	while(minSpace < maxSpace) {
		size_t minPos = minSpace;
		size_t maxPos = minSpace;
		for(size_t i = minSpace+1; i <= maxSpace; i++) {
			if(vec[i] > vec[maxPos]) {
				maxPos = i;
			}

			if(vec[i] < vec[minPos]) {
				minPos = i;
			}
		}
		swap(&vec[minSpace], &vec[minPos]);
		if(maxPos == minSpace) {
			maxPos = minPos; //注意更换较大的下标
		}

		swap(&vec[maxSpace], &vec[maxPos]);

		minSpace++, maxSpace--;
	}
}

static int parition_1(std::vector<int>& vec, int left, int right) {
	int begin = left;
	int end = right;

	while(begin < end) {
		while(begin < end && vec[begin] <= vec[right]){
			begin++;
		}

		while(begin < end && vec[end] >= vec[right]) {
			end--;
		}

		swap(&vec[begin], &vec[end]);
	}
	swap(&vec[begin], &vec[right]);

	return begin;
}

static int parition_2(std::vector<int>& vec, int left, int right) {
	int begin = left;
	int end = right;
	int cur = vec[right];

	while(begin < end) {
		while(begin < end && vec[begin] <= cur) {
			begin++;
		}
		vec[end] = vec[begin];

		while(begin < end && vec[end] >= cur) {
			end--;
		}
		vec[begin] = vec[end];
	}

	vec[begin] = cur;
	return begin;
}

static int parition_3(std::vector<int>& vec, int left, int right) {
	int div = left, cur = left;
	for(; cur < right; cur++) {
		if(vec[cur] <= vec[right]) {
			swap(&vec[cur], &vec[div]);
			div++;
		}
	}

	swap(&vec[div], &vec[right]);
	return div;
}

static void _quickSort(std::vector<int>& vec, int left, int right) {
	if(left == right) {
		return;
	}

	if(right < left) {
		return;
	}

	//int div = parition_1(vec, left, right);
	int div = parition_2(vec, left, right);
	_quickSort(vec, left, div-1);
	_quickSort(vec, div+1, right);
}

void quickSort(std::vector<int>& vec) {
	if(vec.empty()) {
		return;
	}

	int left = 0, right = vec.size()-1;
	_quickSort(vec, left, right);
}

int main()
{
	int array[] = {10, 5, 4, 1, 3, 2, 9, 6, 8};
	int size = sizeof(array) / sizeof(array[0]);
	std::vector<int> vec(array, array+sizeof(array)/sizeof(array[0]));
	//insertSort(vec);
	//shellSort(vec);
	//bubbleSort(vec);
	//heapSort(array, 5);
	//selectSort(vec);
	quickSort(vec);
	for(int i = 0; i < size; i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
