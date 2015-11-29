#ifndef TREE_H
#define TREE_H

/*
 * ARCHIVO:
 *      Tree.h
 * 		�ltima modificaci�n: 2007/04/20  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA SBT (ARBOL BINARIO DE BUSQUEDA)
 * DEPENDENCIAS:
 *		nodetree.h Definici�n de un NodeSBT para formar un arbol
 * MODIFICACIONES:
 *		2004/07/15 (Marisol Villacres):	Version original
 *		2007/04/20 (V. Mac�as): Cambio para trabajar con ADTs
 */

#include <nodetree.h>

/*-----------------------------------------------------------------------------------------
							TDA SBT(ARBOL BINARIO DE BUSQUEDA)
  -----------------------------------------------------------------------------------------*/

/****************
	NIVEL L�GICO
 ****************

	Definici�n
	_____________________________________________________________________________________
	<abb> ::= <raiz>|NULL
	<raiz>   ::= <ref_nodo>
	<ref_nodo>:=<clave><contenido><izq><der>
	_____________________________________________________________________________________

                Comprobaci�n de Estado
		bool treeisEmpty(arbol);

		Inserci�n de Nodos
		treeInsertNode(referencia_arbol, referencia_nodo);

		Borrado de Nodos
		referencia_nodo treeRemoveNode(referencia_arbol, contenido);

		B�squeda de un nodo
		referencia_nodo treeSearch(arbol, contenido);

		Recorrido de la lista
		treePreOrder(Arbol);
		treePostOrder(Arbol);
		treeInOrder(Arbol);
*/

/*
 * Tipo: Tree
 * ---------------
 * Un Tree es una referencia a un nodo, que es el nodo raiz
 * desde donde se puede acceder al resto
 */

typedef NodeTree *Tree;

/*
 * Funcion: treeNew
 * --------------------------
 * Modo de uso:
 * Tree A;
 * A = treeNew();
 * Esta operacion crea un arbol vacio, listo para trabajar
 */
Tree treeNew();

/*
 * Funcion: treeIsEmpty
 * --------------------------
 * Modo de uso:
 * Tree A;
 * if(treeIsEmpty(A))
 * Esta operacion recibe un arbol y determina si esta o no vacio
 */
int treeIsEmpty(Tree A);

/*
 * Funcion: treeInsertNode
 * --------------------------
 * Modo de uso:
 * Tree A;
 * NodeTree *nuevo;
 * nuevo->clave = ObtenerCampo(nuevo->contenido);
 * treeInsertNode(&A, nuevo, comocomparar);
 * Esta operacion recibe un arbol e inserta un nuevo nodo en el mismo
 * de tal forma que el arbol conserve su calidad de binario de busqueda
 * El nuevo nodo se ubica en la posicion correcta gracias al 
 * campo clave y a la funcion de comocomparar correcta
 * La funcion de comocomparar compara la clave del nuevo nodo
 * con la clave de c/nodo en el arbol(enteros, cadenas, etc)
 */
void treeInsertNode(Tree *A, NodeTree *nuevo, cmpfn cmp);

/*
 * Funcion: treeRemoveNode
 * --------------------------
 * Modo de uso:
 * Tree A;
 * NodeTree *sacado;
 * Generic G;
 * sacado = treeRemoveNode(&A, G, comocomparar);
 * Esta operacion recibe un arbol y eliminar aquel nodo con clave
 * G. Retorna el nodo removido del arbol
 */
NodeTree *treeRemoveNode(Tree *A, Generic key, cmpfn cmp);

/*
 * Funcion: treeRemoveRoot
 * --------------------------
 * Modo de uso:
 * Tree A;
 * NodeTree *sacado;
 * sacado = treeRemoveRoot(&A);
 * Esta operacion recibe la raiz de un arbol y la remueve del arbol
 * dejandolo con su propiedad correcta de arbol binario de busqueda
 */
NodeTree *treeRemoveRoot(Tree *A);

/*
 * Funcion: treeSearch
 * --------------------------
 * Modo de uso:
 * Tree A;
 * NodeTree *encontrado;
 * Generic G;
 * sacado = treeSearch(A, G, comocomparar);
 * Esta operacion recibe un arbol y una clave. Busca aquel nodo
 * con dicha clave en el arbol. Si lo encuentra, retorna el nodo donde lo encontro
 * Si no, retorna NULL
 */
NodeTree *treeSearch(Tree A, Generic key, cmpfn fn );

/*
 * Funcion: treePreOrder
 * --------------------------
 * Modo de uso:
 * Tree A;
 * treePreOrder(A, comoimprimir);
 * Esta operacion recibe un arbol  y lo recorre en PreOrden
 */
void treePreOrder(Tree A, printfn fn);

/*
 * Funcion: treePreOrder
 * --------------------------
 * Modo de uso:
 * Tree A;
 * treePostOrder(A, comoimprimir);;
 * Esta operacion recibe un arbol  y lo recorre en PosOrden
 */
void treePostOrder(Tree A, printfn fn);

/*
 * Funcion: SBT_InOrder
 * --------------------------
 * Modo de uso:
 * Tree A;
 * treeInOrder(A, comoimprimir));
 * Esta operacion recibe un arbol  y lo recorre en EnOrden
 */
void treeInOrder(Tree A, printfn fn);

Tree treeReadFromFile(char *filename, readfn read, getkeyfn getkey, cmpfn cmp);

#endif