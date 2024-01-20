#include<stdio.h>
#include<stdlib.h>
#include"linkNode.h"
#include"user.h"
#include"hashmap.h"
#include"time.h"

HashMap* hashmap;//��һ�����е�ʱ�򣬻���ļ��ж�ȡ�����û�����ע���ʱ�򣬲��������ļ���д��һ�ݣ�Ҳ����hashmapд��һ��
LinkNode* head;//headͬhashmapһ����head��hashmap��ָ������洢��ͬһ���ַ�������Ի�ȡ�޸�ͬһ���ַ��������ݣ�
char adminName[5] = "root";
char adminPW[5] = "root";

static void adminLogsRecords(char *adminName,char *adminPW,char *oper);

//����Ա�ĵ�¼
void adminLogin(){
	char adminName_login[5];
	char adminPW_login[5];
	while(1){
		printf("���������Ա�˺ţ�\n");
		scanf("%s",adminName_login);
		printf("���������Ա���룺\n");
		scanf("%s",adminPW_login);
		if(strcmp(adminName,adminName_login)==0 && strcmp(adminPW,adminPW_login)==0){
			printf("����Ա��¼�ɹ�\n");
			break;
		}else{
			printf("�˺Ż��������\n");
		}
	}

}

//�鿴�����û�
void showAllUser(){
	//ֱ�Ӵ�ӡlinknode����
	LinkNode *node;
	char *oper = "�鿴�����û���Ϣ";  // ��¼������д����־�ļ�
	Customer* user;
	node = nextNode(head);
	printf("�����û���Ϣ��\n");
	while(node){
		user = (Customer*)malloc(sizeof(Customer));
		user = ((Customer*)((DataType*)node->data)->value);
		printf("�˺ſ���ʱ�䣺%s,�˻����ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺%s���˻���%f\n",user->Time,user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
		node = nextNode(node);
	}
	adminLogsRecords(adminName,adminPW,oper);
}

//�鿴�����û�����Ϣ�Ͳ�����¼
void showSignalUser(){
	int accountCard; // �˻�����
	char *oper = "�鿴�����û���Ϣ";
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("��������Ҫ�鿴�û���Ϣ�������˺ţ�\n");
	scanf("%d",&accountCard);

	while(1){
		if((Customer*)getData(hashmap,accountCard) != NULL){
			user = (Customer*)getData(hashmap,accountCard);
			printf("����Ҫ�鿴���˻����� %d���û���Ϣ�ǣ��˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺%s���˻���%f\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->password,user->money);
			break;
		}else{
			printf("��Ǹ������ҵ��û������ڡ����������\n");
			continue;
		}
	}
	adminLogsRecords(adminName,adminPW,oper);
}

//�鿴����������仯--���䶯��¼�Ǽ�¼�����û�ÿһ�β����˽��仯�����ȡ������������ļ�չʾ����������������һ��
//������¼�ܽ��仯����
void showBankMoney(){
	char *oper = "�鿴����������仯";
	double BankMoney;//��¼�����ܽ��仯
	Customer* user = (Customer*)malloc(sizeof(Customer));
	printf("�˻�����Ϊ %d������¼�ǣ����|ȡ��|ת�ˣ�%d���˻��ܽ��Ϊ��%lf\n",user->accountCard,user->money,BankMoney);
	adminLogsRecords(adminName,adminPW,oper);
	return;
}

// �����û��޸�����
void assistUserChangePW(){
	int accountCard; // �˻�����
	char originPW[7]; // �˺�ԭ����
	char password[7],password_confirm[7]; // �޸�������޸������ȷ������
	char *oper = "�����û��޸�����";
	Customer* user = (Customer*)malloc(sizeof(Customer));
	while(1){
		printf("��������Ҫ�޸�����������˺ţ�\n");
		scanf("%d",&accountCard);
		printf("��������Ҫ�޸������ԭ���룺\n");
		scanf("%s",&originPW);
		user = (Customer*)getData(hashmap,accountCard);
		if(user != NULL){
			if(strcmp(user->password,originPW) == 0){
				printf("�˺�����ƥ��ɹ���\n");
				printf("����������Ҫ�޸ĵ�����\n");
				scanf("%s",&password);
				printf("���ٴ���������Ҫ�޸ĵ�����\n");
				scanf("%s",&password_confirm);
				if(strcmp(user->password,password_confirm) != 0){
					if(strcmp(password_confirm,password) == 0){
						printf("������������һ��\n");
						break;
					}else{
						printf("������������벻һ�£����������");
						continue;
					}
				}else{
					printf("�޸����벻����ԭ����һ�£�\n");
					continue;
				}
			}else{
				printf("���û������������\n");
				continue;
			}
		}else{
			printf("��Ǹ������ҵ��û������ڡ����������\n");
			continue;
			}
	}
	strcpy(user->password,password_confirm); // user�Ѿ�ָ����hashmap��Ϊʲô����ֱ���޸�
	printf("�����޸ĳɹ���\n");
	userUpgrade_filePut(head);
	adminLogsRecords(adminName,adminPW,oper);
	return;
}

//���ļ���ȡ������Ա������־
void admin_fileGet(){
	FILE *fp;
	char ch[10],time[30];
	fp = fopen("����Ա������־�ļ�.txt","r");
	if(fp == NULL){
		perror("���ļ�ʧ����");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%s\n",&ch)==1){
				printf("����Ա�Ĳ���Ϊ��%s %s",time,ch);
			}else{
				printf("����Ա��ʱû�в�����\n");
				system("pause");
			}
		}
	fclose(fp);
}

//������Ա������־�ļ������ļ���
static void adminLogsRecords(char *adminName,char *adminPW,char *oper){
	FILE *fp;
	char time[30];
	fp = fopen("����Ա������־�ļ�.txt","a");
	currentTime(time);
	fprintf(fp,"%s %s %s %s\n",time,adminName,adminPW,oper);
	fclose(fp);
	return;
}