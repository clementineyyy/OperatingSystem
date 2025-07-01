/*
���̵����е�ɨ��(SCAN)�㷨
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

// �����ƶ���ͷ
void up() {
	for (int j = r; j < processes.size(); j++) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

// �����ƶ���ͷ
void down() {
	for (int j = l; j >= 0; j--) {
		set(j);		// ����set���������ǰ���ʴŵ������ƶ����룬�����´�ͷλ��
	}
}

//���̵����е�ɨ��(SCAN)�㷨
void SCAN() {			
	//���ҵ������ڲ��ı߽�
	for (int i = 0; i < processes.size(); i++) {
		// ����ŵ���С�ڴ�ͷλ�ã�����lΪ��ǰ����
		if (processes[i] < head) {
			l = i;
			continue;
		}
		// ����ŵ��Ÿպõ��ڴ�ͷλ�ã�ֱ�������ǰ���ʴŵ������ƶ�����
		if (processes[i] == head) {
			cout << "��ǰ���ʴŵ�����" << processes[i] << ' ';
			cout << "�ƶ����룺0" << endl;
			continue;
		}
		if (processes[i] > head) {
			r = i;	// r�ǵ�һ�����ڴ�ͷλ�õĴŵ��ŵ�����
			break;  // ��Ϊ�ǵ�һ�����ڴ�ͷλ�õĴŵ��ŵ����������ҵ����˳�ѭ��
		}
	}


	//����ƶ���������ŵ������ӷ����ƶ�
	if (isIncrease) {
		// ��Ϊ�����ź����ˣ�����ֱ�������ݣ������ƶ�
		up();
		// ��Ϊ�����ź����ˣ�����ֱ�������ݣ������ƶ�
		down();
	}
	// ����ƶ���������ŵ�����С�����ƶ�
	else {
		// ��Ϊ�����ź����ˣ�����ֱ�������ݣ������ƶ�
		down();
		// ��Ϊ�����ź����ˣ�����ֱ�������ݣ������ƶ�
		up();
	}
	
	cout << "ƽ��Ѱ�����ȣ�" << sumMove / processes.size() << endl; // ���ƽ��Ѱ������
}

int main() {
	cout << "E22314049 ����" << endl;
	//ʵ��������������
	while (true) {
		int process;
		cin >> process;
		processes.push_back(process);		// ������Ľ��̷��ʵĴŵ��Ŵ��붯̬����
		if (cin.get() == '\n')
			break;
	}
	sort(processes.begin(), processes.end());// �Դŵ��Ž�������
	SCAN();
}

