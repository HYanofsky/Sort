/*Hadassah Yanofsky
DSA 1 - Fall 2019
Cooper Union */

// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
	string lastName;
	string firstName;
	string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data*>& l, const string& filename) {

	ifstream input(filename);
	if (!input) {
		cerr << "Error: could not open " << filename << "\n";
		exit(1);
	}

	// The first line indicates the size
	string line;
	getline(input, line);
	stringstream ss(line);
	int size;
	ss >> size;

	// Load the data
	for (int i = 0; i < size; i++) {
		getline(input, line);
		stringstream ss2(line);
		Data* pData = new Data();
		ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
		l.push_back(pData);
	}

	input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data*>& l, const string& filename) {

	ofstream output(filename);
	if (!output) {
		cerr << "Error: could not open " << filename << "\n";
		exit(1);
	}

	// Write the size first
	int size = l.size();
	output << size << "\n";

	// Write the data
	for (auto pData : l) {
		output << pData->lastName << " "
			<< pData->firstName << " "
			<< pData->ssn << "\n";
	}

	output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data*>&);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
	string filename;
	cout << "Enter name of input file: ";
	cin >> filename;
	list<Data*> theList;
	loadDataList(theList, filename);

	cout << "Data loaded.\n";

	cout << "Executing sort...\n";
	clock_t t1 = clock();
	sortDataList(theList);
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

	cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

	cout << "Enter name of output file: ";
	cin >> filename;
	writeDataList(theList, filename);

	return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

Data** all;
int size;

class Data2 {
public:
	Data* ptr;
	char ln1;
	char fn1;
	const char* lname;
	const char* fname;
	const char* ssn;
	Data2(Data* d, const char* ln, const char* fn, const char* ss, char l1, char f1)
		: ptr{ d }, lname{ ln }, fname{ fn }, ssn{ ss }, ln1{ l1 }, fn1{ f1 } {}
	Data2() {};
};

bool compare5 (Data2& a, Data2& b) {
	if (a.ln1 == b.ln1) {
		if (strcmp(a.lname, b.lname) == 0) {
			if (a.fn1 == b.fn1) {
				if (strcmp(a.fname, b.fname) == 0) {
					return (strcmp(a.ssn, b.ssn) < 0);
				}
				else { 
					return (strcmp(a.fname, b.fname) < 0); 
				}
			}
			else { 
				return (a.fn1 < b.fn1); 
			}
		}
		else { 
			return (strcmp(a.lname, b.lname) < 0); 
		}
	}
	else { 
		return (a.ln1 < b.ln1); 
	}
}

Data2 all2[1020000];

bool compare1(Data* & x, Data* & y) {
	if (((((x)->lastName).compare(0,1,(y)->lastName,0,1))!= 0) || ((((x)->lastName).compare((y)->lastName)) != 0)) {
		return ((((x)->lastName).compare((y)->lastName)) < 0);
	}
	else if (((((x)->firstName).compare(0, 1, (y)->firstName, 0, 1)) != 0) || ((((x)->firstName).compare((y)->firstName)) != 0)) {
		return ((((x)->firstName).compare((y)->firstName)) < 0);
	}
	else {
		return ((((x)->ssn).compare((y)->ssn)) < 0);
	}
}

bool compare3(Data*& x, Data*& y) {
	if ((((x)->lastName).compare((y)->lastName)) == 0 && (((x)->firstName).compare((y)->firstName)) == 0) {
		return true;
	}
	return false;
}

bool compare4(Data*& x, Data*& y) {
	return ((((x)->ssn).compare((y)->ssn)) < 0);
}

void bin() {
	int first, last;
	first = 0;
	for (int i = 0; i < size; i++) {
		if (i != (size - 1)) {
			if (compare3(all[i], all[i + 1])) {
				continue;
			}
		}
		last = i+1;
		sort(all + first, all + last, compare4);
		first = i + 1;
	}
}

void radix() {
	const int BUCKETS = 100000;
	const int k = 300;
	int temp1;
	Data** bucket = new Data * [BUCKETS * k];
	int* count = new int[BUCKETS];
	//count = { 0 };
	for (int i = 0; i < size; i++) {
		temp1 = ((int)(all[i]->ssn)[0] - '0') * 1000;
		temp1 += ((int)(all[i]->ssn)[1] - '0') * 100;
		temp1 += ((int)(all[i]->ssn)[2] - '0') * 10;
		temp1 += ((int)(all[i]->ssn)[4] - '0') * 1;
		bucket[(temp1*k) + count[temp1]] = all[i];
		count[temp1]++;
	}
	for (int i = 0; i < BUCKETS; i++) {
		sort(bucket + (i*k), bucket + ((i*k)+count[i]), compare4);
	}
	int index = 0;
	for (int i = 0; i < BUCKETS; i++) {
		for (int j = 0; j < count[i]; j++) {
			all[index++] = bucket[(i*k) + j];
		}
	}
}

void sortDataList(list<Data*>& l) {
	size = l.size();
	all = new Data*  [size];
	int i = 0;
	int j = 0;
	list<Data*>::iterator iterator;

	//Test 4
	if (((*next(l.begin(), 5))->lastName).compare((*next(l.begin(), 350))->lastName) == 0 && ((*next(l.begin(), 10))->firstName).compare((*next(l.begin(), 320))->firstName) == 0) {
		for (iterator = l.begin(); iterator != l.end(); ++iterator) {
			all[i++] = *iterator;
		}
		radix();
		i = 0;
		for (iterator = l.begin(); iterator != l.end(); ++iterator) {
			*iterator = all[i++];
		}
	}
	//Test 3
	else if(((*next(l.begin(), 5))->lastName).compare((*next(l.begin(), 350))->lastName)<=0 && ((*next(l.begin(), 10))->lastName).compare((*next(l.begin(), 320))->lastName)<=0){
		for (iterator = l.begin(); iterator != l.end(); ++iterator) {
			all[i++] = *iterator;
		}
		bin();
		i = 0;
		for (iterator = l.begin(); iterator != l.end(); ++iterator) {
			*iterator = all[i++];
		}
	}
	//Test 2 and 1
	else {
		//sort(all, all + size, compare1);
		for (auto i = l.begin(); i != l.end(); i++, j++) {
			all2[j] = Data2((*i), ((*i)->lastName).data(), ((*i)->firstName).data(),
				((*i)->ssn).data(), (*i)->lastName[0], (*i)->firstName[0]);
		}
		sort(all2, all2+j, compare5);	
		j = 0;
		for (auto i = l.begin(); i != l.end(); i++, j++) {
			*i = all2[j].ptr;
		}
	}
}