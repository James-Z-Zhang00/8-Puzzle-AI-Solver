# The first AI search project in C++

## Initial Board States

The initial given boards are "120483765","208135467","704851632","536407182" and "638541720".

Each number is for one position on a 3 x 3 board.

The AI will find the shorest path to return them back to "123456780".

Number 0 is the empty pile on the board.

![8-puzzle-search](https://github.com/James-Z-Zhang00/8-Puzzle-AI-Solver/assets/144994336/71708f6d-0b61-45e6-a516-0160495a5f49)

As shown in the graph, the blank tile can be filled by any other tiles nearby, I convert this theory into a C++ map, where 0 indicates the tile on the top left corner, 1 indicates the tile on the top middle.

```
|0|1|2|
|3|4|5|
|7|8|9|
```

From position 0, you can go to position 1 and 3.
From position 1, you can go to position 0, 4 and 5.
And so on

```cpp
boardRules["0"] = "13";
boardRules["1"] = "042";
boardRules["2"] = "15";
boardRules["3"] = "046";
boardRules["4"] = "1375";
boardRules["5"] = "248";
boardRules["6"] = "37";
boardRules["7"] = "468";
boardRules["8"] = "57";
```

## The Algorithm

In a while loop, create a `Queue (Q)` to save the current board status. If the status matches our goal, break the loop.

The board status was save as an object in the queue.

```cpp
if (Q.empty()) {cout<<"Goal NOT Found"<<endl;break;}
        grabbedBoard = Q.front();
        pop_heap(Q.begin(),Q.end(),pc);
        Q.pop_back();
		
		if (grabbedBoard.checkGoal()) {
			keep_running = false;
			break;
		}
```

Save the board status into has map to avoid check the same path again.

Once we find the path is not what we are looking for, leave it.

```cpp
		
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

```

If the path is not proved bad path (we didn't check before), check the next possible move, then see if we are closer to our goal.

Loop through all possible moves and push the new status into the queue, the queue will sort (heap sorting) out the cloest move and save it for the next exploration.

```cpp
for (int i = 0; i < newPositions.length(); i++) {
  Board currentBoard = grabbedBoard;
  newPosition = newPositions[i];
  currentBoard.addNewPathAndUpdateBoard(stoi(newPosition));
  Q.push_back(currentBoard);
  push_heap(Q.begin(),Q.end(),pc);
}
```

During searching and sorting, grabbedBoard object will keep track the path/move (U: Up, D: Down, L: Left, R: Right) and return it when we reached our goal.

```cpp
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	path = grabbedBoard.getPath();
	cout << endl;
	cout << path << endl;
	pathLength = path.size();
	return path;
```

## Apply the Algorithm by Different Sorting Factors


