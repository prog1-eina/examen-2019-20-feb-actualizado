#include "constantes.hpp"


#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


/* Declaraciones de las constantes definidas en el enunciado */

/*
 * Registro para almacenar la información sísmica de cada una de las
 * provincias según el contenido de los ficheros «terremotos.csv» y 
 * «provincias.txt": 
 *  - el nombre de la provincia (como una cadena de caracteres de tipo string),
 *  - el número de terremotos registrados en la provincia según el fichero
 *    «terremotos.csv» y
 *  - la suma de sus magnitudes, para luego poder calcular su media.
 * 
 * No es necesario almacenar el código de la provincia puesto que en la
 * solución que se plantea a continuación, se va a utilizar un vector de
 * registros de este tipo y los datos de cada provincia se almacenarán en la
 * componente indexada por su código de provincia. Esto será así hasta que se
 * ordene el vector de mayor a menor número de terremotos, momento en el que
 * dejará de ser necesaria la relación entre las provincias y sus códigos.
 */
struct SismicidadProvincial {
    string provincia;
    unsigned numTerremotos = 0;
    double sumaMagnitudes = 0.0;
};


/* 
 * Pre:  Si el fichero «nombreFicheroProvincias» existe, se trata de un
 *       fichero de texto cuyo contenido cumple con la regla sintáctica 
 *       <fichero-provincias> y con el resto de restricciones establecidas en
 *       el enunciado.
 *       El vector «sismicidad» tiene NUM_PROVINCIAS + 1 componentes.
 * Post: Ha asignado, al campo «provincia» de cada una de las componentes
 *       indexadas entre 1 y NUM_PROVINCIAS del vector «sismicidad», ambas
 *       inclusive, el nombre de la provincia cuyo código sirve de índice a la
 *       componente, según los datos del fichero «nombreFicheroProvincias».
 *       Los valores de los otros campos no se han modificado. El valor de
 *       sismicidad[0] no está determinado.
 */
bool inicializarProvincias(const string nombreFicheroProvincias,
                            SismicidadProvincial sismicidad[]) {
    ifstream f(nombreFicheroProvincias);
    if (f.is_open()) {
        unsigned codProvincia;
        while (f >> codProvincia) {
            f.ignore(); // Separador entre código y nombre de la provincia
            // Lectura del nombre de la provincia a través de getline y no
            // del operado de extracción, debido a que hay provincias cuyo
            // nombre consta de más de una palabra.
            getline(f, sismicidad[codProvincia].provincia);
        }
        f.close();
        return true;
    } else {
        cerr << "No ha podido abrirse el fichero \""
             << nombreFicheroProvincias << "\"." << endl;
        return false;
    }    
}


/*
 * Pre:  El flujo «f» está abierto y asociado con un fichero de texto cuyo 
 *       contenido cumple con la regla sintáctica <fichero-terremotos> y el 
 *       resto de restricciones establecidas en el enunciado. Se está en
 *       disposición de leer de «f» desde el principio de una línea distinta a
 *       la de cabecera.
 * Post: Ha extraído una línea completa del flujo «f», asignando a los
 *       parámetros «magnitud» y «codProvincia» los valores correspondientes
 *       leídos de «f».
 *       Ha devuelto true si no se han terminado los datos del fichero en el
 *       intento de lectura y false en caso contrario.
 */
bool leerTerremoto(istream &f, double &magnitud, unsigned &codProvincia) {
    // También se podría haber optado por
    // repetir la instrucción 4 veces a través de un bucle for.
    string ignorar;
    getline(f, ignorar, DELIMITADOR);    // Código del terremoto
    getline(f, ignorar, DELIMITADOR);    // Fecha y hora
    getline(f, ignorar, DELIMITADOR);    // Coordenadas
    getline(f, ignorar, DELIMITADOR);    // Profundidad
    f >> magnitud;
    f.ignore();                          // DELIMITADOR
    f >> codProvincia;
    getline(f, ignorar);                 // Carácter de fin de línea
    return !f.eof();
}

/* 
 * Pre:  Si el fichero «nombreFicheroTerremotos» existe, se trata de un 
 *       fichero de texto cuyo contenido cumple con la regla sintáctica
 *       <fichero-terremotos> y con el resto de restricciones establecidas en
 *       el enunciado.
 *       El vector «sismicidad» tiene NUM_PROVINCIAS + 1 componentes en cada
 *       una de sus componentes indexadas entre 1 y NUM_PROVINCIAS los valores
 *       de los campos «numTerremotos» y «sumaMagnitudes» son iguales a 0.
 * Post: En cada una de las componentes indexadas entre 1 y NUM_PROVINCIAS del
 *       vector «sismicidad», ambas inclusive, el valor del campo
 *       «numTerremotos» es igual al número de terremotos registrados en la
 *       provincia cuyo código sirve de índice a la componente, según los
 *       datos del fichero «nombreFicheroTerremotos»; análogamente, el valor
 *       del campo «sumaMagnitudes» es igual a la suma de las magnitudes de
 *       los terremotos registrados en la provincia cuyo código sirve de
 *       índice a la componente, de nuevo, según los datos del fichero
 *       «nombreFicheroTerremotos». Los valores de los nombres de las
 *       provincias (campo «provincia») no se han modificado.
 *       El valor de sismicidad[0] no está determinado.
 */
bool leerTerremotos(const string nombreFicheroTerremotos,
                    SismicidadProvincial sismicidad[]) {
    ifstream f(nombreFicheroTerremotos);
    if (f.is_open()) {
        // Extracción de la cabecera del fichero  
        string cabecera;
        getline(f, cabecera); 
        
        double magnitud;
        unsigned codProvincia;
        while (leerTerremoto(f, magnitud, codProvincia)) {
        // Mientras se leen los datos del flujo y la última lectura es correcta
            // Se procesa el último dato leído: 
            sismicidad[codProvincia].numTerremotos++;
            sismicidad[codProvincia].sumaMagnitudes += magnitud;
        }
        f.close();
        return true;
    } else {
        cerr << "No ha podido abrirse el fichero \"" 
             << nombreFicheroTerremotos << "\"." << endl;
        return false;
    }
}

/*
 * Pre:  ---
 * Post: Ha intercambiado los valores iniciales de los parámetros «a» y «b».
 * Nota: Esta función es utilizada por la función como «ordenar» que figura a
 *       continuación y cuyo código no se solicitaba. Por lo tanto, esta
 *       función «intercambiar» podría no formar parte de la solución
 *       proporcionada por los estudiantes a este problema.
 */
void intercambiar(SismicidadProvincial &a, SismicidadProvincial &b) {
    SismicidadProvincial temp = a;
    a = b;
    b = temp;
}

/*
 * Pre:  El vector «sismicidad» tiene NUM_PROVINCIAS + 1 componentes. Las
 *       componentes indexadas entre 1 y NUM_PROVINCIAS, ambas inclusive,  
 *       almacenan información sísmica de una provincia diferente. El valor de
 *       sismicidad[0] no está determinado.
 * Post: Los datos de las componentes indexadas entre 1 y NUM_PROVINCIAS del 
 *       vector «sismicidad», ambas inclusive, están ordenados de mayor a
 *       menor número de terremotos y son una permutación de las que contenía
 *       el vector «sismicidad» al inicio de la ejecución de esta función.
 * Nota: El enunciado permitía utilizar una función de ordenación como
 *       «ordenar» sin necesidad de escribir el código que sigue. No obstante,
 *       se exigía proporcionar su cabecera y especificación.
 */ 
void ordenar(SismicidadProvincial sismicidad[]) {
    // Algoritmo de ordenación por selección directa.
    for (unsigned i = 1; i < NUM_PROVINCIAS; i++) {
        unsigned iMayor = i;
        for (unsigned j = i + 1; j <= NUM_PROVINCIAS; j++) {
            if (sismicidad[j].numTerremotos > sismicidad[iMayor].numTerremotos) {
                iMayor = j;
            }
        }
        intercambiar(sismicidad[i], sismicidad[iMayor]);
    }
}


/*
 * Pre:  El vector «sismicidad» tiene NUM_PROVINCIAS + 1 componentes. Las
 *       componentes indexadas entre 1 y NUM_PROVINCIAS, ambas inclusive,  
 *       almacenan información sísmica de una provincia diferente, ordenada de 
 *       mayor a menor número de terremotos. El valor de sismicidad[0] no está
 *       determinado.
 * Post: Esta función ha escrito en la pantalla un listado en en el que
 *       aparecen los nombres de las provincias españolas en las que
 *       se haya registrado al menos un terremoto según los datos del vector
 *       «sismicidad». En el listado se ha indicado el número de terremotos
 *       por provincia y la magnitud media de estos y se ha escrito ordenado por 
 *       número de terremotos de forma descendente, de acuerdo con el
 *       siguiente formato:
 * 
 *           Provincia     Nº terremotos  Magnitud media
 *       ===============================================
 *        1. Huelva                    18           2.49
 *        2. Cádiz                     12           2.33
 *        3. Granada                    7           2.16
 *       ... ...                      ...            ...
 */
void mostrar(const SismicidadProvincial sismicidad[]) {
    cout << "    Provincia     Nº terremotos  Magnitud media" << endl;
    cout << "===============================================" << endl;
    cout << fixed << setprecision(2);
    unsigned i = 1;
    while (i <= NUM_PROVINCIAS && sismicidad[i].numTerremotos > 0) {
        cout << setw(2) << i << ". " 
             << left << setw(25) << sismicidad[i].provincia 
             << right << setw(3) << sismicidad[i].numTerremotos 
             << setw(15) 
             << sismicidad[i].sumaMagnitudes / sismicidad[i].numTerremotos 
             << endl;
        i++;
    }
}


/* Pre:  Si los ficheros «FICH_TERREMOTOS» y «FICH_PROVINCIAS» existen, son
 *       ficheros de texto cuyos contenidos cumplen, respectivamente, con las
 *       reglas sintácticas <fichero-terremotos> y <fichero-provincias> y con 
 *       el resto de restricciones establecidas en el enunciado.
 * Post: Cuando es ejecutado, este programa escribe en la pantalla un listado
 *       en el que aparecen los nombres de las provincias españolas en las que
 *       se haya registrado al menos un terremoto según los datos del fichero 
 *       «FICH_TERREMOTOS». En el listado se indica el número de terremotos
 *       por provincia que aparecen en el citado fichero y la magnitud media
 *       de los mismos y aparece ordenado por número de terremotos de forma
 *       descendente, de acuerdo con el siguiente formato:
 *           Provincia     Nº terremotos  Magnitud media
 *       ===============================================
 *        1. Huelva                    18           2.49
 *        2. Cádiz                     12           2.33
 *       ... ...                      ...            ...
 *     
 *       En caso de que no se haya podido abrir alguno de los
 *       ficheros, ha informado escribiendo un mensaje de error en «cerr».
 */
int main() {
    // Declaración de un vector de 53 componentes para almacenar la información
    // sísmica de cada una de las provincias. La información de cada provincia 
    // estará indexada en la componente correspondiente a su código INE. La
    // componente indexada por 0 va a tener un valor no determinado y no va a
    // ser utilizada. Los valores iniciales de los campos «numTerremotos» y
    // «sumaMagnitudes» de cada componente son 0, puesto que así se ha indicado
    // en la definición del tipo registro «SismicidadProvincial».
    SismicidadProvincial sismicidad[NUM_PROVINCIAS + 1];
    
    if (inicializarProvincias(FICH_PROVINCIAS, sismicidad)) {
        if (leerTerremotos(FICH_TERREMOTOS, sismicidad)) {
            ordenar(sismicidad);
            mostrar(sismicidad);
            return RESULTADO_OK;        
        } else {
            return RESULTADO_ERROR_FICH_TERREMOTOS;
        }
    } else {
        return RESULTADO_ERROR_OTRO_FICH;
    }
}
