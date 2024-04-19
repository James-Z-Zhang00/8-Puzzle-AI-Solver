#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdlib>
#include <string>
using namespace std;

class Board {
	
private:

    string currentBoard;
    string goalBoard;
    int misplacedTiles;
	int manhattanDistance;
    string path;

public:

	void calculateMisplacedTiles();
	void calculateManhattanDistance();
	int getManhattanDistance();
	int getHeuByMisplacedTiles();
    void addNewPathAndUpdateBoard(int positionNew);
    string getPath();
    int getCost();
    bool checkGoal();
    string getContent();
    Board(string content, string goal);
    Board(); // default constructor
    ~Board(); // destructure
    void setContent(string s);
    int getBlankTilePosition();
    void printBoard();

};