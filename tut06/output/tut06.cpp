#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

const int INF = 1e9; // Represents infinity

struct Link {
    string node1;
    string node2;
    int cost;
};

int N; // Number of routers

vector<thread> threads;
vector<vector<int>> matrix;
vector<mutex> mutex;
vector<int> complete;
mutex printMutex;

bool isConnected(vector<vector<int>>& matrix, int N) {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (matrix[i][i] != 0) {
            return false; // Graph is disconnected.
        }
    }
    return true; // Graph is connected.
}

void update(int threadId) {
    for (int i = 0; i < N; i++) {
        if (i != threadId) {
            lock_guard<mutex> lock(mutex[i]);
            for (int j = 0; j < N; j++) {
                matrix[i][j] = min(matrix[i][j], matrix[i][threadId] + matrix[threadId][j]);
            }
        }
    }
    complete[threadId]++;
}

void printMatrix(int iteration) {
    lock_guard<mutex> lock(printMutex);
    cout << "Iteration " << iteration << ":\n";
    cout << "Threads\t";
    for (int i = 0; i < N; i++) {
        cout << "\tTh " << i;
    }
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "Thread " << i << "\t";
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void init(int threadId) {
    lock_guard<mutex> lock(mutex[threadId]);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (auto neighbor : graph[threadId]) {
        int node = neighbor.first;
        int dist = neighbor.second;
        matrix[threadId][node] = dist;
    }

    complete[threadId]++;
    for (int j = 0; j < N; j++) {
        if (complete[j] < 1)
            j = 0;
    }

    printMatrix(0);

    for (int i = 0; i < N; i++) {
        update(threadId);
        for (int j = 0; j < N; j++) {
            if (complete[j] < i + 2)
                j = 0;
        }
        printMatrix(i + 1);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    ifstream inputFile("topology.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    inputFile >> N; // Read the number of routers from the file.

    vector<string> routerNames(N);
    for (int i = 0; i < N; ++i) {
        inputFile >> routerNames[i];
    }

    vector<Link> links;
    string node1, node2;
    int cost;

    vector<vector<pair<int, int>> graph(N);

    while (inputFile >> node1 >> node2 >> cost) {
        int node1Index = find(routerNames.begin(), routerNames.end(), node1) - routerNames.begin();
        int node2Index = find(routerNames.begin(), routerNames.end(), node2) - routerNames.begin();
        graph[node1Index].push_back({node2Index, cost});
        graph[node2Index].push_back({node1Index, cost});
    }

    inputFile.close();

    matrix.resize(N, vector<int>(N, INF));
    mutex.resize(N);
    complete.resize(N, 0);

    if (!isConnected(matrix, N)) {
        cout << "The input topology is disconnected." << endl;
        return 1;
    }

    for (int i = 0; i < N; i++) {
        threads.emplace_back(init, i);
    }

    for (int i = 0; i < N; i++) {
        threads[i].join();
    }

    return 0;
}
