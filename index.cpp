#include <bits/stdc++.h>
using namespace std;

//==========================================
// 1. 0/1 KNAPSACK PROBLEM
//==========================================
// Time Complexity: O(n*W) where n is number of items and W is capacity
// Space Complexity: O(n*W)
int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    // Create a 2D dp table
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;                              // Base case: no items or no capacity
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], // Include item
                               dp[i - 1][w]);                          // Exclude item
            else
                dp[i][w] = dp[i - 1][w];                   // Can't include this item
        }
    }
    
    return dp[n][W];  // Return maximum value
}

//==========================================
// 2. FLOYD WARSHALL ALGORITHM
//==========================================
// Time Complexity: O(V³) where V is the number of vertices
// Space Complexity: O(V²)
#define INF 99999

void floydWarshall(vector<vector<int>>& graph, int V) {
    // dist[][] will be the output matrix
    vector<vector<int>> dist(V, vector<int>(V));
    
    // Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    
    // k is the intermediate vertex
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    
    // Print the shortest distance matrix
    cout << "Shortest distances between all pairs of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

//==========================================
// 3. COIN CHANGE PROBLEM
//==========================================
// Time Complexity: O(amount * coins.size())
// Space Complexity: O(amount)

// Minimum number of coins to make change
int coinChange(vector<int>& coins, int amount) {
    // dp[i] represents the minimum number of coins needed to make amount i
    vector<int> dp(amount + 1, amount + 1);
    
    // Base case: 0 coins needed to make amount 0
    dp[0] = 0;
    
    // Fill dp table bottom-up
    for (int i = 1; i <= amount; i++) {
        // Try each coin if it doesn't exceed current amount
        for (int coin : coins) {
            if (coin <= i) {
                // Transition: either use the coin or don't
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    // If dp[amount] is still amount+1, it means amount can't be made
    return dp[amount] > amount ? -1 : dp[amount];
}

// Total number of ways to make change
int coinChangeWays(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // Base case: one way to make amount 0 (using no coins)
    
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[amount];
}

//==========================================
// 4. MATRIX CHAIN MULTIPLICATION
//==========================================
// Time Complexity: O(n³)
// Space Complexity: O(n²)
int matrixChainMultiplication(vector<int>& p, int n) {
    // dp[i][j] = Minimum number of scalar multiplications needed to compute the
    // matrix chain product from matrix i to matrix j
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // L is chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            
            // Try each possible split point
            for (int k = i; k < j; k++) {
                // Cost = cost of multiplying matrices from i to k +
                //        cost of multiplying matrices from k+1 to j +
                //        cost of multiplying the resulting matrices
                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    return dp[1][n-1];
}

//==========================================
// 5. LONGEST COMMON SUBSEQUENCE
//==========================================
// Time Complexity: O(m*n) where m and n are lengths of the two strings
// Space Complexity: O(m*n)
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    
    // dp[i][j] represents the length of LCS of text1[0..i-1] and text2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Build dp table in bottom-up fashion
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                // If current characters match, add 1 to diagonal value
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // Otherwise, take the maximum of excluding either character
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // Optional: Reconstruct the LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (text1[i - 1] == text2[j - 1]) {
            lcs = text1[i - 1] + lcs;
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    cout << "LCS: " << lcs << endl;
    return dp[m][n];
}

//==========================================
// 6. LONGEST INCREASING SUBSEQUENCE
//==========================================
// Standard O(n²) solution
// Time Complexity: O(n²)
// Space Complexity: O(n)
int lengthOfLIS_dp(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    
    // dp[i] represents the length of the LIS ending at index i
    vector<int> dp(n, 1);
    
    // Fill dp array
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    // Find maximum in dp array
    return *max_element(dp.begin(), dp.end());
}

// Optimized O(n log n) solution using binary search
// Time Complexity: O(n log n)
// Space Complexity: O(n)
int lengthOfLIS_optimized(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    
    // tails[i] = smallest value that ends an increasing subsequence of length i+1
    vector<int> tails;
    
    for (int x : nums) {
        // Binary search to find the position to insert x
        auto it = lower_bound(tails.begin(), tails.end(), x);
        
        if (it == tails.end()) {
            // x is greater than all values in tails, append it
            tails.push_back(x);
        } else {
            // Replace the smallest value >= x
            *it = x;
        }
    }
    
    return tails.size();
}

//==========================================
// 7. EDIT DISTANCE (STRING EDITING)
//==========================================
// Time Complexity: O(m*n) where m and n are lengths of the two strings
// Space Complexity: O(m*n)
int minDistance(string word1, string word2) {
    int m = word1.length();
    int n = word2.length();
    
    // dp[i][j] represents the minimum number of operations required
    // to convert word1[0..i-1] to word2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Base cases: empty string transformations
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;  // Delete all characters from word1
    
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;  // Insert all characters from word2
    
    // Fill dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                // Characters match, no operation needed
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Choose minimum of three operations:
                // 1. Insert: dp[i][j-1] + 1
                // 2. Delete: dp[i-1][j] + 1
                // 3. Replace: dp[i-1][j-1] + 1
                dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
            }
        }
    }
    
    return dp[m][n];
}

//==========================================
// 8. DYNAMIC PROGRAMMING FUNDAMENTALS
//==========================================
// Fibonacci examples to demonstrate DP approaches

// 1. Recursive approach (not DP) - Inefficient
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 2. Memoization approach (Top-down DP)
// Time Complexity: O(n)
// Space Complexity: O(n)
int fib_memoization(int n, vector<int>& memo) {
    if (n <= 1) return n;
    
    // If value already calculated, return it
    if (memo[n] != -1) return memo[n];
    
    // Otherwise calculate and store result
    memo[n] = fib_memoization(n - 1, memo) + fib_memoization(n - 2, memo);
    return memo[n];
}

// 3. Tabulation approach (Bottom-up DP)
// Time Complexity: O(n)
// Space Complexity: O(n)
int fib_tabulation(int n) {
    if (n <= 1) return n;
    
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// 4. Space-optimized approach
// Time Complexity: O(n)
// Space Complexity: O(1)
int fib_optimized(int n) {
    if (n <= 1) return n;
    
    int prev2 = 0;
    int prev1 = 1;
    int current;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Demonstration of standard dynamic programming steps
void dynamic_programming_fundamentals() {
    cout << "\n=== DYNAMIC PROGRAMMING FUNDAMENTALS ===\n";
    cout << "Four key steps for solving DP problems:\n";
    cout << "1. Identify if it's a DP problem:\n";
    cout << "   - Has optimal substructure\n";
    cout << "   - Has overlapping subproblems\n";
    cout << "   - Often involves optimization or counting\n\n";
    
    cout << "2. Define state (what a subproblem is):\n";
    cout << "   - Usually defined as dp[i] or dp[i][j]\n\n";
    
    cout << "3. Write recurrence relation:\n";
    cout << "   - How subproblems relate to each other\n\n";
    
    cout << "4. Identify base cases\n\n";
    
    cout << "Implementation approaches:\n";
    cout << "   a. Top-down (memoization): recursive with caching\n";
    cout << "   b. Bottom-up (tabulation): iterative building\n";
    cout << "   c. Space optimization when possible\n";
}

//==========================================
// MAIN FUNCTION WITH EXAMPLE CALLS
//==========================================
int main() {
    cout << "\n====== DYNAMIC PROGRAMMING EXAMPLES ======\n";
    
    // 1. Knapsack example
    cout << "\n=== 0/1 KNAPSACK PROBLEM ===\n";
    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    int n = val.size();
    cout << "Maximum value in Knapsack: " << knapsack(W, wt, val, n) << endl;
    
    // 2. Floyd Warshall example
    cout << "\n=== FLOYD WARSHALL ALGORITHM ===\n";
    int V = 4;  // Number of vertices
    vector<vector<int>> graph = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    floydWarshall(graph, V);
    
    // 3. Coin Change example
    cout << "\n=== COIN CHANGE PROBLEM ===\n";
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << "Minimum coins needed: " << coinChange(coins, amount) << endl;
    cout << "Total ways to make change: " << coinChangeWays(coins, amount) << endl;
    
    // 4. Matrix Chain Multiplication example
    cout << "\n=== MATRIX CHAIN MULTIPLICATION ===\n";
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int matrixCount = dimensions.size();
    cout << "Minimum number of multiplications: " << 
         matrixChainMultiplication(dimensions, matrixCount) << endl;
    
    // 5. Longest Common Subsequence example
    cout << "\n=== LONGEST COMMON SUBSEQUENCE ===\n";
    string text1 = "ABCDGH";
    string text2 = "AEDFHR";
    cout << "Length of LCS: " << longestCommonSubsequence(text1, text2) << endl;
    
    // 6. Longest Increasing Subsequence example
    cout << "\n=== LONGEST INCREASING SUBSEQUENCE ===\n";
    vector<int> nums = {10, 22, 9, 33, 21, 50, 41, 60};
    cout << "Length of LIS (DP O(n²)): " << lengthOfLIS_dp(nums) << endl;
    cout << "Length of LIS (Optimized O(n log n)): " << lengthOfLIS_optimized(nums) << endl;
    
    // 7. Edit Distance example
    cout << "\n=== EDIT DISTANCE (STRING EDITING) ===\n";
    string word1 = "horse";
    string word2 = "ros";
    cout << "Minimum edit distance: " << minDistance(word1, word2) << endl;
    
    // 8. DP Fundamentals with Fibonacci examples
    cout << "\n=== FIBONACCI EXAMPLES ===\n";
    int fibN = 10;
    cout << "Fibonacci(" << fibN << ") using recursive: " << fib_recursive(fibN) << endl;
    
    vector<int> memo(fibN + 1, -1);
    cout << "Fibonacci(" << fibN << ") using memoization: " << fib_memoization(fibN, memo) << endl;
    
    cout << "Fibonacci(" << fibN << ") using tabulation: " << fib_tabulation(fibN) << endl;
    
    cout << "Fibonacci(" << fibN << ") using space optimization: " << fib_optimized(fibN) << endl;
    
    // Display DP fundamentals
    dynamic_programming_fundamentals();
    
    return 0;
}
