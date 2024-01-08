#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkNode.h"

typedef struct DataType{
	int key;
	void* value;
}DataType;

typedef struct HashMap{
	int size;
	LinkNode* table;
}HashMap;

//int hash(HashMap* hashmap,int k);

// ����һ��hash����ָ�����Ĵ�С
HashMap* createHash(int size);

//��hash���л�ȡ����
void* getData(HashMap* hashmap,int key);

//��hash���з�������
void putData(HashMap* hashmap,int key,void* value);

//����hash��
void destoryHashMap(HashMap* hashmap);

int constainsKey(HashMap* hashmap,int key);