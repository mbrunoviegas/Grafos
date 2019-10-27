#include <iostream>
#include <cstring>
#include <climits>
#include <string>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

void initArray(int *array, int tam, int val)
{
    for (int i = 0; i < tam; i++)
        array[i] = val;
}

void buildMatrix(int **matrix, int v1, int v2)
{
    matrix[v1 - 1][v2 - 1] = 1;
    matrix[v2 - 1][v1 - 1] = 1;
}

void visitaDfs(int **matrix, int *colors, int tam, int v)
{
    colors[v] = GRAY;

    for (int i = 0; i < tam; i++)
    {
        if (colors[i] == WHITE && matrix[v][i] == 1)
            visitaDfs(matrix, colors, tam, i);
    }
    colors[v] = BLACK;
}

int verifyComponents(int **matrix, int tam)
{
    int numComponentes = 0;
    int *colors = new int[tam];

    memset(colors, WHITE, tam * sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        if (colors[i] == WHITE)
        {
            visitaDfs(matrix, colors, tam, i);
            numComponentes++;
        }
    }

    return numComponentes;
}

bool includeEdge(int **matrix, int *colors, int tam, int numEdge)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (colors[i] != colors[j])
            {
                if (matrix[i][j] != 0)
                {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                    numEdge--;
                }
            }
        }

        if (numEdge > 0)
            return false;
        else
            return true;
    }
}

int main()
{
    int test = 0;
    cin >> test;

    for (int i = 0; i < test; i++)
    {
        int v, e, p, c;
        cin >> v >> e >> p >> c;

        int **matrix = new int *[v];
        for (int i = 0; i < v; i++)
        {
            matrix[i] = new int[v];
            memset(matrix[i], -1, v * sizeof(int));
        }

        int *colors = new int[v];
        initArray(colors, v, 0);

        for (int i = 0; i < v; i++)
            cin >> colors[i];

        int v1, v2;
        for (int i = 0; i < e; i++)
        {
            cin >> v1 >> v2;
            buildMatrix(matrix, v1, v2);
        }

        if (includeEdge(matrix, colors, v, p))
        {
            if ((verifyComponents(matrix, v)) > 1)
                cout << "N" << endl
                     << endl;
            else
                cout << "Y" << endl
                     << endl;
        }
    }

    return 0;
}