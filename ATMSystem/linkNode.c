#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linkNode.h"

// ��ʼ��һ���ڵ�
LinkNode* createNode(){
	LinkNode* head;
	head = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = NULL;
	return head;
}

// ��ӽڵ�
void addNode(LinkNode* head,void* data){
	while(head->next){
		head = nextNode(head);
	}
	head->next = (LinkNode*)malloc(sizeof(LinkNode));
	head = nextNode(head);
	head->data = data;
 	head->next = NULL;
}

// ɾ���ڵ�
void deleted(LinkNode* head,void* data,int size){
	LinkNode* temp;
	while(head->next){
		temp = head->next;
		if(checkDataNode(temp->data,data,size)){
			head->next=temp->next;
			free(temp);
		}else{
			head=head->next;
		}
	}
}

//�����������ݾ����ݽ��в��ң�������ھ��������޸�Ϊ������
void updateNode(LinkNode* head,void* newData,void* oldData,int size){
	while(head->next){
		head = head->next;
		if(checkDataNode(head->data,oldData,size)){
			head->data = newData;
		}
	}
}

// ����Ƿ����ĳ�ڵ㣬�����ַ����ַ���Ա仯
int checkDataNode(void* origin,void* now,int size){
	return memcmp(origin,now,size)==0 ? 1:0;
}

// ���ص�ǰ�ڵ����һ���ڵ�
LinkNode* nextNode(LinkNode* node){
	return node->next;
}

//��ǰ����һ�����ڵ�ɾ��
void destoryLinkNode(LinkNode* head){
	LinkNode* node;
	while(head->next){
		node = nextNode(head);
		head->next = nextNode(node);
		free(node->data);
		free(node);
	}
	free(head);
}