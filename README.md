# Zhang_CSCI2270_FinalProject
Micah Zhang CSCI2270 Data Structures Final Project

CSCI2270 CS2:Data Structures
Author: Micah Zhang
Date: July 28th, 2017
Final Project

Project Summary:
-----------------
>The purpose of this program is to successfully combine two data structures: graphs and binary search trees within one class, 
and to use them to solve a meaningful problem: helping the user select the optimal rocket for an interplanetary vacation, where the
"optimal rocket" is defined as the rocket that meets the fuel and passenger capacity requirements of the user with minimum excess.
More specifically, this program parses a text file to create three binary search trees. Each node, or "Rocket", has 3 main properties:
its name, its, fuel consumption (in units), its passenger capacity, and its quantity in the rental company's inventory.
These three trees differ from each other according to which property determines its order, ie, the "nameTree" is ordered
alphabetically based on the names of each of the nodes. Upon initialization, the code will also create a graph with 9 nodes and link them together,
each node representing a different planet. From there, the user will be presented with a menu containing 10 options. The first option
searches through the nameBST for a user inputed name. The second option allows the user to rent a rocket, decrementing its 
quantity in all three BSTs. The third option lists all types of rockets currently in the three BSTs. The fourth option allows the user
to delete any rocket simulatenously from all three trees by entering in the name to be deleted. The fifth option counts the number of unique
nodes in the BSTs and returns this number to the user. The sixth option displays each vertice in the graph along with all of its edges.
The seventh option allows the user to add a new vertice the graph by specifying its name and all edges with their respective weights.
The eight option asks the user for a starting place and a destination, and then uses Dijkstra's algorithm to find the path with the lowest
cumulative weight, representative of the least amount of fuel required, and display to the user both the path and the minimum necessary fuel
cost. The ninth option incorporates both data structures by helping the user "plan a trip". The user is prompted for a starting and ending
destination, with which the program will apply Dijkstra's algorithm to find the shortest path between the two planets, thereby determining
the minimum amount of fuel needed when selecting a rocket. It will also prompt the user for the number of passengers present on the trip, 
thereby determining the minimum passenger capacity needed when selecting a rocket. It then searchs through the fuelBST and the 
passengercapacityBST to find the optimal rocket for the trip: that is, the rocket that satisfies both the minimum fuel requirement and
the minimum passenger capacity requirement with the least amount of excess.          

How to Run:
------------
> To install this program on your machine, clone this repository from github by entering the following line into the the command line: <git clone https://github.com/Micah-Zhang/Zhang_CSCI2270_FinalProject>
> Once installed, traverse into the directory containing the program by entering the following line into the command line: <cd Zhang_CSCI270_FinalProject>
> To compile the program using the g++ compiler, enter the following line into the command line: <g++ -std=c++11 StarlinerIndustries.cpp driverStarlinerIndustries.cpp -o fp>
> This will create an executable file called: "fp".
> To run the program, enter the following line into the command line: <./fp RocketInventory.txt> 
> NOTE: You MUST include the name of the text file when executing the program. Otherwise, the program will not run properly.
> NOTE: Each line in the text file "RocketInventory.txt" follows the format: <name,fuel capacity,passenger capacity, quantity>, with a newline character at the end of every line.
> Feel free to add to the text file as long as you are aware of the format listed above.

Dependencies:
--------------
>This program requires the following libraries:
	1. the <iostream> library
	2. the <string> library
	3. the <stdlib.h> library
	4. the <fstream> library
	5. the <climits> library
	6. the <vector> library
>All of the above libraries are first-party libraries that should have been downloaded alongside the user's initial c++ installation.
>However, if the user is missing one of more of the above libraries, please visit the following website: <http://en.cppreference.com/w/cpp/header>, which will provide additional information on the matter. 

System Requirements:
--------------------
>This program can be run using any operating system, including Windows, MacOS, and Linux, provided the user has the ability to compile and run programs written in c++. This particular program was compiled using the g++ compiler. Of course, the user may choose to use a different one.
>For additional information about the g++ compiler, please refer the the following website: <http://www.cprogramming.com/g++.html>

My Name:
----------
Micah Zhang

Open issues/bugs:
-----------------
>This program is heavily constrained by the nature of binary search trees. 
>Most notably, it cannot differentiate between two rockets with the same fuel capacity or passenger capacity. 
>For example, when two rockets, both with a fuel capacity of 4 are present, the program will consistenly select the first rocket it encounters while conducting its search.
>This greatly limits its relevance in real-world applications.
>Future implementations of this program may replace the binary search tree with a more effective data structure.
