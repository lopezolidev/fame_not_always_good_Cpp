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

struct Nodo {
  int valor;
  bool visitado;
};

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

void merge(int *arr, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

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
    if (L[i] <= M[j]) {
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

void mergeSort(int *arr, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;


    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
} // implementación para ordenar el arreglo de aristas de forma ascendente según el peso

bool repetido(int *array, int v, int a){return true;}

void fillParents(int *padres, int dungeons, Edge *aristas, int cuantas_aristas){
  int i = 0;
  while(i < dungeons){
      padres[i] = -1;
      i++;
  }

  //arreglo donde escribiremos los nodos repetidos
  int repetidos[cuantas_aristas*2];
  for (int i = 0; i < cuantas_aristas*2; i++)
  {
      repetidos[i] = -1;
  }
    
  i = 0;
  int j = 0;
  while(i < cuantas_aristas && j < cuantas_aristas*2){
    repetidos[j] = aristas[i].origen;
    repetidos[j+1] = aristas[i].dest;
    i++;
    j+=2;
  }

  mergeSort(repetidos, 0, cuantas_aristas*2 - 1);

  int k = 0;
  i = 0;
  j = 1;
  padres[k] = repetidos[i];
  k++;
  while(j < cuantas_aristas*2){
    if(repetidos[i] != repetidos[j]){
      padres[k] = repetidos[j];
      k++;
    }
    i++;
    j++;
  }

} // función de llenar un arreglo de padres con los nodos no repetidos



void kruskal(Edge *arr, int dungeons, int aristas){
  // ordenaremos el arreglo de aristas de menor a mayor. Implementamos mergeSort para un mejor desempeño del ordenamiento en caso de un elevado volúmen de datos.
  mergeSort(arr, 0, aristas - 1);

  Edge *salida = new Edge[dungeons - 1]; //arreglo que almacena el camino mínimo

  //arreglo de los nodos sin alterar
  int *padres = new int[dungeons];
  fillParents(padres, dungeons, arr, aristas);

  //este arreglo de nodos lo utilizaremos para señalar si dos nodos pertenecen al mismo conjunto  
  Nodo nodes[dungeons];
  int j = 0;
  while(j < dungeons){
    nodes[j].valor = padres[j];
    nodes[j].visitado = false;
    j++;
  }

  int count = 0;
  int i = 0;
  while(count != aristas - 1){
    Edge currentEdge = arr[i];

    //chequeamos si podemos agregar la arista al grafo mínimal o no
    Nodo* x = nullptr;
    Nodo* y = nullptr;

    int l = 0;
    while(l < dungeons){
      if(currentEdge.origen == nodes[l].valor){
        x = &nodes[l];
      }
      l++;
    } // seleccionando el uno de los nodos

    l = 0;
    while(l < dungeons){
      if(currentEdge.dest == nodes[l].valor){
        y = &nodes[l];
      }
      l++;
    }

    if(!(x->visitado && y->visitado)){
      salida[count] = currentEdge;
      x->visitado = !x->visitado;
      y->visitado = !y->visitado;
      count++;
    } else {
      break;
    }
    i++;
  }

  cout << endl;
  int k = 0;
  while (k < count) {
    cout << salida[k].origen << " " << salida[k].dest << " " << salida[k].peso << endl;
    k++;
  }

  delete[] salida;
  delete[] padres;
  // limpieza de memoria de los arreglos de salida y padres
}

void getData(){
    int N, PW, K;
    N = PW = K = 0;

    cin >> N >> PW >> K;

    Edge *aristas_totales = new Edge[K]; // arreglo total de aristas

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