#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Digraph.h"

using namespace std;


/*
 GUARDAR LISTA COMPLETA EN UN ARCHIVO .TXT
  (Incluye el texto introductorio con el nodo mayor)
*/  
void save_adjacency_to_file(
    const Digraph<string> &g,
    const string &filename,
    const string &max_ip,
    int max_degree
) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "No se pudo crear el archivo: " << filename << "\n";
        return;
    }

    //TEXTO DESCRIPTIVO AL INICIO 
    out << "===============================================\n";
    out << "   RESULTADO DEL ANALISIS DEL GRAFO\n";
    out << "===============================================\n";
    out << "Nodo con MAYOR grado de salida:\n";
    out << "IP: " << max_ip << "\n";
    out << "Grado de salida: " << max_degree << "\n";
    out << "===============================================\n\n";

    out << "LISTA COMPLETA DE ADYACENCIAS:\n\n";

    // Obtener la lista desde el Digraph
    auto adj = g.get_adjacency();

    for (auto &node : adj) {
        out << node.first << ": ";
        for (auto &nb : node.second) {
            out << nb << " | ";
        }
        out << "\n";
    }

    out.close();
    cout << "\nLa lista COMPLETA se guardó en: " << filename << "\n";
}


//MAIN
int main() {
    Digraph<string> g;
    unordered_map<string, int> outdegree;

    string filename;
    cout << "Ingresa el nombre del archivo CSV: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo.\n";
        return 1;
    }

    string line;

    // Ignorar encabezado del CSV
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string fecha, hora, ip_src, port_src, ip_dst, port_dst, razon;

        // Leer las 7 columnas del archivo CSV
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, ip_src, ',');   // IP ORIGEN
        getline(ss, port_src, ',');
        getline(ss, ip_dst, ',');   // IP DESTINO
        getline(ss, port_dst, ',');
        getline(ss, razon, ',');

        if (ip_src.empty() || ip_dst.empty()) {
            continue;
        }

        g.add_edge(ip_src, ip_dst);
        outdegree[ip_src]++;
    }

    if (outdegree.empty()) {
        cout << "No se encontraron conexiones.\n";
        return 0;
    }

// Encontrar IP con mayor grado de salida
    string max_ip;
    int max_degree = -1;

    for (auto &p : outdegree) {
        if (p.second > max_degree) {
            max_degree = p.second;
            max_ip = p.first;
        }
    }

    cout << "\n--- RESULTADOS EN CONSOLA ---\n";
    cout << "IP con MAYOR grado de salida: " << max_ip << "\n";
    cout << "Grado de salida: " << max_degree << "\n";

    // Guardar la lista COMPLETA en un archivo .txt
    save_adjacency_to_file(g, "lista_completa.txt", max_ip, max_degree);

    return 0;
}
