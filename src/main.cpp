#include <iostream>
#include <math.h>
using namespace std;

const int INF = int(INFINITY);

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

class Nodo {
public: 
  int id;
  int distancia;
  bool enMST;
  int padre;
  Nodo* nexos;
  int numero_nexos;

  Nodo(int id){
    this->id = id;
    distancia = INF;
    enMST = false;
    padre = 0;
    nexos = nullptr;
    numero_nexos = 0;
  }

  Nodo(){}
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

void fillParents(Nodo *padres, int dungeons, Edge *aristas, int cuantas_aristas){
  int i = 0;
  while(i < dungeons){
      padres[i].id = -1;
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
  padres[k].id = repetidos[i];
  k++;
  while(j < cuantas_aristas*2){
    if(repetidos[i] != repetidos[j]){
      Nodo nuevoNodo = Nodo(repetidos[j]);
      padres[k] = nuevoNodo;
      k++;
    }
    i++;
    j++;
  }

} // función de llenar un arreglo de padres con los nodos no repetidos

void crear_nexos(Edge* arreglo_aristas, int numero_aristas, Nodo* arreglo_nodos, int dungeons){
    int i = 0;
    int c = 0;
    while(i < dungeons){
      int j = 0;
      c = 0;
      while(j < numero_aristas){
        if(arreglo_aristas[j].origen == arreglo_nodos[i].id || arreglo_aristas[j].dest == arreglo_nodos[i].id ){
          c++;
        }
        j++;
      }

      arreglo_nodos[i].nexos = new Nodo[c];
      //arreglo de punteros a nodos del nodo en cuestión

      arreglo_nodos[i].numero_nexos = c;
      cout << "contador: " << c << endl;
      cout << "nodo " << arreglo_nodos[i].id; 

      Nodo* nodo_a_agregar = nullptr;

      int k = 0;
      int id_nodo_a_buscar = 0;
      int m = 0;
      while(k < numero_aristas && m < c){
        if(arreglo_aristas[k].origen == arreglo_nodos[i].id){
          id_nodo_a_buscar = arreglo_aristas[k].dest;
        }else if(arreglo_aristas[k].dest == arreglo_nodos[i].id){
          id_nodo_a_buscar = arreglo_aristas[k].origen; 
        }
        k++;

        int l = 0;
        while(l < dungeons){
          if(arreglo_nodos[l].id == id_nodo_a_buscar){
            arreglo_nodos[i].nexos[m] = arreglo_nodos[l];
            m++;
          }
          l++;
        }
      }
      int n = 0;
      while(n < c){
        cout << " conectado con: " << arreglo_nodos[i].nexos[n].id << endl;
        n++;
      }

      i++;
    }

    // i = 0;
    // while(i < dungeons){
    //   cout << "nodo " << arreglo_nodos[i].id << " está unido a los nodos: ";
    //   int j = 0;
    //   while(j < arreglo_nodos[i].numero_nexos){
    //     cout << arreglo_nodos[i].nexos[j].id << endl;
    //     j++;
    //   }
    //   i++;
    // }
}

void recommendation(Edge* arreglo_aristas, int numero_aristas, Nodo* arreglo_nodos, int dungeons){
    crear_nexos(arreglo_aristas,numero_aristas, arreglo_nodos, dungeons);

}// función que encuentra los nodos recomendados para que sean posibles raíces




void update_nodos(Nodo* nodo, Nodo* arreglo_nodos, Edge* arreglo_aristas, int numero_aristas, int dungeons){
  int i = 0;
  int valor_actualizable = 0;
  while(i < numero_aristas){
    if(arreglo_aristas[i].origen == nodo->id){
      valor_actualizable = arreglo_aristas[i].dest;
      // cout << "para nodo " << nodo->id << " valor actualizable es: " << valor_actualizable << endl;
    } else if(arreglo_aristas[i].dest == nodo->id){
      valor_actualizable = arreglo_aristas[i].origen;
    }

    int distancia_arista_actual = arreglo_aristas[i].peso;

    // cout << "infinity: " << INF << endl;

    int j = 0;
    while(j < dungeons){
      if((arreglo_nodos[j].id == valor_actualizable && arreglo_nodos[j].enMST == false) && distancia_arista_actual < arreglo_nodos[j].distancia){
        arreglo_nodos[j].distancia = distancia_arista_actual;
        arreglo_nodos[j].padre = nodo->id;
        // cout << "arreglo_nodos[" << j << "].distancia : " << arreglo_nodos[j].distancia << endl; 
      } 
      j++;
    }
    i++;
  }
}//función que actualiza las aristas que conectan nodos. Estas serán actualizadas a los nodos alcanzables si cumplen con la condición de que la distancia de la arista en el momento de la iteración sea menor a la distancia a la que ya es alcanzable el nodo, este no se encuentra en el MST (Minimum Spanning Tree) y su valor es el buscadoe en el arreglo de nodos. Además actualizamos el padre del nodo actualizado, así sabiendo que puede tener "un solo padre" (el nodo del que provenimos)

Nodo* dame_el_menor(Nodo* nodos_candidatos, int counter){
    int i = 0;
    Nodo* candidato = &nodos_candidatos[0];
    while(i < counter){
      if(nodos_candidatos[i].distancia < candidato->distancia){
        candidato = &nodos_candidatos[i];
      }
      i++;
    }

    return candidato;
}

Nodo* calcula_siguiente_nodo(Nodo* arreglo_nodos, int mazmorras){
  Nodo* menor_nodo = nullptr;

  int i = 0;
  while(i < mazmorras){
    if(arreglo_nodos[i].enMST == false && arreglo_nodos[i].distancia < INF){
      if(menor_nodo == nullptr || arreglo_nodos[i].distancia < menor_nodo->distancia){
        menor_nodo = &arreglo_nodos[i];
      }
    }
    i++;
  }

  if(menor_nodo != nullptr){
    menor_nodo->enMST = true;
  }

  return menor_nodo;
} // función que calcula el próximo nodo a procesar con los criterios del algoritmo de Prim. Empleando un puntero que señala a la dirección de memoria del nodo con menor distancia alcanzable y que no haya sido seleccionado dentro del conjunto de nodos del árbol mínimo recubridor

Edge* aristas_escogidas(Edge* aristas_salida, Edge* arreglo_aristas, int numero_aristas, Nodo* arreglo_nodos, int mazmorras){
  
  int i = 1;

  while(i < mazmorras){
  
    int j = 0;
    while(j < numero_aristas){
  
      if((arreglo_nodos[i].id == arreglo_aristas[j].origen || arreglo_nodos[i].id == arreglo_aristas[j].dest) && (arreglo_nodos[i].padre == arreglo_aristas[j].origen || arreglo_nodos[i].padre == arreglo_aristas[j].dest) && arreglo_nodos[i].distancia == arreglo_aristas[j].peso){
  
        aristas_salida[i - 1] = arreglo_aristas[j];
        i++;
  
      }
  
      j++;
    }
  }

  return aristas_salida;
} // función que retorna el arreglo de aristas que conforman el grafo minimal. Se escoge la arista con base a los criterios de que el nodo en cuestión sea origen o destino de la arista, el padre de dicho nodo sea el origen o destino de la arista y el peso de la misma sea la distancia mínima alcanzable del nodo particular

void prim(Edge *arreglo_aristas, int dungeons, int aristas){
  // ordenaremos el arreglo de aristas de menor a mayor. Implementamos mergeSort para un mejor desempeño del ordenamiento en caso de un elevado volúmen de datos.
  mergeSort(arreglo_aristas, 0, aristas - 1);

  Edge *salida = new Edge[dungeons - 1]; //arreglo que almacena el camino mínimo

  //arreglo de los nodos sin alterar
  Nodo *nodos = new Nodo[dungeons];
  fillParents(nodos, dungeons, arreglo_aristas, aristas);

  //este arreglo de nodos lo utilizaremos para señalar si dos nodos pertenecen al mismo conjunto  
  
  nodos[0].distancia = 0;
  nodos[0].padre = -1;

  int i = 0;
  while(i < dungeons){
    Nodo* nodo_actual = calcula_siguiente_nodo(nodos, dungeons);

    update_nodos(nodo_actual, nodos, arreglo_aristas, aristas, dungeons);

    i++;
  }

  salida = aristas_escogidas(salida, arreglo_aristas, aristas, nodos, dungeons);

  mergeSort(salida, 0, dungeons - 1);

  cout << endl << endl << endl;

  i = 0;
  while(i < dungeons-1){
    cout << salida[i].origen << " " << salida[i].dest << " " << salida[i].peso << endl;
    i++;
  } // impresión de caminos mínimos del grafo

recommendation(salida, dungeons - 1, nodos, dungeons);

} // función que ejecuta el algoritmo de Prim. 

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

    prim(aristas_totales, N, K);



    delete[] aristas_totales;

} //función para tomar los datos de entrada y llenar el arreglo de aristas

int main(){
    getData();

    return 0;
}