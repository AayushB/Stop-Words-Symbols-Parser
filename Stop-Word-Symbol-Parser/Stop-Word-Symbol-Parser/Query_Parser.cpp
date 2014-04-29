//
//  main.cpp
//  Stop-Word-Symbol-Parser
//
//  Created by Aayush Bhandari on 4/28/14.
//  Copyright (c) 2014 Aayush Bhandari. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/*-----------------------------------------------------------------------------------
                                Function Declarations
 -----------------------------------------------------------------------------------*/
bool isASymbol(char value);
void tokenize(vector<string>& tokenizedQuery, string rawQuery);
void removeStopWords(vector<string>& tokenizedQuery, string filename);
void removeCase(string &rawQuery);

/*-----------------------------------------------------------------------------------
                                    Main Program
 -----------------------------------------------------------------------------------*/


int main(int argc, const char * argv[])
{
    if (argc < 3) { // We expect 3 arguments: the program name, the query and the stop file name
        std::cerr << "Usage: " << argv[0] << "QUERY STOPWORDSFILE" << std::endl;
        return 1;
    }
    
    
    
    string rawQuery = argv[1];
    string stopWordFileName= argv[2];
    
    ///This is where I have the file saved.
    //Users/Aayush/Desktop/GitHubFolders/Stop-Words-Symbols-Parser/Stop-Word-Symbol-Parser/Stop-Word-Symbol-Parser/stoplist.dft"
    
    removeCase(rawQuery);//The query is made case insensitive
    rawQuery.erase(remove_if(rawQuery.begin(), rawQuery.end(), isASymbol), rawQuery.end());
        vector<string> tokenizedQuery;// all the symbols are removed
    tokenize(tokenizedQuery, rawQuery);// query is tokenized
    removeStopWords(tokenizedQuery, stopWordFileName);// all the stop words are removed
    
    //print the final parsed query
    for(int i=0; i<tokenizedQuery.size(); i++)
    {
        if(tokenizedQuery.at(i)!="")
            cout << tokenizedQuery.at(i) << " ";
    }
    return 0;
}



bool isASymbol(char value)
{
    /*
     * Precondition:
     * None
     *
	 * Purpose:
	 * The function accepts a char and evaluates if its one of the 26 english alphabets, single quote, numbers
     * or a space.
	 *
	 * Postcondition:
     * A true value is returned for english alphabets, single quote or spaces. A false is returned otherwise.
	 *
	 */
    
    int x= value;
    if((x>=65 && x <=90)|| (x >=97 && x<=122) || (x>=48 && x<=57) || x==32 || x==39 || x==45)
        // using the ASCII value for comparison for english alphabets, numbers apotrophe and space, hyphens
    {
        return false;
    }
    return true;
}



void tokenize(vector<string>& tokenizedQuery, string rawQuery)
{
    
    /*
     * Precondition:
     * The rawQuery is expected to have all the symbols removed at this point.
	 * Purpose:
     * The function accepts a vector tokenizedQuery as a reference and pushes back individual word from the
     * recieved rawQuery into the vector.
	 *
	 * Postcondition:
     * Since the vector is recieved as a reference the  vector will change directly in the main
     * program.
	 */
    
    string* temp= new string;
    for (int i=0; i<rawQuery.length(); i++)
    {
        if (rawQuery.at(i)!=' ')
        {
            *temp+=rawQuery.at(i);
        }
        else if(*temp!="")
        {
            tokenizedQuery.push_back(*temp);
            temp= new string;
        }
    }
    if (*temp!="") // pushing the last element into the vector
        tokenizedQuery.push_back(*temp);
}




void removeStopWords(vector<string>& tokenizedQuery, string filename)
{
    /*
     * Precondition:
     * Filename should be present and contain the stop words.
     *
	 * Purpose:
	 * The function accepts a filename and a vector and removes all instances of the stop words
     * occuring in the filename from the vector
	 *
	 * Postcondition:
     * The tokenizedQuery is left changed in the main program.
	 *
	 */

    fstream file;
    file.open(filename, ios::in);//open file in input mode
    if (file.fail())
    {
        cout << "file could not be opened";
    }
    
    string str;
    while(file >> str) //extract each stop word from the file into str
    {
        for(int i=0; i<tokenizedQuery.size(); i++)
        {
            if(str==tokenizedQuery.at(i)) //if string is in vector, replace with ""
            {
                tokenizedQuery.at(i)="";
            }
        }
    }
}


void removeCase(string &rawQuery)
{
    
    /*
     * Precondition:
     * None
     *
	 * Purpose:
	 * The function accepts a raw query as reference and changes each character in the string
     * into a lowered case version.
	 *
	 * Postcondition:
     * The rawQuery is changed in the main program and turned into all lowered case.
	 *
	 */
    for (int i=0; i<rawQuery.length(); i++)
    {
        string temp(1,tolower(rawQuery.at(i))); // converting char into lowerd case string
        rawQuery.replace(i,1,temp);
    }
}



