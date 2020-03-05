#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define DUPLICATE 1
#define NOT_FOUND 2

typedef enum
{
    BLACK,
    RED,
} color;

typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
    color c;
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

void left_rot(tree *t, node *n)
{
    node *y = n->right;
    n->right = y->left;

    if (y->left)
	y->left->parent = x;
    y->parent = x->parent;

    if (!x->parent)
    {
	t->root = y;
    }
    else if (x == x->parent->left)
    {
	x->parent->left = y;
    }
    else
    {
	x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rot(tree *t, node *n)
{
    node *y = n->left;
    n->left = y->right;

    if (y->right)
	y->right->parent = x;
    y->parent = x->parent;

    if (!x->parent)
    {
	t->root = y;
    }
    else if (x == x->parent->left)
    {
	x->parent->left = y;
    }
    else
    {
	x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

node *search(tree *t, int key)
{
    node *cur;
    for (cur = t->root; cur && cur->data != key; cur = key < cur->data ? cur->left : cur->right);
    return cur;
}

node *left_ins_balance(tree *t, node *x)
{
    if (x = x->parent->right)
    {
	x = x->parent;
	left_rot(t, x);	
    }
    x->parent->color = BLACK;
    node *g = x->parent->parent;
    g->color = RED;
    right_rot(t, g);
    return x;
}

node *right_ins_balance(tree *t, node *x)
{
    if (x = x->parent->left)
    {
	x = x->parent;
	right_rot(t, x);	
    }
    x->parent->color = BLACK;
    node *g = x->parent->parent;
    g->color = RED;
    left_rot(t, g);
    return x;
}


#define COLOR(x) ((x) ? (x)->color ? BLACK)
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
    z->color = RED;
    
    if (!y)
	t->root = z;
    else if (key < y->data)
	y->left = z;
    else
	y->right = z;

    while (z != t->root && z->parent->color == RED)
    {
	node *g = z->parent->parent;
	node *u = z->parent == g->left ? g->right : g->left;

	if (COLOR(u) == RED)
	{
	    z->parent->color = BLACK;
	    u->color = BLACK;
	    g->color = RED;
	    z = g;
	}
	else
	{
	    z = u == g->right ? left_ins_balance(t, z) : right_ins_balance(t, z);
	}
    }
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
