#include<iostream>
#include"AOENetwork.h"
#include"pre_work.h"
#include<string>
#include<map>
using namespace std;

int main()
{
	//一共7个顶点,8个活动
	//构建邻接链表网络图
	AOENetwork<double> G(7);
	//构建活动
	ProjectAct activity[8] = {
		{0,6,0,1,"a0"},
		{1,3,0,2,"a1"},
		{2,1,1,3,"a2"},
		{3,1,2,3,"a3"},
		{4,9,3,4,"a4"},
		{5,6,3,5,"a5"},
		{6,7,4,6,"a6"},
		{7,3,5,6,"a7"}
	};
	//完成图的结构
	for (int i = 0; i < 8; i++)
	{
		G.setEdge(activity[i].From, activity[i].To, activity[i].Duration, activity[i].Name);
	}

	G.CriticalPath();
	system("pause");
	return 0;
}