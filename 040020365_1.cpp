/********************************************
 * Object Oriented Programming Assignment 2 *
 *											*
 * Student  : MEHMET CAMBAZ                 *
 * Number   : 040020365                     *
 *											*
 * Compiler : Microsoft Visual C++ 6.0      *
 ********************************************/

#include<iostream>

using namespace std;

class Counter {

protected:
	int value;

public:
	Counter(int=0);				//constructor
	int getValue();
	void setValue(int);
	void operator++(int);		//postincrement
	void operator--();
	bool operator>(Counter &);

};

Counter::Counter(int setvalue)
{
	value = setvalue;
}

int Counter::getValue()
{
	return value;
}

void Counter::setValue(int new_value)
{
	value = new_value;
}

void Counter::operator++(int)				//postincrement
{
	value = value+1;
}

void Counter::operator--()
{
	value = value-1;
}

bool Counter::operator>(Counter &right)		//compares two counters
{
	if(value > right.value)
		return true;
	else
		return false;
}

/****************************************************************************/
/*  ModN_Counter is a Counter, it is derived privately from Counter,
    all public methods are inherited as private to ModN_Counter 
    ModN_Counter and Counter classes have "is-a" relation
    so that ModN_Counter is a Counter										*/
/****************************************************************************/
class ModN_Counter : private Counter {
	
protected:
	int n;	//mod of counter

public: 
	ModN_Counter(int, int=0);				//constructor
	ModN_Counter(const ModN_Counter &);		//copy constructor
	using Counter::getValue;				//we made Counter's getValue() method public to ModN_Counter
	bool operator++(int);					//postincrement operator overloaded
	bool operator--();						//decrement operator overloaded
	bool operator>(ModN_Counter &);			//bigger than operator overloaded
};

ModN_Counter::ModN_Counter(int mod, int initial) : Counter(initial)
{
	if(mod<2)
		mod = 2;

	n = mod;

	if(initial > n-1)
		initial = n-1;
	
	value = initial;
}

ModN_Counter::ModN_Counter(const ModN_Counter &copy)
{
	value = copy.value;
	n = copy.n;
}

bool ModN_Counter::operator++(int)	//postincrement
{
	value = (value+1)%n;

	if(value == 0)		//if next value is n, then according to mod arithmetic; value is set to zero
		return true;
	else 
		return false;
}

bool ModN_Counter::operator--()
{
	if( value == 0 ) {
		value = n-1;		//if existing value is 0 then previous value of the existing value is mod-1 (n-1)
		return true;
	}
	else {
		value = (value-1)%n;
		return false;
	}
}

bool ModN_Counter::operator>(ModN_Counter &right)
{
	if( value > right.value ) 
		return true;
	else 
		return false;
}

/****************************************************************************/
/*  TimeOfDay class has three ModN_Counter variables
    this means TimeOfDay and ModN_Counter have "has-a" relation
	so that TimeOfDay has ModN_Counter in its structure						*/
/****************************************************************************/
class TimeOfDay {	

protected:
	ModN_Counter second;
	ModN_Counter minute;
	ModN_Counter hour;

public:
	TimeOfDay(int=0, int=0, int=0);		//constructor
	TimeOfDay(TimeOfDay &);				//copy constructor
	incS();								//increment second
	incM();								//increment minute
	incH();								//increment hour
	getS();								//get second's value
	getM();								//get minute's value
	getH();								//get hour's value
	bool operator>(TimeOfDay &);		//bigger than operator overloaded, compares 2 TimeOfDay objects
	void operator=(const TimeOfDay &);		//assignment operator overloaded, assigns 1 TimeOfDay object to an another one
	print();
};

TimeOfDay::TimeOfDay(int h, int m, int s)		//constructor
: hour(24, h), minute(60, m), second(60, s)		
/* ModN_Counter's constructors, in order to produce 1 TimeOfDay object,
   3 ModN_Counter objects (h,m,s) must be produced and initialized		*/
{
}

TimeOfDay::TimeOfDay(TimeOfDay &copy)			//copy constructor
: hour(24, copy.getH()), minute(60, copy.getM()), second(60, copy.getS())
//a new TimeOfDay variable is initialized with given TimeOfDay object copy's values
{
}

TimeOfDay::incS()
{
	if(second++) 	//if second == 59 then second = 0 (returns true) and minute is incremented by 1
		incM();
}

TimeOfDay::incM()
{
	if(minute++) 	//if minute == 59 then minute = 0 (returns true) and hour is incremented by 1
		incH();
}

TimeOfDay::incH()
{				
	hour++;		//if hour is 23 then hour is set to 0
}

TimeOfDay::getS()
{
	return second.getValue();
}

TimeOfDay::getM()
{
	return minute.getValue();
}

TimeOfDay::getH()
{
	return hour.getValue();
}

bool TimeOfDay::operator>(TimeOfDay &right)
{
	if (hour.getValue() > right.getH())
		return true;				//h1 > h2

	if (hour.getValue() == right.getH()) {
		if (minute.getValue()  > right.getM())
			return true;			//h1 = h2, m1 > m2
	}

	if (minute.getValue() == right.getM()) {
		if (second.getValue() > right.getS())
			return true;			//h1 = h2, m1 = m2, s1 > s2
	}

	return false;
}

void TimeOfDay::operator=(const TimeOfDay &right)
{
	second = right.second;
	minute = right.minute;
	hour = right.hour;
}


/*************MAIN FUNCTION*********************/
int main()
{
	TimeOfDay time1(7, 45, 3);
	TimeOfDay time2, time4;
	TimeOfDay time3 = time1;

	time2.incS();
	time2.incM();
	time2.incH();

	time4 = time2;

	if (time3 > time2)
		cout<<"time3 is greater (later) than time2"<<endl;
	else
		cout<<"time3 is smaller (earlier) than time2"<<endl;

	cout<<"Time 3= Hour: "<<time3.getH()<<" Minute: "<<time3.getM()<<endl;

	return 0;
}
