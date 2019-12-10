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
	Counter& operator++(); // 전위연산
	//const Counter operator++(int i); // 후위연산
	friend ostream& operator<<(ostream& out, const Counter& c) // ostream = 출력을담당하는 반복자
	{//operator = 뒤에붙는 연산자를 재정의 해준다는 뜻
		out << c.value; // <<만 써도 c.value가 나옴
		return out;
	}
};

Counter Counter::operator+(const Counter& c)
{
	Counter result =this->value + c.value;
	return result;
}
Counter& Counter::operator=(const Counter& c)
{ // 객체의 포인터를 받음
	this->value = c.value; // 자신의값에 c의 값을 넣음
	return *this; // 자신을 반환 *는 포인터라서
}
/*a = 5, b = 6
c = a + ++b; = a=5, b=7 c = 12 전위
c = a + b++; a = 5 b = 6 c = 11, b=7
*/
Counter& Counter::operator++() // 전위연산
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