#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include "FuncionesAuxiliares.h"

using namespace std;

bool correoExiste(const string& correo) {
    ifstream archivo("registro.csv");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string columna;
        for (int i = 0; i < 6; i++) {
            getline(ss, columna, ';'); // Ignorar las primeras 6 columnas
        }
        getline(ss, columna, ';'); // Leer la columna del correo electronico

        if (columna == correo) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool validarClave(const string& correo, const string& clave) {
    ifstream archivo("registro.csv");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string columna;
        for (int i = 0; i < 6; i++) {
            getline(ss, columna, ';'); // Ignorar las primeras 6 columnas
        }
        getline(ss, columna, ';'); // Leer la columna del correo electronico

        if (columna == correo) {
            getline(ss, columna, ';'); // Leer la columna de la clave

            archivo.close();
            return (columna == clave);
        }
    }

    archivo.close();
    return false;
}

bool iniciarSesion() {
    string correo;
    string clave;
    int intentos = 4;

    cout << "=== INICIAR SESION ===" << endl;

    do {
        cout << "Correo: ";
        cin >> correo;

        if (!correoExiste(correo)) {
            cout << "El correo ingresado no existe en la base de datos. Intentelo de nuevo." << endl;
            cout << endl;
        }
    } while (!correoExiste(correo));

    cout << "Clave: ";
    clave = "";

    // Leer la clave con asteriscos
    char ch;
    while ((ch = _getch()) != 13) { // 13 es el codigo ASCII de la tecla Enter
        if (ch == 8) { // 8 es el codigo ASCII de la tecla Backspace
            if (clave.length() > 0) {
                cout << "\b \b";
                clave.pop_back();
            }
        } else {
            cout << "*";
            clave.push_back(ch);
        }
    }

    cout << endl << endl;

    while (!validarClave(correo, clave) && intentos > 1) {
        cout << "La clave no coincide. Intente de nuevo." << endl;
        cout << "Le quedan " << intentos - 1 << " intentos." << endl;
        cout << endl;

        cout << "Clave: ";
        clave = "";

        // Leer la clave con asteriscos
        while ((ch = _getch()) != 13) {
            if (ch == 8) {
                if (clave.length() > 0) {
                    cout << "\b \b";
                    clave.pop_back();
                }
            } else {
                cout << "*";
                clave.push_back(ch);
            }
        }

        cout << endl << endl;

        intentos--;
    }

    if (validarClave(correo, clave)) {
        cout << "Inicio de sesion exitoso." << endl;
        return true;
    } else {
        cout << "La clave no coincide. Se han agotado los intentos. Cerrando el programa." << endl;
        return false;
    }
}
