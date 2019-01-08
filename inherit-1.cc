#include <iostream>

#if 0
class Base{
	public:
		void SetBase(int pri, int pro, int pub){
			_priB = pri;
			_proB = pro;
			_pruB = pub;
		}

		void Print(){
			std::cout << "_priB = " << _priB << std::endl;
			std::cout << "_proB = " << _proB << std::endl;
			std::cout << "_pruB = " << _pruB << std::endl;
		}
	private:
		int _priB;
	protected:
		int _proB;
	public:
		int _pruB;
};

class Derived : /*public*/ /*protected*/ private Base{
	public:
		void SetDerived(int pub, int pro, int pri){
			//SetBase(pub, pro, pri);
			_pruB = pub;
			_proB = pro;
			_priD = pri;
		}
	private:
		int _priD;
	protected:
		int _proD;
	public:
		int _pruD;

};

int main()
{
	std::cout << sizeof(Derived) << std::endl;

	return 0;
}
#endif

#if 0
class Base{
	public:
		int _pruB;
};

class Child : public Base{
	public:
		int _pruC;
};

int main()
{
	std::cout << sizeof(Child) << std::endl;
	Base b;
	Child c;
	std::cout << &b._pruB << std::endl;
	std::cout << &c._pruB << std::endl;
	std::cout << &c._pruC << std::endl;
	return 0;
}
#endif

class Base{
	public:
		void TestFunc(){
			std::cout << "Base::TestFunc" << std::endl;
		}
	public:
		int _b;
};

class Child : public Base{
	public:
		void TestFunc(){
			std::cout << "Child::TestFunc" << std::endl;
		}
	public:
		char _b;
};

int main()
{
	Child d;
	d._b = 'c';
	d.Base::_b = 1;
	std::cout << d.Base::_b << std::endl;

	d.Base::TestFunc();
	d.TestFunc();
	return 0;
}
