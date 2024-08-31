#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para cargar el diccionario desde un archivo
vector<string> cargarDiccionario(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> diccionario;
    string palabra;
    
    while (archivo >> palabra) {
        diccionario.push_back(palabra);
    }
    
    return diccionario;
}

// Función para cargar las consultas desde un archivo
vector<string> cargarConsultas(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> consultas;
    string consulta;
    
    while (archivo >> consulta) {
        consultas.push_back(consulta);
    }
    
    return consultas;
}

// Implementación de QuickSort
int particion(vector<string>& diccionario, int bajo, int alto) {
    string pivote = diccionario[alto];
    int i = (bajo - 1);
    
    for (int j = bajo; j <= alto - 1; j++) {
        if (diccionario[j] <= pivote) {
            i++;
            swap(diccionario[i], diccionario[j]);
        }
    }
    swap(diccionario[i + 1], diccionario[alto]);
    return (i + 1);
}

void quickSort(vector<string>& diccionario, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(diccionario, bajo, alto);
        
        quickSort(diccionario, bajo, pi - 1);
        quickSort(diccionario, pi + 1, alto);      
    }
}

// Algoritmo Secuencial
int algoritmoSecuencial(const vector<string> &diccionario, const string &consulta) {
    for (const auto &palabra : diccionario) {
        if (palabra == consulta) {
            return 1;
        }
    }
    return 0;
}

// Algoritmo de Búsqueda Binaria
int algoritmoBinario(const vector<string> &diccionario, const string &consulta) {
    int izquierda = 0, derecha = diccionario.size() - 1;
    
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (diccionario[medio] == consulta) {
            return 1;
        }
        if (diccionario[medio] < consulta) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return 0;
}

int main() {
    string nombreArchivoDiccionario;
    cout << "Ingresa el nombre del archivo del diccionario: ";
    cin >> nombreArchivoDiccionario;
    
    vector<string> diccionario = cargarDiccionario(nombreArchivoDiccionario);
    vector<string> consultas = cargarConsultas("Nc.txt");

    // Ordenar el diccionario utilizando QuickSort para la búsqueda binaria
    auto startSort = high_resolution_clock::now();
    quickSort(diccionario, 0, diccionario.size() - 1);
    auto stopSort = high_resolution_clock::now();
    auto sortDuration = duration_cast<milliseconds>(stopSort - startSort);
    
    int encontradosSecuencial = 0, encontradosBinario = 0;
    
    auto startSecuencial = high_resolution_clock::now();
    for (const auto &consulta : consultas) {
        encontradosSecuencial += algoritmoSecuencial(diccionario, consulta);
    }
    auto stopSecuencial = high_resolution_clock::now();
    auto secuencialDuration = duration_cast<milliseconds>(stopSecuencial - startSecuencial);

    auto startBinario = high_resolution_clock::now();
    for (const auto &consulta : consultas) {
        encontradosBinario += algoritmoBinario(diccionario, consulta);
    }
    auto stopBinario = high_resolution_clock::now();
    auto binarioDuration = duration_cast<milliseconds>(stopBinario - startBinario);

    cout << "Algoritmo Secuencial: " << secuencialDuration.count() << " ms, encontrados: " << encontradosSecuencial << endl;
    cout << "Algoritmo Binario (sin sort): " << binarioDuration.count() << " ms, encontrados: " << encontradosBinario << endl;
    cout << "Tiempo de ordenamiento: " << sortDuration.count() << " ms" << endl;
    cout << "Algoritmo Binario (con sort): " << binarioDuration.count() + sortDuration.count() << " ms" << endl;

    return 0;
}
