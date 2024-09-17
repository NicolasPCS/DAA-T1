#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


///////// Creación de estructuras /////////

// Se crea estructura de las páginas

class Página
{
private:
    int h;
public:
    vector <int> pagina[256];
    bool buscar(int y);
    void insertar(int y);
};

class Pagina_principal: public Página{
public:
    vector<class Página> paginas_rebalse;
};

// Funciones de la Clase Página

bool Página::buscar(int y)
{
    int count = pagina.size(); 
    for (size_t i = 0; i < count; i++)
    {
        if (pagina[i] == y){
            return true;
        }
        if (pagina[i] == NULL)
        {
            return false;
        }
        
    }
}

void Página::insertar(int y)
{
    int count = pagina.size(); 
    for (size_t i = 0; i < count; i++)
    {
        if (pagina[i] == NULL){
            pagina[i] = y;
            break;
        }
        
    }
}







struct Paginas_rebalse
{
    int h;
    int pagina[256];
};

struct Pagina_principal
{
    int h;
    int pagina[256]; 
    vector<struct Paginas_rebalse> paginas_rebalse;
};


// Se crea estructura de la lista de hashing
struct lhashing
{
    int t;
    int p;
    int costo_actual;
    vector<struct Pagina_principal> paginas_principales;
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

//Función para buscar en página

bool buscar_pagina(int y, struct ){

}

// Función para ver si un elemento "y" está o no en la lista de hashing "lhashing"
bool buscar_hash(int y, struct lhashing *lh){
    vector<struct Pagina_principal> pag_principal = lh -> paginas_principales;

    int k = h(y) % (2^{lhashing.t + 1});
    
    // Buscamos en página principal con valor k 
    Pagina_principal pagk = pag_principal[k];
    int count = pagk.size();
    for (int i = 0; i < count; i++){
        lh-> costo_actual++;
        if(buscar_pagina(y, pagk.pagina[i])){
            return true;
        }
    }

    // Buscamos en páginas de rebalse asociadas a la página principal con valor k 
    vector<struct Paginas_rebalse> pag_rebalse = pagk.paginas_rebalse;

    //Se ve que existan páginas de rebalse
    if(pag_rebalse != NULL){
        int count = pag_rebalse.size();
        // Se busca en cada página de rebalse
        for (int i = 0; i < count; i++){
            lh-> costo_actual++;
            if(buscar_pagina(y, pag_rebalse[i])){
                return true;
            }
        }
    }
    //No se encontró el elemento y 
    return false
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