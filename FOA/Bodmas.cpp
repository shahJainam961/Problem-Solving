#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> numbers;
vector<char> operators;
set<ll> dp[31][31];

ll calculate(ll a, ll b, char c) {
    if (c == '-') return a - b;
    if (c == '+') return a + b;
    return a * b;
}

ll evaluateExpression(vector<ll> &values, vector<char> &ops) {
    stack<ll> num_stack;
    stack<char> op_stack;
    map<char, int> precedence;
    precedence['-'] = 1;
    precedence['+'] = 1;
    precedence['*'] = 3;
    num_stack.push(values[0]);
    ll n = ops.size();
    
    for (ll i = 0; i < n; i++) {
        while (!op_stack.empty() && precedence[op_stack.top()] >= precedence[ops[i]]) {
            ll val1 = num_stack.top(); num_stack.pop();
            ll val2 = num_stack.top(); num_stack.pop();
            char op = op_stack.top(); op_stack.pop();
            num_stack.push(calculate(val2, val1, op));
        }
        op_stack.push(ops[i]);
        num_stack.push(values[i + 1]);
    }
    
    while (!op_stack.empty()) {
        ll val1 = num_stack.top(); num_stack.pop();
        ll val2 = num_stack.top(); num_stack.pop();
        char op = op_stack.top(); op_stack.pop();
        num_stack.push(calculate(val2, val1, op));
    }
    
    return num_stack.top();
}

set<ll> calculateResults(int start, int end) {
    if (start == end) {
        return set<ll>{numbers[start]};
    }
    if (dp[start][end].size()) {
        return dp[start][end];
    }
    set<ll> result_set;
    for (int k = start; k < end; k++) {
        for (int p1 : calculateResults(start, k)) {
            for (int p2 : calculateResults(k + 1, end)) {
                result_set.insert(calculate(p1, p2, operators[k]));
            }
        }
    }
    return dp[start][end] = set<ll>(result_set);
}

int main() {
    string input;
    cin >> input;
    int n;
    cin >> n;
    vector<ll> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    ll current_value = 0;
    for (char c : input) {
        if (isdigit(c)) {
            current_value = 10 * current_value + (c - '0');
        } else {
            numbers.push_back(current_value);
            current_value = 0;
            operators.push_back(c);
        }
    }
    numbers.push_back(current_value);
    
    set<ll> all_results = calculateResults(0, numbers.size() - 1);
    
    ll original_result = evaluateExpression(numbers, operators);
    ll score = 0;
    for (int i : values) {
        if (i == original_result) {
            score += 5;
        } else if (all_results.count(i)) {
            score += 2;
        }
    }
    cout << score << "\n";
    return 0;
}

