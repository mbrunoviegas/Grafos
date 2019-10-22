#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>

using namespace std;

double twoPointsDistance(int i, int j, double *latitude, double *longitude)
{
    double distance = sqrt(pow((latitude[i] - latitude[j]), 2.0) + pow((longitude[i] - longitude[j]), 2.0));
    return distance;
}

int posMin(double *key, int numVertices)
{
    double min = 999999999;
    int pos = 0;
    for (int i = 0; i < numVertices; i++)
    {
        if (key[i] < min && key[i] != -1)
        {
            min = key[i];
            pos = i;
        }
    }
    return pos;
}

void prim(double **matrix, int numVertices, double *key)
{
    for (int i = 0; i < numVertices; i++)
        key[i] = 99999999.99;
    key[0] = -1;
    int count = numVertices;
    int u = 0;
    double distance = 0.0;
    while (count >= 0)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (matrix[u][i] < key[i] && u != i && key[i] != -1)
            {
                key[i] = matrix[u][i];
            }
        }
        u = posMin(key, numVertices);
        distance += key[u];
        key[u] = -1;
        count--;
    }
    distance /= 100.0;
    distance += 0.02;
    cout << fixed << setprecision(2) << distance << endl;
}

void printMatrix(double **matrix, int numVertices)
{
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
            cout << setprecision(2) << fixed << matrix[i][j] << ' ';
        cout << endl;
    }
}

void buildMatrix(double **matrix, int numVertices, double *latitude, double *longitude)
{
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            matrix[i][j] = twoPointsDistance(i, j, latitude, longitude);
        }
    }
}

int main()
{
    int numTest;
    int numVertices;
    double **matrix;
    double *key;
    double *latitude;
    double *longitude;

    cin >> numTest;

    for (int i = 0; i < numTest; i++)
    {
        cin >> numVertices;

        matrix = new double *[numVertices];
        for (int i = 0; i < numVertices; i++)
            matrix[i] = new double[numVertices];

        for (int i = 0; i < numVertices; i++)
            memset(matrix[i], 0.0, numVertices * sizeof(int));

        latitude = new double[numVertices];
        longitude = new double[numVertices];
        key = new double[numVertices];

        memset(latitude, 0.0, numVertices * sizeof(int));
        memset(longitude, 0.0, numVertices * sizeof(int));
        memset(key, 0.0, numVertices * sizeof(int));

        for (int j = 0; j < numVertices; j++)
        {
            cin >> latitude[j];
            cin >> longitude[j];
        }

        buildMatrix(matrix, numVertices, latitude, longitude);
        //   printMatrix(matrix, numVertices);
        prim(matrix, numVertices, key);
        cout << endl;
        
        for (int i = 0; i < numVertices; i++)
            delete matrix[i];
        delete[] matrix;
        delete[] latitude;
        delete[] longitude;
        delete[] key;
    }
    return 0;
}