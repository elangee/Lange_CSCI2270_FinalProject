#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
  std::string name;
	bool visited;
	int distance;
	vertex *previous;
  std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
		void Dijkstra(string sourceVertex, string destinationVertex);
		void build();
    protected:
    private:
        std::vector<vertex> vertices;

};

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.distance = 0;
        v.visited = false;
        v.previous = nullptr;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    cout<<"============================================================"<<endl;
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->"<<endl;
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            cout<<" (distance: "<<vertices[i].adj[j].v->distance
            <<", visited: "<<vertices[i].adj[j].v->visited<<", parent: ";
            if (vertices[i].adj[j].v->previous==nullptr)
              cout<<" nullptr)"<<endl;
            else
              cout<<vertices[i].adj[j].v->previous->name<<")"<<endl;
        }
        cout<<"============================================================"<<endl;
    }
}

void Graph::Dijkstra(string starting, string destination){

    vertex * start = nullptr;
    vertex * ending = nullptr;
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].visited = false;
        vertices[i].distance = INT_MAX;
        vertices[i].previous = nullptr;
        if (vertices[i].name == starting) {
            start = &vertices[i];
        }
        if (vertices[i].name == destination) {
            ending = &vertices[i];
        }
    }
    if (start != nullptr && ending != nullptr)
    {
      start->visited = true;
      start->distance = 0;
      vector<vertex *> solved;
      vector<vertex *> path;
      solved.push_back(start);
      adjVertex * v;
      vertex * u;
      vertex * minVertex;
      vertex * prev;
      while (ending->visited == false) {
        int minDistance = INT_MAX;
        for (int i = 0; i < solved.size(); i++) {
            u = solved[i];
            for (int j = 0; j < u->adj.size(); j++) {
                v = &solved[i]->adj[j];
                if (v->v->visited == false) {
                    int dist = u->distance + v->weight;
                    if (dist < minDistance) {
                        minDistance = dist;
                        minVertex = v->v;
                        prev = u;
                    }
                }
            }

        }
        solved.push_back(minVertex);
        minVertex->distance = minDistance;
        minVertex->previous = prev;
        minVertex->visited = true;
      }
      cout<<"Shortest Path"<<endl;
      vertex * vert = ending;
      while (vert != nullptr) {
          path.push_back(vert);
          vert = vert->previous;
      }
          for (int i = 0; i < path.size(); i++) {
            if (i == path.size()-1)
              cout<<path[path.size()-1-i]->name;
            else
              cout<<path[path.size()-1-i]->name<<" - ";

          }
      cout<<endl;
      cout<<"Minimum Distance: "<<solved[solved.size()-1]->distance<<endl;
  }else if (ending!=nullptr){
    cout<<"start not found"<<endl;
    exit(1);
  }else{
    cout<<"ending not found"<<endl;
    exit(1);
  }
}

void Graph::build(){
    addVertex("O");
    addVertex("A");
    addVertex("B");
    addVertex("C");
    addVertex("D");
    addVertex("E");
    addVertex("F");
    addVertex("G");
    addVertex("H");
    addVertex("I");

    addEdge("O", "B", 1);
    addEdge("O", "A", 1);
    addEdge("O", "C", 1);
    addEdge("A", "B", 1);
    addEdge("A", "D", 1);
    addEdge("B", "C", 1);
    addEdge("B", "E", 1);
    addEdge("C", "F", 1);
    addEdge("D", "E", 1);
  	addEdge("D", "G", 1);
    addEdge("E", "F", 1);
    addEdge("E", "H", 1);
    addEdge("F", "I", 1);
    addEdge("G", "H", 1);
    addEdge("H", "I", 1);

}

int main() {
    Graph g;
    g.build();
    string input;
    string prev;
    queue<string> q;

    cout<<"Enter the locations of passengers waiting to be picked up (x to quit): "<<endl;
    while(input != "x"){
        cin>>input;
        q.push(input);
    }

    g.Dijkstra("O", q.front());
    prev = q.front();
    q.pop();

    while(!q.empty() && q.front() != "x"){
        g.Dijkstra(prev, q.front() );
        prev=q.front();
        q.pop();

    }
    //g.displayEdges();

	  return 0;
}
