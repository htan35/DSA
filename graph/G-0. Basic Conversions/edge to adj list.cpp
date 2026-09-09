# https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1
# input

edges = {
    {0,1},
    {0,2},
    {1,2},
    {2,3}
};

# adj list 
vector<vector<int>> adj(V);

for(auto edge : edges){
    int u = edge[0];
    int v = edge[1];

    adj[u].push_back(v);
    adj[v].push_back(u);
}
