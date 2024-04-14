#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm> //used by transform - to lower case
#include <exception>

using namespace std;

string list_of_initialStates[5] = { "120483765","208135467","704851632","536407182","638541720" };
string goalState = { "123456780" };

int main( int argc, char* argv[] ){
    string path;
    cout << "Solving Board: " << list_of_initialStates[0] << endl;

    return 0;
}
