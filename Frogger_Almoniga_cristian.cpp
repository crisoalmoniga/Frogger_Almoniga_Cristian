#include <iostream>
#include <windows.h>

using namespace std;

// Definimos una función para establecer la posición del cursor en la consola
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Plataforma {
public:
	int x, y; // Posición de la plataforma en la pantalla
	int width, height; // Tamaño de la plataforma
	
	Plataforma(int startX, int startY, int w, int h) : x(startX), y(startY), width(w), height(h) {}
	
	void dibujar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << "#"; // Carácter de "encendido"
			}
		}
	}
	
	void apagar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << " "; // Carácter de "apagado"
			}
		}
	}
	
	void mover(int direction) {
		x += direction;
	}
};

class PlataformaFija {
public:
	int x, y; // Posición de la plataforma en la pantalla
	int width, height; // Tamaño de la plataforma
	
	PlataformaFija(int startX, int w, int h) : x(startX), width(w), height(h) {
		// Calcula la posición vertical en la parte inferior de la pantalla
		y = 27 - h;
	}
	
	void dibujar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << "#"; // Carácter de "encendido"
			}
		}
	}
};


int main() {
	// Crea dos plataformas móvil
	Plataforma plataforma1(10, 10, 10, 5);
	Plataforma plataforma2(50, 15, 10, 5);
	
	int plataforma1Direction = 1; // Dirección de movimiento de plataforma1
	int plataforma2Direction = -1; // Dirección de movimiento de plataforma2

	// Crea una plataforma fija en la parte inferior
	PlataformaFija plataformaInferior(00, 80, 4);
	
	
	// Loop principal
	while (true) {
		// Apaga las plataformas en sus posiciones anteriores
		plataforma1.apagar();
		plataforma2.apagar();
		
		// Mueve las plataformas
		plataforma1.mover(plataforma1Direction);
		plataforma2.mover(plataforma2Direction);
		
		// Dibuja las plataformas en sus nuevas posiciones
		plataforma1.dibujar();
		plataforma2.dibujar();
	
		// Dibuja la plataforma fija en la parte inferior
		plataformaInferior.dibujar();
		
		// Espera un breve período de tiempo para una animación suave
		Sleep(100);
		
		// Revisa los bordes y cambia la dirección si es necesario
		if (plataforma1.x <= 0 || plataforma1.x + plataforma1.width >= 80) {
			plataforma1Direction *= -1;
		}
		
		if (plataforma2.x <= 0 || plataforma2.x + plataforma2.width >= 80) {
			plataforma2Direction *= -1;
		}
	}
	
	return 0;
}
