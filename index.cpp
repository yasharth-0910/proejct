#include <bits/stdc++.h>
using namespace std;

// 1. Minimum Coin Change (Greedy)
// Time: O(n log n + amount), Space: O(amount)
void minCoinChange(int coins[], int n, int amount) {
    sort(coins, coins + n, greater<int>()); // O(n log n)
    vector<int> result;
    for (int i = 0; i < n && amount > 0; ++i) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            result.push_back(coins[i]);
        }
    }
    cout << "Coins used: ";
    for (int c : result) cout << c << " ";
    cout << endl;
}

// 2. Fractional Knapsack (Greedy)
// Time: O(n log n), Space: O(1)
struct Item {
    int value, weight;
    Item(int v, int w) : value(v), weight(w) {}
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> items) {
    sort(items.begin(), items.end(), cmp);
    double totalValue = 0.0;
    for (auto &item : items) {
        if (W >= item.weight) {
            W -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            break;
        }
    }
    return totalValue;
}

// 3. Activity Selection (Greedy)
// Time: O(n log n), Space: O(1)
struct Activity {
    int start, end;
};

bool activityCmp(Activity a, Activity b) {
    return a.end < b.end;
}

void activitySelection(vector<Activity> &activities) {
    sort(activities.begin(), activities.end(), activityCmp);
    cout << "Selected Activities: \n";
    int lastEnd = -1;
    for (auto act : activities) {
        if (act.start >= lastEnd) {
            cout << "(" << act.start << ", " << act.end << ")\n";
            lastEnd = act.end;
        }
    }
}

// 4. Huffman Encoding (Greedy + String)
// Time: O(n log n), Space: O(n)
struct HuffNode {
    char ch;
    int freq;
    HuffNode *left, *right;
    HuffNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

struct compareHuff {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

void printHuffCodes(HuffNode* root, string str) {
    if (!root) return;
    if (root->ch != '#') cout << root->ch << ": " << str << endl;
    printHuffCodes(root->left, str + "0");
    printHuffCodes(root->right, str + "1");
}

void huffmanCodes(vector<pair<char, int>> freqTable) {
    priority_queue<HuffNode*, vector<HuffNode*>, compareHuff> pq;
    for (auto &p : freqTable)
        pq.push(new HuffNode(p.first, p.second));

    while (pq.size() > 1) {
        HuffNode* l = pq.top(); pq.pop();
        HuffNode* r = pq.top(); pq.pop();
        HuffNode* merged = new HuffNode('#', l->freq + r->freq);
        merged->left = l;
        merged->right = r;
        pq.push(merged);
    }

    printHuffCodes(pq.top(), "");
}

// 5. Rabin-Karp Algorithm for Pattern Matching
// Time: O(n + m), Space: O(1)
#define d 256
#define q 101
void rabinKarp(string pat, string txt) {
    int M = pat.length(), N = txt.length();
    int p = 0, t = 0, h = 1;

    for (int i = 0; i < M - 1; i++) h = (h * d) % q;

    for (int i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= N - M; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < M; j++)
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            if (match) cout << "Pattern found at index " << i << endl;
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0) t = (t + q);
        }
    }
}

// 6. Karp-Rabin (Simplified Rolling Hash Version for Comparison)
// Time: O(n + m), Space: O(1)
int karpRollingHash(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();
    int hash_pat = 0, hash_txt = 0, h = 1, d = 256, q = 101;

    for (int i = 0; i < m - 1; i++) h = (h * d) % q;
    for (int i = 0; i < m; i++) {
        hash_pat = (d * hash_pat + pat[i]) % q;
        hash_txt = (d * hash_txt + txt[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (hash_pat == hash_txt) {
            if (txt.substr(i, m) == pat) return i;
        }
        if (i < n - m) {
            hash_txt = (d * (hash_txt - txt[i] * h) + txt[i + m]) % q;
            if (hash_txt < 0) hash_txt = (hash_txt + q);
        }
    }
    return -1;
}

// 7. String Compression (like s.c)
// Time: O(n), Space: O(n)
string compressString(string s) {
    string result = "";
    int count = 1;
    for (int i = 1; i <= s.length(); i++) {
        if (s[i] == s[i - 1]) {
            count++;
        } else {
            result += s[i - 1] + to_string(count);
            count = 1;
        }
    }
    return result;
}

// 8. Toggle Case (like t.cc)
// Time: O(n), Space: O(1)
string toggleCase(string s) {
    for (char &ch : s) {
        if (islower(ch)) ch = toupper(ch);
        else if (isupper(ch)) ch = tolower(ch);
    }
    return s;
}

// Sample main to demonstrate all
int main() {
    // Coin Change
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 500, 2000};
    int n = sizeof(coins)/sizeof(coins[0]);
    minCoinChange(coins, n, 93);

    // Fractional Knapsack
    vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    cout << "Max value in Knapsack = " << fractionalKnapsack(50, items) << endl;

    // Activity Selection
    vector<Activity> acts = {{1, 3}, {2, 5}, {0, 6}, {8, 9}, {5, 9}, {5, 7}, {3, 4}};
    activitySelection(acts);

    // Huffman Coding
    vector<pair<char, int>> freq = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    huffmanCodes(freq);

    // Rabin-Karp Pattern Matching
    string txt = "GEEKS FOR GEEKS";
    string pat = "GEEK";
    rabinKarp(pat, txt);

    // Karp-Rabin (Rolling Hash)
    int foundIdx = karpRollingHash("hellohelloworld", "world");
    cout << "Pattern found at index (Karp Hash): " << foundIdx << endl;

    // String Compression
    cout << "Compressed: " << compressString("aaabbbcccaaa") << endl;

    // Toggle Case
    cout << "Toggle Case: " << toggleCase("aBcDeF") << endl;

    return 0;
}
