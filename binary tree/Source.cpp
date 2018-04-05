#include <fstream> 
#include <math.h>
#include <algorithm>
#include <string>
using namespace std;
ifstream cin("bstsimple.in");
ofstream cout("bstsimple.out");




struct node {
	int key;
	node *left, *right,*parent;
};

node* minimum(node* tree) {
	if (tree->left == NULL)
		return tree;
	return minimum(tree->left);
}

void show(node*tree) {
	if (tree != NULL) {
		show(tree->left);
		cout << tree->key << " ";
		show(tree->right);
	}
}

node* insert(node *tree, int x) {
	if (tree == NULL) {
		tree = new node;
		tree->key = x;
		tree->left = tree->right = NULL;
	}
	else {
		if (x > tree->key) tree->right = insert(tree->right, x);
		if (x < tree->key) tree->left = insert(tree->left, x);
	}
	return tree;
}

bool exists(node* tree, int x) {
	if (tree == NULL) return false;
	else {
		if (x == tree->key) return true;
		if (x < tree->key) return exists(tree->left, x);
		if (x > tree->key) return exists(tree->right, x);
	}
}

void next(node*&tree, int x) {
	node *current = tree, *successor = NULL;
	while (current != NULL)
		if (current->key > x) {
			successor = current;
			current = current->left;
		}
		else {
			current = current->right;
		}
		if (successor == NULL) cout << "none" << endl;
		else cout << successor->key << endl;
}

void pred(node*&tree, int x) {
	node *current = tree, *successor = NULL;
	while (current != NULL)
		if (current->key < x) {
			successor = current;
			current = current->right;
		}
		else {
			current = current->left;
		}
		if (successor == NULL) cout << "none" << endl;
		else cout << successor->key << endl;
}

node *del(node *&root, int a) {
	if (root == NULL) {
		return root;
	}
	if (a < root->key) {
		root->left = del(root->left, a);
	}
	else if (a > root->key) {
		root->right = del(root->right, a);
	}
	else if (root->left != NULL && root->right != NULL) {
		root->key = minimum(root->right)->key;
		root->right = del(root->right, root->key);
	}
	else {
		if (root->left != NULL) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return root;
}


int main() {
	node *root = NULL;
	string s;
	int x;
	while (cin >> s) {
		cin >> x;
		if (s == "insert") root = insert(root, x);
		if (s == "exists") {
			if (exists(root, x)) cout << "true" << endl;
			else cout << "false" << endl;
		}
		if (s == "next") next(root, x);
		if (s == "prev") pred(root, x);
		if (s == "delete") root = del(root, x);
	}
	return 0;

}