#include <iostream>
#include <vector>
#include <forward_list>
#include <unordered_set>
#include <queue>

struct Node {
    size_t id;
    size_t weight;
};

using Graph = std::vector<std::forward_list<Node>>;

void printDot(Graph const& graph)
{
    std::cout << "digraph G { \n";
    for (auto i = 0; i < graph.size(); i++)
    {
        for (auto const& neighbour : graph.at(i))
        {
            std::cout << i << " -> " << neighbour.id << std::endl;
        }
    }
    std::cout << "}\n";
}

bool hasEdge(Graph const& graph, size_t from, size_t to)
{
    // neighbours of from -> graph[from]
    if (from >= graph.size())
        return false;

    for (const auto& neighbour : graph.at(from))
    {
        if (neighbour.id == to)
            return true;
    }
    return false;
}

bool addVertex(Graph& graph)
{
    graph.push_back(std::forward_list<Node>());
}

bool addDirectedEdge(Graph& graph, size_t from, size_t to, size_t weight = 1)
{
    if (from < graph.size() && !hasEdge(graph, from, to))
    {
       graph.at(from).push_front({to, weight});
       return true;
    }
    return false;
}

bool addUndirectedEdge(Graph& graph, size_t from, size_t to, size_t weight)
{
    return addDirectedEdge(graph, from, to, weight) && addDirectedEdge(graph, to, from, weight);
}

// search: log2(n)
void dfsHelper(Graph const& graph, size_t current, std::unordered_set<size_t>& visited)
{
    visited.insert(current);

    for (auto const& neighbour : graph.at(current))
    {
        // if present -> iterator
        // if not present -> visited.end()
        if (visited.find(neighbour.id) == visited.end())
        {
            dfsHelper(graph, neighbour.id, visited);
        }
    }
}

size_t countComponents(Graph const& graph)
{
    std::unordered_set<size_t> visited;
    size_t count = 1;

    dfsHelper(graph, 0, visited);
    for (size_t i = 0; i < graph.size(); i++)
    {
        if (visited.find(i) == visited.end())
        {
            dfsHelper(graph, i, visited);
        }
    }

    return count;
}

bool hasCycleHelper(Graph const& graph, size_t current, std::vector<bool> &visited, std::vector<bool> &path)
{
    if (path[current])
        return true;

    path[current] = true;

    for (auto const& neighbour : graph[current])
    {
        if (!visited[neighbour.id])
        {
            if (hasCycleHelper(graph, neighbour.id, visited, path))
            {
                return true;
            }
        }
    }

    visited[current] = true;
    return false;
}

void dfs(Graph const& graph)
{
    std::unordered_set<size_t> visited;
    dfsHelper(graph, 0, visited);
}

bool hasCycle(Graph const& graph)
{
    std::vector<bool> visited(graph.size(), false);
    std::vector<bool> path(graph.size(), false);
    return hasCycleHelper(graph, 0, visited, path);
}

void bfs(Graph &g)
{
    std::queue<size_t> q;
    q.push(0);
    std::vector<bool> visited(g.size(), false);

    while (!q.empty())
    {
        size_t current = q.front();
        visited[current] = true;
        std::cout << current << " ";
        q.pop();
        for (auto const& neighbour : g[current])
        {
            if (!visited.at(neighbour.id))
            {
                q.push(neighbour.id);
            }
        }
    }

    std::cout << std::endl;
}

int main() {
    Graph g(4);
    addDirectedEdge(g, 0, 1);
    addDirectedEdge(g, 0, 2);
    addDirectedEdge(g, 1, 2);
    addDirectedEdge(g, 1, 3);
//    addDirectedEdge(g, 2, 1);
    printDot(g);
    bfs(g);
    std::cout << hasCycle(g) << std::endl;
}
