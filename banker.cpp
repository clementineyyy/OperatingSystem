/*
���м��㷨��������
ʵ�����ڣ�2025.4.29
E22314049 ����
*/
#include <iostream>
using namespace std;

class Matrix {
private:
	int a;			// A��Դ��ֵ
	int b;          // B��Դ��ֵ
	int c;          // C��Դ��ֵ

public:
	Matrix(int _a = 0, int _b = 0, int _c = 0) :a(_a), b(_b), c(_c) {}
	// ����һ�����̶Ը�����Դ��ֵ
	void setValue(int _a, int _b, int _c) {
		a = _a;
		b = _b;
		c = _c;
	}
	//��һ�εĿ�������Դ����work=��ǰ�Ŀ�������Դ����work+��������allocation
	void add(const Matrix& allocation) {
		a = a + allocation.a;
		b = b + allocation.b;
		c = c + allocation.c;
	}
	// ���̶���Դ���������=����������-�ѷ�����Դ����
	Matrix divide(const Matrix& allocated) {
		return { a - allocated.a,b - allocated.b,c - allocated.c };
	}
	//�ȽϽ��̶���Դ������Ϳ�����Դ�Ĵ�С�����������Դ���ڵ���������Դ���򷵻�true�����򷵻�false
	bool compare(const Matrix& work) const {
		return (a <= work.a && b <= work.b && c <= work.c);
	}
	//չʾ��Դ����ľ���ֵ
	void display() const {
		cout << "��ԴA:" << a << " ��ԴB:" << b << " ��ԴC:" << c << endl;
	}
};

class Process {
private:
	int id;								// ����ID
	Matrix max;							// �����Դ����
	Matrix allocated;					// �ѷ�����Դ
	Matrix need;						// ������Դ
	Matrix work;						// ������Դ

public:
	Process(int _id = 0, const Matrix& _max = { 0 }, const Matrix& allocated = { 0 }, const Matrix& need = { 0 }, const Matrix& _work = { 0 }) :
		id(_id), max(_max), allocated(allocated), need(need), work(_work) {}
	// ���ý��̵�ID�������Դ����max���ѷ�����Դallocated��������Դneed�͹�������work
	void setValue(int _id, const Matrix& _max, const Matrix& _allocated, const Matrix& _need,const Matrix& _work) {
		id = _id;
		max = _max;
		allocated = _allocated;
		need = _need;
		work = _work;
	}
	Matrix getAllocated() const { return allocated; }	// ��ȡ���̵��ѷ�����Դ����
	Matrix getNeed() const { return need; }				// ��ȡ���̵��������
	Matrix getWork() const { return work; }				// ��ȡ���̵Ĺ�������
	void setWork(const Matrix& _work) { work = _work; }	// ���ý��̵Ĺ�������
};

//�ж��ǲ������н��̵���Դ�������������
bool allFinished(bool finished[]) {
	for (int i = 0; i < 5; i++) {
		if (finished[i] == false) {
			return false;	// ֻҪ��һ������û����ɣ��ͷ���false
		}
	}
	return true;			// ������н��̶�����ˣ��ͷ���true
}

int main()
{
	cout << "E22314049 ����" << endl;
	Process p[5];					// ����5������
	int a = 0, b = 0, c = 0;
	cout << "�������������Դ������";
	cin >> a >> b >> c;
	Matrix available(a, b, c);			// ��ʼ��������Դ����
	for (int i = 0; i < 5; i++) {
		cout << "���������P" << i << "�������Դ����Max��";
		cin >> a >> b >> c;
		Matrix max(a, b, c);		// ��ʼ�������Դ�������
		cout << "���������P" << i << "���ѷ�����ԴAllocated��";
		cin >> a >> b >> c;
		Matrix allocated(a, b, c);	// ��ʼ���ѷ�����Դ����
		cout << "������㲢�������P" << i << "����Դ����Need" << endl;
		Matrix need = max.divide(allocated);
		need.display();
		p[i].setValue(i, max, allocated, need, available);
	}
	bool finished[5] = { 0 };			// ��¼������ɵĽ�����
	int runtimes = 0;
	bool signal = true;
	int line[5] = { 0 };				// ���յİ�ȫ����
	int j = 0;							// ��ȫ���е��±�
	cout << "==========================================================" << endl;
	while (runtimes<=6)
	{	
		for (int i = 0; i < 5; i++) {
			if (finished[i] == false) {
				// �������û�б�������Դ���
				Matrix need = p[i].getNeed();				// ��ȡ���̵��������
				Matrix work = available;					// ��ȡ���̵Ĺ�������
				bool flag = need.compare(work);				// �Ƚ��������͹�������
				if (flag == true) {							// ������̵�����С�ڵ��ڹ�������������Է�����Դ
					p[i].setWork(work);						// ���½��̵Ĺ�������
					if (signal == true) {
						// ����ǵ�һ�����ж��ҿ��Է�����Դ�������ǰ������Դ
						cout << "��ǰ������ԴΪ" << endl;
						available.display();
						signal = false;
					}
					cout << "����P" << i << "����Դ������������������������Դ���£�" << endl;
					need.display();
					cout << "==========" << endl;
					Matrix allocation = p[i].getAllocated();	// ��ȡ��������
					available.add(allocation);					// ���¹�������
					finished[i] = true;							// ��ǽ��̵���Դ�ѷ��������
					line[j] = i;								// ���̼��밲ȫ����
					j++;										// ��ȫ���е��±��1
					cout << "��ǰ������ԴΪ" << endl;
					available.display();						// ��ʾ��ǰ������Դ
				}
			}
		}
		runtimes++;
	}
	cout << "==========================================================" << endl;

	//������н��̶�����ˣ�˵����ȫ
	if (allFinished(finished)) {
		cout << "{ ";
		for (int i = 0; i < 5; i++) {
			cout << "P" << line[i] << " " ;	// �����ȫ����
		}
		cout << "}" << endl;
		cout << "����������ʾ�İ�ȫ���У����Խ��̲�������" << endl;
	}
	else {
		cout << "�����������İ�ȫ���У����Խ��̿�������" << endl;
	}
}