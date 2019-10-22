#include <iostream>
#include <vector>
#include <cstring>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

using namespace std;

class Grafos
{
private:
    int **matriz;
    int numVertices;
    int *cor;
    int *corComponente;
    int numComponentes;

public:
    Grafos(int numVertices)
    {
        this->numVertices = numVertices;
        this->numComponentes = 0;

        this->corComponente = new int[numVertices];
        this->cor = new int[numVertices];

        this->matriz = new int *[numVertices];
        for (int i = 0; i < numVertices; i++)
            this->matriz[i] = new int[numVertices];

        for (int i = 0; i < this->numVertices; i++)
            memset(matriz[i], 0, numVertices * sizeof(int));
    }
    ~Grafos()
    {
        for (int i = 0; i < numVertices; i++)
            delete[] matriz[i];
        delete[] matriz;
    }

    void insereAresta(char v1, char v2)
    {
        this->matriz[v1 - 97][v2 - 97] = 1;
        this->matriz[v2 - 97][v1 - 97] = 1;
    }
    void visitaDfs(int v)
    {
        this->cor[v] = CINZA;

        for (int i = 0; i < this->numVertices; i++)
        {
            if (this->cor[i] == BRANCO && this->matriz[v][i] == 1)
                this->visitaDfs(i);
        }
        this->cor[v] = PRETO;
        this->corComponente[v] = PRETO;
    }

    void verificaComponentes()
    {
        int numComponentes;

        memset(cor, BRANCO, numVertices * sizeof(int));
        memset(corComponente, BRANCO, numVertices * sizeof(int));

        for (int i = 0; i < this->numVertices; i++)
        {
            if (this->cor[i] == BRANCO)
            {
                this->visitaDfs(i);

                for (int j = 0; j < numVertices; j++){
                    if(corComponente[j] == PRETO)
                        cout << (char)(j + 97) << ",";
                }

                memset(corComponente, BRANCO, numVertices * sizeof(int));
                cout << endl;
                this->numComponentes++;
            }
        }

        cout << this->numComponentes << " connected components" << endl;
        cout << endl;
    }

    void printMatrix()
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
                cout << matriz[i][j] << ' ';
            cout << endl;
        }
    }
};

int main()
{
    int numTestes = 0;
    int numVertices = 0;
    int numArestas = 0;
    char v1, v2;
    Grafos *grafo;
    cin >> numTestes;

    for (int i = 0; i < numTestes; i++)
    {
        cin >> numVertices >> numArestas;

        grafo = new Grafos(numVertices);

        for (int j = 0; j < numArestas; j++)
        {
            cin >> v1 >> v2;
            grafo->insereAresta(v1, v2);
        }

        //grafo->printMatrix();

        cout << "Case #" << (i + 1) << ":" << endl;
        grafo->verificaComponentes();

        delete grafo;
    }

    return 0;
}