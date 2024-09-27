#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
using namespace std;


///////// Creación de estructuras /////////

// Se crea estructura de las páginas

// class Página
// {
// private:
//     int h;
// public:
//     vector <int> pagina[256];
//     bool buscar(int y);
//     void insertar(int y);
// };

// class Pagina_principal: public Página{
// public:
//     vector<class Página> paginas_rebalse;
// };

// // Funciones de la Clase Página

// bool Página::buscar(int y)
// {
//     int count = pagina.size(); 
//     for (size_t i = 0; i < count; i++)
//     {
//         if (pagina[i] == y){
//             return true;
//         }
//         if (pagina[i] == NULL)
//         {
//             return false;
//         }
        
//     }
// }

// void Página::insertar(int y)
// {
//     int count = pagina.size(); 
//     for (size_t i = 0; i < count; i++)
//     {
//         if (pagina[i] == NULL){
//             pagina[i] = y;
//             break;
//         }
        
//     }
// }
struct Paginas_rebalse
{
    int h;
    vector<int> pagina_r;
};

struct Pagina_principal
{
    int h;
    vector<int> pagina_p;
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
    double d= pow(2,64);
    srand(y);
    long long hash = fmod(rand(),d);
    return hash;
}

// double porcentaje_llenado(vector<struct Pagina> paginas){
//     return
// }

//Función aux: Encuentra la ultima posicion vacía de un vector de int
int posicion_vacia(vector<int> v){
    for(int i=0; i<1023;i++){
        if(v[i]==NULL){
            return i;
        }
    }
    return -1;
}

//Función aux: Entrega la ultima posicion vacia de la pagina de rebalse i
vector<int> pag_r_y_posicion(vector<struct Paginas_rebalse> vp){
    vector<int> v= {-1,-1};
    for(int i=0;i<vp.size();i++){
        struct Paginas_rebalse vp_i = vp[i];
        int pos= posicion_vacia(vp_i.pagina_r);
        if(pos!=-1){
            v[0]=i;
            v[1]=pos;
            return v;
        }
        
    }
    return v;
}

//Función aux: Imprime un vector de int
void print_vector(vector<int> v){
    cout <<"(";
    for(int i=0;i<(int)v.size();i++){
        cout << v[i]<<" ";
    }
    cout <<")\n";
    return;
}

//Función aux: Imprime un vector de Paginas pricipales
void print_paginas(vector<struct Pagina_principal> p, int np){
    for(int i=0; i < np;i++){
        struct Pagina_principal pag_p = p[i];
        cout << "Pag principal " << i <<"\n";
        print_vector(pag_p.pagina_p);
        cout<<"Largo paginas principales "<<pag_p.pagina_p.size()<<"\n";
        if(pag_p.pagina_p.size()==128){
            vector<struct Paginas_rebalse> pags_r=pag_p.paginas_rebalse;
            for (int j=0; j<pags_r.size();j++){
                struct Paginas_rebalse pagina_r=pags_r[j];
                cout << "Pag rebalse " << j <<"(pp "<< i<<")\n";
                print_vector(pagina_r.pagina_r);
            }
        }
    }
    return;
}
//Función aux: Imprime un lhashing completo
void print_hash(lhashing *lh){
    cout << "Hashing Lineal:\n";
    cout << "t: " << lh->t << "\n";
    cout << "p: " << lh->p << "\n";
    cout << "costo_actual: " << lh->costo_actual << "\n";
    print_paginas(lh->paginas_principales,lh->p);
    return;    
}
//Funcion aux: Busca un int y en un vector 
bool buscar_vec(int y, vector<int> v){
    for( int i=0; i<v.size();i++){
        if(v[i]==y){
            return true;
        }
    }
    return false;
}
//Función aux: Busca int y en vector de paginas de rebalse
bool buscar_paginas_r(int y, vector<struct Paginas_rebalse> pr){
    for(int j=0;j<pr.size();j++){
        vector<int> r= pr[j].pagina_r;
        if(buscar_vec(y,r)){
            return true;
        }
    }
    return false;
}
//Función aux: Busca int y en una pagina principal
bool buscar_pagina_p(int y, Pagina_principal pp){
    vector<struct Paginas_rebalse> pr= pp.paginas_rebalse;
    vector<int> p=pp.pagina_p;
    if(buscar_vec(y ,p)){
        return true;
    }
    return buscar_paginas_r(y,pr);
}

// Función aux: Busca un int "y" en la lista de hashing "lhashing"
bool buscar_hash(int y, struct lhashing *lh){
    vector<struct Pagina_principal> pag_principal = lh -> paginas_principales;
    if(pag_principal.size()<1){
        return false;
    }
    for (int i = 0; i < pag_principal.size(); i++){
        Pagina_principal pagk = pag_principal[i];
        cout<<"dentro del for\n";
        lh-> costo_actual++;
        if(buscar_pagina_p(y, pagk)){
            return true;
        }
    
    }
    return false;
}
bool pagina_r_libre(vector<Paginas_rebalse> p_r){
    if(p_r[p_r.size()-1].pagina_r.size()<128){
        return true;
    }
    else{
        return false;
    }
}

// Función que inserta un elemento en la lista de hashing cuando este no se encuentre
void insertar_hash(int y, struct lhashing *lh){
    vector<struct Pagina_principal> pag_principal = lh -> paginas_principales;
    cout<<"extraje pags princ\n";
    // Se encuentra que el elemento "y" ya está
    if(buscar_hash(y, lh)){
        cout<<"y ya existe\n";
        return;
    }
    int k;
    // El elemento "y" no se encuentra, se busca donde insertarlo
    cout<<"antes de k\n";
    if (pag_principal.size()<2){
        k=0;
    }else{
        k = h(y) % (long long)pow(2,lh->t + 1);
    }
    cout<<"obtuve k "<<k<<"\n";
    // Página ya existe
    if(k < (lh -> p)){
        cout<<"pag k existe\n";
        vector<int> pagk = pag_principal[k].pagina_p;
        cout<<"tengo pagk\n";
        // La página k se rebalsa, se crea página de rebalse 
        if(pagk.size()==128){
            cout<<"pagk estaba llena\n";
            if (pag_principal[k].paginas_rebalse.size()>=1){
                int largo_pag_r=pag_principal[k].paginas_rebalse.size();
                if(pagina_r_libre(pag_principal[k].paginas_rebalse)){
                    cout<<"tengo espacio en pag de rebalse\n";
                    lh -> paginas_principales[k].paginas_rebalse[largo_pag_r-1].pagina_r.push_back(y);
                    return;
                }else{
                    cout<<"no tengo espacio en pag rebalse\n";
                    struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
                    nueva_rebalse->h=pag_principal[k].h;
                    nueva_rebalse->pagina_r.push_back(y);
                    lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
                    lh->costo_actual++;
                    return; 
                }
            }else{
                cout<<"no hay pag de rebalse\n";
                struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
                nueva_rebalse->h=pag_principal[k].h;
                nueva_rebalse->pagina_r.push_back(y);
                lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
                lh->costo_actual++;
                return;
            }
        }
        // Se inserta en la página k
        else{
            cout<<"antes de insertar y\n";
            lh -> paginas_principales[k].pagina_p.push_back(y);
            //pag_principal[k].pagina_p.push_back(y);
            cout<<"largo pag "<<pag_principal[k].pagina_p.size()<<"\n";
            return;
        }
    }

    // La página k aún no ha sido creada, por lo cual se debe insertar en la página k − 2t.
    else{
        cout<<"pag k no existe\n";
        int posicion = k- 2*(lh->t);
        if (posicion<0){
            cout<<"posicion <0\n";
            struct Pagina_principal pag_0 = pag_principal[0];
            cout<<"primera pag pric\n";
            vector<int> pag_pag_0= pag_0.pagina_p;
            int pos_i=posicion_vacia(pag_pag_0);
            if(pos_i<=128){
                lh -> paginas_principales[0].pagina_p.push_back(y);
                return;
            }else{
                if (pag_0.paginas_rebalse.size()>1){
                int largo_pag_r=pag_0.paginas_rebalse.size();
                    if(pagina_r_libre(pag_0.paginas_rebalse)){
                        lh -> paginas_principales[k].paginas_rebalse[largo_pag_r-1].pagina_r.push_back(y);
                        return;
                    }else{
                        struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
                        nueva_rebalse->h=pag_principal[k].h;
                        nueva_rebalse->pagina_r.push_back(y);
                        lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
                        lh->costo_actual++;
                        return; 
                    }
                }else{
                struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
                nueva_rebalse->h=pag_principal[k].h;
                nueva_rebalse->pagina_r.push_back(y);
                lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
                lh->costo_actual++;
                return;
                }
            }
        }
        cout<<"posicion: "<<posicion<<"\n";
        struct Pagina_principal pag_k_2t = pag_principal[posicion];
        vector<int> pag_pag_k_2t= pag_k_2t.pagina_p;
        int pos_i=posicion_vacia(pag_pag_k_2t);
        if(pos_i<=127){
            lh -> paginas_principales[posicion].pagina_p.push_back(y);
            return;
        }else{
            if (pag_k_2t.paginas_rebalse.size()>1){
                int largo_pag_r=pag_k_2t.paginas_rebalse.size();
                if(pagina_r_libre(pag_k_2t.paginas_rebalse)){
                    lh -> paginas_principales[k].paginas_rebalse[largo_pag_r-1].pagina_r.push_back(y);
                    return;
                }else{
                    struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
                    nueva_rebalse->h=pag_principal[k].h;
                    nueva_rebalse->pagina_r.push_back(y);
                    lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
                    lh->costo_actual++;
                    return; 
                }
            }else{
            struct Paginas_rebalse *nueva_rebalse=new Paginas_rebalse;
            nueva_rebalse->h=pag_principal[k].h;
            nueva_rebalse->pagina_r.push_back(y);
            lh -> paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
            lh->costo_actual++;
            return;
            }
        }
        return;
    }
    
}

//Función aux: Crea un lhashing con t y p paginas
struct lhashing *crear_lhashing(int t,int p){
    struct lhashing *lh= new lhashing;
    lh->t=t;
    lh->p=p;
    lh->costo_actual=0;
    cout<<"antes del crear vector\n";
    vector<struct Pagina_principal> pag_princ;
    cout<<"antes del for\n";
    for(int i=0;i<p;i++){
        cout<<"for\n";
        long long h=0;
        struct Pagina_principal pag_i;
        pag_i.h = h;
        pag_princ.push_back(pag_i);
    }
    lh->paginas_principales = pag_princ;
    return lh;
}

///////// Main /////////

int main(){
    struct lhashing *lh=crear_lhashing(0,1);
    for (int i =1; i<301; i++){
        cout<<i<<"\n";
        insertar_hash(i,lh);
    }
    cout<<"antes de morir\n";
    print_hash(lh);    
    return 0;
}