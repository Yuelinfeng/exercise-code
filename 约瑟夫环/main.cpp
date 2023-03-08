#include "LinkList.h"
// ������ʽ
int test01()
{
	using namespace LinkList;
	linkList * list = createLinkList();
	insertNodetoList(list, "2021214376", "���ַ�");
	insertNodetoList(list, "2021214377", "����");
	insertNodetoList(list, "2021214378", "����");
	insertNodetoList(list, "2021214379", "����");
	insertNodetoList(list, "2021214380", "����");
	insertNodetoList(list, "2021214381", "Ǯ��");
	insertNodetoList(list, "2021214380", "���");
	headtoEnd(list); // ����ѭ������
	int m,k;
	cout << "�ٶ�һ������"; cin >> m;
	cout << "�ӵڼ���������"; cin >> k;
	changeHeadLocation(list, k);
	while (list->len > 1)
	{
		deleteNodefromList(list, m);
	}
	cout << "ʤ�����ǵ�: " << list->head->pos << 
		"������\n����" << list->head->name << 
		",ѧ��Ϊ: " << list->head->number << endl;
	//releaseLinkList(list);
	return 0;
}

int test03(int n, int m)
{
		int a[10] = { 0 };
		int i = 0;
		for (; i < n; i++)
			a[i] = i + 1;
		while (n > 1)
		{
			int k = 0;
			i = (i + m - 1) % n;
			k++;
			cout << "��" << k << "����Ȧ����:" << a[i] << endl;
			for (int j = i + 1; j < n; j++)
				a[j - 1] = a[j];
			n--;
			if (i == n)
				i = 0;
		}
		cout << "���ʣ�µ���:" << a[i] << endl;
		return 0;
}
int main()
{
	test01();
	test03(7, 4);
}