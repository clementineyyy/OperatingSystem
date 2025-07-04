/*
磁盘调度中的扫描(SCAN)算法
实验日期：2025.6.10
E22314049 谷昕璐
*/
#include <iostream>
#include <vector>
#include <algorithm>						
using namespace std;

vector<int> processes;						// 创建一个动态数组，用来存放磁道号
int head = 100;								// 磁头初始位置
bool isIncrease = true;						// 磁头移动方向，true表示向磁道数增加方向移动，false表示向磁道数减小方向移动
float sumMove = 0;							// 初始化总的移动距离
int l = -1;									// 电梯的下边界，表示最后一个小于磁头位置的磁道号的索引
int r = -1;									// 电梯的上边界，表示第一个大于磁头位置的磁道号的索引

// 更新磁头位置并输出当前访问磁道数和移动距离，调用函数做到代码重用
void set(int j) {
	cout << "当前访问磁道数：" << processes[j] << ' ';
	cout << "移动距离：" << abs(processes[j] - head) << endl;
	sumMove += abs(processes[j] - head);	// 累加移动距离
	head = processes[j];				    // 更新磁头位置
}

// 向上移动磁头
void up() {
	for (int j = r; j < processes.size(); j++) {
		set(j);		// 调用set函数输出当前访问磁道数和移动距离，并更新磁头位置
	}
}

// 向下移动磁头
void down() {
	for (int j = l; j >= 0; j--) {
		set(j);		// 调用set函数输出当前访问磁道数和移动距离，并更新磁头位置
	}
}

//磁盘调度中的扫描(SCAN)算法
void SCAN() {			
	//先找到数组内部的边界
	for (int i = 0; i < processes.size(); i++) {
		// 如果磁道号小于磁头位置，更新l为当前索引
		if (processes[i] < head) {
			l = i;
			continue;
		}
		// 如果磁道号刚好等于磁头位置，直接输出当前访问磁道数和移动距离
		if (processes[i] == head) {
			cout << "当前访问磁道数：" << processes[i] << ' ';
			cout << "移动距离：0" << endl;
			continue;
		}
		if (processes[i] > head) {
			r = i;	// r是第一个大于磁头位置的磁道号的索引
			break;  // 因为是第一个大于磁头位置的磁道号的索引所以找到就退出循环
		}
	}


	//如果移动方向是向磁道数增加方向移动
	if (isIncrease) {
		// 因为数组排好序了，所以直接坐电梯，向上移动
		up();
		// 因为数组排好序了，所以直接坐电梯，向下移动
		down();
	}
	// 如果移动方向是向磁道数减小方向移动
	else {
		// 因为数组排好序了，所以直接坐电梯，向下移动
		down();
		// 因为数组排好序了，所以直接坐电梯，向上移动
		up();
	}
	
	cout << "平均寻道长度：" << sumMove / processes.size() << endl; // 输出平均寻道长度
}

int main() {
	cout << "E22314049 谷昕璐" << endl;
	//实现数据与程序分离
	while (true) {
		int process;
		cin >> process;
		processes.push_back(process);		// 将输入的进程访问的磁道号存入动态数组
		if (cin.get() == '\n')
			break;
	}
	sort(processes.begin(), processes.end());// 对磁道号进行排序
	SCAN();
}

