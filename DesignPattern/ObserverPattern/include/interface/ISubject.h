/**
*@file ISubject.h
*
*@brief ����ӿ�, �������¹��ܣ�
*
*  1 - ��ӹ۲��߶���
*  2 - �Ƴ��۲��߶���
*  3 - ֪ͨ�۲��߶���
*
* Copyright (C) 2016 www.firemail.wang
*
* ��Ȩ���� (C) 2016 ��ħ�Ƽ�
*
*@author hechengjin
*
*@version 1.0
*
*@date 2016-06-14
*
*@changelog
*	22016-06-14 �γɽ� ��ʼ��
*
*/

#ifndef __ISUBJECT_H__
#define __ISUBJECT_H__

#include "IObserver.h"

/**
*    �۲��߽ӿ��ࡣ
*/
class ISubject
{
public:
	/**
	*	��ӹ۲���
	*@param pObserver
	*	[in] �۲��߶���ָ��
	*@return void
	*	��
	*/
	virtual void Attach(IObserver *pObserver) = 0; 

	/**
	*	��ӹ۲���
	*@param pObserver
	*	[in] �۲��߶���ָ��
	*@return void
	*	��
	*/
	virtual void Remove(IObserver *pObserver) = 0;

	/**
	*	֪ͨ�۲���
	*@param 
	*@return void
	*	��
	*/
	virtual void Notify() = 0;
};

#endif // __ISUBJECT_H__

