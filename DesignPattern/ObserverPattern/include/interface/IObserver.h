/**
*@file IObserver.h
*
*@brief 观察者接口, 包括以下功能：
*
*  1 - 观察的对象发生变化时，得到通知并自动更新。
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

#ifndef __IOBSERVER_H__
#define __IOBSERVER_H__


/**
*    观察者接口类。
*/
class IObserver
{
public:

	/**
	*   关注的主题发生变化时的更新响应函数。
	*@param
	*@return void
	*/
	virtual void Update() = 0;
};

#endif // __IOBSERVER_H__
