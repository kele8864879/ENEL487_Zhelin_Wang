/**
   Programmer: Zhelin Wang
   Project: Assignment2
   Date: 2020-9-28

   Description: This is the code for assignment 2. It include a class Comples, three function for interactive and batch running and a main function.
 */
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

static char flag = 'w'; // for operation 

class Complex // the calculator function
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
	Complex operator/(const Complex& c); // divide algoritm



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
	ofstream outData;
	outData.open("output.txt");
	outData << real << " + (" << image << ")j" << endl;
	cout << real << " + (" << image << ")j" << endl;
	outData.close();
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



void Interactive_mode() // interactive function, 
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

void Batch_mode_calculation(char flag, double n[4]) 
{	
	if (flag == 'a')
	{
		Complex c1, c2, c3;
		c1.set(n[0],n[1] );
		c2.set(n[2],n[3] );
		c3 = c1 + c2;
		c3.show();
	}

	if (flag == 's')
	{
		Complex c1, c2, c3;
		c1.set(n[0], n[1]);
		c2.set(n[2], n[3]);
		c3 = c1 - c2;
		c3.show();
	}

	if (flag =='m')
	{
		Complex c1, c2, c3;
		c1.set(n[0], n[1]);
		c2.set(n[2], n[3]);
		c3 = c1 * c2;
		c3.show();
	}

	if (flag == 'd')
	{
		Complex c1, c2, c3;
		c1.set(n[0], n[1]);
		c2.set(n[2], n[3]);
		c3 = c1 / c2;
		c3.show();
	}
}
void Batch_mode()
{
	string str;
	ifstream inData;                    // declares input stream
	ofstream outData;                   // declares output stream
	int counter_1 = 0;                  //location that we run the str[]
	int counter_2 = 0;                  //record how many value is stored
	int counter_3 = 0;					//take position of value				
	double number = 0;
	double n[4];
	int i = 0;
	inData.open("input.txt");
	outData.open("output.txt");
	
	while (!inData.eof())
	{
		if (flag == 'q')
		{
			break;
		}
		if (counter_1 == str.size())
		{
			counter_1 = 0;
		}
		getline(inData, str);
		for (counter_1; counter_1 < str.size(); counter_1++)
		{

			if (str[counter_1] == 'A' || str[counter_1] == 'a')
			{
				flag = 'a';
			}
			else if (str[counter_1] == 'S' || str[counter_1] == 's')
			{
				flag = 's';
			}
			else if (str[counter_1] == 'M' || str[counter_1] == 'm')
			{
				flag = 'm';
			}
			else if (str[counter_1] == 'D' || str[counter_1] == 'd')
			{
				flag = 'd';
			}
			else if (str[counter_1] == 'Q' || str[counter_1] == 'q')
			{
				flag = 'q';
				break;
			}
			else if (str[counter_1] == ' ') // take the number's position in the string
			{
				if (counter_2 < 3)
				{
					counter_3 = counter_1;
					while (str[counter_3 + 1] != ' ')
					{
						counter_3++;
					}
					n[i] = stod(str.substr(counter_1, str.size()));
					//cout << n[i] << endl;
					i++;
					counter_2++;
				}
				else if (counter_2 == 3)
				{
					n[i] = stod(str.substr(counter_1, str.size()));
					//cout << n[i] << endl;
					i = 0;
					counter_2 = 0;
					Batch_mode_calculation(flag, n);
				}

			}
			
		}

	}


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
			flag = 'w';
		}
		else
			cout << "wrong choice please do it again" << endl;
	}
		while (1);
	
}