/**
*@file IObserver.h
*
*@brief �۲��߽ӿ�, �������¹��ܣ�
*
*  1 - �۲�Ķ������仯ʱ���õ�֪ͨ���Զ����¡�
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

#ifndef __IOBSERVER_H__
#define __IOBSERVER_H__


/**
*    �۲��߽ӿ��ࡣ
*/
class IObserver
{
public:

	/**
	*   ��ע�����ⷢ���仯ʱ�ĸ�����Ӧ������
	*@param
	*@return void
	*/
	virtual void Update() = 0;
};

#endif // __IOBSERVER_H__
