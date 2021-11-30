﻿#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

const int inf = 1000000;

class AbstractGraph {
private:
    int n, m;
    std::vector<std::vector<int>> MatrixAdj;
public:

    AbstractGraph() {
        Input();
    }

    AbstractGraph(int n): n(n), m(rand()%(n*(n-1)/2)) {
        MatrixAdj.resize(n);
        for (int i = 0; i < n; i++) MatrixAdj[i].resize(n, inf);

        Generation(n, m);
    };

    void Input() {
        int choice;
        std::string fname;
        std::cout << "Do you want to read data from file or write by console? Enter 0 or 1" << std::endl;
        std::cin >> choice;
        if (!choice) {
            std::ifstream F;
            std::cout << "Enter filename: ";
            std::cin >> fname;
            F.open(fname, std::ios::in);
            F >> n >> m;

            MatrixAdj.resize(n);
            for (int i = 0; i < n; i++) MatrixAdj[i].resize(n);

            for (int i = 0; i < m; i++) {
                int v, u, s;
                F >> v >> u >> s;
                MatrixAdj[v - 1][u - 1] = MatrixAdj[u - 1][v - 1] = s;
            }
            F.close();
        }
        else {
            std::cout << "Enter count of vertices and edges: ";
            std::cin >> n >> m;

            MatrixAdj.resize(n);
            for (int i = 0; i < n; i++) MatrixAdj[i].resize(n);

            std::cout << "Enter numbers of start and final vertices of edges and lengths of the edges:\n";
            for (int i = 0; i < m; i++) {
                int v, u, s;
                std::cin >> v >> u >> s;
                MatrixAdj[v - 1][u - 1] = MatrixAdj[u - 1][v - 1] = s;
            }
        }

    }

    void Generation(int n, int m) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rand() % 2){
                    int a = rand() % 100;
                    MatrixAdj[i][j] = a;
                    MatrixAdj[j][i] = a;
                } 
            }
            MatrixAdj[i][i] = 0;
        }
    }

    void Output() {
        std::cout << "\n  | ";
        for (int i = 0; i < n; ++i) {
            std::cout.width(3);
            std::cout << i + 1 << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 4*n + 3; ++i) std::cout << "-";
        std::cout << std::endl;

        for (int i = 0; i < n; ++i) {
            std::cout << i + 1 << " | ";
            for (int j = 0; j < n; ++j) {
                if (MatrixAdj[i][j] == inf) {
                    std::cout.width(3);
                    std::cout << "inf" << " ";
                }
                else {
                    std::cout.width(3);
                    std::cout << MatrixAdj[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    friend std::vector<int> Dijkstra(AbstractGraph G, int s);
    friend std::list<int> Path(AbstractGraph G, std::vector<int> A, int s, int f);
};

int main() {
    srand(time(0));
    //AbstractGraph G;
    AbstractGraph G1(7);

    //G.Output();
    G1.Output();

    int s, f;
    std::cout << "\nEnter numbers of start and final vertices: ";
    
    std::cin >> s >> f;

    std::cout << "Distance: ";
    std::vector<int> A = Dijkstra(G1, s - 1);
    for (auto& i : A)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Path: ";
    std::list<int> B = Path(G1, A, s - 1, f - 1);
    for (auto& i : B)
        std::cout << i << " ";

    return 0;
}

std::vector<int> Dijkstra(AbstractGraph G, int s) {
    std::vector<int> D(G.n);
    for (int v = 0; v < G.n; v++) {
        if (G.MatrixAdj[s][v])
            D[v] = G.MatrixAdj[s][v];
        else
            D[v] = 100000;
    }
    D[s] = 0;

    std::vector<bool> visited(G.n);
    visited[s] = 1;

    for (int i = 0; i < G.n; i++) {
        int v = s, minWeight = 1000000;

        for (int j = 0; j < G.n; j++)
            if (not visited[j] and D[j] < minWeight) {
                v = j;
                minWeight = D[j];
            }
        visited[v] = 1;

        for (int u = 0; u < G.n; u++) {
            if (not visited[u] and G.MatrixAdj[v][u]) {
                if (D[v] + G.MatrixAdj[v][u] < D[u])
                    D[u] = D[v] + G.MatrixAdj[v][u];
            }
        }
    }

    return D;
}

std::list<int> Path(AbstractGraph G, std::vector<int> A, int s, int f) {
    std::list<int> B;

    int v = f;
    B.push_front(v + 1);

    while (v != s) {
        for (int u = 0; u < G.n; u++) {
            if (G.MatrixAdj[v][u])
                if (A[u] == A[v] - G.MatrixAdj[v][u]) {
                    v = u;
                    B.push_front(v + 1);
                    break;
                }
        }
    }

    return B;
}
