/*
���̵����е������ȷ���(FCFS)�㷨
ʵ�����ڣ�2025.5.27
E22314049 ����
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> processes;					// ����һ����̬���飬������Ŵŵ���

//���̵����е������ȷ���(FCFS)�㷨
void FCFS() {
	int head = 100;						// ��ͷ��ʼλ��
	float sumMove = 0;					// �ƶ��ŵ���֮��,Ϊ�˼���ƽ��Ѱ������(С��)����������float
	for (int i = 0; i < processes.size(); i++) {
		cout << "���ʴŵ��ţ�" << processes[i] << ' ';	// �����ǰ���ʵĴŵ���
		cout << "��ͷ�ƶ����룺" << abs(head - processes[i]) << endl;	// �����ͷ�ƶ�����,ע���Ǿ���ֵ
		sumMove += abs(head - processes[i]);			// �ۼӴ�ͷ�ƶ����룬ע���Ǿ���ֵ
		head = processes[i];			// ���´�ͷλ��
	}
	cout << "ƽ��Ѱ�����ȣ�" << sumMove / processes.size() << endl;		// ���ƽ��Ѱ������
}

int main() {
	cout << "E22314049 ����" << endl;
	//ʵ��������������
	while (true) {
		int process;
		cin >> process;
		processes.push_back(process);	// ������Ľ��̷��ʵĴŵ��Ŵ��붯̬����
		if (cin.get() == '\n')
			break;
	}
	FCFS();
}