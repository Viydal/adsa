#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class UnionFind {
public:
  std::vector<int> parent;
  std::vector<int> seniority;

  UnionFind() {}

  UnionFind(int n) {
    for (int i = 0; i < n; i++) {
      parent.push_back(i);
      seniority.push_back(0);
    }
  }

  int find(int node) {
    if (parent[node] == node) {
      return node;
    } else {
      return find(parent[node]);
    }
  }

  bool linkInitialise(int node1, int node2) {
    int root1 = find(node1);
    int root2 = find(node2);

    if (root1 != root2) {
      if (seniority[root1] < seniority[root2]) {
        parent[root1] = root2;
      } else if (seniority[root1] > seniority[root2]) {
        parent[root2] = root1;
      } else {
        parent[root2] = root1;
        seniority[root1]++;
      }
      return true;
    }
    return false;
  }

  bool link(int node1, int node2) {
    int root1 = find(node1);
    int root2 = find(node2);

    if (root1 != root2) {
      if (seniority[root1] < seniority[root2]) {
        parent[root1] = root2;
      } else if (seniority[root1] > seniority[root2]) {
        parent[root2] = root1;
      } else {
        parent[root2] = root1;
        seniority[root1]++;
      }
      return true;
    }
    return false;
  }

  void printPandS() {
    for (size_t i = 0; i < parent.size(); i++) {
      std::cout << parent[i] << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < seniority.size(); i++) {
      std::cout << seniority[i] << " ";
    }
    std::cout << std::endl;
  }
};

class MST {
public:
  struct Edge {
    int a, b, weight;

    Edge(int a_, int b_, int weight_) {
      a = a_;
      b = b_;
      weight = weight_;
    }
  };

  std::vector<Edge> createEdges(std::vector<std::string> cost) {
    std::vector<Edge> costVector;
    for (size_t i = 0; i < cost.size(); i++) {
      for (size_t j = 0; j < cost[0].size(); j++) {
        if (i == j) {
          continue;
        }
        Edge edge(i, j, letterValue(cost[i][j]));
        costVector.push_back(edge);
      }
    }

    sortEdges(costVector);
    removeDuplicateEdges(costVector);

    return costVector;
  }

  void sortEdges(std::vector<Edge> &edges) {
    for (size_t i = 0; i < edges.size(); i++) {
      for (size_t j = 0; j < edges.size() - 1; j++) {
        if (edges[j].weight > edges[j + 1].weight) {
          Edge temp = edges[j];

          edges[j] = edges[j + 1];
          edges[j + 1] = temp;
        }
      }
    }
  }

  void removeDuplicateEdges(std::vector<Edge> &edges) {
    for (size_t i = 0; i < edges.size(); i++) {
      for (size_t j = 0; j < edges.size() - 1; j++) {
        if (edges[j].a == edges[j + 1].b && edges[j + 1].a == edges[j].b) {
          edges.erase(edges.begin() + j);
        }
      }
    }
  }

  int letterValue(char letter) {
    int value;
    if (letter >= 65 && letter <= 90) {
      value = letter - 'A';
    } else {
      value = letter - 'a' + 26;
    }
    return value;
  }

  int createMST(std::vector<std::string> cityConnections, std::vector<std::string> buildCost, std::vector<std::string> destroyCost) {
    UnionFind uf(cityConnections.size());

    std::vector<Edge> buildEdges = createEdges(buildCost);
    std::vector<Edge> destroyEdges = createEdges(buildCost);  

    printEdges(buildEdges);
    // printEdges(destroyEdges);

    for (size_t i = 0; i < cityConnections.size(); ++i) {
      for (size_t j = 0; j < cityConnections[i].size(); ++j) {
        if (cityConnections[i][j] == '1') {
          if (uf.linkInitialise(i, j)) {
            std::cout << "SUCCESSFUL CONNECTION | connected node1: " << i << ", to node2: " << j << std::endl;
          } else {
            std::cout << "CONNECTION FAILURE | connected node1: " << i << ", to node2: " << j << std::endl;
          }
        }
      }
    }

    uf.printPandS();

    int weight = 0;

    for (size_t i = 0; i < buildEdges.size(); i++) {
      if (uf.find(buildEdges[i].a) != uf.find(buildEdges[i].b)) {
        weight += buildEdges[i].weight;
        uf.link(buildEdges[i].a, buildEdges[i].b);
      }
    }

    uf.printPandS();

    return weight;
  }

  void printEdges(std::vector<Edge> edges) {
    for (size_t i = 0; i < edges.size(); i++) {
      std::cout << "first node: " << edges[i].a
                << " | second node: " << edges[i].b
                << " | weight: " << edges[i].weight << std::endl;
    }
  }
};

int main() {
  MST mst;

  std::vector<std::string> cityConnections = {"000", "000", "000"};
  std::vector<std::string> buildCost = {"ABD", "BAC", "DCA"};
  std::vector<std::string> destroyCost = {"ABD", "BAC", "DCA"};

  std::cout << mst.createMST(cityConnections, buildCost, destroyCost) << std::endl;
}