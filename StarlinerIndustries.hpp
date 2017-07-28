/*
*CSCI2270 CS2:Data Structures
*Author:Micah Zhang
*Date: July 28th, 2017
*Final Project
*/
#ifndef StarlinerIndustries_HPP
#define StarlinerIndustries_HPP

#include <vector>

//forward declarations needed to prevent circular definitions
struct vertex;

struct adjVertex{
	vertex *v;
	int weight;
};

struct vertex{
	std::string name;
	bool visited;
	int distance;
	vertex *previous;
	std::vector<adjVertex> adj;
};

struct Rocket{
	std::string name; //stores name of rocket
	int fuel;
	int capacity;
	int quantity;
	Rocket *parent; //stores address of parent
	Rocket *left; //stores address of left child
	Rocket *right; //stores address of right child
	Rocket(std::string n, int f, int c, int q, Rocket *p, Rocket *l, Rocket *r): name(n), fuel(f), capacity(c), quantity(q), parent(p), left(l), right(r){}; //allows for easy definition
};

class StarlinerIndustries
{
	public:
		StarlinerIndustries();
		~StarlinerIndustries();
		//Graphs
		void addEdge(std::string v1, std::string v2, int weight);
		void addVertex(std::string name);
		void printGraph();
		int Dijkstra(std::string starting, std::string destination);
		//BSTs
		void build(std::string filename);
		void nameSearch(std::string searchName);
		void print();
		int countTree();
		void optimizeRocket(int minFuel, int minCapacity);
		void rent(std::string rentName);
		void deleteRocket(std::string deleteName);
		void deleteAll();
	private:
		//Graphs
		std::vector<vertex> vertices;
		//BSTs
		int count;
		Rocket *root; //tree 1: BST ordered by rocket NAME
		Rocket *froot; //tree 2: BST ordered by rocket FUEL CAPACITY
		Rocket *croot; //tree 3: BST ordered by rocket PASSENGER CAPACITY
		Rocket *nameSearchRecursive(Rocket *startRocket, std::string searchName);
		Rocket *fuelSearchRecursive(Rocket *startRocket, int searchFuel);
		Rocket *capacitySearchRecursive(Rocket *startRocket, int searchCapacity);
		Rocket *insertRecursive(Rocket *parent, Rocket *root, std::string newName, int newFuel, int newCapacity, int newQuantity);
		Rocket *fuelInsertRecursive(Rocket *parent, Rocket *root, std::string newName, int newFuel, int newCapacity, int newQuantity);
		Rocket *capacityInsertRecursive(Rocket *parent, Rocket *root, std::string newName, int newFuel, int newCapacity, int newQuantity);
		Rocket *deleteRecursive(Rocket *startRocket, std::string deleteName);
		Rocket *fuelDeleteRecursive(Rocket *startRocket, int deleteFuel);
		Rocket *capacityDeleteRecursive(Rocket *startRocket, int deleteCapacity);
		Rocket *minRecursive(Rocket *startRocket);
		Rocket *maxRecursive(Rocket *startRocket);
		void deleteAllRecursive(Rocket *startRocket);
		void fdeleteAllRecursive(Rocket *startRocket);
		void printRecursive(Rocket *startRocket);
		void countRecursive(Rocket *startRocket);
};

#endif//StarlinerIndustries_HPP
