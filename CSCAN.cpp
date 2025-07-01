/*
���̵����е�ѭ��ɨ��(CSCAN)�㷨
ʵ�����ڣ�2025.6.10
E22314049 ����
*/
#include <iostream>
#include <vector>
#include <algorithm>						
using namespace std;

vector<int> processes;						// ����һ����̬���飬������Ŵŵ���
int head = 100;								// ��ͷ��ʼλ��
bool isIncrease = true;						// ��ͷ�ƶ�����true��ʾ��ŵ������ӷ����ƶ���false��ʾ��ŵ�����С�����ƶ�
float sumMove = 0;							// ��ʼ���ܵ��ƶ�����
int l = -1;									// ���ݵ��±߽磬��ʾ���һ��С�ڴ�ͷλ�õĴŵ��ŵ�����
int r = -1;									// ���ݵ��ϱ߽磬��ʾ��һ�����ڴ�ͷλ�õĴŵ��ŵ�����

// ���´�ͷλ�ò������ǰ���ʴŵ������ƶ����룬���ú���������������
void set(int j) {
	cout << "��ǰ���ʴŵ�����" << processes[j] << ' ';
	cout << "�ƶ����룺" << abs(processes[j] - head) << endl;
	sumMove += abs(processes[j] - head);	// �ۼ��ƶ�����
	head = processes[j];				    // ���´�ͷλ��
}

// �����Ұ�����飬�����ƶ���ͷ
void upRight() {
	for (int j = r; j < processes.size(); j++) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

// �����������飬�����ƶ���ͷ
void upLeft() {
	for (int j = 0; j <= l; j++) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

// �����������飬�����ƶ���ͷ
void downLeft() {
	for (int j = l; j >= 0; j--) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

// �����Ұ�����飬�����ƶ���ͷ
void downRight() {
	for (int j = processes.size() - 1; j >= r; j--) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

//���̵����е�ѭ��ɨ��(CSCAN)�㷨
void CSCAN() {
	//���ҵ������ڲ��ı߽�
	for (int i = 0; i < processes.size(); i++) {
		// ����ŵ���С�ڴ�ͷλ�ã�����lΪ��ǰ����
		if (processes[i] < head) {
			l = i;
			r = l + 1; // ��һ�����ڴ�ͷλ�õĴŵ��ŵ���������ָ���һ��Ԫ��
			continue;
		}
		// ����ŵ��Ÿպõ��ڴ�ͷλ�ã�ֱ�������ǰ���ʴŵ������ƶ�����
		if (processes[i] == head) {
			cout << "��ǰ���ʴŵ�����" << processes[i] << ' ';
			cout << "�ƶ����룺0" << endl;
			r = i + 1; // ��һ�����ڴ�ͷλ�õĴŵ��ŵ���������ָ���һ��Ԫ��
			continue;
		}
		if (processes[i] > head) {
			r = i;	// r�ǵ�һ�����ڴ�ͷλ�õĴŵ��ŵ�����
			break;
		}
	}

	//����ƶ���������ŵ������ӷ����ƶ�
	if (isIncrease) {
		// �����Ұ�����������ƶ�
		upRight();
		//�����������������ƶ�
		upLeft();
	}
	// ����ƶ���������ŵ�����С�����ƶ�
	else {
		// �����������������ƶ�
		downLeft();
		// �����Ұ�����������ƶ�
		downRight();
	}

	cout << "ƽ��Ѱ�����ȣ�" << sumMove / processes.size() << endl; // ���ƽ��Ѱ������
}

int main() {
	cout << "E22314049 ����" << endl;
	//ʵ��������������
	while (true) {
		int process;
		cin >> process;
		processes.push_back(process);		  // ������Ľ��̷��ʵĴŵ��Ŵ��붯̬����
		if (cin.get() == '\n')
			break;
	}
	sort(processes.begin(), processes.end());// �Դŵ��Ž�������
	CSCAN();
}