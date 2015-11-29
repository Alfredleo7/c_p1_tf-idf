#include <tree.h>

/*
 * ARCHIVO:
 *      tree.c
 * 		�ltima modificaci�n: 2004/07/15  (Marisol Villacres)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones
 *		 para el manejo del TDA Tree
 *
 * DEPENDENCIAS:
 *      tree.h:   la interfaz
 * MODIFICACIONES:
 *		2004/07/15 (Marisol Villacres):	Version original 
 *		2004/08/11 (Ronald Criollo): Correccion sobre la operacion SacarRaiz
 */

Tree treeNew(){
	Tree A;
	A = NULL;
	return A;
}


int treeIsEmpty(Tree A){
	return (A == NULL);
}

NodeTree *treeSearch(Tree A, Generic clave, cmpfn fn ){
	if(treeIsEmpty(A)) return NULL;
	if(fn(nodeTreeGetKey(A), clave) == 0) return A;
	if(fn(nodeTreeGetKey(A), clave) < 0)
		return treeSearch(nodeTreeGetRight(A), clave, fn);
	else
		return treeSearch(nodeTreeGetLeft(A), clave, fn);
}

void treeInsertNode(Tree *A, NodeTree *nuevo, cmpfn fn){
	if(!treeIsEmpty(*A)){
		if(fn(nodeTreeGetKey(nuevo),nodeTreeGetKey(*A)) >0){
			treeInsertNode(&((*A)->right),nuevo,fn);
		}
		else{
			treeInsertNode(&((*A)->left),nuevo,fn);
		}
	} else{
		//Si esta vacio, alli insertar
		*A = nuevo;
	}
}

NodeTree *treeRemoveNode(Tree *A, Generic clave, cmpfn fn){
	NodeTree *tmp = *A;
	if(treeIsEmpty(*A)) return NULL;
	if(fn((*A)->key, clave) < 0)
		return(treeRemoveNode(&(*A)->right, clave, fn));
        else if(fn((*A)->key, clave) >0)
		return(treeRemoveNode(&(*A)->left, clave, fn));

	if((*A)->right == NULL){
            (*A) = (*A)->left;
	}
        else if((*A)->left == NULL){
            (*A) = (*A)->right;
	}
        else{
		tmp = treeRemoveRoot(A);
    }
	return tmp;
}

NodeTree *treeRemoveRoot(Tree *A){
	NodeTree *q,*tmp;
	q = (*A)->left;
	if(!q->right){
		(*A)->value = q->value;
		(*A)->key= q->key;
		tmp = q;
		(*A)->left = q->left;
		return tmp;
	}
	else{
		while(q->right->right!=NULL){
			q = q->right;
		}
		(*A)->value = q->right->value;
		(*A)->key= q->right->key;
		tmp = q->right;
		q->right = q->right->left;
		return tmp;
	}
}

void treePreOrder(Tree A, printfn fn){
	if(!treeIsEmpty(A)){
		fn(A->value);
		treePreOrder(A->left, fn);
		treePreOrder(A->right, fn);
	}
}

void treePostOrder(Tree A, printfn fn){
	if(!treeIsEmpty(A)){
		treePostOrder(A->left, fn);
		treePostOrder(A->right, fn);
		fn(A->value);
	}
}

void treeInOrder(Tree A, printfn fn){
	if(!treeIsEmpty(A)){
		treeInOrder(A->left, fn);
		fn(A->value);
		treeInOrder(A->right, fn);
	}
}


Tree treeReadFromFile(char *nombrearchivo, readfn comoleer, getkeyfn como_obtenerclave, cmpfn como_comparar){
	Generic gvalor;
	NodeTree *nuevo;
	Tree A;
	FILE *F;
	F = fopen(nombrearchivo,"r");
	if(!F) return NULL;

	A = treeNew();

	//Reviso el archivo del inicio hasta el final
	while(!feof(F)){
		gvalor = comoleer(F);
		nuevo = nodeTreeNew(como_obtenerclave(gvalor),gvalor);
		treeInsertNode(&A, nuevo, como_comparar);
	}
	fclose(F);
	return A;

}
