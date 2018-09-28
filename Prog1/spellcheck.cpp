#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
using namespace std;

void throwError(string message, string file, int type)
{
    if (type == 1)
    {
        cerr << "ERROR: " << message << ": " << file << ". " << strerror(errno) << endl;
    }
    else
    {
        cerr << "ERROR: " << message << strerror(errno) << endl;
    }
    exit(-1);
}

int main()
{
    string infile, outfile, dictfile, line, word;
    bool ignore;
    char c;
    int i;
    unsigned long lineNo = 0;
    clock_t start, end;
    ifstream input;
    ofstream output;

    hashTable *dictionaryHash = new hashTable(50000);
    cout << "Enter the name of dictionary: ";
    cin >> dictfile;

    start = clock();
    // // Open the file, read the file to count its bytes
    // ifstream file(dictfile.c_str(), ios::binary | ios::ate);
    // // Aprroximate word count based on the amount of bytes in the file
    // int wordCount = (file.tellg() / 5) * 2;
    // //Close file
    // file.close();
    // cout << wordCount << endl;
    // implement loading to hash table here
    ifstream dictionary;
    dictionary.open(dictfile);
    if (dictionary.fail())
        throwError("Failed to open the dictrionary file", dictfile, 1);

    while (getline(dictionary, line))
    {
        for (i = 0; i <= line.length(); i++)
        {
            line[i] = tolower(line[i]);
        }
        dictionaryHash->insert(line, NULL);
    }
    dictionary.close();

    end = clock();
    cout << "Total time (in seconds) to load dictionary: " << ((double)(end - start)) / CLOCKS_PER_SEC << endl;

    cout << "Enter the name of input file: ";
    cin >> infile;

    cout << "Enter the name of output file: ";
    cin >> outfile;
    start = clock();
    input.open(infile);
    if (input.fail())
        throwError("Failed to open the input file", infile, 1);

    output.open(outfile);
    if (output.fail())
        throwError("Failed to open the output file", outfile, 1);

    while (getline(input, line))
    {
        lineNo++;
        for (i = 0; i <= line.length(); i++)
        {
            c = tolower(line[i]);
            int asciic = c;
            if (isalnum(c) || (asciic == 39) || (asciic == 45))
            {
                word += c;
                if (isdigit(c))
                    ignore = true;
            }
            else if ((ignore == false) && (word.length() > 0))
            {
                if (word.length() > 20)
                {
                    output << "Long word at line " << lineNo << ", starts: " << word.substr(0, 20) << endl;
                }
                else if (!dictionaryHash->contains(word))
                {
                    output << "Unknown word at line " << lineNo << ": " << word << endl;
                }
                word = "";
            }
            else
            {
                word = "";
                ignore = false;
            }
        }
    }

    input.close();
    output.close();
    end = clock();

    cout << "Total time (in seconds) to check document: " << ((double)(end - start)) / CLOCKS_PER_SEC << endl;

    return 0;
}