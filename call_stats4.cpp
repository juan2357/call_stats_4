/************************************************************************************************************************

Name: Juan Perez   Z#:23026404
Course: COP 3014
Professor: Dr. Lofton Bullard
Due Date: 3/2/18     Due Time: 11:59
Total Points: 20
Assignment 6: call_stats4.cpp

Description:
1. Read the contents of a datafile one record at a time into an array of
   records;
2. Process the data stored in an array of records;
3. Print the records stored in an array to a datafile using an ofstream
   (output file stream) object;
4. Use an array of record records;
6. Use an ifstream object;
7. Use an ofstream object;
*************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE = 200; //the capacity of the array which is the total amount
                      //of memory allocated to the array.  The is a static
                      //array, therefore the compiler will manage its memory,
                      //allocate and de-allocate the memory.


//sample record (class with no functionality)
class call_record
{
public:
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


//function prototype -- allows compiler to setup for function calls
void Input(call_record call_DB[ ], int & count);
void Output(const call_record call_DB[ ],const int & count);
void Process(call_record call_DB[ ], const int & count);

///*************************************************************************************
//Name:  Input
//Precondition: The varialbes cell_num, relays, and call_length have not been initialized
//Postcondition: The variables have been initialized by data file.
//Description: Get input values from txt file.
//*************************************************************************************

void Input(call_record call_DB[], int & count)
{
	ifstream in; //input file stream object declaration
	count = 0;  //remember to initialize count before the first come

	in.open("call_data.txt"); //bind the file "call_data.txt" to the input
	                          //file stream "in".
	if (in.fail()) //if file not found print message and exit program
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}
	//Remember to use a while loop when reading from a file because
	//you do not know how many records you will be reading.
	while (!in.eof())
	{
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;
		count++;
	}
	in.close();
}
///*************************************************************************************
//Name:  Output
//Precondition: The variables have been initialized and calculated
//Postcondition: Results are displayed.
//Description: Prints results from user input and calculations to a file
//*************************************************************************************
void Output(const call_record call_DB[], const int & count)
{
	ofstream out; //declare the output file stream "out".

	out.open("weekly4_call_info.txt");//bind the file "weekly4_call_info.txt" to
	                       //to the output file stream "out".
	//Magic Formula
	out.setf(ios::showpoint);
 	out.precision(2);
 	out.setf(ios::fixed);

	if (out.fail()) // if problem opening file, print message and exit program
	{
		cout << "Output file did not open correctly" << endl;
		exit(1);
	}
  // use a "for" loop here to
	// print the output to file
	for (int i = 0; i < count; i++) {
		out<< std::left << setw(30)<< "Cell Phone " <<call_DB[i].cell_number<<"  "<<endl;
		out<< std::left << setw(30)<< "Number of Relay Stations " <<call_DB[i].relays<<"   "<<endl;
		out<< std::left << setw(30)<< "Minutes Used " <<call_DB[i].call_length<<endl;
	  out<< std::left << setw(30)<< "Net Cost " <<call_DB[i].net_cost<<endl;
	  out<< std::left << setw(30)<< "Tax Rate " <<call_DB[i].tax_rate<<endl;
	  out<< std::left << setw(30)<< "Call Tax " <<call_DB[i].call_tax<<endl;
	  out<< std::left << setw(30)<< "Total Cost of Call " <<call_DB[i].total_cost<<endl<<endl;
	}
	out.close();
}

///*************************************************************************************
//Name:  Process
//Precondition: The variables have been initialized by the data file.
//Postcondition: Conditional statements initialize relay variables.
//Description: Calculates net_cost, call_tax and total_cost.
//*************************************************************************************

void Process(call_record call_DB[], const int & count)
{
	//Remember to use a "for" loop when you know how many items
	//you will be processing.  Use the dot operator when you are
	//accessing fields in a record.  For example, when we need
	//to access the relay field in the first record in the array use
	//call_DB[0].relay
	for (int i = 0; i < count; i++)
	{
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;
		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;
	  call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
		//Conditional statements to determine tax rates
		if (call_DB[i].relays <= 0 && call_DB[i].relays <=5) {
	    call_DB[i].tax_rate = 0.01;
	  } else if (call_DB[i].relays <= 6 && call_DB[i].relays <=11) {
	    call_DB[i].tax_rate = 0.03;
	  } else if (call_DB[i].relays <= 12 && call_DB[i].relays <=20) {
	    call_DB[i].tax_rate = 0.05;
	  } else if (call_DB[i].relays <= 21 && call_DB[i].relays <=50) {
	    call_DB[i].tax_rate = 0.08;
	  } else {
	    call_DB[i].tax_rate = 0.12;
	  }
	}
}

int main()
{

	call_record call_DB[SIZE];
	int count = 0;

	Input(call_DB, count); //this function will read all the input stored in a file
	                       //into the array call_DB
	Process(call_DB, count); //this function will process each call_record stored
	                       //in the array call_DB.
	Output(call_DB, count);//this function prints all the fields
	                       //of every record stored in the array call_DB to an output file.
	                       //Each record with be print on a separate line in the output file.
	return 0;
}
