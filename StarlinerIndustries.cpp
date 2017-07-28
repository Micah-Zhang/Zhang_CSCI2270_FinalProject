/* Micah Zhang
Final Project
Shirly */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <climits>

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
	std::string name; //stores name of movie
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
		void displayEdges();
		int Dijkstra(std::string sourceVertex, std::string destinationVertex);
		//BSTs
		void build(std::string filename);
		void search(std::string searchName);
		void print();
		int countTree();
		void rent(std::string rentName);
		void deleteRocket(std::string deleteName);
		void deleteAll();
	private:
		//Graphs
		std::vector<vertex> vertices;
		//BSTs
		int count;
		Rocket *root;
		Rocket *searchRecursive(Rocket *startRocket, std::string searchName);
		Rocket *insertRecursive(Rocket *parent, Rocket *root, std::string newName, int newFuel, int newCapacity, int newQuantity);
		Rocket *deleteRecursive(Rocket *startRocket, std::string deleteName);
		Rocket *minRecursive(Rocket *startRocket);
		void deleteAllRecursive(Rocket *startRocket);
		void printRecursive(Rocket *startRocket);
		void countRecursive(Rocket *startRocket);
};

StarlinerIndustries::StarlinerIndustries(){
	root = NULL;
}

StarlinerIndustries::~StarlinerIndustries(){
	deleteAll();
}

//Graphs implementation
void StarlinerIndustries::addVertex(std::string n){
	bool found = false;
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == n){
			found = true;
			std::cout<<vertices[i].name<<" found."<<std::endl;
			}
		}
	if(found == false){
		vertex v;
		v.name = n;
		v.distance = 0;
		v.visited = false;
		v.previous = nullptr;
		vertices.push_back(v);
	}
}

void StarlinerIndustries::addEdge(std::string v1, std::string v2, int weight){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == v1){
			for(int j = 0; j < vertices.size(); j++){
				if(vertices[j].name == v2 && i != j){
					adjVertex av;
					av.v = &vertices[j];
					av.weight = weight;
					vertices[i].adj.push_back(av);
					adjVertex av2;
					av2.v = &vertices[i];
					av2.weight = weight;
					vertices[j].adj.push_back(av2);
				}
			}
		}
	}
}

//loop through all vertices and adjacent vertices
void StarlinerIndustries::displayEdges(){
	std::cout<<"============================================================"<<std::endl;
	for(int i = 0; i < vertices.size(); i++){
		std::cout<<vertices[i].name<<"-->"<<std::endl;
		for(int j = 0; j < vertices[i].adj.size(); j++){
			std::cout<<vertices[i].adj[j].v->name;
			std::cout<<" (distance: "<<vertices[i].adj[j].v->distance
			<<", visited: "<<vertices[i].adj[j].v->visited<<", parent: ";
			if (vertices[i].adj[j].v->previous==nullptr)
				std::cout<<" nullptr)"<<std::endl;
			else
				std::cout<<vertices[i].adj[j].v->previous->name<<")"<<std::endl;
		}
		std::cout<<"============================================================"<<std::endl;
	}
}

int StarlinerIndustries::Dijkstra(std::string starting, std::string destination){
	vertex * start = nullptr;
	vertex * ending = nullptr;
	//search routine to find starting and destination
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		vertices[i].distance = INT_MAX;
		vertices[i].previous = nullptr;
		if (vertices[i].name == starting) {
			start = &vertices[i];
		}
		if (vertices[i].name == destination) {
			ending = &vertices[i];
		}
	}
	if (start != nullptr && ending != nullptr){
		start->visited = true;
		start->distance = 0;
		std::vector<vertex *> solved;
		std::vector<vertex *> path;
		solved.push_back(start);
		adjVertex * v;
		vertex * u;
		vertex * minVertex;
		vertex * prev;
		while (ending->visited == false) {
			int minDistance = INT_MAX;
			for (int i = 0; i < solved.size(); i++) {
				u = solved[i];
				for (int j = 0; j < u->adj.size(); j++) {
					v = &solved[i]->adj[j];
					if (v->v->visited == false) {
						int dist = u->distance + v->weight;
						if (dist < minDistance) {
							minDistance = dist;
							minVertex = v->v;
							prev = u;
						}
					}
				}
			}
			solved.push_back(minVertex);
			minVertex->distance = minDistance;
			minVertex->previous = prev;
			minVertex->visited = true;
		}
		vertex * vert = ending;
		while (vert != nullptr) {
			path.push_back(vert);
			vert = vert->previous;
		}
		return solved[solved.size()-1]->distance;
	}else if (ending!=nullptr){
		std::cout<<"start not found"<<std::endl;
		exit(1);
	}else{
		std::cout<<"ending not found"<<std::endl;
		exit(1);
	}
}

//user accessible rent function.
void StarlinerIndustries::rent(std::string rentName){
	Rocket *rentRocket;
	rentRocket=searchRecursive(root, rentName); //search entire treee for movie to be rented
	if(rentRocket==NULL){ //if movie not found, say so.
		std::cout<<"Rocket not found."<<std::endl;
	}else{ //otherwise, decrement the quantity of the movie and print its updated information
		rentRocket->quantity--;
		std::cout << "Rocket has been rented." << std::endl;
		std::cout << "Rocket Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Name:" << rentRocket->name << std::endl;
		std::cout << "Fuel:" << rentRocket->fuel << std::endl;
		std::cout << "Capacity:" << rentRocket->capacity << std::endl;
		std::cout << "Quantity:" << rentRocket->quantity << std::endl;
		if(rentRocket->quantity==0){ //if the quantity of movie reaches zero, delete it
			deleteRecursive(root,rentRocket->name);
		}
	}
}

//no user accessible count function.
void StarlinerIndustries::countRecursive(Rocket *startRocket){
	if(startRocket->left!=NULL){ //uses inorder traversal to count the number of nodes in the tree.
		countRecursive(startRocket->left);
	}
	count++;
	if(startRocket->right!=NULL){
		countRecursive(startRocket->right);
	}
}

//user accessible count function.
int StarlinerIndustries::countTree(){
	count = 0; //reset count each time in case the tree changes.
	countRecursive(root); //count each node in tree.
	return count;
}

//non user accessible print tree function.
void StarlinerIndustries::printRecursive(Rocket *startRocket){
	if(startRocket->left!=NULL){ //uses inorder traversal to print the name and quantity of each node in the tree in alphabetcal order.
		printRecursive(startRocket->left);
	}
	std::cout<<"Rocket: "<<startRocket->name<<" "<<startRocket->quantity<<std::endl;
	if(startRocket->right!=NULL){
		printRecursive(startRocket->right);
	}
}

//user accessible print tree function. root is hidden.
void StarlinerIndustries::print(){
	return printRecursive(root);
}

//uses text file to build tree
void StarlinerIndustries::build(std::string filename){
	std::string newName, nF, nC, nQ;
	int newFuel;
	int newCapacity;
	int newQuantity;
	std::ifstream myfile(filename);
	if(myfile.is_open()){
		while(std::getline(myfile,newName,',')){ //keep reading until end of file
			std::getline(myfile,nF,',');
			std::getline(myfile,nC,',');
			std::getline(myfile,nQ,'\n');
			newFuel = std::stoi(nF);
			newCapacity = std::stoi(nC);
			newQuantity = std::stoi(nQ);
			root = insertRecursive(NULL,root,newName,newFuel,newCapacity,newQuantity); //pass root = null to specify new tree
		}
	myfile.close();
	}else std::cout<<"Unable to open file"<<std::endl;
}

//recursively insert new movies into tree
Rocket* StarlinerIndustries::insertRecursive(Rocket *tparent, Rocket *troot, std::string newName, int newFuel, int newCapacity, int newQuantity){
	if(troot==NULL){ //if end of tree is reached, insert new movie
		troot = new Rocket(newName,newFuel,newCapacity,newQuantity,tparent,NULL,NULL);
	}
	else if(newName.compare(troot->name)<0){ //if newName is alphabetically smaller than current name, traverse left
		troot->left=insertRecursive(troot,troot->left,newName,newFuel,newCapacity,newQuantity);
	}
	else{ //if newName is alphabetically larger than the current name, traverse right
		troot->right=insertRecursive(troot,troot->right,newName,newFuel,newCapacity,newQuantity);
	}
	return troot; //always return the address of the new movie to be inserted into end of tree
}

//non user accessible function find the minimum of a tree.
Rocket* StarlinerIndustries::minRecursive(Rocket *startRocket){
	while(startRocket->left != NULL){ //keep traversing left until leaf reached. leaf is minimum.
		startRocket = startRocket->left;
	}return startRocket;
}

//user accessible recursive delete function.
void StarlinerIndustries::deleteRocket(std::string deleteName){
	Rocket *deleted = searchRecursive(root, deleteName);
	if(deleted==NULL){
		std::cout<<"Rocket not found."<<std::endl;
	}else{
		deleted = deleteRecursive(root, deleteName);
	}
}


//non user accessible recursive delete function.
Rocket* StarlinerIndustries::deleteRecursive(Rocket *startRocket, std::string deleteName){
	if(startRocket==NULL)return startRocket; //if tree empty, return null
	else if(deleteName.compare(startRocket->name)<0){ //traverse left and right respectively until found node to be deleted.
		startRocket->left = deleteRecursive(startRocket->left,deleteName);
	}else if(deleteName.compare(startRocket->name)>0){
		startRocket->right = deleteRecursive(startRocket->right, deleteName);
	}else{
		//Leaf. No children.
		if(startRocket->left == NULL && startRocket->right == NULL){ //easiest case: delete leaf.
			delete startRocket; //delete leaf
			startRocket = NULL; //reset pointer
		}else if(startRocket->left==NULL){ //1 child on right //middle case: determine if has left or right child, then shift child up appropriately before deleting node. 
			Rocket *tmp = startRocket;
			startRocket = startRocket->right;
			startRocket->parent = tmp->parent;
			delete tmp;
		}else if(startRocket->right==NULL){ //1 child on left
			Rocket *tmp = startRocket;
			startRocket = startRocket->left;
			startRocket->parent = tmp->parent;
			delete tmp;
		}else{ //2 children
			Rocket *tmp = minRecursive(startRocket->right); //most difficult case: find the minimum right value in the tree
			startRocket->name = tmp->name; //replace current node with min right value below root.
			startRocket->fuel = tmp->fuel;
			startRocket->capacity = tmp->capacity;
			startRocket->quantity = tmp->quantity;
			startRocket->right = deleteRecursive(startRocket->right,tmp->name); //now just like deleting a node with one child. delete the min right node using recursion. this effectively shifts the right side of the current node up one node, while in the process deleting the current node
		}
	}
	return startRocket;
}

//recursively search tree for string "searchName"
Rocket* StarlinerIndustries::searchRecursive(Rocket *startRocket, std::string searchName){
	if(startRocket==NULL)return NULL; //if empty BST, return NULL
	if(startRocket->name==searchName)return startRocket; //if found, return address where found
	else if(searchName.compare(startRocket->name)<0) //if name > searchName, searchName must be in the left branch of the tree
		return searchRecursive(startRocket->left,searchName); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return searchRecursive(startRocket->right, searchName); //continue searching right of tree
}

//recursively search accessible by user. hides access to root.
void StarlinerIndustries::search(std::string searchName){
	Rocket *foundRocket;
	foundRocket = searchRecursive(root, searchName);
	if(foundRocket==NULL){ //if move not found, say so
		std::cout<<"Rocket not found."<<std::endl;
	}else{ //otherwise display information of found node
		std::cout<<"Rocket Info:"<<std::endl;
		std::cout<<"==========="<<std::endl;
		std::cout<<"Name:"<<foundRocket->name<<std::endl;
		std::cout<<"Fuel:"<<foundRocket->fuel<<std::endl;
		std::cout<<"Capacity:"<<foundRocket->capacity<<std::endl;
		std::cout<<"Quantity:"<<foundRocket->quantity<<std::endl;
	}
}

//non user accessible recursive delete ALL function.
void StarlinerIndustries::deleteAllRecursive(Rocket *startRocket){
	if(startRocket == NULL){
		return;
	}
	if(startRocket->left!=NULL){ //delete all nodes using postorder traversal
		deleteAllRecursive(startRocket->left);
	}
	if(startRocket->right!=NULL){
		deleteAllRecursive(startRocket->right);
	}
	std::cout<<"Deleting: "<<startRocket->name<<std::endl;
	delete startRocket;
}

//user accessible recursive delete ALL function
void StarlinerIndustries::deleteAll(){
	return deleteAllRecursive(root);
}

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
		int newFuel;
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
		std::cout << "8. Plan Trip" << std::endl;
		std::cout << "9. Quit" << std::endl;
		std::getline(std::cin,choice);

		if(choice=="1"){ //Find a movie
			std::cout<<"Enter name:"<<std::endl;
			std::getline(std::cin,searchName);
			myStarlinerIndustries.search(searchName);
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
			myStarlinerIndustries.displayEdges();
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
		else if(choice=="8"){
			std::cout<<"Enter starting planet:"<<std::endl;
			std::getline(std::cin,searchName);
			std::cout<<"Enter destination planet:"<<std::endl;
			std::getline(std::cin,rentName);
			newFuel = myStarlinerIndustries.Dijkstra(searchName,rentName);
			std::cout << newFuel << std::endl;
		}
		else{ //Quit
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
	}
	return 0;
}
