#include <iostream>
#include <ostream>
#include <assert.h>
#include <string.h>

class String{
	public:
		typedef char* Iterator;
	private:
		char *_str;
		size_t _capacity;
		size_t _size;
	private:
		friend std::ostream& operator<<(std::ostream& _cout, const String& s);
	public:
		String(const char* str = ""){
			if(NULL == str){
				assert(false);
				return;
			}
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity+1];
			strcpy(_str, str);
		}

		String(const String& s)
			: _str(new char[s._capacity+1])
			, _size(s._size)
			, _capacity(s._capacity)
		{
			strcpy(_str, s._str);
		}	

		String& operator=(const String& s){
			if(this != &s){
				char *Pstr = new char[s._capacity+1];
				strcpy(Pstr, s._str);

				delete _str;
				_str = Pstr;
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;
		}

		~String(){
			if(_str){
				delete[] _str;
				_str = NULL;
			}
		}

		//Iterator
		Iterator begin(){
			return _str;
		}

		Iterator end(){
			return _str + _size;
		}

		//modify
		void push_back(char c){
			if(_size == _capacity){
				reserve(_capacity*2);
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}

		void append(size_t n, char c){
			for(int i = 0; i < n; i++){
				push_back(c);
			}
		}

		void append(const char* str){
			for(int i = 0; i < strlen(str); i++){
				push_back(str[i]);
			}
		}

		String& operator+=(char c){
			push_back(c);
			return *this;
		}

		String& operator+=(const char* str){
			for(int i = 0; i < strlen(str); i++){
				push_back(str[i]);
			}
			return *this;
		}

		void clear(){
			_size = 0;
			_str[_size] = '\0';
		}

		void Swap(String& s){
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		const char* c_str() const{
			return _str;
		}

		//capacity
		size_t size()const{
			return _size;
		}

		size_t capacity()const{
			return _capacity;
		}

		bool empty()const{
			return _size == 0;
		}

		void resize(size_t newSize, char c = char()){
			if(newSize > _size){
				if(newSize > _capacity){
					reserve(newSize);
				}
				memset(_str+_size, c, newSize-_size);
			}
			_size = newSize;
			_str[newSize] = '\0';
		}

		void reserve(size_t newCapacity){
			if(newCapacity > _capacity){
				char *str = new char[newCapacity + 1];
				strcpy(str, _str);

				delete _str;
				_str = str;
				_capacity = newCapacity;
			}
		}

		//access
		char& operator[](size_t index){
			assert(index < _size);
			return _str[index];
		}

		const char& operator[](size_t index) const{
			assert(index < _size);
			return _str[index];
		}

		//operator
		bool operator<(const String& s){
			return _size < s._size;
		}

		bool operator<=(const String& s){
			return _size <= s._size;
		}
		
		bool operator>(const String& s){
			return _size > s._size;
		}

		bool operator>=(const String& s){
			return _size >= s._size;
		}

		bool operator==(const String& s){
			return _size == s._size;
		}

		bool operator!=(const String& s){
			return _size != s._size;
		}

		size_t find(char c, size_t pos = 0)const{
			assert(pos < _size);
			for(int i = pos; i < _size; i++){
				if(_str[i] == c){
					return i;
				}
			}
			return -1;
		}

		size_t find(const char* str, size_t pos = 0)const;

		String substr(size_t pos, size_t n){
			assert(pos < _size);
			String tmp;
			for(int i = pos; i < n; i++){
				if(i == _size){
					break;
				}
				tmp.push_back(_str[i]);
			}
			return tmp;
		}

		//在pos位置插入，返回字符位置
		String& insert(size_t pos, char c){
			assert(pos < _size);
			if(_size >= _capacity){
				reserve(2*_capacity + 1);
			}

			if(pos != _size){
				for(size_t i = _size; i > pos; i--){
					_str[i] = _str[i-1];
				}
			}
			_str[pos] = c;
			++_size;
			_str[_size] = '\0';
			return *this;
		}

		String& insert(size_t pos, const char* str);

		//删除pos上的元素，返回该元素的下一个位置
		String& earse(size_t pos, size_t len);
};

std::ostream& operator<<(std::ostream& _cout, const String& s){
	std::cout << s._str;
	return _cout;
}


void TestString1(){
	String s1;
	String s2("hello world");
	String s3(s2);

	s1 = s3;
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;
}

void TestString2(){
	String s("hello wolrd");
	s.push_back(' ');
	s.push_back('g');
	s.push_back('z');
	s.push_back('y');
	s.append(1, ' ');
	s += "i am y";

	auto it = s.begin();
	while(it != s.end()){
		std::cout << *it++;
	}
	std::cout << std::endl;

	String s1 ("hello!!!");
	s.Swap(s1);
	std::cout << s << std::endl;
	std::cout << s1 << std::endl;
}

void TestString3(){
	String s("hello");
	std::cout << s << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;

	s.resize(10, 'a');
	std::cout << s << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;

	s.resize(20);
	std::cout << s << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;

	s.resize(5);
	std::cout << s << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;

	s.reserve(50);
	std::cout << s << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;
}

int main()
{
	TestString3();
	return 0;
}
