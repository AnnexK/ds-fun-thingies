#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define DUPLICATE 1
#define NOT_FOUND 2

typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;

typedef struct
{
    node *root;
} tree;

void make_tree(tree *t)
{
    t->root = NULL;
}

void dest_tree_node(node *n)
{
    if (n)
    {
	dest_tree_node(n->left);
	dest_tree_node(n->right);
    }
    free(n);
}

void dest_tree(tree *t)
{
    dest_tree_node(t->root);
}

node *search(tree *t, int key)
{
    node *cur;
    for (cur = t->root; cur && cur->data != key; cur = key < cur->data ? cur->left : cur->right);
    return cur;
}

int insert(tree *t, int key)
{
    node *y = NULL;
    node *x;
    for (x = t->root; x && x->data != key; x = key < x->data ? x->left : x->right)
	y = x;

    if (y && y->data == key)
	return DUPLICATE;

    node *z = malloc(sizeof(node));
    z->data = key;   
    z->parent = y;
    z->left = z->right = NULL;
    
    if (!y)
	t->root = z;
    else if (key < y->data)
	y->left = z;
    else
	y->right = z;
    return SUCCESS;
}

node *tree_min(node *n)
{
    node *r;
    for (r = n; r; r = r->left);
    return r;
}

int delete(tree *t, int key)
{
    /* удаляемая вершина */
    node *z = search(t, key);
    if (!z)
	return NOT_FOUND;

    /* вершина, которую будем реально удалять */
    node *y = !(z->left && z->right) ? z : tree_min(z->right);
    /* вершина, которую нужно будет "переподвесить" */
    node *x = y->left ? y->left : y->right;
    if (x)
	x->parent = y->parent;
    if (!y->parent)
	t->root = x;
    else if (y == y->parent->left)
	y->parent->left = x;
    else
	y->parent->right = x;

    if (y != z)
	z->data = y->data;

    free(y);
    return SUCCESS;
}

void _infix(node *n, void (*foo)(node *))
{
    if (n)
    {
	_infix(n->left, foo);
	foo(n);
	_infix(n->right, foo);
    }
}

void infix(tree *t, void (*foo)(node *))
{
    _infix(t->root, foo);
}

void print(node *n)
{
    printf("%d ", n->data);
}

int main(void)
{
    tree *t = malloc(sizeof(tree));
    make_tree(t);

    insert(t, 4);
    insert(t, 9);
    insert(t, 14);
    insert(t, 1);

    infix(t, print);
    putchar('\n');

    insert(t, 13);
    delete(t, 1);
    delete(t, 14);
    
    infix(t, print);
    putchar('\n');

    dest_tree(t);
    free(t);

    return 0;
}
