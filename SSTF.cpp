/*
磁盘调度中的最短寻道时间优先(SSTF)算法
实验日期：2025.5.27
E22314049 谷昕璐
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> processes;						// 创建一个动态数组，用来存放磁道号
int head = 100;								// 磁头初始位置

//磁盘调度中的最短寻道时间优先(SSTF)算法
void SSTF() {
	int minIndex = 0;						// 初始化最小移动距离对应的进程号
	float sumMove = 0;						// 初始化总移动距离,为了计算平均寻道长度(小数)所以类型是float
	int size = processes.size();			// 保存数组长度
	for (int t = 0; t < size; t++) {		//t控制循环次数，直到所有进程都被访问
		//遍历数组找到最近的被访问的磁道号
		int minDistance = 10000;				// 初始化最小移动距离
		for (int i = 0; i < processes.size(); i++) {
			// 如果当前进程要求访问的磁道数比最小移动距离还小，就更新最小移动距离
			int distance = abs(head - processes[i]);
			if (distance <= minDistance) {
				minDistance = distance;	// 更新最小移动距离
				minIndex = i;				// 更新最小移动距离对应的进程号		
			}
		}
		cout << "访问磁道号：" << processes[minIndex] << ' ';	// 输出访问的磁道号
		cout << "磁头移动距离：" << minDistance << endl;		// 输出磁头移动距离
		sumMove += minDistance;				// 累加总移动距离
		head = processes[minIndex];			// 更新磁头位置
		processes.erase(processes.begin() + minIndex);			// 删除已访问的磁道号
	}
	cout << "平均寻道长度：" << sumMove / size << endl;		// 输出平均寻道长度
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
	SSTF();
}
