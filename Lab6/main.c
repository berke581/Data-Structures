#include <stdio.h>
#include <stdlib.h>


typedef struct binarySearchTree
{
	int id;
	int mark;
	struct binarySearchTree* left;
	struct binarySearchTree* right;
}BinarySearchTree;


// Auxiliary queue for level order traversal
typedef struct queue
{
	BinarySearchTree* node;
	BinarySearchTree* parent;
	struct queue* next;
}Queue;


// BST related functions
void insert(BinarySearchTree** root, int id, int mark);
void traverseInOrder(BinarySearchTree* root);
void traverseLevelOrder(BinarySearchTree* root);


// Queue related functions
void enqueue(Queue** head, Queue** tail, BinarySearchTree* node, BinarySearchTree* parentNode, int* size);
BinarySearchTree* dequeue(Queue** head, Queue** tail, int* size);


int main() {
	BinarySearchTree* root = NULL;
	
	// Getting inputs and inserting them to the BST
	int id, mark;
	scanf("%d", &id);
	while (id != -1)
	{
		scanf("%d", &mark);
		insert(&root, id, mark);
		scanf("%d",& id);
	}

	traverseInOrder(root);
	printf("\n");
	traverseLevelOrder(root);

	return 0;
}


//


void insert(BinarySearchTree** root, int id, int mark)
{
	if (*root == NULL)
	{
		BinarySearchTree* newNode = (BinarySearchTree*)malloc(sizeof(BinarySearchTree) * 1);
		newNode->id = id;
		newNode->mark = mark;
		newNode->left = NULL;
		newNode->right = NULL;
		*root = newNode;
	}
	else if ((*root)->mark > mark)
	{
		insert(&(*root)->left, id, mark);
	}
	else
	{
		insert(&(*root)->right, id, mark);
	}
}

void traverseInOrder(BinarySearchTree* root)
{
	if (root != NULL)
	{
		traverseInOrder(root->left);
		printf("%d %d\n", root->id, root->mark);
		traverseInOrder(root->right);
	}
}


void traverseLevelOrder(BinarySearchTree* root)
{
	if (root == NULL)
		return;
	
	Queue* head = NULL;
	Queue* tail = NULL;
	int queueSize = 0;
	
	enqueue(&head, &tail, root, NULL, &queueSize);
	
	while (1)
	{
		int size = queueSize;
		if (size == 0)
			break;
		
		while (size > 0)
		{
			BinarySearchTree* parent = head->parent;
			BinarySearchTree* currentNode = dequeue(&head, &tail, &queueSize);
			
			if (currentNode == NULL)
				break;
			
			if (parent == NULL)
			{
				printf("%d %d", currentNode->id, currentNode->mark);
			}
			else
			{
				if (parent->mark > currentNode->mark)
					printf("%d %d (%d L)", currentNode->id, currentNode->mark, parent->mark);
				else
					printf("%d %d (%d R)", currentNode->id, currentNode->mark, parent->mark);
					
				if (size > 1)
					printf(" ");
			}
			
			if (currentNode->left != NULL)
				enqueue(&head, &tail, currentNode->left, currentNode, &queueSize);
			
			if (currentNode->right != NULL)
				enqueue(&head, &tail, currentNode->right, currentNode, &queueSize);
			
			--size;
		}
		printf("\n");
	}
}


//


void enqueue(Queue** head, Queue** tail, BinarySearchTree* node, BinarySearchTree* parentNode, int* size)
{
	Queue* newPtr = (Queue*)malloc(sizeof(Queue) * 1);
	newPtr->node = node;
	newPtr->parent = parentNode;
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

BinarySearchTree* dequeue(Queue** head, Queue** tail, int* size)
{
	if (*head == NULL)
		return NULL;

	Queue* temp = *head;
	BinarySearchTree* res = temp->node;
	*head = (*head)->next;
	free(temp);
	
	*size = *size - 1;

	if (*head == NULL)
		*tail = NULL;
	
	return res;
}

