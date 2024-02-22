#include <iostream>
#include <conio.h>
#include <time.h>
#include <thread>
#include <chrono>
#include "tragaperras.h"
using namespace std;

tragaperras::tragaperras(){

    srand(time(0)); // Inicializar semilla random
}

void tragaperras::jugar(){

    while(tecla != 'x'){

        int simboloGanador[6] = {0}; // Un total de 6 simbolos, mas info. en elegirRecompensa
        int simboloEstado[3] = {0}; // Centinela 
        string simbolo[3] = {};

        validarDinero(dinero, apuestaAceptada);

        while(!apuestaAceptada || tecla == 'a'){

            elegirApuesta(tipoApuesta, dinero, multiploApuesta, restaApuesta, tecla, apuestaAceptada);
        }

        if(apuestaAceptada){

            girar(simboloGanador, simboloEstado, simbolo, simboloEmojis);

            elegirRecompensa(simboloGanador, dinero, multiploApuesta, restaApuesta);

            //Imprimir los simbolos elegidos para evitar errores
            for(int p = 0; p < 3; p++){

                cout << simbolo[p];
            }

            cout << "\nCreditos: " << dinero << "$" << endl;
        }

        while(true){ 

            cout << "Presiona enter para jugar otra vez, A para cambiar de tipo de apuesta o X para salir\n" << endl;
            tecla = getch();

            if(static_cast<int>(tecla) == 13 || tecla == 'x' || tecla == 'a'){ // 13 es enter
                break;
            }
            else{

                cout << "La tecla " << tecla << " no es valida, ingrese una tecla valida" << endl;
            }
        }
    }

    cout << "\nTe vas con: " << dinero << "$" << endl;
}


void tragaperras::validarDinero(float& dinero, bool& apuestaAceptada){

    if(dinero == 0){

        apuestaAceptada = false;
        cout << "Ingrese la cantidad de dinero a apostar: $";
        cin >> dinero;

        while(cin.fail() || cin.peek() != '\n' || dinero <= 0) {

            cout << "Ingrese una cantidad de dinero valida\n" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cout << "$";
            cin >> dinero;
        }
    }
}

void tragaperras::elegirApuesta(int tipoApuesta, float dinero, int& multiploApuesta, float& restaApuesta, char& tecla, bool& apuestaAceptada){

    apuestaAceptada = false;
    cout << "\nIngrese el tipo de apuesta" << endl;
    cout << "\n1. Normal (0.40 dolares)\n2. Doble (0.80 dolares)\n3. Triple(1.20 dolares)\n4. Apuesta maxima (" << dinero << " dolares)\n";

    cin >> tipoApuesta;

    while(cin.fail() || cin.peek() != '\n' || tipoApuesta <= 0 || tipoApuesta > 4) {

        cout << "Ingrese una opcion valida" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> tipoApuesta;
    }

    switch (tipoApuesta)
    {
    case 1:
            multiploApuesta = 1;
            restaApuesta = 0.40;
            break;
    case 2:
            multiploApuesta = 2;
            restaApuesta = 0.80;
            break;
    case 3:
            multiploApuesta = 3;
            restaApuesta = 1.20;
            break;
    case 4:
            multiploApuesta = dinero;
            restaApuesta = dinero;
            break;
    default:
        break;
    }

    apuestaAceptada = true;
    tecla = 0;
}

void tragaperras::girar(int (&simboloGanador)[6],int (&simboloEstado)[3], string (&simbolo)[3], const string *simboloEmojis){

    while(simboloEstado[2] != 1){
        for(int i = 0; i < 3; i++){

            int simboloIndex = rand() % 100;

            for(int x = 0; x < 40; x++){
                for(int j = 0; j < 3; j++){
                    if(simboloEstado[j] != 1){

                        int simboloIndex2 = rand() % 6;
                        simbolo[j] = simboloEmojis[simboloIndex2];
                    }
                    cout << simbolo[j];
                }
                this_thread::sleep_for (chrono::milliseconds(50));
                cout << "\r";
            }

            if(simboloIndex <= 60){

                simbolo[i] = simboloEmojis[5]; //🐱 60% de probabilidades
                simboloGanador[5] = simboloGanador[5] + 1;
            }
            else if(simboloIndex > 60 && simboloIndex <= 73){

                simbolo[i] = simboloEmojis[4]; //🐢 13% de probabilidades
                simboloGanador[4] = simboloGanador[4] + 1;
            }
            else if(simboloIndex > 73 && simboloIndex <= 85){

                simbolo[i] = simboloEmojis[3]; //🐷 12% de probabilidades
                simboloGanador[3] = simboloGanador[3] + 1;
            }
            else if(simboloIndex > 85 && simboloIndex <= 93){

                simbolo[i] = simboloEmojis[2]; //🐧 8% de probabilidades
                simboloGanador[2] = simboloGanador[2] + 1;
            }
            else if(simboloIndex > 93 && simboloIndex <= 99){

                simbolo[i] = simboloEmojis[1]; //🦊 6% de probabilidades
                simboloGanador[1] = simboloGanador[1] + 1;
            }
            else{

                simbolo[i] = simboloEmojis[0]; //🐶 1% de probabilidades
                simboloGanador[0] = simboloGanador[0] + 1;
            }

            simboloEstado[i] = 1;
        }
    }
}

void tragaperras::elegirRecompensa(int (&simboloGanador)[6], float& dinero, int multiploApuesta, float restaApuesta){

    /* RECOMPENSAS
        🐶🐶🐶 100$
        🦊🦊🦊 80$
        🐧🐧🐧 50$
        🐷🐷🐷 20$
        🐢🐢🐢 10$
        🐧🐧 5$
        🐢🐢 5$
        🐶 2$
        🦊 1$
    */
    /* ID'S
        🐶 = 0
        🦊 = 1
        🐧 = 2
        🐷 = 3
        🐢 = 4
        🐱 = 5
    */
    if(simboloGanador[4] == 3){

        dinero = dinero + (10 * multiploApuesta); //🐢🐢🐢
    }
    else if(simboloGanador[3] == 3){

        dinero = dinero + (20 * multiploApuesta); //🐷🐷🐷
    }
    else if(simboloGanador[2] == 3){

        dinero = dinero + (50 * multiploApuesta); //🐧🐧🐧
    }
    else if(simboloGanador[1] == 3){

        dinero = dinero + (80 * multiploApuesta); //🦊🦊🦊
    }
    else if(simboloGanador[0] == 3){

        dinero = dinero + (100 * multiploApuesta); //🐶🐶🐶
    }
    else if((simboloGanador[1] == 2 && simboloGanador[0] == 1) || simboloGanador[0] == 2){

        dinero = dinero + (4 * multiploApuesta); //🦊🦊🐶 OR 🐶🐶*
    }
    else if((simboloGanador[0] == 2 && simboloGanador[1] == 1) || simboloGanador[2] == 2 || simboloGanador[4] == 2 ){

        dinero = dinero + (5 * multiploApuesta); //🐶🐶🦊 OR 🐧🐧* OR 🐢🐢*
    }
    else if((simboloGanador[2] == 2 || simboloGanador[4] == 2) && simboloGanador[1] == 1){

        dinero = dinero + (6 * multiploApuesta); //🐢🐢🦊 OR 🦊🐧🐧
    }
    else if((simboloGanador[2] == 2 || simboloGanador[4] == 2) && simboloGanador[0] == 1){

        dinero = dinero + (7 * multiploApuesta); //🐢🐢🐶 OR 🐶🐧🐧
    }
    else if(simboloGanador[1] == 2 || simboloGanador[0] == 1){

        dinero = dinero + (2 * multiploApuesta); //🦊🦊* OR 🐶**
    }
    else if(simboloGanador[1] == 1){

        dinero = dinero + (1 * multiploApuesta); //🦊**
    }
    else{

        dinero = dinero - restaApuesta;

        if(dinero < 0){
            dinero = 0;
        }
    }
}
