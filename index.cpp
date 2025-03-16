#include <bits/stdc++.h>
using namespace std;

// -------------------- TEMPLATE START --------------------

// Ford-Fulkerson Algorithm for Maximum Flow
class MaxFlow {
    int V;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

public:
    MaxFlow(int vertices) : V(vertices), capacity(vertices, vector<int>(vertices, 0)), adj(vertices) {}

    void addEdge(int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] = cap;
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t) return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int fordFulkerson(int s, int t) {
        int max_flow = 0;
        vector<int> parent(V);
        int new_flow;

        while ((new_flow = bfs(s, t, parent))) {
            max_flow += new_flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return max_flow;
    }
};

// Edmonds-Karp Algorithm (BFS-based Ford-Fulkerson)
int edmondsKarp(vector<vector<int>>& capacity, int s, int t) {
    int V = capacity.size();
    vector<vector<int>> adj(V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (capacity[i][j] > 0) adj[i].push_back(j);

    int max_flow = 0;
    vector<int> parent(V);
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});
        parent[s] = -2;

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t) {
                        max_flow += new_flow;
                        int curr = t;
                        while (curr != s) {
                            int prev = parent[curr];
                            capacity[prev][curr] -= new_flow;
                            capacity[curr][prev] += new_flow;
                            curr = prev;
                        }
                        return max_flow;
                    }
                    q.push({next, new_flow});
                }
            }
        }
        return max_flow;
    }
}

// Generate Binary Strings with Hamming Distance d
void generateBinaryStrings(string S, int d, int index, int flipped) {
    if (flipped == d) {
        cout << S << endl;
        return;
    }
    if (index >= S.size()) return;

    generateBinaryStrings(S, d, index + 1, flipped);
    S[index] = (S[index] == '0') ? '1' : '0';
    generateBinaryStrings(S, d, index + 1, flipped + 1);
}

// Subset Sum Partition (Backtracking)
bool canPartition(vector<int>& nums, int index, int sum, int total) {
    if (sum * 2 == total) return true;
    if (sum > total / 2 || index >= nums.size()) return false;

    return canPartition(nums, index + 1, sum + nums[index], total) || canPartition(nums, index + 1, sum, total);
}

bool subsetSumPartition(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0) return false;
    return canPartition(nums, 0, 0, total);
}

// Magic Square Generator (Backtracking)
void generateMagicSquare(vector<vector<int>>& grid, int i, int j, int n) {
    if (i == n) {
        for (auto& row : grid) {
            for (int x : row) cout << x << " ";
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (int num = 1; num <= n * n; num++) {
        grid[i][j] = num;
        generateMagicSquare(grid, i + (j + 1) / n, (j + 1) % n, n);
        grid[i][j] = 0;
    }
}

// Find Sum Combinations (Backtracking)
void findCombinations(vector<int>& nums, int target, int index, vector<int>& current) {
    if (target == 0) {
        for (int num : current) cout << num << " ";
        cout << endl;
        return;
    }
    if (index >= nums.size() || target < 0) return;

    findCombinations(nums, target, index + 1, current);
    current.push_back(nums[index]);
    findCombinations(nums, target - nums[index], index + 1, current);
    current.pop_back();
}

// -------------------- MAIN FUNCTION FOR TESTING --------------------
int main() {
    // 1. Max Flow (Ford-Fulkerson)
    MaxFlow g(6);
    g.addEdge(0, 1, 30);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 3, 25);
    g.addEdge(2, 3, 10);
    g.addEdge(3, 5, 30);
    cout << "Max Flow: " << g.fordFulkerson(0, 5) << endl;

    // 2. Hamming Distance Binary Strings
    string S = "1010";
    int d = 2;
    cout << "Binary Strings with Hamming Distance " << d << ":" << endl;
    generateBinaryStrings(S, d, 0, 0);

    // 3. Subset Sum Partition
    vector<int> nums = {1, 5, 11, 5};
    cout << "Partition Possible: " << (subsetSumPartition(nums) ? "YES" : "NO") << endl;

    // 4. Magic Square
    int n = 3;
    vector<vector<int>> grid(n, vector<int>(n, 0));
    cout << "Magic Square of Order " << n << ":" << endl;
    generateMagicSquare(grid, 0, 0, n);

    // 5. Sum Combinations
    vector<int> numbers = {2, 3, 6, 7, 2, 2};
    cout << "Sum Combinations for Target 7:" << endl;
    vector<int> current;
    findCombinations(numbers, 7, 0, current);

    return 0;
}
