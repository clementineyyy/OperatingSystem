/*
����洢�����е��Ƚ��ȳ�(FIFO)ҳ���û��㷨
ʵ�����ڣ�2025.5.13
E22314049 ����
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> pages;								//����һ����̬���飬�������ҳ���
vector<int> frames;								//����һ����̬���飬�������������
vector<int> pageFaults;							//����һ����̬���飬�������ȱҳ��ҳ���
vector<int> removePages;						//����һ����̬���飬������ű�������ҳ���
const int FRAME_SIZE = 3;						//���������Ĵ�СΪ3

//�жϵ�ǰ��ҳ����Ƿ����������
bool findPageInFrames(int page) {
	vector<int>::iterator it = find(frames.begin(), frames.end(), page);
	if (it != frames.end())
		return true;	//����ҵ���ҳ��ţ�����true
	else
		return false;	//���û�ҵ�ҳ��ţ�����false
}

//�ѵ�һ��������е�ҳ����û���ȥ
void removePage() {
	//�õ�������е�һ��ҳ��ŵĵ�����
	vector<int>::iterator remove = frames.begin();
	removePages.push_back(*remove);				//�ѱ�������ҳ��ŷŽ���������ҳ�������
	frames.erase(remove);						//���������ɾ����������ҳ���
}


//����û��㷨
void FIFO() {
	vector<int>::iterator it = pages.begin();	//����һ������������������ҳ������ô�����ʼ��Ϊҳ������ô��Ŀ�ʼλ��
	for (; it != pages.end(); ++it) {
		//�����ǰ��ҳ�������������У��Ͳ�ȱҳ
		if (findPageInFrames(*it))
			continue;
		//��������ǰ��ҳ��Ų���������ж��ҵ�ǰ�����û��������ôֱ�Ӱѵ�ǰ��ҳ��ŷŽ������,����������һ��ȱҳ
		else if (frames.size() < FRAME_SIZE) {
			frames.push_back(*it);
			pageFaults.push_back(*it);			//�ѵ�ǰ��ҳ��ŷŽ�ȱҳ����
			continue;
		}
		//�����ǰ��ҳ��Ų���������У����ҵ�ǰ��������ˣ���ô��Ҫ����ҳ���û�
		else {
			removePage();
			frames.push_back(*it);				//�ѵ�ǰ��ҳ��ŷŽ������
			pageFaults.push_back(*it);			//�ѵ�ǰ��ҳ��ŷŽ�ȱҳ����
		}
	}
}

//���ҳ������ô�
void showPage(vector<int> page) {
	for (int v : page)
		cout << v << " ";
	cout << endl;
}

//����ȱҳ��=ȱҳ��/ҳ������ô�����
float calcPageFaultRate() {
	//��Ϊ������������Խ���ǿ������ת��
	return pageFaults.size() / (float)pages.size();
}


int main() {
	cout << "E22314049 ����" << endl;
	int page = 0;
	cout << "ҳ������ô�Ϊ��";
	//ʵ���������㷨���룬�û��Ӽ�������һ��ҳ���
	while (cin >> page) {
		//ҳ��ż��뵽ҳ������ô���β��
		pages.push_back(page);
		//���������ǻ��з������˳�ѭ��
		if (cin.get() == '\n')
			break;
	}
	//�����Ƚ��ȳ��㷨
	FIFO();
	//���ȱҳ��ҳ���
	cout << "ȱҳ��ҳ���Ϊ��";
	showPage(pageFaults);
	//�����������ҳ���
	cout << "��������ҳ���Ϊ��";
	showPage(removePages);
	//���ȱҳ��
	cout << "ȱҳ��Ϊ��";
	cout << calcPageFaultRate() << endl;
}