#ifndef NODETREE_H
#define NODETREE_H

/*
 * ARCHIVO:
 *      NodeTree.h
 * 		�ltima modificaci�n: 2007/04/20  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA NodeTree para un arbol binario de busqueda
 * DEPENDENCIAS:
 *		generic.h Definici�n de Tipo de Dato Gen�rico
 *		stdlib.h   operaciones malloc y free para crear y eliminar dinamicamente
 * MODIFICACIONES:
 *		2004/07/15 (Marisol Villacres):	Version original
 *		2007/04/20 (V. Mac�as): Cambio para trabajar con ADTs
 */


#include <generic.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------------------
							TDA NODESBT
  -----------------------------------------------------------------------------------------*/

/****************
	NIVEL L�GICO
 ****************

	Definici�n
	_____________________________________________________________________________________
	<NodeTree>       ::= <contenido> + <hijo_izq> + <hijo_der>
	<contenido>		::= <dato>{<dato>}
	<hijo_izq>      ::= <abb>
	<hijo_der>      ::= <abb>
	_____________________________________________________________________________________

	Creacion
		Crea una NUEVA hoja con el contenido indicado,
		una vez creado lo retorna

		Ref_nodo Nueva_Hoja(Contenido);
	Eliminacion
		Libera un nodo en memoria, lo elimna para que no se pueda usar mas
		NodeSBT_Delete(Ref_nodo);

	Operaciones de Acceso
		Modifica el contenido de un nodo dado
		NodeSBT_ModificarContenido(Ref_nodo, Contenido);

		Modifica el enlace izquiero de un nodo dado,
		asignadole otra referencia a otro nodo
		NodeSBT_AsignarIzq(Ref_nodo, Ref_nodo);

		Modifica el enlace derecho de un nodo dado,
		asignadole otra referencia a otro nodo
		NodeSBT_AsignarDer(Ref_nodo, Ref_nodo);

		Consulta el contenido de un nodo dado y lo retorna
		Contenido NodeSBT_ConsultarContenido(Ref_nodo);

		Consulta el enlace izquierdo de un nodo dado y lo retorna
		Ref_nodo NodeSBT_GetLeft(Ref_nodo);

		Consulta el enlace derecho de un nodo dado y lo retorna
		Ref_nodo NodeSBT_GetRight(Ref_nodo);

		bool NodeSBT_isLeave(Ref_nodo);
*/


/*
 * Tipo: NodoSBT
 * ---------------
 * Un nodo es un elemento que tiene tres partes:
 * contenido donde almacena la informacion
 * y enlace al izquierdo y al derecho. De esta forma un nodo siempre va
 * a conocer quienes son y como acceder a sus hijos
 */

typedef struct TNodeTree{
	Generic key;
	Generic value;
	struct TNodeTree *left, *right;
}NodeTree;

/*
 * Funcion: NodeSBT_New
 * --------------------------
 * Modo de uso:
 * Generic G;
 * NodeSBT *nuevo;
 * nuevo = NodeSBT_New(G)
 * Esta operacion recibe un contenido, y la clave de dicho contenido
 * (que puede ser cualquier campo de G), para almacenarlo en un nodo
 * La operacion crea el nodo, le ubica el contenido dentro y
 * retorna la referencia al nuevo nodo
 */
NodeTree *nodeTreeNew(Generic key, Generic value);


/*
 * Funcion: nodeTreeisLeave
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * if (NodeSBT_isLeave(p))
 * Esta operacion recibe un nodo y determina si es o no un nodo hoja
 */
int nodeTreeisLeaf(NodeTree *node);

/*
 * Funcion: NodeSBT_GetContent
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * Generic G;
 * G = NodeSBT_GetContent(p);
 * Esta operacion recibe un nodo retorna el contenido del mismo
 */
Generic nodeTreeGetValue(NodeTree *node);

/*
 * Funcion: NodeSBT_GetKey
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * Generic clave;
 * clave = NodeSBT_GetKey(p);
 * Esta operacion recibe un nodo y retorna la clave del mismo
 */
Generic nodeTreeGetKey(NodeTree *node);


/*
 * Funcion: NodeSBT_GetLeft
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * NodeSBT *q;
 * a = NodeSBT_GetLeft(p);
 * Esta operacion recibe un nodo y retorna el enlace a su nodo izq
 */
NodeTree *nodeTreeGetLeft(NodeTree *node);
/*
 * Funcion: NodeSBT_GetRight
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * NodeSBT *q;
 * a = NodeSBT_GetRight(p);
 * Esta operacion recibe un nodo y retorna el enlace a su nodo der
 */
NodeTree *nodeTreeGetRight(NodeTree *node);

/*
 * Funcion: NodeSBT_SetContent
 * --------------------------
 * Modo de uso:
 * NodeSBT *p;
 * Generic G;
 * NodeSBT_SetContent(p, G);
 * Esta operacion recibe un nodo y cambia el contenido del mismo con G
 */
void nodeTreeSetValue (NodeTree *node , Generic value);
void nodeTreeSetKey(NodeTree *node , Generic key);

/*
 * Funcion: NodeSBT_SetLeft
 * --------------------------
 * Modo de uso:
 * NodeSBT *p, *q;
 * NodeSBT_SetLeft(p, q);
 * Esta operacion recibe un nodo y cambia su enlace a su nodo izquierdo por q
 */
void nodeTreeSetLeft(NodeTree *node, NodeTree *newleft);
/*
 * Funcion: NodeSBT_SetRight
 * --------------------------
 * Modo de uso:
 * NodeSBT *p, *q;
 * NodeSBT_SetRight(p, q);
 * Esta operacion recibe un nodo y cambia su enlace a su nodo derecho por q
 */
void nodeTreeSetRight(NodeTree *node, NodeTree *newright);

#endif