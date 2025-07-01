/*多级反馈队列调度算法
* 抢占式
* 实验日期：2025.4.17
E22314049 谷昕璐
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Process
{
private:
	int arriveTime;			//进程的到达时间
	int serveTime;			//进程的服务时间
	int needTime;			//进程的剩余时间=服务时间-已完成的时间
	int finishTime;			//进程的完成时间
	int time2BeContinued;	//进程如果被抢占后剩下的时间片的时间

public:
	//默认构造函数
	Process() {}
	//构造函数：参数只传入进程已知的到达时间和服务时间，所求的结束时时间默认为0
	Process(int _arriveTime, int _serveTime) :arriveTime(_arriveTime), serveTime(_serveTime), needTime(_serveTime), finishTime(0), time2BeContinued(0) {}
	int getArriveTime() { return arriveTime; }	//获取进程的到达时间
	int getServeTime() { return serveTime; }	//获取进程的服务时间
	int getNeedTime() { return needTime; }		//获取进程的剩余时间
	int getFinishTime() { return finishTime; }	//获取进程的完成时间
	int getTime2BeContinued() { return time2BeContinued; }										//获取进程的剩余时间片
	void setNeedTime(int _needTime) { needTime = _needTime; }									//设置进程的剩余时间
	void setFinishTime(int _finishTime) { finishTime = _finishTime; }							//设置进程的完成时间
	void setTime2BeContinued(int _time2BeContinued) { time2BeContinued = _time2BeContinued; }	//设置进程的剩余时间片
};

//判断多级反馈队列是否为空，空返回true，非空返回false
//传入参数是一个多级反馈队列，即一维数组
bool isEmptyQueue(const int queue[])
{
	if (queue[0] != 0)	        //如果队列的第一个元素不为0，说明队列不为空
		return false;
	return true;					//队列为空
}

//队首进程出队后，把后面排队的进程依次前移
void setQueue(int queeuIndex, int queue[], int queueEndIndex[])
{
	for (int i = 0; i < 9; i++)
		queue[i] = queue[i + 1];				//将队列中的元素依次前移
	queueEndIndex[queeuIndex]--;				//队列的结束索引减1
	queue[queueEndIndex[queeuIndex]] = 0;		//将队列的最后一个元素置为0
}

//时间片轮转调度算法运行队列中的作业
//传入二维数组队列，不同队列的时间片，进程，当前队列下标queueIndex，队尾进程在队列中的位置，当前处理进程的下标，下一个进程的下标，所有进程数，当前时间，已完成的进程数, 是否抢占
void RR(int queue[][10], int timeSlice[], vector<Process>& processes, int queueIndex, int queueEndIndex[], int processIndex, int nextProcess, int n, int& runTime, int& finishedProcess, bool &isPreempted)
{
	int processNeedTime = processes[processIndex].getNeedTime();						//获取当前进程的剩余时间
	int time2BeContinued = processes[processIndex].getTime2BeContinued();					//获取当前进程的剩余时间片
	if (time2BeContinued == 0)
		time2BeContinued = timeSlice[queueIndex];						//如果当前进程的剩余时间片为0，说明当前进程没有被抢占过，那么就用当前队列的时间片
	if (nextProcess > n)
		nextProcess = n;												//防止容器溢出
	if ((processIndex!=nextProcess) && (runTime< processes[nextProcess].getArriveTime()) && (runTime + time2BeContinued > processes[nextProcess].getArriveTime()))
		//如果在当前时间片内有新进程到达，那么抢占
	{
		int processTime = processes[nextProcess].getArriveTime() - runTime;				//当前时间片内当前进程可以执行的时间	
		if (processTime > processNeedTime)												//如果当前进程的剩余时间等于当前时间片内可以执行的时间，那么不抢占
		{
			runTime += processNeedTime;														//当前时间加上当前进程的剩余时间
			processes[processIndex].setNeedTime(0);											//当前进程的剩余时间等于0
			processes[processIndex].setFinishTime(runTime);									//当前进程的完成时间等于当前时间
			cout << "第" << processIndex << "个进程在第" << runTime - processNeedTime << "时刻开始执行，执行了" << processNeedTime << "个单位的时间，该进程调度结束" << endl;
			finishedProcess++;																//已完成的进程数加1
			processes[processIndex].setTime2BeContinued(0);									//当前进程的剩余时间片等于0
		}
		else //抢占
		{
			runTime += processTime;														//当前时间加上当前进程可以执行的时间
			processes[processIndex].setNeedTime(processNeedTime - processTime);				//当前进程的剩余时间等于当前的剩余时间减去当前时间片内可以执行的时间
			cout << "第" << processIndex << "个进程在第" << runTime << "时刻开始执行，执行了" << processTime << "个单位的时间，剩余" << processes[processIndex].getNeedTime() << "个单位的时间" << endl;
			int putIndex = queueEndIndex[queueIndex];										//得到当前队列的队尾位置
			queue[queueIndex][putIndex] = processIndex;										//将当前进程放入当前队列的队尾
			queueEndIndex[queueIndex]++;													//当前队列的队尾位置加1
			processes[processIndex].setTime2BeContinued(time2BeContinued - processTime);		//当前进程的剩余时间片等于当前的剩余时间减去当前时间片内可以执行的时间
			isPreempted = true;																//当前进程被抢占
		}
	}
	else {
		//不抢占
		if (processNeedTime > time2BeContinued)										//如果当前进程的剩余时间大于时间片
		{
			runTime += time2BeContinued;												//当前时间加上时间片
			processes[processIndex].setNeedTime(processNeedTime - time2BeContinued);	//当前进程的剩余时间等于当前的剩余时间减去时间片
			cout << "第" << processIndex << "个进程在第" << runTime - time2BeContinued << "时刻开始执行，执行了" << time2BeContinued << "个单位的时间，剩余" << processes[processIndex].getNeedTime() << "个单位的时间" << endl;
			int putIndex = queueEndIndex[queueIndex + 1];									//得到下一个队列的队尾位置
			queue[queueIndex + 1][putIndex] = processIndex;									//将当前进程放入下一个队列的队尾
			queueEndIndex[queueIndex + 1]++;												//下一个队列的队尾位置加1
		}
		else
		{
			runTime += processNeedTime;													    //当前时间加上当前进程的剩余时间
			processes[processIndex].setNeedTime(0);											//当前进程的剩余时间等于0
			processes[processIndex].setFinishTime(runTime);									//当前进程的完成时间等于当前时间
			cout << "第" << processIndex << "个进程在第" << runTime - processNeedTime << "时刻开始执行，执行了" << processNeedTime << "个单位的时间，该进程调度结束" << endl;
			finishedProcess++;																//已完成的进程数加1
		}
	}
	setQueue(queueIndex, queue[queueIndex], queueEndIndex);									//将当前队列的队首进程出队,后面的进程依次前移
	cout << "当前时间为" << runTime << endl;												//输出当前时间
}

bool isFinished(int finishedProcess, int n)		//判断是否所有进程都完成
{
	if (finishedProcess == n)					//如果所有进程都完成，返回true
		return true;
	return false;								//否则返回false
}


int main()
{
	cout << "E22314049 谷昕璐" << endl;
	int n = 0;											//n为进程数，实现程序和数据分离
	cout << "请输入作业数：";
	cin >> n;
	vector<Process> processes;							//创建进程数组
	processes.emplace_back();							//第一个进程为空，使第一个进程的下标为1
	int arriveTime = 0;									//进程的到达时间
	int serveTime = 0;									//进程的服务时间
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << i + 1 << "个进程的到达时间和服务时间：";
		cin >> arriveTime >> serveTime;
		processes.emplace_back(arriveTime, serveTime);	//初始化进程对象
	}
	int queue[4][10] = { 0 };							//创建4个队列，每个队列最多10个进程，自上而下优先级递减
	int timeSlice[4] = { 1,2,4,8 };						//不同队列的时间片大小
	queue[0][0] = 1;									//第一个队列的第一个进程为1号进程
	int queueIndex = 0;									//队列索引，表示当前正在执行的队列
	int queueEndIndex[4] = { 1,0,0,0 };					//队列结束索引，表示队列最后一个进程之后下一个位置的索引
	int processIndex = 1;								//进程索引，表示当前正在执行的进程
	int nextProcess = 2;								//下一个即将到来的进程的索引
	int finishedProcess = 0;							//已完成的进程数
	bool isPreempted = false;							//是否抢占
	int runTime = processes[1].getArriveTime();			//当前时间为第一个进程的到达时间
	//当前还有进程没有结束时继续循环
	while (!isFinished(finishedProcess, n))
	{
		if (!isEmptyQueue(queue[queueIndex]))
			//如果当前队列不为空就做RR算法
		{
			if (nextProcess<=n && runTime + timeSlice[queueIndex] > processes[nextProcess].getArriveTime())
				//如果在当前时间片内有新进程到达，那么抢占
			{
				int tail = queueEndIndex[0];	//获取第一个队列的队尾位置
				queue[0][tail] = nextProcess;	//将新进程放入第一个队列的队尾
				queueEndIndex[0]++;			//队列的队尾位置加1
				nextProcess++;							//下一个即将到来的进程索引+1
			}
			RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, nextProcess, n, runTime, finishedProcess, isPreempted);	//调用RR函数，进行时间片轮转
		}
		if (isPreempted)
		{
			//如果被抢占，从最高优先级的队列开始执行
			queueIndex = 0;
			processIndex = queue[queueIndex][0];		//获取当前队列的队首进程
			isPreempted = false;						//如果当前进程被抢占，那么将抢占标志置为false
			continue;									//继续执行下一个进程
		}
		//如果没有新进程到达
		if (nextProcess > n)
		{
			while (!isEmptyQueue(queue[queueIndex]))
			{
				processIndex = queue[queueIndex][0];	//获取当前队列的队首进程
				RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, nextProcess, n, runTime, finishedProcess, isPreempted);
			}
			//说明当前队列的进程都执行完了，执行下一级队列的进程
			queueIndex++;								//队列索引加1，表示下一个队列
			processIndex = queue[queueIndex][0];		//下一个执行的进程是队头进程
			continue;
		}

		if (processIndex + 1 < processes.size() && runTime < processes[nextProcess].getArriveTime())
			//如果当前时间小于下一个进程的到达时间
		{
			if (isEmptyQueue(queue[queueIndex]))
				//说明当前队列为空，执行下一级队列的进程
				queueIndex++;											//队列索引加1，表示下一个队列
			processIndex = queue[queueIndex][0];					//开始执行下一个队列队首的元素
			continue;
		}
		else
		{
			//说明当前进程还在执行的时候下一个进程已经到达，那么现在执行优先级高的队列的新进程
			queueIndex = 0;										//队列索引归0，表示去优先级最高的队列执行进程
			if (nextProcess < processes.size())
				//保证不溢出
			{
				processIndex = nextProcess;							//执行新来的进程
				int tail = queueEndIndex[queueIndex];				//获取当前队列的队尾位置
				queue[queueIndex][tail] = processIndex;				//将新来的进程放入队列的队尾
				queueEndIndex[queueIndex]++;						//队列的队尾位置加1
				nextProcess++;										//下一个即将到来的进程索引+1
			}
			continue;
		}
	}
	cout << "进程调度结束，下面展示进程完成时间：" << endl;
	for (int i = 1; i <= n; i++)
		cout << "第" << i << "个进程的完成时间为：" << processes[i].getFinishTime() << endl;
	return 0;
}