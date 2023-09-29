#include <iostream>
#include <fstream>
#include <string>
#include "constantes.hpp"
using namespace std;

/*
 * Pre:  Si el fichero «nombreFicheroTerremotos» existe, es un fichero de
 *       texto cuyo contenido cumple con la regla sintáctica
 *       <fichero-terremotos> y el resto de restricciones establecidas en el
 *       enunciado.
 * Post: Si el fichero «nombreFicheroTerremotos» existe, ha asignado a
 *       «codEvento» el valor del código del terremoto correspondiente a la
 *       última línea del fichero y ha devuelto «true». En caso contrario, ha
 *       devuelto «false».
 */
bool obtenerUltimoCodigo(const string nombreFicheroTerremotos, 
                         string& codEvento) {
    ifstream f(nombreFicheroTerremotos);
    if (f.is_open()) {
        string cabecera;
        getline(f, cabecera);    

        string codEventoLeido;
        while (getline(f, codEventoLeido, DELIMITADOR)) {
            string restoLinea;
            getline(f, restoLinea);
        }
        f.close();
        codEvento = codEventoLeido;
        return true;
    } else {
        cerr << "No ha podido abrirse el fichero \"" 
             << nombreFicheroTerremotos << "\"." << endl;
        return false;
    }
}
