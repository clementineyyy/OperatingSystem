/*
����ҵ����(SJF)�����㷨
ʵ�����ڣ�2025.4.1
E22314049 ����
*/

#include <iostream>
#include <algorithm>
using namespace std;

//���ڲ�ͬ��ҵ�и��Եĵ���ʱ�䣬����ʱ���ʱ�䣬��˶���һ���ṹ�����洢��ҵ����Ϣ
struct job
{
	char label = 'A';					//��ҵ����
	int arriveTime = 0;					//����ʱ��
	int serveTime = 0;					//����ʱ��
	int startTime = 0;					//��ʼִ��ʱ��
	int finishTime = 0;					//���ʱ��
	//��תʱ�䣬���ڴ�Ȩ��תʱ������תʱ����Է���ʱ�䣬������С������˶�����תʱ����float���ͣ�������־�������
	float turnAroundTime = 0;
	float weightedTurnAroundTime = 0;	//��Ȩ��תʱ��
	bool isOperated = false;			//����ҵ�Ƿ��Ѿ�������
};

//������ʱ������,�ú�����Ϊsort�����еıȽ���������sort����������ҵ�ĵ���ʱ���С��������
int compareSequence(job a, job b)
{
	return a.arriveTime < b.arriveTime;
}

//������ʱ������,�ú�����Ϊsort�����еıȽ���������sort����ʵ�ֶ���ҵ����
int compareServeTime(job a, job b)
{
	return a.serveTime < b.serveTime;
}

//����ҵ��������,�ú�����Ϊsort�����еıȽ���������sort����������ҵ�����ƴ�С��������
int compareLabel(job a, job b)
{
	return a.label < b.label;
}

int main()
{
	cout << "E22314049 ����" << endl;
	int n = 0;					//��ҵ��	
	cout << "��������ҵ����";
	cin >> n;
	job* jobs = new job[n];		//����n����ҵ
	//�����������룬�û�������ҵ�ĵ���ʱ��͹��Ƶķ���ʱ��
	for (int i = 0; i < n; i++)
	{
		cout << "�������" << i + 1 << "����ҵ�ĵ���ʱ��ͷ���ʱ�䣺";
		cin >> jobs[i].arriveTime >> jobs[i].serveTime;
		jobs[i].label = 'A' + i;
	}

	//�Ȱ�����ʱ�������ҵ����ȵ������ҵ��һ��ִ��
	sort(jobs, jobs + n, compareSequence);
	int time = jobs[0].arriveTime;		//��ǰʱ���ǵ�һ����ҵ�ĵ���ʱ�䣬δ����0
	jobs[0].startTime = time;			//��һ����ҵ�Ŀ�ʼִ��ʱ���ǵ�ǰʱ��
	jobs[0].finishTime = time + jobs[0].serveTime;	//��һ����ҵ�����ʱ��=��ʼִ��ʱ��+����ʱ��
	jobs[0].turnAroundTime = jobs[0].finishTime - jobs[0].arriveTime;	//��һ����ҵ����תʱ��=���ʱ��-����ʱ��
	jobs[0].weightedTurnAroundTime = jobs[0].turnAroundTime / jobs[0].serveTime;	//��һ����ҵ�Ĵ�Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
	jobs[0].isOperated = true;			//��һ����ҵ�Ѿ�������
	time = jobs[0].finishTime;			//���µ�ǰʱ��,��ǰʱ����ǵ�һ����ҵ�����ʱ��

	sort(jobs, jobs + n, compareServeTime);	//������ʱ������ʵ�ֶ���ҵ����
	for (int i = 0; i < n; i++)
	{
		if (jobs[i].isOperated)		//�������ҵ�Ѿ������У����������ǵ���һ���������ҵ�Ѿ������е����
			continue;
		//��ҵ�Ŀ�ʼִ��ʱ��Ϊ��ǰʱ��͵���ʱ���е����ֵ
		jobs[i].startTime = max(time, jobs[i].arriveTime);
		//��ҵ�����ʱ��=��ʼִ��ʱ��+����ʱ��
		jobs[i].finishTime = jobs[i].startTime + jobs[i].serveTime;
		//���µ�ǰʱ��,��ǰʱ�������ҵ�����ʱ��
		time = jobs[i].finishTime;
		//��ҵ����תʱ��=���ʱ��-����ʱ��
		jobs[i].turnAroundTime = jobs[i].finishTime - jobs[i].arriveTime;
		//��ҵ�Ĵ�Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
		jobs[i].weightedTurnAroundTime = jobs[i].turnAroundTime / jobs[i].serveTime;
		jobs[i].isOperated = true;		//����ҵ�Ѿ�������
	}
	float averageTurnAroundTime = 0;		//ƽ����תʱ��
	float averageWeightedTurnAroundTime = 0;	//ƽ����Ȩ��תʱ��
	for (int i = 0; i < n; i++)
	{
		//ƽ����תʱ��=������ҵ����תʱ��֮��/��ҵ��
		averageTurnAroundTime += jobs[i].turnAroundTime;
		//ƽ����Ȩ��תʱ��=������ҵ�Ĵ�Ȩ��תʱ��֮��/��ҵ��
		averageWeightedTurnAroundTime += jobs[i].weightedTurnAroundTime;
	}
	averageTurnAroundTime /= n;
	averageWeightedTurnAroundTime /= n;

	//����ҵ��������,�����м䴦��ʱ��������������Ӧ��֤��ҵ�����˳��������˳��һ��
	sort(jobs, jobs + n, compareLabel);
	for (int i = 0; i < n; i++)
	{
		char c = 'A' + i;
		cout << "��ҵ" << c << "�Ŀ�ʼִ��ʱ�䣺" << jobs[i].startTime << endl;
		cout << "��ҵ" << c << "�����ʱ�䣺" << jobs[i].finishTime << endl;
		cout << "��ҵ" << c << "����תʱ�䣺" << jobs[i].turnAroundTime << endl;
		cout << "��ҵ" << c << "�Ĵ�Ȩ��תʱ�䣺" << jobs[i].weightedTurnAroundTime << endl;
		cout << endl;
	}
	cout << "ƽ����תʱ�䣺" << averageTurnAroundTime << endl;
	cout << "ƽ����Ȩ��תʱ�䣺" << averageWeightedTurnAroundTime << endl;
	return 0;
}