#include <iostream>
#include <assert.h>
#include <algorithm>

template<class T>
class vector{
	public:
		typedef T* Iterator;
		typedef const T* ConstIterator;
	private:
		Iterator _start; //数据开始
		Iterator _finish; //数据结尾
		Iterator _endOfSt; //存储结尾
	public:
		Iterator begin(){
			return _start;
		}
		Iterator end(){
			return _finish;
		}
		ConstIterator cbegin() const{
			return _start;
		}
		ConstIterator cend() const{
			return _finish;
		}

		size_t size(){
			return _finish-_start;
		}
		size_t capacity(){
			return _endOfSt-_start;
		}
		bool empty(){
			if(_finish-_start){
				return false;
			}
			return true;
		}
		vector() 
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfSt(nullptr)
		{}

		vector(int n, const T& value = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfSt(nullptr)
		{
			reserve(n);
			while(n--){
				push_back(value);
			}
		}

		template<class inputIterator> //重新声明迭代器区间
		vector(inputIterator first, inputIterator last) : _start(nullptr), _finish(nullptr), _endOfSt(nullptr){
			reserve(last - first);
			while(first != last){
				push_back(*first);
				first++;
			}
		}

		vector(vector<T>& vec) : _start(nullptr), _finish(nullptr), _endOfSt(nullptr){
			reserve(vec.capacity());
			Iterator it = begin();
			ConstIterator cit = vec.cbegin();
			while(cit != vec.cend()){
				*it++ = *cit++;
			}
			_finish = _start + vec.size();
			_endOfSt = _start + vec.capacity();
		}		

		vector<T>& operator=(vector<T> vec){
			Swap(vec);
			return *this;
		}

		~vector(){
			delete[] _start;
			_start = _finish = _endOfSt = nullptr;
		}

		/////////////////////////////
		//capacity
		void reserve(size_t n){
			if(n > capacity()){
				size_t s = size();
				T* tmp = new T[n];

				if(_start){
					for(size_t i = 0; i < s; i++){
						tmp[i] = _start[i];
					}
				}
				_start = tmp;
				_finish = _start + s;
				_endOfSt = _start + n;
			}
		}

		void resize(size_t n, const T& value = T()){
			if(n <= size()){
				_finish = _start+n;
				return;
			}

			if(n > capacity()){
				reserve(n);
			}

			Iterator it = _finish;
			_finish = _start+n;
			while(it != _finish){
				*it = value;
				it++;
			}
		}

		void Swap(vector<T>& vec){
			std::swap(_start, vec._start);
			std::swap(_finish, vec._finish);
			std::swap(_endOfSt, vec._endOfSt);
		}

		void push_back(const T& x){
			insert(end(), x);
		}

		void pop_back(){
			erase(--end());
		}

		Iterator insert(Iterator pos, const T& x){
			assert(pos <= _finish);

			size_t cur = pos - _start;
			if(_finish == _endOfSt){ //空间不够先增容
				//size_t s = size();
				size_t newCapacity = capacity() == 0 ? 1 : capacity() * 2;
				reserve(newCapacity);
				//发生增容，重置pos
				pos = _start + cur;
			}

			Iterator end = _finish-1;
			while(end >= pos){
				*(end+1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}

		Iterator erase(Iterator pos){
			Iterator begin = pos + 1;
			while(begin != _finish){
				*(begin-1) = *begin;
				++begin;
			}
			--_finish;
			return pos;
		}

		T& operator[](size_t pos){
			return _start[pos];
		}
};


void testVector1(){
	vector<int> first;
	if(first.empty()){
		std::cout << "first is empty" << std::endl;
	}

	vector<int> second(4, 100);
	for(auto x : second){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	vector<int> third(second.begin(), second.end());
	for(auto x : third){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	vector<int> fourth(third);
	for(auto x : fourth){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	int arr[] = {1, 2, 5, 7};
	vector<int> fifth(arr, arr+sizeof(arr)/sizeof(arr[0]));
	for(vector<int>::Iterator it = fifth.begin(); it != fifth.end(); it++){
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;


	vector<std::string> strV;
	strV.push_back("1111");
	strV.push_back("2222");
	strV.push_back("3333");
	strV.push_back("4444");
	for(size_t i = 0; i < strV.size(); i++){
		std::cout << strV[i] << " ";
	}
	std::cout << std::endl;
}

void printVector(const vector<int>& vec){
	vector<int>::ConstIterator it = vec.cbegin();
	while(it != vec.cend()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}

void testVector2(){
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	vector<int>::Iterator it = vec.begin();
	while(it != vec.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	it = vec.begin();
	while(it != vec.end()){
		*it *= 2;
		it++;
	}
	printVector(vec);
}

void testVector3(){
	size_t sz;
	vector<int> vec;
	sz  = vec.capacity();
	std::cout << "making vec grow:\n";
	for(int i = 0; i < 100; i++){
		vec.push_back(i);
		if(sz != vec.capacity()){
			sz = vec.capacity();
			std::cout << "capacity changed : " << sz << '\n';
		}
	}

	std::cout << "-----------------------" << std::endl;
	//reserve
	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);
	std::cout << "making bar grow:\n";
	for(int i = 0; i < 100; i++){
		bar.push_back(i);
		if(sz != bar.capacity()){
			sz = bar.capacity();
			std::cout << "capacity changed : " << sz << '\n';
		}
	}

	std::cout << "-----------------------" << std::endl;
	vector<int> foo;
	for(int i = 0; i < 10; i++){
		foo.push_back(i);
	}

	std::cout << "-------------------------" << std::endl;
	for(auto x : foo){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	foo.resize(5);
	std::cout << "-------------------------" << std::endl;
	for(auto x : foo){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	foo.resize(8, 100);
	std::cout << "-------------------------" << std::endl;
	for(auto x : foo){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	foo.resize(12);
	std::cout << "-------------------------" << std::endl;
	for(auto x : foo){
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

void testVector4(){
	int arr[] = {1, 2, 3, 4, 5};
	vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

	vector<int>::Iterator pos = std::find(vec.begin(), vec.end(), 3);
	vec.insert(pos, 30);

	vector<int>::Iterator it = vec.begin();
	while(it != vec.end()){
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	pos = std::find(vec.begin(), vec.end(), 3);
	vec.erase(pos);

	it = vec.begin();
	while(it != vec.end()){
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void testVector6(){
	int arr[] = {1, 2, 3, 4};
	vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

	vec[0] = 10;
	std::cout << vec[0] << std::endl;

	for(size_t i = 0; i < vec.size(); i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	vector<int> swapv;
	swapv.Swap(vec);

	std::cout << "vec data:";
	for(size_t i = 0; i < vec.size(); i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "swapv data:";
	for(size_t i = 0; i < swapv.size(); i++){
		std::cout << swapv[i] << " ";
	}
	std::cout << std::endl;
}

void testVector7(){
	int arr[] = {1, 2, 3, 4};
	vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

	vector<int>::Iterator pos = std::find(vec.begin(), vec.end(), 3);
	vec.erase(pos);
	std::cout << *pos << std::endl;
	for(size_t i = 0; i < vec.size(); i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	pos = std::find(vec.begin(), vec.end(), 3);
	vec.insert(pos, 30);
	std::cout << *pos << std::endl;
	for(size_t i = 0; i < vec.size(); i++){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	testVector7();
	return 0;
}
