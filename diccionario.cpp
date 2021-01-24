#include "diccionario.h"
#include <stdlib.h>
#include "iostream"
#include <cstring>

using namespace std;

Diccionario  *diccionario_nuevo (void){
    Diccionario *D = new Diccionario;
    D->Nodos=NULL;
    D->tamano=0;
    return D;
}
void diccionario_agrega(Diccionario *D, const char* nuevo_nombre,double nuevo_valor){
        diccionario_aumenta(&D,1);
        D->Nodos[D->tamano-1]->nombre=nuevo_nombre;
        D->Nodos[D->tamano-1]->valor=nuevo_valor;
}
void diccionario_muestra(const Diccionario *D){
    int i;
    for (i=0;i<D->tamano;++i){
        const char* nombre_nodo = D->Nodos[i]->nombre;
        double valor_nodo = D->Nodos[i]->valor;
        cout << nombre_nodo<< ":"<<valor_nodo <<endl;
    }
}
void diccionario_aumenta(Diccionario **D, int unidades){
    Diccionario *E = diccionario_nuevo();
    E->tamano=(**D).tamano;
    E->Nodos=new Nodo* [E->tamano];
    diccionario_inicializa_contenido(E);
    diccionario_copia(*D,E,E->tamano);
    diccionario_libera(*D);
    *D=diccionario_nuevo();
    (**D).tamano= E->tamano + unidades;
    (**D).Nodos=new Nodo*[(**D).tamano];
    diccionario_inicializa_contenido(*D);
    diccionario_copia(E, *D,E->tamano);
    diccionario_libera(E);
}

void diccionario_copia(const Diccionario *Do,Diccionario *Dd, int cantidad){
    int i;
    for ( i=0; i<cantidad;++i){
        Dd->Nodos[i]->nombre= Do->Nodos[i]->nombre;
        Dd->Nodos[i]->valor= Do->Nodos[i]->valor;
        }
}
void diccionario_inicializa_contenido(Diccionario *D){
    int i;
    for (i=0; i<D->tamano;++i){
        D->Nodos[i]=new Nodo ;
        D->Nodos[i]->nombre=NULL;
        D->Nodos[i]->valor=0;
        }
}
void diccionario_libera(Diccionario *D){
    int i;
    for ( i = 0;i<D->tamano;++i){
        delete D->Nodos[i];
    }
    delete D->Nodos;
    delete D;
}
double diccionario_busca_significado(Diccionario *D,const char* nombre){
    int j;
    for (j=0; j<D->tamano;++j){
    const char *nombre_busqueda=D->Nodos[j]->nombre;
    int valor=strcmp(nombre_busqueda,nombre);
    if (valor==0){
            return D->Nodos[j]->valor;
        }
        
    }
    return 0;


}

