#include <iostream>

#if 0
class Base{
	public:
		Base(int b) : _b(b) {}

		Base(const Base& b) : _b(b._b) {}

		Base& operator=(const Base& b){
			std::cout << "Base::operator()" << this << std::endl;
			if(this != &b){
				_b = b._b;
			}
			return *this;
		}

		~Base(){
			std::cout << "~Base()" << this << std::endl;
		}
	protected:
		int _b;
};

class Derived : public Base{
	public:
		Derived(int b, int d) : Base(b), _d(d){
			std::cout << _b << " " << _d << std::endl;
		}

		Derived(const Derived& d) : Base(d._b), _d(d._d) {}

		Derived& operator=(const Derived& d){
			std::cout << "Derived::operator=()" << this << std::endl;
			if(this != &d){
				Base::operator=(d);
				_d = d._d;
			}
			return *this;
		}

		~Derived(){
			std::cout << "~Derived" << this << std::endl;
		}
	private:
		int _d;
};

int main()
{
	Derived d1(10, 20); //派生类调用基类构造函数
	Derived d2(d1); //派生类调用基类拷贝构造函数

	d2 = d1; //派生类调用基类赋值运算符重载
	//先调用派生类的析构函数，后调用基类构造函数
	return 0;
}
#endif

#if 0
//设计一个不能被继承的类
//C++98
class NonInherit{
	public:
		static NonInherit GetStackIntance(){
			return NonInherit();
		}

		static NonInherit* GetHeapIntance(){
			return new NonInherit();
		}
	private:
		NonInherit() {} //构造函数私有化，派生类无法初始化
};

//C++11
class NonInherit_C11 final{ //不能被继承
	public:
		NonInherit_C11() {}
};

#endif

#if 0
class Base{
	friend void Testfunc();
	protected:
		int _b;
};

class Derived : public Base{
	protected:
		int _d;
};

void Testfunc(){
	Base b;
	b._b = 10;

	//Derived d;
	//d._d = 20; //友元关系不继承
}
#endif

#if 0
//静态成员在继承体系中只有一份
class Base{
	public:
		Base(){
			_count++;
		}
		Base(const Base& ){
			_count++;
		}
		~Base(){
			_count--;
		}
	protected:
		static int _count;
};

int Base::_count = 0;

class Derived : public Base{
	public:
		Derived() {}
};

int main()
{
	std::cout << Base::_count << " " << Derived::_count << std::endl;
	return 0;
}
#endif

#if 0
class B{
	public:
		int _b;
};

class C1 : public B{
	public:
		int _c1;
};

class C2 : public B{
	public:
		int _c2;
};

class D : public C1, public C2{
	public:
		int _d;
};

int main()
{
	std::cout << sizeof(D) << std::endl;
	D d;
	d.C1::_b = 1;
	return 0;
}
#endif

#if 0
class B{
	public:
		int _b;
};

//虚拟继承
class D : virtual public B{
	public:
		int _d;
};

int main()
{
	std::cout << sizeof(D) << std::endl;
	D d;
	d._b = 1; //先从对象前四个字节中取出偏移量表格的地址addr
			  //addr向后偏移四个字节，取出该地址空间中的内容
			  //通过取到的基类对象相对于派生类对象起始位置的偏移量
			  //在派生类中根据偏移量来找到基类成员
	return 0;
}
#endif

//菱形虚拟继承---解决菱形继承的二义性
class B{
	public:
		int _b;
};

class C1 : virtual public B{
	public:
		int _c1;
};

class C2 : virtual public B{
	public:
		int _c2;
};

class D : public C1, public C2{
	public:
		int _d;
};

int main()
{
	D d;
	d._b = 1;
	d._c1 = 2;
	d._c2 = 3;
	d._d = 4;
	std::cout << sizeof(d) << std::endl;
	return 0;
}
