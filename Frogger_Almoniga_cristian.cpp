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

void OcultarCursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon,&cci);	
	
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



int main() {
	
	OcultarCursor();
	// Establece las coordenadas iniciales para la rana
	int x = 55,y = 27;
	
	// Ajusta la velocidad del movimiento
	int velocidadDesplazamiento = 5; // Puedes cambiar este valor según tu preferencia
	
	bool game_over = false;
	while (!game_over) {
		if (_kbhit()) {
			char tecla = _getch();
			
			// Borra la rana en la posición anterior
			irAxy(x, y);
			printf("       ");  // Cuerpo superior de la rana
			irAxy(x, y + 1);
			printf("       ");  // Ojos de la rana
			irAxy(x, y + 2);
			printf("         ");  // Cuerpo inferior de la rana
			
			// Actualiza las coordenadas según la tecla presionada
			if (tecla == DERECHA) x += velocidadDesplazamiento;
			if (tecla == IZQUIERDA) x -= velocidadDesplazamiento;
			if (tecla == ARRIBA) y -= velocidadDesplazamiento;
			if (tecla == ABAJO) y += velocidadDesplazamiento;
		}
		
		// Dibuja la rana en las nuevas coordenadas
		dibujarRana(x, y);
		
		// Añade un pequeño retardo para que el usuario pueda ver el resultado y interactuar
		Sleep(30);
	}
	
	return 0;
}
