#include <iostream>
#include <vector>
#include <string>

using namespace std;

//All charecters to be compressed are stored in individually in this vector
vector<unsigned char> DNAVector;
//All integers to be decompressed are stored individually in this vector
vector<int> encodedVector;
//The position of which to read charecters from within the vector when compressing
unsigned int position = 0;

/*
  Function: Adds encoded charecters to vector of compressed data
  based on its binary configuration.
  Inputs: The DNA substring to evaluate.
 */
void addToVector(string DNA);

/*
  Function: The emcompassing funtion that completes the whole compression
  proccess. Uses bit wise operators to encode inputted charecters.
  Inputs: The string of DNA to compress.
 */
void compressDNA(string cmdLnArg);

/*
  Function: Encompasses the process of decompressing. This function calls the intToString() and
  intToBin() functions to do so. This function reverse engineers the process of compressing to
  determine what string corelates to encoded cmd ln args.
  Inputs: The length of DNA charecters to determine remainder, the list of integers to decompress.
 */
void decompress(int length, vector<int> cmdLnArgs);

/*
  Function: Converts an integer to a string by breaking down its binary composition.
  Inputs: the number to convert
  Outputs: its coorelating string
 */
string intToString(int num);

/*
  Function: Breaks down the binary composition of a number so that it can be converted to a string.
  Inputs: the number to convert.
  Outputs: The numbers binary composition.
 */
vector<int> intToBin(int input);

/*
  An algorithm for compressing an decompressing DNA string based on a binary encoding.
 */
int main(int argc, char*argv[]) {

    string option = argv[1];

    if (option == "-c") {
        compressDNA(argv[2]);
    } else {
        for (int i = 3 ; i < argc ; i++) {
            encodedVector.push_back(stoi(argv[i]));
        }
        decompress(stoi(argv[2]), encodedVector);
    }
}

void decompress(int length, vector<int> list) {

    string DNAString;
    int remainder = (list.size() * 4) - length;
    for (unsigned int i = 0 ; i < list.size() ; i++) {
        DNAString += intToString(list[i]);
    }
    cout << DNAString.substr(0,DNAString.length() - remainder) << endl;
}

string intToString(int num) {
    string output;
    vector<int> temp = intToBin(num);

    for (unsigned int i = 0 ; i < temp.size() ; i = i + 2) {
        int valueA = temp[i];
        int valueB = temp[i + 1];
        if (valueA == 0 && valueB == 0) {
            output += "A";
        } else if (valueA == 0 && valueB == 1) {
            output += "T";
        } else if (valueA == 1 && valueB == 0) {
            output += "C";
        } else {
            output += "G";
        }
    }
    return output;
}


vector<int> intToBin(int input) {
    int quotient = input;
    int remainder = 0;
    vector<int> output;
    while(quotient > 0){
        remainder = quotient % 2;
        quotient = quotient / 2;
        //insert at beggining to invert order
        output.insert(output.begin(),remainder);
    }

    while (8 - output.size() > 0) {
        output.insert(output.begin(),0);
    }
    if(input == 0){
        output.push_back(0);
    }
    return output;
}


void compressDNA(string cmdLnArg) {

    string fullDNA = cmdLnArg;
    unsigned int DNALength = fullDNA.length();
    unsigned int remainder = DNALength % 4;

    //add charecters for divisibles of 4
    for (unsigned int i = 0 ; i < (DNALength - remainder) / 4; i++) {
        addToVector(fullDNA.substr(position, position + 4));
    }
    //add remaining charecters
    if (remainder != 0) {
        string remainingDNA = fullDNA.substr(position, DNALength);
        for (unsigned int i = 0 ; i < 4 - remainder ; i++) {
            remainingDNA += "A";
        }
        addToVector(remainingDNA);
    }
    //print vector
    cout << DNALength << " ";
    for (unsigned int i = 0 ; i < DNAVector.size() ; i ++) {
        cout << (int) DNAVector[i] << " ";
    }
    cout << endl;
}

void addToVector(string DNA) {
    unsigned char d = 0;
    for (unsigned int i = 0; i < 4; i++) {
        d = d << 2;
        if (DNA.at(i) == 'A') {
            d += 0;
        } else if (DNA.at(i) == 'T') {
            d+= 1;
        } else if (DNA.at(i)== 'C') {
            d += 2;
        } else if (DNA.at(i) == 'G') {
            d += 3;
        }
        position++;
    }
    DNAVector.push_back(d);
}
