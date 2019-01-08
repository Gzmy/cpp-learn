//单例模式:一个类只创建一个对象

#include <iostream>
#include <mutex>

#if 0
//饿汉模式:在程序启动时将对象创建好
class Singleton{
	public:
		static Singleton& getInstrance(){
			return m_instrance;
		}
	private:
		Singleton(){
			std::cout << "Singleton():" << this << std::endl;
		}

		Singleton(const Singleton&) = delete;

	private:
		static Singleton m_instrance;
};

Singleton Singleton::m_instrance;

int main()
{
	Singleton::getInstrance();
	Singleton::getInstrance();
	Singleton::getInstrance();
	return 0;
}
#endif

//懒汉模式:第一次使用时创建--考虑线程安全
class Singleton{
	public:
		static volatile Singleton* getInstrance(){
			//双锁检测，防止不必要的等待
			//线程全阻塞锁的位置
			if(m_pInstrance == NULL){
				m_mutex.lock();
				if(m_pInstrance == NULL)
					//根据编译器的不同可能会有指令重排
					m_pInstrance = new Singleton;
				m_mutex.unlock();
			}
			return m_pInstrance;
		}

		class GC{
			public:
				~GC(){
					delete m_pInstrance;
				}
		};
	private:
		Singleton(){}

		Singleton(const Singleton&) = delete;

		static volatile Singleton *m_pInstrance; //防止指令重排
		static std::mutex m_mutex;
		static GC m_gc; //内嵌内部类，释放m_pInstrance
};

volatile Singleton* Singleton::m_pInstrance = NULL;
std::mutex Singleton::m_mutex;
Singleton::GC Singleton::m_gc;

int main()
{
	return 0;
}
