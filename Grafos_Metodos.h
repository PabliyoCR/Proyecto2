
// --- Prototipos ---

ListaVertices* crearListaVertices();
Vertice* crearVertice(char nombreLugar[30], char provincia[30], unsigned poblacionAprox);
void eliminarVertice(int pos);
CaminosListaAdyacencia* crearListaCaminos();
Camino* crearCamino(Vertice* VOrigen, Vertice* VDestino, unsigned tiempo, unsigned distancia);
void eliminarCamino(CaminosListaAdyacencia* CL, int pos);
void menuCrearVertice();
void menuEliminarVertice();
void menuCrearCamino();
void menuEliminarCamino();
void imprimirGrafo();
int menuSeleccionarVertice();
Vertice* obtenerVerticeEnPosicion(int pos);
void mostrarTodosCaminos();
int menuSeleccionarCaminoEnVertice(CaminosListaAdyacencia* CL);
Camino* obtenerCaminoEnPosicion(CaminosListaAdyacencia* CL, int pos);
int obtenerPosicionDeCaminoPorDestino(CaminosListaAdyacencia* CL, Vertice* VDestino);

// --- Definición de funciones ---

ListaVertices* crearListaVertices(){
    ListaVertices *L = (ListaVertices *) malloc(sizeof(ListaVertices));
    L->inicio = NULL;
    return L;
};

Vertice* crearVertice(char nombreLugar[30], char provincia[30], unsigned poblacionAprox){
    // Datos del vértice
    Vertice *V = (Vertice *) malloc(sizeof(Vertice));
    strcpy(V->nombreLugar, nombreLugar);
    strcpy(V->provincia, provincia);
    V->poblacionAprox = poblacionAprox;
    V->caminos = crearListaCaminos();;

    // Agregar un vertice al inicio de la lista de vertices
    V->verticeSiguiente = grafo->inicio;
    grafo->inicio = V;
    return V;
}

void eliminarVertice(int pos){
    Vertice* V, *V_prev;
    if(pos > 0){
        V_prev = obtenerVerticeEnPosicion(pos-1);
        V = V_prev->verticeSiguiente;
        V_prev->verticeSiguiente = V->verticeSiguiente;
    }else if(pos == 0){
        V = grafo->inicio;
        grafo->inicio = V->verticeSiguiente;
    }
    // Eliminar caminos hacia el vertice a eliminar
    Camino* C;

    for(C = V->caminos->inicio; C != NULL; C = C->caminoSiguiente){
        eliminarCamino(C->destino->caminos, obtenerPosicionDeCaminoPorDestino(C->destino->caminos, V));
    }

    // Liberar espacio en memoria
    free(V);
}

CaminosListaAdyacencia* crearListaCaminos(){
    CaminosListaAdyacencia *L = (CaminosListaAdyacencia *) malloc(sizeof(CaminosListaAdyacencia));
    L->inicio = NULL;
    return L;
}

Camino* crearCamino(Vertice* VOrigen, Vertice* VDestino, unsigned tiempo, unsigned distancia){
    // Datos del camino
    Camino *C = (Camino *) malloc(sizeof(Camino));
    C->tiempo = tiempo;
    C->distancia = distancia;
    C->destino = VDestino;
    // Agregar un camino al inicio de la lista de caminos de un vertice de origen
    if(VOrigen->caminos->inicio == NULL){
        C->caminoSiguiente = NULL;
        VOrigen->caminos->inicio = C;
    }else{
        C->caminoSiguiente = VOrigen->caminos->inicio;
        VOrigen->caminos->inicio = C;
    }
    return C;
}

void eliminarCamino(CaminosListaAdyacencia* CL, int pos){
    Camino *C, *C_prev;
    if(pos > 0){
        C_prev = obtenerCaminoEnPosicion(CL, pos-1);
        C = C_prev->caminoSiguiente;
        C_prev->caminoSiguiente = C->caminoSiguiente;
    }else if(pos == 0){
        C = CL->inicio;
        CL->inicio = C->caminoSiguiente;
    }
    free(C);
}

// --- Menus de navegación---

void menuCrearVertice(){
    system("cls");
    printf("--- CREAR VERTICE ---\n");
    char nombreLugar[30];
    char provincia[30];
    unsigned poblacionAprox;
    printf("\nIngrese Nombre del Lugar: ");
    scanf("%s", &nombreLugar);
    printf("\nIngrese Provincia: ");
    scanf("%s", &provincia);
    printf("\nIngrese Poblacion Aproximada: ");
    scanf("%i", &poblacionAprox);
    crearVertice(nombreLugar, provincia, poblacionAprox);
}

void menuEliminarVertice(){
    system("cls");
    printf("--- ELIMINAR VERTICE ---\n");
    printf("\nSeleccione un vertice a eliminar:\n");
    int pos = menuSeleccionarVertice();
    if(pos == 0){
        return;
    }
    eliminarVertice(pos-1);
}

void menuCrearCamino(){
    system("cls");
    printf("--- CREAR CAMINO ---\n");
    printf("\nSeleccione un vertice de origen:\n");
    int posOrigen = menuSeleccionarVertice();
    if(posOrigen == 0){
        return;
    }
    printf("\nSeleccione un vertice de destino:\n");
    int postDestino = menuSeleccionarVertice();
    if(postDestino == 0){
        return;
    }
    Vertice* vOrigen =  obtenerVerticeEnPosicion(posOrigen-1);
    Vertice* vDestino =  obtenerVerticeEnPosicion(postDestino-1);
    unsigned tiempo;
    unsigned distancia;
    printf("\nIngrese Tiempo de Recorrido: ");
    scanf("%i", &tiempo);
    printf("\nIngrese Distancia: ");
    scanf("%i", &distancia);

    // Creacion de camino, bidireccional
    crearCamino(vOrigen, vDestino, tiempo, distancia);
    crearCamino(vDestino, vOrigen, tiempo, distancia);
}
  
void menuEliminarCamino(){
    system("cls");
    printf("--- ELIMINAR CAMINO ---\n");
    printf("\nCaminos: ");
    mostrarTodosCaminos();
    printf("\n\nSeleccione un vertice origen o destino del camino a eliminar:\n");
    int posVertice = menuSeleccionarVertice();
    if(posVertice == 0){
        return;
    }
    Vertice* VOrigen =  obtenerVerticeEnPosicion(posVertice-1);
    printf("\nSeleccione el camino que debe eliminarse:\n");
    int posCamino = menuSeleccionarCaminoEnVertice(VOrigen->caminos);
    if(posVertice == 0){
        return;
    }
    Vertice* VDestino = obtenerCaminoEnPosicion(VOrigen->caminos, posCamino-1)->destino;
    eliminarCamino(VOrigen->caminos, posCamino-1);
    eliminarCamino(VDestino->caminos, obtenerPosicionDeCaminoPorDestino(VDestino->caminos, VOrigen));
}

void imprimirGrafo(){
    system("cls");
    printf("--- GRAFO ---\n");
    Vertice* v_i;
    for (v_i = grafo->inicio; v_i != NULL; v_i = v_i->verticeSiguiente)
    {
        printf("\nLugar: %s     Provincia: %s    Poblacion Aproximada: %i", v_i->nombreLugar, v_i->provincia, v_i->poblacionAprox);
        printf("\nVertices Adyacentes: ");
        if(v_i->caminos != NULL){
            Camino* c_i;
            for(c_i = v_i->caminos->inicio; c_i != NULL; c_i = c_i->caminoSiguiente){
                printf("%s ", c_i->destino->nombreLugar);
            }
        }
        printf("\n");
    }
    printf("\n\nPresione enter para continuar... ");
    fflush(stdin);
    getchar();
}

int menuSeleccionarVertice(){
    Vertice* v_i;
    unsigned i = 1;
    for (v_i = grafo->inicio; v_i != NULL; v_i = v_i->verticeSiguiente)
    {
        printf("\n%i. %s, %s", i, v_i->nombreLugar, v_i->provincia);
        i++;
    }
    printf("\n%i. Volver...", i);
    int opVertice;
    printf("\nIngrese opcion de vertice o seleccione Volver: ");
    scanf("%i", &opVertice);
    if(opVertice >= i || opVertice <= 0){
        if(opVertice != i){
            printf("\nOpcion invalida. Presione enter para continuar...");
            fflush(stdin);
            getchar();
        }
        return 0;
    }
    return opVertice;
}

Vertice* obtenerVerticeEnPosicion(int pos){
    Vertice* v_i;
    int i = 0;
    for (v_i = grafo->inicio; v_i != NULL; v_i = v_i->verticeSiguiente)
    {
        if(i == pos){
            return v_i;
        }
        i++;
    }
    return NULL;
}

void mostrarTodosCaminos(){
    Vertice* V_Aux;
    Camino* c_i;
    for(V_Aux = grafo->inicio; V_Aux != NULL; V_Aux = V_Aux->verticeSiguiente){
        for (c_i = V_Aux->caminos->inicio; c_i != NULL; c_i = c_i->caminoSiguiente)
        {
            printf("\n   - %s - %s", V_Aux->nombreLugar, c_i->destino->nombreLugar);
        }
    }
}

int menuSeleccionarCaminoEnVertice(CaminosListaAdyacencia* CL){
    Camino* c_i;
    unsigned i = 1;
    for (c_i = CL->inicio; c_i != NULL; c_i = c_i->caminoSiguiente)
    {
        printf("\n%i. %s", i, c_i->destino->nombreLugar);
        i++;
    }
    printf("\n%i. Volver...", i);
    int opCamino;
    printf("\nIngrese opcion de camino o seleccione Volver: ");
    scanf("%i", &opCamino);
    if(opCamino >= i || opCamino <= 0){
        if(opCamino != i){
            printf("\nOpcion invalida. Presione enter para continuar...");
            fflush(stdin);
            getchar();
        }
        return 0;
    }
    return opCamino;
}

Camino* obtenerCaminoEnPosicion(CaminosListaAdyacencia* CL, int pos){
    Camino* c_i;
    int i = 0;
    for (c_i = CL->inicio; c_i != NULL; c_i = c_i->caminoSiguiente)
    {
        if(i == pos){
            return c_i;
        }
        i++;
    }
    return NULL;
}

int obtenerPosicionDeCaminoPorDestino(CaminosListaAdyacencia* CL, Vertice* VDestino){
    int pos = 0;
    Camino* c_i;
    for (c_i = CL->inicio; c_i != NULL; c_i = c_i->caminoSiguiente)
    {
        if(c_i->destino == VDestino){
            return pos;
        }
        pos++;
    }
    return -1;
}