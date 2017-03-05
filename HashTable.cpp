//Developing a harder version that can auto test.
#include "HashTable.h"

ostream & operator <<(ostream & os, const HashTable & theTable)
{
	for (int i = 0; i < theTable.capacity; i++)
	{
		cout << "Index " << i << ":";
		if (theTable.table[i] == -1)
			cout << "E" << endl;
		else
			cout << theTable.table[i] << endl;
	}
	return os;
}

HashTable::HashTable()
{
	numOfElements = 0;
	capacity = CAPACITY;
	table = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		table[i] = -1;
}
HashTable::HashTable(int capacity)
{
	numOfElements = 0;
	this->capacity = capacity;
	table = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		table[i] = -1;
}

HashTable::HashTable(const HashTable & otherTable)
{
	numOfElements = otherTable.numOfElements;
	capacity = otherTable.capacity;

	table = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		table[i] = otherTable.table[i];
}
//Function for insert
void HashTable::insert(int theKey)
{
	int j = 0;
	int hValue = hashValue(theKey, j); //Hash Value for Readability

	//while ((count < (capacity) && (table[hValue] != -1)) //linear probing
	
	//Quadratic function.
	while ((j < (capacity + 1) / 2) && (table[hValue] != -1)
		&& (table[hValue] != -2)) //quadratic function
	{
		hValue = hashValue(theKey, ++j);
	}
	if (numOfElements == capacity)
		cerr << "Table is full. Cannot insert." << endl;
	else
	{
		++numOfElements;
		table[hValue] = theKey;
	}
	//Insert should be when f == r. Cannot since f and r are not declared in private.
}
//Search for a specific item in the hash table. Return True if found.
bool HashTable::search(int item)
{
	
	bool flag = true;	//Need a flag to know if we are finished.
	int j= 0;
	int hValue = hashValue(item, j); //j ill work on it
	//while ((count < (capacity) && (table[theHashIdx] != item) && (table[theHashIdx] != -1)) //linear probing
	while ((j < (capacity + 1) / 2) && (table[hValue] != item)
		&& (table[hValue] != -1)) //quadratic function
	{	
		hValue = hashValue(item, ++j); //value changed
	}
	//Created flag variable for readability
	//This flag determines if we were finished. Notice it ends at (capacity + 1)/2
	if ((table[hValue] == -1) || ((capacity + 1) / 2 == j))
		flag = false;
	return flag;
}

//Return capacity
int HashTable::getCapacity() const
{
	return capacity;
}

//Returns to find the index using the bracket characters,
//But also be able to store an item at a particular index.
int & HashTable::operator[](int i)
{
	if (i > capacity)
	{
		cerr << "Index is out of bounds" << endl;
		//Returning first element to return an item.
		return table[0];
	}
	else
		return table[i];

}

//The has table needs and operator overloader for = for readability.
HashTable& HashTable::operator=(const HashTable & otherTable)
{
	if (&otherTable != this)
	{
		if (capacity != otherTable.capacity)
		{
			delete[] table;
			table = new int[otherTable.capacity];

			capacity = otherTable.capacity;
		}
		numOfElements = otherTable.numOfElements;

		for (int i = 0; i < capacity; i++)
			table[i] = otherTable.table[i];

	}
	else
		cerr << "Attempted assignment to itself." << endl;
	return *this;
}

HashTable::~HashTable()
{
	capacity = 0;
	numOfElements = 0;
	delete[] table;
	table = NULL;
}

//Private hashValue Key
int HashTable::hashValue(int key, int j) const
{
	//return ((key + (j * STEPSIZE)) % CAPACITY); //Again this is for linear probing.
	return (((2 * key + 5) + (j*j)) % capacity); //Quadratic
}

//Asked for in the instructions,
//An overloaded way to get directly to linear probing
int HashTable::hashValue(int theKey) const
{
	//This gets me the hashValue if the function. ONLY for LINEAR PROBING.
	return ((theKey) % capacity);
}

//deleteKey
void HashTable::deleteKey(int key)
{
	if (numOfElements == 0)
		cerr << "Hash table is empty. Cannot delete." << endl;
	else
	{
		int idx = searchKeyIdx(key);
		if (idx == -999)
			cout << "Key Not Found." << endl;
		else
		{
			table[idx] = -2;	//Done in order to skip over for deletion. 
						//This -2 is done in order to signal to the compiler that there was something here.
			numOfElements--;	//Decrement elements.
		}
	}
}

//searchKeyIdx
int HashTable::searchKeyIdx(int key) const
{
	int j = 0;
	int hValue = hashValue(key, j);
	bool flag = false;
	while ((table[hValue] != -1) &&
		(j < (capacity + 1) / 2) && (!flag))
	{
		if (table[hValue] == key)
			flag = true;
		else
		{
			hValue = hashValue(key, ++j);
			flag = false;
			hValue = -999;
		}
	}
	return hValue;
}
