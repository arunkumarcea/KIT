#include <stdlib.h>
#include <stdio.h>
#include <time.h>		// Timer
#include <sys/time.h>	// Timer

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>

#include "MISR.h"
using namespace std;


bool is_special_char3 (char c);
bool read_line_as_tokens3 (string line, vector<string>& tokens);
int PPI_PO_size(string);





 string input_file;


 int main(int argc, char *argv[])
 {

	for (int i=1 ; i<argc  ; i++ ){
			if ( strcmp(argv[i],"-file") == 0 || strcmp(argv[i],"-f") == 0 )
			{
				input_file = string(argv[++i]);
			}
			else{
			cout<<"Error: Unknown Argument : "<<argv[i];
			cin.get();
			exit(0);}
		}
	cout<<input_file<<endl;


	std::string inputs_str = "";


int MISRsize;
int montr_ff;
montr_ff = PPI_PO_size(input_file);
//#$%
  return 0;
}




 bool is_special_char3 (char c) {

  static const char specialChars[] = {'(', ')', ',', ':', ';', '/', '#', '{', '}', '*', '\"', '\\', '+' , '_' , ' ', '\n'} ;

  for (int i=0; i < sizeof(specialChars); ++i) {
    if (c == specialChars[i])
      return true ;
  }

  return false ;
}

// Read the next line and return it as a list of tokens skipping white space and special characters
// The return value indicates success/failure.
 bool read_line_as_tokens3 (string line, vector<string>& tokens) {

  tokens.clear() ;



 // string line ;
 // std::getline (is, line) ;

  while (tokens.empty()) {

    string token = "" ;

    for (int i=0; i < line.size(); ++i) {

      char currChar = line[i] ;


      if (std::isspace (currChar) || is_special_char3(currChar)) {

        if (!token.empty()) {
          // Add the current token to the list of tokens
          tokens.push_back(token) ;
          token.clear() ;
        }
        // else if the token is empty, simply skip the whitespace or special char

      } else {
        // Add the char to the current token
        token.push_back(currChar) ;

      }

    }

    if (!token.empty())
      tokens.push_back(token) ;


    //if (tokens.empty())
      // Previous line read was empty. Read the next one.
      //std::getline (is, line) ;
  }

  //for (int i=0; i < tokens.size(); ++i)
  //  cout << tokens[i] << " " ;
  //cout << endl ;

  return !tokens.empty() ;
}

//######################################FIND THE MONITOR_FF SIZE (PPI+PO
int PPI_PO_size(string input_file)
{
int local_montr_ff;
//			stringstream ss;//create a stringstream
//			ss << '0';//add number to the stream

				int data_array[1010][1000];
				int sp_array[1000];
	ofstream sppo_file;
	sppo_file.open("sppo.txt");



	 for (int iteration=0;iteration<2000;	iteration++)
	 {
	   cout<<"iteration: "<<iteration<<endl;
			stringstream ss;//create a stringstream

			ss << iteration;//add number to the stream






			//input patterns file (input)
			string dump_name=ss.str();
			dump_name="input/"+input_file+"/"+input_file+"_PPI_"+dump_name;
			string myfile1=dump_name;
			ifstream file1 (myfile1.c_str());


			//input patterns file (input)
			string dump_name2=ss.str();
			dump_name2="input/"+input_file+"/"+input_file+"_PO_"+dump_name2;
			string myfile2=dump_name2;
			ifstream file2 (myfile2.c_str());




			//cout<<myfile1<<endl;




//			//input patterns file (input)
//			string dump_name=ss.str();
//			dump_name="input/"+input_file+"/"+input_file+"_PPI_"+dump_name;
//			string myfile1=dump_name;
//			ifstream file1 (myfile1.c_str());
//
//
//			//input patterns file (input)
//			string dump_name2=ss.str();
//			dump_name2="input/"+input_file+"/"+input_file+"_PO_"+dump_name2;
//			string myfile2=dump_name2;
//			ifstream file2 (myfile2.c_str());
//



			//cout<<myfile1<<endl;

			string line="";

			for (int i=0;i<1000;i++)
			{
			vector<string> tokens;

				tokens.clear() ;
				getline( file1 , line , '\n');
				bool valid = read_line_as_tokens3 (line, tokens);


				//cout<<tokens.size()<<endl;

				ss.str("");
				ss.clear();
				for(int m=0; m < tokens.size(); m++)
				ss << tokens[m];

				tokens.clear() ;
				getline( file2 , line , '\n');
				valid = read_line_as_tokens3 (line, tokens);

				//cout<<tokens.size()<<endl;

				for(int m=0; m < tokens.size(); m++)
				ss << tokens[m];

				std::string total_inputs_str;
				int wrapno;

				total_inputs_str = ss.str();

				for(unsigned int z = 0; z<total_inputs_str.length(); z++) {
  				  char c = total_inputs_str[z]; //this is your character
    					int sank= c - '0';
					cout << sank << "\t" << c << endl;
				data_array[i][z]=sank;
//				cout << "i is " << i << " z is " << z << "data_array  is " << data_array[i][z] << endl;
					}


				cout << total_inputs_str <<endl;
				local_montr_ff = total_inputs_str.size();


				}//loop for 1000
				//write the sp value to spp file for each coloumn of a file


				float sp_value=0;
				float total_value=0;
				for(int l=0;l<local_montr_ff;l++)
				{
				sp_value=0;
				total_value=0;
					for(int k=0;k<1000;k++)
					{
					total_value=total_value+data_array[k][l];
					if (data_array[k][l]==0 || data_array[k][l]==1)
					{}
					else
					{cout <<" report error " << data_array[k][l] <<" "<< k <<" " << l <<endl;}
//					cout << "total value is " << total_value <<endl;
//				cout << "k is " << k << " l is " << l << "data_array  is " << data_array[k][l] << "monitor_ff is "<< montr_ff << "total_value " << total_value<< endl;
						if (total_value>1000)
						{
				cout << "k is " << k << " l is " << l << "data_array  is " << data_array[k][l] << "monitor_ff is "<< local_montr_ff << "total_value " << total_value<< "sp_value is " << sp_value <<endl;}
					}
					sp_value=total_value/1000;
					//cout << "sp_value is " << sp_value << endl;

					sppo_file << sp_value << "\t";
				}
				sppo_file << endl;
//				return montr_ff;
			}// for the loop 2000
sppo_file.close();
}

//######################################FIND THE MONITOR_FF SIZE (PPI+PO

