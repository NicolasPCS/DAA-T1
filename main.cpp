#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


///////// Creación de estructuras /////////

// Se crea estructura de las páginas
struct Pagina
{
    int pagina[256]; 
};

// Se crea estructura de la lista de hashing
struct lhashing
{
    int h;
    int t;
    int p;
    int costo_actual;
    vector<vector <int>[256]> paginas_principales;
    vector<vector <int>[256]> paginas_rebalse;
    
};

///////// Creación de funciones  /////////


// Función de hashing h(y) que debe devolver un valor aleatorio entre 0 y 264 − 1 para cualquier elemento y
long long h(int y){
    long long hash = rand() % (2^[64]);
    return hash;
}

double porcentaje_llenado(vector<struct Pagina> paginas){
    return
}

// Función para ver si un elemento "y" está o no en la lista de hashing "lhashing"
bool buscar_hash(int y, struct lhashing *lh){
    vector<vector <int>[256]> pag_principal = lh -> paginas_principales;
    vector<vector <int>[256]> pag_rebalse = lh -> paginas_rebalse;

    


    lh-> costo_actual++;
    return true
}

// Función que inserta un elemento en la lista de hashing cuando este no se encuentre
void insertar_hash(int y, struct lhashing *lh, int costo_promedio){
    vector<vector <int>[256]> pag_principal = lh -> paginas_principales;
    // Se encuentra que el elemento "y" ya está
    if(buscar_hash(y, lh)){
        
    }

    // El elemento "y" no se encuentra, se busca donde insertarlo

    int k = h(y) % (2^{lhashing.t + 1});

    // Página ya existe
    if(k < (lh -> p)){

        vector <int>[256] pagk = pag_principal[k];

        // La página k se rebalsa, se crea página de rebalse 
        if(pag_principal[k].tail() != NULL){
            Pagina *nueva_rebalse;

            nueva_rebalse -> pagina.push(y);
            lh.paginas_rebalse.push(nueva_rebalse);
            lh.costo_actual++;
        }
        // Se inserta en la página k
        else{

        }
    }

    // La página k aún no ha sido creada, por lo cual se debe insertar en la página k − 2t.
    else{


    }
    
}


///////// Main /////////

int main()
{
    std::cout << "Hola mundo!" << std::endl;
    return 0;
}