#include "obtenerUltimoCodigo.hpp"
#include "constantes.hpp"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Declaraciones de las constantes definidas en el enunciado */

/* Declaración y definición de la función «obtenerUltimoCodigo» */


/*
 * Pre:  Los flujos «terremotos» y «ultimos» están abiertos y asociados con ficheros
 *       de texto cuyos contenidos cumplen con la regla sintáctica
 *       <fichero-terremotos> y el resto de restricciones establecidas en el
 *       enunciado. Se está en disposición de leer desde el principio del flujo
 *       «ultimos» flujos y en disposición de escribir a partir del final del flujo
 *       «terremotos». Además, el primer terremoto del flujo «terremotos» es igual o
 *       anterior al primer evento del flujo «ultimos». Análogamente, el último
 *       terremoto de «ultimos» es igual o posterior al primer evento del flujo
 *       «terremotos».
 * Post: Tras ser ejecutada, esta función ha actualizado los datos del flujo
 *       «terremotos» con los datos de los terremotos del flujo «ultimos», añadiendo
 *       únicamente la información de los terremotos del flujo «ultimos» que no se
 *       encontraran inicialmente en «terremotos». Ha asignado al parámetro
 *       «numSismosNuevos» el número de terremotos añadidos al flujo «ultimos».
 */
void actualizar(ostream &terremotos, istream &ultimos, const string codEvento,
               unsigned &numSismosNuevos) {
    string cabecera;
    getline(ultimos, cabecera);

    numSismosNuevos = 0;
    string codEventoLeido;
    while (getline(ultimos, codEventoLeido, DELIMITADOR)) {
    // Mientras se leen los datos del flujo y la última lectura es correcta
        // Se procesa el último dato leído: 
        string restoLinea;
        getline(ultimos, restoLinea);
        if (codEventoLeido > codEvento) {
            terremotos << codEventoLeido << DELIMITADOR << restoLinea << endl;
            numSismosNuevos++;
        }
    }
}


/*
 * Pre:  Si los ficheros «nombreFicheroTerremotos» y «nombreFicheroUltimos»
 *       existen, son ficheros de texto cuyos contenidos cumplen con la regla
 *       sintáctica <fichero-terremotos> y el resto de restricciones
 *       establecidas en el enunciado. Además, el primer terremoto de
 *       «nombreFicheroUltimos» es igual o posterior al primer evento de
 *       «nombreFicheroTerremotos». Análogamente, el último terremoto de
 *       «nombreFicheroUltimos» es también igual o posterior al primer evento
 *       de «nombreFicheroTerremotos».
 * Post: Tras ser ejecutada, esta función ha actualizado los datos del fichero
 *       «nombreFicheroTerremotos» con los datos de los terremotos del fichero
 *       «nombreFicheroUltimos», añadiendo únicamente los terremotos de
 *       «nombreFicheroUltimos» que no se encontraran inicialmente en 
 *       «nombreFicheroTerremotos». Si ha podido abrir correctamente ambos
 *       ficheros, ha asignado al parámetro «numSismosNuevos» el número de
 *       terremotos añadidos al fichero «nombreFicheroTerremotos» y ha asignado
 *       a «lecturaOk» el valor «RESULTADO_OK». En caso contrario, ha escrito
 *       un mensaje de error en «cerr» y ha asignado a «lecturaOk» el valor
 *       «RESULTADO_ERROR_FICH_TERREMOTOS» si el fichero que no se ha podido
 *       abrir ha sido «nombreFicheroTerremotos» o «RESULTADO_ERROR_OTRO_FICH»
 *       si el que no se ha podido abrir ha sido «nombreFicheroUltimos».
 */
void actualizar(const string nombreFicheroTerremotos,
                const string nombreFicheroUltimos, const string codEvento,
                unsigned &numSismosNuevos, bool &lecturaOk) {
    ofstream terremotos(nombreFicheroTerremotos, ios::app);
    if (terremotos.is_open()) {
        ifstream ultimos(nombreFicheroUltimos);
        if (ultimos.is_open()) {
            actualizar(terremotos, ultimos, codEvento, numSismosNuevos);
            ultimos.close();
            lecturaOk = true;
        } else {
            cerr << "No ha podido abrirse el fichero \""
                 << nombreFicheroUltimos << "\"." << endl;
            lecturaOk = false;
        }
        terremotos.close();
    } else {
        cerr << "No ha podido abrirse el fichero \"" << nombreFicheroTerremotos
             << "\" para la concatenación de datos." << endl;
        lecturaOk = false;
    }
}


/*
 * Pre:  Si los ficheros «FICH_TERREMOTOS» y «FICH_ULTIMOS» existen, son
 *       ficheros de texto cuyos contenidos cumplen con la regla sintáctica
 *       <fichero-terremotos> y el resto de restricciones establecidas en el
 *       enunciado. Además, el primer terremoto de «FICH_ULTIMOS» es igual
 *       o posterior al primer evento de «FICH_TERREMOTOS». Análogamente, el 
 *       último terremoto de «FICH_ULTIMOS» es también igual o posterior al 
 *       primer evento de «FICH_TERREMOTOS».
 * Post: Tras ser ejecutado, este programa ha actualizado los datos del 
 *       fichero «FICH_TERREMOTOS» con los datos de los terremotos del
 *       fichero «FICH_ULTIMOS», añadiendo únicamente la información de los
 *       terremotos del fichero «FICH_ULTIMOS» que no se encontraran 
 *       inicialmente en «FICH_TERREMOTOS». Si ha podido abrir correctamente
 *       ambos ficheros, ha informado al usuario del número de terremotos
 *       añadidos al fichero «FICH_TERREMOTOS» escribiendo un mensaje en la
 *       pantalla. En caso de que no se haya podido abrir alguno de los
 *       ficheros, ha informado escribiendo un mensaje de error en «cerr».
 */
int main() {
    string codEvento;
    if (obtenerUltimoCodigo(FICH_TERREMOTOS, codEvento)) {
        unsigned numSismosNuevos;
        bool lecturaOk;
        actualizar(FICH_TERREMOTOS, FICH_ULTIMOS, codEvento, 
                   numSismosNuevos, lecturaOk);
        if (lecturaOk) {
            cout << "Se han añadido " << numSismosNuevos 
                 << " eventos al fichero \"" << FICH_TERREMOTOS << "\"." 
                 << endl;
            return 0;
        }
    }
    return 1;
}
