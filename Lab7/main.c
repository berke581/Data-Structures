#include <stdio.h>
#include <stdlib.h>


typedef struct AVL_node
{
	int data;
	int height;
	struct AVL_node* left;
	struct AVL_node* right;
}AVLNode;


// Auxiliary queue for level order traversal
typedef struct queue
{
	AVLNode* node;
	AVLNode* parent;
	struct queue* next;
}Queue;

// Queue related functions
void enqueue(Queue** head, Queue** tail, AVLNode* node, AVLNode* parentNode, int* size);
AVLNode* dequeue(Queue** head, Queue** tail, int* size);


void traverseLevelOrder(AVLNode* root);

int max2(int num1, int num2);

int getHeight(AVLNode* node);
int getBalanceFactor(AVLNode* node);

void rotateLL(AVLNode** node);
void rotateLR(AVLNode** node);
void rotateRR(AVLNode** node);
void rotateRL(AVLNode** node);

AVLNode* createAVLNode(int data);
void insert(AVLNode** node, int data);

void traverseAndPrintInOrder(AVLNode* root);

int main() {
	AVLNode* root = NULL;
	
	int data;
	scanf("%d", &data);
	while (data != -1)
	{
		insert(&root, data);
		scanf("%d", &data);
	}
	
	traverseAndPrintInOrder(root);
	printf("\n");
	traverseLevelOrder(root);
	
	return 0;
}


int max2(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}

int getHeight(AVLNode* node)
{
	if (node != NULL)
		return node->height;
	else
		return -1;
}

int getBalanceFactor(AVLNode* node)
{
	if (node != NULL)
		return getHeight(node->left) - getHeight(node->right);
	else
		return 0;
}

void rotateLL(AVLNode** node)
{
	AVLNode* l = (*node)->left;
	AVLNode* lr = l->right;
	
	// Rotating nodes
	l->right = *node;
	(*node)->left = lr;
	
	// Recalculating heights
	(*node)->height = max2(getHeight((*node)->left), getHeight((*node)->right)) + 1;
	l->height = max2(getHeight(l->left), getHeight(l->right)) + 1;
	
	*node = l;
}

void rotateLR(AVLNode** node)
{
	rotateRR(&((*node)->left));
	rotateLL(node);
}

void rotateRR(AVLNode** node)
{
	AVLNode* r = (*node)->right;
	AVLNode* rl = r->left;
	
	// Rotating nodes
	r->left = *node;
	(*node)->right = rl;
	
	// Recalculating heights
	(*node)->height = max2(getHeight((*node)->left), getHeight((*node)->right)) + 1;
	r->height = max2(getHeight(r->left), getHeight(r->right)) + 1;
	
	*node = r;
}

void rotateRL(AVLNode** node)
{
	rotateLL(&((*node)->right));
	rotateRR(node);
}

AVLNode* createAVLNode(int data)
{
	AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode) * 1);
	
	newNode->data = data;
	newNode->height = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

void insert(AVLNode** node, int data)
{
	if (*node == NULL)
	{
		*node = createAVLNode(data);
		return;
	}
	
	if (data < (*node)->data)
		insert(&((*node)->left), data);
	else if (data > (*node)->data)
		insert(&((*node)->right), data);
	else
		return;
	
	(*node)->height = max2(getHeight((*node)->left), getHeight((*node)->right)) + 1;
	
	int balanceFactor = getBalanceFactor(*node);
	
	
	if (balanceFactor > 1 && data < (*node)->left->data)
		rotateLL(node);
	else if (balanceFactor > 1 && data > (*node)->left->data)
		rotateLR(node);
	else if (balanceFactor < -1 && data > (*node)->right->data)
		rotateRR(node);
	else if (balanceFactor < -1 && data < (*node)->right->data)
		rotateRL(node);
}

void traverseAndPrintInOrder(AVLNode* root)
{
	if (root != NULL)
	{
		traverseAndPrintInOrder(root->left);
		printf("%d\n", root->data);
		traverseAndPrintInOrder(root->right);
	}
}

void enqueue(Queue** head, Queue** tail, AVLNode* node, AVLNode* parentNode, int* size)
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

AVLNode* dequeue(Queue** head, Queue** tail, int* size)
{
	if (*head == NULL)
		return NULL;

	Queue* temp = *head;
	AVLNode* res = temp->node;
	*head = (*head)->next;
	free(temp);
	
	*size = *size - 1;

	if (*head == NULL)
		*tail = NULL;
	
	return res;
}

void traverseLevelOrder(AVLNode* root)
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
			AVLNode* parent = head->parent;
			AVLNode* currentNode = dequeue(&head, &tail, &queueSize);
			
			if (currentNode == NULL)
				break;
			
			if (parent == NULL)
			{
				printf("%d (%d B)", currentNode->data, getBalanceFactor(currentNode));
			}
			else
			{
				if (parent->data > currentNode->data)
					printf("%d (%d L) (%d B)", currentNode->data, parent->data, getBalanceFactor(currentNode));
				else
					printf("%d (%d R) (%d B)", currentNode->data, parent->data, getBalanceFactor(currentNode));
					
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

