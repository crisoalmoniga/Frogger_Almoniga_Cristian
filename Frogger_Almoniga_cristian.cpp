#include <iostream>
#include <windows.h>

using namespace std;

// Definimos una funci�n para establecer la posici�n del cursor en la consola
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Plataforma {
public:
	int x, y; // Posici�n de la plataforma en la pantalla
	int width, height; // Tama�o de la plataforma
	
	Plataforma(int startX, int startY, int w, int h) : x(startX), y(startY), width(w), height(h) {}
	
	void dibujar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << "#"; // Car�cter de "encendido"
			}
		}
	}
	
	void apagar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << " "; // Car�cter de "apagado"
			}
		}
	}
	
	void mover(int direction) {
		x += direction;
	}
};

class PlataformaFija {
public:
	int x, y; // Posici�n de la plataforma en la pantalla
	int width, height; // Tama�o de la plataforma
	
	PlataformaFija(int startX, int w, int h) : x(startX), width(w), height(h) {
		// Calcula la posici�n vertical en la parte inferior de la pantalla
		y = 27 - h;
	}
	
	void dibujar() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gotoxy(x + j, y + i);
				cout << "#"; // Car�cter de "encendido"
			}
		}
	}
};


int main() {
	// Crea dos plataformas m�vil
	Plataforma plataforma1(10, 10, 10, 5);
	Plataforma plataforma2(50, 15, 10, 5);
	
	int plataforma1Direction = 1; // Direcci�n de movimiento de plataforma1
	int plataforma2Direction = -1; // Direcci�n de movimiento de plataforma2

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
		
		// Espera un breve per�odo de tiempo para una animaci�n suave
		Sleep(100);
		
		// Revisa los bordes y cambia la direcci�n si es necesario
		if (plataforma1.x <= 0 || plataforma1.x + plataforma1.width >= 80) {
			plataforma1Direction *= -1;
		}
		
		if (plataforma2.x <= 0 || plataforma2.x + plataforma2.width >= 80) {
			plataforma2Direction *= -1;
		}
	}
	
	return 0;
}
