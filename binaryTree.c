#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int value;
    struct Node * parent;
    struct Node * left;
    struct Node * right;
} NODE;

NODE * createNode( int value, NODE * parent );
void destroyNode( NODE * nodeToDestroy );
static void insertWithFather( NODE ** tree, NODE * parent, int value );
void insertNode( NODE ** tree, int value );
static void replaceNode( NODE * nodeToReplace, NODE * newNode );
void deleteNode( NODE * tree, int value );
static void delete( NODE * nodeToDelete );
static NODE * min( NODE * subTree );

void printInOrder( NODE * tree );

int main()
{
    NODE * arbol = NULL;

    insertNode( &arbol, 40 );
    insertNode( &arbol, 20 );
    insertNode( &arbol, 60 );
    insertNode( &arbol, 10 );
    insertNode( &arbol, 30 );
    insertNode( &arbol, 50 );
    insertNode( &arbol, 70 );

    printInOrder( arbol );

    printf( "\n" );

    deleteNode( arbol, 70 );

    printInOrder( arbol );

    printf( "\n" );

    deleteNode( arbol, 40 );

    printInOrder( arbol );

    return 0;
}

NODE * createNode( int value, NODE * parent )
{
    NODE * newNode;
    newNode = malloc( sizeof( NODE ) );
    newNode->left = newNode->right = NULL;
    newNode->value = value;
    newNode->parent = parent;
    return newNode;
}

void destroyNode( NODE * nodeToDestroy )
{
    nodeToDestroy->left = nodeToDestroy->right = NULL;
    free( nodeToDestroy );
}

void printInOrder( NODE * tree )
{
    if ( !tree )
    {
        printf( "" );
    } 
    else 
    {
        printInOrder( tree->left );
        printf( "%d ", tree->value );
        printInOrder( tree->right);
    }
}

static void insertWithFather( NODE ** tree, NODE * parent, int value )
{
    if ( !(*tree) ) {
        *tree = createNode( value, parent );
    } else {
        int rootValue = (*tree)->value;
        if ( value < rootValue )
        {
            insertWithFather( &(*tree)->left, *tree, value );
        }
        else
        {
            insertWithFather( &(*tree)->right, *tree, value );
        }

    }
}

void insertNode( NODE ** tree, int value )
{
    insertWithFather( tree, NULL, value );
}

static void replaceNode( NODE * nodeToReplace, NODE * newNode )
{
    if ( nodeToReplace->parent )
    {
        if ( nodeToReplace->value == nodeToReplace->parent->left->value )
        {
            nodeToReplace->parent->left = newNode;
        }
        else if ( nodeToReplace->value == nodeToReplace->parent->right->value )
        {
            nodeToReplace->parent->right = newNode;
        }
    }
    if ( newNode )
    {
        newNode->parent = nodeToReplace->parent;
    }
}

void deleteNode( NODE * tree, int value )
{
    if ( !tree ) 
    {
        return;
    }
    else if ( value < tree->value )
    {
        deleteNode( tree->left, value );
    }
    else if ( value > tree->value )
    {
        deleteNode( tree->right, value );
    }
    else
    {
        delete( tree );
    }
}

static void delete( NODE * nodeToDelete )
{
    if ( nodeToDelete->left && nodeToDelete->right )
    {
        NODE * sucesor;
        sucesor = min( nodeToDelete->right );
        nodeToDelete->value = sucesor->value;
        delete( sucesor );
    }
    else if ( nodeToDelete->left )
    {
        replaceNode( nodeToDelete, nodeToDelete->left );
        destroyNode( nodeToDelete );
    }
    else if ( nodeToDelete->right )
    {
        replaceNode( nodeToDelete, nodeToDelete->right );
        destroyNode( nodeToDelete );
    }
    else
    {
        replaceNode( nodeToDelete, NULL );
        destroyNode( nodeToDelete );
    }
}

static NODE * min( NODE * subTree )
{
    if ( !subTree )
    {
        return NULL;
    }
    else if ( subTree->left )
    {
        return min( subTree->left );
    }
    else
    {
        return subTree;
    }
}