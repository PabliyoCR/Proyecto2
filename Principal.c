// Librerias Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
#include "Grafos_Structs.h"

// Lista Global
ListaVertices* grafo = NULL;

// Metodos
#include "Grafos_Metodos.h"

// Menu de navegacion
#include "Navegacion.h"

int main(void)
{
    grafo = crearListaVertices();

    Vertice *vv;
    Vertice *ww;
    Vertice *xx;
    vv = crearVertice("san_ramon", "Alajuela", 200);
    ww = crearVertice("palmares", "Alajuela", 100);
    xx = crearVertice("guadalupe", "SanJose", 300);

    menuPrincipal();


    return 0;
}