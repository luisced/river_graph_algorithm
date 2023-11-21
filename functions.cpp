#include "classes/queue/queue.h"
#include "classes/double_linked_list/list.h"
#include <iostream>
#include <climits>
#include <cstring>

const int MAX = 1e5; // Ajusta esto al máximo tamaño de tu grafo
LinkedList<int> adj[MAX];
int parejas[MAX], distancia[MAX];

// BFS para encontrar la distancia de los caminos de aumento
bool bfs(int n)
{
    Queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (parejas[i] == 0)
        {
            distancia[i] = 0;
            q.enqueue(i);
        }
        else
            distancia[i] = INT_MAX;
    }
    distancia[0] = INT_MAX;

    while (!q.isEmpty())
    {
        int u = q.dequeue();
        if (u != 0)
        {
            Node<int> *node = adj[u].getHead(); // Get the head of the linked list
            while (node != nullptr)
            {
                int v = node->data;
                if (distancia[parejas[v]] == INT_MAX)
                {
                    distancia[parejas[v]] = distancia[u] + 1;
                    q.enqueue(parejas[v]);
                }
                node = node->next; // Move to the next node in the list
            }
        }
    }
    return distancia[0] != INT_MAX;
}

// DFS to find and mark augmenting paths
bool dfs(int u)
{
    if (u != 0)
    {
        Node<int> *node = adj[u].getHead(); // Get the head of the linked list
        while (node != nullptr)
        {
            int v = node->data;
            if (distancia[parejas[v]] == distancia[u] + 1 && dfs(parejas[v]))
            {
                parejas[v] = u;
                parejas[u] = v;
                return true;
            }
            node = node->next; // Move to the next node in the list
        }
        distancia[u] = INT_MAX;
        return false;
    }
    return true;
}

int min_guards(int n)
{
    memset(parejas, 0, sizeof(parejas));
    int emparejamiento = 0;
    while (bfs(n))
        for (int i = 1; i <= n; ++i)
            if (parejas[i] == 0 && dfs(i))
                emparejamiento++;
    return emparejamiento;
}

void solve()
{
    int n, m, p;
    std::cin >> n >> m >> p;

    bool conectadoIzq[n + 1], conectadoDer[m + 1];

    // Initialize the arrays to false
    for (int i = 0; i <= n; ++i)
        conectadoIzq[i] = false;
    for (int i = 0; i <= m; ++i)
        conectadoDer[i] = false;

    for (int i = 0; i < p; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        adj[u].add(v + n); // Use add method for LinkedList
        conectadoIzq[u] = true;
        conectadoDer[v] = true;
    }

    int emparejamientos = min_guards(n);

    std::cout << emparejamientos << std::endl;
}
