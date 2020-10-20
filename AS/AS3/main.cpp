/**
   Programmer: Zhelin Wang
   Project: Assignment3
   Date: 2020-10-19

   Description: This is the code for assignment 2. It include a class Comples, three function for interactive and batch running and a main function.
 */
#include<iostream>
#include <assert.h>
#include<string>
#include<math.h>
#include<regex>
//#include <sstream>
using namespace std;

char flag = 'w'; // for operation 
#define PI 3.141592654
//regex r("^[-+]?(\\d+(\\.\\d*)?|\\.\\d+)([eE][-+]?\\d+)?[dD]?$");



class Complex // the calculator function
{
public:
	Complex(); // default constructor
	Complex(double r, double i); 
	~Complex();

	void set(double r, double i); // set the value of real and image.
	void show();	//	cout the result
	void abs();		//	algorith of abs
	void arg();		//	algorith of arg
	void argDeg();	//	algorith of argdeg
	void complex_exp(); 	//	algorith of exp
	void inv();					//	algorith of inv


	Complex operator+(const Complex& c); //add algorithm
	Complex operator-(const Complex& c); //decrease algoritm
	Complex operator*(const Complex& c); //mutiple algoritm
	Complex operator/(const Complex& c); // divide algoritm



private:
	double real = 0, image = 0, result = 0;

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
	char s = '+';
	if (image < 0)
	{
		s = '-';
		image = fabs(image);
	}
	cout << real << s <<"j" << image << endl;
}

void Complex::abs()
{
	result = real * real + image * image;
	result = sqrt(result);
	cout << result << endl;
}

void Complex::arg()
{
	result = fabs(atan(image / real));
	if (real >= 0 && image >= 0)
	{
		result = result;
	}
	else if (real >= 0 && image < 0)
	{
		result = -result;
	}
	else if (real < 0 && image >= 0)
	{
		result = PI - result;
	}
	else if (real < 0 && image < 0)
	{
		result = result - PI;
	}
	cout << result << endl;
}

void Complex::argDeg()
{
	result = fabs(atan(image / real));
	if (real >= 0 && image >= 0)
	{
		result = result;
	}
	else if (real >= 0 && image < 0)
	{
		result = -result;
	}
	else if (real < 0 && image >= 0)
	{
		result = PI - result;
	}
	else if (real < 0 && image < 0)
	{
		result = result - PI;
	}
	result = (result / (2 * PI)) * 360;
	cout << result << endl;
}

void Complex::complex_exp()
{
	double real_temp, image_temp; //temporary real and image value
	real_temp = exp(real) * cos(image);
	image_temp = exp(real) * sin(image);
	real = real_temp;
	image = image_temp;
	show();
}

void Complex::inv()
{
	double real_temp, image_temp; //temporary real and image value
	real_temp = real / (real * real + image * image);
	image_temp = (-image) / (real * real + image * image);
	real = real_temp;
	image = image_temp;
	cout << real << "+ j(" << image << ")" << endl;
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

/*string doubleTranStr(double n) {
	stringstream ss;
	ss << n;
	return ss.str();
}*/


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
	if (flag == 'b')
	{
		Complex c1;
		c1.set(n[0], n[1]);
		c1.abs();
	}
	if (flag == 'r')
	{
		Complex c1;
		c1.set(n[0], n[1]);
		c1.arg();
	}
	if (flag == 'D')
	{
		Complex c1;
		c1.set(n[0], n[1]);
		c1.argDeg();
	}

	if (flag == 'e')
	{
		Complex c1;
		c1.set(n[0], n[1]);
		c1.complex_exp();
	}

	if (flag == 'i')
	{
		Complex c1;
		c1.set(n[0], n[1]);
		c1.inv();
	}
}

void Batch_mode()
{
	string str;
	cerr << "Enter exp:";
	getline(cin, str);
	int counter_1 = 0;                  //location that we run the str[],initialization
	int counter_2 = 0;                  //record how many value is stored,initialization
	int counter_3 = 0;					//take position of value. The counter_3 will be used check space, and let variable "space" ++
	int counter_4 = 0;					//counter_4 is used for error judge part. it helps my function leave the endless loop,initialization
	//double number = 0;
	double n[4];						//an array which save the number real_1 real_2 j1 j2.initialization
	int i = 0;							//as variable for above array.initialization
	int space = 0;                         //this parameter is used to judge how many space that u have entered. if space do not == 2 or 4. flag goes 'w' which means u input has errors. initialization
	bool Division_by_0 = false;				//	as the name, judge division by 0
;   flag = 'w';							//flag of wrong. it mease u input a wrong command
	
	for (counter_3 = 0; counter_3 <= str.size(); counter_3++)  // this loop is to judge how many space that u enter. counter_3 will goes the whole string to find the space.
	{
		if (str[counter_3] == ' ')
			space++;
	}
	counter_3 = 0;

	while(counter_1 != str.size()) // counter_1 will run the whole string untill counter_1 == str.size
	{ 
		
		for (counter_1; counter_1 < str.size(); counter_1++)	//counter_1 run
		{

			if ((str[counter_1] == 'A' || str[counter_1] == 'a') && (str[counter_1 + 1] == ' ') && space == 4)		//judge the algorith. flag represent the algorith name "add"
			{	
				//if (counter_1 == 0)
				flag = 'a';
			}
			else if ((str[counter_1] == 'S' || str[counter_1] == 's') && (str[counter_1 + 1] == ' ') && space == 4)	//judge the algorith. flag represent the algorith name "substract"
			{
				//if (counter_1 == 0)
				flag = 's';
			}
			else if ((str[counter_1] == 'M' || str[counter_1] == 'm') && (str[counter_1 + 1] == ' ') && space == 4)	//judge the algorith. flag represent the algorith name "multiple"
			{
				flag = 'm';
			}
			else if ((str[counter_1] == 'D' || str[counter_1] == 'd') && (str[counter_1 + 1] == ' ') && space == 4)//judge the algorith. flag represent the algorith name "divide"
			{
				flag = 'd';
			}
			else if (str[counter_1] == 'Q' || str[counter_1] == 'q')	//judge the algorith. flag represent the algorith name "quit"
			{
				if (str.size() == 1)
				flag = 'q';
			}
			else if ((str[counter_1] == ' ') && (flag == 'a' || flag == 's' || flag == 'm' || flag == 'd')) // take the number's position in the string
			{
				if (counter_2 < 3)
				{
					/*counter_3 = counter_1;
					while (str[counter_3 + 1] != ' ')		
					{
						counter_3++;
					}
					*/
						n[i] = stod(str.substr(counter_1, str.size()));	
						i++;
						counter_2++;				
				}
				else if (counter_2 == 3)		// it means there are 3 value is taken to the array, counter_1 is stand at the last space
				{
					n[i] = stod(str.substr(counter_1, str.size()));
					//cout << n[i] << endl;
					i = 0;
					counter_2 = 0;
					if (n[2] == 0 && n[3] == 0 && flag == 'd') // judge the denominator should not be 0 in divide function
					{
						flag = 'w';
						Division_by_0 = true;					//the denominator is 0
					}
					
					Batch_mode_calculation(flag, n);
				}
			}
			//judge if the input is abs
			else if ((str[counter_1] == 'A' || str[counter_1] == 'a') && (str[counter_1 + 1] == 'B' || str[counter_1 + 1] == 'b') && (str[counter_1 + 2] == 'S' || str[counter_1 + 2] == 's') && space == 2)
			{
				flag = 'b';//flag for abs
				counter_1 = counter_1 + 2;
			}
			//judge if the input is arg
			else if ((str[counter_1] == 'A' || str[counter_1] == 'a') && (str[counter_1 + 1] == 'R' || str[counter_1 + 1] == 'r') && (str[counter_1 + 2] == 'g' || str[counter_1 + 2] == 'g') && (str[counter_1 + 3] == ' ') && space == 2)
			{
				flag = 'r';//flag for arg
				counter_1 = counter_1 + 2;
			}
			//judge if the input is argdeg
			else if ((str[counter_1] == 'A' || str[counter_1] == 'a') && (str[counter_1 + 1] == 'R' || str[counter_1 + 1] == 'r') && (str[counter_1 + 2] == 'G' || str[counter_1 + 2] == 'g') && (str[counter_1 + 3] == 'D' || str[counter_1 + 3] == 'd') && (str[counter_1 + 4] == 'E' || str[counter_1 + 4] == 'e') && (str[counter_1 + 5] == 'G' || str[counter_1 + 5] == 'g') && space == 2)
			{
				flag = 'D';//flag for argdeg
				counter_1 = counter_1 + 5;
			}
			//judge if the input is exp
			else if ((str[counter_1] == 'E' || str[counter_1] == 'e') && (str[counter_1 + 1] == 'X' || str[counter_1 + 1] == 'x') && (str[counter_1 + 2] == 'P' || str[counter_1 + 2] == 'p') && space == 2)
			{
				flag = 'e';//flag for exp
				counter_1 = counter_1 + 2;
			}

			else if ((str[counter_1] == 'I' || str[counter_1] == 'i') && (str[counter_1 + 1] == 'N' || str[counter_1 + 1] == 'n') && (str[counter_1 + 2] == 'V' || str[counter_1 + 2] == 'v') && space == 2)
			{
				flag = 'i';//flag for inv
				counter_1 = counter_1 + 2;
			}
			else if ((str[counter_1] == ' ') && (flag == 'b' || flag == 'r' || flag == 'D' || flag == 'e' || flag == 'i')) // take the number's position in the string
			{
				if (counter_2 < 1)		// take the number's position in the string
				{
					/*counter_3 = counter_1;
					while (str[counter_3 + 1] != ' ')
					{
						counter_3++;
					}*/

					n[i] = stod(str.substr(counter_1, str.size()));
					//cout << n[i] << endl;
					i++;
					counter_2++;
				}
				else if (counter_2 == 1)
				{
					n[i] = stod(str.substr(counter_1, str.size()));
					//cout << n[i] << endl;
					i = 0;
					counter_2 = 0;

					if (n[0] == 0 && n[1] == 0 && flag == 'i') // the denominator should not be 0, check.
					{
						flag = 'w';
						Division_by_0 = true;					//the denominator is 0
					}
					Batch_mode_calculation(flag, n);
					
				}
			}
			else if (flag == 'w')		//this part is deal with the wrong code.
			{
			if (counter_4 ==0)			//test if it is the first time run this if.
				/*for (counter_3 = 0; counter_3 <= str.size(); counter_3++)
				{
					if (str[counter_3] == ' ')
						break;
				}*/
				counter_4 = 1;
				if (Division_by_0 == false)
				{
					cout << "Malformed command: input line was: " << str << endl;
					counter_1 = str.size();			//close the while(counter_1 != str.size())
					break;
				}
				else if (Division_by_0 == true)
				{
						cout << "Division by 0: input line was: " << str << endl;
						counter_1 = str.size();			//close the while(counter_1 != str.size())
						break;
				}
			}
		}

	}


}

int main()
{
	while (flag != 'q')
	{
		cerr << "Type a letter to specify the arithmetic operator (A, S, M, D)followed by two complex numbers expressed as pairs of doubles.Type Q to quit." << endl << endl;
		Batch_mode();
	}
		
	return 0;
}