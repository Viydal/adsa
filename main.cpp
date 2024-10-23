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

  void reset() {
    int n = parent.size();
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
      seniority[i] = 0;
    }
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
    std::vector<Edge> destroyEdges = createEdges(destroyCost);  

    // printEdges(buildEdges);
    // std::cout << std::endl;
    // printEdges(destroyEdges);

    int weight = initialWeight(cityConnections, buildEdges, destroyEdges, uf);

    // uf.printPandS();

    for (size_t i = 0; i < buildEdges.size(); i++) {
      if (uf.find(buildEdges[i].a) != uf.find(buildEdges[i].b)) {
        std::cout << "ADDING CONNECTION | " << buildEdges[i].a << " to " << buildEdges[i].b << " with cost " << buildEdges[i].weight << std::endl;
        weight += buildEdges[i].weight;
        uf.link(buildEdges[i].a, buildEdges[i].b);
      }
    }

    // uf.printPandS();

    return weight;
  }

  int initialWeight(std::vector<std::string> cityConnections, std::vector<Edge> buildEdges, std::vector<Edge> destroyEdges, UnionFind &uf) {
    std::vector<Edge> perfectEdges;

    printEdges(destroyEdges);

    int initialWeight = 0;

    for (size_t i = 0; i < cityConnections.size(); i++) {
      for (size_t j = i; j < cityConnections[i].size(); j++) {
        if (cityConnections[i][j] == '1') {
          int index1 = i;
          int index2 = j;

          if (uf.find(index1) != uf.find(index2)) {
            for (size_t k = 0; k < destroyEdges.size(); k++) {
              if ((destroyEdges[k].a == index1 && destroyEdges[k].b == index2) || (destroyEdges[k].b == index1 && destroyEdges[k].a == index2)) {
                std::cout << "ADDING CONNECTION | " << destroyEdges[k].a << " to " << destroyEdges[k].b << std::endl;
                perfectEdges.push_back(destroyEdges[k]);

                uf.link(index1, index2);

                uf.printPandS();
                std::cout << std::endl;
              }
            }
          } else {
            int root = uf.find(index1);

            std::cout << "ATTEMPTING SWAP | " << index1 << " to " << index2 << std::endl;
            for (size_t k = 0; k < perfectEdges.size(); k++) {
              if (uf.find(perfectEdges[k].a) == root || uf.find(perfectEdges[k].b) == root) {
                std::cout << "SWAP INTIATED | " << index1 << " to " << index2 << " with cost " << perfectEdges[k].weight << std::endl;
                initialWeight += perfectEdges[k].weight;

                perfectEdges.erase(perfectEdges.begin() + k);

                uf.reset();

                for (size_t l = 0; l < perfectEdges.size(); l++) {
                  if (uf.find(index1) != uf.find(index2)) {
                    uf.link(perfectEdges[l].a, perfectEdges[l].b);
                  }
                }
                uf.link(index1, index2);

                uf.printPandS();
              }
            }
          }
        }
      }
    }
    
    return initialWeight;
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

  std::vector<std::string> cityConnections = {"011000","101000","110000","000011","000101","000110"};
  std::vector<std::string> buildCost = {"ABDFFF","BACFFF","DCAFFF","FFFABD","FFFBAC","FFFDCA"};
  std::vector<std::string> destroyCost = {"ABDFFF","BACFFF","DCAFFF","FFFABD","FFFBAC","FFFDCA"};

  std::cout << mst.createMST(cityConnections, buildCost, destroyCost) << std::endl;
}