#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50 /* size of largest matrix */
typedef enum { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
}entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
}matrix_node;
matrix_pointer hdnode[MAX_SIZE];
matrix_pointer hdnode_t[MAX_SIZE];
FILE* fp;

matrix_pointer new_node() {
	matrix_pointer ret = (matrix_pointer)calloc(sizeof(struct matrix_node), 1);
	return ret;
}
int num_terms;

matrix_pointer mread() {
	FILE* fp;
	int num_rows, num_cols, num_heads, i;
	int row, col, val, current_row;
	matrix_pointer temp, last, node;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d %d", &num_rows, &num_cols, &num_terms);
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node(); node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;
	if (!num_heads) node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0];
		for (i = 0; i < num_terms; i++) {
			fscanf(fp, "%d %d %d", &row, &col, &val);
			if (row > current_row) {
				last->right = hdnode[current_row];
				current_row = row;
				last = hdnode[row];
			}
			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = val;
			last->right = temp;
			last = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[current_row];
		for (i = 0; i < num_cols; i++) {
			hdnode[i]->u.next->down = hdnode[i];
		}
		for (i = 0; i < num_heads - 1; i++) {
			hdnode[i]->u.next = hdnode[i + 1];
		}
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
	fclose(fp);
}

void mwrite(matrix_pointer node)
{ /* print out the matrix in row major form */
	FILE* fp;
	fp = fopen("output.txt", "w");
	fprintf(fp,"%5d%5d%5d\n", node->u.entry.row, node->u.entry.col,node->u.entry.value);
	int i;
	matrix_pointer temp, head = node->right;
	/* matrix dimensions */
	for (i = 0; i < node->u.entry.row; i++) {
		/* print out the entries in each row */
		for (temp = head->right; temp != head; temp = temp->right)
			fprintf(fp,"%5d%5d%5d\n",
				temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next; /* next row */
	}
	fclose(fp);
}

matrix_pointer mtransepose(matrix_pointer node) {
	int num_rows, num_cols, num_heads, i;
	int row, col, val, current_row;
	matrix_pointer temp, last, ret;
	matrix_pointer x, h = node->right;
	x = h->down;
	num_rows = node->u.entry.col;
	num_cols = node->u.entry.row;
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	ret = new_node(); ret->tag = entry;
	ret->u.entry.row = num_rows;
	ret->u.entry.col = num_cols;
	if (!num_heads) ret->right = ret;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode_t[i] = temp; hdnode_t[i]->tag = head;
			hdnode_t[i]->right = temp; hdnode_t[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode_t[0];
		for (i = 0; i < num_terms; i++) {
			if (x == h) {
				h = h->u.next;
				x = h->down;
			}
			row = x->u.entry.col;
			col = x->u.entry.row;
			val = x->u.entry.value;
			if (row > current_row) {
				last->right = hdnode_t[current_row];
				current_row = row; last = hdnode_t[row];
			}
			temp = new_node(); temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = val;
			last->right = temp; /* link into row list */
			last = temp;
			hdnode_t[col]->u.next->down = temp; /* link into column list */
			hdnode_t[col]->u.next = temp;
			x = x->down;
		}
		last->right = hdnode_t[current_row];
		/* close all column lists */
		for (i = 0; i < num_cols; i++)
			hdnode_t[i]->u.next->down = hdnode_t[i];
		/* link all header nodes together */
		for (i = 0; i < num_heads - 1; i++)
			hdnode_t[i]->u.next = hdnode_t[i + 1];
		hdnode_t[num_heads - 1]->u.next = ret;
		ret->right = hdnode_t[0];
	}
	return ret;
}



int main() {
	matrix_pointer node = mread();
	matrix_pointer node_t = mtransepose(node);
	mwrite(node_t);
	return 0;
}