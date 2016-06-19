#ifndef __SINGLETON_H__ 
#define __SINGLETON_H__

#include <iostream>
using namespace std;

class Singleton
{
public:
	static Singleton* GetInstance(const char* name);
	virtual void Show() {}
protected: //����Ϊ�����������˽�����ԣ������޷����ʸ���Ĺ��캯��
	Singleton() {}
private:
	static Singleton *singleton; //Ψһʵ����ָ��
};

#endif //__SINGLETON_H__
