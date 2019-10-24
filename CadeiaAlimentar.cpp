#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

class Graph
{

private:
    int numVertices;
    int **matrix;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        this->matrix = new int *[numVertices];

        for (int i = 0; i < this->numVertices; i++)
            matrix[i] = new int[numVertices];

        for (int i = 0; i < this->numVertices; i++)
            memset(matrix[i], 0, this->numVertices * sizeof(int));
    }

    ~Graph()
    {
        for (int i = 0; i < numVertices; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    void buildMatrix(int v1, int v2)
    {
        matrix[v1 - 1][v2 - 1] = 1;
    }

    int minDistance(int dist[], bool sptSet[])
    {
        int min = INT_MAX, min_index;

        for (int v = 0; v < this->numVertices; v++)
        {
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v], min_index = v;
            }
        }
        return min_index;
    }

    void dijkstra(int u, int *dist)
    {
        bool sptSet[this->numVertices];

        for (int i = 0; i < this->numVertices; i++)
            dist[i] = INT_MAX, sptSet[i] = false;

        dist[u] = 0;

        for (int count = 0; count < this->numVertices - 1; count++)
        {
            u = minDistance(dist, sptSet);
            sptSet[u] = true;
            for (int v = 0; v < this->numVertices; v++)
                if (!sptSet[v] && matrix[u][v] && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
                    dist[v] = dist[u] + matrix[u][v];
        }
    }
};

int main()
{
    int numVertices;
    int numEdges;
    int v1;
    int v2;

    cin >> numVertices >> numEdges;

    Graph *graph = new Graph(numVertices);

    for (int i = 0; i < numEdges; i++)
    {
        cin >> v1 >> v2;
        graph->buildMatrix(v1, v2);
    }

    int *dist = new int[numVertices];
    memset(dist, 0, numVertices * sizeof(int));

    int *dist2 = new int[numVertices];
    memset(dist2, 0, numVertices * sizeof(int));

    graph->dijkstra(0, dist);

    for (int i = 0; i < numVertices; i++)
    {
        if (dist[i] == INT_MAX)
        {
            graph->dijkstra(i, dist2);

            if (dist2[0] == INT_MAX)
            {
                cout << "Nao Bolada" << endl;
                break;
            }
            else
            {
                cout << "Bolada" << endl;
                break;
            }
        }
        else if (i == numVertices - 1)
        {
            cout << "Bolada" << endl;
            break;
        }
    }
    delete dist;
    delete dist2;
    delete graph;

    return 0;
}
