/********************************************
 * Object Oriented Programming Assignment 3 *
 *											*
 * Student  : MEHMET CAMBAZ                 *
 * Number   : 040020365                     *
 *											*
 * Compiler : Microsoft Visual C++ 6.0      *
 ********************************************/

#include <iostream>		// cout, cin
#include <string>		// string class
#include <cmath>		// pow(2, i)
using namespace std;	// std::cout


/***************************************************************************
* Function name		: smallest											   *
* Purpose			: finds the smallest element's index in the array sent *
* Input parameters	: the array to be searched, size of the array		   *
* Output parameters	: the minimum elements's index number                  *
* Data structures	: none												   *
* Algorithm			: iterative     									   *
****************************************************************************/
/****************************FUNCTION TEMPLATE******************************/

template <class T>
unsigned int smallest(T &array, unsigned int size)	//array can be formed from any type of elements 
{
	unsigned int i, minIndex = 0;			//default minimum is set to 0th element

	for(i=1; i<size; i++)
	{
		if( array[i] < array[minIndex] )	//if any member smaller than existing minimum found 
			minIndex = i;					//then the new minimum element's index is set i (ith element is minimum)
	}
	
	return minIndex;						//the minimum elements's index number is returned
}


/**************************TempArray CLASS TEMPLATE*************************/

template <class Type>
class TempArray {

    Type *contents;						//this class's contents member can ve formed from any type of elements
    unsigned int size;

public:
	TempArray(unsigned int);			// constructor
    Type& operator[](unsigned int);		// [] operator overloaded
	~TempArray();						// destructor
};

template <class Type>
TempArray<Type>::TempArray(unsigned int length)
{
	size = length;						//content's size is "length"
	contents = new Type [size];			//allocates memory at size "size"
}

template <class Type>
Type& TempArray<Type>::operator[](unsigned int index)
{
	string error( "Error: index is out of boundaries" );	//a string consists of the sentence given is formed

	if( (index >= size) || (index < 0) )					//if the index sent is out of the boundaries of array
		throw error;										//error occures
else
	return contents[index];								    //returns the indexth contents member
}

template <class Type>
TempArray<Type>::~TempArray()
{
	delete [] contents;										//gives back the allocated memory area for contents
}


/******************************Binary CLASS***********************************/

class Binary {

	unsigned int *contents;				//the array contains binary number's bits
	unsigned int size;					//how many bits that the binary number consists of

public:
	Binary() { size = 0; }				//default constructor, assigns size variable zero to say binary number is not set
	Binary(unsigned int);				//constructor, to set the binary number
	unsigned int calculate();			//calculates binary numbers value as decimal number
	unsigned int * getContents() { return contents; }	//returns binary number's contents array's start address
	unsigned int getSize() { return size; }				//returns the size of contents
	bool operator<(Binary &);			//overloaded < operator (for the "smallest" template function)
	//the destructor is not written because b1 and b2 will be destroyed after exiting try block
};

Binary::Binary(unsigned int length)
{
	unsigned int inData;											//the bit user enters
	string error( "Error in bit entering, a bit can be 0 or 1" );	//a string consists of the sentence given is formed

	size = length;
	contents = new unsigned int [size];				//allocating memory

	for(int i=0; i<size; i++)
	{
			cout << "Enter " << i << ". bit: ";
			cin >> inData;

			if( (inData > 1) || (inData < 0) )		//a bit can be only 0 or 1
				throw error;						//if inData is not suitable error occures
			else 
				contents[i] = inData;				//if no problem assign given bit to ith contents member

	}
}

unsigned int Binary::calculate()
{
	unsigned int sum = 0;

	for(int i=0; i<size; i++)
	{
		sum += contents[i]*pow(2,i);	
		//a binary number's decimal value is sum of the ( contents[i]*pow(2,i) ) s  where i=0 to i=size-1
		//contents[i] is the ith bit of the binary number
	}

	return sum;
}

bool Binary::operator<(Binary & b)
{
	if( this->calculate() < b.calculate() )		//compares binary numbers' decimal values
		return true;
	else
		return false;
}

// Overloading << to show binary class' contents on the screen

ostream& operator <<(ostream& out, Binary& b)  
{
	unsigned int *number;

	number = b.getContents();				//binary number's contents is returned
	
	for(int i = b.getSize()-1; i>=0; i--)
		out << number[i];					//adding binary number's bits in the reverse order to output (nth bit to 0th bit)
	
	out << endl;
    
	return out;
};



/***********************MAIN FUNCTION************************************/
int main()
{
	/* a */
	int inta[4] = {1,-7,0,3};
	unsigned int smallest_i = smallest(inta, 4);
	cout << "Smallest element is: " << inta[smallest_i] << endl;


	/* b */ 
	TempArray<int> intArr(5);
	try {
	    intArr[0] = 1;
	    intArr[1] = -5;
	    intArr[2] = 8;
	}
	catch(const string &msg) {
	    cout << msg << endl;
	}
	smallest_i = smallest(intArr, 3);
	cout << "Smallest element is: " << intArr[smallest_i] << endl;  


	/* c */
	TempArray<Binary> binArr(3);
	try {
		Binary b1(3), b2(2);
		binArr[0] = b1;
		binArr[1] = b2;
	}
	catch(const string & msg) {
		cout << msg << endl;
	}
	smallest_i = smallest(binArr, 2);
	cout << binArr[smallest_i] << endl;


	return 0;
} 