#include <iostream>
#include <cstring>
#include <climits>
#include <string>

#define INFINITY INT_MAX

using namespace std;

void initArray(int *arr, int n, int val)
{
    for (int i = 0; i < n; i++)
        arr[i] = val;
}

int minDistance(bool *visited, int *dist, int n)
{
    int min = INFINITY;
    int u = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            u = i;
        }
    }
    return u;
}

void clearEdge(int **matrix, int parent, int v)
{
    matrix[parent][v] = -1;
    matrix[v][parent] = -1;
}

int dijkstra(int **matrix, int numVertex)
{
    bool *visited = new bool[numVertex];
    int *dist = new int[numVertex];
    int *parent = new int[numVertex];

    for (int i = 0; i < numVertex; i++)
        visited[i] = false;

    initArray(dist, numVertex, INFINITY);
    initArray(parent, numVertex, -1);

    visited[0] = 0;
    dist[0] = 0;

    int u = 0;

    for (int i = 0; i < numVertex; i++)
    {
        for (int v = 0; v < numVertex; v++)
        {
            if ((visited[v] != 1) && (matrix[u][v] != -1) && (v != u) && (dist[v] > dist[u] + matrix[u][v]))
            {
                dist[v] = dist[u] + matrix[u][v];
                parent[v] = u;
            }
        }
        visited[u] = true;
        u = minDistance(visited, dist, numVertex);
    }

    int i = numVertex - 1;
    int sum = dist[numVertex - 1];

    while (true)
    {
        if (parent[i] != -1)
        {
            clearEdge(matrix, parent[i], i);
            i = parent[i];
        }
        else if (i == 0)
            return sum;
        else
            return -1;
    }
}

void buildMatrix(int **matrix, int v1, int v2, int dist)
{
    matrix[v1 - 1][v2 - 1] = dist;
    matrix[v2 - 1][v1 - 1] = dist;
}

int main()
{
    int v, e;
    int inst = 1;
    while (cin >> v >> e)
    {
        int **matrix = new int *[v];
        for (int i = 0; i < v; i++)
        {
            matrix[i] = new int[v];
            memset(matrix[i], -1, v * sizeof(int));
        }

        for (int i = 0; i < e; i++)
        {
            int v1, v2, price;
            cin >> v1 >> v2 >> price;
            buildMatrix(matrix, v1, v2, price);
        }

        int numFriends, numSeats;
        cin >> numFriends >> numSeats;

        int finalPrice = 0;

        while (numFriends > 0)
        {
            if (numFriends > numSeats)
                finalPrice += (dijkstra(matrix, v) * numSeats);
            else
                finalPrice += (dijkstra(matrix, v) * numFriends);

            numFriends -= numSeats;
            if (finalPrice == -1)
                break;
        }

        cout << "Instancia " << inst << endl
             << endl;
        inst++;
        if (finalPrice == -1)
        {
            cout << "impossivel" << endl
                 << endl
                 << endl
                 << endl;
        }
        else
        {
            cout << finalPrice << endl
                 << endl
                 << endl
                 << endl;
        }
    }
    return 0;
}
