#include "include/Blog.h"
#include "include/Reader.h"


int main()
{
	CBlog *blog = new CBlog("���»�");
	CReader *reader1 = new CReader("�γɽ�", blog);
	blog->Attach(reader1);
	blog->SetStatus(" ���쿪�ݳ��ᣡ");
	blog->Notify();
	delete blog; 
	delete reader1;
	cin.get();
	return 0;
}