#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"
#include"hashmap.h"
#define N 100
int userNum = 0;
HashMap* hashmap;
LinkNode* head;
Customer* custCurrent;//�洢��ǰ�û�����Ϣ��ÿһ���޸��û���Ϣ�󣬶�Ӧ�����¸�һ��ֵ

void initUser(){
	hashmap = createHash(N);
	head = createNode();
}

//��¼
void login(){
	int accountCard;
	char password[7];
	Customer* user;

	printf("��ӭ������¼����\n");
	printf("�������������п��ź�����:\n");

	while(1){
		scanf("%d %s",&accountCard,&password);
		user = (Customer*)getData(hashmap,accountCard);
		//ȥ��¼�в��ң����1.�Ƿ���ڴ˿��ţ�2.�����Ƿ���ȷ
		if(user!=NULL){
			//��������Ƿ�������ȷ
			custCurrent = user; //���ҳɹ����ͽ����ҵ�����Ϣ��ֵһ�ݸ�custCurrent�����ں���һֱ�õ��û�����Ϣ
			if(strcmp(password,user->password)==0){
				//���û���Ϣ��¼���û���¼��¼�ļ���
				printf("��¼�ɹ���������������Ĳ���\n");
				return;	
			}
		}else{
			printf("���п��ź���������������������룺\n");
		}
	}
}

//ע��
void sign(){
	Customer* cust = (Customer*)malloc(sizeof(Customer));
	char pw[7];

	printf("��ӭ����ע�����\n");	
	printf("������������������  �ֻ�����  ���֤:\n");
	scanf("%s %s %s",&cust->accountName,&cust->mobile,&cust->sfz);
	cust->accountCard = atoi(cust->sfz);

	if(constainsKey(hashmap,cust->accountCard)){
		printf("�û��Ѵ��ڣ���ȥ��¼\n");
		return;
	}

	printf("ע��ɹ����������п���Ϊ��%d\n",cust->accountCard);
	while(1){
		printf("�������������п�����(6λ��):\n");
		scanf("%s",&cust->password);
		printf("���ٴ�����������п�����:\n");
		scanf("%s",&pw);
		if(strcmp(cust->password,pw) != 0){
			//ע��ɹ�����Ҫ����ע����û���Ϣ��¼����
			printf("�����������벻һ�£�����������\n");
			continue;
		}else{
			break;
		}
	}
	cust->money = 0.0;//ע���ʱ���û������Ϊ01
	putData(hashmap,cust->accountCard,cust);
	filePut();
	printf("��������������ȷ�����п�ע��ɹ�!\n");
	return;
}

//�޸��û���Ϣ
void updateInfo(){
	int i=0;
	int flag = 1;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);

	printf("��ӭ�����޸ĸ�����Ϣ����:\n");
	printf("������ϢΪ��");
	printf("���п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	
	while(flag){
		printf("������Ҫ�޸�ʲô��Ϣ��\n");
		printf("1 �޸��˻�����\n");//��Щ�˸�����
		printf("2 �޸ĵ绰����\n");
		printf("3 �޸�����\n");//��Ϊ���޸���Ϣ��ʱ������Ҳ���ڸ�����Ϣ��Ӧ�ü���
		printf("0 �˳��޸ĸ�����Ϣ����\n");

		scanf("%d",&i);
		switch(i){
		case 1:printf("�������˻�����:\n");scanf("%s",&user->accountName);break;
		case 2:printf("������绰����:\n");scanf("%s",&user->mobile);break;
		case 3:printf("������Ҫ�޸ĵ�����:\n");scanf("%s",&user->password);break;
		case 0:flag = 0;break;//��ô�˳��أ���ִ�к�������
		default:printf("���������������Ӧ��ֵ");
		}
		printf("������ϢΪ��");
		printf("���п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	}
	custCurrent = user;
	//printf("���п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺%s����%lf\n\n",custCurrent->accountCard,custCurrent->accountName,custCurrent->mobile,custCurrent->sfz,custCurrent->password,custCurrent->money);
	
	putData(hashmap,user->accountCard,user);
	//updateNode(head,newData,oldData,size);//ΪʲôҪ������Ҳ��һ������
	printf("�޸��û���Ϣ�ɹ��� ");
	system("pause");
	//���޸ĺ����Ϣ��¼���û�Դ��Ϣ�С�
	return;
}

//�޸�����
void changePW(){
	char passWord[7],passWord_1[7];
	printf("��ӭ�����޸��������\n");
	while(1){
		printf("������ԭ����:\n");
		scanf("%s",&passWord);

		if(strcmp(passWord,custCurrent->password) == 0){
			printf("����������Ҫ�޸ĵ�����:\n");
			scanf("%s",&passWord_1);
			if(strcmp(passWord,passWord_1)==0){
				printf("�����޸�Ϊԭ���룡�����²���\n");
				continue;
			}else{
				break;
			}
		}else{
			printf("ԭ����������������²���\n");
			continue;
		}
	}
	strcpy(custCurrent->password,passWord_1);
	putData(hashmap,custCurrent->accountCard,custCurrent);
	printf("�����޸ĳɹ���\n");
}

void drawMoney(){
	int money;
	printf("����������Ҫȡ��Ľ��(ֻ��ȡ������Ԫ)\n");

	scanf("%d",&money);
	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		if(money <= custCurrent->money){
			printf("��������㹻������Ϊ��ȡ��\n");
			custCurrent->money -= money;
			putData(hashmap,custCurrent->accountCard,custCurrent);
			printf("ȡ��ɹ���\n");
			printf("�������п���Ϊ��%d,���ڵ����Ϊ:%f\n",custCurrent->accountCard,custCurrent->money);
		}else{
			printf("�������㣬�޷�ȡ������Ҫ��Ǯ�������²���\n");
		}
	}else{
		printf("��ȡ����Ǯ�������٣�����������\n");
	}
}

// ȡ��ҵ��
void drawMoneyLogical(){
	int i=0,flag=1;
	printf("��ӭ����ȡ�����\n");
	while(flag){
		printf("1 ȡ��\n");
		printf("2 �˳�\n");
		scanf("%d",&i);
		switch(i){
		case 1:drawMoney();break;
		case 2:flag=0;break;
		default:printf("�����������������룡\n");break;
		}
	}
	return;
}

//���ҵ��
void saveMoney(){
	float money;
	printf("��ӭ����������\n");
	printf("��������Ҫ�洢��Ǯ(ֻ�洢����Ԫ)\n");
	scanf("%f",&money);

	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		custCurrent->money += money;
		putData(hashmap,custCurrent->accountCard,custCurrent);
		printf("�洢�ɹ���\n");
		printf("�������п���Ϊ��%d,���ڵ����Ϊ:%f\n",custCurrent->accountCard,custCurrent->money);
	}else{
		printf("���洢��Ǯ�����������������´洢���ٵ�Ǯ\n");
	}
	return;
}

void saveMoneyLogical(){
	int i=0,flag=1;
	printf("��ӭ����������\n");
	while(flag){
		printf("1 ���\n");
		printf("2 �˳�\n");
		scanf("%d",&i);
		switch(i){
		case 1:saveMoney();break;
		case 2:flag=0;break;
		default:printf("�����������������룡\n");break;
		}
	}
	return;
}

//��ѯ���
void showMoney(){
	printf("��ӭ������ѯ������\n");

	printf("�������п���Ϊ:%d\n",custCurrent->accountCard);
	printf("�������Ϊ:%lf\n",custCurrent->money);
	return;
}

//ת��
void transferMoney(){
	Customer* custTMP_1;
	int flag,accountCard;
	char accountName[10];
	float money=0;

	printf("��ӭ����ת�˽���\n");
	printf("����������Ҫת�˵��˺� ����\n");
	scanf("%d %s",&accountCard,&accountName);

	if((custTMP_1 = (Customer*)getData(hashmap,accountCard)) != NULL){
		//�˺Ŵ��ڣ���ʼУ������,get�������ض�Ӧ���ŵ��û���Ϣ
		if(strcmp(accountName,accountName) == 0){
			printf("��Ҫת�˵��û���Ϊ��%s\n",custTMP_1->accountName);

			printf("������ת�˽��:\n");
			scanf("%f",&money);
			//������ȷ��ת����ʵҲ������һ�����棨�Ż���
			printf("ȷ��ת��������1����������ȡ��ת��\n");
			scanf("%d",&flag);
			if(flag==1){
				//����У���Լ����˻��Ƿ����㹻ת�˵Ľ��
				if(((int)money)/100 != 0 && ((int)money)%100 == 0){
						if((custCurrent->money - money) >= 0){
							custCurrent->money -= money;
							custTMP_1->money += money;
							putData(hashmap,custCurrent->accountCard,custCurrent);
							putData(hashmap,custTMP_1->accountCard,custTMP_1);
							printf("ת�˳ɹ���");
					}else{
						printf("�����˻�������\n");
						return;
					}
				}
			}else{
				printf("ȡ��ת�ˣ�\n");
				return;
			}
		}
	}else{
		printf("��������˺Ų����ڣ�");
		return;
	}
}

//�������ǲ���д�����ĺ����ģ�Ӧ��Ƕ�뵽ת�ˡ���ȡ���ܺ����С�
//���䶯��¼
void balanceChange(){
	
}

//�û���¼��¼
void userLoginRecords(){
	
}

//���û�����Ϣ�����ļ���
void filePut(){
	FILE *fp;
	int i = 0;
	Customer* custTmp;
	LinkNode* node = &(hashmap->table[0]);

	fp = fopen("�û�Դ��Ϣ.txt","w+");
	while(node){
		custTmp = (Customer *)&node->data;
		fprintf(fp,"%d %s %s %s %s %lf\n",custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
		node = node->next;
	}
	fclose(fp);
	return;
}

//���ļ���ȡ���û���Ϣ
void fileGet(){
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
