#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <ctime>

using namespace std;

class ObjetoBase {
public:
	int x;
	int y;
	char imagen;
	int color;
	
public:
	ObjetoBase(int _x, int _y, char _imagen, int _color)
		: x(_x), y(_y), imagen(_imagen), color(_color) {}
	
	virtual void dibujar() {
		textcolor(color);
		putchxy(x, y, imagen);
	}
	
	virtual void borrar() {
		textcolor(color);
		putchxy(x, y, ' ');
	}
};

class Rana : public ObjetoBase {
public:
	Rana(int _x, int _y) : ObjetoBase(_x, _y, '#', 10) {}
	
	void mover(int dx, int dy) {
		borrar();
		x += dx;
		y += dy;
		dibujar();
	}
};

class Obstaculo : public ObjetoBase {
private:
	static const int ancho = 5;
	static const int alto = 5;
	char Matriz[ancho][alto];
	int colorMatriz[ancho][alto];
	
public:
	Obstaculo(int _x, int _y) : ObjetoBase(_x, _y, '#', 10) { // Cambié el color a verde (10)
		// Inicializar la matriz de caracteres y colores
		for (int i = 0; i < ancho; i++) {
			for (int j = 0; j < alto; j++) {
				Matriz[i][j] = '#';
				colorMatriz[i][j] = 12; // Cambié el color a verde (10)
			}
		}
	}
	
	virtual void dibujar() override {
		for (int i = 0; i < ancho; i++) {
			for (int j = 0; j < alto; j++) {
				textcolor(colorMatriz[i][j]);
				putchxy(x + i, y + j, Matriz[i][j]);
			}
		}
	}
	
	void mover() {
		borrarAnterior(); // Borra el obstáculo anterior
		x--; // Mueve el obstáculo
		dibujar(); // Dibuja el obstáculo en su nueva posición
	}
	
private:
		void borrarAnterior() {
			for (int i = 0; i < ancho; i++) {
				for (int j = 0; j < alto; j++) {
					textcolor(colorMatriz[i][j]);
					putchxy(x + i, y + j, ' '); // Borra el caracter anterior
				}
			}
		}
};

class Juego {
private:
	Rana rana;
	Obstaculo obstaculos[2];
	int puntaje;
	
public:
	Juego() : rana(10, 10), obstaculos{{15, 5}, {10, 15}}, puntaje(0) {}
	
	void iniciarJuego() {
		clrscr();
		mostrarTeclas();
		
		while (true) {
			if (kbhit()) {
				int tecla = getch();
				procesarTecla(tecla);
			}
			
			rana.dibujar();
			moverObstaculos();
			actualizarPuntaje();
			Sleep(100);
		}
	}
	
private:
		void mostrarTeclas() {
			textcolor(14);
			gotoxy(2, 2);
			cout << "Teclas: W - Arriba, A - Izquierda, S - Abajo, D - Derecha";
		}
		
		void procesarTecla(int tecla) {
			switch (tecla) {
			case 'w':
				rana.mover(0, -1);
				break;
			case 'a':
				rana.mover(-1, 0);
				break;
			case 's':
				rana.mover(0, 1);
				break;
			case 'd':
				rana.mover(1, 0);
				break;
			}
		}
		
		void moverObstaculos() {
			for (int i = 0; i < 2; i++) {
				obstaculos[i].mover();
				if (obstaculos[i].x == 0) {
					obstaculos[i].x = 79;
					puntaje++;
				}
			}
		}
		
		void actualizarPuntaje() {
			textcolor(15);
			gotoxy(2, 1);
			cout << "Puntaje: " << puntaje;
		}
};

int main() {
	srand(time(NULL));
	_setcursortype(_NOCURSOR);
	Juego juego;
	juego.iniciarJuego();
	return 0;
}
