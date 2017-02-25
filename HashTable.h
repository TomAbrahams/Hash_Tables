#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
using namespace std;

const int CAPACITY = 11;
const int STEPSIZE = 3;

class HashTable
{
	//Overloaded Ostream to print out the hash table
	friend ostream & operator <<(ostream & os, const HashTable & theTable);



public:
	//Default Constructor
	HashTable();

	//Overloaded Constructor
	HashTable(int capacity);

	//Copy Constructor
	HashTable(const HashTable & otherTable);

	//Insert an element into the hash table using the appropriate
	//Technique.
	void insert(int theKey);

	//Search for a particular element
	bool search(int item);

	//Return capacity
	int getCapacity() const;

	//Overloaded assignment operator
	HashTable& operator=(const HashTable& otherTable);

	//Overloated the [] operator to return an index of the hash table
	int &operator[](int i);

	//Destructor
	~HashTable();

	//Delete Key
	void deleteKey(int key);


	//Search key Idx
	int searchKeyIdx(int key) const;
private:

	//This is a standard hash value as assigned
	int hashValue(int key) const;
	//This can be linear probing, or quadratic
	int hashValue(int key, int j) const;
	//Standard items for the hash table
	int *table;				//pointer to the hash table
	int numOfElements;		//number of items in the hash table
	int capacity;			//maximum length of the hash table	
};

#endif
