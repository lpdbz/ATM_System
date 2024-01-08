#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashmap.h"
#include"linkNode.h"

int hash(HashMap* hashmap,int k){
	k = abs(k) % hashmap->size;
	return k;
}

HashMap* createHash(int size){
	int i;
	HashMap *hashmap;
	hashmap = (HashMap*)malloc(sizeof(HashMap));

	hashmap->size = size;
	hashmap->table = (LinkNode*)malloc(size*sizeof(LinkNode));
	
	for(i=0;i<hashmap->size;i++){
		hashmap->table[i].data = NULL;
		hashmap->table[i].next = NULL;
	}
	return hashmap;
}


void* getData(HashMap* hashmap,int key){
	int pos;
	DataType* data;
	LinkNode* head,*node;

	//�õ�hashɢ��ֵ
	pos = hash(hashmap,key);

	//�õ�Ҫ�ҵ����ݵ�ͷ���
	head = &(hashmap->table[pos]);
	node = nextNode(head);
	//����������б����ҵ�key��ֵ
	while(node){
		data = (DataType *)(node->data);
		if(data->key == key){
			return data->value;
		}
		node = nextNode(node);
	}
	return NULL;	
}

void putData(HashMap* hashmap,int key,void* value){
	int pos;
	DataType* data;
	LinkNode* head;

	data = (DataType*)malloc(sizeof(DataType));
	data->key = key;
	data->value = value;
	//�õ�hashɢ��ֵ
	pos = hash(hashmap,key);
	head = &(hashmap->table[pos]);
	
	//���ҵ���ͷ����в�������
	addNode(head,data);
}


/*void printHashMap(HashMap* hashmap){
	int i;
	DataType* tmp;
	LinkNode* node = &(hashmap->table[0]);
	tmp = (DataType *)(hashmap->table[0].data);
	for(i=0;i<hashmap->size;i++){
		printf("hashmap��ֵΪ��[%d,%s]->",tmp->key,tmp->value);
		node = &(hashmap->table[i]);
		while(node->next){
			node = node->next;
			printf("[%d,%s]->",tmp->key,tmp->value);
		}
		printf("null\n\n");
	}
}*/

void destoryHashMap(HashMap* hashmap){
	LinkNode* head;
	int i;
	for(i=0;i<hashmap->size;i++){
		head = &(hashmap->table[i]);
		destoryLinkNode(head);
	}
	free(hashmap->table);
	free(hashmap);
}

int constainsKey(HashMap* hashmap,int key){
	return getData(hashmap,key) == NULL ? 0:1;
}

/*void main1111(){	
	int key,fkey;
	char value[10];
	HashMap *hashmap = createHash(10);
	while(1){
		printf("��������Ҫ�洢��key��value(����'q'�˳�����)\n");
		if(scanf("%d",&key)==1 && key >= 0 ){
			scanf("%s",&value);
			putData(hashmap,key,value);
		}else{
			printf("�����쳣ֵ���������룡\n");
			break;
		}
	}
	printHashMap(hashmap);

	printf("����������Ҫ�õ���key:\n");
	fflush(stdin);
	scanf("%d",&fkey);
	printf("fkey=%d\n",fkey);
	getData(hashmap,fkey);
	destoryHashMap(hashmap);
}*/