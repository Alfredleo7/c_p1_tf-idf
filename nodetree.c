#include <nodetree.h>

/*
 * ARCHIVO:
 *      NodeTree.c
 * 		�ltima modificaci�n: 2004/07/28  (Marisol Villacres)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones
 *		 para el manejo del TDA NodeTree
 *
 * DEPENDENCIAS:
 *      NodeTree.h:   la interfaz
 * MODIFICACIONES:
 *		2004/07/15 (Marisol Villacres):	Version original 
 *		2004/07/28 (Marisol Villacres):	Se le a�adio un campo clave al nodo y
 *										debido a esto cambiaron las implementaciones
 *										de la busqueda, insercion y eliminacion
 */


NodeTree *nodeTreeNew(Generic key, Generic value){
	NodeTree *nuevo;
	nuevo = malloc(sizeof(NodeTree));
	nuevo->value = value;
	nuevo->key = key;
	nuevo->left = NULL;
	nuevo->right = NULL;
	return nuevo;
}

int nodeTreeIsLeaf(NodeTree *p){
	if(!p) return 1;
	return (p->left == NULL && p->right == NULL);
}

Generic nodeTreeGetValue(NodeTree *nodo){
	if(nodo!=NULL) return nodo->value;
	else return NULL;
}

Generic nodeTreeGetKey(NodeTree *nodo){
	if(nodo!=NULL) return nodo->key;
	else return NULL;
}

NodeTree *nodeTreeGetLeft (NodeTree *nodo){
	if(nodo!=NULL) return nodo->left;
	else return NULL;
}
NodeTree *nodeTreeGetRight(NodeTree *nodo){
	if(nodo!=NULL) return nodo->right;
	else return NULL;
}

void nodeTreeSetKey(NodeTree *nodo , Generic key){
	if(nodo!=NULL) nodo->key = key;
}

void nodeTreeSetValue (NodeTree *nodo , Generic value){
	if(nodo!=NULL) nodo->value = value;
}
void nodeTreeSetLeft(NodeTree *nodo, NodeTree *enlace){
	if(nodo!=NULL) nodo->left = enlace;
}

void nodeTreeSetRight(NodeTree *nodo, NodeTree *enlace){
	if(nodo!=NULL) nodo->right = enlace;
}