#include <stdio.h>
#include <windows.h>
#include <conio.h>
using namespace std;

// Funci�n para posicionar el cursor en la consola
void irAxy(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

// Funci�n para establecer el color del texto en la consola
void setColorTexto(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// Funci�n para dibujar una rana en la consola
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

int main() {
	// Establece las coordenadas iniciales para la rana
	int x = 10, y = 5;
	
	// Ajusta la velocidad del movimiento lateral
	int velocidadDesplazamiento = 3; // Puedes cambiar este valor seg�n tu preferencia
	
	bool game_over = false;
	while (!game_over) {
		if (_kbhit()) {
			char tecla = _getch();
			
			// Borra la rana en la posici�n anterior
			irAxy(x, y);
			printf("       ");  // Cuerpo superior de la rana
			irAxy(x, y + 1);
			printf("       ");  // Ojos de la rana
			irAxy(x, y + 2);
			printf("         ");  // Cuerpo inferior de la rana
			
			// Actualiza las coordenadas seg�n la tecla presionada
			if (tecla == 'd') x+= velocidadDesplazamiento;
			if (tecla == 'a') x-= velocidadDesplazamiento;
			if (tecla == 'w') y-= velocidadDesplazamiento;
			if (tecla == 's') y+= velocidadDesplazamiento;
		}
		
		// Dibuja la rana en las nuevas coordenadas
		dibujarRana(x, y);
		
		// A�ade un peque�o retardo para que el usuario pueda ver el resultado y interactuar
		Sleep(30);
	}
	
	return 0;
}
