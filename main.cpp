#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <ctime>

using namespace std;
const int PAGE_SIZE = 1024 / sizeof(long long);

//-- Definición de estructuras --//

// Estructura de una página
struct PaginaPrincipal
{
    vector<int> pagina_principal;
    vector<struct PaginaRebalse> paginas_rebalse;
};

// Estructura de páginas de rebalse
struct PaginaRebalse
{
    vector<int> pagina_rebalse;
};

// Estructura de la lista de hashing
struct HashingLineal
{
    int t;
    int p;
    int semilla_h;
    int costo_actual;
    int cant_elementos_insert;
    vector<struct PaginaPrincipal> paginas_principales;
};

//-- Implementación de funciones --//

// Función de hashing h(y)
// Devuelve un valor aleatorio entre 0 y 264 − 1 para cualquier elemento 'y'
long long h(int y, int semilla)
{
    srand(semilla);
    double d = pow(2, 64);
    srand(y);
    long long hash = fmod(rand(), d);
    return hash;
}

// Función aux: Encuentra la ultima posicion vacía de un vector de int
int posicion_vacia(vector<int> v)
{
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        if (v[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

// Función aux: Imprime un vector de int
void print_vector(vector<int> v)
{
    cout << "(";
    for (int i = 0; i < (int)v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << ")\n";
    return;
}

// Función aux: Calcula el porcentaje de llenado de una página
double porcentaje_llenado_pagina(vector<int> pag){
    if (pag.size() == PAGE_SIZE)
    {
        return 100;
    } else {
        return (pag.size() * 100) / PAGE_SIZE;
    }
}

// Función aux: Imprime un vector de páginas pricipales y sus páginas de rebalse
void print_paginas(vector<struct PaginaPrincipal> p, int np)
{
    for (int i = 0; i < np; i++)
    {
        struct PaginaPrincipal pag_p = p[i];
        cout << "Pag. principal -> " << i << "\n";
        print_vector(pag_p.pagina_principal);
        

        if (pag_p.pagina_principal.size() == PAGE_SIZE)
        {
            vector<struct PaginaRebalse> pags_r = pag_p.paginas_rebalse;
            for (int j = 0; j < pags_r.size(); j++)
            {
                struct PaginaRebalse pagina_rebalse = pags_r[j];
                cout << "Pag rebalse " << j << " (Pag. Princ. -> " << i << ")\n";
                print_vector(pagina_rebalse.pagina_rebalse);
            }
        }
    }
    return;
}

// Función aux: Imprime un HashingLineal completo
void print_hash(HashingLineal *lh)
{
    cout << "Hashing Lineal:\n";
    cout << "t: " << lh->t << "\n";
    cout << "p: " << lh->p << "\n";
    cout << "costo_actual: " << lh->costo_actual << "\n";
    cout << "cantidad de elementos insertados: " << lh->cant_elementos_insert << "\n";
    cout << "costo promedio real: " << ((lh -> costo_actual) / (lh ->cant_elementos_insert)) << "\n";
    print_paginas(lh->paginas_principales, lh->p);
    return;
}

// Funcion aux: Busca un elemento 'y' en un vector
bool buscar_val_vec(int y, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == y)
        {
            return true;
        }
    }
    return false;
}

// Función aux: Busca un elemento 'y' en un vector de paginas de rebalse
bool buscar_val_vec_pagina_r(struct HashingLineal *lh, int y, vector<struct PaginaRebalse> pr)
{
    for (int j = 0; j < pr.size(); j++)
    {
        lh->costo_actual++;
        vector<int> r = pr[j].pagina_rebalse;
        if (buscar_val_vec(y, r))
        {
            return true;
        }
    }
    return false;
}

// Función aux: Busca un elemento 'y' en una pagina principal
bool buscar_val_vec_pagina_p(struct HashingLineal *lh, int y, PaginaPrincipal pp)
{
    vector<struct PaginaRebalse> pr = pp.paginas_rebalse;
    vector<int> p = pp.pagina_principal;
    lh->costo_actual++;
    if (buscar_val_vec(y, p))
    {
        return true;
    }
    return buscar_val_vec_pagina_r(lh, y, pr); // Si no se encuentra en la pagina principal, 
                                           // se busca en las paginas de rebalse
}

// Función aux: Busca un elemento "y" en la lista de hashing "HashingLineal"
bool buscar_hash(int y, struct HashingLineal *lh, int k)
{
    vector<struct PaginaPrincipal> pag_principal = lh->paginas_principales;
    struct PaginaPrincipal pagk = pag_principal[k];
    // if(pagk.pagina_principal.size()<PAGE_SIZE){
    //     lh->costo_actual++;
    //     return buscar_val_vec(y, pagk.pagina_principal);
    // }
    
    return buscar_val_vec_pagina_p(lh,y, pagk);
}

// Función aux: Verifica si una página de rebalse tiene espacio para un nuevo elemento
bool pagina_rebalse_libre(vector<PaginaRebalse> p_r)
{
    if (p_r[p_r.size() - 1].pagina_rebalse.size() < PAGE_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Función aux: Crea un HashingLineal con t y p paginas
struct HashingLineal *crear_HashingLineal(int t, int p)
{
    int s= rand();
    struct HashingLineal *lh = new HashingLineal;
    lh->t = t;
    lh->p = p;
    lh->semilla_h=s;
    lh->costo_actual = 0;
    lh->cant_elementos_insert = 0;
    vector<struct PaginaPrincipal> pag_princ;
    for (int i = 0; i < p; i++)
    {
        struct PaginaPrincipal pag_i;
        pag_princ.push_back(pag_i);
    }
    lh->paginas_principales = pag_princ;
    return lh;
}
void borrar_pag(struct HashingLineal *lh,int k, int elem_elim)
{
    //cout<<"BORRAR_PAG\n";
    lh->costo_actual=0;
    int cnt_elem=lh->cant_elementos_insert;
    lh->cant_elementos_insert=cnt_elem-elem_elim;
    lh->paginas_principales[k].pagina_principal.erase(lh->paginas_principales[k].pagina_principal.begin() + 0, lh->paginas_principales[k].pagina_principal.begin() + lh->paginas_principales[k].pagina_principal.size());
    lh->paginas_principales[k].paginas_rebalse.erase(lh->paginas_principales[k].paginas_rebalse.begin() + 0, lh->paginas_principales[k].paginas_rebalse.begin() + lh->paginas_principales[k].paginas_rebalse.size());
    //cout<<"largo pagina "<<k<<"= "<<lh->paginas_principales[k].pagina_principal.size()<<" largo pag rebalse= "<<lh->paginas_principales[k].paginas_rebalse.size()<<"\n";

    return;
}
vector <int> extraer_para_insertar(struct HashingLineal *lh1,int k)
{
    vector<int> vector_elementos;
    vector<int> pagina_p_pag_k_lh1= lh1->paginas_principales[k].pagina_principal;
    vector<struct PaginaRebalse> paginas_r_pag_k_lh1=lh1->paginas_principales[k].paginas_rebalse;

    for(int j=0;j<paginas_r_pag_k_lh1.size();j++)
    {
        struct PaginaRebalse p_r=paginas_r_pag_k_lh1[j];
        for (int l=0;l<p_r.pagina_rebalse.size();l++)
        {
            vector_elementos.push_back(p_r.pagina_rebalse[l]);
        }

    }
    for (int i=0;i<pagina_p_pag_k_lh1.size();i++)
    {
        vector_elementos.push_back(pagina_p_pag_k_lh1[i]);
    }
    
    return vector_elementos;
}
//Función aux: Crea una nueva página principal
struct HashingLineal *crear_pagina_principal(struct HashingLineal *lh)
{
    //cout<<"Crear pag principal\n";
    struct PaginaPrincipal *nueva_principal = new PaginaPrincipal;
    lh->paginas_principales.push_back(*nueva_principal);
    lh->costo_actual++;
    lh->p++;
    return lh;
};

struct HashingLineal *Expancion_Hash(struct HashingLineal *lh, int k,vector<int> *elem)
{
    *elem= extraer_para_insertar(lh,k);
    borrar_pag(lh,k,elem->size());
    lh= crear_pagina_principal(lh);
    
    return lh;
}
// Función aux: Crea una nueva página de rebalse, inserta un elemento 'y',
// la agrega a la tabla de hashing e incrementa el costo actual
void crear_pagina_rebalse(struct HashingLineal *lh, int y, int k)
{
    //cout<<"crear_pagina_rebalse\n";
    struct PaginaRebalse *nueva_rebalse = new PaginaRebalse;
    nueva_rebalse->pagina_rebalse.push_back(y);
    lh->costo_actual++;
    lh->paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
    lh->costo_actual++;
    lh->cant_elementos_insert++;
    return;
}
// Inserta un elemento en la lista de hashing si este no se encuentra.
void insertar_hash(int y, struct HashingLineal *lh, int cmax)
{
    vector<struct PaginaPrincipal> pag_principal = lh->paginas_principales;
    vector<int>elem;

    int k = h(y,lh->semilla_h) % (long long)pow(2, lh->t + 1);

    // Buscar si el elemento "y" ya existe en la tabla de hashing
    if (k<lh->p)
    {
        if (buscar_hash(y, lh,k))
        {   
            lh->cant_elementos_insert++;
            // cout << "y ya existe\n";
            return;
        }

    }
    else
    {
        k=k-pow(2,lh->t);
        if (buscar_hash(y, lh,k))
        {   
            lh->cant_elementos_insert++;
            // cout << "y ya existe\n";
            return;
        }
    }
    
    //Si k < p, se inserta en la página k (o en una nueva si la actual rebalsa)
    //cout<<"Antes de verificar condicion de expancion\n";
    if ((lh->cant_elementos_insert >=1) and (((lh ->costo_actual) / (lh ->cant_elementos_insert)) >= cmax))
    {
        int costo_act=lh ->costo_actual;
        int cnt_elem=lh->cant_elementos_insert;
        lh=Expancion_Hash(lh,k,&elem);
        for(int i=0;i<elem.size();i++){
            insertar_hash(elem[i],lh,cmax);
        }
        if((lh ->p ) == (pow(2, lh->t+1)))
        {
            lh->t++;
        }
        lh->cant_elementos_insert=cnt_elem;
        int costo_n=lh->costo_actual;
        lh->costo_actual=costo_act-costo_n;
        insertar_hash(y,lh,cmax);
        return; 
    }
    
    else{
        //cout<<"Despues de verificar condicion de expancion\n";
        if (k < (lh->p))
        {
            vector<int> pagk = lh->paginas_principales[k].pagina_principal;


            // Cuando la página k se rebalsa, se crea una nueva página de rebalse
            if (pagk.size() == PAGE_SIZE)
            {
                //cout<<"Pagk llena\n";
                // Se verifica si la página k tiene asociada una página de rebalse
                if (lh->paginas_principales[k].paginas_rebalse.size() >= 1)
                {
                    int largo_pag_r = lh->paginas_principales[k].paginas_rebalse.size();

                    // Si tiene, se verifica que la página de rebalse tiene espacio y se inserta el elemento
                    if (pagina_rebalse_libre(lh->paginas_principales[k].paginas_rebalse))
                    {
                        lh->paginas_principales[k].paginas_rebalse[largo_pag_r - 1].pagina_rebalse.push_back(y);
                        lh->costo_actual++;
                        lh->cant_elementos_insert++;
                        return;
                    }

                    // Si la página de rebalse no tiene espacio, se crea una nueva página de rebalse
                    else
                    {
                        crear_pagina_rebalse(lh, y, k);
                        return;
                        
                    }
                }

                // Si la página 'k' no tiene, se crea una nueva página de rebalse
                else
                {
                    crear_pagina_rebalse(lh, y, k);
                    return;
                }
            }

            // Si la página 'k' aún tiene espacio, se inserta el elemento en la página k
            else
            {
                //cout<<"Hay espacio en pagk\n";
                lh->paginas_principales[k].pagina_principal.push_back(y);
                lh->costo_actual++;
                lh->cant_elementos_insert++;
                return;
            }
        }

        // Si k >= p, la página k aún no ha sido creada, por lo cual se debe insertar en la página k − 2^t.
        else
        {
            int posicion = k - pow(2,(lh->t));            
            struct PaginaPrincipal pag_k_2t = pag_principal[posicion];
            vector<int> pag_pag_k_2t = pag_k_2t.pagina_principal;
            int pos_i = posicion_vacia(pag_pag_k_2t);
            
            if (pos_i <= 127)
            {
                lh->paginas_principales[posicion].pagina_principal.push_back(y);
                lh->costo_actual++;
                lh->cant_elementos_insert++;
                return;
            }
            else
            {
                if (pag_k_2t.paginas_rebalse.size() > 1)
                {
                    int largo_pag_r = pag_k_2t.paginas_rebalse.size();
                    if (pagina_rebalse_libre(pag_k_2t.paginas_rebalse))
                    {
                        lh->paginas_principales[k].paginas_rebalse[largo_pag_r - 1].pagina_rebalse.push_back(y);
                        lh->costo_actual++;
                        lh->cant_elementos_insert++;
                        return;
                    }
                    else
                    {
                        crear_pagina_rebalse(lh, y, k);
                        return;
                    }
                }
                else
                {
                    crear_pagina_rebalse(lh, y, k);
                    return;
                }
            }
            return;
        }
    }    
}



// Función principal
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    string str_exponente = "Exponente: ";
    string str_creal = "C_Real: ";
    string str_cmax = "C_Controlado: ";
    string str_pllenado = "Porcentaje de llenado: ";

    int base = 2;
    int exponente = 10;
    int cmax = 6;
    int costo_prom_real = 0;
    double porcentaje_llenado_ultp = 0;
    double prom_porcentaje_llenado = 0;
    vector<double> porcentajes_llenado;

    do {
        cout << exponente<< endl;
        struct HashingLineal *lh = crear_HashingLineal(0, 1);
        prom_porcentaje_llenado = 0;
        porcentaje_llenado_ultp = 0;
        porcentajes_llenado = {};

        for (int i = 1; i < pow(base,exponente); i++)
        {
            insertar_hash(i, lh, cmax);
        }

        vector<struct PaginaPrincipal> p = lh->paginas_principales;
        int np = lh->p;

        for (int i = 0; i < np; i++) {
            struct PaginaPrincipal pag_pr = p[i];

            // Si tiene páginas de rebalse
            if (pag_pr.pagina_principal.size() == PAGE_SIZE) {
                vector<struct PaginaRebalse> pags_re = pag_pr.paginas_rebalse;

                for (int j = 0; j < pags_re.size(); j++) {
                    struct PaginaRebalse pagina_rebalse = pags_re[j];
                    porcentaje_llenado_ultp = porcentaje_llenado_pagina(pagina_rebalse.pagina_rebalse);
                }
            } else { // No tiene página de rebalse, nos quedamos con el % de la Página principal
                porcentaje_llenado_ultp = porcentaje_llenado_pagina(pag_pr.pagina_principal);
            }

            // Agregar a lista y calcular promedio
            porcentajes_llenado.push_back(porcentaje_llenado_ultp);
            porcentaje_llenado_ultp = 0;
        }

        porcentaje_llenado_ultp = 0;

        // Cálculo del promedio de porcenjaje de llenado
        for (int i = 0; i < porcentajes_llenado.size(); i++)
        {
            porcentaje_llenado_ultp += porcentajes_llenado[i];
        }

        prom_porcentaje_llenado = porcentaje_llenado_ultp / np;

        costo_prom_real = ((lh->costo_actual) / (lh->cant_elementos_insert));

        str_exponente += to_string(exponente) + ", ";
        str_creal += to_string(costo_prom_real) + ", ";
        str_cmax += to_string(cmax) + ", ";
        str_pllenado += to_string(prom_porcentaje_llenado) + "%, ";

        delete lh;
        exponente += 1;
    } while (exponente <= 21);

    str_exponente.erase(str_exponente.size() - 2);
    str_creal.erase(str_creal.size() - 2);
    str_cmax.erase(str_cmax.size() - 2);
    str_pllenado.erase(str_pllenado.size() - 2);

    cout << str_exponente << "\n"
         << str_creal << "\n"
         << str_cmax << "\n\n";

    cout << str_exponente << "\n"
         << str_pllenado << "\n"
         << str_creal << "\n";

    return 0;
}