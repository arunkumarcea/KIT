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

//#define SPACE_SAMPLE_PERCENT 50

#define REQ_CYCLES 10

bool is_special_char3 (char c);
bool read_line_as_tokens3 (string line, vector<string>& tokens);
int PPI_PO_size(string);



 vector<int> space_sample;
 string input_file;
 string rff_filename;


 int main(int argc, char *argv[])
 {

srand((unsigned)time(NULL));

	for (int i=1 ; i<argc  ; i++ ){
			if ( strcmp(argv[i],"-file") == 0 || strcmp(argv[i],"-f") == 0 )
			{
				input_file = string(argv[++i]);
			}
			else if  ( strcmp(argv[i],"-rff") == 0 )
			{
				rff_filename =string(argv[++i]);
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
cout << "value of montr_ff " <<montr_ff <<endl;//#$%#$%
	if (montr_ff <= 32)
	{
		MISRsize=montr_ff;


	}
	else if (montr_ff>32 && montr_ff<64)
	{
		MISRsize=32;
	}
	else
	{
		MISRsize=64;
	}
	MISR TAPS(MISRsize);


 cout << montr_ff << "is montr_ff" <<endl;

	//output of MISR
	ofstream CG_file;
	string gate_dump="output_RFF/" + rff_filename + ".dat";
	CG_file.open(gate_dump.c_str() );

	//CG_file<<"chi"<<endl;
	//cout<<gate_dump<<endl;

	std::stringstream ss;
	std::stringstream ss_selected;
	 int iteration=0;



	 for (iteration=0;iteration<1;	iteration++)
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


//################################################################################
            vector<int> shuff_itr(1000);
            vector<int> rand_itr(REQ_CYCLES);
            for(int i=0;i<1000;i++)
            shuff_itr[i]=i;

            std::random_shuffle ( shuff_itr.begin(), shuff_itr.end() );
            for (int i=0;i<REQ_CYCLES;i++)
            {
            rand_itr[i]=shuff_itr[i];
            //cout << i <<"th element of rand_itr is "<< rand_itr[i] <<endl;
            }
             std::sort(rand_itr.begin(), rand_itr.end());
             int h=0;

//##############################################################################################################




			//cout<<myfile1<<endl;

			string line="";


			vector<string> tokens;

			for (int i=0;i<1000;i++)  //1000 inputs in each file
			{
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


//				####################
			    if(i!=rand_itr[h])
			    {
			        continue;
			    }
			    h++;
//				####################

				std::string total_inputs_str;
				int wrapno;

				total_inputs_str = ss.str();
				int input_size = total_inputs_str.size();

				//space sampling jan18

						ss_selected.str("");
				ss_selected.clear();
  //            cout << total_inputs_str << " initial samples " << " input size  " << input_size <<endl;

                cout <<endl;

             //   for (int kk=0;kk<input_size;kk++)
	     //   		{
             //       cout << space_sample[kk] ;
	     //   		}
	     //   		cout << "the random index" <<endl;
             //    cout <<endl;

				for (int kk=0;kk<input_size;kk++)
				{
				    if(space_sample[kk]==1)
				    {
				      //  cout << total_inputs_str[kk] << "  this is a sample " << kk <<endl;
				       ss_selected << total_inputs_str[kk] ;
				    }

				}
                total_inputs_str=ss_selected.str();
                input_size=total_inputs_str.size();
               //cout << total_inputs_str << " selected samples " <<endl;
                ss_selected.str("");
				ss_selected.clear();
//				std::string space_sample="111100000000000000000000000001111";
  //            cout << total_inputs_str << " initial samples " << " input size  " << input_size <<endl;
//
//
//				for (int i=0;i<input_size;i++)
//				{
//				    if(space_sample[i]=='1')
//				    {
//				        cout << total_inputs_str[i] << "  this is a sample " <<endl;
//				       ss_selected << total_inputs_str[i] ;
//				    }
//
//				}
//                total_inputs_str=ss_selected.str();
//                cout << total_inputs_str << " selected samples " <<endl;
//                ss_selected.str("");
//				ss_selected.clear();
				//input_size = total_inputs_str.size();
				//space samplingjan18 2015

				int quotnt = total_inputs_str.size() / MISRsize;//need to modify if remainder /= 0
				int overflow;
				overflow = total_inputs_str.size() % MISRsize;
				int extnd_input_size = input_size +overflow;

						if (overflow != 0)
						{
							total_inputs_str.resize (input_size+MISRsize-overflow,'0');
						}

				wrapno = total_inputs_str.size() / MISRsize;

				for (int l=0;l<wrapno;l++){
					for (int k=0;k<MISRsize;k++){
					stringstream bb;
					string s;
					char c = total_inputs_str[ l*MISRsize + k ];
					bb << c;
					bb >> s;
					inputs_str.append(s);
					}

				TAPS.shift(inputs_str);
				inputs_str= "";

			    }


			}

			//TAPS.Reset();
			// PRINT THE OUTPUT INTO FILE MISRfile.txt
			CG_file << TAPS << "\n";

		}  //end iteration


		CG_file.close();

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
			stringstream ss;//create a stringstream
			stringstream ss_selected;
			ss << '0';//add number to the stream






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

			string line="";


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
                 int input_size=total_inputs_str.size();

                //space sampling jan18
                vector<int> RFF_index;
                int no_of_RFFs=0;
		ifstream RFF_file;
		string rff_fil= rff_filename;
		RFF_file.open(rff_fil.c_str() );
                std::string RFF_line;
                int RFF_int=0;
                while (std::getline(RFF_file, RFF_line))
                {
                     //RFF_int=RFF_line;
                    RFF_int=std::atoi(RFF_line.c_str());
                    RFF_index.push_back(RFF_int);
                }

                //take the indexes
                //push them to a vector
                //sort them
                no_of_RFFs = RFF_index.size();
                for (int rr=0; rr<input_size;rr++)
                {
                  space_sample.push_back(0);
                }
                std::sort (RFF_index.begin(), RFF_index.end());
                 for (std::vector<int>::iterator it_RFF_index = RFF_index.begin() ; it_RFF_index != RFF_index.end(); ++it_RFF_index)
                 {
                        space_sample[*(it_RFF_index)-1] = 1;
                        cout << *(it_RFF_index)-1 << " this is the index of RFFs" << endl;
                 }
                RFF_file.close();


				//std::string space_sample="111100000000000000000000000001111";

				//input_size = total_inputs_str.size();
				//space samplingjan18 2015



				int montr_ff = no_of_RFFs;
				return montr_ff;
}

//######################################FIND THE MONITOR_FF SIZE (PPI+PO

