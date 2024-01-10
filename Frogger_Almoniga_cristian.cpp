#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <conio2.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

int corazones = 3;  // Agrega esta variable global para contar los corazones

// Función para posicionar el cursor en la consola
void irAxy(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon, &cci);
}

void pintar_limites() {
	for (int i = 2; i < 120; i++) {
		gotoxy(i, 3);
		printf("%c", 205);
		gotoxy(i, 30);
		printf("%c", 205);
	}
	
	for (int i = 4; i < 30; i++) {
		gotoxy(1, i);
		printf("%c", 186);
		gotoxy(120, i);
		printf("%c", 186);
	}
	
	gotoxy(1, 3);
	printf("%c", 201);
	gotoxy(1, 30);
	printf("%c", 200);
	gotoxy(120, 1);
	printf("%c", 187);
	gotoxy(120, 30);
	printf("%c", 188);
}

// Función para establecer el color del texto en la consola
void setColorTexto(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// Clase Rana
class Rana {
	int x, y;
	
public:
	Rana(int _x, int _y);
	void dibujar();
	void borrar();
	void mover(int direccion);
	void pintar_corazones();
};

Rana::Rana(int _x, int _y) : x(_x), y(_y) {}

void Rana::dibujar() {
	// Establece el color de fondo a verde y el color del texto a negro
	setColorTexto(FOREGROUND_GREEN);
	
	irAxy(x, y);
	printf("   \\_/");  // Cuerpo superior de la rana
	irAxy(x, y + 2);
	printf("  (o o)");  // Ojos de la rana
	irAxy(x, y + 3);
	printf(" /  V  \\");  // Cuerpo inferior de la rana
	
	// Restaura el color original de la consola
	setColorTexto(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void Rana::borrar() {
	irAxy(x, y);
	printf("       ");  // Cuerpo superior de la rana
	irAxy(x, y + 2);
	printf("       ");  // Ojos de la rana
	irAxy(x, y + 3);
	printf("         ");  // Cuerpo inferior de la rana
}

void Rana::mover(int direccion) {
	borrar();
	
	// Actualiza las coordenadas según la dirección
	switch (direccion) {
	case IZQUIERDA:
		if (x > 1)
			x--;
		break;
	case DERECHA:
		if (x + 1 > 18)
			x++;
		break;
	case ARRIBA:
		if (y > 4)
			y--;
		break;
	case ABAJO:
		if (y + 2 < 23)
			y++;
		break;
	}
	
	pintar_corazones();
	
	dibujar();
}

void Rana::pintar_corazones() {
	gotoxy(64, 2);
	printf("Salud");
	gotoxy(70, 2);
	printf("     ");
	for (int i = 0; i < corazones; i++) {
		gotoxy(70 + i, 2);
		printf("%c", 3);
	}
}

// Clase Auto
class Auto {
	int x, y;
	int direccion;
	
public:
	Auto(int _x, int _y, int _direccion);
	void pintar();
	void borrar();
	void mover();
	void reiniciarPosicion();
};

Auto::Auto(int _x, int _y, int _direccion) : x(_x), y(_y), direccion(_direccion) {}

void Auto::pintar() {
	irAxy(x, y);
	printf("%c%c%c%c%c", 219, 219, 219, 219, 219); // Cuadrado grande
}

void Auto::borrar() {
	irAxy(x, y);
	printf("                                                                                    "); // Espacios para borrar el cuadrado grande
}

void Auto::mover() {
	borrar();
	
	// Mover hacia la izquierda
	if (direccion == 1 && x > 1) {
		x--;
	}
	// Mover hacia la derecha
	else if (direccion == 2 && x < 80) {
		x++;
	}
	
	pintar();
}

void Auto::reiniciarPosicion() {
	// Reiniciar la posición cuando alcanza el borde de la pantalla
	if (direccion == 1 && x <= 1) {
		x = 80;
	} else if (direccion == 2 && x >= 80) {
		x = 1;
	}
}

int main() {
	OcultarCursor();
	// Establece las coordenadas iniciales para la rana
	Rana rana(55, 27);
	pintar_limites();
	rana.pintar_corazones();
	
	// Establece las coordenadas iniciales y direcciones para los autos
	Auto autoIzquierda(2, 10, 1);  // Dirección: Izquierda
	Auto autoDerecha(80, 18, 2);    // Dirección: Derecha
	
	// Ajusta la velocidad del movimiento
	int velocidadDesplazamiento = 3; // Puedes cambiar este valor según tu preferencia
	
	bool game_over = false;
	while (!game_over) {
		if (_kbhit()) {
			char tecla = _getch();
			
			// Borra la rana en la posición anterior
			rana.borrar();
			
			// Actualiza las coordenadas según la tecla presionada
			switch (tecla) {
			case DERECHA:
				rana.mover(DERECHA);
				break;
			case IZQUIERDA:
				rana.mover(IZQUIERDA);
				break;
			case ARRIBA:
				rana.mover(ARRIBA);
				break;
			case ABAJO:
				rana.mover(ABAJO);
				break;
			}
		}
		
		// Mueve los autos
		autoIzquierda.mover();
		autoDerecha.mover();
		
		// Reinicia la posición de los autos cuando alcanzan el borde de la pantalla
		autoIzquierda.reiniciarPosicion();
		autoDerecha.reiniciarPosicion();
		
		// Dibuja la rana en las nuevas coordenadas
		rana.dibujar();
		
		// Añade un pequeño retardo para que el usuario pueda ver el resultado y interactuar
		Sleep(30);
	}
	
	return 0;
}
