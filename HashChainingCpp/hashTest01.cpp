#include <iostream>
#include "HashTable.h"

using namespace std;

unsigned int DivResidue(unsigned int key)
{
	return key % static_cast<unsigned int>(TBL_MAX);
}

int main(void)
{
	HashTable<int> tbl1(DivResidue);

	int a1 = 1000;
	int a2 = 2000;
	int a3 = 3000;
	int a4 = 4000;
	int a5 = 5000;

	int val;

	tbl1.TInsert(101, a1);
	tbl1.TInsert(102, a2);
	tbl1.TInsert(202, a3);
	tbl1.TInsert(104, a4);
	tbl1.TInsert(105, a5);

	bool temp = tbl1.TSearch(105, val);

	printf("the searched value : %d \n", val);

	temp = tbl1.TDelete(101, val);
	tbl1.TDelete(102, val);
	tbl1.TDelete(202, val);
	tbl1.TDelete(104, val);
	tbl1.TDelete(105, val);

	printf("the deleted value : %d \n", val);

	cout << "----------------------" << endl;

	temp = tbl1.TSearch(101, val);
	printf("the searched value : %d \n", val);
	
	temp = tbl1.TSearch(102, val);
	printf("the searched value : %d \n", val);
	
	temp = tbl1.TSearch(202, val);
	printf("the searched value : %d \n", val);

	temp = tbl1.TSearch(104, val);
	printf("the searched value : %d \n", val);

	temp = tbl1.TSearch(105, val);
	printf("the searched value : %d \n", val);


	return 0;
}
