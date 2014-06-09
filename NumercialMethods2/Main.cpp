/*
 *	Main.cpp
 *  
 *  Compute the roots of the system of non-linear set of two equations 
 *  given below using the multiple-equation Newton-Raphson method
 *  x^2 + xy = 10
 *  y + 3xy^2 = 57
 *
 *  Created on: March 31, 2014
 *  Author: David Crossman
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct roots 
{
	double x;
	double y;
};

double method1(roots);
double method1dx(roots);
double method1dy(roots);
double method2(roots);
double method2dx(roots);
double method2(roots);

roots newtonRapsonMethod(roots);

int main () {
	bool rootsFound = false;
	while (!rootsFound)
	{
		roots result;
		cout << "Please enter the value of x1" << endl;
		cin >> result.x;
		cout << "Please enter the value of x2" << endl;
		cin >> result.y;
		result = newtonRapsonMethod(result);
		if(result.x >= 0 && result.y >= 0) {
			cout << "The roots are: x1 = " << result.x << " and x2 = " << result.y << endl;
			rootsFound = true;
		}
		else
			cout << "You received negative roots please try again" << endl;
		cout << endl;
	}
	return 0;
}

double method1(roots val)
{
	return pow(val.x, 2) + val.x*val.y - 10;
}

double method1dx(roots val)
{
	return 2*val.x + val.y;
}

double method1dy(roots val)
{
	return val.x;
}

double method2(roots val)
{
	return val.y + 3*val.x*pow(val.y, 2) - 57;
}

double method2dx(roots val)
{
	return 3*pow(val.y, 2);
}

double method2dy(roots val)
{
	return 1 + 3*val.x*2*val.y;
}

roots newtonRapsonMethod(roots val)
{
	double x = val.x;
	double y = val.y;
	double J[2][2] = {0};
	double JInverse[2][2] = {0};
	double f1 = method1(val);
	double f2 = method2(val);

	J[0][0] = method1dx(val);
	J[0][1] = method1dy(val);
	J[1][0] = method2dx(val);
	J[1][1] = method2dy(val);

	double det = J[0][0]*J[1][1]-J[0][1]*J[1][0];

	JInverse[0][0] = (1/det)*J[1][1];
	JInverse[0][1] = (1/det)*-1*J[0][1];
	JInverse[1][0] = (1/det)*-1*J[1][0];
	JInverse[1][1] = (1/det)*J[0][0];

	val.x = x - (JInverse[0][0]*f1 + JInverse[0][1]*f2);
	val.y = y - (JInverse[1][0]*f1 + JInverse[1][1]*f2);

	//cout << x << endl;
	if(abs(val.x - x)/abs(x) < pow(0.1, 7) * abs(x) && abs(val.y - y)/abs(y) < pow(0.1, 7) * abs(y))
        return val;
	else
		return newtonRapsonMethod(val);
}