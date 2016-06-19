#ifndef __SINGLETONA_H__ 
#define __SINGLETONA_H__
#include "Singleton.h"

class SingletonA: public Singleton
{
	friend class Singleton; //必须为友元类，否则父类无法访问子类的构造函数
public:
	void Show() { cout << "SingletonA" << endl; }
private: //保护属性，这样外界无法通过构造函数进行实例化 
	SingletonA() {}
};

#endif //__SINGLETONA_H__
