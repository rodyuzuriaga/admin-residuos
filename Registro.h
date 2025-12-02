#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Funcion para verificar si una cadena contiene solo letras
bool contieneSoloLetras(const string& str)
{
    for (char c : str)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

// Funcion para verificar si una cadena contiene solo numeros
bool contieneSoloNumeros(const string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Funcion para registrar los datos en el registro CSV
void registrarDatos(const string& registro)
{
    ofstream file(registro, ios::app);
    
    if (!file)
    {
        cout << "Error al abrir el registro." << endl;
        return;
    }
    
    string primerNombre;
    string segundoNombre;
    string apellidoPaterno;
    string apellidoMaterno;
    string dni;
    string telefono;
    string correo;
    string clave;
    string confirmarClave;
    string palabraClave;
    
    // Solicitar y validar el primer nombre
    cout << "Ingrese su primer nombre: ";
    getline(cin, primerNombre);
    
    while (!contieneSoloLetras(primerNombre))
    {
        cout << "Error. El primer nombre solo debe contener letras. Ingrese nuevamente: ";
        getline(cin, primerNombre);
    }
    
    // Solicitar y validar el segundo nombre
    cout << "Ingrese su segundo nombre: ";
    getline(cin, segundoNombre);
    
    while (!contieneSoloLetras(segundoNombre))
    {
        cout << "Error. El segundo nombre solo debe contener letras. Ingrese nuevamente: ";
        getline(cin, segundoNombre);
    }
    
    // Solicitar y validar el apellido paterno
    cout << "Ingrese su apellido paterno: ";
    getline(cin, apellidoPaterno);
    
    while (!contieneSoloLetras(apellidoPaterno))
    {
        cout << "Error. El apellido paterno solo debe contener letras. Ingrese nuevamente: ";
        getline(cin, apellidoPaterno);
    }
    
    // Solicitar y validar el apellido materno
    cout << "Ingrese su apellido materno: ";
    getline(cin, apellidoMaterno);
    
    while (!contieneSoloLetras(apellidoMaterno))
    {
        cout << "Error. El apellido materno solo debe contener letras. Ingrese nuevamente: ";
        getline(cin, apellidoMaterno);
    }
    
    // Solicitar y validar el DNI
    cout << "Ingrese su DNI: ";
    getline(cin, dni);
    
    while (!contieneSoloNumeros(dni))
    {
        cout << "Error. El DNI solo debe contener numeros. Ingrese nuevamente: ";
        getline(cin, dni);
    }
    
    // Solicitar y validar el numero de telefono
    cout << "Ingrese su numero de telefono: +51 ";
    getline(cin, telefono);
    
    while (!contieneSoloNumeros(telefono))
    {
        cout << "Error. El numero de telefono solo debe contener numeros. Ingrese nuevamente: +51 ";
        getline(cin, telefono);
    }
    
    // Solicitar y validar el correo electronico
    cout << "Ingrese su correo electronico: ";
    getline(cin, correo);
    
    ifstream readFile(registro);
    string line;
    bool correoExistente = false;
    
    while (getline(readFile, line))
    {
        if (line.find(correo) != string::npos)
        {
            correoExistente = true;
            break;
        }
    }
    
    while (correoExistente)
    {
        cout << "Error. El correo electronico ya esta registrado. Ingrese nuevamente: ";
        getline(cin, correo);
        
        correoExistente = false;
        
        readFile.clear();
        readFile.seekg(0);
        
        while (getline(readFile, line))
        {
            if (line.find(correo) != string::npos)
            {
                correoExistente = true;
                break;
            }
        }
    }
    
    // Solicitar y validar la clave
    cout << "Ingrese su clave: ";
    getline(cin, clave);
    
    cout << "Confirme su clave: ";
    getline(cin, confirmarClave);
    
    while (clave != confirmarClave)
    {
        cout << "Error. Las claves no coinciden. Ingrese nuevamente." << endl;
        
        cout << "Ingrese su clave: ";
        getline(cin, clave);
        
        cout << "Confirme su clave: ";
        getline(cin, confirmarClave);
    }
    
    // Solicitar y guardar la palabra clave de recuperacion
    cout << "Ingrese su palabra clave de recuperacion: ";
    getline(cin, palabraClave);
    
    // Escribir los datos en el registro CSV
    file << primerNombre << ";" << segundoNombre << ";" << apellidoPaterno << ";" << apellidoMaterno
         << ";" << dni << ";" << telefono << ";" << correo << ";" << clave << ";"
         << confirmarClave << ";" << palabraClave << endl;
    
    file.close();
}
