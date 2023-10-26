#include <iostream>
#include <ctime>
#include <conio2.h>
#include <windows.h>

using namespace std;


class Ranita {
public:
	int x, y; // Posición de la ranita en la pantalla
	
	Ranita(int startX, int startY) : x(startX), y(startY) {}
	
	void saltarArriba() {
		// Implementa el salto hacia arriba
	}
	
	void saltarDerecha() {
		// Implementa el salto hacia la derecha
	}
	
	void saltarIzquierda() {
		// Implementa el salto hacia la izquierda
	}
};

class Hoja {
public:
	int x, y; // Posición de la hoja en la pantalla
	
	Hoja(int startX, int startY) : x(startX), y(startY) {}
	
	void moverDerecha() {
		// Implementa el movimiento de la hoja hacia la derecha
	}
};

class Contador {
public:
	time_t startTime;
	int duration; // Duración del contador en segundos
	
	Contador(int seconds) : duration(seconds) {
		startTime = time(nullptr);
	}
	
	bool tiempoAgotado() {
		time_t currentTime = time(nullptr);
		return (int)difftime(currentTime, startTime) >= duration;
	}
};



int main(int argc, char *argv[]) {
	
	return 0;
}

