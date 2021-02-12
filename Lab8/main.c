#include <stdio.h>
#include <stdlib.h>


// Node structure to hold node information
typedef struct RBT_Node
{
	int data;
	char color;
	struct RBT_Node* right;
	struct RBT_Node* left;
	struct RBT_Node* parent;
}RBTNode;


// Auxiliary queue for level order traversal
typedef struct queue
{
	RBTNode* node;
	struct queue* next;
}Queue;


// Queue related functions
void enqueue(Queue** head, Queue** tail, RBTNode* node, int* size);
RBTNode* dequeue(Queue** head, Queue** tail, int* size);

// Helper functions to traverse and print the tree
void traverseInOrder(RBTNode* root, RBTNode* leaf);
void traverseLevelOrder(RBTNode* root, RBTNode* leaf);

RBTNode* createRBTNode(int data);
void rotateLL(RBTNode* currentNode);
void rotateRR(RBTNode* currentNode);
void insertRBT(RBTNode* newNode);
void fixInsertionViolations(RBTNode* currentNode);


// Declared root and the leaf node globally
RBTNode* root = NULL;
RBTNode* leaf = NULL;

int main()
{
	// Initialize the node to represent leaf nodes
	leaf = (RBTNode*)malloc(sizeof(RBTNode) * 1);
	leaf->data = -1; // Leaf nodes don't contain data
	leaf->color = 'B'; // B denotes black, leaf nodes are always black
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->parent = NULL;
	
	// Root is leaf when no insertions done
	root = leaf;
	
	int data;
	scanf("%d", &data);
	while (data != -1)
	{
		// Create new node and insert it into red black tree
		RBTNode* newNode = createRBTNode(data);
		insertRBT(newNode);
		scanf("%d", &data);
	}

	traverseInOrder(root, leaf);
	printf("\n");
	traverseLevelOrder(root, leaf);

	return 0;
}


void enqueue(Queue** head, Queue** tail, RBTNode* node, int* size)
{
	Queue* newPtr = (Queue*)malloc(sizeof(Queue) * 1);
	newPtr->node = node;
	newPtr->next = NULL;
	
	*size = *size + 1;

	if (*tail != NULL)
	{
		(*tail)->next = newPtr;
		*tail = newPtr;
	}
	else
	{
		*tail = newPtr;
		*head = *tail;
	}

}

RBTNode* dequeue(Queue** head, Queue** tail, int* size)
{
	if (*head == NULL)
		return NULL;

	Queue* temp = *head;
	RBTNode* res = temp->node;
	*head = (*head)->next;
	free(temp);
	
	*size = *size - 1;

	if (*head == NULL)
		*tail = NULL;
	
	return res;
}


//


void traverseInOrder(RBTNode* root, RBTNode* leaf)
{
	if (root == NULL) return;
	
	// Don't print the leaves
	if (root != leaf)
	{
		traverseInOrder(root->left, leaf);
		printf("%d\n", root->data);
		traverseInOrder(root->right, leaf);
	}
}

void traverseLevelOrder(RBTNode* root, RBTNode* leaf)
{
	if (root == leaf)
		return;
	
	Queue* head = NULL;
	Queue* tail = NULL;
	int queueSize = 0;
	
	enqueue(&head, &tail, root, &queueSize);
	
	while (1)
	{
		int size = queueSize;
		if (size == 0)
			break;
		
		while (size > 0)
		{
			RBTNode* parent = head->node->parent;
			RBTNode* currentNode = dequeue(&head, &tail, &queueSize);
			
			if (currentNode == leaf)
				break;
			
			if (parent == leaf)
			{
				printf("%d %c", currentNode->data, currentNode->color);
			}
			else
			{
				if (parent->data > currentNode->data)
					printf("%d %c (%d L)", currentNode->data, currentNode->color, parent->data);
				else
					printf("%d %c (%d R)", currentNode->data, currentNode->color, parent->data);
					
				if (size > 1)
					printf(" ");
			}
			
			if (currentNode->left != leaf)
				enqueue(&head, &tail, currentNode->left, &queueSize);
			
			if (currentNode->right != leaf)
				enqueue(&head, &tail, currentNode->right, &queueSize);
			
			--size;
		}
		printf("\n");
	}
}


//


RBTNode* createRBTNode(int data)
{
	RBTNode* newNode = (RBTNode*)malloc(sizeof(RBTNode) * 1);
	newNode->data = data;
	newNode->color = 'R'; // R denotes red node color, new created nodes are always red if not root
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

void rotateLL(RBTNode* currentNode)
{
	RBTNode* r = currentNode->right;
	currentNode->right = r->left;
	
	if (r->left != leaf)
		r->left->parent = currentNode;
	
	r->parent = currentNode->parent;
	if (currentNode->parent == leaf)
		root = r;
	else if (currentNode == currentNode->parent->left)
		currentNode->parent->left = r;
	else if (currentNode == currentNode->parent->right)
		currentNode->parent->right = r;
	
	r->left = currentNode;
	currentNode->parent = r;
}

void rotateRR(RBTNode* currentNode)
{
	RBTNode* l = currentNode->left;
	currentNode->left = l->right;
	
	if (l->right != leaf)
		l->right->parent = currentNode;
	
	l->parent = currentNode->parent;
	if (currentNode->parent == leaf)
		root = l;
	else if (currentNode == currentNode->parent->left)
		currentNode->parent->left = l;
	else if (currentNode == currentNode->parent->right)
		currentNode->parent->right = l;
	
	l->right = currentNode;
	currentNode->parent = l;
}

void insertRBT(RBTNode* newNode)
{
	RBTNode* parentOfCurrent = leaf;
	RBTNode* currentNode = root;

	while (currentNode != leaf)
	{
		parentOfCurrent = currentNode;
		
		if (newNode->data < currentNode->data)
			currentNode = currentNode->left;
		else if (newNode->data > currentNode->data)
			currentNode = currentNode->right;
	}
	
	// Update the parent of newNode
	newNode->parent = parentOfCurrent;

	if (parentOfCurrent == leaf) // If the node we are adding is root, currently tree is empty
		root = newNode;
	else if (newNode->data < parentOfCurrent->data)
		parentOfCurrent->left = newNode;
	else if (newNode->data > parentOfCurrent->data)
		parentOfCurrent->right = newNode;

	newNode->right = leaf;
	newNode->left = leaf;

	fixInsertionViolations(newNode);
}

void fixInsertionViolations(RBTNode* currentNode)
{
	while (currentNode->parent->color == 'R')
	{
		// If newNode's parent is left child
		if (currentNode->parent == currentNode->parent->parent->left)
		{
			RBTNode* uncleNode = currentNode->parent->parent->right;
			
			if (uncleNode->color == 'R')
			{
				currentNode->parent->color = 'B';
				uncleNode->color = 'B';
				currentNode->parent->parent->color = 'R';
				currentNode = currentNode->parent->parent;
			}
			else
			{
				if (currentNode == currentNode->parent->right)
				{
					currentNode = currentNode->parent;
					rotateLL(currentNode);
				}
				
				currentNode->parent->color = 'B';
				currentNode->parent->parent->color = 'R';
				rotateRR(currentNode->parent->parent);
			}
		}
		else
		// If newNode's parent is right child
		{
			RBTNode* uncleNode = currentNode->parent->parent->left;
			
			if (uncleNode->color == 'R')
			{
				currentNode->parent->color = 'B';
				uncleNode->color = 'B';
				currentNode->parent->parent->color = 'R';
				currentNode = currentNode->parent->parent;
			}
			else
			{
				if (currentNode == currentNode->parent->left)
				{
					currentNode = currentNode->parent;
					rotateRR(currentNode);
				}
				currentNode->parent->color = 'B';
				currentNode->parent->parent->color = 'R';
				rotateLL(currentNode->parent->parent);
			}
		}
	}
	
	root->color = 'B'; // Root node's color should always be black
}

