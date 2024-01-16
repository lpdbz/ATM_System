#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"
#include"user.h"
#include"time.h"

#define N 10
int userNum = 0;

HashMap* hashmap;
LinkNode* head;
LinkNode* time;
Customer* custCurrent;//�洢��ǰ�û�����Ϣ��ÿһ���޸��û���Ϣ�󣬶�Ӧ�����¸�һ��ֵ

//ÿ����ز���������Ҫ��ӡƾ����Ҳû��д

void initUser(){
	hashmap = createHash(N);
	head = createNode();
	time = createNode();
	userLink_fileGet(hashmap,head,userNum);
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
		//printf("��¼ʱ��ȡhashmap�Ĵ�ӡ�����п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
		//ȥ��¼�в��ң����1.�Ƿ���ڴ˿��ţ�2.�����Ƿ���ȷ
		if(user!=NULL){
			//��������Ƿ�������ȷ
			custCurrent = user; //���ҳɹ����ͽ����ҵ�����Ϣ��ֵһ�ݸ�custCurrent�����ں���һֱ�õ��û�����Ϣ
			if(strcmp(password,user->password)==0){
				//���û���Ϣ��¼����־logs��¼�ļ���
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
	Customer* user = (Customer*)malloc(sizeof(Customer));
	char pw[7];

	printf("��ӭ����ע�����\n");	
	printf("������������������  �ֻ�����  ���֤:\n");
	scanf("%s %s %s",&user->accountName,&user->mobile,&user->sfz);
	user->accountCard = atoi(user->sfz);

	if(constainsKey(hashmap,user->accountCard)){
		printf("�û��Ѵ��ڣ���ȥ��¼\n");
		return;
	}

	printf("ע��ɹ����������п���Ϊ��%d\n",user->accountCard);
	while(1){
		printf("�������������п�����(6λ��):\n");
		scanf("%s",&user->password);
		printf("���ٴ�����������п�����:\n");
		scanf("%s",&pw);
		if(strcmp(user->password,pw) != 0){
			printf("�����������벻һ�£�����������\n");
			continue;
		}else{
			break;
		}
	}
	user->money = 0.0;//ע���ʱ���û������Ϊ0
	putData(hashmap,user->accountCard,user);
	addNode(head,user);
	user_filePut(user);
	printf("��������������ȷ�����п�ע��ɹ�!\n");
	return;
}

//�޸��û���Ϣ
void updateInfo(){
	int i=0;
	int flag = 1;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	Customer *user_1 = (Customer*)getData(hashmap,custCurrent->accountCard);
	user_1 = custCurrent;

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
	updateNode(head,custCurrent,user_1,sizeof(user_1));//�����º���û���Ϣ��Ҳ�������и���һ��
	userUpgrade_filePut(head,time);
	printf("�޸��û���Ϣ�ɹ��� ");
	system("pause");
	//���޸ĺ����Ϣ��¼���û�Դ��Ϣ�С�
	return;
}

//�޸�����
void changePW(){
	char passWord[7],passWord_1[7];
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
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
	updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
	userUpgrade_filePut(head,time);
	printf("�����޸ĳɹ���\n");
}

void drawMoney(){
	int money;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("����������Ҫȡ��Ľ��(ֻ��ȡ������Ԫ)\n");

	scanf("%d",&money);
	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		if(money <= custCurrent->money){
			printf("��������㹻������Ϊ��ȡ��\n");
			custCurrent->money -= money;
			putData(hashmap,custCurrent->accountCard,custCurrent);
			updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
			userUpgrade_filePut(head,time);
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
	char* time2;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("��ӭ����������\n");
	printf("��������Ҫ�洢��Ǯ(ֻ�洢����Ԫ)\n");
	scanf("%f",&money);

	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		custCurrent->money += money;
		//printf("put��hashmapǰ�Ĵ�ӡ�����п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",custCurrent->accountCard,custCurrent->accountName,custCurrent->mobile,custCurrent->sfz,custCurrent->money);
		putData(hashmap,custCurrent->accountCard,custCurrent);
		updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
		// �޸ĵ���Ϣ����Դ��Ϣ�ļ�ʱ����Ҫԭ����ʱ�䣬��������ȡ����ʱ��������
		time2 = (char *)(time->next->data);
		printf("��ӡ��ȡ���ļ�ʱ��ʱ�䣺%s",time2);
		userUpgrade_filePut(head,time);

		//�޸ĵ���ϢӦ�ô�����־�ļ���
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
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;

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
							updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
							userUpgrade_filePut(head,time);
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
//���䶯��¼--
void balanceChange(){
	
}

//�û���¼��¼
void userLoginRecords(){
	
}

void userLink_fileGet(HashMap *hashmap,LinkNode *head,int userNum){
	FILE *fp;
	Customer custTmp,*user;
	char time1[30];
	char* time2 = (char*)malloc(30 * sizeof(char)); // Ϊÿ��ʱ�����һ���µ��ڴ�ռ�
	userNum = 0;
	user = (Customer*)malloc(sizeof(Customer));

	fp = fopen("�û�Դ��Ϣ�ļ�.txt","r");
	if(fp == NULL){
		perror("���ļ�ʧ����");
		system("pause");
		exit(1);
	}

	while(!feof(fp)){
		if(fscanf(fp,"%s %d %s %s %s %s %lf\n",&time1,&custTmp.accountCard,&custTmp.accountName,&custTmp.mobile,&custTmp.sfz,&custTmp.password,&custTmp.money)==7){
				*user = custTmp;
				strcpy(time2, time1); // �� time1 ��ֵ���Ƶ��µ��ڴ�ռ���
				putData(hashmap,custTmp.accountCard,user);
				addNode(head,user);
				addNode(time,time2);
				userNum++;
			}else{
				printf("��ʱû���κ�ѧ����Ϣ������¼�룡\n");
				system("pause");
			}
		}
	fclose(fp);
}

//ע�᣺���û�����Ϣ�����ļ���
void user_filePut(Customer *custTmp){
	FILE *fp;
	char time[30];
	fp = fopen("�û�Դ��Ϣ�ļ�.txt","a");
	currentTime(time);
	fprintf(fp,"%s %d %s %s %s %s %f\n",time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	fclose(fp);
	return;
}

//���£���ȡ�ת�ˡ��޸��û���Ϣ���޸����룩ʱ�û�Դ��Ϣ�����ļ�
void userUpgrade_filePut(LinkNode* head,LinkNode* time){
	FILE *fp;
	Customer *custTmp;
	char* time1;
	fp = fopen("�û�Դ��Ϣ�ļ�.txt","w");
	while(nextNode(head)){
		custTmp = (Customer*)head->data;
		nextNode(time);
		time1 = (char*)(time->data);
		fprintf(fp,"%s %d %s %s %s %s %f\n",time1,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	}
}