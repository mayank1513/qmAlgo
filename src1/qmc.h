/*
 * qmc.h
 * classes and functions declarations
 */

#ifndef QMC_H_
#define QMC_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
 * CLASS DECLARATIONS
 */

class Implicant;
class Minterm;
class List;
class Array;
class Chart;

/*
 * END OF CLASS DECLARATIONS
 */

/*
 * FUNCTION DECLARATIONS
 */

void Qsort(short int* data, int first, int last);
void Qsort(unsigned int* data, int first, int last);

/*
 * END OFFUNCTION DECLARATIONS
 */

/*
 * CLASS DEFINITIONS
 */

class Implicant {
private:
	unsigned int* dec; // dynamic array of minterms
	short int* diff; // dynamic array of differences in binary representation of minterms
	Implicant* next; //pointer for the next element in list
	int info; // counts iteration number
	bool checked;
	int xcount; // number of 'x' in row
public:
	Implicant() {};
	~Implicant();
	Implicant(unsigned int decval);
	Implicant(Implicant* temp1, Implicant* temp2, short int differ, int step);
	void display(int i);
	friend class List;
	friend class Array;
	friend class Chart;
};

class Minterm {
private:
	unsigned int minterm; // decimal value of minterm
	int xcount; // number of 'x' in column
	bool checked;
public:
	Minterm() {};
	Minterm(unsigned int a);
	friend class Chart;
};

class List {
private:
	Implicant* start;
public:
	List() :
		start(NULL) {
	}
	;
	~List();
	void inline add(Implicant* object);
	inline Implicant* remove();
	inline void del(int step);
	inline Implicant* remove_first();
	int count();
	void display(int &number);
	friend class Array;
	friend class Chart;
};

class Array {
private:
	unsigned int** intab; // array of input variables
	List** vector; // dynamic array of pointers to lists
public:
	int decsize, binsize, min_count, dc_count;
	clock_t start;
	Array();
	~Array();
	void merge();
	inline short int hamdist(Implicant* x, Implicant* y, int step);
	inline unsigned int str2int(const std::string &str);
	inline int bitcount(unsigned int i);
	friend class Chart;
};

class Chart {
private:
	Minterm** mtab; // dynamic array of minterms
	Implicant** itab; // dynamic array of implicants
	List* coverage; // pointer to the list of solution implicants
	List* coverage2;
	bool** matrix; // boolean value matrix for finding minimal coverage
	int isize, msize, eliminated_dre, eliminated_dce; // sizes of dynamic arrays of implicants and minterms
public:
	int primenr, minnr;
	Chart(Array &object);
	~Chart();
	void initialize(Array &object);
	void init();
	inline bool essential();
	inline void add();
	inline void dre();
	inline void dce();
	void eliminate();
	void full_elimination();
	bool check();
	void display();
	void cdisplay();
	void create_output(int binsize);
	inline void dec2bin(int binsize, int decval, char* bin);
	inline int count();
	friend void inline Qsort(short int* data, int first, int last);
};

/*
 * END OF CLASS DEFINITIONS
 */

#endif /* QMC_H_ */
