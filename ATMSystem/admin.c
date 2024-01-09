#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"user.h"
#include"hashmap.h"

HashMap *hashmap;

//�鿴�����û�
void showAllUser(){
	//ֱ�Ӵ�ӡlinknode����
	LinkNode* head,*node;
	Customer* user = (Customer*)malloc(sizeof(Customer));
	node = nextNode(head);
	printf("�����û���Ϣ��\n");
	while(node){
		user = (Customer*)node->data;
		printf("�˻����ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺%s���˻���%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
		node = nextNode(node);
	}
}

//�鿴�����û�����Ϣ�Ͳ�����¼
void showSignalUser(int accountCard){
	Customer* user = (Customer*)malloc(sizeof(Customer));
	user = (Customer*)getData(hashmap,accountCard);
	//��ô��������¼�أ�Ӧ�ý�������¼���ļ��У�Ȼ������ļ��ж�Ӧ��accountCard
	printf("����Ҫ�鿴���˻����� %d���û���Ϣ�ǣ��˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺%s���˻���%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
}

//�鿴����������仯--���䶯��¼�Ǽ�¼�����û�ÿһ�β����˽��仯�����ȡ�ת�˲����������ļ�չʾ����������������һ��
//������¼�ܽ��仯����
void showBankMoney(){
	double BankMoney;//��¼�����ܽ��仯
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("�˻�����Ϊ %d������¼�ǣ����|ȡ��|ת�ˣ�%d���˻��ܽ��Ϊ��%lf\n",user->accountCard,user->money,BankMoney);
	return;
}

//�����û��޸�����
void assistUserChangePW(int accountCard){
	char password[7],password_confirm[7];
	Customer* user = (Customer*)malloc(sizeof(Customer));
	user = (Customer*)getData(hashmap,accountCard);
	printf("����������Ҫ�޸ĵ�����\n");
	scanf("%s",&password);
	printf("���ٴ���������Ҫ�޸ĵ�����\n");
	scanf("%s",&password_confirm);
	if(strcmp(password_confirm,password) == 0){
		printf("������������һ��\n");
		strcpy(user->password,password);
		putData(hashmap,accountCard,user);
		printf("�����޸ĳɹ���\n");
	}
	return;
}