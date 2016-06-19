#include "include/Singleton.h"


int main()
{
	Singleton *st = Singleton::GetInstance("SingletonB");
	st->Show();
	cin.get();
	return 0;
}