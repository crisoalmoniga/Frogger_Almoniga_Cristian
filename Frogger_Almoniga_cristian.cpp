#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

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
		irAxy(i, 3);
		printf("%c", 205);
		irAxy(i, 30);
		printf("%c", 205);
	}
	
	for (int i = 4; i < 30; i++) {
		irAxy(1, i);
		printf("%c", 186);
		irAxy(120, i);
		printf("%c", 186);
	}
	
	irAxy(1, 3);
	printf("%c", 201);
	irAxy(1, 30);
	printf("%c", 200);
	irAxy(120, 1);
	printf("%c", 187);
	irAxy(120, 30);
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
	int vida;
	
public:
	Rana(int _x, int _y, int _vida);
	int getX() { return x; }
	int getY() { return y; }
	int getVida() { return vida; }
	
	void dibujar();
	void borrar();
	void mover(int direccion);
	void golpeada();
};

Rana::Rana(int _x, int _y, int _vida) : x(_x), y(_y), vida(_vida) {}

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
		if (x + 1 < 118)
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
	
	dibujar();
}

void Rana::golpeada() {
	vida--;
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
	void colision(class Rana &r);
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
	else if (direccion == 2 && x + 5 < 118) {
		x++;
	}
	
	pintar();
}

void Auto::reiniciarPosicion() {
	// Reiniciar la posición cuando alcanza el borde de la pantalla
	if (direccion == 1 && x <= 1) {
		x = 118;
	} else if (direccion == 2 && x + 5 >= 118) {
		x = 1;
	}
}

void Auto::colision(class Rana &r) {
	if (x + 5 > r.getY() && x < r.getY() + 2 && y == r.getY()) {
		r.golpeada();
		r.borrar();
		irAxy(2, 2);
		printf("vidas %d", r.getVida());
	}
}

// Clase Juego
class Juego {
	Rana rana;
	Auto autoIzquierda;
	Auto autoDerecha;
	bool game_over;
	
public:
	Juego();
	void iniciarJuego();
	void manejarTecla(char tecla);
};

Juego::Juego() : rana(55, 27, 10), autoIzquierda(2, 10, 1), autoDerecha(80, 18, 2), game_over(false) {}

void Juego::iniciarJuego() {
	OcultarCursor();
	pintar_limites();
	
	while (!game_over) {
		if (_kbhit()) {
			char tecla = _getch();
			manejarTecla(tecla);
		}
		
		autoIzquierda.mover();
		autoDerecha.mover();
		
		autoIzquierda.colision(rana);
		autoDerecha.colision(rana);
		
		autoIzquierda.reiniciarPosicion();
		autoDerecha.reiniciarPosicion();
		
		rana.dibujar();
		
		Sleep(30);
	}
}

void Juego::manejarTecla(char tecla) {
	rana.borrar();
	
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

int main() {
	Juego juego;
	juego.iniciarJuego();
	
	return 0;
}
