
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

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
#include <omp.h>
#include <map>


using namespace std;

int FF_index[5000];// array that can hold 100 numbers for 1st column
int weight[5000];// array that can hold 100 numbers for 2nd column

#define number_of_flipflops 47
#define number_of_lines_in_file 22
#define threshold 1

int main() // int main NOT void main
{
  ifstream infile;
  ofstream outfile;

  outfile.open("binary_imp_select.dat");


  int num = 0; // num must start at 0
  infile.open("pinAssign.pin");// file containing numbers in 3 columns
     if(infile.fail()) // checks to see if file opended
    {
      cout << "error" << endl;
      return 1; // no point continuing if the file didn't open...
    }
       while(!infile.eof()) // reads file to end of *file*, not line
      {
         infile >> FF_index[num]; // read first column number
         infile >> weight[num]; // read second column number

         ++num; // go to the next number

         // you can also do it on the same line like this:
         // infile >> FF_index[num] >> weight[num] >> exam3[num]; ++num;
      }
  infile.close();
for(int i=0;i<number_of_lines_in_file;i++)
{
cout << "FF_index is " << FF_index[i] << "\t";
cout << "weight is " << weight[i] <<endl;
}

stringstream ss;
for(int i=0;i<number_of_flipflops;i++)
{
    ss << '0';

}
 cout << ss.str() << endl;
string binary = ss.str();


for(int i=0;i<number_of_lines_in_file;i++)
{
    if (weight[i] > threshold)
        {
            binary[FF_index[i]]='1';
        }
}
    cout << binary << endl;
    outfile << binary <<endl;
    outfile.close();
 //cout << ss.str() << endl;

  return 0; // everything went right.
}
