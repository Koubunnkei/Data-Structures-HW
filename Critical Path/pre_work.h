#pragma once
#include <string>
#include<iostream>
#define UNVISITED 0

//
using namespace std;
template<class Edgetype>
class Edge {
public:
	int start, end;//��㣬�յ�;
	Edgetype weight;
	string name;

	Edge() {};
	Edge(int st, int en, Edgetype w, string n) {
		start = st;
		end = en;
		weight = w;
		name = n;
	}
};

template<class Edgetype>
class Graph
{
public:
	int vertexNum; //ͼ�Ķ�����Ŀ
	int edgeNum; //ͼ�ı���Ŀ
	int* Mark;//���ĳ�����Ƿ񱻷��ʹ�
	int* InDegree;//���ÿ����������
	Graph(int verticesNum)//���캯��
	{
		vertexNum = verticesNum;
		edgeNum = 0;
		Mark = new int[verticesNum];
		InDegree = new int[verticesNum];
		for (int i = 0; i<verticesNum; i++)
		{
			Mark[i] = UNVISITED;
			InDegree[i] = 0;
		}
	}

	~Graph() { delete[] Mark; delete[] InDegree; }

	virtual Edge<Edgetype> FirstEdge(int oneVertex) = 0; //�����붥��oneVertex������ĵ�һ����
	virtual Edge<Edgetype> NextEdge(Edge<Edgetype> oneEdge) = 0;//�����붥��oneVertex����ͬ������һ����

	int VerticesNum() { return vertexNum; }//���ض���ĸ���
	int EdgesNum() { return edgeNum; }//���رߵ���Ŀ

	bool IsEdge(Edge<Edgetype> oneEdge)//���oneEdge�Ǳ��򷵻�TRUE�����򷵻�FALSE
	{
		if (oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.end >= 0)
			return true;
		else
			return false;
	}

	int StartVertex(Edge<Edgetype> oneEdge) { return oneEdge.start; }
	int EndVertex(Edge<Edgetype> oneEdge) { return oneEdge.end; }

	double Weight(Edge<Edgetype> oneEdge) { return oneEdge.weight; }
	virtual void setEdge(int start, int end, Edgetype weight,string name) = 0;
	virtual void delEdge(int start, int end) = 0;
};



//�����ڽӱ�
template<class Edgetype>
class ListData
{
public:
	int end;
	Edgetype weight;
	string name;
};

template<class Elem>//Elem���ǽ�����ListData<Edgetype>
class ListNode
{
public:
	Elem element;
	ListNode<Elem> *next;
	ListNode(const Elem & elemval, ListNode<Elem> *nextval = NULL)
	{
		element = elemval;
		next = nextval;
	}
	ListNode(ListNode<Elem> *nextval = NULL)//��ʼ��EdgeList��headʱ����
	{
		next = nextval;
	}
};

template<class Elem>
class EdgeList
{
public:
	ListNode<Elem> *head;
	EdgeList()
	{
		head = new ListNode<Elem>;
	}
	~EdgeList()
	{
		ListNode<Elem> *temp;
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

template<class Edgetype>
class ListGraph :public Graph<Edgetype>
{
private:
	EdgeList<ListData<Edgetype>> *graList;
public:
	ListGraph(int verticesNum) :Graph<Edgetype>(verticesNum)
	{
		graList = new EdgeList<ListData<Edgetype>>[verticesNum];
	}
	~ListGraph()
	{
		delete[]graList;
	}
	Edge<Edgetype> FirstEdge(int oneVertex)
	{
		Edge<Edgetype> temp;
		temp.start = oneVertex;
		if (graList[oneVertex].head->next!= NULL)
		{
			ListNode<ListData<Edgetype>> *first = graList[oneVertex].head->next;
			temp.end = first->element.end;
			temp.weight = first->element.weight;
			temp.name = first->element.name;
		}
		return temp;
	}

	Edge<Edgetype> NextEdge(Edge<Edgetype> oneEdge)
	{
		Edge<Edgetype> temp;
		temp.start = oneEdge.start;
		ListNode<ListData<Edgetype>> *p_temp = graList[oneEdge.start].head;
		while (p_temp->next != NULL && p_temp->next->element.end <= oneEdge.end)
		{
			p_temp = p_temp->next;
		}
		if (p_temp->next != NULL)
		{
			temp.end = p_temp->next->element.end;
			temp.weight = p_temp->next->element.weight;
			temp.name = p_temp->next->element.name;
		}
		return temp;
	}

	void setEdge(int start, int end, Edgetype weight,string name)
	{
		//�ҵ������
		ListNode<ListData<Edgetype>> *p_temp = graList[start].head;
		while (p_temp->next != NULL&&p_temp->next->element.end < end)
		{
			p_temp = p_temp->next;
		}
		if (p_temp->next == NULL)
		{
			ListNode<ListData<Edgetype>> *new_node = new ListNode<ListData<Edgetype>>;
			p_temp->next = new_node;
			new_node->element.end = end;
			new_node->element.weight = weight;
			new_node->element.name = name;
			edgeNum++;
			InDegree[end]++;
			return;
		}
		else if (p_temp->next->element.end == end)
		{
			p_temp->next->element.weight = weight;
			p_temp->next->element.name = name;
			return;
		}
		else if (p_temp->next->element.end > end)
		{
			ListNode<ListData<Edgetype>> *p_temp2 = p_temp->next;
			p_temp->next = new ListNode<ListData<Edgetype>>;
			p_temp->next->element.end = end;
			p_temp->next->element.weight = weight;
			p_temp->next->element.name = name;
			p_temp->next->next = p_temp2;
			edgeNum++;
			InDegree[end]++;
			return;
		}
	}
	void delEdge(int start, int end)
	{
		ListNode<ListData<Edgetype>> *p_temp = graList[start].head;
		while (p_temp->next != NULL&&p_temp->next->element.end < end)
		{
			p_temp = p_temp->next;
		}
		if (p_temp->next == NULL) return;
		else if (p_temp->next->element.end == end)
		{
			ListNode<ListData<Edgetype>> *p_temp2 = p_temp->next->next;
			delete p_temp->next;
			p_temp->next = p_temp2;
			edgeNum--;
			InDegree[end]--;
		}
	}
};
