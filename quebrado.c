#include <quebrado.h>
#include <stdlib.h>
#include <stdio.h>

Quebrado *quebradoNew(int nuevonum, int nuevoden){
    Quebrado *nuevo;
    nuevo = malloc(sizeof(Quebrado));
    nuevo->n = nuevonum;
    nuevo->d = nuevoden;
    return nuevo;
}

void quebradoSetNum(Quebrado *q, int nuevonum){
    q->n = nuevonum;
}
void quebradoSetDen(Quebrado *q, int nuevoden){
    q->d = nuevoden;
}
int quebradoGetNum(Quebrado *q){
    return q->n;
}
int quebradoGetDen(Quebrado *q){
    return q->d;
}



Quebrado *quebradoSumar(Quebrado *a, Quebrado *b){
    return quebradoNew(a->n * b->d + b->n * a->d, a->d * b->d);

}


int quebradoCmpxNum(Quebrado *a, int *valor){
    if(a->n == *valor) return 0;
    else if(a->n > *valor) return 1;
    return -1;
}
int quebradoCmpDenominadores(Quebrado *a, Quebrado *quebrado){
    if(a->d == quebrado->d) return 0;
    else if(a->d > quebrado->d) return 1;
    return -1;
    
}

void quebradoPrint(Quebrado *a){
    printf("%d / %d \n", a->n, a->d);
}



