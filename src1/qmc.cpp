/***************************************************************************
 *   Function definitions                                                  *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "qmc.h"

using namespace std;
/*
 * METHODS DEFINITIONS
 */

inline Implicant::Implicant(unsigned int decval) {
	next = NULL;
	xcount = 0;
	info = 0;
	checked = false;
	dec = new unsigned int [1];
	diff = NULL;
	dec[0] = decval;
}

Implicant::~Implicant() {
	delete [] dec;
	delete [] diff;
}

inline Implicant::Implicant(Implicant *temp1, Implicant *temp2, short int differ,
		int step) {
	next = NULL;
	xcount = 0;
	info = step;
	checked = false;
	int x = ( int ) pow( 2, step);
	int y = ( int ) pow( 2, step - 1);
	dec = new unsigned int [x];
	diff = new short int [x];
	for (int i = 0; i < y; i++) {
		dec[i] = temp1->dec[i];
	}
	for (int i = y; i < x; i++) {
		dec[i] = temp2->dec[i - y];
	}
	for (int i = 0; i < step - 1; i++) {
		diff[i] = temp1->diff[i];
	}
	diff[step - 1] = differ;
	Qsort(diff, 0, step - 1);
	Qsort(dec, 0, x - 1);
}

void Implicant::display(int i) {
	for (int k = 0; k < ( int ) pow( 2, info); k++)
		cout << dec[k] << ", ";
	cout << "\t" << "info = " << info << endl;
}

Minterm::Minterm(unsigned int a) {
	minterm = a;
	checked = false;
}

List::~List() {
	if (start != NULL) {
		Implicant* temp = start;
		while (temp != NULL) {
			start = temp;
			temp = temp->next;
			delete start;
			cout << "deleted" << endl;
		}
	}
}

inline void List::add(Implicant* object) {     // adds the implicants to the implicant list
	if (start == NULL) {                       //1st checks whether it is there already or not.
		start = object;
	} else {
		Implicant *temp= NULL, *previous= NULL;
		temp = start;
		while (temp != NULL) {
			int check = 0;
			if (temp->info == object->info) {                           //checks whether implicant is already there or not
				int x = ( int ) pow( 2, object->info);
				for (int i = 0; i < x; i++) {
					if (temp->dec[i] == object->dec[i])
						check++;
				}
				if (check == x) {
					delete object;
					return;
				}
			}
			previous = temp;
			temp = temp->next;
		}
		previous->next = object;                                    // new implicant is added.
	}
}

inline Implicant* List::remove() {
	Implicant* obj = start;
	start = start->next;
	obj->next = NULL;
	return obj;
}

inline void List::del(int step) // deletes implicants which were merged from the list in each step
{
	Implicant* prev;
	Implicant* temp;
	temp = this->start;
	prev = temp;
	while (temp != NULL) {
		if (temp == this->start && temp->info <= step && temp->checked == true) { // if first in the list has to be deleted
			if (temp->next == NULL) { // if there's only one on the list
				delete temp;
				this->start = NULL;
				return;
			} else {
				this->start = temp->next;
				temp->next = NULL;
				delete temp;
				temp = this->start;
			}
		} else if (temp->info <= step && temp->checked == true) {
			prev->next = temp->next;
			temp->next = NULL;
			delete temp; // why?
			temp = prev;
		}
		prev = temp;
		temp = temp->next;
	}
}

inline Implicant* List::remove_first() {
	Implicant* temp;
	if (this->start != NULL) {
		temp = this->start;
		this->start = this->start->next;
		temp->next = NULL;
		return temp;
	} else return NULL;
}

int List::count() {
	Implicant* ptr = start;
	int counter = 0;
	while (ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
	return counter;
}

void List::display(int &number) {
	if (start == NULL)
		/*cout << "List is empty" << endl*/;
	else {
		Implicant* temp = start;
		number=0;
		while (temp != NULL) {
			number++;
			/*for ( int k = 0; k < ( int ) pow ( 2, temp->info ); k++ ) cout << temp->dec[k] << ", ";
			 cout << "\t" << "info = " << temp->info << endl;*/
			temp = temp->next;
		}
		number++;
	}
}

Array::Array() {
	char file[15];
	int decval = 0, numlen = 0, maxval = 0, counter = 1;
	cout << "Input file name: ";
	cin >> file;
	start=clock();
	ifstream input(file);
	if ( !input) {
		cout << "Error: Can't open the file named input.txt." << endl;
		exit( 1);
	}
	string str;
	getline(input, str); // reads the first line of input
	if (str[0] == 'x') // checks for dc value
		str.erase( 0, 1); // erases the 'x' character from str for str2int correct input
	decval = str2int(str);
	numlen = str.length();
	if (decval > maxval)
		maxval = decval;
	while (input) {
		getline(input, str);
		min_count++;
		while ( !input.eof() ) // keep reading until end-of-file
		{
			min_count++;
			if (str[0] == 'x') { // checks for dc value
				str.erase( 0, 1); // erases the 'x' character from str for str2int correct input
				dc_count++;
			}
			decval = str2int(str);
			numlen = str.length();
			if (decval > maxval)
				maxval = decval;
			input >> str; // sets EOF flag if no value found
			counter++;
		}
	}
	input.close();
	//cout << "End-of-file reached.." << endl;
	binsize = ( int ) ceil(log2( ( double ) maxval ) ); // calculates binsize
	if (fmod(sqrt(maxval), 2) == 0)
		binsize = binsize + 1;
	decsize = counter; // calculates decsize
	ifstream input2(file);
	getline(input2, str);
	intab = new unsigned int *[decsize];
	for (int i = 0; i < decsize; i++)
		intab[i] = new unsigned int [2];
	for (int i = 0; i < decsize; i++) {
		for (int j = 0; j < 2; j++)
			intab[i][j] = 0;
	}
	if (str[0] == 'x') {
		str.erase( 0, 1); // erases the 'd' character from str for str2int correct input
		intab[0][1] = 1;
	}
	intab[0][0] = str2int(str);
	int i = 1;
	while (input2) {
		getline(input2, str);
		while ( !input2.eof() ) // keep reading until end-of-file
		{
			if (str[0] == 'x') {
				str.erase( 0, 1); // erases the 'x' character from str for str2int correct input
				intab[i][1] = 1;
			}
			intab[i][0] = str2int(str);
			i++;
			input2 >> str; // sets EOF flag if no value found
		}
	}
	input2.close();
	//cout << "End-of-file reached.." << endl;

	vector = new List* [binsize + 1];
	for (int i = 0; i < binsize + 1; i++) {
		vector[i] = new List();
	}
	for (int i = 0; i < decsize; i++) {
		(vector[bitcount(intab[i][0])])->add(new Implicant(intab[i][0]));
	}
}

Array::~Array() {
	for (int i = 0; i < binsize + 1; i++) {
		delete vector[i];
	}
	delete [] vector;
	for (int i = 0; i < decsize; i++) {
		delete [] intab[i];
	}
	delete [] intab;
}

inline int Array::bitcount(unsigned int i) // counts number of ones in unsigned int number
{
	i = i - ( (i >> 1 ) & 0x55555555 );
	i = (i & 0x33333333 ) + ( (i >> 2 ) & 0x33333333 );
	i = (i + (i >> 4 ) ) & 0x0f0f0f0f;
	i = i + (i >> 8 );
	i = i + (i >> 16 );
	return ( int ) (i & 0x3f );
}

inline unsigned int Array::str2int(const string &str) // converts string value into integer value
{
	stringstream ss(str);
	unsigned int n;
	ss >> n;
	return n;
}

inline short int Array::hamdist(Implicant* x, Implicant* y, int step) // calculates Hamming distance between two implicants
{
	if (x->info == 0 && y->info == 0) {
		unsigned int val = x->dec[0] ^ y->dec[0];
		if (bitcount(val) == 1) {
			short int i = 0;
			while (val) {
				val >>= 1;
				i++;
			}
			return i;
		} else
			return -1;
	} else {
		int check = 0;
		unsigned int val = 0;
		int counter = 0;
		for (int i = 0; i < x->info; i++) {
			if (x->diff[i] == y->diff[i])
				check++;
		}
		if (check == x->info) {
			for (int i = 0; i < x->info; i++) {
				for (int j = 0; j < x->info; j++) {
					val = x->dec[i] ^ y->dec[j];
					if (bitcount(val) == 1)
						counter++;
					if (counter == 1)
						break;
				}
				if (counter == 1)
					break;
			}
			if (counter == 1) {
				short int i = 0;
				while (val) {
					val >>= 1;
					i++;
				}
				return i;
			} else
				return -1;
		} else
			return -1;
	}
}

void Array::merge() // merges the implicants
{
	Implicant* temp1 = NULL;
	Implicant* temp2 = NULL;
	short int differ = 0;
	for (int i = 0; i < 11; i++) {
		for (int j = 1; j < binsize + 1; j++) {
			temp1 = ( this->vector[j - 1] )->start;
			temp2 = ( this->vector[j] )->start;
			if (temp1 != NULL && temp2 != NULL) {
				while (temp1 != NULL) {
					while (temp2 != NULL) {
						if (temp1->info == i && temp2->info == i) {
							differ = hamdist(temp1, temp2, i);
							if (differ != -1) {
								temp1->checked = true;
								temp2->checked = true;
								Implicant* ptr = new Implicant( temp1, temp2, differ, i + 1 );
								( this->vector[j - 1] )->add(ptr);
							}
						}
						temp2 = temp2->next;
					}
					temp1 = temp1->next;
					temp2 = ( this->vector[j] )->start;
				}
			}
			this->vector[j - 1]->del(i);	//delete implicants that were merged
			if (j == binsize) {
				this->vector[j]->del(i);
			}
		}
	}
}

Chart::Chart(Array &object) {
	mtab = NULL;
	itab = NULL;
	msize = 0;
	isize = 0;
	eliminated_dre = 0;
	eliminated_dce = 0;
	coverage = new List();
	coverage2 = new List();
	int size1 = 0, size2 = 0;
	Implicant* ptr= NULL;
	for (int i = 0; i < object.binsize + 1; i++) // calculates isize
	{
		if (object.vector[i][0].start != NULL) {
			ptr = object.vector[i][0].start;
			while (ptr != NULL) {
				size1++;
				//ptr->display(0);
				ptr = ptr->next;
			}
		}
	}
	isize = size1;
	cout << endl << "implicants after merging (isize): " << isize << endl;
	for (int i = 0; i < object.decsize; i++) //calculates msize
	{
		if (object.intab[i][1] != 1)
			size2++;
	}
	msize = size2;
	cout << endl << "input minterms (msize): " << msize << endl;
	matrix = new bool* [isize];
	for (int i = 0; i < isize; i++) {
		matrix[i] = new bool [msize];
	}
	initialize(object);
}

Chart::~Chart() {
	for (int i = 0; i < isize; i++) {
		delete itab[i];
		delete [] matrix[i];
	}
	delete [] itab;
	coverage->start = NULL; // coverage is pointing to the same addreses as itab[i]
	coverage2->start = NULL;
	delete [] matrix;
	for (int i = 0; i < msize; i++) {
		delete mtab[i];
	}
	delete [] mtab;
	delete coverage;
	delete coverage2;
}

void Chart::initialize(Array &object){
	Implicant* ptr= NULL;
	for (int i = 0; i < isize; i++) // initializes matrix with boolean 'false' values
	{
		for (int j = 0; j < msize; j++) {
			matrix[i][j] = false;
		}
	}
	mtab = new Minterm* [msize]; // table of minterms without DC values
	for (int j = 0, counter = 0; j < object.decsize; j++) {
		if (object.intab[j][1] == 1)
			counter++;
		if (object.intab[j][1] != 1) {
			mtab[j - counter] = new Minterm(object.intab[j][0]);
		}
	}
	itab = new Implicant* [isize]; // table of prime implicants
	int j = 0; // position in eteb
	for (int i = 0; i < object.binsize + 1; i++) // fills the table of prime implicants;
	{
		ptr = object.vector[i]->remove_first();
		while (ptr != NULL) {
			itab[j] = ptr;
			itab[j]->checked = false;
			j++;
			ptr = object.vector[i]->remove_first();
		}
	}
	for (int i = 0; i < isize; i++) // sets boolean 'true' marks in the matrix
	{
		int x = ( int ) pow( 2, itab[i]->info);
		for (int j = 0; j < msize; j++) {
			int counter = 0;
			for (int k = 0; k < x; k++) {
				if (itab[i]->dec[k] == mtab[j]->minterm)
					counter++;
				if (counter > 0)
					break;
			}
			if (counter > 0) {
				matrix[i][j] = 1;
			}
		}
	}
}

void Chart::init() // initializes/modifies values of implicant and minterm objects - counts 'true' marks for each column/row
{
	int cxcounter = 0, rxcounter = 0;
	for (int j = 0; j < msize; j++) {
		mtab[j]->checked = 0;
		cxcounter = 0;
		for (int i = 0; i < isize; i++) {
			if (matrix[i][j] == 1) {
				cxcounter++;
			}
		}
		mtab[j]->xcount = cxcounter;
	}
	for (int i = 0; i < isize; i++) {
		rxcounter = 0;
		for (int j = 0; j < msize; j++) {
			if (matrix[i][j] == 1) {
				rxcounter++;
			}
		}
		itab[i]->xcount = rxcounter;
	}

}

inline int Chart::count() // counts 'true' marks that are left in the matrix
{
	int counter = 0;
	if (isize < msize) {
		for (int i = 0; i < isize; i++) {
			counter += itab[i]->xcount;
		}
	} else {
		for (int i = 0; i < msize; i++) {
			counter += mtab[i]->xcount;
		}
	}
	return counter;
}

inline bool Chart::essential() // finds essential implicants in the matrix
{
	bool found = false;
	for (int j = 0; j < msize; j++) {
		if (mtab[j]->xcount == 1) {
			mtab[j]->xcount = 0;
			int row = 0;
			for (int i = 0; i < isize; i++) {
				if (matrix[i][j] == true) {
					matrix[i][j] = false;
					row = i;
					found = true;
				}
			}
			primenr++;
			itab[row]->xcount = 0;
			//itab[row]->next = NULL; // need to get rid of this here
			coverage->add(itab[row]);
			for (int k = 0; k < msize; k++) {
				if (matrix[row][k] == true) {
					matrix[row][k] = false;
					mtab[k]->xcount = 0;
					for (int l = 0; l < isize; l++) {
						if (matrix[l][k] == true) {
							matrix[l][k] = false;
							itab[l]->xcount--;
						}
					}
				}
			}
		}
	}
	return found;
}

inline void Chart::dre() { // dominated row elimination
	int equal = 0, more = 0;
	for (int j = 0; j < isize - 1; j++) {
		if (itab[j]->xcount > 0) {
			for (int k = j + 1; k < isize; k++) {
				if (itab[k]->xcount > 0) {
					equal = 0;
					more = 0;
					if (itab[j]->xcount >= itab[k]->xcount) {
						for (int l = 0; l < msize; l++) {
							if (matrix[j][l] == true && matrix[k][l] == true)
								equal++;
						}
						if (equal == itab[k]->xcount) {
							itab[k]->checked = true;
						}
					}
					if (itab[j]->xcount < itab[k]->xcount) {
						for (int l = 0; l < msize; l++) {
							if (matrix[j][l] == true && matrix[k][l] == true)
								equal++;
						}
						if (equal == itab[j]->xcount) {
							itab[j]->checked = true;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < isize; i++) {
		if (itab[i]->checked == true) {
			itab[i]->checked = false;
			itab[i]->xcount = 0;
			for (int j = 0; j < msize; j++) {
				if (matrix[i][j] == true) {
					matrix[i][j] = false;
                }
			}
		}
	}
}

inline void Chart::dce() { //dominating column elimination
	int equal, more;
	for (int j = 0; j < msize - 1; j++) {
		if (mtab[j]->xcount > 0 && mtab[j]->checked == false) {
			for (int k = j + 1; k < msize; k++) {
				if (mtab[k]->xcount > 0 && mtab[j]->checked == false) {
					equal = 0;
					more = 0;
					if (mtab[j]->xcount <= mtab[k]->xcount) {
						for (int l = 0; l < isize; l++) {
							if (matrix[l][j] == true && matrix[l][k] == true)
								equal++;
						}
						if (equal == mtab[j]->xcount) {
							mtab[k]->checked = true;
						}
					}
					if (mtab[j]->xcount > mtab[k]->xcount) {
						for (int l = 0; l < isize; l++) {
							if (matrix[l][j] == true && matrix[l][k] == true)
								equal++;
						}
						if (equal == mtab[k]->xcount) {
							mtab[j]->checked = true;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < isize; i++) {
		if (itab[i]->checked == true) {
			itab[i]->checked = false;
			itab[i]->xcount = 0;
			for (int j = 0; j < msize; j++) {
				if (matrix[i][j] == true) {
					matrix[i][j] = false;
					mtab[j]->xcount--;
				}
			}
		}
	}
}

/*
 *	this function searches for the highest xcount value in each row and adds this row to the solution
 */
void Chart::eliminate() { // heuristic method of solving the SCP
	int max = 0, row = 0;
	essential();
	while (count() /*check() == false*/) {
		max = 0;
		row = 0;
		for (int i = 0; i < isize; i++) {
			//if (itab[i].xcount > 0) {
				if (itab[i]->xcount > max) {
					max = itab[i]->xcount;
					row = i;
				}
			//}
		}
		itab[row]->xcount = 0;
		//itab[row]->next = NULL;
		coverage->add(itab[row]);
		for (int k = 0; k < msize; k++) {
			if (mtab[k]->xcount > 0) {
				if (matrix[row][k] == true) {
					matrix[row][k] = false;
					mtab[k]->xcount = 0;
					for (int l = 0; l < isize; l++) {
						if (matrix[l][k] == true) {
							matrix[l][k] = false;
							itab[l]->xcount--;
						}
					}
				}
			}
		}
	}
}

/*
 *	this is the full elimination method. it utilizes the dce() and dre() functions for solving the SCP.
 *	since the SCP is NP-hard thus for large input files it takes some time to find the solution using ths method.
 *	the function performs the dce and dre oprerations on the matrix removing all redundant columns/rows based on the QMC algorithm.
 *	after each run of the dce() and dre() 'true' marks in the matrix are counted.
 *	when there was a modification of 'true' marks count the essential() function is used to find newly created "post-essential" implicants.
 *	in other case a heuristic function is used - it takes the row with the highest xcount and adds it to the solution.
 */

void Chart::full_elimination() {
	int before = 0, after = 0, row = 0, max = 0;
	essential();
	while (count() /*check() == false*/) {
		//function call
		//before = count(); // count 'true' marks before invoking dce() and dre() functions
		dre();
		dce();
		//after = count(); // count 'true' marks after invoking dce() and dre() functions
		if (essential() == false) {
			//cout << "heuristic function used" << endl;
			max = 0;
			row = 0;
			for (int i = 0; i < isize; i++) {
				if (itab[i]->xcount > 0) {
					if (itab[i]->xcount > max) {
						max = itab[i]->xcount;
						row = i;
					}
				}
			}
			itab[row]->xcount = 0;
			//itab[row]->next = NULL;
			coverage->add(itab[row]);
			for (int k = 0; k < msize; k++) {
				if (mtab[k]->xcount > 0) {
					if (matrix[row][k] == true) {
						matrix[row][k] = false;
						mtab[k]->xcount = 0;
						for (int l = 0; l < isize; l++) {
							if (matrix[l][k] == true) {
								matrix[l][k] = false;
								itab[l]->xcount--;
								/*if (itab[l]->xcount < 0)
									cout << "Xcount negativ - error" << endl;*/ // for debug purpose
							}
						}
					}
				}
			}
		}
		//after = count(); // for testing purpose
	}
	Implicant* obj= NULL; // check for implicant redundancy
	int x = coverage->count();
	for (int i = 0; i < x; i++) {
		obj = coverage->remove();
		if (check() == 0)
			coverage->add(obj);
	}
}

inline void Chart::dec2bin(int binsize, int decval, char *bin) {
	for (int i = binsize - 1; i >= 0; --i) {
		bin[i] = (decval % 2 == 0 ? '0' : '1' );
		decval >>= 1;
	}
}

void Chart::create_output(int binsize) { // creates the output file
	binsize = binsize;
	ofstream output;
	output.open("output.txt");
	char *bin = new char[binsize];
	Implicant *temp = coverage->start;
	while (temp != NULL) {
		dec2bin(binsize, temp->dec[0], bin);
		for (int i = 0; i < temp->info; i++) {
			int x = temp->diff[i];
			bin[binsize - x] = '-';
		}
		bin[binsize] = 0;
		for (int x = 0; x < binsize; x++) {
			if (bin[x] != '-') {
				output << " ";
				output << char ( 97 + x );

				if (bin[x] == 49)
					output << " ";
				else
					output << "'";
			} else
				output << "   ";
		}
		output << "\n";
		temp = temp->next;
	}
	output.close();
	cdisplay();
	delete [] bin;
}

void Chart::cdisplay() // displays the minimal coverage list
{
	coverage->display(minnr);
}

void Chart::display() {
	cout << "implikanty: " << endl;
	for (int i = 0; i < isize; i++) {
		for (int j = 0; j < ( int ) pow( 2, itab[i]->info); j++)
			cout << itab[i]->dec[j] << ", ";
		cout << itab[i]->info << endl;
	}
	cout << "mintermy: " << endl;
	for (int i = 0; i < msize; i++) {
		cout << mtab[i]->minterm << " ";
	}
	cout << endl;
	for (int i = 0; i < isize; i++) {
		for (int j = 0; j < msize; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool Chart::check() { // checks the solution
	for (int i = 0; i < msize; i++) { // clears the 'checked' boolean filed
		mtab[i]->checked = 0;
	}
	Implicant * temp = coverage->start;
	while (temp != NULL) { // checks the list of solution implicants
		int x = ( int ) pow( 2, temp->info);
		for (int j = 0; j < x; j++) {
			for (int k = 0; k < msize; k++) {
				if ((unsigned int)temp->dec[j] == mtab[k]->minterm){
					mtab[k]->checked = 1;
				}
			}
		}
		temp = temp->next;
	}
	int counter = 0;
	for (int i = 0; i < msize; i++) {
		if (mtab[i]->checked == 1)
			counter++;
	}
	cout << "counter = " << counter << endl;
	if (counter == msize)
		return 1;
	else
		return 0;
}

/*
 * END OF METHODS DEFINITIONS
 */

/*
 * FUNCTION DEFINITIONS
 */
inline void Qsort(short int *data, int first, int last) { // quick-sort
	if (first >= last)
		return;
	short int pivot = data[first];
	int left = first, right = last + 1;
	while ( 1) {
		do
			left++;
		while (left <= last && data[left] < pivot);
		do
			right--;
		while (data[right] > pivot);
		if (left > right)
			break;
		swap(data[left], data[right]);
	}
	swap(data[first], data[right]);
	Qsort(data, first, right - 1);
	Qsort(data, right + 1, last);
}

inline void Qsort(unsigned int *data, int first, int last) { // quick-sort
	if (first >= last)
		return;
	unsigned int pivot = data[first];
	int left = first, right = last + 1;
	while ( 1) {
		do
			left++;
		while (left <= last && data[left] < pivot);
		do
			right--;
		while (data[right] > pivot);
		if (left > right)
			break;
		swap(data[left], data[right]);
	}
	swap(data[first], data[right]);
	Qsort(data, first, right - 1);
	Qsort(data, right + 1, last);
}
/*
 * END OF FUNCTION DEFINITIONS
 */
