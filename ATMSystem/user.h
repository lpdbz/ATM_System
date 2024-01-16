#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"hashmap.h"

typedef struct user{
	int accountCard;//�˻�����
	char accountName[10];//�˻�����
	char mobile[12];//�ֻ�����
	char sfz[19];//���֤
	char password[7];//����  �������룬�ڿ���̨����ʾ��*����
	double money;//�˻����
}user;

typedef struct Customer{

	int accountCard;//�˻�����
	char accountName[10];//�˻�����
	char mobile[12];//�ֻ�����
	char sfz[19];//���֤
	char password[7];//����  �������룬�ڿ���̨����ʾ��*����
	double money;//�˻����
}Customer;


//��ʼ��user
void initUser();

//��¼
void login();

//ע��
void sign();

//�޸��û���Ϣ
void updateInfo();
//�޸�����
void changePW();

// ȡ��ҵ��
void drawMoneyLogical();

//���ҵ��
void saveMoneyLogical();

//��ѯ���
void showMoney();

//ת��
void transferMoney();
//���䶯��¼
void balanceChange();

//�û���־logs��¼
void userLogsRecords(Customer *custTmp,char *oper);

//ע��ʱ�û�Դ��Ϣ�����ļ�
void user_filePut(Customer *custTmp);

//����ʱ�û�Դ��Ϣ�����ļ�
void userUpgrade_filePut(LinkNode* head,LinkNode* time);

void userLink_fileGet(HashMap *hashmap,LinkNode *head,int userNum);