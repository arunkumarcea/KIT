# ifndef MISR_H
# define MISR_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <cassert>
#include <math.h> 
#include "maxtap.h"



class MISR{

	public:
		
		/**************************************************
		/*	Constructor MISR:						*
		/*	Input: Initial value of register			*
		/*	Taps: Mask, to XOR operate or not			*	
		***************************************************/
		MISR(int n);
		
		
		/**************************************************
		/*	Constructor MISR with maximal TAP:			*
		/*	Input: Initial value of register			*
		***************************************************/
		//This corresponds to constructor overloading. The constructor is called corresponding to the data types passed.
		//If a string is passed then the below function(or constructor) is called.
		MISR(const std::string input);

		
		/**************************************************
		/*	Constructor MISR with maximal TAP:			*
		/*	file: name of file to find the connetion	*
		/*	values: vector all inputs					*
		***************************************************/
		MISR( const std::vector<unsigned>& inputs,  const std::string& values);


		/**************************************************
		/*	Get_MISR:	This function return the actual 	*
		/* 		of register(binary).				*
		/*   !!!ATENTTION: the value is inverted.¡¡¡¡	*
		/*	Output: Return a String with the register 	*
		/* 		value in binary					*
		***************************************************/
		const std::string get_MISR()const;


		/**************************************************
		/*	Get_Value_MISR:  This function return	 	*
		/* 		 the actual of register(decimal).		*
		/*	Output: Return a String with the register 	*
		/* 		value in decimal					*
		***************************************************/
		const long int get_value_MISR()const;

		/**************************************************
		/*	Size of MISR:	Return size of register		*
		***************************************************/
		const int size(){return MyRegister.size();}

		
		/**************************************************
		/*	String to Vector Bool: Create a Vector with	  * 
		/*		String                                    *
		***************************************************/
		std::vector<bool> String_to_VecBool(const std::string &input) const;
		
		
		/**************************************************
		/*	Iteration of MISR:	Make ONE shift the value	*
		/*		of register						*	
		/*	inputs: The inputs value in String variable	* 
		/*	Output: The last value of register, before	* 
		/*		the iteration.				 		*	
		***************************************************/
		std::string Iteration(const std::string &inputs);		

		std::string shift(const std::string &inputs);


		/**************************************************
		/*	Reset MISR:	Put "0" in all bit of register	  *	
		***************************************************/
		void Reset();	

		
		/**************************************************
		/*	Iterations of MISR:	Make more of ONE 		*
		/*		shift the value of register.			*	
		/*	Inputs: All of inputs of each iteration	* 
		/*	Output: All last values of each itetation	* 
		/*		, before each iteration.				*	
		***************************************************/
		std::vector<std::string> Iterations(const std::vector<std::string> &inputs);	
	

		/**************************************************
		/*	Destructor MISR:						*	
		***************************************************/
		~MISR();


		/**************************************************
		/*	Print MISR: You can print MISR with the 	*
		/*		function "cout"					*
		***************************************************/
		friend std::ostream& operator << (std::ostream& os, const MISR& ar);
	
		
		/**************************************************
		/*	Print n iterations MISR: You can print  	*
		/*		N iterations						*
		***************************************************/
		void print_n_Iterations(const std::vector<std::string> &inputs);
		
		
		
		/**************************************************
		/*	Print n iterations with randon input MISR: 	  *
		***************************************************/
		std::vector<std::string> n_random_Iterations(int n);
		
		/**************************************************
		/*	Print n iterations with randon input MISR: 	  *
		***************************************************/
		void print_n_random_Iterations(int n);
		
		/**************************************************
		/*	Get a conections from file:					  *	
		/*	name: name of file							  * 
		***************************************************/
		static std::string Get_random(unsigned n);	
	
		
	
	private:
		
		std::vector<bool> MyRegister;
		std::vector<bool> MyTaps;
		std::string MyTapsSTR;
		int Rsize;
};

std::vector<bool> MISR::String_to_VecBool(const std::string &input)const{
	std::vector<bool> MyReg(input.size());
	for(int i=0; i<input.size(); i++){
		// We need correct inputs.
		assert(input[i] == '0' || input[i] == '1');
		if(input[i]=='1')
			MyReg[i] = true;
		else
			MyReg[i]= false;
	}
	return MyReg;	
}

std::string MISR::Get_random(unsigned n){
	std::stringstream ss;
	srand(time(0));
	for(int i=0; i<n; i++)
		ss << rand()%2;
	return ss.str();
	
}



MISR::MISR(const std::vector<unsigned>& inputs, const std::string& values){
	std::vector<unsigned> aux = std::vector<unsigned>(inputs);

	//I dont know if it is important to keep order of connections, 
		//now we don't keep order, but if it were necessary,
		//then, you have to uncomment the next instruction:
		
	//std::sort(aux.begin(),aux.end());
	std::string output="";
	for(int i=0; i<aux.size(); i++){
		assert(aux[i] >= 1 && aux[i] <= values.size());
		// I guess "+" works as a concatenation operator on the string 'output'
		output+= values[aux[i]];
	}	
	//Why is it in " "?
	assert(output.size() > 1 && "inputs: SIZE <= 1");
	assert(values.size() > 1 && "Values: SIZE <= 1");
	Rsize = output.size();
	MyRegister = String_to_VecBool(output);
	MyTapsSTR =  maxtap::get_inv_maxtap(output.size()-1);
	MyTaps =  String_to_VecBool(MyTapsSTR);
}

MISR::MISR(const std::string input){
	
	// The mask size and the register size have to be equal.
	assert(input.size() > 1);
	Rsize = input.size();
	MyRegister = String_to_VecBool(input);
	MyTapsSTR =  maxtap::get_inv_maxtap(Rsize);
	MyTaps =  String_to_VecBool(MyTapsSTR);
}

/* replacing this constructor. MISR should be initialized to seed 0
//#$% The register size is passed as the argument n 
MISR::MISR(int n)
{	
	// register size must be greater than 1
	assert(n > 1);
	// ss is an object of class stringstream (for easy conversion to other numerical forms)
	std::stringstream ss;
	Rsize = n;
	//seeding initial value for random number generator
	srand(time(0));
	// Register shouldnt be locked up at the value 000000000
	ss << '1'; // to get register != 0.
	
	//Filling ss with either 0 or 1 randomly until n-1 keeping the '1' added earlier
	for(int i=1; i<n; i++)
		ss << rand()%2;
	// Changing the string '01100.....' to false true true ' boolean vector
	MyRegister = String_to_VecBool(ss.str());
	// I guess its looking for a mirror sequence or tap sequence. Not sure
	MyTapsSTR =  maxtap::get_inv_maxtap(Rsize);
	//Again to boolean vector from string form.
	MyTaps =  String_to_VecBool(MyTapsSTR);
	
}*/

//#$% The register size is passed as the argument n 
MISR::MISR(int n)
{	
	// register size must be greater than 1
	assert(n > 1);
	// ss is an object of class stringstream (for easy conversion to other numerical forms)
	std::stringstream ss;
	Rsize = n;
	
	for(int i=0; i<n; i++)
		ss << '0';
	// Changing the string '01100.....' to false true true ' boolean vector
	MyRegister = String_to_VecBool(ss.str());
	// I guess its looking for a mirror sequence or tap sequence. Not sure
	MyTapsSTR =  maxtap::get_inv_maxtap(Rsize);
	//Again to boolean vector from string form.
	MyTaps =  String_to_VecBool(MyTapsSTR);
	
}


std::string MISR::Iteration(const std::string &inputs){
	//assert(inputs.size() == Rsize);	NOW WE DONT NEED THIS CONDITION
	bool value = true;
	std::vector<bool> Vinputs = String_to_VecBool(inputs);
	// aux(MyRegister) means aux is a copy of MyRegister.
	std::vector<bool> aux(MyRegister);
	
	value = Vinputs[0];
/*	//for debug
std::vector<bool>::iterator it;
for(it = Vinputs.begin(); it != Vinputs.end(); it++){
std::cout << *it;

//std::cout << std::endl;
}
std::cout << std::endl;
	//for debug*/
	
	if (MyTaps[0])
		value^=aux.back();
	MyRegister[0]= value;
	
	for(int i=1; i<Rsize; i++){
		value = aux[i-1]^Vinputs[i];
		if (MyTaps[i])
			value^=aux.back();
		MyRegister[i]= value;
	}
	


	return get_MISR();
}	


std::string MISR::shift(const std::string &inputs){
	return Iteration(inputs);
}	


void MISR::Reset(){
	MyRegister = std::vector<bool>(Rsize,false);
}


std::vector<std::string> MISR::Iterations(const std::vector<std::string> &inputs){
	std::vector<std::string> output;
	for(int i=0; i<inputs.size(); i++)
		output.push_back(Iteration(inputs[i]));
	return output;
}


const std::string MISR::get_MISR()const{
	std::stringstream ss;
	for(int i=0; i<MyRegister.size(); i++){
		ss << (MyRegister[i]==true)?'1':'0';
		ss<<"\t";
	}
    	return ss.str();
}

const long int MISR::get_value_MISR()const{
	long int value=0;
	std::vector<bool> aux(MyRegister);
	while(!aux.empty()){
		value *= 2;		
		value += int(aux.front());
		aux.erase(aux.begin());
	}
	return value;
}

std::ostream& operator << (std::ostream &os,const MISR &ar){
	//os << ar.get_MISR() << " (" << ar.get_value_MISR() << ")";
os << ar.get_MISR() << " " << ar.get_value_MISR() << "";
    return os;
}


void MISR::print_n_Iterations(const std::vector<std::string> &inputs){
	for(int i=0; i<inputs.size(); i++){
		std::cout << "---- Iteration " << i << ":----" << "\n Input = \t" << inputs[i] << "\n Initial value =\t"<< *this << "\n TAP = \t" << MyTapsSTR <<"\n";
		Iteration(inputs[i]);
		std::cout << " Final Value = \t" << *this << "\n";
	}
	std::cout << std::endl;
}


std::vector<std::string> MISR::n_random_Iterations(int n){
		
	std::vector<std::string> values;
	srand(time(0));
	
	for(int i=0; i<n; i++){
			std::stringstream ss;
			for(int j=0; j<Rsize; j++)
				ss << rand()%2;
			values.push_back(ss.str());
	}
	return Iterations(values);
}



void MISR::print_n_random_Iterations(int n){
	std::vector<std::string> values;
	
	srand(time(0));
	for(int i=0; i<n; i++){
			std::stringstream ss;
			for(int j=0; j<Rsize; j++)
				ss << rand()%2;
			values.push_back(ss.str());
	}
	print_n_Iterations(values);
	
}

inline MISR::~MISR(){}



# endif 
