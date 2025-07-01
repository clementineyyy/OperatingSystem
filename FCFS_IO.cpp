/*
磁盘调度中的先来先服务(FCFS)算法
实验日期：2025.5.27
E22314049 谷昕璐
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> processes;					// 创建一个动态数组，用来存放磁道号

//磁盘调度中的先来先服务(FCFS)算法
void FCFS() {
	int head = 100;						// 磁头初始位置
	float sumMove = 0;					// 移动磁道数之和,为了计算平均寻道长度(小数)所以类型是float
	for (int i = 0; i < processes.size(); i++) {
		cout << "访问磁道号：" << processes[i] << ' ';	// 输出当前访问的磁道号
		cout << "磁头移动距离：" << abs(head - processes[i]) << endl;	// 输出磁头移动距离,注意是绝对值
		sumMove += abs(head - processes[i]);			// 累加磁头移动距离，注意是绝对值
		head = processes[i];			// 更新磁头位置
	}
	cout << "平均寻道长度：" << sumMove / processes.size() << endl;		// 输出平均寻道长度
}

int main() {
	cout << "E22314049 谷昕璐" << endl;
	//实现数据与程序分离
	while (true) {
		int process;
		cin >> process;
		processes.push_back(process);	// 将输入的进程访问的磁道号存入动态数组
		if (cin.get() == '\n')
			break;
	}
	FCFS();
}