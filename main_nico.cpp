#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

// Tamaño máximo de un página en disco -> 1024 byes
// Un entero del tipo del tipo long long ocupa -> 8 bytes (64 bits) en disco
const int PAGE_SIZE = 1024 / sizeof(long long);

// Estructura que representa una página -> Lista de elementos
struct Page {
    list <long long> elements;
    list <long long> overflow;
};

// Función de hash simple
// Genera un valor entre 0 y 2^64 - 1
long long hashFunction(long long y) {
    const long long prime = 11400714819323198485ull;  // Número primo grande
    return (y * prime) ^ (y >> 33);
}

// Clase Hashing Lineal
class LinearHashing {
    vector<Page> hashTable; // Tabla de páginas
    int t;                  // Define el tamaño del hash (2^t)
    int p;                  // Número de páginas actuales
    int pageSize;           // Tamaño máximo de la página

public:
    LinearHashing(int initialPageSize) : pageSize(initialPageSize) {
        t = 0;
        p = 1;
        hashTable.resize(p);
    }

    // Inserta un elemento 'y' en la tabla hash
    void insert(long long y) {
        // (1 << (t + 1)) -> Significa que desplazamos el bit 1 't + 1' veces a la izquierda
        long long k = hashFunction(y) % (1 << (t + 1));
        if (k < p) {
            // Si la página k existe, insertamos el elemento
            insertInPage(k, y);
        } else {
            // Si la página aún no existe, la creamos
            insertInPage(k - (1 << t), y);
        }

        // Revisamos si se necesita expansión, si es así se expande
        if (needsExpansion()) {
            expand();
        }
    }

    // Inserta un elemento en una página
    void insertInPage(int pageIndex, long long y) {
        // Recorremos toda la lista para verificar si el elemento ya existe
        for (long long element : hashTable[pageIndex].elements) {
            if (element == y) {
                // Si encontramos el elemento, no lo insetamos
                cout << "Elemento " << y << " ya existe en la página " << pageIndex << endl;
                return;
            }
        }

        // Verificamos también en la lista de rebalse
        for (long long element : hashTable[pageIndex].overflow) {
            if (element == y) {
                // Si encontramos el elemento, no lo insetamos
                cout << "Elemento " << y << " ya existe en la lista de rebalse de la página " << pageIndex << endl;
                return;
            }
        }

        // Si el elemento no está, lo insertamos en la página
        if (hashTable[pageIndex].elements.size() < PAGE_SIZE) {
            hashTable[pageIndex].elements.push_back(y);
        } else {
            // Si la página está llena, lo insertamos en la lista de rebalse
            hashTable[pageIndex].overflow.push_back(y);
        }
    }

    // Verifica si es necesario expandir la tabla hash
    bool needsExpansion() {
        return (p >= (1 << t));
    }

    // Expande la tabla hash
    void expand() {
        cout << "Expandiendo la tabla hash..." << endl;
        // Añadimos una nueva página y redistribuimos los elementos
        hashTable.push_back(Page());

        int oldPageIndex = p - (1 << t);

        if (oldPageIndex < hashTable.size() && p < hashTable.size()) {
            redistribute(oldPageIndex, p);
        } else {
            cout << "Error: Índices fuera de los límites durante la expansión." << endl;
            return;
        }

        p++;

        if (p > (1 << (t + 1))) {
            cout << "Error: Expansión incorrecta. P: " << p << ", t: " << t << endl;
            return;
        }

        if (p == (1 << (t + 1))) {
            t++; // Incrementamos el exponente t cuando p = 2^(t+1)
        }
    }

    // Redistribuye los elementos entre dos páginas
    void redistribute(int oldPageIndex, int newPageIndex) {
        if (oldPageIndex >= hashTable.size()) {
            cout << "Error: El índice de la página vieja está fuera de los límites." << endl;
            return;
        }

        if (newPageIndex >= hashTable.size()) {
            cout << "Error: El índice de la nueva página está fuera de los límites." << endl;
            return;
        }

        list<long long> temp;
        // Recorremos la página y redistribuimos los elementos en base al nuevo valor hash.
        for (long long y : hashTable[oldPageIndex].elements) {
            long long k = hashFunction(y) % (1 << (t + 1));
            if (k == newPageIndex) {
                hashTable[newPageIndex].elements.push_back(y);
            } else {
                temp.push_back(y);
            }
        }
        hashTable[oldPageIndex].elements = temp;

        // También redistribuimos los elementos de la lista de rebalse
        list<long long> tempOverflow;
        for (long long y : hashTable[oldPageIndex].overflow) {
            long long k = hashFunction(y) % (1 << (t + 1));
            if (k == newPageIndex) {
                hashTable[newPageIndex].elements.push_back(y);
            } else {
                tempOverflow.push_back(y);
            }
        }
        hashTable[oldPageIndex].overflow = tempOverflow;
    }

    // Imprimir tabla hash
    void printHashTable() {
        for (int i = 0; i < p; i++) {
            cout << "Página " << i << ": ";
            for (long long y : hashTable[i].elements) {
                cout << y << " ";
            }
            cout << endl;

            if (!hashTable[i].overflow.empty()) {
                cout << "  Lista de rebalse: ";
                for (long long y : hashTable[i].overflow) {
                    cout << y << " ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    // Inicializamos la semilla para la función rand()
    srand(time(0));

    int N = 100; // Número de elementos a insertar
    LinearHashing hashTable(PAGE_SIZE);

    // Insertamos N elementos en la tabla hash
    for (int i = 0; i < N; i++) {
        long long y = rand() % 1000000; // Generamos un número aleatorio de 64 bits
        cout << "Insertando " << y << endl;
        hashTable.insert(y);
    }

    // Imprimimos la tabla hash
    hashTable.printHashTable();

    return 0;
}