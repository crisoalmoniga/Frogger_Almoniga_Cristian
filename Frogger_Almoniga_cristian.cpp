#include <stdio.h>
#include <windows.h>
#include <conio.h>

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

// Función para establecer el color del texto en la consola
void setColorTexto(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// Función para dibujar una rana en la consola
void dibujarRana(int x, int y) {
	// Establece el color de fondo a verde y el color del texto a negro
	setColorTexto(FOREGROUND_GREEN);
	
	irAxy(x, y);
	printf("   \\_/");  // Cuerpo superior de la rana
	irAxy(x, y + 1);
	printf("  (o o)");  // Ojos de la rana
	irAxy(x, y + 2);
	printf(" /  V  \\");  // Cuerpo inferior de la rana
	
	// Restaura el color original de la consola
	setColorTexto(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

class AUTO {
	int x, y;
	int direccion;  // Variable para almacenar la dirección del movimiento
	
public:
	AUTO(int _x, int _y, int _direccion);
	void pintar();
	void borrar();
	void mover();
	void reiniciarPosicion();
};

AUTO::AUTO(int _x, int _y, int _direccion) : x(_x), y(_y), direccion(_direccion) {}void AUTO::pintar() {
	irAxy(x, y);
	printf("%c%c%c%c%c", 219, 219, 219, 219, 219); // Cuadrado grande

}

void AUTO::borrar() {
	irAxy(x, y);
	printf("                                                                                    "); // Espacios para borrar el cuadrado grande
}
void AUTO::mover() {
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

void AUTO::reiniciarPosicion() {
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
	int xRana = 55, yRana = 27;
	
	// Establece las coordenadas iniciales y direcciones para los autos
	AUTO autoIzquierda(2, 10, 1);  // Dirección: Izquierda
	AUTO autoDerecha(80, 18, 2);    // Dirección: Derecha
	
	// Ajusta la velocidad del movimiento
	int velocidadDesplazamiento = 5; // Puedes cambiar este valor según tu preferencia
	
	bool game_over = false;
	while (!game_over) {
		if (_kbhit()) {
			char tecla = _getch();
			
			// Borra la rana en la posición anterior
			irAxy(xRana, yRana);
			printf("       ");  // Cuerpo superior de la rana
			irAxy(xRana, yRana + 1);
			printf("       ");  // Ojos de la rana
			irAxy(xRana, yRana + 2);
			printf("         ");  // Cuerpo inferior de la rana
			
			// Actualiza las coordenadas según la tecla presionada
			if (tecla == DERECHA) xRana += velocidadDesplazamiento;
			if (tecla == IZQUIERDA) xRana -= velocidadDesplazamiento;
			if (tecla == ARRIBA) yRana -= velocidadDesplazamiento;
			if (tecla == ABAJO) yRana += velocidadDesplazamiento;
		}
		
		// Mueve los autos
		autoIzquierda.mover();
		autoDerecha.mover();
		
		// Reinicia la posición de los autos cuando alcanzan el borde de la pantalla
		autoIzquierda.reiniciarPosicion();
		autoDerecha.reiniciarPosicion();
		
		// Dibuja la rana en las nuevas coordenadas
		dibujarRana(xRana, yRana);
		
		// Añade un pequeño retardo para que el usuario pueda ver el resultado y interactuar
		Sleep(30);
	}
	
	return 0;
}
