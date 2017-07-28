/*
*CSCI2270 CS2:Data Structures
*Author: Micah Zhang
*Date: July 28th, 2017
*Final Project
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <climits>
#include <vector>
#include "StarlinerIndustries.hpp"

//must initialize all 3 roots as NULL otherwise insertRecursive fails
StarlinerIndustries::StarlinerIndustries(){
	root = NULL;
	froot = NULL;
	croot = NULL;
}

//delete all upon program exiting
StarlinerIndustries::~StarlinerIndustries(){
	deleteAll();
}

//Graphs implementation

//adds vertex to graph. Code taken from Shirly's graphs implementation code on Moodle
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

//adds edge to graph. Code taken from Shirly's graphs implementation code on Moodle
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
//Code taken from textbook.
void StarlinerIndustries::printGraph(){
	for(int x = 0; x < vertices.size();x++){
		std::cout<<vertices[x].name<<"-->";
		for(int y = 0; y < vertices[x].adj.size(); y++){
			std::cout<<vertices[x].adj[y].v->name<<" ";
		}
		std::cout<<"\n";
	}
}

//Uses Dijkstra's algorithm to find and print the shortest path between two nodes. Code taken from Shirly's implementation file on Moodle
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
    if (start != nullptr && ending != nullptr)
    {
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
      std::cout<<"Shortest Path:"<<std::endl; //display to user shortest path between two planets
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
      std::cout<<"Minimum Distance: "<<solved[solved.size()-1]->distance<<std::endl; //display minimum distance between 2 planets
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
	Rocket *rentRocket, *frentRocket, *crentRocket;
	rentRocket=nameSearchRecursive(root, rentName); //search entire tree for rocket to be rented
	if(rentRocket==NULL){ //if rocket not found, say so.
		std::cout<<"Rocket not found."<<std::endl;
	}else{ //otherwise, decrement the quantity of the rocket from all three trees and and print its updated information
		frentRocket = fuelSearchRecursive(froot, rentRocket->fuel);
		crentRocket = capacitySearchRecursive(croot, rentRocket->capacity);
		rentRocket->quantity--;
		frentRocket->quantity--;
		crentRocket->quantity--;
		std::cout << "Rocket has been rented." << std::endl;
		std::cout << "Rocket Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Name:" << rentRocket->name << std::endl;
		std::cout << "Fuel:" << rentRocket->fuel << std::endl;
		std::cout << "Capacity:" << rentRocket->capacity << std::endl;
		std::cout << "Quantity:" << rentRocket->quantity << std::endl;
		if(rentRocket->quantity==0){ //if the quantity of rocket reaches zero, delete it from all three trees
			deleteRecursive(root,rentRocket->name);
			fuelDeleteRecursive(froot, rentRocket->fuel);
			capacityDeleteRecursive(croot, rentRocket->capacity);
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
			froot = fuelInsertRecursive(NULL,froot,newName,newFuel,newCapacity,newQuantity); //built three trees, each ordered using a different property of the rocket
			croot = capacityInsertRecursive(NULL,croot,newName,newFuel,newCapacity,newQuantity);
		}
	myfile.close();
	}else std::cout<<"Unable to open file"<<std::endl;
}

//recursively insert new rockets into capacity tree
Rocket* StarlinerIndustries::capacityInsertRecursive(Rocket *tparent, Rocket *troot, std::string newName, int newFuel, int newCapacity, int newQuantity){
	if(troot==NULL){ //if end of tree is reached, insert new rocket
		troot = new Rocket(newName,newFuel,newCapacity,newQuantity,tparent,NULL,NULL);
	}
	else if(newCapacity < troot->capacity){ //if newName is alphabetically smaller than current name, traverse left
		troot->left=capacityInsertRecursive(troot,troot->left,newName,newFuel,newCapacity,newQuantity);
	}
	else{ //if newName is alphabetically larger than the current name, traverse right
		troot->right=capacityInsertRecursive(troot,troot->right,newName,newFuel,newCapacity,newQuantity);
	}
	return troot; //always return the address of the new movie to be inserted into end of tree
}

//recursively insert new rockets into fuel tree
Rocket* StarlinerIndustries::fuelInsertRecursive(Rocket *tparent, Rocket *troot, std::string newName, int newFuel, int newCapacity, int newQuantity){
	if(troot==NULL){ //if end of tree is reached, insert new rocket
		troot = new Rocket(newName,newFuel,newCapacity,newQuantity,tparent,NULL,NULL);
	}
	else if(newFuel < troot->fuel){ //if newName is alphabetically smaller than current name, traverse left
		troot->left=fuelInsertRecursive(troot,troot->left,newName,newFuel,newCapacity,newQuantity);
	}
	else{ //if newName is alphabetically larger than the current name, traverse right
		troot->right=fuelInsertRecursive(troot,troot->right,newName,newFuel,newCapacity,newQuantity);
	}
	return troot; //always return the address of the new rocket to be inserted into end of tree
}

//recursively insert new rockets into name tree
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

//non user accessible function to find the maxmium of a tree
Rocket *StarlinerIndustries::maxRecursive(Rocket *startRocket){
	while(startRocket->right != NULL){
		startRocket = startRocket->right;
	}return startRocket;
}

//user accessible recursive delete function.
void StarlinerIndustries::deleteRocket(std::string deleteName){
	Rocket *deleted = nameSearchRecursive(root, deleteName);
	if(deleted==NULL){
		std::cout<<"Rocket not found."<<std::endl;
	}else{
		Rocket *ndeleted = deleteRecursive(root, deleted->name);
		Rocket *fdeleted = fuelDeleteRecursive(froot, deleted->fuel);
		Rocket *cdeleted = fuelDeleteRecursive(croot, deleted->capacity);
	}
}


//non user accessible recursive delete function for name tree.
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

//deletes node from fuel tree
Rocket* StarlinerIndustries::fuelDeleteRecursive(Rocket *startRocket, int deleteFuel){
	if(startRocket==NULL)return startRocket; //if tree empty, return null
	else if(deleteFuel < startRocket->fuel){ //traverse left and right respectively until found node to be deleted.
		startRocket->left = fuelDeleteRecursive(startRocket->left,deleteFuel);
	}else if(deleteFuel > startRocket->fuel){
		startRocket->right = fuelDeleteRecursive(startRocket->right, deleteFuel);
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
			startRocket->right = fuelDeleteRecursive(startRocket->right,tmp->fuel); //now just like deleting a node with one child. delete the min right node using recursion. this effectively shifts the right side of the current node up one node, while in the process deleting the current node
		}
	}
	return startRocket;
}

//deletes node from capacity tree
Rocket* StarlinerIndustries::capacityDeleteRecursive(Rocket *startRocket, int deleteCapacity){
	if(startRocket==NULL)return startRocket; //if tree empty, return null
	else if(deleteCapacity < startRocket->capacity){ //traverse left and right respectively until found node to be deleted.
		startRocket->left = capacityDeleteRecursive(startRocket->left,deleteCapacity);
	}else if(deleteCapacity > startRocket->capacity){
		startRocket->right = capacityDeleteRecursive(startRocket->right, deleteCapacity);
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
			startRocket->right = capacityDeleteRecursive(startRocket->right,tmp->capacity); //now just like deleting a node with one child. delete the min right node using recursion. this effectively shifts the right side of the current node up one node, while in the process deleting the current node
		}
	}
	return startRocket;
}


//recursively search name tree for string "searchName"
Rocket* StarlinerIndustries::nameSearchRecursive(Rocket *startRocket, std::string searchName){
	if(startRocket==NULL)return NULL; //if empty BST, return NULL
	if(startRocket->name==searchName)return startRocket; //if found, return address where found
	else if(searchName.compare(startRocket->name)<0) //if name > searchName, searchName must be in the left branch of the tree
		return nameSearchRecursive(startRocket->left,searchName); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return nameSearchRecursive(startRocket->right, searchName); //continue searching right of tree
}

//recursively search fuel tree for int "searchFuel"
Rocket* StarlinerIndustries::fuelSearchRecursive(Rocket *startRocket, int searchFuel){
	if(startRocket==NULL)return NULL; //if empty BST, return NULL
	if(startRocket->fuel==searchFuel)return startRocket; //if found, return address where found
	else if(searchFuel < startRocket->fuel) //if name > searchName, searchName must be in the left branch of the tree
		return fuelSearchRecursive(startRocket->left,searchFuel); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return fuelSearchRecursive(startRocket->right, searchFuel); //continue searching right of tree
}

//recursively search capacity tree for int "searchCapacity"
Rocket* StarlinerIndustries::capacitySearchRecursive(Rocket *startRocket, int searchCapacity){
	if(startRocket==NULL)return NULL; //if empty BST, return NULL
	if(startRocket->capacity==searchCapacity)return startRocket; //if found, return address where found
	else if(searchCapacity < startRocket->capacity) //if name > searchName, searchName must be in the left branch of the tree
		return capacitySearchRecursive(startRocket->left,searchCapacity); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return capacitySearchRecursive(startRocket->right, searchCapacity); //continue searching right of tree
}


//recursively search accessible by user for name tree. hides access to root.
void StarlinerIndustries::nameSearch(std::string searchName){
	Rocket *foundRocket;
	foundRocket = nameSearchRecursive(root, searchName);
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

//finds the rocket that meets both the minimum fuel and minimum passenger capacity with the least excess
void StarlinerIndustries::optimizeRocket(int minFuel, int minCapacity){
	bool found = false;
	Rocket *foundFuel = NULL;
	Rocket *foundCapacity = NULL;
	Rocket *maxFuel = maxRecursive(froot); //find the max fuel
	Rocket *maxCapacity = maxRecursive(croot); //find the max capacity
	for(int i = minFuel; i<=maxFuel->fuel; i++){ //iterate through each node in the fuel tree
		foundFuel = fuelSearchRecursive(froot,i); //search for min fuel
		for(int j = minCapacity; j<=maxCapacity->capacity; j++){ //iterate through each node in tne capacity tree
			foundCapacity = capacitySearchRecursive(croot,j); //search for min capacity
			if((foundFuel!=NULL) && (foundCapacity!=NULL) && (foundFuel->name == foundCapacity->name)){ //keep increase the two mins and iterating until they match up. if so, then both fuel and capacity have been optimized. return.
				found = true;
				break;
			}
		}
		if(found){
			break;
		}

	}
	if((foundFuel!=NULL) && (foundCapacity!=NULL) && (foundFuel->name == foundCapacity->name)){ //if optimal rocket found, tell user
		std::cout<<"We recommend the "<<foundFuel->name<<", which has fuel capacity of "<<foundFuel->fuel<<" units"<<" and a passenger capacity of "<< foundCapacity->capacity << " people." << std::endl;
	}else{ //if optimal rocket not found, tell user
		std::cout<<"Sorry, we do not have any rockets with the fuel capacity or passenger capacity that you require."<<std::endl;
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
	deleteAllRecursive(root); //delete all nodes from all three nodes
	fdeleteAllRecursive(croot);
	return fdeleteAllRecursive(froot);
}

//non user accessible recursive delete ALL function. NO PRINT STATEMENTS
void StarlinerIndustries::fdeleteAllRecursive(Rocket *startRocket){
	if(startRocket == NULL){
		return;
	}
	if(startRocket->left!=NULL){ //delete all nodes using postorder traversal
		deleteAllRecursive(startRocket->left);
	}
	if(startRocket->right!=NULL){
		deleteAllRecursive(startRocket->right);
	}
	delete startRocket;
}
