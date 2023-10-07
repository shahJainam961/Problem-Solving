class Solution {

public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        if (n <= 5) return 0;

        unordered_set<int> adj[n];
        int remainingNodes = n;
        for (auto edge : edges) {
            adj[edge[0]].insert(edge[1]);
            adj[edge[1]].insert(edge[0]);
        }

        queue<int> emptyLeavesWithNoCoins;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() == 1 and !coins[i]) emptyLeavesWithNoCoins.push(i);
        }

        while (!emptyLeavesWithNoCoins.empty()) {
            int node = emptyLeavesWithNoCoins.front(); emptyLeavesWithNoCoins.pop(); remainingNodes--;
            vector<int> neighbours(adj[node].begin(), adj[node].end());
            for (int adjNode : neighbours) {
                adj[adjNode].erase(node);
                adj[node].erase(adjNode);
                if (adj[adjNode].size() == 1 and !coins[adjNode]) emptyLeavesWithNoCoins.push(adjNode);
            }
        }

        queue<int> removeTwoLayerFromLeafWithCoin;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() == 1) removeTwoLayerFromLeafWithCoin.push(i);
        }

        for (int i = 0; i < 2; i++) {
            if (!removeTwoLayerFromLeafWithCoin.empty()) {
                int size = removeTwoLayerFromLeafWithCoin.size();
                for (int i = 0; i < size; i++) {
                    int node = removeTwoLayerFromLeafWithCoin.front(); removeTwoLayerFromLeafWithCoin.pop(); remainingNodes--;
                    vector<int> neighbours(adj[node].begin(), adj[node].end());
                    for (int adjNode : neighbours) {
                        adj[adjNode].erase(node);
                        adj[node].erase(adjNode);
                        if (adj[adjNode].size() == 1) removeTwoLayerFromLeafWithCoin.push(adjNode);
                    }
                }
            }
        }

        return remainingNodes > 1 ? 2 * (remainingNodes - 1) : 0;
    }
};