#pragma once
#include <iostream>
using namespace std;
namespace LinkList
{
	typedef struct Node
	{
		string number{};//ѧ��
		string name{};
		int pos{};//λ��
		struct Node* next{};//��һ���˵�λ��
	}node;

	struct linkList
	{
		int len{};//�ڵ���
		Node* head{};//ͷָ�룬ָ���һ���ڵ�
	};
	// ��������
	linkList* createLinkList();
	// �ͷ�����
	void releaseLinkList(linkList* list);
	// β�巨
	void insertNodetoList(linkList* list, string number, string name);
	// ɾ��ĳ���ڵ�
	void deleteNodefromList(linkList* list, int pos);
	// �ı�ͷ�ڵ�λ��
	void changeHeadLocation(linkList* list, const int pos);
	// ͷβ����
	void headtoEnd(linkList* list);
	linkList* createLinkList()
	{
		linkList* list = new linkList;
		return list;
	}
	void releaseLinkList(linkList* list)
	{
		if (!list)
		{
			return;
		}
		Node *cur = list->head;
		while (cur != nullptr)
		{
			Node* tmp = cur;
			if (cur != cur->next)
			{
				cur = cur->next;
			}
			delete tmp;
			tmp = nullptr;
			list->len--;
		}
		cout << "��ʣ" << list->len << "���ڵ�!" << endl;
		delete list;
	}

	void insertNodetoList(linkList* list, string number, string name)
	{
		if (!list)
		{
			return;
		}
		if (!list->head)
		{
			Node* node = new Node;
			node->number = number;
			node->name = name;
			node->pos = ++list->len;// ����������
			// ����ĩβ
			list->head = node;
			return;
		}
		Node* cur{}, * pre{};
		cur = list->head;
		while (cur)
		{
			pre = cur;
			cur = cur->next;
		}
		// �½��ڵ�
		Node* node = new Node;
		node->number = number;
		node->name = name;
		node->pos = ++list->len;// ����������
		// ����ĩβ
		pre->next = node;
	}
	static Node* searchPreNode(Node* head, int pos)
	{
		Node* pre{}, * cur;
		cur = head;
		for (int i = 0; i < pos; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		return pre;
	}
	void deleteNodefromList(linkList* list, int pos)
	{
		Node* pre = searchPreNode(list->head, pos);
		Node* tmp = pre->next;
		pre->next = tmp->next;
		list->head = pre->next;
		cout << "ɾ����" << tmp->pos << " " << tmp->name << " " << tmp->number << endl;
		delete tmp;
		list->len--;
	}


	void changeHeadLocation(linkList* list, const int pos)
	{
		Node* cur, * pre{};
		cur = list->head;
		while (cur)
		{
			if (pos == cur->pos)
			{
				list->head = cur;
				break;
			}
			pre = cur;
			cur = cur->next;
		}
	}
	void headtoEnd(linkList* list)
	{
		Node* pre{}, * cur;
		cur = list->head;
		while (cur)
		{
			pre = cur;
			cur = cur->next;
		}
		pre->next = list->head;
	}
}
