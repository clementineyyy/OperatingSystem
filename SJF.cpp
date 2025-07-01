/*
短作业优先(SJF)调度算法
实验日期：2025.4.1
E22314049 谷昕璐
*/

#include <iostream>
#include <algorithm>
using namespace std;

//由于不同作业有各自的到达时间，服务时间等时间，因此定义一个结构体来存储作业的信息
struct job
{
	char label = 'A';					//作业名称
	int arriveTime = 0;					//到达时间
	int serveTime = 0;					//服务时间
	int startTime = 0;					//开始执行时间
	int finishTime = 0;					//完成时间
	//周转时间，由于带权周转时间是周转时间除以服务时间，可能是小数，因此定义周转时间是float类型，避免出现精度问题
	float turnAroundTime = 0;
	float weightedTurnAroundTime = 0;	//带权周转时间
	bool isOperated = false;			//该作业是否已经被运行
};

//按到达时间排序,该函数作为sort函数中的比较器，控制sort函数根据作业的到达时间从小到大排序
int compareSequence(job a, job b)
{
	return a.arriveTime < b.arriveTime;
}

//按服务时间排序,该函数作为sort函数中的比较器，控制sort函数实现短作业优先
int compareServeTime(job a, job b)
{
	return a.serveTime < b.serveTime;
}

//按作业名称排序,该函数作为sort函数中的比较器，控制sort函数根据作业的名称从小到大排序
int compareLabel(job a, job b)
{
	return a.label < b.label;
}

int main()
{
	cout << "E22314049 谷昕璐" << endl;
	int n = 0;					//作业数	
	cout << "请输入作业数：";
	cin >> n;
	job* jobs = new job[n];		//定义n个作业
	//数据与程序分离，用户输入作业的到达时间和估计的服务时间
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << i + 1 << "个作业的到达时间和服务时间：";
		cin >> jobs[i].arriveTime >> jobs[i].serveTime;
		jobs[i].label = 'A' + i;
	}

	//先按到达时间排序，找到最先到达的作业第一个执行
	sort(jobs, jobs + n, compareSequence);
	int time = jobs[0].arriveTime;		//当前时间是第一个作业的到达时间，未必是0
	jobs[0].startTime = time;			//第一个作业的开始执行时间是当前时间
	jobs[0].finishTime = time + jobs[0].serveTime;	//第一个作业的完成时间=开始执行时间+服务时间
	jobs[0].turnAroundTime = jobs[0].finishTime - jobs[0].arriveTime;	//第一个作业的周转时间=完成时间-到达时间
	jobs[0].weightedTurnAroundTime = jobs[0].turnAroundTime / jobs[0].serveTime;	//第一个作业的带权周转时间 = 周转时间 / 服务时间
	jobs[0].isOperated = true;			//第一个作业已经被运行
	time = jobs[0].finishTime;			//更新当前时间,当前时间就是第一个作业的完成时间

	sort(jobs, jobs + n, compareServeTime);	//按服务时间排序，实现短作业优先
	for (int i = 0; i < n; i++)
	{
		if (jobs[i].isOperated)		//如果该作业已经被运行，跳过，考虑到第一个到达的作业已经被运行的情况
			continue;
		//作业的开始执行时间为当前时间和到达时间中的最大值
		jobs[i].startTime = max(time, jobs[i].arriveTime);
		//作业的完成时间=开始执行时间+服务时间
		jobs[i].finishTime = jobs[i].startTime + jobs[i].serveTime;
		//更新当前时间,当前时间就是作业的完成时间
		time = jobs[i].finishTime;
		//作业的周转时间=完成时间-到达时间
		jobs[i].turnAroundTime = jobs[i].finishTime - jobs[i].arriveTime;
		//作业的带权周转时间 = 周转时间 / 服务时间
		jobs[i].weightedTurnAroundTime = jobs[i].turnAroundTime / jobs[i].serveTime;
		jobs[i].isOperated = true;		//该作业已经被运行
	}
	float averageTurnAroundTime = 0;		//平均周转时间
	float averageWeightedTurnAroundTime = 0;	//平均带权周转时间
	for (int i = 0; i < n; i++)
	{
		//平均周转时间=所有作业的周转时间之和/作业数
		averageTurnAroundTime += jobs[i].turnAroundTime;
		//平均带权周转时间=所有作业的带权周转时间之和/作业数
		averageWeightedTurnAroundTime += jobs[i].weightedTurnAroundTime;
	}
	averageTurnAroundTime /= n;
	averageWeightedTurnAroundTime /= n;

	//按作业名称排序,由于中间处理时经过了排序，所以应保证作业输入的顺序和输出的顺序一致
	sort(jobs, jobs + n, compareLabel);
	for (int i = 0; i < n; i++)
	{
		char c = 'A' + i;
		cout << "作业" << c << "的开始执行时间：" << jobs[i].startTime << endl;
		cout << "作业" << c << "的完成时间：" << jobs[i].finishTime << endl;
		cout << "作业" << c << "的周转时间：" << jobs[i].turnAroundTime << endl;
		cout << "作业" << c << "的带权周转时间：" << jobs[i].weightedTurnAroundTime << endl;
		cout << endl;
	}
	cout << "平均周转时间：" << averageTurnAroundTime << endl;
	cout << "平均带权周转时间：" << averageWeightedTurnAroundTime << endl;
	return 0;
}