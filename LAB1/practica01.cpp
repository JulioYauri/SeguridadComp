#include <fstream> 
#include <vector> 
#include <string> 
#include <map> 
#include <iostream> 
using namespace std;  

map<char, char> sust;
void init_susti() {
    sust['J'] = 'I';
    sust['H'] = 'I'; 
    sust['K'] = 'L';
    sust['U'] = 'V'; 
    sust['W'] = 'V';
    sust['Y'] = 'Z'; 
}

bool convert(char &c) {
    if(!isalpha(c)) return false; // si no es una letra, se debe borrar el caracter
    c = toupper(c); // se convierte el caracter a mayúscula 
    if(sust.count(c)) c = sust[c]; // se realizan las sustituciones 
    return true; 
}

vector<int> frecuencias(vector<string> input) {
    vector<int> res(26, 0);
    for(string s : input) {
        for(char c : s) {
            if(c >= 'A' && c <= 'Z') {
                res[c - 'A']++; 
            }
        }
    }
    return res; 
}

void guardar(vector<string> texto, string nombre) {
    ofstream output(nombre);
    for(auto i : texto) output << i << "\n"; 
    output.close();
}

void preprocess() {
    ifstream input("heraldosnegros.txt");
    vector<string> texto;
    string s; 
    while(getline(input, s)) texto.push_back(s);

    // preprocesando el texto 
    int n = texto.size();
    vector<string> res(n);
    for(int i = 0; i < n; i++) {
        string s = texto[i];
        string to; 
        for(char c : s) { // se intenta convertir cada caracter
            // si no se cumple, el caracter no era una letra 
            if(convert(c)) to.push_back(c);
        }
        res[i] = to; 
    }

    // se obtienen las frecuencias 
    vector<int> freq = frecuencias(res);
    map<int, char> order;  // ordenando las frecuencias 
    for(int i = 0; i < (int)freq.size(); i++) {
        order[freq[i]] = 'A' + i; 
    }

    guardar(res, "HERALDOSNEGROS_pre.txt");

    cout << "preprocesamiento terminado\n"; 
    cout << "caracteres con mayor frecuencia:\n"; 
    // imprimiendo los 5 caracterers con mayor frecuencia
    auto it = order.rbegin();
    for(int i = 0; i < 5; i++) {
        cout << it -> second << " -> " << it -> first << " veces\n"; 
        it++; 
    }

}

int main() {
    preprocess();
}