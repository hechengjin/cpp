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
	string m_name;  //�۲�������  
	CBlog *m_blog;   //�۲�����⣬��Ȼ��������ʽ���ã��Ϳ��Թ۲�������
};

#endif //__ABOUTIMPL_H__
