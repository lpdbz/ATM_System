#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"user.h"
#include"admin.h"


void sign_loginOperator(){
	int a,flag=1;
	initUser();

	while(flag){
		sign_loginMenu();
		printf("��ѡ��ע���¼������\n");
		scanf("%d",&a);
		switch(a){
		case 1:sign();system("pause");break;
		case 2:login();system("pause");flag=0;break;
		case 0:flag=0;break;//���ص���һ�����棬���������⣬���ص�����һ������
		default:printf("������������������\n");system("pause");
		}
		system("cls");
	}
}

void userOperator(){
	int flag=1,i;
	while(flag){
		userMenu();
		scanf("%d",&i);
		switch(i){
		case 1:saveMoneyLogical();system("pause");break;
		case 2:drawMoneyLogical();system("pause");break;
		case 3:transferMoney();system("pause");break;
		case 4:showMoney();system("pause");break;
		case 5:changePW();system("pause");break;
		case 6:updateInfo();system("pause");break;
		case 0:flag=0;system("pause");break;
		default:printf("������������������\n");
		}
		system("cls");
	}
}

void adminOperator(){
	int flag=1,i;
	initUser();

	while(flag){
		adminMenu();
		scanf("%d",&i);
		switch(i){
		case 1:showAllUser();system("pause");break;
		//case 2:showSignalUser(accountCard);system("pause");break;
		case 3:showBankMoney();system("pause");break;
		//case 4:assistUserChangePW(accountCard);system("pause");break;
		}
	}
	
}

void main(){
	int id,flag=1;
	while(flag){
		menu();
		printf("��ѡ���û������Ա����\n");
		scanf("%d",&id);
		switch(id){
		case 1:sign_loginOperator();userOperator();break;
		case 2:adminOperator();break;
		case 0:flag=0;break;
		default:printf("������������������");break;
		}
		system("cls");
	}
}
