#include <iostream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

vector<string> split(string line, const char delimiter);
void ingresarArticulo();
bool guardarArticuloEnArchivo(string nombre, string cantidad, string valor);
bool menuPrincipal();
void verArticulosEnInventario();

int main()
{
    while(menuPrincipal());
    cout << "Fin del programa. Gracias por utilizar nuestro servicio de inventario." << endl;
    return 0;
}

bool menuPrincipal()
{
    int opcion = 0; // Esta variable se utiliza para almacenar el numero ingresado por el usuario.
    bool valido = false;
    do
    {
        cout << "\n\n**-**-** Sistema de inventario **-**-**\n\n";
        cout << "Ingrese una opcion: \n";
        cout << "1. Ingresar articulos al inventario\n";
        cout << "2. Ver todos los articulos en el inventario\n";
        cout << "3. Realizar una venta\n";
        cout << "4. Salir\n";
        cout << "Su seleccion >> ";
        cin >> opcion;

        if (cin.good())
        {
            valido = true;
        }
        else
        {
            cin.clear();
            cin.ignore();
            system("cls");
            cout << "Entrada invalida. Por favor ingrese una opcion valida" << endl;
        }
    }while(!valido);

    switch (opcion)
    {
        case 1:
            ingresarArticulo();
            return true;
        case 2:
            verArticulosEnInventario();
            return true;
        case 3:
            cout << "Escogencia: Realizar una venta\n";
            break;
        case 4:
            break;
        default:
            cout << "No es una opcion valida. Las opciones son: 1, 2, 3 y 4.\n";
            return true;
    }
    return false;
}

//Esta funcion obtiene los tokens de una cadena segun el separador indicado y los retorna en un vector/arreglo
vector<string> split(string line, const char delimiter)
{
    stringstream ss(line);
    string tok;
    vector <string> tokens;

    while (getline(ss, tok, delimiter)) {
        tokens.push_back(tok);
    }
    return tokens;
}

void ingresarArticulo()
{
    bool valido = false;
    string datosArticulo = "";

    do {
        cout << "--- Ingresar un articulo al inventario ---\n";
        cout << "Ingrese el articulo de la siguiente forma: Nombre,unidades,valor unitario (sin espacios).\n";
        cout << "Por ejemplo: Arroz,50,1000\n";
        cin >> datosArticulo;

        if (cin.good())
        {
            valido = true;
        }
        else
        {
            cin.clear();
            cin.ignore();
            system("cls");
            cout << "Entrada invalida. Por favor ingrese los datos como se solicitan" << endl;
        }
    }while(!valido);

    vector<string> datosInventario = split(datosArticulo, ','); //El vector es un arreglo que dentro lleva multiples cadenas.


    cout << "--> Se procedera a almacenar en el inventario la siguiente informacion:\n";
    cout << "** Nombre del articulo: " << datosInventario[0] << endl;
    cout << "** Cantidad de unidades: " << datosInventario[1] << endl;
    cout << "** Valor unitario: " << datosInventario[2] << endl;

    string nombreArticulo = datosInventario[0];
    string cantidadArticulo = datosInventario[1];
    string valorArticulo = datosInventario[2];

    if (guardarArticuloEnArchivo(nombreArticulo, cantidadArticulo, valorArticulo))
        cout << "\n--> Articulo almacenado en inventario exitosamente!" << endl;
    else
        cout << "--> Error al almacenar el articulo en el inventario" << endl;
}

bool guardarArticuloEnArchivo(string nombre, string cantidad, string valor)
{
    /*La funcion unicamente agrega datos al final del archivo.
    Falta:
    - Agregar el indice de los articulos (identificador)
    - Evitar duplicados

    */
    ofstream archivoArticulos;
    archivoArticulos.open ("inventario.dat", ios::out | ios::app);
    if (archivoArticulos.fail())
    {
        return false;
    }
    else
    {
        archivoArticulos << nombre << "\t" << cantidad << "\t" << valor << endl;
        return true;
    }
}


void verArticulosEnInventario()
{
    /*Falta:
    - Manejo de excepciones: (Si el archivo no existe?)
    */
    ifstream archivoArticulos;
    archivoArticulos.open("inventario.dat");
    string linea;
    cout << "\n\n*** Articulos en inventario ***" << endl;
    cout << "\n| Nombre\t|Cantidad\t|Valor Unitario\t|" <<endl;
    while (getline(archivoArticulos, linea))
    {
        vector<string> datosInventario = split(linea, '\t');
        if(datosInventario[0].length() >= 8)
        {
            cout << datosInventario[0] << "\t   " <<datosInventario[1] << "\t\t   " << datosInventario[2] << endl;
        }
        else
        {
            cout << datosInventario[0] << "\t\t   " << datosInventario[1] << "\t\t   " << datosInventario[2] << endl;
        }
    }
    archivoArticulos.close();
}


