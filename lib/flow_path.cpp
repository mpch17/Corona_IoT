#include "flow_path.hpp"
#include <queue>

using namespace std;

// A special BFS version that returns true if there's a path from source to sink.
static bool BFS(vector< vector<int> > &resAdjMatrix, int &source, int &sink, vector<int> &parent)
{
    // Create an array for all nodes we visited. Initialized to false.
    int n = resAdjMatrix.size();
    bool visited[n] = { false };

    // Create a queue to check each node.
    queue<int> q;

    // Push our source into the queue and mark it as visited. It has no parent.
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    // Keep visiting vertices.
    while(q.empty() == false)
    {
        int u = q.front();
        q.pop();

        // Check all of u's friends.
        for(int i = 0; i < n; i++)
        {
            int v = i;
            int capacity = resAdjMatrix[u][v];

            // We find a neighbor that hasn't been visited, and the capacity is bigger than 0.
            if(visited[v] == false && capacity > 0)
            {
                // Push the neighbor onto the queue, mark it's parent, and mark it as visited.
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
   }

    // If the sink got visited, then we found a path to it.
    if(visited[sink] == true)
    { return true; }

    return false;
}

// Use the Ford Fulkerson algorithm. Return the max flow.
pair<vector<int>, int> FordFulkerson(vector< vector<int> > &adjMatrix, int &source, int &sink)
{
    int maxflow = 0;

    // 1. Create the residual graph. (Same as the original graph.)
    vector< vector<int> > resAdjMatrix;
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++)
    {
        vector<int> row;
        resAdjMatrix.push_back(row);

        for(int j = 0; j < adjMatrix[i].size(); j++)
        {
            resAdjMatrix[i].push_back(adjMatrix[i][j]);
        }
    }

    // 2. Create an empty parent array for BFS to store the augmenting path.
    vector<int> parent;
    vector<int> bestpath;

    for(int i = 0; i < n; i++)
    {
        parent.push_back(-1);
    }

    // 3. Keep calling BFS to check for an augmenting path (from the source to the sink...
    while(BFS(resAdjMatrix, source, sink, parent) == true)
    {
        // 4. Find the max flow through the path we just found.
        int pathflow = 10000007;

        // Go through the path we just found. Iterate through the path.
        int v = sink;

        while(v != source)
        {
            int u = parent[v]; // The parent.

            // Update the pathflow to this capacity if it's smaller
            int capacity = resAdjMatrix[u][v];
            pathflow = min(pathflow, capacity);

            // Setup for the next edge in the path.
            v = u;
        }

        // 5. Update the residual capacities of the edges and reverse edges.
        v = sink;

        while(v != source)
        {
            int u = parent[v]; // The parent.

            // Update the capacities.
            resAdjMatrix[u][v] -= pathflow;
            resAdjMatrix[v][u] += pathflow;

            // Setup for the next edge in the path.
            v = u;
        }

        // 6. Save the highest flow.
        if (pathflow > maxflow)
            bestpath = parent;

        maxflow = max(maxflow, pathflow);
    }

    return std::pair<vector<int>, int>(bestpath, maxflow);
}
