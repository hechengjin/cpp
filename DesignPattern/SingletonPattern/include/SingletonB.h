#ifndef __SINGLETONB_H__ 
#define __SINGLETONB_H__
#include "Singleton.h"

class SingletonB: public Singleton
{
	friend class Singleton; //����Ϊ��Ԫ�࣬�������޷���������Ĺ��캯��
public:
	void Show() { cout << "SingletonB" << endl; }
private: //�������ԣ���������޷�ͨ�����캯������ʵ���� 
	SingletonB() {}
};

#endif //__SINGLETONB_H__
