#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include"hashmap.h"

//���ļ���ȡ���û���Ϣ
void user_fileGet(){
	FILE *fp;
	Customer custTmp;
	//HashNode* node = &(hashmap->table[0]);
	fp = fopen("�û�Դ��Ϣ.txt","r");
	if(fp == NULL){
		perror("���ļ�ʧ����");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%d %s %s %s %s %lf\n",&custTmp.accountCard,&custTmp.accountName,&custTmp.mobile,&custTmp.sfz,&custTmp.password,&custTmp.money)==6){
				putData(hashmap,custTmp.accountCard,&custTmp);
				userNum++;
			}else{
				printf("��ʱû���κ�ѧ����Ϣ������¼�룡\n");
				system("pause");
			}
		}
	fclose(fp);
}

//���û�����Ϣ�����ļ���
void user_filePut(){
	FILE *fp;
	Customer* custTmp;
	LinkNode* node = nextNode(head);

	fp = fopen("�û�Դ��Ϣ.txt","w+");
	while(node){
		custTmp = (Customer *)&node->data;
		fprintf(fp,"%d %s %s %s %s %lf\n",custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
		node = node->next;
	}
	fclose(fp);
	return;
}

//�����䶯����Ϣ���û���¼����Ϣ�����ļ���

//���ļ���ȡ�����䶯��Ϣ



//���ļ���ȡ�����䶯��Ϣ

//������Ա������־�ļ������ļ���
void admin_filePut(char* ch){
	FILE *fp;

	fp = fopen("����Ա������־�ļ�.txt","w+");
	fprintf(fp,"%s\n",ch);
	fclose(fp);
	return;
}

//���ļ���ȡ������Ա������־
void admin_fileGet(){
	FILE *fp;
	char ch[10];
	fp = fopen("����Ա������־�ļ�.txt","r");
	if(fp == NULL){
		perror("���ļ�ʧ����");
		system("pause");
		exit(1);
	}
	while(!feof(fp)){
		if(fscanf(fp,"%s\n",&ch)==1){
				printf("����Ա�Ĳ���Ϊ��%s",ch);
			}else{
				printf("����Ա��ʱû�в�����\n");
				system("pause");
			}
		}
	fclose(fp);
}