#include<stdio.h>
#include<stdlib.h>

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

//�û���¼��¼
void userLoginRecords();

void filePut();

void fileGet();
