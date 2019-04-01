#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

//System functions: 

void menu(void) {
	cout << "Polynomial Algebra:" << endl
		<< "1. Addition of a two polynoms" << endl
		<< "2. Subtraction of a two polynoms" << endl
		<< "3. Multiplication of a two polynoms" << endl
		<< "4. Division of a two polynoms" << endl
		<< "5. Multiplication of a polynom by a constant" << endl
		<< "6. Dirivative of a polynom" << endl
		<< "7. Antidirivative of a polynom" << endl
		<< "8. Superposition of a polynom" << endl
		<< "9. Value of a polynom in a point" << endl;
}

void printPolynom(vector <double> v) {
	/*Function prints vector from the biggest power*/
	for (int i = v.size() - 1; i >= 0; i--) {
		if (v[v.size() - i - 1] == 0 && i == 0)
			cout << " 0 ";
		else if (v[v.size() - i - 1] > 0 && i != 0 && i != 1)
			cout << v[v.size() - i - 1] << "x^" << i << " + ";
		else if (v[v.size() - i - 1] < 0 && i != 0 && i != 1)
			cout << "(" << v[v.size() - i - 1] << ")x^" << i << " + ";
		else if (i == 1 && v[v.size() - i - 1] < 0)
			cout << "(" << v[v.size() - i - 1] << ")x";
		else if (i == 1 && v[v.size() - i - 1] > 0)
			cout << "" << v[v.size() - i - 1] << "x";
		else if (i == 0 && v[v.size() - i - 1] < 0)
			cout << " + (" << v[v.size() - i - 1] << ")";
		else if (i == 0 && v[v.size() - i - 1] > 0)
			cout << " + " << v[v.size() - i - 1];
		else {
			cout << " 0 ";
			break;
		}
	}
	cout << endl;
}

//vector <double> enterPolynomStr(void) {
//}

vector <double> enterPolynom(void) {
	double power = 0;
	cout << "Enter power: "; cin >> power;
	vector <double> polynomVector(power + 1);
	for (int i = 0; i < polynomVector.size(); i++) {
		cout << "Enter x^" << power - i << ": ";
		cin >> polynomVector[i];
	}
	return polynomVector;
}

vector <double> vectorReverse(vector<double>v) {
	/*Returns a reversed vector*/
	vector <double> result;
	for (int i = v.size() - 1; i >= 0; i--)
		result.push_back(v[i]);
	return result;
}

vector <double> zeroVector(vector <double> v, double vectorSize) {
	/*Returns a vector of vectorSize zeros*/
	for (int i = 0; i <= vectorSize; i++) {
		v.push_back(0);
	}
	return v;
}

//Engine of the program:

vector <double> polynomSum(vector <double>& v1, vector <double>& v2) {
	/*Polynom addition*/
	if (v1.size() < v2.size()) {
		v1.swap(v2);
	}
	v1 = vectorReverse(v1);
	v2 = vectorReverse(v2);
	for (int i = v2.size() - 1; i >= 0; i--)
	{
		v1[i] = ((v1[i] + v2[i]));
	}
	return vectorReverse(v1);
}

vector <double> polynomSub(vector <double>& v1, vector <double>& v2) {
	/*Polynom subtraction*/
	v1 = vectorReverse(v1);
	v2 = vectorReverse(v2);
	while (v1.size() < v2.size()) {
		v1.push_back(0);
	}
	for (int i = v2.size() - 1; i >= 0; i--) {
		v1[i] = ((v1[i] - v2[i]));
	}
	v1 = vectorReverse(v1);
	return v1;
}

vector <double> polynomMult(vector <double>& v1, vector <double>& v2) {
	/*Polynom Multiplication*/
	double powsize = v1.size() + v2.size() - 2;
	vector <double> result = zeroVector(result, powsize);
	vector <double> rem = zeroVector(rem, powsize);
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			rem[i + j] = v1[i] * v2[j];
		}
		result = polynomSum(rem, result);
		rem.clear();
		rem = zeroVector(rem, powsize);
	}
	result = vectorReverse(result);
	return result;
}

vector <double> polynomDivision(vector <double> v1, vector <double> v2) {
	vector<double>divisor;
	vector<double>rem;
	if (v2.size() == 1 && v2[0] == 0)
		return v2;
	int a = v1.size();
	int b = v2.size();
	int c = a - b;
	v1 = vectorReverse(v1);
	v2 = vectorReverse(v2);
	if (v1 == v2) {
		rem.push_back(0);
		divisor.push_back(1);
		return vectorReverse(divisor);
	}
	if (c < 0) {
		while (b >= a) {
			double symb = v2[0] / v1[0];
			divisor.push_back(symb);
			for (int i = 0; i < v1.size(); i++)
				v1[i] *= symb;
			rem = polynomSub(v2, v1);
			rem.erase(rem.begin());
			v2 = rem;
			b--;
		}
	}
	else if (c > 0) {
		while (a >= b) {
			double symb = v1[0] / v2[0];
			divisor.push_back(symb);
			for (int i = 0; i < v2.size(); i++)
				v2[i] *= symb;
			rem = polynomSub(v1, v2);
			rem.erase(rem.begin());
			v1 = rem;
			a--;
		}
	}
	else {
		double symb = v2[0] / v1[0];
		divisor.push_back(symb);
		for (int i = 0; i < v1.size(); i++)
			v1[i] *= symb;
		rem = polynomSub(v2, v1);
	}
	rem = vectorReverse(rem);
	return vectorReverse(divisor);
}


vector <double> polynomAntidirivative(vector<double> v) {
	v.push_back(0);
	for (int i = 0; i < v.size(); i++)
		v[i] = v[i] / (v.size() - i - 1);
	return v;
}

vector <double> polynomDerivative(vector <double> v) {
	for (int i = 0; i < v.size(); i++)
		v[i] = v[i] * (v.size() - i - 1);
	v.pop_back();
	return v;

}

vector <double> polynomMultConst(vector <double>& v, double n) {
	for (int i = 0; i < v.size(); i++)
		v[i] *= n;
	return v;
}

vector <double> polynomPower(vector <double> v, double power) {
	vector <double> rem;
	rem = v;
	for (int i = 0; i < power - 1; i++) {
		v = polynomMult(rem, v);
	}
	return v;
}

//vector <double> polynomSuperposition(vector <double> v1, vector <double> v2) {
//	vector <double> sp;
//	int k;
//	zeroVector(sp, v2.size());
//	sp.insert(sp.begin(), v1[0]);
//	for (int i = 1; i < v1.size(); i++) {
//		v2 = polynomPower(v2, i);
//		for (int j = 0; j < v2.size(); i++)
//			v2[j] *= v1[i];
//		sp = polynomSum(sp, v2));
//	}
//	return sp;
//}

double polynomValueInPoint(vector <double> v, double x) {
	double sum = 0;
	for (int i = 0; i < v.size(); i++)
		sum += v[i] * pow(x, (v.size() - 1 - i));
	return sum;
}


int main() {
	vector <double> v1, v2, result;
	double constant = 1;
	int choice;
	menu();
	cin >> choice;

	switch (choice) {
	case(1):
		//Addition
		system("CLS");
		v1 = enterPolynom();
		v2 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		cout << " + " << endl;
		printPolynom(v2);
		cout << " = " << endl;
		result = polynomSum(v1, v2);
		printPolynom(result);
		break;
	case(2):
		//Subtraction
		system("CLS");
		v1 = enterPolynom();
		v2 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		cout << " - " << endl;
		printPolynom(v2);
		cout << " = " << endl;
		result = polynomSub(v1, v2);
		printPolynom(result);
		break;
	case(3):
		//Multiplication
		system("CLS");
		v1 = enterPolynom();
		v2 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		cout << " x " << endl;
		printPolynom(v2);
		cout << " = " << endl;
		result = polynomMult(v1, v2);
		result = vectorReverse(result);
		printPolynom(result);
		break;
	case(4):
		//Division
		system("CLS");
		v1 = enterPolynom();
		v2 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		cout << " x " << endl;
		printPolynom(v2);
		cout << " = " << endl;
		result = polynomDivision(v1, v2);
		result = vectorReverse(result);
		printPolynom(result);
		break;
	case(5):
		//Multiply by a constant
		system("CLS");
		v1 = enterPolynom();
		cout << "Enter a constant: ";
		cin >> constant;
		system("CLS");
		printPolynom(v1);
		cout << " x " << endl << constant
			<< endl << " = " << endl;
		v1 = polynomMultConst(v1, constant);
		printPolynom(v1);
		break;
	case(6):
		//Dirivative
		system("CLS");
		v1 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		result = polynomDerivative(v1);
		printPolynom(result);
		break;
	case(7):
		//Antidivative
		system("CLS");
		v1 = enterPolynom();
		system("CLS");
		printPolynom(v1);
		result = polynomAntidirivative(v1);
		printPolynom(result);
		break;
	case(8):
		//Superposition
		break;
	case(9):
		//Value in a point
		system("CLS");
		v1 = enterPolynom();
		cout << "Enter a point: ";
		cin >> constant;
		system("CLS");
		printPolynom(v1);
		cout << "x = " << constant << endl;
		constant = polynomValueInPoint(v1, constant);
		cout << "Result = " << constant << endl;
		break;
	default:
		cout << "Oops!" << endl << "You have entered wrong command!" << endl;
		break;

	}
	system("pause");
	return 0;
}