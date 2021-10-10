#pragma once
#include"pre_work.h"
#include<iostream>
#include<string>
#include<queue>
using namespace std;

class ProjectAct
{
public:
	int Index;
	double Duration;
	int From;
	int To;
	string Name;
	ProjectAct(){}
	ProjectAct(int Index, double Duration, int From, int To, string Name)
	{
		this->Index = Index;
		this->Duration = Duration;
		this->From = From;
		this->To = To;
		this->Name = Name;
	}
};

template<class Edgetype>
class AOENetwork:public ListGraph<Edgetype>
{
public:
	AOENetwork(int verticesNum) :ListGraph<Edgetype>(verticesNum)
	{}
	~AOENetwork()
	{}

	bool TopologySort(Edgetype *VE, int *SortArray)//VE计算节点最早发生时间
	{
		int v;
		for (int i = 0; i < vertexNum; i++)
		{
			VE[i] = 0;
		}

		//确定拓扑序列
		for (int i = 0; i < vertexNum; i++)//一次确定拓扑序列的第i个元素
		{
			for (v = 0; v < vertexNum; v++)
			{
				if (InDegree[v] == 0 && Mark[v] == 0)
				{
					break;
				}
			}
			if (v == vertexNum) return false;

			Mark[v] = 1;
			SortArray[i] = v;
			for (Edge<Edgetype> e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
			{
				InDegree[e.end]--;
				if (VE[e.end] < VE[v] + e.weight)
				{
					VE[e.end] = VE[v] + e.weight;
				}
			}

		}
		return true;
	}

	bool CriticalPath()
	{
		int v;
		Edgetype* VE = new Edgetype[vertexNum];
		Edgetype* VL = new Edgetype[vertexNum];
		int* TopOrder = new int[vertexNum];
		if (!TopologySort(VE, TopOrder))
		{
			return false;
		}

		//初始化最迟发生时间
		for (int i = 0; i < vertexNum; i++)
		{
			VL[i] = VE[TopOrder[vertexNum - 1]];
		}
		
		//逆拓扑序列计算VL
		for (int i = vertexNum - 1; i >= 0; i--)
		{
			int x = TopOrder[i];
			for (Edge<Edgetype> e = FirstEdge(x); IsEdge(e); e = NextEdge(e))
			{
				if (VL[x] > VL[e.end] - e.weight)
				{
					VL[x] = VL[e.end] - e.weight;
				}
			}
		}

		for (v = 0; v < vertexNum; v++)
		{
			for (Edge<Edgetype> e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
			{
				if (VE[v] == VL[e.end] - e.weight)
				{
					cout << v << '-' << e.end <<' ' <<e.name<<endl;
				}
			}
		}

	}

};