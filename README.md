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
