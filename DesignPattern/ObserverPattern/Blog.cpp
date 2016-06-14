#include "include/Blog.h"


void CBlog::Attach(IObserver *pObserver)
{
	m_observers.push_back(pObserver);
}

void CBlog::Remove(IObserver *pObserver)
{
	m_observers.remove(pObserver);
}

void CBlog::Notify()
{
	list<IObserver*>::iterator iter = m_observers.begin();
	for (; iter != m_observers.end(); iter++)
		(*iter)->Update();
}