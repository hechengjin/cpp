#include "include/Reader.h"



void CReader::Update()
{
	string status = m_blog->GetStatus();
	cout << m_name << "收到通知：-------" << status << endl;
}
