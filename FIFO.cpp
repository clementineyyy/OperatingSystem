/*
虚拟存储管理中的先进先出(FIFO)页面置换算法
实验日期：2025.5.13
E22314049 谷昕璐
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> pages;								//创建一个动态数组，用来存放页面号
vector<int> frames;								//创建一个动态数组，用来代表物理块
vector<int> pageFaults;							//创建一个动态数组，用来存放缺页的页面号
vector<int> removePages;						//创建一个动态数组，用来存放被换出的页面号
const int FRAME_SIZE = 3;						//定义物理块的大小为3

//判断当前的页面号是否在物理块中
bool findPageInFrames(int page) {
	vector<int>::iterator it = find(frames.begin(), frames.end(), page);
	if (it != frames.end())
		return true;	//如果找到了页面号，返回true
	else
		return false;	//如果没找到页面号，返回false
}

//把第一个物理块中的页面号置换出去
void removePage() {
	//得到物理块中第一个页面号的迭代器
	vector<int>::iterator remove = frames.begin();
	removePages.push_back(*remove);				//把被换出的页面号放进被换出的页面号数组
	frames.erase(remove);						//在物理块中删除被换出的页面号
}


//最佳置换算法
void FIFO() {
	vector<int>::iterator it = pages.begin();	//创建一个迭代器，用来遍历页面号引用串，初始化为页面号引用串的开始位置
	for (; it != pages.end(); ++it) {
		//如果当前的页面号是在物理块中，就不缺页
		if (findPageInFrames(*it))
			continue;
		//如果如果当前的页面号不在物理块中而且当前物理块没放满，那么直接把当前的页面号放进物理块,并且这算是一次缺页
		else if (frames.size() < FRAME_SIZE) {
			frames.push_back(*it);
			pageFaults.push_back(*it);			//把当前的页面号放进缺页数组
			continue;
		}
		//如果当前的页面号不在物理块中，而且当前物理块满了，那么就要进行页面置换
		else {
			removePage();
			frames.push_back(*it);				//把当前的页面号放进物理块
			pageFaults.push_back(*it);			//把当前的页面号放进缺页数组
		}
	}
}

//输出页面号引用串
void showPage(vector<int> page) {
	for (int v : page)
		cout << v << " ";
	cout << endl;
}

//计算缺页率=缺页数/页面号引用串长度
float calcPageFaultRate() {
	//因为是整型相除所以进行强制类型转换
	return pageFaults.size() / (float)pages.size();
}


int main() {
	cout << "E22314049 谷昕璐" << endl;
	int page = 0;
	cout << "页面号引用串为：";
	//实现数据与算法分离，用户从键盘输入一串页面号
	while (cin >> page) {
		//页面号加入到页面号引用串的尾部
		pages.push_back(page);
		//如果输入的是换行符，则退出循环
		if (cin.get() == '\n')
			break;
	}
	//调用先进先出算法
	FIFO();
	//输出缺页的页面号
	cout << "缺页的页面号为：";
	showPage(pageFaults);
	//输出被换出的页面号
	cout << "被换出的页面号为：";
	showPage(removePages);
	//输出缺页率
	cout << "缺页率为：";
	cout << calcPageFaultRate() << endl;
}