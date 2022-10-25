#include <iostream>
using namespace std;
#define delimiter "_______________________________________"
class Fraction
{
	int Integer = 0;
	int Num = 0;
	int Denum = 1;
public:
	int get_Integer()const
	{
		return Integer;
	}
	int get_Num()const
	{
		return Num;
	}
	int get_Denum()const
	{
		return Denum;
	}
	void set_Integer(int x)
	{
		this->Integer = x;
	}
	void set_Num(int x)
	{
		this->Num = x;
	}
	void set_Denum(int x)
	{
		this->Denum = x;
	}
	//Constructors
	Fraction(int Integer = 0, int Num = 0, int Denum = 1)
	{
		if (Denum == 0)
		{
			cout << "Ошибка ввода, на ноль делить нельзя" << endl;
			return;
		}
		if (Num >= Denum)
		{
			this->Num = Num % Denum;
			this->Integer = Integer + (Num / Denum);
			this->Denum = Denum;
			//cout << "Constructor: " << this << endl;
		}
		else
		{
			this->Num = Num;
			this->Integer = Integer;
			this->Denum = Denum;
			//cout << "Constructor: " << this << endl;
		}
	}
	Fraction(const Fraction& other)
	{
		this->Num = other.Num;
		this->Integer = other.Integer;
		this->Denum = other.Denum;
		//cout << "CopyConstructor: " << this << endl;
	}
	~Fraction()
	{
		//cout << "Destructor:\t" << this << endl;
	}


	//Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->Integer = other.Integer;
		this->Num = other.Num;
		this->Denum = other.Denum;
		//cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator++()//Prefix increment
	{
		Integer++;
		return *this;
	}
	Fraction operator++(int/*здесь возможен только int*/) //Postfix increment (Suffix increment)
	{
		Fraction old = *this;
		Integer++;
		return old;
	}

	Fraction& operator()(int i, int n, int d)
	{
		set_Integer(i);
		set_Num(n);
		set_Denum(d);
		return *this;
	}

	//Methods
	double Decimal()const //Перевод в десятичную дробь
	{
		return (double(this->Integer) + double(this->Num) / double(this->Denum));
	}

	void print()const
	{
		if (Num == 0)	cout << Integer << endl;
		else if (Integer == 0) cout << Num << "/" << Denum << endl;
		else cout << Integer << " " << Num << "/" << Denum << endl;
	}

	Fraction correction() //метод для проверки неправильности дроби после арифметических выражений
	{
		if (Num * Num < Denum * Denum) return *this;
		else
		{
			this->Integer = Integer + Num / Denum;
			this->Num = Num % Denum;
		}
		return *this;
	}
};

Fraction operator+ (const Fraction& first, const Fraction& second)//сложение с таким же объектом-дробью
{
	Fraction res;
	res.set_Integer(first.get_Integer() + second.get_Integer());
	if (first.get_Denum() == second.get_Denum())
	{
		res.set_Num(first.get_Num() + second.get_Num());
		res.set_Denum(first.get_Denum());
	}
	else
	{
		res.set_Num(first.get_Num() * second.get_Denum() + second.get_Num() * first.get_Denum());
		res.set_Denum(first.get_Denum() * second.get_Denum());
	}
	res.correction();
	return res;
}

Fraction operator+ (const Fraction& first, int x)//сложение с целым числом
{
	Fraction res;
	res.set_Integer(first.get_Integer() + x);
	res.set_Num(first.get_Num());
	res.set_Denum(first.get_Denum());
	return res;
}
Fraction operator+ (const Fraction& first, double x)//сложение с десятичной дробью
{
	Fraction res;
	res.set_Integer(first.get_Integer() + (int)x);
	res.set_Num(first.get_Num() * 100 + (int)((x - (int)x) * 100) * first.get_Denum());
	res.set_Denum(first.get_Denum() * 100);
	return res;
}

Fraction operator-(const Fraction& first, const Fraction& second)
{
	Fraction res;
	if (first.get_Denum() == second.get_Denum())
	{
		res.set_Num((first.get_Integer() * first.get_Denum() + first.get_Num()) - (second.get_Integer() * second.get_Denum() + second.get_Num()));
		res.set_Denum(first.get_Denum());
	}
	else
	{
		res.set_Num((first.get_Integer() * first.get_Denum() + first.get_Num()) * second.get_Denum() - (second.get_Integer() * second.get_Denum() + second.get_Num()) * first.get_Denum());
		res.set_Denum(first.get_Denum() * second.get_Denum());
	}
	res.correction();
	return res;
}

Fraction operator*(const Fraction& first, const Fraction& second)//умножение объектов-дробей
{
	Fraction res;
	res.set_Num((first.get_Integer() * first.get_Denum() + first.get_Num()) * (second.get_Integer() * second.get_Denum() + second.get_Num()));
	res.set_Denum(first.get_Denum() * second.get_Denum());
	res.correction();
	return res;
}

bool operator==(const Fraction& first, const Fraction& second)
{

	return first.get_Integer() == second.get_Integer() && first.get_Num() * second.get_Denum() == second.get_Num() * first.get_Denum();
}

bool operator !=(const Fraction& first, const Fraction& second)
{
	return !(first == second);
}

bool operator<(const Fraction& first, const Fraction& second)
{
	if (first.get_Integer() == second.get_Integer())
		return (first.get_Num() * second.get_Denum()) < (second.get_Num() * first.get_Denum());
	else return first.get_Integer() < second.get_Integer();
}

bool operator<=(const Fraction& first, const Fraction& second)
{
	if (first.get_Integer() == second.get_Integer())
		return (first.get_Num() * second.get_Denum()) <= (second.get_Num() * first.get_Denum());
	else return first.get_Integer() <= second.get_Integer();
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_Integer() == 0)
		os << obj.get_Num() << "/" << obj.get_Denum();
	else
		os << obj.get_Integer() << " " << obj.get_Num() << "/" << obj.get_Denum();
	return os;
}

void main()
{
	setlocale(LC_ALL, "");
	Fraction A(1, 3, 4);
	A.print();
	Fraction B = A;
	B.print();
	cout << delimiter << endl;
	cout << "Перевод в десятичную дробь:" << endl << A << " = " << A.Decimal() << endl;
	cout << delimiter << endl;

	cout << "Сложение объектов-дробей" << endl;
	Fraction C = A + B;
	cout << A << " + " << B << " = " << C << endl;
	cout << delimiter << endl;

	cout << "Сложение объекта и целого числа" << endl;
	cout << C << " + 2" << endl;
	cout << C + 2 << endl;
	//C.print();
	cout << delimiter << endl;

	cout << "Сложение объекта и десятичной дроби (округление до сотых)" << endl;
	cout << C << " + 2.456" << endl;
	cout << C + 2.456 << endl;
	//C.print();
	cout << delimiter << endl;

	cout << "Умножение объектов-дробей" << endl;
	cout << B << " * " << A << endl;
	cout << B * A << endl;
	//C.print();
	cout << delimiter << endl;

	cout << "Вычитание объектов-дробей" << endl;
	Fraction E = A + B;
	cout << E << " - " << A << endl;
	cout << E - A << endl;
	cout << delimiter << endl;
}