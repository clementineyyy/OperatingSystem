/*
银行家算法避免死锁
实验日期：2025.4.29
E22314049 谷昕璐
*/
#include <iostream>
using namespace std;

class Matrix {
private:
	int a;			// A资源的值
	int b;          // B资源的值
	int c;          // C资源的值

public:
	Matrix(int _a = 0, int _b = 0, int _c = 0) :a(_a), b(_b), c(_c) {}
	// 设置一个进程对各种资源的值
	void setValue(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
	//下一次的可利用资源向量work=当前的可利用资源向量work+分配向量allocation
	void add(const Matrix& allocation) {
		a = a + allocation.a;
		b = b + allocation.b;
		c = c + allocation.c;
	}
	// 进程对资源的需求矩阵=最大需求矩阵-已分配资源矩阵
	Matrix divide(const Matrix& allocated) {
		return { a - allocated.a,b - allocated.b,c - allocated.c };
	}
	//比较进程对资源的需求和可用资源的大小，如果可用资源大于等于需求资源，则返回true，否则返回false
	bool compare(const Matrix& work) const {
		return (a <= work.a && b <= work.b && c <= work.c);
	}
	//展示资源矩阵的具体值
	void display() const {
		cout << "资源A:" << a << " 资源B:" << b << " 资源C:" << c << endl;
	}
};

class Process {
private:
	int id;								// 进程ID
	Matrix max;							// 最大资源需求
	Matrix allocated;					// 已分配资源
	Matrix need;						// 还需资源
	Matrix work;						// 可用资源

public:
	Process(int _id = 0, const Matrix& _max = { 0 }, const Matrix& allocated = { 0 }, const Matrix& need = { 0 }, const Matrix& _work = { 0 }) :
		id(_id), max(_max), allocated(allocated), need(need), work(_work) {}
	// 设置进程的ID、最大资源需求max、已分配资源allocated、还需资源need和工作向量work
	void setValue(int _id, const Matrix& _max, const Matrix& _allocated, const Matrix& _need,const Matrix& _work) {
		id = _id;
		max = _max;
		allocated = _allocated;
		need = _need;
		work = _work;
	}
	Matrix getAllocated() const { return allocated; }	// 获取进程的已分配资源矩阵
	Matrix getNeed() const { return need; }				// 获取进程的需求矩阵
	Matrix getWork() const { return work; }				// 获取进程的工作向量
	void setWork(const Matrix& _work) { work = _work; }	// 设置进程的工作向量
};

//判断是不是所有进程的资源都被分配完成了
bool allFinished(bool finished[]) {
	for (int i = 0; i < 5; i++) {
		if (finished[i] == false) {
			return false;	// 只要有一个进程没有完成，就返回false
		}
	}
	return true;			// 如果所有进程都完成了，就返回true
}

int main()
{
	cout << "E22314049 谷昕璐" << endl;
	Process p[5];					// 创建5个进程
	int a = 0, b = 0, c = 0;
	cout << "请输入可利用资源向量：";
	cin >> a >> b >> c;
	Matrix available(a, b, c);			// 初始化可用资源向量
	for (int i = 0; i < 5; i++) {
		cout << "请输入进程P" << i << "的最大资源需求Max：";
		cin >> a >> b >> c;
		Matrix max(a, b, c);		// 初始化最大资源需求矩阵
		cout << "请输入进程P" << i << "的已分配资源Allocated：";
		cin >> a >> b >> c;
		Matrix allocated(a, b, c);	// 初始化已分配资源矩阵
		cout << "下面计算并输出进程P" << i << "的资源需求Need" << endl;
		Matrix need = max.divide(allocated);
		need.display();
		p[i].setValue(i, max, allocated, need, available);
	}
	bool finished[5] = { 0 };			// 记录分配完成的进程数
	int runtimes = 0;
	bool signal = true;
	int line[5] = { 0 };				// 最终的安全序列
	int j = 0;							// 安全序列的下标
	cout << "==========================================================" << endl;
	while (runtimes<=6)
	{	
		for (int i = 0; i < 5; i++) {
			if (finished[i] == false) {
				// 如果进程没有被分配资源完成
				Matrix need = p[i].getNeed();				// 获取进程的需求矩阵
				Matrix work = available;					// 获取进程的工作向量
				bool flag = need.compare(work);				// 比较需求矩阵和工作向量
				if (flag == true) {							// 如果进程的需求小于等于工作向量，则可以分配资源
					p[i].setWork(work);						// 更新进程的工作向量
					if (signal == true) {
						// 如果是第一次运行而且可以分配资源，输出当前可用资源
						cout << "当前可用资源为" << endl;
						available.display();
						signal = false;
					}
					cout << "进程P" << i << "的资源需求满足条件，给它分配资源如下：" << endl;
					need.display();
					cout << "==========" << endl;
					Matrix allocation = p[i].getAllocated();	// 获取分配向量
					available.add(allocation);					// 更新工作向量
					finished[i] = true;							// 标记进程的资源已分配已完成
					line[j] = i;								// 进程加入安全序列
					j++;										// 安全序列的下标加1
					cout << "当前可用资源为" << endl;
					available.display();						// 显示当前可用资源
				}
			}
		}
		runtimes++;
	}
	cout << "==========================================================" << endl;

	//如果所有进程都完成了，说明安全
	if (allFinished(finished)) {
		cout << "{ ";
		for (int i = 0; i < 5; i++) {
			cout << "P" << line[i] << " " ;	// 输出安全序列
		}
		cout << "}" << endl;
		cout << "存在如上所示的安全序列，所以进程不会死锁" << endl;
	}
	else {
		cout << "不存在这样的安全序列，所以进程可能死锁" << endl;
	}
}