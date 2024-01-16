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

//�����hashmap���Ѿ����ڵ�key�أ�����û���жϣ�Ӧ���Ǹ���
//hashmap�������͸��²���Ӧ�úϲ�
void putData(HashMap* hashmap,int key,void* value){
	int pos;
	DataType* data,*data1;
	LinkNode* head;

	data = (DataType*)malloc(sizeof(DataType));
	data->key = key;
	data->value = value;

	//�õ�hashɢ��ֵ
	pos = hash(hashmap,key);
	head = &(hashmap->table[pos]);

	//���hashmap�д��ڣ�����½ڵ㣻��������ڣ�����ӽڵ�
	if((DataType*)getData(hashmap,key)){
		data1 = (DataType*)getData(hashmap,key);
		updateNode(head,data,data1,sizeof(data1));
	}else{
		//���ҵ��������ͷ����в�������
		addNode(head,data);
	}
}


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