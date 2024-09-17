#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define len_productos 1

int temp_dinero = 0, dinero_clientes = 0, band_dincliente = 1,
menu_eleccion = 0, dinero_maquina = 0, productos_precios[4][4];

char buffer[1024];
char*** matrizDeNombres; // El 4 es porque son 4 filas y 4 columnas
int precioDeProductos[len_productos][len_productos];

void gotoxy(int x, int y) {
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
}

void menu() {
	gotoxy(40, 5);
	printf("+-------------------------------------------------------+");
	gotoxy(40, 6);
	printf("| Men%c                                                  |", 163);
	gotoxy(40, 8);
	printf("| Digita un numero para acceder al apartado deseado:    |");
	gotoxy(40, 9);
	printf("| 1. Ver productos disponibles                          |");
	gotoxy(40, 10);
	printf("| 2. Ingresar dinero para comprar                       |");
	gotoxy(40, 11);
	printf("| 3. Configurar m%quina expendedora                      |", 160);
	gotoxy(40, 12);
	printf("+-------------------------------------------------------+");
	gotoxy(40, 14);
	scanf("%i", &menu_eleccion);
	switch(menu_eleccion) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			configurarMaquina();
			break;
	}
}

int configurarMaquina() {
    int i = 0, j = 0;
    
    // Inicializa la matriz de nombres
    for (i = 0; i < len_productos; i++) {
        matrizDeNombres[i] = malloc(sizeof(char*) * len_productos);
        for (j = 0; j < len_productos; j++) {
            matrizDeNombres[i][j] = NULL;  // Inicializar a NULL
        }
    }
    
    // Llenar la matriz con datos del usuario
    for (i = 0; i < len_productos; i++) {
        for (j = 0; j < len_productos; j++) {
            // Leer el nombre del producto
            printf("Nombre del producto: [%i][%i]\n", i, j);
            getchar();
            // Leer Strings
            fgets(buffer, 1024, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            
            printf("Precio del producto: [%i][%i]\n", i, j);
            scanf("%i", &precioDeProductos[i][j]);
            
            int length = strlen(buffer) + 1;
            matrizDeNombres[i][j] = malloc(sizeof(char) * length);
            strcpy(matrizDeNombres[i][j], buffer);
        }
    }
    printf("Ingresa cantidad de dinero que habr%c disponible en la m%cquina expendedora:\n", 160, 160);
    scanf("%i", &dinero_maquina);
    system("cls");
    comprarProducto();
    return 0;
}

void comprarProducto() {
	
}

void ingresarDinero() {
	while(band_dincliente == 1) {
		printf("Ingrese monedas o billetes: [1][2][5][10][20]\n");
		scanf("%i", &temp_dinero);
		if(temp_dinero % 5 == 0 || temp_dinero == 2 || temp_dinero == 1) {
			dinero_clientes += temp_dinero;
		}else {
			printf("\nNo puede agregar esa moneda o billete\n\n");
		}
		printf("%cQuiere continuar agregando dinero? SI = 1, NO = 0\n", 168);
		scanf("%i", &band_dincliente);
	}
	system("cls");
	menu();
}

void seleccionarProducto() {
	printf("***************************");
	printf("Máquina Expendedora");
	
	
	
	printf("***************************");
}

int main() {
	matrizDeNombres = malloc(sizeof(char**) * len_productos);
	
	menu();
	
	//ingresarDinero();
	
	//seleccionarProducto();
	
	
	return 0;
	
}
