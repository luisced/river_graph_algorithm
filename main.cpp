#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits> // Añade esta línea para definir INT_MAX

using namespace std;

const int MAX = 1e5;  // Ajusta esto al máximo tamaño de tu grafo
vector<int> adj[MAX]; // Listas de adyacencia
int parejas[MAX], distancia[MAX];

// BFS para encontrar la distancia de los caminos de aumento
bool bfs(int n)
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (parejas[i] == 0)
        {
            distancia[i] = 0;
            q.push(i);
        }
        else
        {
            distancia[i] = INT_MAX;
        }
    }
    distancia[0] = INT_MAX;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u != 0)
        {
            for (int v : adj[u])
            {
                if (distancia[parejas[v]] == INT_MAX)
                {
                    distancia[parejas[v]] = distancia[u] + 1;
                    q.push(parejas[v]);
                }
            }
        }
    }
    return distancia[0] != INT_MAX;
}

// DFS para encontrar y marcar los caminos de aumento
bool dfs(int u)
{
    if (u != 0)
    {
        for (int v : adj[u])
        {
            if (distancia[parejas[v]] == distancia[u] + 1 && dfs(parejas[v]))
            {
                parejas[v] = u;
                parejas[u] = v;
                return true;
            }
        }
        distancia[u] = INT_MAX;
        return false;
    }
    return true;
}

// Algoritmo de Hopcroft-Karp para emparejamiento máximo en grafos bipartitos
int hopcroftKarp(int n)
{
    memset(parejas, 0, sizeof(parejas));
    int emparejamiento = 0;
    while (bfs(n))
    {
        for (int i = 1; i <= n; ++i)
        {
            if (parejas[i] == 0 && dfs(i))
            {
                emparejamiento++;
            }
        }
    }
    return emparejamiento;
}

int main()
{
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 0; i < p; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v + n); // Asumimos que v+n es la representación del checkpoint en el lado derecho
    }

    cout << hopcroftKarp(n) << endl;

    return 0;
}
