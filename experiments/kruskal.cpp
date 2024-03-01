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

  // for (int i = 0; i < cuantas_aristas*2; i++)
  // {
  //   cout << repetidos[i] << " ";
  // }
  // cout << endl;

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

} //terminar función de encontrar repetido



// finish function of findparent



int findParent(int node, int* parents){

}






void kruskal(Edge *arr, int dungeons, int aristas){
  // ordenaremos el arreglo de aristas de menor a mayor. Implementamos mergeSort para un mejor desempeño del ordenamiento en caso de un elevado volúmen de datos.
  mergeSort(arr, 0, aristas - 1);

  int i = 0;
  while(i < aristas){
      cout << "Nodo 1: " << arr[i].origen << ", Nodo 2: " << arr[i].dest << ", Peso: " << arr[i].peso << endl;
      i++;
  } // impresión para debugs

  Edge *salida = new Edge[dungeons - 1]; //arreglo que almacena el camino mínimo

  int *padres = new int[dungeons];
  fillParents(padres, dungeons, arr, aristas);
    
  for (int i = 0; i < dungeons; i++)
    {
      cout << padres[i] << " ";
    }
  cout << endl;

  int count = 0;
  i = 0;
  while(count != aristas - 1){
    Edge currentEdge = arr[i];

    //chequeamos si podemos agregar la arista al grafo mínimal o no
  
    int sourceParent = findParent(currentEdge.origen, padres);
    int destParent = findParent(currentEdge.dest, padres);

    if(sourceParent != destParent){
      salida[count] = currentEdge;
      count++;

      int j = 0;
      while(j < dungeons){
        if(padres[j] == sourceParent){
          padres[j] = destParent;
        }
        j++;
      }
    }
    i++;
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