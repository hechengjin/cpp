#include "include/Blog.h"
#include "include/Reader.h"


int main()
{
	CBlog *blog = new CBlog("刘德华");
	CReader *reader1 = new CReader("何成进", blog);
	blog->Attach(reader1);
	blog->SetStatus(" 明天开演唱会！");
	blog->Notify();
	delete blog; 
	delete reader1;
	cin.get();
	return 0;
}