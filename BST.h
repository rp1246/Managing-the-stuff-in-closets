/*
Name:Raj Phuyal
Compiler Used:GCC
Program Description:In this project, We write a program that implements and manages several user defined BST's where each BST's will represent a container and inventory of item it stores.
#I used some of the code from my previous projects that I could use in this one.
*/


#include <string>
#include <vector>

using namespace std;
//define item in the BST
class Node {
public:
   string item;
   int count;
   struct Node *leftChild;
   struct Node *rightChild;
   Node() {
		item = "";
		count = 0;
		leftChild = rightChild = NULL;
   }
};
// define BST
class BST {
public:
	string name;
	Node * root;
	BST() {
		name = "";
		root = NULL;
	}
	~BST () {
	}
};
//define Container for BSTs
class Container {
private:
	vector<BST> containers;
	//check existence of container and return index number if exist or -1 if not
	int existContainer(string container);
	// find Item in the "id"th container
	Node * findItem(int id, string item);
	// implement in-order traversal of BST
	void inorder_traversal(Node* root);
	// implement pre-order traversal of BST
	void pre_order_traversal(Node* root);
	// implement post-order traversal of BST
	void post_order_traversal(Node* root);
	// remove item in the BST
	void remove(string item, Node* node);
	Node* findMin(Node* node);
public:
	Container() {}
	~Container() {}
	// displays the contents of the specified container by given type
	void display(string type, string container);
	// searches each container for the specified item
	void find_item(string item);
	// searches the given container for the specified item
	void find_item_in(string item, string container);
	// Removes the specified item from each container
	void remove_item(string item);
	// Removes the specified item from the given container
	void remove_item_from(string item, string container);
	// Inserts count of the specified item into the given container
	// if already exist, update the item count through addition
	void insert_item_into(string item, int count, string container);
	// Creates the specified container and adds it to the list of containers
	void create(string container);
	// Destroys the specified container and its contents
	void destroy(string container);
};
