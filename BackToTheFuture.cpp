#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

class Graph
{

private:
    int numVertices;
    int **matrix;
    int *dist;
    int *sPath;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        this->matrix = new int *[numVertices];
        this->dist = new int[numVertices];
        this->sPath = new int[numVertices];

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
        delete[] this->sPath;
        delete[] this->dist;
    }

    void buildMatrix(int v1, int v2, int dist)
    {
        matrix[v1 - 1][v2 - 1] = dist;
        matrix[v2 - 1][v1 - 1] = dist;
    }

    int *getDist()
    {
        return this->dist;
    }

    int *getShortestPath()
    {
        return this->sPath;
    }

    void clearEdge(int i, int parent)
    {
        matrix[i][parent] = 0;
        matrix[parent][i] = 0;
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

    void dijkstra(int u)
    {

        memset(this->dist, INT_MAX, this->numVertices * sizeof(int));

        bool sptSet[this->numVertices];

        for (int i = 0; i < this->numVertices; i++)
            dist[i] = INT_MAX, sptSet[i], sPath[i] = -1;

        dist[u] = 0;
        int count = 0;
        while (count < this->numVertices - 1)
        {
            u = minDistance(dist, sptSet);
            sptSet[u] = true;
            for (int v = 0; v < this->numVertices; v++)
            {
                if (!sptSet[v] && matrix[u][v] && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
                {
                    sPath[v] = u;
                    dist[v] = dist[u] + matrix[u][v];
                }
            }

            count++;
        }
    }
};

int main()
{
    int numVertex; //each city is a vertex
    int numEdges;  //each route is a edge
    int v1;        //city 1
    int v2;        //city 2
    int price = 0;
    int numFriends = 0;
    int numSeats = 0;
    int k = 0;

    while (cin >> numVertex)
    {
        cin >> numEdges;

        Graph *graph = new Graph(numVertex);

        for (int i = 0; i < numEdges; i++)
        {
            cin >> v1 >> v2 >> price;
            graph->buildMatrix(v1, v2, price);
        }

        cin >> numFriends >> numSeats;

        cout << "Instancia " << k + 1 << endl
             << endl;

        if (numSeats * numEdges < numFriends)
        {
            cout << "impossivel" << endl
                 << endl;
        }
        else
        {
            int finalPrice = 0;
            graph->dijkstra(0);

            int *path = new int[numVertex];
            int *prices = new int[numVertex];

            for (int u = 0; u < numVertex - 1; u++)
                path[u] = 0;

            for (int u = 0; u < numVertex - 1; u++)
                prices[u] = 0;

            prices = graph->getDist();
            path = graph->getShortestPath();

            int aux = numFriends;
            numFriends -= numSeats;

            if (numFriends > 0)
            {
                finalPrice += (prices[numVertex - 1] * (aux - numSeats));
            }
            else
            {
                finalPrice += (prices[numVertex - 1] * aux);
            }

            if (path[numVertex - 1] != -1)
            {
                while (numFriends > 0)
                {
                    if (numFriends >= numSeats)
                    {
                        int i = numVertex - 1;
                        while (i != -1)
                        {
                            if (path[i] != -1)
                            {
                                graph->clearEdge(i, path[i]);
                                i = path[i];
                            }
                            else if (i == 0)
                            {
                                i = -1;
                            }
                            else
                            {
                                i--;
                            }
                        }
                        graph->dijkstra(0);
                        prices = graph->getDist();
                        finalPrice += prices[numVertex - 1] * numSeats;
                    }
                    else
                    {
                        prices = graph->getDist();
                        finalPrice += prices[numVertex - 1] * numFriends;
                        break;
                    }
                    numFriends -= numSeats;
                }

                cout << finalPrice << endl
                     << endl
                     << endl
                     << endl;
            }
            else
            {
                cout << "impossivel" << endl
                     << endl;
            }
        }

        delete graph;
        k++;
    }

    return 0;
}