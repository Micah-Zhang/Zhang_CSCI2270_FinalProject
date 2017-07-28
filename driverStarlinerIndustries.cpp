/*
*CSCI2270 CS2:Data Structures
*Author: Micah Zhang
*Date: July 28th, 2017
*Final Project
*/

#include <iostream>
#include "StarlinerIndustries.hpp"

//DRIVER
int main(int argc, char *argv[]){ //allows text file to be passed from the command line as a command line argument
	std::string filename  = std::string(argv[1]);
	StarlinerIndustries myStarlinerIndustries;
	myStarlinerIndustries.build(filename);
	myStarlinerIndustries.addVertex("Earth");
	myStarlinerIndustries.addVertex("Mustafar");
	myStarlinerIndustries.addVertex("Kamino");
	myStarlinerIndustries.addVertex("Solaris");
	myStarlinerIndustries.addVertex("Cybertron");
	myStarlinerIndustries.addVertex("Genesis");
	myStarlinerIndustries.addVertex("Krypton");
	myStarlinerIndustries.addVertex("Dagobah");
	myStarlinerIndustries.addVertex("Kronos");
	myStarlinerIndustries.addEdge("Earth","Mustafar",2);
	myStarlinerIndustries.addEdge("Earth","Kamino",10);
	myStarlinerIndustries.addEdge("Earth","Solaris",3);
	myStarlinerIndustries.addEdge("Mustafar","Dagobah",10);
	myStarlinerIndustries.addEdge("Mustafar","Krypton",5);
	myStarlinerIndustries.addEdge("Mustafar","Kamino",2);
	myStarlinerIndustries.addEdge("Kamino","Cybertron",4);
	myStarlinerIndustries.addEdge("Kamino","Genesis",8);
	myStarlinerIndustries.addEdge("Dagobah","Kronos",3);
	myStarlinerIndustries.addEdge("Krypton","Dagobah",2);
	myStarlinerIndustries.addEdge("Krypton","Cybertron",2);
	myStarlinerIndustries.addEdge("Cybertron","Genesis",2);
	myStarlinerIndustries.addEdge("Solaris","Genesis",4);
	myStarlinerIndustries.addEdge("Genesis","Kronos",7);
	myStarlinerIndustries.addEdge("Kronos","Cybertron",5);
	myStarlinerIndustries.addEdge("Mustafar","Dagobah",10);
	myStarlinerIndustries.addEdge("Solaris","Mustafar",1);
	while(true){ //Display menu
		int newFuel, newCapacity;
		bool exists = false;
		std::string choice, searchName, rentName, deleteName;
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
			myStarlinerIndustries.nameSearch(searchName);
		}
		else if(choice=="2"){ //Rent a rocket
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,rentName);
			myStarlinerIndustries.rent(rentName);
		}
		else if(choice=="3"){ //Print the inventory
			myStarlinerIndustries.print();
		}
		else if(choice=="4"){ //Delete a rocket
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,deleteName);
			myStarlinerIndustries.deleteRocket(deleteName);
		}
		else if(choice=="5"){ //Count the rockets
			std::cout<<"Tree contains: "<<myStarlinerIndustries.countTree()<<" rockets."<<std::endl;
		}
		else if(choice=="6"){ //View map
			myStarlinerIndustries.printGraph();
		}
		else if(choice=="7"){ //Add planet
			std::cout<<"Enter the name of the new planet:"<<std::endl;
			std::getline(std::cin,searchName);
			myStarlinerIndustries.addVertex(searchName);
			while(true){
				std::cout<<"Enter the name of planet adjacent to the new planet:"<<std::endl;
				std::cout<<"(Enter <DONE> if there are no more planets adjacent to the new planet)"<<std::endl;
				std::getline(std::cin,rentName);
				if(rentName == "DONE"){
						break;
				}else{
					std::cout<<"Enter the fuel needed to travel between these two planets:"<<std::endl;
					std::getline(std::cin,deleteName);
					newFuel = std::stoi(deleteName);
					myStarlinerIndustries.addEdge(searchName,rentName,newFuel);
					std::cout<<"New destination added"<<std::endl;
				}
			}
		}
		else if(choice == "8"){ //Calculate shortest path between 2 planets
			std::cout<<"Enter starting planet:"<<std::endl;
			std::getline(std::cin,searchName);
			std::cout<<"Enter destination planet:"<<std::endl;
			std::getline(std::cin,rentName);
			newFuel = myStarlinerIndustries.Dijkstra(searchName,rentName);
		}
		else if(choice == "9"){ //find optinal route and rocket
			std::cout<<"Enter starting planet:"<<std::endl;
			std::getline(std::cin,searchName);
			std::cout<<"Enter destination planet:"<<std::endl;
			std::getline(std::cin,rentName);
			std::cout<<"Enter number of passengers present:"<<std::endl;
			std::getline(std::cin,deleteName);
			newCapacity = std::stoi(deleteName);
			newFuel = myStarlinerIndustries.Dijkstra(searchName,rentName);
			myStarlinerIndustries.optimizeRocket(newFuel,newCapacity);
		}
		else{ //Quit
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
	}
	return 0;
}
