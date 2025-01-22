#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <cctype>


using namespace std; 

/*Vamos a leer el archivo para crear la matriz*/
vector<vector<int>> readFile (string filee){
    ifstream file(filee);
    if(!file){
        cout << "No se encontró el archivo \n";
        return {}; 
    }

    int size; 
    string line; 
    getline(file, line); 

    stringstream convertir(line); 
    convertir >> size;

    if(size <= 0){
        cout <<"El tamaño de la matriz es inváliddo";
        return{};
    }

    vector<vector<int>> matrix(size, vector<int>(size));

    for (int i = 0; i < size; i++) {
        getline(file, line); 
        stringstream lineS(line); 
        string n; 

        for (int j = 0; j < size; j++) {
            getline(lineS,n, ',' );
            matrix [i][j]= stoi(n);
        }
    }

    return matrix;
}

/*EL algoritmo de dijkstra para saber el camino más corto*/
vector<int> dijkstra (vector<vector<int>> matrix, int start){
    int size= matrix.size();
    vector <int> distance( size, numeric_limits<int>::max());
    vector <bool> visit (size, false);

    distance[start]= 0; 

    for (int i=0; i< size; i++){
        int min= numeric_limits<int>::max();
        int actual= -1; 

        for (int j=0; j < size; j++){
            if(!visit[j] && distance [j] < min){
                min= distance [j];
                actual= j; 

            }
        }

        if (actual== -1) break;

        visit[actual]= true; 

        for ( int a=0; a< size; a++){
            if(matrix[actual][a] > 0 && !visit[a]){
                int newDistance= distance[actual] + matrix [actual][a];
                if(newDistance < distance[a]){
                    distance[a]= newDistance; 
                }
            }
        }
    }

    return distance; 

}

int main(){

    string file= "texto.txt"; 
    vector<vector<int>> matrix= readFile(file); 

    /*imprimo la matriz que aparece en el txt*/
    for (const auto& row : matrix) {
        for (int n : row) {
            cout << n << " ";
        }
        cout << endl;
    }

    /*Implemento la parte de letras y cosas de dijkstra*/
    char input; 
    cout << "\n Ingrese el nodo al cual quiere llegar: ";
    cin >> input; 
    input= toupper(input);

    int find = input - 'A'; 

    if(find < 0 || find >= matrix.size()){
        cout <<"Nodo inválido \n";
        return 1; 
    }

    vector<int> distance= dijkstra (matrix, 0);

    if(distance[find] == numeric_limits<int>::max()){
        cout << "No hay camino \n";
    }else{
        cout <<" La distancia es: " << distance [find] << endl; 
    }

    return 0;
}

