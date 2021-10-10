#pragma once
#include <string>
#include<iostream>
#define UNVISITED 0

//
using namespace std;
template<class Edgetype>
class Edge {
public:
	int start, end;//起点，终点;
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
	int vertexNum; //图的顶点数目
	int edgeNum; //图的边数目
	int* Mark;//标记某顶点是否被访问过
	int* InDegree;//标记每个顶点的入度
	Graph(int verticesNum)//构造函数
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

	virtual Edge<Edgetype> FirstEdge(int oneVertex) = 0; //返回与顶点oneVertex相关联的第一条边
	virtual Edge<Edgetype> NextEdge(Edge<Edgetype> oneEdge) = 0;//返回与顶点oneVertex有相同起点的下一条边

	int VerticesNum() { return vertexNum; }//返回顶点的个数
	int EdgesNum() { return edgeNum; }//返回边的数目

	bool IsEdge(Edge<Edgetype> oneEdge)//如果oneEdge是边则返回TRUE，否则返回FALSE
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



//构建邻接表
template<class Edgetype>
class ListData
{
public:
	int end;
	Edgetype weight;
	string name;
};

template<class Elem>//Elem就是将来的ListData<Edgetype>
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
	ListNode(ListNode<Elem> *nextval = NULL)//初始化EdgeList的head时调用
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
		//找到插入点
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
