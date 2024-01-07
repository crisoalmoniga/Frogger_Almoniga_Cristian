#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}
	
	void setTextColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}
	
	void drawGreenBox(int x, int y, int width, int height) {
		gotoxy(x, y);
		
		// Establece el color de fondo a verde y el color del texto a negro
		setTextColor(FOREGROUND_GREEN);
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				printf("%c", 219);  // Imprime el bloque de color en ASCII
			}
			printf("\n");  // Salto de línea al final de cada fila
			gotoxy(x, y + i + 1);  // Mueve el cursor a la siguiente fila
		}
		
		// Restaura el color original de la consola
		setTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	}
	
	int main() {
		// Establece el tamaño y la posición del cuadro verde
		int x = 10;
		int y = 5;
		int width = 4;
		int height = 2;
		
		// Dibuja el cuadro verde en las coordenadas especificadas
		drawGreenBox(x, y, width, height);
		
		return 0;
	}
