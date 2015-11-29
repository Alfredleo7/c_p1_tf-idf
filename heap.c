
#include "heap.h"
#include <stdlib.h>

/*
 * ARCHIVO:
 *      Heap.c
 * 		�ltima modificaci�n: 2007/04/25  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones
 *		 para el manejo del TDA Heap
 * DEPENDENCIAS:
 *      heap.h:   la interfaz
 *		stdlib.h :  malloc
 * MODIFICACIONES:
 *		2004/07/29 (Marisol Villacres):	Creacion del TDA
 *		2007/04/25 (V. Mac�as): Cambio soporte de version en Ingles
 */

/************************PROTOTIPOS DE FUNCIONES PRIVADAS EN EL HEAP**************/

/*
 * Funcion: Heap_IdxLeft
 * --------------------------
 * Modo de uso:
 * Heap H;
 * int pos, posizq;
 * posizq = Heap_IdxLeft(H, pos);
 * Descripcion:
 * Calcula la posicion del hijo izquierdo de un nodo de posicion pos
 * en el Heap. Si no hay hijo izquierdo, retorna -1
 */
static int heapIdxLeft(Heap *H, int idxfather);

/*
 * Funcion: Heap_IdxRight
 * --------------------------
 * Modo de uso:
 * Heap H;
 * int pos, posder;
 * posder = Heap_IdxRight(H, pos);
 * Descripcion:
 * Calcula la posicion de hijo derecho de un nodo de posicion pos en 
 * el Heap. Si no hay hijo derecho, retorna -1 
 */
static int heapIdxRight(Heap *H, int idxfather);

/*
 * Funcion: Heap_IdxFather
 * --------------------------
 * Modo de uso:
 * Heap H;
 * int pos, pospadre;
 * pospadre = Heap_IdxFather(H, pos);
 * Descripcion:
 * Calcula la posicion del padre de un nodo de posicion pos en 
 * el Heap. Si pos es 0(la raiz), retorna -1 
 */
static int heapIdxFather(Heap *H, int idx);


/*
 * Funcion: Heap_Adjust
 * --------------------------
 * Modo de uso:
 * Heap H;
 * int posnodo;
 * Heap_Adjust(&H, posnodo, Generico_CompararEnteros);
 * Descripcion:
 * Arregla el Heap desde un nodo de posicion posnodo en el Heap
 * NOTA: Solo funciona si el unico da�o es en esa posicion, si hay mas
 * da�os en el resto del arbol NO LOS ARREGLA
 */
static void heapFix(Heap *H, int idx);

/*
 * Funcion: Heap_CompareXTipe
 * --------------------------
 * Modo de uso:
 * Heap H;
 * THeap tipo=Heap_ASC;
 * Generic a, b;
 * if(Heap_CompareXTipe(Heap_ASC, a, b, Generico_CompararEnteros)>0)
 * Descripcion:
 * Si tipo es Heap_ASC:
 *		Retorna 1 si a es menor que b
 *		Retorna 0 si a es mayor que b
 * Si tipo es Heap_DESC
 *		Retorna 1 si a es mayor que b
 *		Retorna 0 si a es menro que b
 */
static int heapCompareXType(Heap *H, int idxa, int idxb);

static void heapSwap(Heap *H, int idxa, int idxb);

/************************IMPLEMENTACION*****************************/

int heapIsEmpty(Heap *H){
	return (H->nData == 0);
}

Heap *heapNew(int max, TSort type, cmpfn cmp){
	Heap *H;
	int i;
	H = malloc(sizeof(Heap));
	H->Data = malloc(sizeof(Generic)* max);
	for(i = 0; i < max; i++)
		H->Data[i] = NULL;
	H->max = max;
	H->nData = 0;
	H->type = type;
        H->cmp = cmp;
	return H;
}


List *heapSort(Heap *H){
	List *LOrdenada;
	Generic elemento;
	LOrdenada = listNew();
	while(!heapIsEmpty(H)){
		elemento = heapDeQueue(H);
		listAddNode(LOrdenada, nodeListNew(elemento));
	}
	return LOrdenada;
}


Generic heapDeQueue(Heap *H){
	Generic gmax;
	if(!heapIsEmpty(H)){
		gmax = H->Data[0];
		heapSwap(H,0,H->nData-1);
		H->nData --;
                heapFix(H, 0);
		return gmax;
	}
	return NULL;
}


void heapEnQueue(Heap *H, Generic G){
	int padre, i;
	if(H->nData < H->max){
		H->Data[H->nData] = G;
		H->nData++;
		i = H->nData-1;
		padre = heapIdxFather(H,i);
		while((i>=0 && padre>=0) && heapCompareXType(H,i, padre)){
			heapSwap(H,i,padre);
			i = padre;
			padre = heapIdxFather(H,i);
		}
	}
}


int heapIdxLeft(Heap *H, int pospadre){
	int indiceizq;
	indiceizq = pospadre *2	+1;
	if(indiceizq < H->nData) return indiceizq;
	return -1;
}
int heapIdxRight(Heap *H, int pospadre){
	int indiceder;
	indiceder = pospadre *2	+2;
	if(indiceder < H->nData) return indiceder;
	return -1;
}
int heapIdxFather(Heap *H, int poshijo){
	int indicepadre;
	indicepadre = (poshijo-1)/2;
	if(poshijo!=0) return indicepadre;
	return -1;
}

static void heapFix(Heap *H, int posnodo){
	int pos_mayor, izq, der;
	pos_mayor = posnodo;
	izq = heapIdxLeft(H, posnodo);
	der = heapIdxRight(H, posnodo);
	if(izq>=0 && heapCompareXType(H,izq,posnodo))
		pos_mayor = izq;
	if(der>=0 && heapCompareXType(H,der,pos_mayor))
		pos_mayor = der;
	if(pos_mayor != posnodo){
		heapSwap(H,pos_mayor,posnodo);
		heapFix(H,pos_mayor);
	}
}

static int heapCompareXType(Heap *H, int idxa, int idxb){
	if(H->type == DESC)
		return (H->cmp(H->Data[idxa],H->Data[idxb]) > 0);
	else if(H->type == ASC)
		return (H->cmp(H->Data[idxa],H->Data[idxb]) < 0);
	return -1;
}
Generic heapGetDatum(Heap *H, int i){
	return H->Data[i];
}

int heapGetSize(Heap *H){
    return H->nData;
}

void heapPrint(Heap *H, printfn print){
    int i;
    for(i = 0; i< H->nData; i++){
        print(H->Data[i]);
    }
}

void heapMake(Heap *H){
	int i;
	for(i = H->nData/2-1; i >= 0; i --){
		heapFix(H, i);
	}
}

static void heapSwap(Heap *H, int idxa, int idxb){
    Generic tmp;
    tmp = H->Data[idxa];
    H->Data[idxa] = H->Data[idxb];
    H->Data[idxb] = tmp;
}