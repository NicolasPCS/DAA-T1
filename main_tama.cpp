#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

using namespace std;

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
    int costo_actual;
    int cant_elementos_insert;
    vector<struct PaginaPrincipal> paginas_principales;
};

//-- Implementación de funciones --//

// Función de hashing h(y)
// Devuelve un valor aleatorio entre 0 y 264 − 1 para cualquier elemento 'y'
long long h(int y)
{
    double d = pow(2, 64);
    srand(y);
    long long hash = fmod(rand(), d);
    return hash;
}

// double porcentaje_llenado(vector<struct Pagina> paginas){
//     return
// }

// Función aux: Encuentra la ultima posicion vacía de un vector de int
int posicion_vacia(vector<int> v)
{
    for (int i = 0; i < 1023; i++)
    {
        if (v[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

// Función aux: Entrega la ultima posicion vacia de la pagina de rebalse i
/* vector<int> pag_r_y_posicion(vector<struct PaginaRebalse> v_pagR)
{
    vector<int> v = {-1, -1};
    for (int i = 0; i < v_pagR.size(); i++) // Tamaño de la lista de la página de rebalse 'v_pagR'
    {
        struct PaginaRebalse v_pagR_i = v_pagR[i]; // Se obtiene la posición i de la página de rebalse
        int pos = posicion_vacia(v_pagR_i.pagina_rebalse);
        if (pos != -1)
        {
            v[0] = i;
            v[1] = pos;
            return v;
        }
    }
    return v;
} */

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

// Función aux: Imprime un vector de páginas pricipales y sus páginas de rebalse
void print_paginas(vector<struct PaginaPrincipal> p, int np)
{
    for (int i = 0; i < np; i++)
    {
        struct PaginaPrincipal pag_p = p[i];
        cout << "Pag. principal -> " << i << "\n";
        print_vector(pag_p.pagina_principal);
        

        if (pag_p.pagina_principal.size() == 128)
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
    // cout << "Hashing Lineal:\n";
    // cout << "t: " << lh->t << "\n";
    // cout << "p: " << lh->p << "\n";
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
    if (buscar_val_vec(y, p))
    {
        return true;
    }
    return buscar_val_vec_pagina_r(lh, y, pr); // Si no se encuentra en la pagina principal, 
                                           // se busca en las paginas de rebalse
}

// Función aux: Busca un elemento "y" en la lista de hashing "HashingLineal"
bool buscar_hash(int y, struct HashingLineal *lh)
{
    vector<struct PaginaPrincipal> pag_principal = lh->paginas_principales;
    

    if (pag_principal.size() < 1)
    {
        return false;
    }
    for (int i = 0; i < pag_principal.size(); i++)
    {
        PaginaPrincipal pagk = pag_principal[i];
        // cout << "dentro del for\n";
        lh->costo_actual++;
        
        if (buscar_val_vec_pagina_p(lh,y, pagk))
        {
            return true;
        }
    }
    return false;
}

// Función aux: Verifica si una página de rebalse tiene espacio para un nuevo elemento
bool pagina_rebalse_libre(vector<PaginaRebalse> p_r)
{
    if (p_r[p_r.size() - 1].pagina_rebalse.size() < 128)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Función aux: Crea una nueva página de rebalse, inserta un elemento 'y',
// la agrega a la tabla de hashing e incrementa el costo actual
void crear_pagina_rebalse(struct HashingLineal *lh, int y, int k)
{
    struct PaginaRebalse *nueva_rebalse = new PaginaRebalse;
    nueva_rebalse->pagina_rebalse.push_back(y);
    lh->paginas_principales[k].paginas_rebalse.push_back(*nueva_rebalse);
    lh->costo_actual++;
    lh->cant_elementos_insert++;
    return;
}

//Función aux: Crea una nueva página principal
void crear_pagina_principal(struct HashingLineal *lh)
{
    struct PaginaPrincipal *nueva_principal = new PaginaPrincipal;
    lh -> paginas_principales.push_back(*nueva_principal);
    lh -> p++;
    return;
};

// Inserta un elemento en la lista de hashing si este no se encuentra.
void insertar_hash(int y, struct HashingLineal *lh, int cmax)
{
    vector<struct PaginaPrincipal> pag_principal = lh->paginas_principales;

    // Buscar si el elemento "y" ya existe en la tabla de hashing
    if (buscar_hash(y, lh))
    {   
        lh->cant_elementos_insert++;
        // cout << "y ya existe\n";
        return;
    }

    if ((lh->cant_elementos_insert >=1) and (((lh ->costo_actual) / (lh ->cant_elementos_insert)) >= cmax)) 
    {
        crear_pagina_principal(lh);
        lh -> costo_actual = 0;
        lh -> t++;
        cout << "antes de insertar en expansien" << "\n";
        insertar_hash(y, lh, cmax);
        cout << "cantd paginas principales " << lh -> paginas_principales.size() <<"\n";
        cout << "despues de insertar en expansion, " << y <<"\n";
        if((lh ->p ) == (pow(2, lh->t)))
        {
            cout << "Hola, " << lh->p <<"\n";
            return;
        }
        else
        {
            lh -> p--;
            return;
        }
    }
    
    else
    {
        int k;

        // Si el elemento "y" no se encuentra, se busca donde insertarlo
        // Si el tamaño principal es menor que 2, se asigna el índice 'k' como 0
        if (pag_principal.size() < 2)
        {
            k = 0;
        }

        // Caso contrario, se calcula 'k' como el hash del valor 'y' módulo 2^(t+1)
        else
        {
            cout << "valor de h(y)" << h(y) << "\n";
            k = h(y) % (long long)pow(2, lh->t + 1);
        }

        
        // Si k < p, se inserta en la página k (o en una nueva si la actual rebalsa)
        if (k < (lh->p))
        {
            vector<int> pagk = pag_principal[k].pagina_principal;


            // Cuando la página k se rebalsa, se crea una nueva página de rebalse
            if (pagk.size() == 128)
            {
                // Se verifica si la página k tiene asociada una página de rebalse
                if (pag_principal[k].paginas_rebalse.size() >= 1)
                {
                    int largo_pag_r = pag_principal[k].paginas_rebalse.size();

                    // Si tiene, se verifica que la página de rebalse tiene espacio y se inserta el elemento
                    if (pagina_rebalse_libre(pag_principal[k].paginas_rebalse))
                    {
                        lh->paginas_principales[k].paginas_rebalse[largo_pag_r - 1].pagina_rebalse.push_back(y);
                        lh->cant_elementos_insert++;
                        return;
                    }

                    // Si la página de rebalse no tiene espacio, se crea una nueva página de rebalse
                    else
                    {
                        crear_pagina_rebalse(lh, y, k);
                    }
                }

                // Si la página 'k' no tiene, se crea una nueva página de rebalse
                else
                {
                    crear_pagina_rebalse(lh, y, k);
                }
            }

            // Si la página 'k' aún tiene espacio, se inserta el elemento en la página k
            else
            {
                lh->paginas_principales[k].pagina_principal.push_back(y);
                lh->cant_elementos_insert++;
                return;
            }
        }

        // Si k >= p, la página k aún no ha sido creada, por lo cual se debe insertar en la página k − 2^t.
        else
        {
            int posicion = k - 2 * (lh->t);
            if (posicion < 0)
            {
                // cout << "posicion <0\n";
                struct PaginaPrincipal pag_0 = pag_principal[0];
                // cout << "primera pag pric\n";
                vector<int> pag_pag_0 = pag_0.pagina_principal;
                int pos_i = posicion_vacia(pag_pag_0);
                if (pos_i <= 128)
                {
                    lh->paginas_principales[0].pagina_principal.push_back(y);
                    lh->cant_elementos_insert++;
                    return;
                }
                else
                {
                    if (pag_0.paginas_rebalse.size() > 1)
                    {
                        int largo_pag_r = pag_0.paginas_rebalse.size();
                        if (pagina_rebalse_libre(pag_0.paginas_rebalse))
                        {
                            lh->paginas_principales[k].paginas_rebalse[largo_pag_r - 1].pagina_rebalse.push_back(y);
                            lh->cant_elementos_insert++;
                            return;
                        }
                        else
                        {
                            crear_pagina_rebalse(lh, y, k);
                        }
                    }
                    else
                    {
                        crear_pagina_rebalse(lh, y, k);
                    }
                }
            }
            
            struct PaginaPrincipal pag_k_2t = pag_principal[posicion];
            vector<int> pag_pag_k_2t = pag_k_2t.pagina_principal;
            int pos_i = posicion_vacia(pag_pag_k_2t);
            
            if (pos_i <= 127)
            {
                lh->paginas_principales[posicion].pagina_principal.push_back(y);
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
                        lh->cant_elementos_insert++;
                        return;
                    }
                    else
                    {
                        crear_pagina_rebalse(lh, y, k);
                    }
                }
                else
                {
                    crear_pagina_rebalse(lh, y, k);
                }
            }
            return;
        }
    }
}

// Función aux: Crea un HashingLineal con t y p paginas
struct HashingLineal *crear_HashingLineal(int t, int p)
{
    struct HashingLineal *lh = new HashingLineal;
    lh->t = t;
    lh->p = p;
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

// Función principal
int main()
{
    struct HashingLineal *lh = crear_HashingLineal(0, 1);
    for (int i = 1; i < pow(2,10); i++)
    {
        insertar_hash(i, lh, 2000);
        insertar_hash(i, lh, 2000);
    }
    for (int i = 1; i < 10; i++)
    {
        long long hash = h(i);
        cout << "valor de hashing: " << hash << "\n";
    }
    cout << "Nuevo hashing: " << "\n";
    for (int i = 1; i < 10; i++)
    {
        long long hash = h(i);
        cout << "valor de hashing: " << hash << "\n";
    }
    print_hash(lh);
    return 0;
}