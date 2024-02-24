#include <iostream>
using namespace std;

class Edge{
    public:
        int peso;
        int origen;
        int dest;
    Edge(){
        peso = 0;
        origen = 0;
        dest = 0;
    }
}; // edge class → arista

void merge(Edge *arr, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  Edge L[n1], M[n2];

  for (int i = 0; i < n1; i++) {
    L[i] = arr[p + i];
  }
  for (int j = 0; j < n2; j++) {
    M[j] = arr[q + 1 + j];
  }

  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i].peso <= M[j].peso) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }


  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(Edge *arr, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;


    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
} // implementación para ordenar el arreglo de aristas de forma ascendente según el peso

bool repetido(int *array, int v, int a){

}

void fillParents(int *arr, int d, Edge *aristas, int cuantas_aristas){
    int i = 0;
    while(i < d){
        arr[i] = -1;
        i++;
    }

    int j = 0;
    int k = 0;
    while(j < cuantas_aristas){

        if(!repetido(arr, aristas[j].origen, k)){
            arr[k] = aristas[j].origen;
            k++;
        } 
        if(!repetido(arr, aristas[j].dest, k)){
            arr[k] = aristas[j].dest;
            k++;
        }

        j++;
    }
    
} //terminar función de encontrar repetido

void kruskal(Edge *arr, int dungeons, int Aristas){
    // ordenaremos el arreglo de aristas de menor a mayor. Implementamos mergeSort para un mejor desempeño del ordenamiento en caso de un elevado volúmen de datos.
    mergeSort(arr, 0, Aristas - 1);

    int i = 0;
    while(i < Aristas){
        cout << "Nodo 1: " << arr[i].origen << ", Nodo 2: " << arr[i].dest << ", Peso: " << arr[i].peso << endl;
        i++;
    } // impresión para debugs

    Edge *salida = new Edge[dungeons - 1]; //arreglo que almacena el camino mínimo

    int *padres = new int[dungeons];
    fillParents(padres, dungeons, arr, Aristas);


    // delete[] salida;
    // delete[] padres;
    // limpieza de memoria de los arreglos de salida y padres
}

void getData(){
    int N, PW, K;
    N = PW = K = 0;

    cin >> N >> PW >> K;

    Edge *aristas_totales = new Edge[K]; // arreglo total de aristas

    cout << "dungeons: " << N << ", " << "power: " << PW << ", " << "connections: " << K << endl; 

    int i = 0;
    while(i < K){
        int o, d, p;

        cin >> o >> d >> p;

        aristas_totales[i].origen = o;
        aristas_totales[i].dest = d;
        aristas_totales[i].peso = p;

        i++;
    }

    kruskal(aristas_totales, N, K);

    delete[] aristas_totales;

} //función para tomar los datos de entrada y llenar el arreglo de aristas

int main(){
    getData();

    return 0;
}