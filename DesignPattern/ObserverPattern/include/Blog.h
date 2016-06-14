#ifndef __BLOG_H__ 
#define __BLOG_H__

#include "interface/ISubject.h"
//cout
#include <iostream>
using namespace std;
//string
#include <string>
#include <list>
using std::string;
using std::list;

class CBlog
	: public ISubject
{
public:
	CBlog(string name) : m_name(name) {};
	~CBlog() {};

public:
	// ISubject
	void Attach(IObserver *pObserver);
	void Remove(IObserver *pObserver);
	void Notify();


	//����״̬
	void SetStatus(string s) { m_status = m_name + s; } 
	//���״̬
	string GetStatus() { return m_status; }  
protected:
	string m_status; //״̬
private:
	list<IObserver* > m_observers; //�۲�������
private:
	string m_name; //��������
};

#endif //__BLOG_H__
