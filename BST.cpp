/*
Name:Raj Phuyal
Compiler Used:GCC
Program Description: In this project, We write a program that implements and manages several user defined BST's where each BST's will represent a container and inventory of item it stores.

*/


#include "BST.h"
#include <iostream>

using namespace std;
// displays the contents of the specified container by given type
void Container::display(string type, string container) {
	int id;
	id = existContainer(container);
	if (id == -1) {
		cout << ">> Container " << container << " doesn't exist." << endl;
		return ;
	}
	cout << ">> Container: " << container << endl;
	if (type == "in") {
		inorder_traversal(containers[id].root);
	} else if (type == "pre") {
		pre_order_traversal(containers[id].root);
	} else {
		post_order_traversal(containers[id].root);
	}
}
// implement in-order traversal of BST
void Container::inorder_traversal(Node* root) {
   if(root != NULL) {
      inorder_traversal(root->leftChild);
      cout << "Item Name: " << root->item << " Item Count: " << root->count << endl;
      inorder_traversal(root->rightChild);
   }
}
// implement pre-order traversal of BST
void Container::pre_order_traversal(Node* root) {
   if(root != NULL) {
      cout << "Item Name: " << root->item << " Item Count: " << root->count << endl;
      pre_order_traversal(root->leftChild);
      pre_order_traversal(root->rightChild);
   }
}
// implement post-order traversal of BST
void Container::post_order_traversal(Node* root) {
   if(root != NULL) {
      post_order_traversal(root->leftChild);
      post_order_traversal(root->rightChild);
      cout << "Item Name: " << root->item << " Item Count: " << root->count << endl;
   }
}
// searches each container for the specified item
void Container::find_item(string item){
	int i;
	for (i = 0; i < containers.size(); i++) {
		Node * findNode;
		findNode = findItem(i, item);
		if (findNode == NULL) {
			cout << ">> Item not found in Container " << containers[i].name << "." << endl;
		} else {
			cout << ">> Item found in Container " << containers[i].name << "." << endl;
			cout << "	Item Name: " << findNode->item << endl;
			cout << "	Item Count: " << findNode->count << endl;
		}
	}
}
// Removes the specified item from each container
void Container::find_item_in(string item, string container) {
	int id;
	id = existContainer(container);
	if (id == -1) {
		cout << ">> Container " << container << " doesn't exist." << endl;
		return ;
	}
	
	Node *findNode;
	findNode = findItem(id, item);
	if (findNode != NULL ) {
		cout << ">> Item found in Container " << container << "." << endl;
		cout << "	Item Name: " << findNode->item << endl;
		cout << "	Item Count: " << findNode->count << endl;
	} else {
		cout << ">> Item not found in Container " << container << "." << endl;
	}
}
// Removes the specified item from each container
void Container::remove_item(string item){
	int i;
	for (i = 0; i < containers.size(); i++) {
		remove_item_from(item, containers[i].name);
	}
}
// Removes the specified item from the given container
void Container::remove_item_from(string item, string container) {
	int id;
	id = existContainer(container);
	if (id == -1) {
		cout << ">> Container " << container << " doesn't exist." << endl;
		return ;
	}
	remove(item, containers[id].root);
}

Node* Container::findMin(Node* node) {
	if( node == NULL )
		return NULL;
	else if( node->leftChild == NULL )
		return node;
	return findMin( node->leftChild );
}

Node * parent = new Node (); 
// remove item in the BST
void Container::remove(string item, Node* node) {
	if( node == NULL )
		return;
	else if( item < node->item) {
		parent = node;
		remove( item, node->leftChild );
	}
	else if( item > node->item ) {
		parent = node;
		remove( item, node->rightChild );
	}
	else if( node->leftChild != NULL && node->rightChild != NULL ) {
		node->item = ( item = findMin(node->rightChild)->item );
		node->count = findMin(node->rightChild)->count;
		parent = node;
		remove( item, node->rightChild );
	} else {
		if (parent->rightChild == node) {
			parent->rightChild = ( node->leftChild != NULL ? node->leftChild : node->rightChild );
		}
		if (parent->leftChild == node) {
			parent->leftChild = ( node->leftChild != NULL ? node->leftChild : node->rightChild );
		}
	}
}
// Inserts count of the specified item into the given container
// if already exist, update the item count through addition
void Container::insert_item_into(string item, int count, string container) {
	int id, i;
	id = existContainer(container);
	if (id == -1) {
		cout << ">> Container " << container << " doesn't exist." << endl;
		return ;
	}
	
	Node *tempNode = new Node();
   	Node *current = new Node();
	Node *parent = new Node();
	
	tempNode->item = item;
	tempNode->count = count;
	tempNode->leftChild = NULL;
	tempNode->rightChild = NULL;		

	if(containers[id].root == NULL) {
      containers[id].root = tempNode;
   } else {
      current = containers[id].root;
      parent = NULL;

      while(1) { 
         parent = current;
         
         //go to left of the tree
         if(item < parent->item) {
            current = current->leftChild;                
            
            //insert to the left
            if(current == NULL) {
               parent->leftChild = tempNode;
               return;
            }
         }  //go to right of the tree
         else if(item > parent->item) {
            current = current->rightChild;

            //insert to the right
            if(current == NULL) {
               parent->rightChild = tempNode;
               return;
            }
         } else {
         	current->count += count;
         	return;
		 }
      }            
   }
}
// Creates the specified container and adds it to the list of containers
void Container::create(string container) {
	if (existContainer(container) != -1) {
		cout << ">> Container of the same name already exists." << endl;
		return ;
	}
	BST ct;
	ct.name = container;
	containers.push_back(ct);
}
// Destroys the specified container and its contents
void Container::destroy(string container) {
	int id;
	id = existContainer(container);
	if (id == -1) {
		cout << ">> Container of that name does not exist." << endl;
		return ;
	}
	vector<BST>::iterator it = containers.begin();
	for (;id > 0; id--) it ++;
	containers.erase(it);
	cout << ">> Removed Container " << container << " successfully" << endl;
}
//check existence of container and return index number if exist or -1 if not
int Container::existContainer(string container) {
	int i;
	for (i = 0; i < containers.size(); i++) {
		if (containers[i].name == container)
			return i;
	}
	return -1;
}
// find Item in the "id"th container
Node * Container::findItem(int id, string item) {
	Node *current = containers[id].root;
	
	while(current->item != item) {
	
		//go to left tree
		if(current->item > item) {
			current = current->leftChild;
		}
		//else go to right tree
		else {                
			current = current->rightChild;
		}
		
		//not found
		if(current == NULL) {
			return NULL;
		}
	}
	
	return current;
}
