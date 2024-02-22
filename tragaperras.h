#include <iostream>
using namespace std;

class tragaperras{

    public:
        tragaperras();
        void validarDinero(float& dinero, bool&apuestaAceptada);
        void elegirApuesta(int tipoApuesta, float dinero, int& multiploApuesta, float& restaApuesta, char& tecla, bool& apuestaAceptada);
        void girar(int (&simboloGanador)[6],int (&simboloEstado)[3], string (&simbolo)[3], const string *simboloEmojis);
        void elegirRecompensa(int (&simboloGanador)[6], float& dinero, int multiploApuesta, float restaApuesta);
        void jugar();

    private:
        string simboloEmojis [6] = {"🐶","🦊","🐧","🐷","🐢","🐱"};
        float dinero = 0, restaApuesta = 0;
        int tipoApuesta, multiploApuesta = 0;
        bool apuestaAceptada = false;
        char tecla;
};