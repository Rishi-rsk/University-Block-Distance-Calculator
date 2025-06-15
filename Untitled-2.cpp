#include <iostream> 
#include <vector> 
#include <queue> 
#include <limits> 
#include <iomanip> 
#include <unordered_map> 
using namespace std; 
 
struct Edge { 
    int destination; 
    double weight; 
}; 
 
class Graph { 
private: 
    vector<vector<Edge>> adjacencyList; 
    unordered_map<string, int> blockMapping; 
    unordered_map<int, string> reverseMapping; 
 
public: 
    Graph() { 
         
        vector<string> blocks = {"A", "B", "C", "D", "E", "F", "G", "H", "AI"}; 
        for (int i = 0; i < blocks.size(); i++) { 
            blockMapping[blocks[i]] = i; 
            reverseMapping[i] = blocks[i]; 
        } 
        adjacencyList.resize(blocks.size()); 
 
         
        addEdge("A", "B", 10.5); 
        addEdge("A", "C", 15.2); 
        addEdge("B", "D", 8.3); 
        addEdge("C", "E", 12.7); 
        addEdge("D", "F", 7.9); 
    } 
 
    void addEdge(const string& source, const string& destination, double weight) { 
        int srcIndex = blockMapping[source]; 
        int destIndex = blockMapping[destination]; 
        adjacencyList[srcIndex].push_back({destIndex, weight}); 
        adjacencyList[destIndex].push_back({srcIndex, weight});  
    } 
 
    vector<double> dijkstra(const string& source) { 
        int srcIndex = blockMapping[source]; 
        int n = adjacencyList.size(); 
        vector<double> distances(n, numeric_limits<double>::max()); 
        distances[srcIndex] = 0; 
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq; 
        pq.push({0, srcIndex}); 
 
        while (!pq.empty()) { 
            double currentDistance = pq.top().first; 
            int currentNode = pq.top().second; 
            pq.pop(); 
 
            if (currentDistance > distances[currentNode]) 
                continue; 
 
            for (auto& edge : adjacencyList[currentNode]) { 
                double newDistance = currentDistance + edge.weight; 
                if (newDistance < distances[edge.destination]) { 
                    distances[edge.destination] = newDistance; 
                    pq.push({newDistance, edge.destination}); 
                } 
            } 
        } 
 
        return distances; 
    } 
 
    double greedyShortestPath(const string& source, const string& destination) { 
        int srcIndex = blockMapping[source]; 
        int destIndex = blockMapping[destination]; 
        vector<bool> visited(adjacencyList.size(), false); 
        double totalDistance = 0; 
        int current = srcIndex; 
 
        while (current != destIndex) { 
            visited[current] = true; 
            double minDistance = numeric_limits<double>::max(); 
            int nextNode = -1; 
 
            for (auto& edge : adjacencyList[current]) { 
                if (!visited[edge.destination] && edge.weight < minDistance) { 
                    minDistance = edge.weight; 
                    nextNode = edge.destination; 
                } 
            } 
 
            if (nextNode == -1) { 
                cout << "No path found between the blocks!\n"; 
                return -1; 
            } 
 
            totalDistance += minDistance; 
            current = nextNode; 
        } 
 
        return totalDistance; 
    } 
 
    void printGraph() { 
        for (int i = 0; i < adjacencyList.size(); i++) { 
            cout << "Block " << reverseMapping[i] << " connects to: "; 
            for (auto& edge : adjacencyList[i]) { 
                cout << "(Block " << reverseMapping[edge.destination] << " with distance " << edge.weight 
<< ") "; 
            } 
            cout << endl; 
        } 
    } 
 
    string getBlockName(int index) { 
        return reverseMapping[index]; 
    } 
}; 
 
int main() { 
    cout << "--- Shoolini University Block Distance Calculator ---\n"; 
 
    Graph graph; 
 
    cout << "\n--- Adjacency List of the Graph ---\n"; 
    graph.printGraph(); 
 
    cout << "\n--- Menu ---\n"; 
    cout << "1. Calculate shortest path using Dijkstra\n"; 
    cout << "2. Calculate approximate path using Greedy Algorithm\n"; 
    cout << "Enter your choice: "; 
 
    int choice; 
    cin >> choice; 
 
    if (choice == 1) { 
        string source; 
        cout << "Enter the source block: "; 
        cin >> source; 
 
        vector<double> distances = graph.dijkstra(source); 
        cout << "\nShortest distances from Block " << source << ":\n"; 
        cout << fixed << setprecision(2); 
        for (int i = 0; i < distances.size(); i++) { 
            cout << "To Block " << graph.getBlockName(i) << ": " << distances[i] << " meters\n"; 
        } 
    } else if (choice == 2) { 
        string source, destination; 
        cout << "Enter the source block: "; 
        cin >> source; 
        cout << "Enter the destination block: "; 
        cin >> destination; 
 
        double distance = graph.greedyShortestPath(source, destination); 
        if (distance != -1) { 
cout << fixed << setprecision(2); 
cout << "Approximate distance from Block " << source << " to Block " << destination << ": " << 
distance << " meters\n"; 
} 
} else { 
cout << "Invalid choice! Please restart the program.\n"; 
} 
return 0; 
}