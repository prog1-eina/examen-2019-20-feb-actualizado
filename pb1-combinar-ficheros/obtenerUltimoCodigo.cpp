#include <iostream>
#include <fstream>
#include <string>
#include "constantes.hpp"
using namespace std;

/*
 * Especificación en el enunciado
 */
bool obtenerUltimoCodigo(const string nombreFicheroTerremotos, string& codEvento) {
    ifstream f(nombreFicheroTerremotos);
    if (f.is_open()) {
        string cabecera;
        getline(f, cabecera);    

        string codEventoLeido;
        while (getline(f, codEventoLeido, DELIMITADOR)) {
        // Mientras se leen los datos del flujo y la última lectura es correcta
            // Se procesa el último dato leído: 
            codEvento = codEventoLeido;
            string restoLinea;
            getline(f, restoLinea);
        }
        f.close();
        return true;
    } else {
        cerr << "No ha podido abrirse el fichero \"" << nombreFicheroTerremotos
             << "\"." << endl;
        return false;
    }
}
