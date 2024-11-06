#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define len_productos 2

int temp_dinero = 0, dinero_clientes = 0, band_dincliente = 1,
menu_eleccion = 0, dinero_maquina = 0, 
productos_precios[len_productos][len_productos];

bool maquinaConfigurada = false;

void menu();

char buffer[1024];
char*** matrizDeNombres;
char*** matrizDeCodigos;

int precioDeProductos[len_productos][len_productos],
cantidadDeProductos[len_productos][len_productos];

int length = 0, i = 0, j = 0;

void gotoxy(int x, int y) {
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
}

void devolverDinero() {
	system("cls");
	int i = 10;	
	while(dinero_clientes > 0) {
		gotoxy(55, i);
		if(dinero_clientes >= 20) {
			dinero_clientes -= 20;
			printf("Devolviendo... $ 20 MXN");
		}else if(dinero_clientes >= 10) {
			dinero_clientes -= 10;
			printf("Devolviendo... $ 10 MXN");
		}else if(dinero_clientes >= 5) {
			dinero_clientes -= 5;
			printf("Devolviendo... $ 5 MXN");
		}else if(dinero_clientes >= 2) {
			dinero_clientes -= 2;
			printf("Devolviendo... $ 2 MXN");
		}else if(dinero_clientes >= 1) {
			dinero_clientes -= 1;
			printf("Devolviendo... $ 1 MXN");
		}
		i++;
		Sleep(1);
	}
	i+=2;	
	gotoxy(49, i);
	printf("Dinero del cliente en la m%cquina: %i", 160, dinero_clientes);
	Sleep(4);
	menu();
}

int configurarMaquina() {
    system("cls");
    printf("---------------- CONFIGURAR MAQUINA EXPENDEDORA -------------\n");
    for (i = 0; i < len_productos; i++) {
        matrizDeNombres[i] = malloc(sizeof(char*) * len_productos);
        for (j = 0; j < len_productos; j++) {
            matrizDeNombres[i][j] = NULL;
        }
    }
    for (i = 0; i < len_productos; i++) {
        matrizDeCodigos[i] = malloc(sizeof(char*) * len_productos);
        for (j = 0; j < len_productos; j++) {
            matrizDeCodigos[i][j] = NULL;
        }
    }
    for (i = 0; i < len_productos; i++) {
        for (j = 0; j < len_productos; j++) {
            printf("Nombre del producto: [%i][%i]\n", i, j);
            getchar();
            fgets(buffer, 1024, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            
            length = strlen(buffer) + 1;
            matrizDeNombres[i][j] = malloc(sizeof(char) * length);
            strcpy(matrizDeNombres[i][j], buffer);
            fflush(stdin);
            
            printf("Ingresa c%cdigo del producto [CODE]: [%i][%i]\n", 162, i, j);
            getchar();
            fgets(buffer, 1024, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            
            length = strlen(buffer) + 1;
            matrizDeCodigos[i][j] = malloc(sizeof(char) * length);
            strcpy(matrizDeCodigos[i][j], buffer);
            fflush(stdin);
            
            printf("Precio del producto $: [%i][%i]\n", i, j);
            scanf("%i", &precioDeProductos[i][j]);
            
            printf("Cantidad de producto [NUM]: [%i][%i]\n", i, j);
            scanf("%i", &cantidadDeProductos[i][j]);
        }
    }
    printf("Ingresa cantidad de dinero que habr%c disponible en la m%cquina expendedora:\n", 160, 160);
    scanf("%i", &dinero_maquina);
    maquinaConfigurada = true;
    system("cls");
    menu();
    return 0;
}

void comprarProducto() {
	system("cls");
	int i = 0, j = 0, k = 3, l = 5;
	gotoxy(0, 0);
	printf("**************** M%cquina expendedora *******************", 160);
	gotoxy(0, 1);
	printf("+-----------------------------------------------------+");
	gotoxy(0, 2);
	printf("| +-------------------------------------------------+ |");
	for(i = 3; i < 15; i++) {
		gotoxy(0, i);
		printf("| |                                                 | |");
	}
	for(i = 0; i < len_productos; i++) {
		if(i != 0) {
			k+=5;
		}
		for(j = 0; j < len_productos; j++) {
			gotoxy(l, k);
			printf("%s", matrizDeNombres[i][j]);
			gotoxy(l, k+1);
			printf("%s", matrizDeCodigos[i][j]);
			gotoxy(l, k+2);
			printf("%c%i", 36, precioDeProductos[i][j]);
			gotoxy(l, k+3);
			printf("CANT %i", cantidadDeProductos[i][j]);
			l+=12;
		}
		gotoxy(0, k+4);
		printf("| +-------------------------------------------------+ |");
		l = 5;
	}
	printf("\n| +-------------------------------------------------+ |\n");
	printf("+-----------------------------------------------------+\n");
}

void ingresarDinero() {
	system("cls");
	int i = 2;
	while(band_dincliente == 1) {
		i++;
		gotoxy(50, i);
		printf("Ingrese monedas o billetes: [1][2][5][10][20]");
		i++;
		gotoxy(50, i);
		scanf("%i", &temp_dinero);
		if(temp_dinero % 5 == 0 || temp_dinero == 2 || temp_dinero == 1) {
			dinero_clientes += temp_dinero;
		}else {
			i++;
			gotoxy(50, i);
			printf("No puede agregar esa moneda o billete");
		}
		i+=2;
		gotoxy(50, i);
		printf("%cQuiere continuar agregando dinero? SI = 1, NO = 0", 168);
		i++;
		gotoxy(50, i);
		scanf("%i", &band_dincliente);
	}
	system("cls");
	menu();
}

void sePuedeDevolver() {
	if(dinero_clientes <= 0) {
		system("cls");
		gotoxy(47, 13);
		printf("+-----------------------------------------+");
		gotoxy(47, 15);
		printf("| No se ha ingresado dinero en la m%cquina |", 160);
		gotoxy(47, 17);
		printf("+-----------------------------------------+");
		Sleep(5);
		menu();
	}else {
		devolverDinero();
	}
}

void estaConfigurada() {
	if(maquinaConfigurada) {
		comprarProducto();
	}else {
		system("cls");
		gotoxy(37, 13);
		printf("+------------------------------------------------------------+");
		gotoxy(37, 15);
		printf("| No se ha configurado la m%cquina, seleccione 3 en el men%c   |", 160, 163);
		gotoxy(37, 17);
		printf("+------------------------------------------------------------+");
		Sleep(5);
		menu();
	}
}

void menu() {
	system("cls");
	gotoxy(40, 2);
	printf("Dinero de la m%cquina: %i             Dinero del cliente: %i      ", 160, dinero_maquina, dinero_clientes);
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
	printf("| 3. Configurar m%cquina expendedora                     |", 160);
	gotoxy(40, 12);
	printf("| 4. Devolverme mi dinero                               |");
	gotoxy(40, 13);
	printf("+-------------------------------------------------------+");
	gotoxy(40, 16);
	scanf("%i", &menu_eleccion);
	switch(menu_eleccion) {
		case 1:
			estaConfigurada();
			break;
		case 2:
			ingresarDinero();
			break;
		case 3:
			configurarMaquina();
			break;
		case 4:
			sePuedeDevolver();
			break;
	}
}

int main() {
	matrizDeNombres = malloc(sizeof(char**) * len_productos);
	matrizDeCodigos = malloc(sizeof(char**) * len_productos);
	menu();
	return 0;
}
