#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"
#include"user.h"
#include"time.h"

#define N 10
int userNum = 0; // ��¼�������й��ж��ٸ��û�
static double BankTotalMoney = 0.0;

HashMap* hashmap;//��һ�����е�ʱ�򣬻���ļ��ж�ȡ�����û�����ע���ʱ�򣬲��������ļ���д��һ�ݣ�Ҳ����hashmapд��һ��
LinkNode* head;//headͬhashmapһ����head��hashmap��ָ������洢��ͬһ���ַ�������Ի�ȡ�޸�ͬһ���ַ��������ݣ�
Customer* custCurrent;//�洢��ǰ�û�����Ϣ��ÿһ���޸��û���Ϣ�󣬶�Ӧ�����¸�һ��ֵ

void initUser(){
	hashmap = createHash(N);
	head = createNode();
	user_fileGet(hashmap,head,userNum);
	Bank_TotalAmount_fileGet(BankTotalMoney);
}

//��¼
void login(){
	int accountCard;  // �洢��¼�û�������˺ţ����ں������˺űȽ�
	char password[7];  // �洢��¼�û���������룬���ں���������Ƚ�
	char *oper = "��¼";  // ��¼������д����־�ļ�
	printf("��ӭ������¼����\n");
	while(1){
		printf("�������������п��ź�����:\n");
		scanf("%d %s",&accountCard,&password);
		//ȥ��¼�в��ң����1.�Ƿ���ڴ˿��ţ�2.�����Ƿ���ȷ
		if((Customer*)getData(hashmap,accountCard)!=NULL){
			//��������������Ƿ�������ȷ
			custCurrent = (Customer*)getData(hashmap,accountCard); //���ҳɹ����ͽ����ҵ�����Ϣ��ֵһ�ݸ�custCurrent�����ں���һֱ�õ��û�����Ϣ
			if(strcmp(password,custCurrent->password)==0){
				//���û���Ϣ��¼����־logs��¼�ļ���
				userLogsRecords(custCurrent,oper);
				printf("��¼�ɹ���������������Ĳ���\n");
				return;	
			}else{
				printf("����������������²���\n");
			}
		}else{
			printf("���п��ź���������������������룺\n");
			continue;
		}
	}
}

//ע��
void sign(){
	char pw[7];  // ����ȷ������
	char *oper = "ע��";
	DataType* data = (DataType*)malloc(sizeof(DataType)); //�洢DataType���͵�data���ݣ�����key��value��value����Customer����
	Customer* user = (Customer*)malloc(sizeof(Customer)); //�洢ע���û���������Ϣ

	printf("��ӭ����ע�����\n");	
	printf("������������������  �ֻ�����  ���֤:\n");
	scanf("%s %s %s",&user->accountName,&user->mobile,&user->sfz);
	user->accountCard = atoi(user->sfz); // ���ַ������͵����֤ת��Ϊ�������͵������˺�

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
	user->money = 0.0;  // ע���ʱ���û������Ϊ0
	
	currentTime(user->Time);  // ��ȡ��ǰʱ�����user�У���ʾ�����û���ʱ��
	data->key = user->accountCard;
	data->value = (Customer *) malloc(sizeof(Customer));//data��valueҲ��Ҫmalloc����
    memcpy(data->value, user, sizeof(Customer));//��ע���û���Ϣ���ݸ��Ƶ�data->value��

	putData(hashmap,data); // ���ո�ע����û���Ϣ�洢��hashmap��
	addNode(head,data); // ���ո�ע����û���Ϣ�洢��head��
	user_filePut(user);
	userLogsRecords(user,oper);
	printf("��������������ȷ�����п�ע��ɹ�!\n");
	free(user);  // Ϊʲô����free����Ҳ������
	//free(data->value); // Ϊʲô����free����������
	//free(data);
	return;
}

//�޸��û���Ϣ 
void updateInfo(){
	char *oper = "�޸��û���Ϣ";
	int i=0;
	int flag = 1;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);

	printf("��ӭ�����޸ĸ�����Ϣ����:\n");
	printf("������ϢΪ��");
	printf("���п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	
	while(flag){
		printf("������Ҫ�޸�ʲô��Ϣ��\n");
		printf("1 �޸��˻�����\n");  // ��Щ�˸�����
		printf("2 �޸ĵ绰����\n");
		printf("3 �޸�����\n");  // ��Ϊ���޸���Ϣ��ʱ������Ҳ���ڸ�����Ϣ��Ӧ�ü���
		printf("0 �˳��޸ĸ�����Ϣ����\n");

		scanf("%d",&i);
		switch(i){
		case 1:printf("�������˻�����:\n");scanf("%s", &user->accountName);break;
		case 2:printf("������绰����:\n");scanf("%s", &user->mobile);break;
		case 3:printf("������Ҫ�޸ĵ�����:\n");scanf("%s", &user->password);break;
		case 0:flag = 0;break;
		default:printf("���������������Ӧ��ֵ");
		}
		printf("������ϢΪ��");
		printf("���п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",user->accountCard,user->accountName,user->mobile,user->sfz,user->money);
	}

	custCurrent = user;
	userUpgrade_filePut(head);
	userLogsRecords(user,oper);
	printf("�޸��û���Ϣ�ɹ��� ");
	system("pause");
	return;
}

//�޸�����
void changePW(){
	char *oper = "�޸�����";
	char passWord[7],passWord_1[7];
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);

	printf("��ӭ�����޸��������\n");
	while(1){
		printf("������ԭ����:\n");
		scanf("%s",&passWord);

		if(strcmp(passWord,user->password) == 0){
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
	strcpy(user->password,passWord_1);
	custCurrent = user;
	userUpgrade_filePut(head);
	userLogsRecords(user,oper);
	printf("�����޸ĳɹ���\n");
}

//ȡ��
void drawMoney(){
	char *oper = "ȡ��";
	int money;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("����������Ҫȡ��Ľ��(ֻ��ȡ������Ԫ)\n");

	scanf("%d",&money);
	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		if(money <= custCurrent->money){
			printf("��������㹻������Ϊ��ȡ��\n");
			custCurrent->money -= money;
			putData(hashmap,custCurrent);
			updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
			userUpgrade_filePut(head);
			userLogsRecords(custCurrent,oper);
			Bank_TotalAmountChange(oper,custCurrent,money);
			printf("ȡ��ɹ���\n");
			printf("�������п���Ϊ��%d,���ڵ����Ϊ:%f\n",custCurrent->accountCard,custCurrent->money);
		}else{
			printf("�������㣬�޷�ȡ������Ҫ��Ǯ�������²���\n");
		}
	}else{
		printf("��ȡ����Ǯ�������٣�����������\n");
	}
}

// ȡ���߼�ҵ��
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

//���
void saveMoney(){
	char *oper = "���";
	float money;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;
	printf("��ӭ����������\n");
	printf("��������Ҫ�洢��Ǯ(ֻ�洢����Ԫ)\n");
	scanf("%f",&money);

	if(((int)money)/100 != 0 && ((int)money)%100 == 0){
		custCurrent->money += money;
		//printf("put��hashmapǰ�Ĵ�ӡ�����п��ţ�%d���˻����ƣ�%s���ֻ����룺%s�����֤��%s�����룺******����%lf\n\n",custCurrent->accountCard,custCurrent->accountName,custCurrent->mobile,custCurrent->sfz,custCurrent->money);
		//putData(hashmap,custCurrent->accountCard,custCurrent);
		updateNode(head,custCurrent,user,sizeof(custCurrent));//�����º���û���Ϣ��Ҳ�������и���һ��
		// �޸ĵ���Ϣ����Դ��Ϣ�ļ�ʱ����Ҫԭ����ʱ�䣬��������ȡ����ʱ��������
		userUpgrade_filePut(head);
		userLogsRecords(custCurrent,oper);
		Bank_TotalAmountChange(oper,custCurrent,money);
		//�޸ĵ���ϢӦ�ô�����־�ļ���
		printf("�洢�ɹ���\n");
		printf("�������п���Ϊ��%d,���ڵ����Ϊ:%f\n",custCurrent->accountCard,custCurrent->money);
	}else{
		printf("���洢��Ǯ�����������������´洢���ٵ�Ǯ\n");
	}
	return;
}

//����߼�ҵ��
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
	char *oper = "��ѯ���";
	printf("��ӭ������ѯ������\n");

	printf("�������п���Ϊ:%d\n",custCurrent->accountCard);
	printf("�������Ϊ:%lf\n",custCurrent->money);
	userLogsRecords(custCurrent,oper);
	return;
}

//ת��--Ŀǰֻ�ܱ���ת�˱���
void transferMoney(){
	char oper[10] = "ת��";
	char oper1[10] = "ת��";
	Customer* custTMP_1;
	int flag,accountCard;
	char accountName[10];
	float money=0;
	Customer *user = (Customer*)getData(hashmap,custCurrent->accountCard);
	user = custCurrent;

	printf("��ӭ����ת�˽���\n");
	while(1){
		printf("����������Ҫת�˵��˺� ����\n");
		scanf("%d %s",&accountCard,&accountName);
		if((custTMP_1 = (Customer*)getData(hashmap,accountCard)) != NULL){
			//�˺Ŵ��ڣ���ʼУ������,get�������ض�Ӧ���ŵ��û���Ϣ
			if(strcmp(custTMP_1->accountName,accountName) == 0){
				printf("��Ҫת�˵��û���Ϊ��%s\n",custTMP_1->accountName);
				while(1){
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
									userUpgrade_filePut(head);
									userLogsRecords(custCurrent,oper);
									Bank_TotalAmountChange(strcat(oper,"����"),custCurrent,money);
									Bank_TotalAmountChange(strcat(oper1,"���շ�"),custCurrent,money);
									printf("ת�˳ɹ���");
									return;
								}else{
									printf("�����˻�������,����������\n");
									continue;
								}
						}else{
							printf("����������ת�˽��\n");
						}
					}else{
						printf("ȡ��ת�ˣ�\n");
						return;
					}
				}
			}else{
				printf("�����������˺Ŷ�Ӧ���˺��������ԣ�����������\n");
				continue;
			}
		}else{
			printf("��������˺Ų����ڣ�");
			return;
		}
	}
}

//�û�����־logs��¼
void userLogsRecords(Customer *custTmp,char *oper){
	FILE *fp;
	char time[30];
	fp = fopen("�û�logs��־�ļ�.txt","a");
	currentTime(time);
	fprintf(fp,"%s %d %s %s\n",time,custTmp->accountCard,custTmp->accountName,oper);
	fclose(fp);
	return;
}

// ���ļ��л�ȡȫ������Ϣ
void user_fileGet(HashMap *hashmap, LinkNode *head, int userNum) {
    FILE *fp;
    Customer custTmp;
    DataType *user;

    fp = fopen("�û�Դ��Ϣ�ļ�.txt", "r");
    if (fp == NULL) {
        perror("���ļ�ʧ����");
        system("pause");
        exit(1);
    }

    while (!feof(fp)) {
        if (fscanf(fp, "%s %d %s %s %s %s %lf\n", &custTmp.Time, &custTmp.accountCard, &custTmp.accountName, &custTmp.mobile, &custTmp.sfz, &custTmp.password, &custTmp.money) == 7) {
            user = (DataType *) malloc(sizeof(DataType));
            user->value = (Customer *) malloc(sizeof(Customer));
            memcpy(user->value, &custTmp, sizeof(Customer));//��custTmp��ֵ���Ƶ�user->value��
            user->key = custTmp.accountCard;
            putData(hashmap, user);
            addNode(head, user);
            userNum++;
        } else {
            printf("��ʱû���κ�ѧ����Ϣ������¼�룡\n");
            system("pause");
        }
    }
    fclose(fp);
}


//ע�᣺���û�����Ϣ�����ļ���
void user_filePut(Customer *custTmp){
	FILE *fp;
	
	fp = fopen("�û�Դ��Ϣ�ļ�.txt","a");
	fprintf(fp,"%s %d %s %s %s %s %f\n",custTmp->Time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	fclose(fp);
	return;
}

// ��¼����������仯
// ���money�ǽ��н�Ǯ�����Ľ��
void Bank_TotalAmountChange(char *oper,Customer *custTmp,double money){
	FILE *fp;
	char time[30];
	currentTime(time);
	if(strcmp(oper,"���")){
		BankTotalMoney += money;
	}else if(strcmp(oper,"ȡ��")){
		BankTotalMoney -= money;
	}
	fp = fopen("�����ܽ��仯�ļ�.txt","a");
	fprintf(fp,"%s %d %s %f %f\n",time,custTmp->accountCard,oper,money,BankTotalMoney);
	fclose(fp);
	return;
}

// �������ܽ���ļ��л�ȡȫ������ϢBank_TotalAmountChange;
void Bank_TotalAmount_fileGet(double BankTotalMoney) {
    //double BankTotalMoney = 0;
    char line[256];
    char *last_line = NULL;
    FILE *fp = fopen("�����ܽ��仯�ļ�.txt", "r");
    if (fp == NULL) {
        perror("���ļ�ʧ����");
        system("pause");
        exit(1);
    }
    while (fgets(line, sizeof(line), fp)) {
        last_line = strdup(line);
    }

    if (last_line != NULL) {
        char *last_num_str = strrchr(last_line, ' ');
        if (last_num_str != NULL) {
            BankTotalMoney = atoi(last_num_str);
        }
        free(last_line);
    }

    printf("The last number in the file is: %lf\n", BankTotalMoney);
    fclose(fp);
    return;
}


// ���£���ȡ�ת�ˡ��޸��û���Ϣ���޸����룩ʱ�û�Դ��Ϣ�����ļ�
// ��ʱû���õ���ֱ����ָ��ָ����Ƭ��ַ��Ȼ���޸���
void userUpgrade_filePut(LinkNode* head){
	FILE *fp;
	Customer *custTmp;
	DataType *user;
	fp = fopen("�û�Դ��Ϣ�ļ�.txt","w");
	while(nextNode(head)){
		head = nextNode(head);
		user = ((DataType*)head->data);
		custTmp = (Customer*)user->value;
		fprintf(fp,"%s %d %s %s %s %s %f\n",custTmp->Time,custTmp->accountCard,custTmp->accountName,custTmp->mobile,custTmp->sfz,custTmp->password,custTmp->money);
	}
	fclose(fp);
}