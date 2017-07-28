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
	Rocket *parent; //stores address of parent
	Rocket *left; //stores address of left child
	Rocket *right; //stores address of right child
	Rocket(std::string n, int *f, int *c, Rocket *p, Rocket *l, Rocket *r): name(n), fuel(f), capacity(c), parent(p), left(l), right(r){}; //allows for easy definition
};

class Graph
{
	public:
		Graph();
		~Graph();
		void addEdge(std::string v1, std::string v2, int weight);
		void addVertex(std::string name);
		void displayEdges();
		void Dijkstra(std::string sourceVertex, std::string destinationVertex);
	private:
		//vector<edge> edges;
		std::vector<vertex> vertices;

};

Graph::Graph(){}

Graph::~Graph(){}

void Graph::addVertex(std::string n){
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

void Graph::addEdge(std::string v1, std::string v2, int weight){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == v1){
			for(int j = 0; j < vertices.size(); j++){
				if(vertices[j].name == v2 && i != j){
					adjVertex av;
					av.v = &vertices[j];
					av.weight = weight;
					vertices[i].adj.push_back(av);
					//another vertex for edge in other direction
					//adjVertex av2;
					//av2.v = &vertices[i];
					//av2.weight = weight;
					//vertices[j].adj.push_back(av2);
				}
			}
		}
	}
}

//loop through all vertices and adjacent vertices
void Graph::displayEdges(){
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

void Graph::Dijkstra(std::string starting, std::string destination){
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
		std::cout<<"pushing "<<start->name<<" into solved"<<std::endl;
		std::vector<vertex *> solved;
		std::vector<vertex *> path;
		solved.push_back(start);
		//path.push_back(start);
		adjVertex * v;
		vertex * u;
		vertex * minVertex;
		vertex * prev;
		while (ending->visited == false) {
			int minDistance = INT_MAX;
			for (int i = 0; i < solved.size(); i++) {
				u = solved[i];
				std::cout<<std::endl;
				std::cout<<"Inspecting route from "<<u->name<<std::endl;
				for (int j = 0; j < u->adj.size(); j++) {
					v = &solved[i]->adj[j];
					std::cout<<"-> to "<<v->v->name;
					if (v->v->visited == false) {
						std::cout<<", not yet solved,";
						int dist = u->distance + v->weight;
						if (dist < minDistance) {
							std::cout<<" the minimum distance was "<<minDistance;
							minDistance = dist;
							minVertex = v->v;
							prev = u;
							std::cout<<" but there is a new minimum distance of "<<dist<<" between "
							<<start->name <<" and "<<minVertex->name<<std::endl;
						}else{std::cout<<" the minimum distance is "<<minDistance
							<<" and there is not a new minimum distance "<<dist<<std::endl;}
					}else{
						std::cout<<" already solved, moving on"<<std::endl;
					}
				}
			}
			solved.push_back(minVertex);
			std::cout<<std::endl;
			std::cout<<"pushing "<<minVertex->name<<" into solved ";
			minVertex->distance = minDistance;
			minVertex->previous = prev;
			minVertex->visited = true;
			std::cout<<minVertex->name;
			std::cout<<"(distance: "<<minVertex->distance
			<<", visited: "<<minVertex->visited
			<<", parent: "<<minVertex->previous->name<<")"<<std::endl;
			std::cout<<"destination "<<ending->name<<" solved? "<<ending->visited<<std::endl;
			std::cout<<std::endl;
		}
		std::cout<<"Shortest Path"<<std::endl;
		vertex * vert = ending;
		while (vert != nullptr) {
			path.push_back(vert);
			vert = vert->previous;
		}
		for (int i = 0; i < path.size(); i++) {
			if (i == path.size()-1)
				std::cout<<path[path.size()-1-i]->name;
			else
				std::cout<<path[path.size()-1-i]->name<<" - ";
		}
		std::cout<<std::endl;
		std::cout<<"Minimum Distance: "<<solved[solved.size()-1]->distance<<std::endl;
	}else if (ending!=nullptr){
		std::cout<<"start not found"<<std::endl;
		exit(1);
	}else{
		std::cout<<"ending not found"<<std::endl;
		exit(1);
	}
}

//HEADER
struct Movie{
	std::string name; //stores name of movie
	std::string rank; //stores movie ranking on IMDB
	std::string year; //stores year released
	int quantity; //stores quantity in stock
	Movie *parent; //stores address of parent
	Movie *left; //stores address of left child
	Movie *right; //stores address of right child
	Movie(std::string n, std::string rk, std::string y, int q, Movie *p, Movie *l, Movie *r): name(n), rank(rk), year(y), quantity(q), parent(p), left(l), right(r){}; //allows for easy definition
};

class MovieTree
{
	private:
		int count;
		Movie *root;
		Movie *searchRecursive(Movie *startMovie, std::string searchName);
		Movie *insertRecursive(Movie *parent, Movie *root, std::string newName, std::string newRank, std::string newYear, int newQuantity);
		Movie *deleteRecursive(Movie *startMovie, std::string deleteName);
		Movie *minRecursive(Movie *startMovie);
		void deleteAllRecursive(Movie *startMovie);
		void printRecursive(Movie *startMovie);
		void countRecursive(Movie *startMovie);
	public:
		MovieTree();
		~MovieTree();
		void build(std::string filename);
		void search(std::string searchName);
		void print();
		int countTree();
		void rent(std::string rentName);
		void deleteMovie(std::string deleteName);
		void deleteAll();
};

//IMPLEMENTATION

//constructor: initialize root as NULL
MovieTree::MovieTree(){
	root = NULL;
}

//destructor: deletes entire tree
MovieTree::~MovieTree(){
	deleteAll();
}


//user accessible rent function.
void MovieTree::rent(std::string rentName){
	Movie *rentMovie;
	rentMovie=searchRecursive(root, rentName); //search entire treee for movie to be rented
	if(rentMovie==NULL){ //if movie not found, say so.
		std::cout<<"Movie not found."<<std::endl;
	}else{ //otherwise, decrement the quantity of the movie and print its updated information
		rentMovie->quantity--;
		std::cout << "Movie has been rented." << std::endl;
		std::cout << "Movie Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking:" << rentMovie->rank << std::endl;
		std::cout << "Title:" << rentMovie->name << std::endl;
		std::cout << "Year:" << rentMovie->year << std::endl;
		std::cout << "Quantity:" << rentMovie->quantity << std::endl;
		if(rentMovie->quantity==0){ //if the quantity of movie reaches zero, delete it
			deleteRecursive(root,rentMovie->name);
		}
	}
}

//no user accessible count function.
void MovieTree::countRecursive(Movie *startMovie){
	if(startMovie->left!=NULL){ //uses inorder traversal to count the number of nodes in the tree.
		countRecursive(startMovie->left);
	}
	count++;
	if(startMovie->right!=NULL){
		countRecursive(startMovie->right);
	}
}

//user accessible count function.
int MovieTree::countTree(){
	count = 0; //reset count each time in case the tree changes.
	countRecursive(root); //count each node in tree.
	return count;
}

//non user accessible print tree function.
void MovieTree::printRecursive(Movie *startMovie){
	if(startMovie->left!=NULL){ //uses inorder traversal to print the name and quantity of each node in the tree in alphabetcal order.
		printRecursive(startMovie->left);
	}
	std::cout<<"Movie: "<<startMovie->name<<" "<<startMovie->quantity<<std::endl;
	if(startMovie->right!=NULL){
		printRecursive(startMovie->right);
	}
}

//user accessible print tree function. root is hidden.
void MovieTree::print(){
	return printRecursive(root);
}

//uses text file to build tree
void MovieTree::build(std::string filename){
	std::string newRank, newName, newYear, nQ;
	int newQuantity;
	std::ifstream myfile(filename);
	if(myfile.is_open()){
		while(std::getline(myfile,newRank,',')){ //keep reading until end of file
			if(root==NULL){ //create first node in tree
				std::getline(myfile,newName,',');
				std::getline(myfile,newYear,',');
				std::getline(myfile,nQ,'\n');
				newQuantity = std::stoi(nQ); //convert quanitity into integer for easy decrementing
				root = insertRecursive(NULL,NULL,newName,newRank,newYear,newQuantity); //pass root = null to specify new tree
			}else{ //create all other nodes
				std::getline(myfile,newName,',');
				std::getline(myfile,newYear,',');
				std::getline(myfile,nQ,'\n');
				newQuantity = std::stoi(nQ);
				insertRecursive(NULL,root,newName,newRank,newYear,newQuantity); //create new node using root of tree and parsed values
			}
		}
	myfile.close();
	}else std::cout<<"Unable to open file"<<std::endl;
}

//recursively insert new movies into tree
Movie* MovieTree::insertRecursive(Movie *tparent, Movie *troot, std::string newName, std::string newRank, std::string newYear, int newQuantity){
	if(troot==NULL){ //if end of tree is reached, insert new movie
		troot = new Movie(newName,newRank,newYear,newQuantity,tparent,NULL,NULL);
	}
	else if(newName.compare(troot->name)<0){ //if newName is alphabetically smaller than current name, traverse left
		troot->left=insertRecursive(troot,troot->left,newName,newRank,newYear,newQuantity);
	}
	else{ //if newName is alphabetically larger than the current name, traverse right
		troot->right=insertRecursive(troot,troot->right,newName,newRank,newYear,newQuantity);
	}
	return troot; //always return the address of the new movie to be inserted into end of tree
}

//non user accessible recursive function to find the minimum of a tree.
Movie* MovieTree::minRecursive(Movie *startMovie){
	while(startMovie->left != NULL){ //keep traversing left until leaf reached. leaf is minimum.
		startMovie = startMovie->left;
	}return startMovie;
}

//user accessible recursive delete function.
void MovieTree::deleteMovie(std::string deleteName){
	Movie *deleted = searchRecursive(root, deleteName);
	if(deleted==NULL){ //check if movie exists
		std::cout<<"Movie not found."<<std::endl;
	}else{ //only attempt to delete if movie does exist.
		deleted = deleteRecursive(root, deleteName);
	}
}


//non user accessible recursive delete function.
Movie* MovieTree::deleteRecursive(Movie *startMovie, std::string deleteName){
	if(startMovie==NULL)return startMovie; //if tree empty, return null
	else if(deleteName.compare(startMovie->name)<0){ //traverse left and right respectively until found node to be deleted.
		startMovie->left = deleteRecursive(startMovie->left,deleteName);
	}else if(deleteName.compare(startMovie->name)>0){
		startMovie->right = deleteRecursive(startMovie->right, deleteName);
	}else{
		//Leaf. No children.
		if(startMovie->left == NULL && startMovie->right == NULL){ //easiest case: delete leaf.
			delete startMovie; //delete leaf
			startMovie = NULL; //reset pointer
		}else if(startMovie->left==NULL){ //1 child on right //middle case: determine if has left or right child, then shift child up appropriately before deleting node. 
			Movie *tmp = startMovie;
			startMovie = startMovie->right;
			delete tmp;
		}else if(startMovie->right==NULL){ //1 child on left
			Movie *tmp = startMovie;
			startMovie = startMovie->left;
			delete tmp;
		}else{ //2 children
			Movie *tmp = minRecursive(startMovie->right); //most difficult case: find the minimum right value in the tree
			startMovie->name = tmp->name; //replace current node with min right value below root.
			startMovie->rank = tmp->rank;
			startMovie->year = tmp->year;
			startMovie->quantity = tmp->quantity;
			startMovie->right = deleteRecursive(startMovie->right,tmp->name); //now just like deleting a node with one child. delete the min right node using recursion. this effectively shifts the right side of the current node up one node, while in the process deleting the current node
		}
	}
	return startMovie;
}

//recursively search tree for string "searchName"
Movie* MovieTree::searchRecursive(Movie *startMovie, std::string searchName){
	if(startMovie==NULL)return NULL; //if empty BST, return NULL
	if(startMovie->name==searchName)return startMovie; //if found, return address where found
	else if(searchName.compare(startMovie->name)<0) //if name > searchName, searchName must be in the left branch of the tree
		return searchRecursive(startMovie->left,searchName); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return searchRecursive(startMovie->right, searchName); //continue searching right of tree
}

//recursively search accessible by user. hides access to root.
void MovieTree::search(std::string searchName){
	Movie *foundMovie;
	foundMovie = searchRecursive(root, searchName);
	if(foundMovie==NULL){ //if move not found, say so
		std::cout<<"Movie not found."<<std::endl;
	}else{ //otherwise display information of found node
		std::cout<<"Movie Info:"<<std::endl;
		std::cout<<"==========="<<std::endl;
		std::cout<<"Ranking:"<<foundMovie->rank<<std::endl;
		std::cout<<"Title:"<<foundMovie->name<<std::endl;
		std::cout<<"Year:"<<foundMovie->year<<std::endl;
		std::cout<<"Quantity:"<<foundMovie->quantity<<std::endl;
	}
}

//non user accessible recursive delete ALL function.
void MovieTree::deleteAllRecursive(Movie *startMovie){
	if(startMovie->left!=NULL){ //delete all nodes using postorder traversal
		deleteAllRecursive(startMovie->left);
	}
	if(startMovie->right!=NULL){
		deleteAllRecursive(startMovie->right);
	}
	std::cout<<"Deleting: "<<startMovie->name<<std::endl;
	delete startMovie;
}

//user accessible recursive delete ALL function
void MovieTree::deleteAll(){
	return deleteAllRecursive(root);
}

//DRIVER
int main(int argc, char *argv[]){ //allows text file to be passed from the command line as a command line argument
	std::string filename  = std::string(argv[1]);
	MovieTree myMovieTree;
	myMovieTree.build(filename);
	while(true){ //Display menu
		std::string choice, searchName, rentName, deleteName;
		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Find a movie" << std::endl;
		std::cout << "2. Rent a movie" << std::endl;
		std::cout << "3. Print the inventory" << std::endl;
		std::cout << "4. Delete a movie" << std::endl;
		std::cout << "5. Count the movies" << std::endl;
		std::cout << "6. Quit" << std::endl;
		std::getline(std::cin,choice);

		if(choice=="1"){ //Find a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,searchName);
			myMovieTree.search(searchName);
		}
		else if(choice=="2"){ //Rent a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,rentName);
			myMovieTree.rent(rentName);
		}
		else if(choice=="3"){ //Print the inventory
			myMovieTree.print();
		}
		else if(choice=="4"){ //Delete a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,deleteName);
			myMovieTree.deleteMovie(deleteName);
		}
		else if(choice=="5"){ //Count the movies
			std::cout<<"Tree contains: "<<myMovieTree.countTree()<<" movies."<<std::endl;
		}
		else{ //Quit
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
	}
	return 0;
}
