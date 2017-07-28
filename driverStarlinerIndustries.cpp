/*
*CSCI2270 CS2:Data Structures
*Author: Micah Zhang
*Date: July 28th, 2017
*Final Project
*/

#include <iostream>
#include "StarlinerIndustries.hpp" //import header and implementation file

//DRIVER
int main(int argc, char *argv[]){ //allows text file to be passed from the command line as a command line argument
	std::string filename  = std::string(argv[1]);
	StarlinerIndustries myStarlinerIndustries; //create instance of "StarlinerIndustries" class, which contains both graphs and BSTs
	myStarlinerIndustries.build(filename); //use the text file to build 3 BSTs
	myStarlinerIndustries.addVertex("Earth"); //add the vertex "Earth" to the graph 
	myStarlinerIndustries.addVertex("Mustafar"); //add the vertex "Mustafar" to the graph
	myStarlinerIndustries.addVertex("Kamino"); //add the vertex "Kamino" to the graph
	myStarlinerIndustries.addVertex("Solaris"); //add the vertex "Solaris" to the graph
	myStarlinerIndustries.addVertex("Cybertron"); //add the vertex "Cybertron" to the graph
	myStarlinerIndustries.addVertex("Genesis"); //add the vertex "Genesis" to the graph
	myStarlinerIndustries.addVertex("Krypton"); //add the vertex "Krypton" to the graph
	myStarlinerIndustries.addVertex("Dagobah"); //add the vertex "Dagobah" to the graph
	myStarlinerIndustries.addVertex("Kronos"); //add the vertex "Kronos" to the graph
	myStarlinerIndustries.addEdge("Earth","Mustafar",2); //create a path between Earth and Mustafar with a weight of 2
	myStarlinerIndustries.addEdge("Earth","Kamino",10); //create a path between Earth and Kamino with a weight of 10
	myStarlinerIndustries.addEdge("Earth","Solaris",3); //create a path between Earth and Solaris with a weight of 3
	myStarlinerIndustries.addEdge("Mustafar","Dagobah",10); //create a path between Mustafar and Dagobah with a weight of 10
	myStarlinerIndustries.addEdge("Mustafar","Krypton",5); //create a path between Mustafar and Krypton with a weight of 5
	myStarlinerIndustries.addEdge("Mustafar","Kamino",2); //create a path between Mustafar and Kamino with a weight of 2
	myStarlinerIndustries.addEdge("Kamino","Cybertron",4); //create a path between Kamino and Cybertron with a weight of 4
	myStarlinerIndustries.addEdge("Kamino","Genesis",8); //create a path between Kamino and Genesis with a weight of 8
	myStarlinerIndustries.addEdge("Dagobah","Kronos",3); //create a path between Dagobah and Kronos with a weight of 3
	myStarlinerIndustries.addEdge("Krypton","Dagobah",2); //create a path between Krypton and Dagobah with a weight of 2
	myStarlinerIndustries.addEdge("Krypton","Cybertron",2); //create a path between Krypton and Cybertron with a weight of 2
	myStarlinerIndustries.addEdge("Cybertron","Genesis",2); //create a path between Krpyton and Cybertron with a weight of 2
	myStarlinerIndustries.addEdge("Solaris","Genesis",4); //create a path between Solaris and Genesis with a weight of 4
	myStarlinerIndustries.addEdge("Genesis","Kronos",7); //create a path between Genesis and Kronos with a weight of 7
	myStarlinerIndustries.addEdge("Kronos","Cybertron",5); //create a path between Kronos and Cybertron with a weight of 5
	myStarlinerIndustries.addEdge("Mustafar","Dagobah",10); //create a path between Mustafar and Dagobah with a weight of 10
	myStarlinerIndustries.addEdge("Solaris","Mustafar",1); //create a path between Solaris and Mustafar with a weight of 1
	while(true){ //Display menu
		int newFuel, newCapacity;
		bool exists = false;
		std::string choice, searchName, rentName, deleteName, newPlanet, adjPlanet, nF, startPlanet, endPlanet,numPass;
		//display menu
		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Find a rocket" << std::endl;
		std::cout << "2. Rent a rocket" << std::endl;
		std::cout << "3. Print the inventory" << std::endl;
		std::cout << "4. Delete a rocket" << std::endl;
		std::cout << "5. Count the rockets" << std::endl;
		std::cout << "6. View map" << std::endl;
		std::cout << "7. Add planet" << std::endl;
		std::cout << "8. Shortest path" << std::endl;
		std::cout << "9. Plan trip" << std::endl;
		std::cout << "10. Quit" << std::endl;
		std::getline(std::cin,choice);

		if(choice=="1"){ //Find a rocket
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,searchName);
			myStarlinerIndustries.nameSearch(searchName); //searches nameBST for rocket name
		}
		else if(choice=="2"){ //Rent a rocket
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,rentName);
			myStarlinerIndustries.rent(rentName); //if movie to be rented is found, quantity of movie decrements by 1 in all three BSTs
		}
		else if(choice=="3"){ //Print the inventory
			myStarlinerIndustries.print();
		}
		else if(choice=="4"){ //Delete a rocket
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,deleteName);
			myStarlinerIndustries.deleteRocket(deleteName); //if movie to be deleted is found, movie is deleted from all 3 BSTs
		}
		else if(choice=="5"){ //Count the rockets
			std::cout<<"Tree contains: "<<myStarlinerIndustries.countTree()<<" rockets."<<std::endl; //counts number of nodes in BST
		}
		else if(choice=="6"){ //View map
			myStarlinerIndustries.printGraph(); //prints each vertex in graph along with all edges originating from it
		}
		else if(choice=="7"){ //Add planet
			std::cout<<"Enter the name of the new planet:"<<std::endl;
			std::getline(std::cin,newPlanet);
			myStarlinerIndustries.addVertex(newPlanet); //adds new vertex to graph with user specified name
			while(true){
				std::cout<<"Enter the name of planet adjacent to the new planet:"<<std::endl; //prompts user for adjacent vertices for new vertex
				std::cout<<"(Enter <DONE> if there are no more planets adjacent to the new planet)"<<std::endl; //user can enter as many vertices as they'd like and exit whenever they want by entering "DONE".
				std::getline(std::cin,adjPlanet);
				if(adjPlanet == "DONE"){ //if user enters "DONE", stop prompting user for new adj vertices
						break;
				}else{
					std::cout<<"Enter the fuel needed to travel between these two planets:"<<std::endl; //prompt user for weight of new path
					std::getline(std::cin,nF);
					newFuel = std::stoi(nF); //must convert string to integer
					myStarlinerIndustries.addEdge(newPlanet,adjPlanet,newFuel); //add new edge to graph using user inputs
					std::cout<<"New planet added"<<std::endl; //notify user when complete
				}
			}
		}
		else if(choice == "8"){ //Calculate shortest path between 2 planets
			std::cout<<"Enter starting planet:"<<std::endl; //prompt user for starting planet
			std::getline(std::cin,startPlanet);
			std::cout<<"Enter destination planet:"<<std::endl; //prompt user for ending planet
			std::getline(std::cin,endPlanet);
			newFuel = myStarlinerIndustries.Dijkstra(startPlanet,endPlanet); //use Dijkstra's algorithm to calculate path with minimum cumulative weight. display path and return minimum weight
		}
		else if(choice == "9"){ //find optinal route and rocket
			std::cout<<"Enter starting planet:"<<std::endl; //prompt user for start planet
			std::getline(std::cin,startPlanet);
			std::cout<<"Enter destination planet:"<<std::endl; //prompt user for end planet
			std::getline(std::cin,endPlanet);
			std::cout<<"Enter number of passengers present:"<<std::endl; //prompt user for minimum passenger capacity
			std::getline(std::cin,numPass);
			newCapacity = std::stoi(numPass); //convert to int
			newFuel = myStarlinerIndustries.Dijkstra(startPlanet,endPlanet); //use Dijkstra's algorithm to calculate path with minimum cumulative weight. display path and min weight.
			myStarlinerIndustries.optimizeRocket(newFuel,newCapacity); //find optimal rocket for trip. display to user.
		}
		else{ //Quit
			std::cout<<"Goodbye!"<<std::endl; //exit program
			break;
		}
	}
	return 0;
}
