/* Objective 3:  minimization of boolean funtions using 1.Quine Mcclusky, 2.hueristic, and 3.random search algorithms */


#include "qmc.h"
#include "qmc.cpp"

using namespace std;
int main(int argc, char *argv[])
{
	clock_t end;
	double diff;
	int choice = 0;

	cout << endl << "Please choose the method of minimizing the boolean function(enter the correspoding number)" << endl << endl;
	cout << "\t(1)\theuristic algorithm (fast, but less accurate)" << endl << endl;
	cout << "\t(2)\tfull minimization (slow, optimum solution)" << endl << endl;
	do{
		cout << "Your choice is: ";
		cin >> choice;
		cout << endl;
	}
	while ((choice < 1) && (choice > 2));
	Array *object = new Array();

	cout << "reading from file\t\tDONE" << endl;
	cout << "merging minterms\t\tSTARTED" << endl;

	object->merge();

	cout << "merging minterms\t\tDONE" << endl;
	cout << "minimization \t\t\tSTARTED" << endl;

	Chart *prime = new Chart(*object);
	prime->init();

	if (choice == 1) prime->eliminate();
	if (choice == 2) prime->full_elimination();
	prime->cdisplay();

	end=clock();
	diff = (end-object->start)/CLK_TCK;

	cout << "Minimization \t\t\tDONE" << endl;
	cout << "max binary size:\t\t" << object->binsize << endl;
	//cout << "prime implicants:\t\t" << prime->primenr << endl;
	cout << "checking solution..." << endl;

	bool check;
	check = prime->check();

	if (check == 1)
		cout << "check:\t\t\t\tSUCCESS" << endl;
	else
		cout << "check:\t\t\tFAILURE" << endl;
	cout << "*********************************************************";
	cout << endl << "*\t\t\t\t\t\t\t*" << endl;
	cout << "*\tnumber of minimal coverage implicants: " <<prime->minnr<< "\t*";
	cout << endl << "*\t\t\t\t\t\t\t*" << endl;
	cout << "*\trun time: " << diff << " [s]" << "\t\t\t\t\t*";
	cout << endl << "*\t\t\t\t\t\t\t*" << endl;
	cout << "*********************************************************" << endl;

	prime->create_output(object->binsize);
	cout << "output file created" << endl;

	delete object;
	delete prime;

	return EXIT_SUCCESS;
}
