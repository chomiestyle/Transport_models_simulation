#ifndef DICCIONARIO_H
#define DICCIONARIO_H
typedef struct Diccionario Diccionario;
typedef struct Nodo Nodo;

struct Nodo {
    const char* nombre;
    double valor;
};

struct Diccionario{
    Nodo **Nodos ;
    int  tamano ;
    
};

Diccionario *diccionario_nuevo (void);
void diccionario_agrega (Diccionario *D,const char* nuevo_nombre,double nuevo_valor);
void diccionario_muestra (const Diccionario *D);
void diccionario_aumenta (Diccionario **D, int unidades);
void diccionario_libera (Diccionario *D);
void diccionario_copia (const Diccionario *Do,Diccionario *Dd, int cantidad);
void diccionario_inicializa_contenido (Diccionario *D);
double diccionario_busca_significado(Diccionario *D,const char* nombre);



#endif
