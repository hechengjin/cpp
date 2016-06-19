#include "include/Singleton.h"
#include "include/SingletonA.h"
#include "include/SingletonB.h"

Singleton* Singleton::singleton = NULL;
Singleton* Singleton::GetInstance(const char* name)
{
	if (NULL == singleton)
	{
		if (strcmp(name, "SingletonA") == 0)
			singleton = new SingletonA();
		else if (strcmp(name, "SingletonB") == 0)
			singleton = new SingletonB();
		else
			singleton = new Singleton();
	}
	return singleton;
}
