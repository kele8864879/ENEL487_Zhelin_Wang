/**
   Programmer: Zhelin Wang
   Project: Assignment2
   Date: 2020-9-28

   Description:
 */
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Complex
{
public:
	Complex(); // default constructor
	Complex(double r, double i); 
	~Complex();

	void set(double r, double i); // set the value of real and image.
	void show();	//	cout the result
	

	Complex operator+(const Complex& c); //add algorithm
	Complex operator-(const Complex& c); //decrease algoritm
	Complex operator*(const Complex& c); //mutiple algoritm
	Complex operator/(const Complex& c); // 



private:
	double real, image;

};

Complex::Complex(double r, double i)
{
	real = r;
	image = i;
}

Complex::~Complex()
{
}

void Complex::set(double r, double i)
{
	real = r;
	image = i;
}

void Complex::show()
{
	cout << real << " + (" << image << ")j" << endl;
}



Complex Complex::operator+(const Complex& c)
{
	this->real += c.real;
	this->image += c.image;
	return Complex(real, image);
}

Complex Complex::operator-(const Complex& c)
{
	real = this->real - c.real;
	image = this->image - c.image;
	return Complex(real, image);
}

Complex Complex::operator*(const Complex& c)
{
	double real_time;
	double image_time;
	real_time = this->real * c.real - this->image * c.image;
	image_time = this->real * c.image + this->image * c.real;
	return Complex(real_time, image_time);
}

Complex Complex::operator/(const Complex& c)
{
	double real_divide;
	double image_divide;
	real_divide = (this->real * c.real + this->image * c.image) / (c.real * c.real + c.image * c.image);
	image_divide = (this->image * c.real - this->real * c.image) / (c.real * c.real + c.image * c.image);
	return Complex(real_divide, image_divide);
}



Complex::Complex()
{
}



void Interactive_mode()
{
		double r1 = 0, r2 = 0, i1 = 0, i2 = 0;
		Complex c1, c2, c3;
		char choice;
		bool loop = 1;
		cout << "Type a letter to specify the arithmetic operator (A, S, M, D)followed by two complex numbers expressed as pairs of doubles.Type Q to quit." << endl;
		do
		{
			cout << "operator: "; cin >> choice;
			if (choice == 'a' || choice == 'A')
			{
				cout << "r1: "; cin >> r1;
				cout << "i1: "; cin >> i1;
				cout << "r2: "; cin >> r2;
				cout << "i2: "; cin >> i2;
				c1.set(r1, i1);
				c2.set(r2, i2);
				c3 = c1 + c2;
				c3.show();
			}
			else if (choice == 's' || choice == 'S')
			{
				cout << "r1: "; cin >> r1;
				cout << "i1: "; cin >> i1;
				cout << "r2: "; cin >> r2;
				cout << "i2: "; cin >> i2;
				c1.set(r1, i1);
				c2.set(r2, i2);
				c3 = c1 - c2;
				c3.show();
			}
			else if (choice == 'm' || choice == 'M')
			{
				cout << "r1: "; cin >> r1;
				cout << "i1: "; cin >> i1;
				cout << "r2: "; cin >> r2;
				cout << "i2: "; cin >> i2;
				c1.set(r1, i1);
				c2.set(r2, i2);
				c3 = c1 * c2;
				c3.show();
			}
			else if (choice == 'd' || choice == 'D')
			{
				cout << "r1: "; cin >> r1;
				cout << "i1: "; cin >> i1;
				cout << "r2: "; cin >> r2;
				cout << "i2: "; cin >> i2;
				c1.set(r1, i1);
				c2.set(r2, i2);
				c3 = c1 / c2;
				c3.show();
			}
			else if (choice == 'q' || choice == 'Q')
			{
				loop = 0;
			}
			else
				cout << "please input correct word" << endl;
		} while (loop);
}

void Batch_mode()
{
	string str1, str2, str3, str4;      // declares 4 variables
	ifstream inData;                    // declares input stream
	ofstream outData;                   // declares output stream

	inData.open("input.txt");
	// binds program variable inData to the input file "input.txt"

	outData.open("output.txt");
	// binds program variable outData to the output file "output.txt"

   // input 4 lines
	getline(inData, str1);
	getline(inData, str2);
	getline(inData, str3);
	getline(inData, str4);

	// output 4 lines
	outData << str4 << endl;
	outData << str3 << endl;
	outData << str2 << endl;
	outData << str1 << endl;  // outputs 4 lines

	inData.close();
	outData.close();

}

int main()
{
	do
	{
		cout << "Please input A or B and choose the mode u want. " << endl << "A. Interactive Mode B. Batch Mode " << endl;
		char function_choice;
		cin >> function_choice;
		if (function_choice == 'a' || function_choice == 'A')
		{
			Interactive_mode();
		}
		else if (function_choice == 'b' || function_choice == 'B')
		{
			Batch_mode();
		}
		else
			cout << "wrong choice please do it again" << endl;
	}
		while (1);
}