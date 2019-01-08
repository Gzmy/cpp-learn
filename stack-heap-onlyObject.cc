#include <iostream>

//only heap create object

class onlyHeapOb{
	public:
		static onlyHeapOb* createInstance(int data){
			return new onlyHeapOb(data);
		}
	private:
		onlyHeapOb(int data) {
			std::cout << "onlyHeapOb" << this << std::endl;
			_data = data;
		}
		onlyHeapOb(const onlyHeapOb& ) = delete;
	private:
		int _data;
};

//create stack only object
//可能会多创建对象
class onlyStackOb{
	private:
		onlyStackOb(int data){
			std::cout << "onlyStackOb()" << this << std::endl;
			_data = data;
		}
	public:
		static onlyStackOb createInstance(int data){
			return onlyStackOb(data);
		}

		onlyStackOb(const onlyStackOb& st){
			std::cout << "onlyStackOb(const onlyStackOb&)" << this << std::endl;
			_data = st._data;
		}

		~onlyStackOb(){
			std::cout << "~onlyStackOb()" << this << std::endl;
		}
	private:
		int _data;
};

class onlyStackOb_2{
	public:
		onlyStackOb_2(){
			std::cout << "onlyStackOb_2" << this << std::endl;
		}
	private:
		void *operator new(size_t);
};

int main()
{
	onlyStackOb(onlyStackOb::createInstance(10));
	return 0;
}
