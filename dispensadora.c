#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define len_productos 4

int temp_dinero = 0, dinero_clientes = 0, band_dincliente = 1,
menu_eleccion = 0, ciclo = 0, k = 7, l = 5,
productos_precios[len_productos][len_productos];

bool maquinaConfigurada = false;

void menu();

char buffer[1024];
char buffer2[1024];

char cliente_eleccion[2];

char*** matrizDeNombres;
char*** matrizDeCodigos;

int precioDeProductos[len_productos][len_productos],
cantidadDeProductos[len_productos][len_productos],
monedas1 = 0, monedas2 = 0, monedas5 = 0, monedas10 = 0, monedas20 = 0;

int length = 0, i = 0, j = 0, n = 0;

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
	i = 10;
	while(dinero_clientes > 0) {
		gotoxy(55, i);
		if(dinero_clientes >= 20) {
			dinero_clientes -= 20;
			monedas20--;
			printf("Devolviendo... $ 20 MXN");
		}else if(dinero_clientes >= 10) {
			dinero_clientes -= 10;
			monedas10--;
			printf("Devolviendo... $ 10 MXN");
		}else if(dinero_clientes >= 5) {
			dinero_clientes -= 5;
			monedas5--;
			printf("Devolviendo... $ 5 MXN");
		}else if(dinero_clientes >= 2) {
			dinero_clientes -= 2;
			monedas2--;
			printf("Devolviendo... $ 2 MXN");
		}else if(dinero_clientes >= 1) {
			dinero_clientes -= 1;
			monedas1--;
			printf("Devolviendo... $ 1 MXN");
		}
		i++;
		sleep(1);
	}
	i+=2;
	gotoxy(49, i);
	printf("Dinero del cliente en la m%cquina: %i", 160, dinero_clientes);
	sleep(4);
	menu();
}

void devolverDineroComprando(int _i, int sleep1, int sleep2) {
	while(dinero_clientes > 0) {
		_i++;
		gotoxy(60, _i);
		if(dinero_clientes >= 20) {
			dinero_clientes -= 20;
			monedas20--;
			printf("Devolviendo... $ 20 MXN\n");
		} else if(dinero_clientes >= 10) {
			dinero_clientes -= 10;
			monedas10--;
			printf("Devolviendo... $ 10 MXN\n");
		} else if(dinero_clientes >= 5) {
			dinero_clientes -= 5;
			monedas5--;
			printf("Devolviendo... $ 5 MXN\n");
		} else if(dinero_clientes >= 2) {
			dinero_clientes -= 2;
			monedas2--;
			printf("Devolviendo... $ 2 MXN\n");
		} else if(dinero_clientes >= 1) {
			dinero_clientes -= 1;
			monedas1--;
			printf("Devolviendo... $ 1 MXN\n");
		}
		sleep(sleep1);
	}
	sleep(sleep2);
	band_dincliente = 1;
}

//int configurarMaquina() {
//    system("cls");
//    gotoxy(36, 2);
//    printf("---------------- CONFIGURAR MAQUINA EXPENDEDORA -------------\n");
//    for (i = 0; i < len_productos; i++) {
//        matrizDeNombres[i] = malloc(sizeof(char*) * len_productos);
//        for (j = 0; j < len_productos; j++) {
//            matrizDeNombres[i][j] = NULL;
//        }
//    }
//    for (i = 0; i < len_productos; i++) {
//        matrizDeCodigos[i] = malloc(sizeof(char*) * len_productos);
//        for (j = 0; j < len_productos; j++) {
//            matrizDeCodigos[i][j] = NULL;
//        }
//    }
//    ciclo = 3;
//    for (i = 0; i < len_productos; i++) {
//        for (j = 0; j < len_productos; j++) {
//            gotoxy(36, ciclo);
//            printf("Nombre del producto: [%i][%i]\n", i, j);
//            ciclo++;
//            gotoxy(36, ciclo);
//            ciclo++;
//            getchar();
//            fgets(buffer, 1024, stdin);
//            buffer[strcspn(buffer, "\n")] = 0;
//            
//            length = strlen(buffer) + 1;
//            matrizDeNombres[i][j] = malloc(sizeof(char) * length);
//            strcpy(matrizDeNombres[i][j], buffer);
//            
//            gotoxy(36, ciclo);
//            printf("Ingresa c%cdigo del producto [CODE]: [%i][%i]\n", 162, i, j);
//            ciclo++;
//            gotoxy(36, ciclo);
//            ciclo++;
//			fgets(buffer2, 1024, stdin);
//            buffer2[strcspn(buffer2, "\n")] = 0;
//            
//            matrizDeCodigos[i][j] = malloc(sizeof(char) * strlen(buffer2) + 1);
//            strcpy(matrizDeCodigos[i][j], buffer2);
//            
//            gotoxy(36, ciclo);
//            printf("Precio del producto $: [%i][%i]\n", i, j);
//            ciclo++;
//            gotoxy(36, ciclo);
//            ciclo++;
//            scanf("%i", &precioDeProductos[i][j]);
//            
//            gotoxy(36, ciclo);
//            printf("Cantidad de producto [NUM]: [%i][%i]\n", i, j);
//            ciclo++;
//            gotoxy(36, ciclo);
//            ciclo++;
//            scanf("%i", &cantidadDeProductos[i][j]);
//        }
//    }
//    ciclo++;
//    gotoxy(36, ciclo);
//    printf("Ingresa cantidad de dinero que habr%c disponible en la m%cquina expendedora:\n", 160, 160);
//    scanf("%i", &dinero_maquina);
//    maquinaConfigurada = true;
//    system("cls");
//    menu();
//    return 0;
//}

int contabilizarDineroMaquina() {
	return monedas1 + (monedas2 * 2) + (monedas5 * 5) + (monedas10 * 10) + (monedas20 * 20);
}

bool puedoRegresarCambio(int i, int j, int dinero_cli) {
    int resultado = dinero_cli - precioDeProductos[i][j];
    int monedas[] = {20, 10, 5, 2, 1};
    int cantidades[] = {monedas20, monedas10, monedas5, monedas2, monedas1};
    for (n = 0; n < 5 && resultado > 0; ++n) {
        while (resultado >= monedas[n] && cantidades[n] > 0) {
            resultado -= monedas[n];
            cantidades[n]--;
        }
    }
    return resultado == 0;
}

int configurarMaquina() {
    system("cls");
    gotoxy(36, 2);
    printf("---------------- CONFIGURAR MAQUINA EXPENDEDORA -------------\n");

    const char* nombres[len_productos][len_productos] = {
        {"Agua", "Refresco", "Snack", "Galletas"},
        {"Jugos", "Dulces", "Chocolates", "Papas"},
        {"Chicles", "Yogurt", "Energizante", "Sandwich"},
        {"Cafe", "Te", "Fruta", "Cereal"}
    };

    const char* codigos[len_productos][len_productos] = {
        {"A1", "A2", "A3", "A4"},
        {"B1", "B2", "B3", "B4"},
        {"C1", "C2", "C3", "C4"},
        {"D1", "D2", "D3", "D4"}
    };

    int precios[len_productos][len_productos] = {
        {10, 15, 12, 8},
        {20, 5, 18, 10},
        {3, 25, 22, 15},
        {12, 6, 20, 13}
    };

    int cantidades[len_productos][len_productos] = {
        {5, 7, 10, 12},
        {4, 8, 3, 6},
        {15, 10, 5, 9},
        {3, 11, 2, 4}
    };

    for (i = 0; i < len_productos; i++) {
        matrizDeNombres[i] = malloc(sizeof(char*) * len_productos);
        matrizDeCodigos[i] = malloc(sizeof(char*) * len_productos);
        for (j = 0; j < len_productos; j++) {
            matrizDeNombres[i][j] = malloc(strlen(nombres[i][j]) + 1);
            strcpy(matrizDeNombres[i][j], nombres[i][j]);

            matrizDeCodigos[i][j] = malloc(strlen(codigos[i][j]) + 1);
            strcpy(matrizDeCodigos[i][j], codigos[i][j]);

            precioDeProductos[i][j] = precios[i][j];

            cantidadDeProductos[i][j] = cantidades[i][j];
        }
    }

    monedas1 = 0;
    monedas2 = 0;
    monedas5 = 0;
    monedas10 = 2;
    monedas20 = 0;
    maquinaConfigurada = true;
    system("cls");
    menu();
    return 0;
}

void comprarProducto() {
	system("cls");
	gotoxy(0, 0);
	printf("Dinero en m%cquina: $ %i", 160, contabilizarDineroMaquina());
	gotoxy(0, 1);
	printf("| [1]: %i | [2]: %i | [5]: %i | [10]: %i | [20]: %i |",
	  monedas1, monedas2, monedas5, monedas10, monedas20);
	gotoxy(0, 2);
	printf("Dinero del cliente: %i", dinero_clientes);
	gotoxy(0, 4);
	printf("**************** M%cquina expendedora *******************", 160);
	gotoxy(0, 5);
	printf("+-----------------------------------------------------+");
	gotoxy(0, 6);
	printf("| +-------------------------------------------------+ |");
	for(i = 7; i < 28; i++) {
		gotoxy(0, i);
		printf("| |                                                 | |");
	}
	for(i = 0; i < len_productos; i++) {
		if(i != 0) {
			k += 5;
		}
		for(j = 0; j < len_productos; j++) {
			gotoxy(l, k);
			printf("%s", matrizDeNombres[i][j]);
			gotoxy(l, k + 1);
			printf("%s", matrizDeCodigos[i][j]);
			gotoxy(l, k + 2);
			printf("%c%i", 36, precioDeProductos[i][j]);
			gotoxy(l, k + 3);
			printf("CANT %i", cantidadDeProductos[i][j]);
			l += 12;
		}
		gotoxy(0, k + 4);
		printf("| +-------------------------------------------------+ |");
		l = 5;
	}
	printf("\n| +-------------------------------------------------+ |\n");
	printf("+-----------------------------------------------------+\n");
	k = 7;
	l = 5;
	gotoxy(60, 5);
	printf("Ingrese el c%cdigo del producto o 'C' para cancelar:", 162);
	gotoxy(60, 6);
	scanf("%s", cliente_eleccion);

	if (strcmp(cliente_eleccion, "C") == 0 || strcmp(cliente_eleccion, "c") == 0) {
		gotoxy(60, 7);
		printf("Compra cancelada. Regresando al men%c principal...", 163);
		gotoxy(60, 8);
		printf("Devolviendo cambio restante...\n");
		devolverDineroComprando(15, 1, 2);
		menu();
		return;
	}

	for(i = 0; i < len_productos; i++) {
		for(j = 0; j < len_productos; j++) {
			if(strcmp(cliente_eleccion, matrizDeCodigos[i][j]) == 0
			&& dinero_clientes >= precioDeProductos[i][j]
			&& cantidadDeProductos[i][j] > 0
			&& puedoRegresarCambio(i, j, dinero_clientes)) {
				dinero_clientes -= precioDeProductos[i][j];
				cantidadDeProductos[i][j]--;
				gotoxy(60, 19);
				printf("Comprado: %s\n", matrizDeNombres[i][j]);
				gotoxy(60, 30);
				printf("Cantidad en stock actualizada: %i\n", cantidadDeProductos[i][j]);
				gotoxy(60, 20);
				printf("Devolviendo cambio restante...\n");
				devolverDineroComprando(21, 1, 3);
				menu();
				return;
			}
		}
	}
	gotoxy(60, 20);
	printf("Producto no encontrado o dinero insuficiente del cliente o la m%cquina.\n", 160);
	devolverDineroComprando(20, 1, 3);
	menu();
}

void ingresarDinero() {
	system("cls");
	i = 2;
	while(band_dincliente == 1) {
		i++;
		gotoxy(50, i);
		printf("Ingrese monedas o billetes: [1][2][5][10][20]");
		i++;
		gotoxy(50, i);
		scanf("%i", &temp_dinero);
        if (temp_dinero == 1 || temp_dinero == 2 || temp_dinero == 5 || temp_dinero == 10 || temp_dinero == 20) {
            dinero_clientes += temp_dinero;
            if (temp_dinero == 1) monedas1++;
            if (temp_dinero == 2) monedas2++;
            if (temp_dinero == 5) monedas5++;
            if (temp_dinero == 10) monedas10++;
            if (temp_dinero == 20) monedas20++;
        } else {
            printf("Moneda no válida. Ingrese nuevamente.\n");
        }
		i+=2;
		gotoxy(50, i);
		printf("%cQuiere continuar agregando dinero? SI = 1, NO = 0", 168);
		i++;
		gotoxy(50, i);
		scanf("%i", &band_dincliente);
	}
	system("cls");
	band_dincliente = 1;
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
		sleep(5);
		menu();
	}else {
		devolverDinero();
	}
}

void estaConfigurada() {
	if(maquinaConfigurada && dinero_clientes > 0) {
		comprarProducto();
	}else {
		system("cls");
		gotoxy(37, 13);
		printf("+------------------------------------------------------------+");
		gotoxy(37, 15);
		printf("| No se ha configurado la m%cquina, seleccione 3 en el men%c   |", 160, 163);
		gotoxy(37, 16);
		printf("|       O no tiene dinero ingresado en la m%cquina            |", 160);
		gotoxy(37, 18);
		printf("+------------------------------------------------------------+");
		sleep(5);
		menu();
	}
}

void menu() {
	system("cls");
	gotoxy(40, 2);
	printf("Dinero de la m%cquina: %i", 
	160, contabilizarDineroMaquina());
	gotoxy(40, 3);
	printf("| [$1]: %i | [$2]: %i | [$5]: %i | [$10]: %i | [$20]: %i |",
	monedas1, monedas2, monedas5, monedas10, monedas20);
	gotoxy(40, 5);
	printf("Dinero del cliente: %i", dinero_clientes);
	gotoxy(40, 7);
	printf("+-------------------------------------------------------+");
	gotoxy(40, 8);
	printf("| Men%c                                                  |", 163);
	gotoxy(40, 9);
	printf("| Digita un numero para acceder al apartado deseado:    |");
	gotoxy(40, 11);
	printf("| 1. Ver productos disponibles                          |");
	gotoxy(40, 12);
	printf("| 2. Ingresar dinero para comprar                       |");
	gotoxy(40, 13);
	printf("| 3. Configurar m%cquina expendedora                     |", 160);
	gotoxy(40, 14);
	printf("| 4. Devolverme mi dinero                               |");
	gotoxy(40, 15);
	printf("+-------------------------------------------------------+");
	gotoxy(40, 18);
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
