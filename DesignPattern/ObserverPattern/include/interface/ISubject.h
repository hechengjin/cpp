/**
*@file ISubject.h
*
*@brief 主题接口, 包括以下功能：
*
*  1 - 添加观察者对象。
*  2 - 移除观察者对象。
*  3 - 通知观察者对象。
*
* Copyright (C) 2016 www.firemail.wang
*
* 版权所有 (C) 2016 着魔科技
*
*@author hechengjin
*
*@version 1.0
*
*@date 2016-06-14
*
*@changelog
*	22016-06-14 何成进 初始化
*
*/

#ifndef __ISUBJECT_H__
#define __ISUBJECT_H__

#include "IObserver.h"

/**
*    观察者接口类。
*/
class ISubject
{
public:
	/**
	*	添加观察者
	*@param pObserver
	*	[in] 观察者对象指针
	*@return void
	*	无
	*/
	virtual void Attach(IObserver *pObserver) = 0; 

	/**
	*	添加观察者
	*@param pObserver
	*	[in] 观察者对象指针
	*@return void
	*	无
	*/
	virtual void Remove(IObserver *pObserver) = 0;

	/**
	*	通知观察者
	*@param 
	*@return void
	*	无
	*/
	virtual void Notify() = 0;
};

#endif // __ISUBJECT_H__

