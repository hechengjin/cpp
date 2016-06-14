#ifndef __READER_H__ 
#define __READER_H__

#include "interface/IObserver.h"
#include "Blog.h"
//cout
#include <iostream>
using namespace std;

#include <string>
using std::string;


class CReader
	: public IObserver
{
public:
	CReader(string name, CBlog *blog) : m_name(name), m_blog(blog) {};
	~CReader() {};

public:
	// IObserver
	virtual void Update();

private:
	string m_name;  //观察者名称  
	CBlog *m_blog;   //观察的主题，当然以链表形式更好，就可以观察多个主题
};

#endif //__ABOUTIMPL_H__
