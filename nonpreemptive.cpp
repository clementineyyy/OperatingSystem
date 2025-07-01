/*�༶�������е����㷨
* ����ռʽ
* ʵ�����ڣ�2025.4.15
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

public:
	//Ĭ�Ϲ��캯��
	Process(){}
	//���캯��������ֻ���������֪�ĵ���ʱ��ͷ���ʱ�䣬����Ľ���ʱʱ��Ĭ��Ϊ0
	Process(int _arriveTime, int _serveTime) :arriveTime(_arriveTime), serveTime(_serveTime), needTime(_serveTime), finishTime(0) {}
	int getArriveTime() { return arriveTime; }	//��ȡ���̵ĵ���ʱ��
	int getServeTime() { return serveTime; }	//��ȡ���̵ķ���ʱ��
	int getNeedTime() { return needTime; }		//��ȡ���̵�ʣ��ʱ��
	int getFinishTime() { return finishTime; }	//��ȡ���̵����ʱ��
	void setNeedTime(int _needTime) { needTime = _needTime; }	//���ý��̵�ʣ��ʱ��
	void setFinishTime(int _finishTime) { finishTime = _finishTime; }	//���ý��̵����ʱ��
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
void setQueue(int queeuIndex, int queue[],int queueEndIndex[])
{
	for (int i = 0; i < 9; i++)
		queue[i] = queue[i + 1];				//�������е�Ԫ������ǰ��
	queueEndIndex[queeuIndex]--;				//���еĽ���������1
	queue[queueEndIndex[queeuIndex]] = 0;		//�����е����һ��Ԫ����Ϊ0
}

//ʱ��Ƭ��ת�����㷨���ж����е���ҵ
//�����ά������У���ͬ���е�ʱ��Ƭ�����̣���ǰ�����±�queueIndex����β�����ڶ����е�λ�ã���ǰ������̵��±꣬��ǰʱ��
void RR(int queue[][10], int timeSlice[], vector<Process>& processes, int queueIndex, int queueEndIndex[], int processIndex, int& runTime, int &finishedProcess)
{
	int processNeedTime = processes[processIndex].getNeedTime();						//��ȡ��ǰ���̵�ʣ��ʱ��
	if (processNeedTime > timeSlice[queueIndex])										//�����ǰ���̵�ʣ��ʱ�����ʱ��Ƭ
	{
		runTime += timeSlice[queueIndex];												//��ǰʱ�����ʱ��Ƭ
		processes[processIndex].setNeedTime(processNeedTime - timeSlice[queueIndex]);	//��ǰ���̵�ʣ��ʱ����ڵ�ǰ��ʣ��ʱ���ȥʱ��Ƭ
		cout << "��" << processIndex << "�������ڵ�" << runTime - timeSlice[queueIndex] << "ʱ�̿�ʼִ�У�ִ����" << timeSlice[queueIndex] << "����λ��ʱ�䣬ʣ��" << processes[processIndex].getNeedTime() << "����λ��ʱ��" << endl;
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
	setQueue(queueIndex, queue[queueIndex], queueEndIndex);													//����ǰ���еĶ��׽��̳���,����Ľ�������ǰ��
	cout << "��ǰʱ��Ϊ" << runTime << endl;											//�����ǰʱ��
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
		cout << "�������" << i+1 << "�����̵ĵ���ʱ��ͷ���ʱ�䣺";
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
	int runTime = processes[1].getArriveTime();			//��ǰʱ��Ϊ��һ�����̵ĵ���ʱ��
	//��ǰ���н���û�н���ʱ����ѭ��
	while (!isFinished(finishedProcess, n))
	{
		//�Ե�ǰ����ִ��1��RR�����㷨
		if (!isEmptyQueue(queue[queueIndex]))
			RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, runTime, finishedProcess);	//����RR����������ʱ��Ƭ��ת
		//���û���½��̵���
		if (nextProcess > n)
		{
			while (!isEmptyQueue(queue[queueIndex]))
			{
				processIndex = queue[queueIndex][0];	//��ȡ��ǰ���еĶ��׽���
				RR(queue, timeSlice, processes, queueIndex, queueEndIndex, processIndex, runTime, finishedProcess);
			}
			//˵����ǰ���еĽ��̶�ִ�����ˣ�ִ����һ�����еĽ���
			queueIndex++;								//����������1����ʾ��һ������
			processIndex = queue[queueIndex][0];		//��һ��ִ�еĽ����Ƕ�ͷ����
			continue;
		}

		if (processIndex + 1 < processes.size() && runTime < processes[nextProcess].getArriveTime())	
			//�����ǰʱ��С����һ�����̵ĵ���ʱ��
		{
			if(isEmptyQueue(queue[queueIndex]))
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