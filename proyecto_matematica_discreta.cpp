#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

typedef unsigned long long ull;

const ull LIMITE = numeric_limits<ull>::max();
const long long INF = numeric_limits<long long>::max() / 4;

string aTexto(int x) {
    ostringstream os;
    os << x;
    return os.str();
}

bool mulSegura(ull a, ull b, ull& res) {
    if (a != 0 && b > LIMITE / a) return false;
    res = a * b;
    return true;
}

ull mcd(ull a, ull b) {
    while (b != 0) { ull t = a % b; a = b; b = t; }
    return a;
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= minimo && valor <= maximo) return valor;
        if (cin.eof()) { cout << "\nFin de la entrada. Saliendo.\n"; exit(0); }
        cout << "  Entrada invalida. Ingrese un numero entre " << minimo
             << " y " << maximo << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int elegirModo() {
    cout << "\n  1. Resolver con mis propios datos\n"
         << "  2. Ver un ejemplo ya resuelto\n";
    return leerEntero("Opcion: ", 1, 2);
}



bool factorial(int n, ull& resultado) {
    resultado = 1;
    for (int i = 2; i <= n; i++) {
        if (!mulSegura(resultado, i, resultado)) return false;
    }
    return true;
}

bool permSinRep(int n, int r, ull& resultado) {
    resultado = 1;
    for (int i = 0; i < r; i++) {
        if (!mulSegura(resultado, n - i, resultado)) return false;
    }
    return true;
}


bool potencia(int n, int r, ull& resultado) {
    resultado = 1;
    for (int i = 0; i < r; i++) {
        if (!mulSegura(resultado, n, resultado)) return false;
    }
    return true;
}


bool binomial(int n, int k, ull& resultado) {
    if (k < 0 || k > n) { resultado = 0; return true; }
    if (k > n - k) k = n - k;
    resultado = 1;
    for (int i = 1; i <= k; i++) {
        ull g = mcd(resultado, i);
        ull a = resultado / g;
        ull d = i / g;
        ull factor = (n - k + i) / d;   
        if (!mulSegura(a, factor, resultado)) return false;
    }
    return true;
}

void avisoDesbordamiento() {
    cout << "\n  [!] El resultado es demasiado grande para representarse en 64 bits.\n"
         << "      Use valores mas pequenos.\n";
}


void permutacionesSinRepeticion() {
    cout << "\n--- PERMUTACIONES SIN REPETICION ---\n";
    cout << "Formula: P(n,r) = n! / (n-r)!\n\n";
    int n = leerEntero("Total de elementos (n): ", 0, 1000);
    int r = leerEntero("Elementos a ordenar (r), r <= n: ", 0, n);

    ull res;
    cout << "\nProcedimiento:\n  P(" << n << "," << r << ") = " << n << "! / ("
         << n << "-" << r << ")! = " << n << "! / " << (n - r) << "!\n";
    if (!permSinRep(n, r, res)) { avisoDesbordamiento(); return; }
    cout << "\nRESULTADO: " << res << " permutaciones\n";
}

void permutacionesConRepeticion() {
    cout << "\n--- PERMUTACIONES CON REPETICION ---\n";
    cout << "Elija el caso:\n"
         << "  1. Elementos que se repiten dentro del conjunto: n! / (n1! n2! ... nk!)\n"
         << "  2. Se pueden reutilizar los elementos al formar la ordenacion: n^r\n";
    int caso = leerEntero("Opcion: ", 1, 2);

    if (caso == 1) {
        int k = leerEntero("\nCuantos tipos distintos de elemento hay (k): ", 1, 50);
        vector<int> rep(k);
        int n = 0;
        for (int i = 0; i < k; i++) {
            rep[i] = leerEntero("  Veces que se repite el elemento " + aTexto(i + 1) + ": ", 1, 1000);
            n += rep[i];
        }
        cout << "\nProcedimiento:\n  n = " << n << "\n  P = " << n << "! / (";
        for (int i = 0; i < k; i++) cout << rep[i] << "!" << (i + 1 < k ? " * " : "");
        cout << ")\n";

        ull res = 1;
        int restante = n;
        bool ok = true;
        for (int i = 0; i < k && ok; i++) {
            ull c;
            if (!binomial(restante, rep[i], c)) { ok = false; break; }
            if (!mulSegura(res, c, res)) { ok = false; break; }
            restante -= rep[i];
        }
        if (!ok) { avisoDesbordamiento(); return; }
        cout << "\nRESULTADO: " << res << " permutaciones distintas\n";
    } else {
        int n = leerEntero("\nTipos de elementos disponibles (n): ", 1, 1000);
        int r = leerEntero("Posiciones a llenar (r): ", 0, 1000);
        cout << "\nProcedimiento:\n  n^r = " << n << "^" << r << "\n";
        ull res;
        if (!potencia(n, r, res)) { avisoDesbordamiento(); return; }
        cout << "\nRESULTADO: " << res << " ordenaciones\n";
    }
}



void ejemploPermSinRep() {
    int n = 5, r = 3;
    ull res;
    cout << "\n=== EJEMPLO: PERMUTACIONES SIN REPETICION ===\n"
         << "Problema: De 5 libros distintos, de cuantas formas se pueden\n"
         << "          ordenar 3 de ellos en un estante?\n\n"
         << "Datos: n = " << n << ", r = " << r << "\n"
         << "Formula: P(n,r) = n! / (n-r)!\n\n"
         << "Procedimiento:\n"
         << "  P(5,3) = 5! / (5-3)! = 5! / 2!\n"
         << "         = (5 * 4 * 3 * 2 * 1) / (2 * 1)\n"
         << "         = 5 * 4 * 3\n";
    permSinRep(n, r, res);
    cout << "\nRESULTADO: " << res << " permutaciones\n";
}

void ejemploPermConRep() {
    ull res;
    cout << "\n=== EJEMPLO: PERMUTACIONES CON REPETICION ===\n"
         << "\nCaso 1: elementos repetidos dentro del conjunto\n"
         << "Problema: Cuantas palabras (con o sin sentido) se pueden formar\n"
         << "          con todas las letras de la palabra MATEMATICA?\n\n"
         << "Letras: M se repite 2 veces, A 3 veces, T 2 veces,\n"
         << "        E 1 vez, I 1 vez, C 1 vez  ->  n = 10\n"
         << "Formula: P = n! / (n1! * n2! * ... * nk!)\n\n"
         << "Procedimiento:\n"
         << "  P = 10! / (2! * 3! * 2! * 1! * 1! * 1!)\n"
         << "    = 3628800 / (2 * 6 * 2)\n"
         << "    = 3628800 / 24\n";
    int rep[6] = {2, 3, 2, 1, 1, 1};
    res = 1;
    int restante = 10;
    for (int i = 0; i < 6; i++) {
        ull c;
        binomial(restante, rep[i], c);
        res *= c;
        restante -= rep[i];
    }
    cout << "\nRESULTADO: " << res << " permutaciones distintas\n";

    cout << "\n------------------------------------------\n"
         << "\nCaso 2: se pueden reutilizar los elementos (n^r)\n"
         << "Problema: Cuantos PIN de 4 digitos se pueden formar con\n"
         << "          los digitos del 0 al 9 (pueden repetirse)?\n\n"
         << "Datos: n = 10 digitos, r = 4 posiciones\n"
         << "Formula: n^r\n\n"
         << "Procedimiento:\n"
         << "  10^4 = 10 * 10 * 10 * 10\n";
    potencia(10, 4, res);
    cout << "\nRESULTADO: " << res << " ordenaciones\n";
}

void ejemploCombSinRep() {
    int n = 10, r = 3;
    ull res;
    cout << "\n=== EJEMPLO: COMBINACIONES SIN REPETICION ===\n"
         << "Problema: En un curso de 10 estudiantes se debe elegir un comite\n"
         << "          de 3 personas. De cuantas formas se puede hacer?\n\n"
         << "Datos: n = " << n << ", r = " << r << "\n"
         << "Formula: C(n,r) = n! / (r! * (n-r)!)\n\n"
         << "Procedimiento:\n"
         << "  C(10,3) = 10! / (3! * 7!)\n"
         << "          = (10 * 9 * 8) / (3 * 2 * 1)\n"
         << "          = 720 / 6\n";
    binomial(n, r, res);
    cout << "\nRESULTADO: " << res << " combinaciones\n";
}

void ejemploCombConRep() {
    int n = 4, r = 3;
    ull res;
    cout << "\n=== EJEMPLO: COMBINACIONES CON REPETICION ===\n"
         << "Problema: Una heladeria tiene 4 sabores. De cuantas formas se\n"
         << "          pueden elegir 3 bolas si los sabores pueden repetirse?\n\n"
         << "Datos: n = " << n << " sabores, r = " << r << " bolas\n"
         << "Formula: CR(n,r) = (n+r-1)! / (r! * (n-1)!)\n\n"
         << "Procedimiento:\n"
         << "  CR(4,3) = (4+3-1)! / (3! * 3!) = 6! / (3! * 3!)\n"
         << "          = 720 / (6 * 6)\n"
         << "          = C(6,3)\n";
    binomial(n + r - 1, r, res);
    cout << "\nRESULTADO: " << res << " combinaciones\n";
}

void menuPermutaciones() {
    int op;
    do {
        cout << "\n===== PERMUTACIONES =====\n"
             << "1. Sin repeticion\n"
             << "2. Con repeticion\n"
             << "0. Volver\n";
        op = leerEntero("Opcion: ", 0, 2);
        if (op == 1) { if (elegirModo() == 1) permutacionesSinRepeticion(); else ejemploPermSinRep(); pausa(); }
        else if (op == 2) { if (elegirModo() == 1) permutacionesConRepeticion(); else ejemploPermConRep(); pausa(); }
    } while (op != 0);
}


void combinacionesSinRepeticion() {
    cout << "\n--- COMBINACIONES SIN REPETICION ---\n";
    cout << "Formula: C(n,r) = n! / (r! (n-r)!)\n\n";
    int n = leerEntero("Total de elementos (n): ", 0, 1000);
    int r = leerEntero("Elementos a elegir (r), r <= n: ", 0, n);

    cout << "\nProcedimiento:\n  C(" << n << "," << r << ") = " << n << "! / ("
         << r << "! * " << (n - r) << "!)\n";
    ull res;
    if (!binomial(n, r, res)) { avisoDesbordamiento(); return; }
    cout << "\nRESULTADO: " << res << " combinaciones\n";
}

void combinacionesConRepeticion() {
    cout << "\n--- COMBINACIONES CON REPETICION ---\n";
    cout << "Formula: CR(n,r) = (n+r-1)! / (r! (n-1)!)\n\n";
    int n = leerEntero("Tipos de elementos disponibles (n): ", 1, 1000);
    int r = leerEntero("Elementos a elegir (r): ", 0, 1000);

    cout << "\nProcedimiento:\n  CR(" << n << "," << r << ") = C(" << (n + r - 1)
         << "," << r << ") = " << (n + r - 1) << "! / (" << r << "! * "
         << (n - 1) << "!)\n";
    ull res;
    if (!binomial(n + r - 1, r, res)) { avisoDesbordamiento(); return; }
    cout << "\nRESULTADO: " << res << " combinaciones\n";
}

void menuCombinaciones() {
    int op;
    do {
        cout << "\n===== COMBINACIONES =====\n"
             << "1. Sin repeticion\n"
             << "2. Con repeticion\n"
             << "0. Volver\n";
        op = leerEntero("Opcion: ", 0, 2);
        if (op == 1) { if (elegirModo() == 1) combinacionesSinRepeticion(); else ejemploCombSinRep(); pausa(); }
        else if (op == 2) { if (elegirModo() == 1) combinacionesConRepeticion(); else ejemploCombConRep(); pausa(); }
    } while (op != 0);
}


struct Grafo {
    int n;
    bool dirigido;
    Grafo() : n(0), dirigido(false) {}
    vector<vector<long long> > peso;   // matriz de pesos (INF = no hay arista)
};

Grafo leerGrafo() {
    Grafo g;
    g.n = leerEntero("Numero de vertices (2-15): ", 2, 15);
    int tipo = leerEntero("Tipo de grafo (1 = no dirigido, 2 = dirigido): ", 1, 2);
    g.dirigido = (tipo == 2);
    g.peso.assign(g.n, vector<long long>(g.n, INF));

    int maxAristas = g.dirigido ? g.n * (g.n - 1) : g.n * (g.n - 1) / 2;
    int m = leerEntero("Numero de aristas (0-" + aTexto(maxAristas) + "): ", 0, maxAristas);

    cout << "\nVertices numerados del 1 al " << g.n << ".\n";
    for (int i = 1; i <= m; i++) {
        cout << "Arista " << i << ":\n";
        int u, v;
        while (true) {
            u = leerEntero("  Origen: ", 1, g.n);
            v = leerEntero("  Destino: ", 1, g.n);
            if (u == v) { cout << "  No se permiten lazos. Intente de nuevo.\n"; continue; }
            if (g.peso[u - 1][v - 1] != INF) { cout << "  Esa arista ya existe. Intente de nuevo.\n"; continue; }
            break;
        }
        int w = leerEntero("  Peso (entero positivo): ", 1, 1000000);
        g.peso[u - 1][v - 1] = w;
        if (!g.dirigido) g.peso[v - 1][u - 1] = w;
    }
    return g;
}

void imprimirRuta(const vector<int>& ruta) {
    for (size_t i = 0; i < ruta.size(); i++)
        cout << ruta[i] + 1 << (i + 1 < ruta.size() ? " -> " : "");
    cout << "\n";
}



void dibujarGrafoTerminal(const Grafo& g, const vector<int>& ruta) {
    const int W = 61, H = 25;
    const double PI = 3.14159265358979;
    vector<string> lienzo(H, string(W, ' '));
    vector<int> px(g.n), py(g.n);
    for (int i = 0; i < g.n; i++) {
        double ang = 2 * PI * i / g.n - PI / 2;
        px[i] = (int)floor(30 + 26 * cos(ang) + 0.5);
        py[i] = (int)floor(12 + 10 * sin(ang) + 0.5);
    }

    vector<vector<bool> > enRuta(g.n, vector<bool>(g.n, false));
    for (size_t i = 0; i + 1 < ruta.size(); i++) {
        enRuta[ruta[i]][ruta[i + 1]] = true;
        enRuta[ruta[i + 1]][ruta[i]] = true;
    }

    for (int pasada = 0; pasada < 2; pasada++) {
        for (int u = 0; u < g.n; u++) {
            for (int v = u + 1; v < g.n; v++) {
                if (g.peso[u][v] == INF && g.peso[v][u] == INF) continue;
                bool roja = enRuta[u][v];
                if ((pasada == 1) != roja) continue;
                char ch = roja ? '#' : '.';
                int x0 = px[u], y0 = py[u], x1 = px[v], y1 = py[v];
                int dx = abs(x1 - x0), dy = abs(y1 - y0);
                int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
                int err = dx - dy;
                while (true) {
                    lienzo[y0][x0] = ch;
                    if (x0 == x1 && y0 == y1) break;
                    int e2 = 2 * err;
                    if (e2 > -dy) { err -= dy; x0 += sx; }
                    if (e2 < dx) { err += dx; y0 += sy; }
                }
            }
        }
    }

    for (int i = 0; i < g.n; i++) {
        string etiqueta = "(" + aTexto(i + 1) + ")";
        int inicio = px[i] - (int)etiqueta.size() / 2;
        if (inicio < 0) inicio = 0;
        if (inicio + (int)etiqueta.size() > W) inicio = W - (int)etiqueta.size();
        for (size_t k = 0; k < etiqueta.size(); k++) lienzo[py[i]][inicio + k] = etiqueta[k];
    }

    cout << "\n  GRAFICO DEL GRAFO\n  +" << string(W, '-') << "+\n";
    for (int r = 0; r < H; r++) cout << "  |" << lienzo[r] << "|\n";
    cout << "  +" << string(W, '-') << "+\n";
    cout << "  Leyenda:  ###  ruta resultado     ...  otras aristas\n";

    cout << "\n  Aristas (" << (g.dirigido ? "dirigido" : "no dirigido") << "): ";
    for (int u = 0; u < g.n; u++) {
        for (int v = 0; v < g.n; v++) {
            if (g.peso[u][v] == INF) continue;
            if (!g.dirigido && u > v) continue;
            cout << (u + 1) << (g.dirigido ? "->" : "-") << (v + 1) << "(" << g.peso[u][v] << ") ";
        }
    }
    cout << "\n\n  Recorrido: ";
    for (size_t i = 0; i < ruta.size(); i++) {
        cout << "[" << ruta[i] + 1 << "]";
        if (i + 1 < ruta.size())
            cout << " --" << g.peso[ruta[i]][ruta[i + 1]] << "--> ";
    }
    cout << "\n";
}


void rutaMasCorta(const Grafo& g, int origen, int destino) {
    vector<long long> dist(g.n, INF);
    vector<int> padre(g.n, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    dist[origen] = 0;
    pq.push(make_pair(0LL, origen));

    while (!pq.empty()) {
        pair<long long, int> top = pq.top(); pq.pop();
        long long d = top.first; int u = top.second;
        if (d > dist[u]) continue;
        for (int v = 0; v < g.n; v++) {
            if (g.peso[u][v] == INF) continue;
            if (dist[u] + g.peso[u][v] < dist[v]) {
                dist[v] = dist[u] + g.peso[u][v];
                padre[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[destino] == INF) {
        cout << "\nNo existe ninguna ruta entre " << origen + 1 << " y " << destino + 1 << ".\n";
        return;
    }
    vector<int> ruta;
    for (int v = destino; v != -1; v = padre[v]) ruta.push_back(v);
    reverse(ruta.begin(), ruta.end());
    cout << "\nRUTA MAS CORTA: ";
    imprimirRuta(ruta);
    cout << "PESO TOTAL: " << dist[destino] << "\n";
    dibujarGrafoTerminal(g, ruta);
}

void dfsLarga(const Grafo& g, int u, int destino, vector<bool>& visitado,
              vector<int>& actual, long long pesoActual,
              long long& mejorPeso, vector<int>& mejorRuta) {
    if (u == destino) {
        if (pesoActual > mejorPeso) { mejorPeso = pesoActual; mejorRuta = actual; }
        return;
    }
    for (int v = 0; v < g.n; v++) {
        if (g.peso[u][v] == INF || visitado[v]) continue;
        visitado[v] = true;
        actual.push_back(v);
        dfsLarga(g, v, destino, visitado, actual, pesoActual + g.peso[u][v], mejorPeso, mejorRuta);
        actual.pop_back();
        visitado[v] = false;
    }
}

void rutaMasLarga(const Grafo& g, int origen, int destino) {
    vector<bool> visitado(g.n, false);
    vector<int> actual, mejorRuta;
    long long mejorPeso = -1;
    visitado[origen] = true;
    actual.push_back(origen);
    dfsLarga(g, origen, destino, visitado, actual, 0, mejorPeso, mejorRuta);

    if (mejorPeso < 0) {
        cout << "\nNo existe ninguna ruta entre " << origen + 1 << " y " << destino + 1 << ".\n";
        return;
    }
    cout << "\nRUTA MAS LARGA (sin repetir vertices): ";
    imprimirRuta(mejorRuta);
    cout << "PESO TOTAL: " << mejorPeso << "\n";
    dibujarGrafoTerminal(g, mejorRuta);
}


void ejemploGrafo(bool corta) {
    Grafo g;
    g.n = 5;
    g.dirigido = false;
    g.peso.assign(g.n, vector<long long>(g.n, INF));
    int ar[7][3] = { {1,2,2}, {1,3,4}, {2,3,1}, {2,4,7}, {3,5,3}, {4,5,2}, {3,4,5} };
    for (int i = 0; i < 7; i++) {
        g.peso[ar[i][0] - 1][ar[i][1] - 1] = ar[i][2];
        g.peso[ar[i][1] - 1][ar[i][0] - 1] = ar[i][2];
    }

    cout << "\n=== EJEMPLO: " << (corta ? "RUTA MAS CORTA" : "RUTA MAS LARGA") << " ===\n"
         << "Problema: Un grafo NO dirigido con 5 vertices y 7 aristas.\n"
         << "          Encontrar la ruta " << (corta ? "mas corta" : "mas larga (sin repetir vertices)")
         << " del vertice 1 al vertice 5.\n\n"
         << "Aristas (origen - destino : peso):\n";
    for (int i = 0; i < 7; i++)
        cout << "  " << ar[i][0] << " - " << ar[i][1] << " : " << ar[i][2] << "\n";

    if (corta) cout << "\nMetodo: algoritmo de Dijkstra.\n";
    else cout << "\nMetodo: se revisan todos los caminos posibles de 1 a 5 sin repetir\n"
              << "vertices y se elige el de mayor peso total.\n";

    if (corta) rutaMasCorta(g, 0, 4);
    else rutaMasLarga(g, 0, 4);
}

void menuGrafos() {
    int op;
    do {
        cout << "\n===== GRAFOS =====\n"
             << "1. Ruta mas corta\n"
             << "2. Ruta mas larga\n"
             << "0. Volver\n";
        op = leerEntero("Opcion: ", 0, 2);
        if (op == 0) break;

        if (elegirModo() == 2) {
            ejemploGrafo(op == 1);
            pausa();
            continue;
        }

        cout << "\n";
        Grafo g = leerGrafo();
        int origen = leerEntero("\nVertice de origen: ", 1, g.n) - 1;
        int destino = leerEntero("Vertice de destino: ", 1, g.n) - 1;

        if (op == 1) rutaMasCorta(g, origen, destino);
        else rutaMasLarga(g, origen, destino);
        pausa();
    } while (op != 0);
}


void menuEjemplos() {
    int op;
    do {
        cout << "\n===== EJEMPLOS YA RESUELTOS =====\n"
             << "1. Permutaciones sin repeticion\n"
             << "2. Permutaciones con repeticion\n"
             << "3. Combinaciones sin repeticion\n"
             << "4. Combinaciones con repeticion\n"
             << "5. Grafos: ruta mas corta\n"
             << "6. Grafos: ruta mas larga\n"
             << "7. Ver TODOS los ejemplos seguidos\n"
             << "0. Volver\n";
        op = leerEntero("Opcion: ", 0, 7);
        switch (op) {
            case 1: ejemploPermSinRep(); pausa(); break;
            case 2: ejemploPermConRep(); pausa(); break;
            case 3: ejemploCombSinRep(); pausa(); break;
            case 4: ejemploCombConRep(); pausa(); break;
            case 5: ejemploGrafo(true); pausa(); break;
            case 6: ejemploGrafo(false); pausa(); break;
            case 7:
                ejemploPermSinRep();
                ejemploPermConRep();
                ejemploCombSinRep();
                ejemploCombConRep();
                ejemploGrafo(true);
                ejemploGrafo(false);
                pausa();
                break;
        }
    } while (op != 0);
}


int main() {
    int op;
    do {
        cout << "\n==========================================\n"
             << "   MATEMATICA DISCRETA - PROYECTO FINAL\n"
             << "==========================================\n"
             << "1. Permutaciones\n"
             << "2. Combinaciones\n"
             << "3. Grafos (ruta mas corta / mas larga)\n"
             << "4. Ejemplos ya resueltos\n"
             << "0. Salir\n";
        op = leerEntero("Seleccione una opcion: ", 0, 4);
        switch (op) {
            case 1: menuPermutaciones(); break;
            case 2: menuCombinaciones(); break;
            case 3: menuGrafos(); break;
            case 4: menuEjemplos(); break;
            case 0: cout << "\nHasta luego.\n"; break;
        }
    } while (op != 0);
    return 0;
}
