How To Run:
How To Compile:

make simpleGame
./simpleGame

The GameData object gets as input the following arguments:
1. Game Id.
2. number to look for.
3. start position.
4. maximum steps for player.
5. list of sorted numbers.


The Player object gets as input the following arguments:
1. number to look for.
2. Player Id.
3. Player algorithm id. id = 1 is for the simple algorithm and any other number is for the smarter algorithm.

The player's goal is to find the number in input list with minimum number of steps.
Player1 is a simple algorithm that moves right until it gets out of the list boundaries and then it moves left until it gets 
out of the list boundaries and so on.
Player2 is a smarter algorithm that checks the current list cell value and changes the direction accordingly (assuming the list is sorted).

