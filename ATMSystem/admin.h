#ifndef __ADMIN_H_
#define __ADMIN_H_

#pragma once

typedef struct Admin{
	char time[30];  // ����Ա����ʱ��
	char adminName[10];  // ����Ա����
	char passWord[7];  // ����Ա����
}Admin;
// ����Ա������ע�ᣬ��ʱֻ���Ѿ��涨�õĹ���Ա�˺�
void showAllUser();

void showSignalUser();

void showBankMoney();

void assistUserChangePW();

//����Ա�ĵ�¼
void adminLogin();

#endif