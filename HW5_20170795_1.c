#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMNTS 10
#define IS_FULL(n)(n==MAX_ELEMNTS-1)
#define IS_EMPTY(n)(!n)

/*tree 구조체 선언*/
typedef struct node *treePointer;
typedef struct node {
	int key;
	treePointer parent;
	treePointer leftChild, rightChild;
}node;
int flag;

treePointer tree_node;
treePointer result;

typedef struct queue {
	struct queue* next;
	node* element;
} queue;

void free_queue(queue** q) {
	queue* current_q = *q;
	while (current_q != NULL) {
		*q = current_q->next;
		free(current_q);
		current_q = *q;
	}
}

queue* make_queue(node* element) {
	queue* q = (queue*)malloc(sizeof(queue));
	q->next = NULL;
	q->element = element;
	return q;
}

void queue_put(node* n, queue** last) {
	if (n->leftChild != NULL) {
		(*last)->next = make_queue(n->leftChild);
		(*last) = (*last)->next;
	}
	if (n->rightChild != NULL) {
		(*last)->next = make_queue(n->rightChild);
		(*last) = (*last)->next;
	}
}
//a factory to create a node
node* make_node(int x, node* parent) {
	node* temp = (node*)malloc(sizeof(node));
	temp->key = x;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->parent = parent;
	return temp;
}
void dln(treePointer root, int num)
{
	if (root == NULL)
		return;
	if (root->key == num)
	{
		flag = 1;
		fprintf(stdout, "Exist number\n");
		return;
	}
	if (!root->leftChild || !root->rightChild)
	{
		return;
	}
	dln(root->leftChild, num);
	dln(root->rightChild, num);
}
void insert(node** root, int num)
{
	flag = 0;
	dln(tree_node, num);
	if (flag == 1)
		return;
	if (*root == NULL)
	{
		*root = make_node(num, NULL);
	}
	/*search for a proper insert point*/
	else {
		queue* q = make_queue(*root);
		queue* current_q = q;
		queue* last_q = q;
		node* node_place;

		while (current_q != NULL) {
			//get one node out of queue
			node_place = current_q->element;

			if (node_place->leftChild == NULL) {
				node_place->leftChild = make_node(num, node_place);
				node_place = node_place->leftChild;
			}
			else if (node_place->rightChild == NULL) {
				node_place->rightChild = make_node(num, node_place);
				node_place = node_place->rightChild;
			}
			else {
				queue_put(node_place, &last_q);
				//increment the current pointer
				current_q = current_q->next;
				continue;
			}

			//put the node to proper point
			while (node_place->parent != NULL && node_place->parent->key < node_place->key) {
				//swap the key
				int temp = node_place->parent->key;
				node_place->parent->key = node_place->key;
				node_place->key = temp;
				node_place = node_place->parent;
			}
			break;
		}

		free_queue(&q);
	}
	fprintf(stdout, "Insert %d\n", num);
	return;
}

void d_dln(treePointer root, treePointer* result_1)
{
	if (root != NULL)
	{
		queue* q = make_queue(root);
		queue* current_q = q;
		queue* last_q = q;
		queue* previous_q;
		node* node_place;
		while (current_q != NULL)
		{
			node_place = current_q->element;

			queue_put(node_place, &last_q);

			previous_q = current_q;
			current_q = current_q->next;
		}
		*result_1 = previous_q->element;
	}
}

void delete(void) {

	if (tree_node == NULL)
	{
		fprintf(stdout, "The heap is empty\n");
		return;
	}
	else
	{
		int num = tree_node->key;
		fprintf(stdout, "Delete %d\n", num);
		node* node_place;
		treePointer temptree = (treePointer*)malloc(sizeof(treePointer) * 10);
		temptree = NULL;
		d_dln(tree_node, &node_place);
		if (node_place->parent == NULL) {
			free(node_place);
			tree_node = NULL;
		}
		else {
			(tree_node)->key = node_place->key;
			node_place = node_place->parent;
			if (node_place->rightChild != NULL) {
				free(node_place->rightChild);
				node_place->rightChild = NULL;
			}
			else {
				free(node_place->leftChild);
				node_place->leftChild = NULL;
			}
			//move down the queue
			int a, b, c;
			node_place = tree_node;
			while (1) {
				if (node_place->leftChild == NULL) {
					//implies current->rightChild == NULL is true
					break;
				}
				else if (node_place->rightChild == NULL) {
					a = node_place->key;
					b = node_place->leftChild->key;
					if (a < b) {
						node_place->key = b;
						node_place->leftChild->key = a;
						node_place = node_place->leftChild;
					}
					else {
						break;
					}
				}
				else {
					if (node_place->key >= node_place->leftChild->key && node_place->key >= node_place->rightChild->key) {
						break;
					}
					else if (node_place->leftChild->key > node_place->key && node_place->leftChild->key >= node_place->rightChild->key) {
						node_place->leftChild->key = node_place->key;
						node_place->key = node_place->leftChild->key;
						node_place = node_place->leftChild;
					}
					else {
						node_place->rightChild->key = node_place->key;
						node_place->key = node_place->rightChild->key;
						node_place = node_place->rightChild;
					}
				}
			}
		}
	}
}

int main(void)
{
	tree_node = (treePointer*)malloc(sizeof(treePointer) * 100);
	tree_node = NULL;
	char order;
	int num;
	for (int i = 0; i < 100; i++)
	{
		fscanf(stdin, "%c", &order);
		switch (order)
		{
		case 'i':
			fscanf(stdin, "%d", &num);
			insert(&tree_node,num);
			break;
		case 'd':
			delete();
			break;
		case 'q':
			exit(1);
		}
		while (getchar() != '\n');
	}
	return 0;
}
