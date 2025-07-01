/*�༶�������е����㷨
* ��ռʽ
* ʵ�����ڣ�2025.4.17
E22314049 ����
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Process
{
private:
	int arriveTime;			//���̵ĵ���ʱ��
	int serveTime;			//���̵ķ���ʱ��
	int needTime;			//���̵�ʣ��ʱ��=����ʱ��-����ɵ�ʱ��
	int finishTime;			//���̵����ʱ��
	int time2BeContinued;	//�����������ռ��ʣ�µ�ʱ��Ƭ��ʱ��

public:
	//Ĭ�Ϲ��캯��
	Process() {}
	//���캯��������ֻ���������֪�ĵ���ʱ��ͷ���ʱ�䣬����Ľ���ʱʱ��Ĭ��Ϊ0
	Process(int _arriveTime, int _serveTime) :arriveTime(_arriveTime), serveTime(_serveTime), needTime(_serveTime), finishTime(0), time2BeContinued(0) {}
	int getArriveTime() { return arriveTime; }	//��ȡ���̵ĵ���ʱ��
	int getServeTime() { return serveTime; }	//��ȡ���̵ķ���ʱ��
	int getNeedTime() { return needTime; }		//��ȡ���̵�ʣ��ʱ��
	int getFinishTime() { return finishTime; }	//��ȡ���̵����ʱ��
	int getTime2BeContinued() { return time2BeContinued; }										//��ȡ���̵�ʣ��ʱ��Ƭ
	void setNeedTime(int _needTime) { needTime = _needTime; }									//���ý��̵�ʣ��ʱ��
	void setFinishTime(int _finishTime) { finishTime = _finishTime; }							//���ý��̵����ʱ��
	void setTime2BeContinued(int _time2BeContinued) { time2BeContinued = _time2BeContinued; }	//���ý��̵�ʣ��ʱ��Ƭ
};

//�ж϶༶���������Ƿ�Ϊ�գ��շ���true���ǿշ���false
//���������һ���༶�������У���һά����
bool isEmptyQueue(const int queue[])
{
	if (queue[0] != 0)	        //������еĵ�һ��Ԫ�ز�Ϊ0��˵�����в�Ϊ��
		return false;
	return true;					//����Ϊ��
}

//���׽��̳��Ӻ󣬰Ѻ����ŶӵĽ�������ǰ��
void setQueue(int queeuIndex, int queue[], int queueEndIndex[])
{
	for (int i = 0; i < 9; i++)
		queue[i] = queue[i + 1];				//�������е�Ԫ������ǰ��
	queueEndIndex[queeuIndex]--;				//���еĽ���������1
	queue[queueEndIndex[queeuIndex]] = 0;		//�����е����һ��Ԫ����Ϊ0
}

//ʱ��Ƭ��ת�����㷨���ж����е���ҵ
//�����ά������У���ͬ���е�ʱ��Ƭ�����̣���ǰ�����±�queueIndex����β�����ڶ����е�λ�ã���ǰ������̵��±꣬��һ�����̵��±꣬���н���������ǰʱ�䣬����ɵĽ�����, �Ƿ���ռ
void RR(int queue[][10], int timeSlice[], vector<Process>& processes, int queueIndex, int queueEndIndex[], int processIndex, int nextProcess, int n, int& runTime, int& finishedProcess, bool &isPreempted)
{
	int processNeedTime = processes[processIndex].getNeedTime();						//��ȡ��ǰ���̵�ʣ��ʱ��
	int time2BeContinued = processes[processIndex].getTime2BeContinued();					//��ȡ��ǰ���̵�ʣ��ʱ��Ƭ
	if (time2BeContinued == 0)
		time2BeContinued = timeSlice[queueIndex];						//�����ǰ���̵�ʣ��ʱ��ƬΪ0��˵����ǰ����û�б���ռ������ô���õ�ǰ���е�ʱ��Ƭ
	if (nextProcess > n)
		nextProcess = n;												//��ֹ�������
	if ((processIndex!=nextProcess) && (runTime< processes[nextProcess].getArriveTime()) && (runTime + time2BeContinued > processes[nextProcess].getArriveTime()))
		//����ڵ�ǰʱ��Ƭ�����½��̵����ô��ռ
	{
		int processTime = processes[nextProcess].getArriveTime() - runTime;				//��ǰʱ��Ƭ�ڵ�ǰ���̿���ִ�е�ʱ��	
		if (processTime > processNeedTime)												//�����ǰ���̵�ʣ��ʱ����ڵ�ǰʱ��Ƭ�ڿ���ִ�е�ʱ�䣬��ô����ռ
		{
			runTime += processNeedTime;														//��ǰʱ����ϵ�ǰ���̵�ʣ��ʱ��
			processes[processIndex].setNeedTime(0);											//��ǰ���̵�ʣ��ʱ�����0
			processes[processIndex].setFinishTime(runTime);									//��ǰ���̵����ʱ����ڵ�ǰʱ��
			cout << "��" << processIndex << "�������ڵ�" << runTime - processNeedTime << "ʱ�̿�ʼִ�У�ִ����" << processNeedTime << "����λ��ʱ�䣬�ý��̵��Ƚ���" << endl;
			finishedProcess++;																//����ɵĽ�������1
			processes[processIndex].setTime2BeContinued(0);									//��ǰ���̵�ʣ��ʱ��Ƭ����0
		}
		else //��ռ
		{
			runTime += processTime;														//��ǰʱ����ϵ�ǰ���̿���ִ�е�ʱ��
			processes[processIndex].setNeedTime(processNeedTime - processTime);				//��ǰ���̵�ʣ��ʱ����ڵ�ǰ��ʣ��ʱ���ȥ��ǰʱ��Ƭ�ڿ���ִ�е�ʱ��
			cout << "��" << processIndex << "�������ڵ�" << runTime << "ʱ�̿�ʼִ�У�ִ����" << processTime << "����λ��ʱ�䣬ʣ��" << processes[processIndex].getNeedTime() << "����λ��ʱ��" << endl;
			int putIndex = queueEndIndex[queueIndex];										//�õ���ǰ���еĶ�βλ��
			queue[queueIndex][putIndex] = processIndex;										//����ǰ���̷��뵱ǰ���еĶ�β
			queueEndIndex[queueIndex]++;													//��ǰ���еĶ�βλ�ü�1
			processes[processIndex].setTime2BeContinued(time2BeContinued - processTime);		//��ǰ���̵�ʣ��ʱ��Ƭ���ڵ�ǰ��ʣ��ʱ���ȥ��ǰʱ��Ƭ�ڿ���ִ�е�ʱ��
			isPreempted = true;																//��ǰ���̱���ռ
		}
	}
	else {
		//����ռ
		if (processNeedTime > time2BeContinued)										//�����ǰ���̵�ʣ��ʱ�����ʱ��Ƭ
		{
			runTime += time2BeContinued;												//��ǰʱ�����ʱ��Ƭ
			processes[processIndex].setNeedTime(processNeedTime - time2BeContinued);	//��ǰ���̵�ʣ��ʱ����ڵ�ǰ��ʣ��ʱ���ȥʱ��Ƭ
			cout << "��" << processIndex << "�������ڵ�" << runTime - time2BeContinued << "ʱ�̿�ʼִ�У�ִ����" << time2BeContinued << "����λ��ʱ�䣬ʣ��" << processes[processIndex].getNeedTime() << "����λ��ʱ��" << endl;
			int putIndex = queueEndIndex[queueIndex + 1];									//�õ���һ�����еĶ�βλ��
			queue[queueIndex + 1][putIndex] = processIndex;									//����ǰ���̷�����һ�����еĶ�β
			queueEndIndex[queueIndex + 1]++;												//��һ�����еĶ�βλ�ü�1
		}
		else
		{
			runTime += processNeedTime;													    //��ǰʱ����ϵ�ǰ���̵�ʣ��ʱ��
			processes[processIndex].setNeedTime(0);											//��ǰ���̵�ʣ��ʱ�����0
			processes[processIndex].setFinishTime(runTime);									//��ǰ���̵����ʱ����ڵ�ǰʱ��
			cout << "��" << processIndex << "�������ڵ�" << runTime - processNeedTime << "ʱ�̿�ʼִ�У�ִ����" << processNeedTime << "����λ��ʱ�䣬�ý��̵��Ƚ���" << endl;
			finishedProcess++;																//����ɵĽ�������1
		}
	}
	setQueue(queueIndex, queue[queueIndex], queueEndIndex);									//����ǰ���еĶ��׽��̳���,����Ľ�������ǰ��
	cout << "��ǰʱ��Ϊ" << runTime << endl;												//�����ǰʱ��
}

bool isFinished(int finishedProcess, int n)		//�ж��Ƿ����н��̶����
{
	if (finishedProcess == n)					//������н��̶���ɣ�����true
		return true;
	return false;								//���򷵻�false
}


int main()
{
	cout << "E22314049 ����" << endl;
	int n = 0;											//nΪ��������ʵ�ֳ�������ݷ���
	cout << "��������ҵ����";
	cin >> n;
	vector<Process> processes;							//������������
	processes.emplace_back();							//��һ������Ϊ�գ�ʹ��һ�����̵��±�Ϊ1
	int arriveTime = 0;									//���̵ĵ���ʱ��
	int serveTime = 0;									//���̵ķ���ʱ��
	for (int i = 0; i < n; i++)
	{
		cout << "�������" << i + 1 << "�����̵ĵ���ʱ��ͷ���ʱ�䣺";
		cin >> arriveTime >> serveTime;
		processes.emplace_back(arriveTime, serveTime);	//��ʼ�����̶���
	}
	int queue[4][10] = { 0 };							//����4�����У�ÿ���������10�����̣����϶������ȼ��ݼ�
	int timeSlice[4] = { 1,2,4,8 };						//��ͬ���е�ʱ��Ƭ��С
	queue[0][0] = 1;									//��һ�����еĵ�һ������Ϊ1�Ž���
	int queueIndex = 0;									//������������ʾ��ǰ����ִ�еĶ���
	int queueEndIndex[4] = { 1,0,0,0 };					//���н�����������ʾ�������һ������֮����һ��λ�õ�����
	int processIndex = 1;								//������������ʾ��ǰ����ִ�еĽ���
	int nextProcess = 2;								//��һ�����������Ľ��̵�����
	int finishedProcess = 0;							//����ɵĽ�����
	bool isPreempted = false;							//�Ƿ���ռ
	int runTime = processes[1].getArriveTime();			//��ǰʱ��Ϊ��һ�����̵ĵ���ʱ��
	//��ǰ���н���û�н���ʱ����ѭ��
	while (!isFinished(finishedProcess, n))
	{
		if (!isEmptyQueue(queue[queueIndex]))
			//�����ǰ���в�Ϊ�վ���RR�㷨
		{
			if (nextProcess<=n && runTime + timeSlice[queueIndex] > processes[nextProcess].getArriveTime())
				//����ڵ�ǰʱ��Ƭ�����½��̵����ô��ռ
			{
				int tail = queueEndIndex[0];	//��ȡ��һ�����еĶ�βλ��
				queue[0][tail] = nextProcess;	//���½��̷����һ�����еĶ�β
				queueEndIndex[0]++;			//���еĶ�βλ�ü�1
				nextProcess++;							//��һ�����������Ľ�������+1
			}
			RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, nextProcess, n, runTime, finishedProcess, isPreempted);	//����RR����������ʱ��Ƭ��ת
		}
		if (isPreempted)
		{
			//�������ռ����������ȼ��Ķ��п�ʼִ��
			queueIndex = 0;
			processIndex = queue[queueIndex][0];		//��ȡ��ǰ���еĶ��׽���
			isPreempted = false;						//�����ǰ���̱���ռ����ô����ռ��־��Ϊfalse
			continue;									//����ִ����һ������
		}
		//���û���½��̵���
		if (nextProcess > n)
		{
			while (!isEmptyQueue(queue[queueIndex]))
			{
				processIndex = queue[queueIndex][0];	//��ȡ��ǰ���еĶ��׽���
				RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, nextProcess, n, runTime, finishedProcess, isPreempted);
			}
			//˵����ǰ���еĽ��̶�ִ�����ˣ�ִ����һ�����еĽ���
			queueIndex++;								//����������1����ʾ��һ������
			processIndex = queue[queueIndex][0];		//��һ��ִ�еĽ����Ƕ�ͷ����
			continue;
		}

		if (processIndex + 1 < processes.size() && runTime < processes[nextProcess].getArriveTime())
			//�����ǰʱ��С����һ�����̵ĵ���ʱ��
		{
			if (isEmptyQueue(queue[queueIndex]))
				//˵����ǰ����Ϊ�գ�ִ����һ�����еĽ���
				queueIndex++;											//����������1����ʾ��һ������
			processIndex = queue[queueIndex][0];					//��ʼִ����һ�����ж��׵�Ԫ��
			continue;
		}
		else
		{
			//˵����ǰ���̻���ִ�е�ʱ����һ�������Ѿ������ô����ִ�����ȼ��ߵĶ��е��½���
			queueIndex = 0;										//����������0����ʾȥ���ȼ���ߵĶ���ִ�н���
			if (nextProcess < processes.size())
				//��֤�����
			{
				processIndex = nextProcess;							//ִ�������Ľ���
				int tail = queueEndIndex[queueIndex];				//��ȡ��ǰ���еĶ�βλ��
				queue[queueIndex][tail] = processIndex;				//�������Ľ��̷�����еĶ�β
				queueEndIndex[queueIndex]++;						//���еĶ�βλ�ü�1
				nextProcess++;										//��һ�����������Ľ�������+1
			}
			continue;
		}
	}
	cout << "���̵��Ƚ���������չʾ�������ʱ�䣺" << endl;
	for (int i = 1; i <= n; i++)
		cout << "��" << i << "�����̵����ʱ��Ϊ��" << processes[i].getFinishTime() << endl;
	return 0;
}