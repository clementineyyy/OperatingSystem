/*
���̵����е����Ѱ��ʱ������(SSTF)�㷨
ʵ�����ڣ�2025.5.27
E22314049 ����
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> processes;						// ����һ����̬���飬������Ŵŵ���
int head = 100;								// ��ͷ��ʼλ��

//���̵����е����Ѱ��ʱ������(SSTF)�㷨
void SSTF() {
	int minIndex = 0;						// ��ʼ����С�ƶ������Ӧ�Ľ��̺�
	float sumMove = 0;						// ��ʼ�����ƶ�����,Ϊ�˼���ƽ��Ѱ������(С��)����������float
	int size = processes.size();			// �������鳤��
	for (int t = 0; t < size; t++) {		//t����ѭ��������ֱ�����н��̶�������
		//���������ҵ�����ı����ʵĴŵ���
		int minDistance = 10000;				// ��ʼ����С�ƶ�����
		for (int i = 0; i < processes.size(); i++) {
			// �����ǰ����Ҫ����ʵĴŵ�������С�ƶ����뻹С���͸�����С�ƶ�����
			int distance = abs(head - processes[i]);
			if (distance <= minDistance) {
				minDistance = distance;	// ������С�ƶ�����
				minIndex = i;				// ������С�ƶ������Ӧ�Ľ��̺�		
			}
		}
		cout << "���ʴŵ��ţ�" << processes[minIndex] << ' ';	// ������ʵĴŵ���
		cout << "��ͷ�ƶ����룺" << minDistance << endl;		// �����ͷ�ƶ�����
		sumMove += minDistance;				// �ۼ����ƶ�����
		head = processes[minIndex];			// ���´�ͷλ��
		processes.erase(processes.begin() + minIndex);			// ɾ���ѷ��ʵĴŵ���
	}
	cout << "ƽ��Ѱ�����ȣ�" << sumMove / size << endl;		// ���ƽ��Ѱ������
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
	SSTF();
}
