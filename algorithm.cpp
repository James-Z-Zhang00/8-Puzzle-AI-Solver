
#include "algorithm.h"
#include "board.h"
#include <list>
#include <unordered_map>
#include <cstdlib>


using namespace std;

/*

STARTBOARD: "120483765","208135467","704851632","536407182","638541720"
GOALBOARD: "123456780"




*/


// for simple list 
bool in_expanded_list(list<string> l, Board b) {
    for (string s : l) {
        if (s == b.getContent()) {return true;}
    }
    return false;
}

// For UC search
class PathsComparator {
public:
    bool operator() (Board a, Board b) {
        return a.getCost() >= b.getCost();
    }
};

// For misplaced tiles
class HeuMTComparator {
public:
    bool operator() (Board a, Board b) {
        return a.getHeuByMisplacedTiles() >= b.getHeuByMisplacedTiles();
    }
};

// For manhattan distance
class HeuMDComparator {
public:
    bool operator() (Board a, Board b) {
        return a.getManhattanDistance() >= b.getManhattanDistance();
    }
};


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string uc_explist(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<uc_explist>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	//srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	//maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	maxQLength = 0;
	//numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY
	numOfStateExpansions = 0;


	vector<Board> Q;
    unordered_map<int, string> Exp;
    unordered_map<string, string> boardRules;
    Board grabbedBoard;
	int oldLength = Exp.size();
	// for hash map 
	hash<string> hashFunc;
	
	Board board(initialState,goalState);
	
	boardRules["0"] = "13";
    boardRules["1"] = "042";
    boardRules["2"] = "15";
    boardRules["3"] = "046";
    boardRules["4"] = "1375";
    boardRules["5"] = "248";
    boardRules["6"] = "37";
    boardRules["7"] = "468";
    boardRules["8"] = "57";
	
	PathsComparator pc;
    Q.push_back(board);
	
	 // make heap

    make_heap(Q.begin(),Q.end(),pc);

    // start search from the first path
	bool keep_running = true;
    while(keep_running) {
        if (Q.empty()) {cout<<"Goal NOT Found"<<endl;break;}
        grabbedBoard = Q.front();
        pop_heap(Q.begin(),Q.end(),pc);
        Q.pop_back();
		
		if (grabbedBoard.checkGoal()) {
			keep_running = false;
			break;
		}
		
		oldLength = Exp.size();
		Exp[hashFunc(grabbedBoard.getContent())] = grabbedBoard.getContent();
		// Try to add the grabbed board (puzzle) into hash table
		// if the previous and the current length is the same
		// that means failed to add, there is a same board existed
		// in hash table already.
		// If the lengths are different, means new board added successfully
		// we did not expand this board before
		// so do the algorithm
		if (oldLength == Exp.size()) {continue;}
		else {
			// Update number of state expansion
			numOfStateExpansions++;
			
            string blankPosition = to_string(grabbedBoard.getContent().find("0"));
            /* Iterate the string */
            string newPositions = boardRules[blankPosition];
            string newPosition;
            for (int i = 0; i < newPositions.length(); i++) {
                Board currentBoard = grabbedBoard;
                newPosition = newPositions[i];
                currentBoard.addNewPathAndUpdateBoard(stoi(newPosition));
                Q.push_back(currentBoard);
                push_heap(Q.begin(),Q.end(),pc);
				
				// Max Q length updating
				if (Q.size() > maxQLength) {maxQLength = Q.size();}
            }
        }
    }
	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	//path = grabbedBoard.getPath();
	path = grabbedBoard.getPath();
	cout << path << endl;
	pathLength = path.size();
	return path;		
		
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List by Misplaced Tiles
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList_Misplacedtiles(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	//srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	//maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	maxQLength = 0;
	//numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY
	numOfStateExpansions = 0;

	vector<Board> Q;
    unordered_map<string, string> boardRules;
    Board grabbedBoard;
	unordered_map<int, string> Exp;
	int oldLength = Exp.size();
	// for hash map 
	hash<string> hashFunc;
	
	Board board(initialState,goalState);
	
	boardRules["0"] = "13";
    boardRules["1"] = "042";
    boardRules["2"] = "15";
    boardRules["3"] = "046";
    boardRules["4"] = "1375";
    boardRules["5"] = "248";
    boardRules["6"] = "37";
    boardRules["7"] = "468";
    boardRules["8"] = "57";
	
	HeuMTComparator pc;
    Q.push_back(board);
	
	 // make heap

    make_heap(Q.begin(),Q.end(),pc);

    // start search from the first path
	bool keep_running = true;
    while(keep_running) {
        if (Q.empty()) {cout<<"Goal NOT Found"<<endl;break;}
        grabbedBoard = Q.front();
        pop_heap(Q.begin(),Q.end(),pc);
        Q.pop_back();
		
		if (grabbedBoard.checkGoal()) {
			keep_running = false;
			break;
		}

        oldLength = Exp.size();
		Exp[hashFunc(grabbedBoard.getContent())] = grabbedBoard.getContent();
		// Try to add the grabbed board (puzzle) into hash table
		// if the previous and the current length is the same
		// that means failed to add, there is a same board existed
		// in hash table already.
		// If the lengths are different, means new board added successfully
		// we did not expand this board before
		// so do the algorithm
		if (oldLength == Exp.size()) {continue;}
		else {
			// Update number of state expansion
			numOfStateExpansions++;
			
            string blankPosition = to_string(grabbedBoard.getContent().find("0"));
            /* Iterate the string */
            string newPositions = boardRules[blankPosition];
            string newPosition;
            for (int i = 0; i < newPositions.length(); i++) {
                Board currentBoard = grabbedBoard;
                newPosition = newPositions[i];
                currentBoard.addNewPathAndUpdateBoard(stoi(newPosition));
                Q.push_back(currentBoard);
                push_heap(Q.begin(),Q.end(),pc);
				
				// Max Q length updating
				if (Q.size() > maxQLength) {maxQLength = Q.size();}
				
            }
        }
    }
	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	path = grabbedBoard.getPath();
	cout << endl;
	cout << path << endl;
	pathLength = path.size();
	return path;		
		
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List by Manhattan Distance
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList_Manhattan(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	//srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	//maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	maxQLength = 0;
	//numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY
	numOfStateExpansions = 0;

	vector<Board> Q;
    unordered_map<string, string> boardRules;
    Board grabbedBoard;
	unordered_map<int, string> Exp;
	int oldLength = Exp.size();
	// for hash map 
	hash<string> hashFunc;
	
	Board board(initialState,goalState);
	
	boardRules["0"] = "13";
    boardRules["1"] = "042";
    boardRules["2"] = "15";
    boardRules["3"] = "046";
    boardRules["4"] = "1375";
    boardRules["5"] = "248";
    boardRules["6"] = "37";
    boardRules["7"] = "468";
    boardRules["8"] = "57";
	
	HeuMDComparator pc;
    Q.push_back(board);
	
	 // make heap

    make_heap(Q.begin(),Q.end(),pc);

    // start search from the first path
	bool keep_running = true;
    while(keep_running) {
        if (Q.empty()) {cout<<"Goal NOT Found"<<endl;break;}
        grabbedBoard = Q.front();
        pop_heap(Q.begin(),Q.end(),pc);
        Q.pop_back();
		
		if (grabbedBoard.checkGoal()) {
			keep_running = false;
			break;
		}

        oldLength = Exp.size();
		Exp[hashFunc(grabbedBoard.getContent())] = grabbedBoard.getContent();
		// Try to add the grabbed board (puzzle) into hash table
		// if the previous and the current length is the same
		// that means failed to add, there is a same board existed
		// in hash table already.
		// If the lengths are different, means new board added successfully
		// we did not expand this board before
		// so do the algorithm
		if (oldLength == Exp.size()) {continue;}
		else {
			// Update number of state expansion
			numOfStateExpansions++;
			
            string blankPosition = to_string(grabbedBoard.getContent().find("0"));
            /* Iterate the string */
            string newPositions = boardRules[blankPosition];
            string newPosition;
            for (int i = 0; i < newPositions.length(); i++) {
                Board currentBoard = grabbedBoard;
                newPosition = newPositions[i];
                currentBoard.addNewPathAndUpdateBoard(stoi(newPosition));
                Q.push_back(currentBoard);
                push_heap(Q.begin(),Q.end(),pc);
				
				// Max Q length updating
				if (Q.size() > maxQLength) {maxQLength = Q.size();}
            }
        }
    }
	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	path = grabbedBoard.getPath();
	cout << endl;
	cout << path << endl;
	pathLength = path.size();
	return path;		
		
}

