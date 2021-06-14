typedef struct Vertice Vertice;
typedef struct ListaVertices ListaVertices;
typedef struct Camino Camino;
typedef struct CaminosListaAdyacencia CaminosListaAdyacencia;

struct Vertice
{
    char nombreLugar[30];
    char provincia[30];
    unsigned poblacionAprox;
    CaminosListaAdyacencia* caminos;
    Vertice* verticeSiguiente;
};

struct ListaVertices
{
    Vertice *inicio;
};

struct Camino
{
    unsigned tiempo;
    unsigned distancia;
    Camino* caminoSiguiente;
    Vertice* destino;
};

struct CaminosListaAdyacencia
{
    Camino *inicio;
};
