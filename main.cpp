#include <iostream>
#include <string>
#include <windows.h>
#include "IniciarSesion.h"
#include "Registro.h"
#include "CambioClave.h"

using namespace std;

void centerText(const string& text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int textWidth = text.length();
    int leftPadding = (consoleWidth - textWidth) / 2;

    cout << string(leftPadding, ' ') << text << endl;
}

int main() {
    string title = "BIENVENIDO AL PROGRAMA GESTION DE RESIDUOS";
    string content = "Bienvenido a nuestro programa de Gestion de Residuos. Esta aplicacion te permite llevar un control eficiente de la recoleccion y gestion de residuos, fomentando practicas sostenibles y la reduccion de impacto ambiental. Con nuestras herramientas intuitivas, podras realizar la recoleccion selectiva de diferentes tipos de residuos, acceder a informacion educativa sobre reciclaje y practicas sostenibles, explorar la infraestructura necesaria para el procesamiento de residuos, monitorear y evaluar tus avances en la gestion de residuos y mucho mas. Unete a nosotros en esta mision para construir un futuro mas limpio y sustentable.";

    system("cls");
    centerText(title);
    cout << endl << content << endl;
    cout << endl;

    system("pause");
    system("cls");

    string opcion;

    do {
        cout << "MENU DE LOGIN" << endl;
        cout << "Iniciar Sesion   [1]" << endl;
        cout << "Crear Cuenta     [2]" << endl;
        cout << "Cambio Clave     [3]" << endl;
        cout << "Salir            [4]" << endl;
        cout << "Ingrese una opcion (1-4): ";
        getline(cin, opcion);

        if (opcion.length() != 1 || opcion < "1" || opcion > "4") {
        	system("cls"); // Limpia la pantalla
            cout << "Opcion invalida. Ingrese una opcion valida (1-4).\n" << endl;
            continue;
        }

        switch (opcion[0]) {
            case '1':
                system("cls"); // Limpia la pantalla
                // Iniciar sesion
                if (iniciarSesion()) {
                    // Inicio de sesion exitoso, realizar acciones necesarias
                } else {
                    // Cerrar el programa debido a intentos fallidos
                    return 0;
                }
                break;
            case '2':
            	system("cls"); // Limpia la pantalla
                // Crear cuenta
                cout << "Ha seleccionado Crear Cuenta.\n" << endl;
                // Llamar a la funcion correspondiente en Registro.h para registrar los datos
                registrarDatos("registro.csv");
                system("cls"); // Limpia la pantalla
                cout << "Cuenta creada exitosamente." << endl;
                break;
            case '3':
            	system("cls"); // Limpia la pantalla
                // Logica para cambio de clave
                cout << "Ha seleccionado Cambio Clave.\n" << endl;
			    cambioClave(); // Llamar a la funcion de cambio de clave en CambioClave.h
			    //system("cls"); // Limpia la pantalla
			    cout << "Clave actualizada correctamente." << endl;
			    break;
            case '4':
            	system("cls"); // Limpia la pantalla
                // Salir del programa
                cout << "Ha seleccionado Salir. Hasta luego\n" << endl;
                break;
        }

        cout << endl;
    } while (opcion[0] != '4');

    return 0;
}
