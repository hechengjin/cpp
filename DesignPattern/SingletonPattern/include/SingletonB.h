#ifndef __SINGLETONB_H__ 
#define __SINGLETONB_H__
#include "Singleton.h"

class SingletonB: public Singleton
{
	friend class Singleton; //必须为友元类，否则父类无法访问子类的构造函数
public:
	void Show() { cout << "SingletonB" << endl; }
private: //保护属性，这样外界无法通过构造函数进行实例化 
	SingletonB() {}
};

#endif //__SINGLETONB_H__
