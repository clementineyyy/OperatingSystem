/*
虚拟存储管理中的最近最久未使用(LRU)页面置换算法
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

//比较三个迭代器，返回最小的那个迭代器指向的值，即为最近最久不被访问的页面号
int compare(vector<int>::iterator it1, vector<int>::iterator it2, vector<int>::iterator it3) {
	if (it1 < it2 && it1 < it3)
		return frames[0];
	else if (it2 < it1 && it2 < it3)
		return frames[1];
	else
		return frames[2];
}

//比较物理块中的页面号，哪个页面号在页面号引用串中出现的时间最早，就把它换出去
void removePage(const vector<int>::iterator it) {
	//获取物理块中的第一个页面号在当前的页面号引用串中最后一次出现的位置，剩下的迭代器以此类推
	vector<int>::iterator it1 = find_end(pages.begin(), it, frames.begin(), frames.begin() + 1);
	vector<int>::iterator it2 = find_end(pages.begin(), it, frames.begin() + 1, frames.begin() + 2);
	vector<int>::iterator it3 = find_end(pages.begin(), it, frames.begin() + 2, frames.end());
	//得到三个迭代器中最小的那个迭代器，即为最近最久不被访问的页面号的迭代器
	int page = compare(it1, it2, it3);
	//在物理块中找到被换出的页面号的迭代器
	vector<int>::iterator remove = find(frames.begin(), frames.end(), page);	
	removePages.push_back(*remove);				//把被换出的页面号放进被换出的页面号数组
	frames.erase(remove);						//在物理块中删除被换出的页面号
}


//最近最久未使用算法
void LRU() {
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
			removePage(it);
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
	//调用最近最久未使用(LRU)算法
	LRU();
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