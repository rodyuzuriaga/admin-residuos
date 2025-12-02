#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include "FuncionesAuxiliares.h"

using namespace std;

bool dniCorrecto(const string& dni) {
    ifstream archivo("registro.csv");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string columna;
        for (int i = 0; i < 4; i++) {
            getline(ss, columna, ';'); // Ignorar las primeras 4 columnas
        }
        getline(ss, columna, ';'); // Leer la columna del DNI

        if (columna == dni) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

bool palabraClaveCorrecta(const string& palabraClave) {
    ifstream archivo("registro.csv");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string columna;
        for (int i = 0; i < 10; i++) {
            getline(ss, columna, ';'); // Ignorar las primeras 10 columnas
        }
        getline(ss, columna, ';'); // Leer la columna de la palabra clave

        if (columna == palabraClave) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void cambiarClave(const string& correo, const string& nuevaClave) {
    ifstream archivoEntrada("registro.csv");
    ofstream archivoSalida("temp.csv");

    string linea;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string columna;
        vector<string> columnas;

        while (getline(ss, columna, ';')) {
            columnas.push_back(columna); // Almacenar todas las columnas en un vector
        }

        if (columnas[6] == correo) {
            // Reemplazar la columna de clave y confirmar clave con la nueva clave
            columnas[7] = nuevaClave;
            columnas[8] = nuevaClave;
        }

        // Escribir todas las columnas en el archivo de salida
        for (const string& col : columnas) {
            archivoSalida << col << ";";
        }

        archivoSalida << endl;
    }

    archivoEntrada.close();
    archivoSalida.close();

    remove("registro.csv");          // Eliminar el archivo original
    rename("temp.csv", "registro.csv"); // Renombrar el archivo de salida como el archivo original
}

void limpiarPantalla() {
    system("cls");
}

void cambioClave() {
    string correo;
    string dni;
    string palabraClave;

    cout << "=== CAMBIO DE CLAVE ===" << endl;

    do {
        cout << "Correo: ";
        cin >> correo;

        if (!correoExiste(correo)) {
            cout << "El correo ingresado no existe en la base de datos. Intentelo de nuevo." << endl;
            cout << endl;
        }
    } while (!correoExiste(correo));

    do {
        cout << "DNI: ";
        cin >> dni;

        if (!dniCorrecto(dni)) {
            cout << "El DNI ingresado no coincide con los datos registrados. Intentelo de nuevo." << endl;
            cout << endl;
        }
    } while (!dniCorrecto(dni));

    do {
        cout << "Palabra Clave: ";
        cin >> palabraClave;

        if (!palabraClaveCorrecta(palabraClave)) {
            cout << "La palabra clave ingresada no coincide con los datos registrados. Intentelo de nuevo." << endl;
            cout << endl;
        }
    } while (!palabraClaveCorrecta(palabraClave));

    limpiarPantalla();
    cout << "Datos correctamente verificados." << endl;
    cout << "Cambiando clave..." << endl;
    cout << endl;

    string nuevaClave;
    string confirmarClave;
    bool clavesCoinciden = false;

    do {
        cout << "Nueva Clave: ";
        cin >> nuevaClave;

        cout << "Confirmar Clave: ";
        cin >> confirmarClave;

        if (nuevaClave == confirmarClave) {
            clavesCoinciden = true;
        } else {
            cout << "La clave y su confirmacion no coinciden. Intentelo de nuevo." << endl;
            cout << endl;
        }
    } while (!clavesCoinciden);

    if (clavesCoinciden) {
        cambiarClave(correo, nuevaClave);
        cout << "La clave ha sido cambiada exitosamente." << endl;
    } else {
        cout << "La clave y su confirmacion no coinciden. No se ha realizado ningun cambio." << endl;
    }

    // Regresar al menu de inicio de sesion
    cout << "Presione cualquier tecla para continuar...";
    getch();
}

