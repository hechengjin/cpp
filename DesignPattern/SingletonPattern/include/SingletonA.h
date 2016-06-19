#ifndef __SINGLETONA_H__ 
#define __SINGLETONA_H__
#include "Singleton.h"

class SingletonA: public Singleton
{
	friend class Singleton; //����Ϊ��Ԫ�࣬�������޷���������Ĺ��캯��
public:
	void Show() { cout << "SingletonA" << endl; }
private: //�������ԣ���������޷�ͨ�����캯������ʵ���� 
	SingletonA() {}
};

#endif //__SINGLETONA_H__
