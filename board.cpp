#include <iostream>
#include "board.h"
#include <list>
#include <unordered_map>
#include <cstdlib>
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////
//constructor & destructor
//////////////////////////////////////////////////////////////
Board::Board() {

}

Board::~Board() {

}

//////////////////////////////////////////////////////////////
//constructor 
//inputs: initial state, goal state
//////////////////////////////////////////////////////////////
Board::Board(string content, string goal) {
    currentBoard = content;
    goalBoard = goal;
	calculateManhattanDistance();
	calculateMisplacedTiles();
}
	
//////////////////////////////////////////////////////////////
//calculate manhattan distance for the current board
//////////////////////////////////////////////////////////////	
void Board::calculateManhattanDistance() {
	int row, col;
	// col: index % 3
	// row: index / 3 must be whole number calculation e.g. int
	// or the result must be rounded down (ignore decimal parts)
	int MD;
	int MDtotal = 0;

	for (int i = 0; i < 9; i++) {
		// cout << s[i] << endl;
		// cout << "col: " << i % 3 << " row: " << i / 3 << endl;
		if (currentBoard[i] == '0') {continue;}
		for (int j = 0; j < 9; j++) {
			if (goalBoard[j] == '0') {continue;}
			if (currentBoard[i] == goalBoard[j]) {
				MD = abs(i % 3 - j % 3) + abs(i / 3 - j / 3);
				MDtotal += MD;
			}
		}
	}
	manhattanDistance = MDtotal;
}

//////////////////////////////////////////////////////////////
//get manhattan distance for the current board
//////////////////////////////////////////////////////////////
int Board::getManhattanDistance() {
	// the total value for sorting should include path length too
	return manhattanDistance + path.length();
}

//////////////////////////////////////////////////////////////
//calculate Heu by misplaced tiles 
//////////////////////////////////////////////////////////////

void Board::calculateMisplacedTiles() {
	int mt = 0;
	for (int i = 0; i < 9; i++) {
		// Exclude the misplaced blank tiles 
		// for Heu counting
		if (currentBoard[i] != goalBoard[i] 
		&& currentBoard              [i] != '0' 
		&& goalBoard[i] != '0') {mt++;}
	}
	misplacedTiles = mt;
}

//////////////////////////////////////////////////////////////
//get Heu by misplaced tiles 
//////////////////////////////////////////////////////////////
int Board::getHeuByMisplacedTiles() {
	return path.length() + misplacedTiles;
}

//////////////////////////////////////////////////////////////
//get Heu by misplaced tiles 
//////////////////////////////////////////////////////////////
void Board::addNewPathAndUpdateBoard(int positionNew) {
	int blank = currentBoard.find("0");
	int decoder = positionNew - blank;
	// Due to the board rules are pre-definded
	// there is no way to move diagonally or skip tiles
	if (decoder == -1) {path+="L";} // Left
	else if (decoder == 1) {path+="R";} // Right
	else if (decoder < -1) {path+="U";} // Up
	else if (decoder > 1) {path+="D";} // Down
	// Update board string & other info
	swap(currentBoard[blank],currentBoard[positionNew]);
	calculateManhattanDistance();
	calculateMisplacedTiles();
	
}

//////////////////////////////////////////////////////////////
//getters & setters & printing function
//////////////////////////////////////////////////////////////
string Board::getPath() {
    return path;
}

int Board::getCost() {
    return path.length();
}

bool Board::checkGoal() {
    return (currentBoard == goalBoard) ? true : false;
}

string Board::getContent() {
    return currentBoard;
}

void Board::setContent(string s) {
    currentBoard = s;
}

int Board::getBlankTilePosition() {
    // the position index will be returned in int type
    return currentBoard.find("0");
}

void Board::printBoard() {
    cout << currentBoard << endl;
}
	