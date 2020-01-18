#include <stdio.h>
#include <stdlib.h>

typedef int Value;
typedef struct Node
{
	Value value;
	struct Node * parent;
	struct Node * left;
	struct Node * right;
} NODE, TREE;

NODE * createNode( Value value, NODE * parent )
{
	NODE * newNode;
	newNode = malloc( sizeof( NODE ) );
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	newNode->parent = parent;
	return newNode;
}

NODE * destroyNode( NODE * nodeToDestroy )
{
	nodeToDestroy->left = nodeToDestroy->right = NULL;
	free( nodeToDestroy );
}

void insertNodeWithParent( NODE ** rootNode, NODE * parent, Value value )
{
	if ( *rootNode == NULL ) {
		*rootNode = createNode( value, parent );
	} else {
		Value rootValue = (*rootNode)->value;
		if ( value < rootValue ) {
			insertNodeWithParent( &(*rootNode)->left, *rootNode, value );
		} else {
			insertNodeWithParent( &(*rootNode)->right, *rootNode, value);
		}
	}
}

void insertNode( NODE ** rootNode, Value value )
{
	insertNodeWithParent( rootNode, NULL, value );
}

void preOrder( const NODE * rootNode )
{
	if ( rootNode == NULL ) {
		printf( " - " );

	} else {
		printf( "( " );
		if ( rootNode->parent == NULL ) {
			printf( " %d {//} ", rootNode->value );
		} else {
			printf( " %d {%d} ", rootNode->value, rootNode->parent->value );
		}
		preOrder( rootNode->left );
		preOrder( rootNode->right );
		printf( " )" );
	}
}

void inOrder( const NODE * rootNode )
{
	if ( rootNode == NULL ) {
		printf( "" );

	} else {
		inOrder( rootNode->left );
		printf( "%d ", rootNode->value );
		inOrder( rootNode->right );
	}
}

void postOrder( const NODE * rootNode )
{
	if ( rootNode == NULL ) {
		printf( "" );
	} else {
		postOrder( rootNode->left );
		postOrder( rootNode->right );
		printf( "%d ", rootNode->value );
	}
}

int stepsToNode( NODE * rootNode, Value value )
{
	if ( value == rootNode->value ) {
		return 1;
	} else {
		if( value < rootNode->value ) {
			return 1 + stepsToNode( rootNode->left, value );
		} else {
			return 1 + stepsToNode( rootNode->right, value );
		}
	}
}

int heightTree( const NODE * rootNode )
{
	if ( rootNode == NULL ) {
		return 0;
	} else {
		int heightLeft = heightTree( rootNode->left );
		int heightRight = heightTree( rootNode->right );
		if ( heightLeft > heightRight ) {
			return heightLeft + 1;
		} else {
			return heightRight + 1;
		}
	}
}

int numberOfNodes( const NODE * rootNode )
{
	if ( rootNode == NULL) {
		return 0;
	} else {
		return 1 + numberOfNodes( rootNode->left ) + numberOfNodes( rootNode->right );
	}
}

int isFullTree( const NODE * rootNode )
{
	if ( rootNode == NULL ) {
		return 1;
	} else {
		if ( heightTree( rootNode->left ) != heightTree( rootNode->right ) ) {
			return 0;
		}
		return isFullTree( rootNode->left ) && isFullTree( rootNode->right );
	}
}

int existsNode( const NODE * rootNode, Value value )
{
	if ( rootNode == NULL ) {
		return 0;
	} else if ( value == rootNode->value ) {
		return 1;
	} else if ( value < rootNode->value ) {
		return existsNode( rootNode->left, value );
	} else {
		return existsNode( rootNode->right, value );
	}
}

NODE * getNode( NODE * rootNode, Value value )
{
	if ( rootNode == NULL ) {
		return;
	} else if ( value == rootNode->value ) {
		return rootNode;
	} else if ( value < rootNode->value ) {
		return getNode( rootNode->left, value );
	} else {
		return getNode( rootNode->right, value );
	}
}

void replaceNode( NODE * rootNode, NODE * nodeToReplace )
{
	if ( rootNode->parent ) {
		if ( rootNode->value == rootNode->parent->left->value ) {
			rootNode->parent->left = nodeToReplace;
		} else if ( rootNode->value == rootNode->parent->right->value ) {
			rootNode->parent->right = nodeToReplace;
		}
	}
	if ( nodeToReplace ) {
		nodeToReplace->parent = rootNode->parent;
	}
}

NODE * getMin( NODE * subTreeBranch ) {
	if ( subTreeBranch == NULL ) {
		return NULL;
	}
	if ( subTreeBranch->left ) {
		return getMin( subTreeBranch->left );
	} else {
		return subTreeBranch;
	}
}

NODE * getMax( NODE * subTreeBranch )
{
	if ( subTreeBranch == NULL ) {
		return NULL;
	}
	if ( subTreeBranch->left ) {
		return getMin( subTreeBranch->right );
	} else {
		return subTreeBranch;
	}
}

void delete( NODE * nodeToDelete )
{
	if ( nodeToDelete->left && nodeToDelete->right ) {
		NODE * minimun = getMin( nodeToDelete->right );
		nodeToDelete->value = minimun->value;
		delete( minimun );
	} else if ( nodeToDelete->left ) {
		replaceNode( nodeToDelete, nodeToDelete->left );
		destroyNode( nodeToDelete );
	} else if ( nodeToDelete->right ) {
		replaceNode( nodeToDelete, nodeToDelete->right );
		destroyNode( nodeToDelete );
	} else {
		replaceNode( nodeToDelete, NULL);
		destroyNode( nodeToDelete );
	}
}

void deleteNode( NODE * nodeToDelete, Value value )
{
	if ( nodeToDelete == NULL ) {
		return;
	} else if ( value < nodeToDelete->value ) {
		deleteNode( nodeToDelete->left, value );
	} else if ( value > nodeToDelete->value ) {
		deleteNode( nodeToDelete->right, value );
	} else {
		delete( nodeToDelete );
	}
}


int main( int argc, const char * argv[] )
{
	// Insertar nodos
	TREE * tree = NULL;
	insertNode( &tree, 40 );
	insertNode( &tree, 20 );
	insertNode( &tree, 10 );
	insertNode( &tree, 30 );
	insertNode( &tree, 60 );
	insertNode( &tree, 50 );
	insertNode( &tree, 70 );

	// Mostrar árbol
	printf("PreOrder\n");
	preOrder( tree );
	printf("\nInOrder\n");
	inOrder( tree );
	printf("\nPostOrder\n");
	postOrder( tree );

	int x = numberOfNodes( tree );
	printf( "\nNumero de nodos: %d\n", x );

	int y = heightTree( tree );
	printf( "Altura del arbol: %d\n", y );

	int isFull = isFullTree( tree );
	printf("El arbol esta lleno? %d\n", isFull );

	printf("El nodo 30 existe? %d\n", existsNode( tree, 30 ) );

	deleteNode( tree, 40 );

	preOrder( tree );

	return 0;
}
