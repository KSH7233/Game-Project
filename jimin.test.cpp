#include<iostream>
using namespace std;

class Counter
{
	int value;
public:
	Counter(int value = 0) : value(value)
	{
		this->value = value;
	}
	Counter operator+(const Counter& c);
	Counter& operator =(const Counter& c);
	Counter& operator++(); // ��������
	//const Counter operator++(int i); // ��������
	friend ostream& operator<<(ostream& out, const Counter& c) // ostream = ���������ϴ� �ݺ���
	{//operator = �ڿ��ٴ� �����ڸ� ������ ���شٴ� ��
		out << c.value; // <<�� �ᵵ c.value�� ����
		return out;
	}
};

Counter Counter::operator+(const Counter& c)
{
	Counter result =this->value + c.value;
	return result;
}
Counter& Counter::operator=(const Counter& c)
{ // ��ü�� �����͸� ����
	this->value = c.value; // �ڽ��ǰ��� c�� ���� ����
	return *this; // �ڽ��� ��ȯ *�� �����Ͷ�
}
/*a = 5, b = 6
c = a + ++b; = a=5, b=7 c = 12 ����
c = a + b++; a = 5 b = 6 c = 11, b=7
*/
Counter& Counter::operator++() // ��������
{
	this->value = this->value + 1;
	return *this;
}

/*const Counter Counter::operator++(int i)
{}*/

int main()
{
	Counter a(5), b(7); 
	Counter c;
	Counter d;
	c = a+b; //operator+ case 1
	cout<< "operator+ case 1 : " << c << endl;
	
	
	c = a=b;
	cout << c <<" "<< a <<" "<< b << endl;
	cout << "operator= case 1 : " << c << endl;
	

	c = ++a;
	cout <<"operator++ case 1 : " << c << endl;


	return 0;
}