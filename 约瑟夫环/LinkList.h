#pragma once
#include <iostream>
using namespace std;
namespace LinkList
{
	typedef struct Node
	{
		string number{};//学号
		string name{};
		int pos{};//位置
		struct Node* next{};//下一个人的位置
	}node;

	struct linkList
	{
		int len{};//节点数
		Node* head{};//头指针，指向第一个节点
	};
	// 创建链表
	linkList* createLinkList();
	// 释放链表
	void releaseLinkList(linkList* list);
	// 尾插法
	void insertNodetoList(linkList* list, string number, string name);
	// 删除某个节点
	void deleteNodefromList(linkList* list, int pos);
	// 改变头节点位置
	void changeHeadLocation(linkList* list, const int pos);
	// 头尾相连
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
		cout << "还剩" << list->len << "个节点!" << endl;
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
			node->pos = ++list->len;// 链表长度增加
			// 插入末尾
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
		// 新建节点
		Node* node = new Node;
		node->number = number;
		node->name = name;
		node->pos = ++list->len;// 链表长度增加
		// 插入末尾
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
		cout << "删除了" << tmp->pos << " " << tmp->name << " " << tmp->number << endl;
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
