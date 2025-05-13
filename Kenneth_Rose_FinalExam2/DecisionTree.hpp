#pragma once
/*
* Coder: Kenneth Rose
* Purpose: Base structure and logic for the binary decision tree to evaluate going to the gym
* Date: April 24th, 2025
*/

#include <iostream>
#include <string>


struct Node
{
	void(*function)(Node*&);
	Node* left;
	Node* right;

	Node(void(*func)(Node*&)) : function(func), left(nullptr), right(nullptr) {}

};

class DecisionTree
{
private:
	Node* root;

public:
	DecisionTree() :root(nullptr) {}
	~DecisionTree() { deleteTree(root); }

	void buildTree()
	{
		//leaf Ndoes
		Node* goToGymSick = new Node(&goToGym);
		Node* restSick = new Node(&rest);
		Node* eatNode = new Node(&eat);
		Node* restTired = new Node(&rest);
		Node* gymHealthy = new Node(&goToGym);

		// Decision Nodes
		Node* sickNode = new Node(&feelSick);
		sickNode->left = restSick;
		sickNode->right = goToGymSick;

		Node* hungryNode = new Node(&feelHungry);
		hungryNode->left = eatNode;
		hungryNode->right = sickNode;
		
		Node* tiredNode = new Node(&feeltired);
		tiredNode->left = restTired;
		tiredNode->right = hungryNode;

		// root Node
		root = new Node(&feelHealthy);
		root->left = gymHealthy;
		root->right = tiredNode;
	}

	void navigateTree()
	{
		Node* currentNode = root;
		while (currentNode != nullptr)
		{
			currentNode->function(currentNode);
		}
	}


private:

	//Decision Node
	static void feelHealthy(Node*& currentNode)
	{
		askQuestion("Do I feel healthy? ", currentNode->left, currentNode->right, currentNode);
	}

	static void feeltired(Node*& currentNode)
	{
		askQuestion("Do I feel tired? ", currentNode->left, currentNode->right, currentNode);
	}

	static void feelHungry(Node*& currentNode)
	{
		askQuestion("Do I feel hungry? ", currentNode->left, currentNode->right, currentNode);
	}


	static void feelSick(Node*& currentNode)
	{
		askQuestion("Do I feel sick? ", currentNode->left, currentNode->right, currentNode);
	}


	//leaf Node
	static void goToGym(Node*& currentNode)
	{
		printDecision("Go To Gym", currentNode);
	}

	static void rest(Node*& currentNode)
	{
		printDecision("Rest", currentNode);
	}

	static void eat(Node*& currentNode)
	{
		printDecision("Eat", currentNode);
	}

	static void askQuestion(std::string question, Node* yesNode, Node* noNode, Node*& currentNode)
	{
		//print question to user\
		//get response
		std::cout << question << "(1==Yes, 0==N0)? ";
		int input;
		std::cin >> input;

		//test yes or no
		//send to appropriate node
		if (input == 1)
		{
			currentNode = yesNode;
		}
		else if (input == 0)
		{
			currentNode = noNode;
		}
	}

	static void printDecision(std::string decision, Node*& currentNode)
	{
		
		std::cout << decision << std::endl;
		currentNode = nullptr;
		
		
		
	}

	static void deleteTree(Node* node)
	{
		if (!node) return;
		deleteTree(node->left);
		deleteTree(node->right);

		delete node;
	}
};