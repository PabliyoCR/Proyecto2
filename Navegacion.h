int op;
int opListasIntercambio;

// Menu de navegacion principal
void menuPrincipal(){
    while(op != 4){
        system("cls");
        printf("--- MENU PRINCIPAL ---\n\n");
        printf("1. Gestionar Grafo\n");
        printf("2. Simulacion de Transporte\n");
        printf("3. Estadisticas\n");
        printf("4. Salir\n");
        printf("\n Ingresa una opcion: ");
        scanf("%i", &op);
        switch (op){
            case 1:
                gestionarGrafo();
                break;
            case 2:
                break;
            case 3:
                break;
        }                                   
        fflush(stdin);
    }   
}

void gestionarGrafo(){
    while(op != 6){
        system("cls");
        printf("--- GESTIONAR GRAFO ---\n\n");
        printf("1. Crear Vertices del Grafo\n");
        printf("2. Eliminar Vertices del Grafo\n");
        printf("3. Crear Camino (Arista) del Grafo\n");
        printf("4. Eliminar Camino (Arista) del Grafo\n");
        printf("5. Visualizar Grafo\n");
        printf("6. Regresar\n");
        printf("\n Ingresa una opcion: ");
        scanf("%i", &op);
        switch (op){
            case 1:
                menuCrearVertice();
                break;
            case 2:
                menuEliminarVertice();
                break;
            case 3:
                menuCrearCamino();
                break;
            case 4:
                menuEliminarCamino();
                break;
            case 5:
                imprimirGrafo();
                break;
        }            
        fflush(stdin);
    }   
}