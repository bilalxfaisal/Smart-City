// include/utils/Nodes.h
#ifndef NODES_H
#define NODES_H
#include "Stack_Heap_nMORE.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
//String Keys
#include <string>
using namespace std;

inline int Polynomial_Rolling_Hash_V1(const string& str) {
    const long long p = 31;
    const long long m = 1000000009LL;  // 1e9 + 9 (prime)

    long long hash_value = 0;
    long long p_pow = 1;

    for (char c : str) {
        // Safely convert char to non-negative integer (0–255)
        long long char_val = static_cast<unsigned char>(c);

        // Compute: hash += char_val * (p^i)
        hash_value = (hash_value + (char_val * p_pow) % m) % m;

        // Update power: p_pow = p_pow * p mod m
        p_pow = (p_pow * p) % m;
    }

    // Normalize to [0, m-1] — critical for hash table indexing
    hash_value = (hash_value % m + m) % m;

    return static_cast<int>(hash_value);
}

inline int Polynomial_Rolling_Hash_V2(string& str)
{
    const int p = 53;
    const int m = 1e9 + 9;
    int hash_value = 0;
    int p_pow = 1;
    for (char c : str) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return static_cast<int>(hash_value);
}
inline int DJB2_Hash(string& str)
{
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return static_cast<int>(hash);
}

// ==================== FORWARD DECLARATIONS ====================

// Transport entities
class BusStop;
class Bus;
class BusRoute;
class RouteStack;
class TransportCompany;
struct Location {
    int x;
    int y;
};

// Education entities
class Student;
class Class;
class Department;
class School;
class Faculty; // yes needed; 25/11/25 11:58 AM
//well I need some classes for school ke graphs
//So HERE GOES NOTHIN -HADIAH
class edgeSchool;
class schoolGraphNode;
class SchoolGraph;


// Medical entities
class Doctor;
class Patient;
class Medicine;
class Pharmacy;
class Hospital;

// Commercial entities
class Product;
class Mall;
class Store;

// Population entities
class Citizen;
class Family;
class House;
class Street;
class Sector;

// Facility entities
class PublicFacility;
class Mosque;
class Park;
class Library;
// idk what else is called a public facility
// me is stupid

// ==================== NODE STRUCTURES ====================
// the rest of the node structures would go here...





//class edgeSchool
//{
//public:
//    int toIndex; //index of vertex to which it points
//    float weight;
//    //A ptr for next in idk ll adjacency list
//    edgeSchool* next = nullptr;
//    edgeSchool(int toi = 0, float w = 0)
//    {
//        toIndex = toi;
//        weight = w;
//        next = nullptr;
//    }
//
//public:
//};
//
//
//
//
//struct DijkstraEntry
//{
//    int vertex;
//    float dist;
//    DijkstraEntry(int v = -1, float d = 0.0f) : vertex(v), dist(d) {}
//};
//
//// Use your MaxHeap as a min-heap by inverting comparison:
//// return >0 when A.dist < B.dist so the heap treats smallest distance as "max".
//static int DijkstraEntryCmp(void* a, void* b)
//{
//    DijkstraEntry* A = static_cast<DijkstraEntry*>(a);
//    DijkstraEntry* B = static_cast<DijkstraEntry*>(b);
//    if (A->dist < B->dist) return 1;
//    if (A->dist > B->dist) return -1;
//    return 0;
//}
//
//
//
//
//class schoolGraphNode
//{
//public:
//    School* mehSchool = nullptr;
//    edgeSchool* adjList = nullptr;
//
//    schoolGraphNode(School* ms = nullptr, edgeSchool* edg = nullptr)
//    {
//        mehSchool = ms;
//        adjList = edg;
//    }
//};
//class SchoolGraph
//{
//private:
//    //ARRAY  OF EDGES AA IN ZERO OF ONE 
//    schoolGraphNode* VertexArray = nullptr;
//    int capacity = 0;
//    int count = 0;
//
//public:
//    SchoolGraph(int vertices = 10)
//    {
//        if (vertices <= 0)
//        {
//            vertices = 10;
//        }
//        capacity = vertices;
//        VertexArray = new schoolGraphNode[vertices];
//    }
//    void resizeGraph()
//    {
//        int newCapacity = capacity * 2;
//        schoolGraphNode* newArray = new schoolGraphNode[newCapacity];
//        for (int i = 0; i < count; i++)
//        {
//            newArray[i] = VertexArray[i];
//        }
//        delete[] VertexArray;
//        VertexArray = newArray;
//        capacity = newCapacity;
//    }
//    void addSchool(School* newSchool)
//    {
//        if (count == capacity)
//        {
//            resizeGraph();
//        }
//        VertexArray[count] = schoolGraphNode(newSchool);
//        count++;
//    }
//    void addLink(int fromIndex, int toIndex, float weight)
//    {
//        if (fromIndex < 0 || fromIndex >= count || toIndex < 0 || toIndex >= count)
//        {
//            std::cout << "Invalid indices for adding link." << std::endl;
//            return;
//        }
//
//        edgeSchool* newEdge = new edgeSchool(toIndex, weight);
//        newEdge->next = VertexArray[fromIndex].adjList;
//        VertexArray[fromIndex].adjList = newEdge;
//    }
//    void bfs(int start)
//    {
//        myQueue q;
//        bool* visited = new bool[count]();
//        //Locate start
//        if (start < 0 || start>count)
//        {
//            return;
//        }
//        schoolGraphNode st = VertexArray[start];
//        q.enqueue(&st);
//        visited[start] = true;
//        while (!q.isEmpty())
//        {
//            schoolGraphNode* s = (schoolGraphNode*)q.dequeue();
//            if (s == nullptr)
//            {
//                continue;
//            }
//            int idx = int(s - VertexArray); //ASSEMBLY AA
//            if (s->mehSchool)
//            {
//                cout << s->mehSchool->schoolName << " ";
//            }
//            else
//            {
//                cout << "(null) ";
//            }
//            edgeSchool* edg = s->adjList;
//            while (edg)
//            {
//                int to = edg->toIndex;
//                if (to >= 0 && !visited[to])
//                {
//                    q.enqueue(&VertexArray[to]);
//                    visited[to] = true;
//                }
//                edg = edg->next;
//            }
//
//
//
//        }
//        std::cout << std::endl;
//        delete[] visited;
//    }
//
//
//    // Prints distances from src to every vertex;
//    void dijkstra(int src)
//    {
//        if (count == 0)
//        {
//            return;
//        }
//        if (src < 0 || src >= count)
//        {
//            return;
//        }
//
//        const float INF = 1e30f; //infinity aaaaaaaa
//        float* dist = new float[count];
//        int* prev = new int[count];
//        bool* visited = new bool[count]();
//
//        for (int i = 0; i < count; ++i) { dist[i] = INF; prev[i] = -1; visited[i] = false; }
//        dist[src] = 0.0f;
//
//        // Heap capacity: at least 1; more entries may be pushed (stale entries allowed).
//        MaxHeap heap((count > 0 ? count : 1) * 2, DijkstraEntryCmp);
//
//        // push source
//        heap.insert(new DijkstraEntry(src, 0.0f));
//
//        while (!heap.isEmpty())
//        {
//            DijkstraEntry* cur = static_cast<DijkstraEntry*>(heap.extractMax());
//            if (!cur) break;
//
//            int u = cur->vertex;
//            float d = cur->dist;
//            delete cur; // free popped entry
//
//            // If already finalized (visited) skip stale entry.
//            if (visited[u]) continue;
//
//            // If this popped dist is greater than best-known, skip.
//            if (d > dist[u]) continue;
//
//            visited[u] = true;
//
//            edgeSchool* e = VertexArray[u].adjList;
//            while (e)
//            {
//                int v = e->toIndex;
//                float w = e->weight;
//                if (v >= 0 && v < count && !visited[v])
//                {
//                    float nd = dist[u] + w;
//                    if (nd < dist[v])
//                    {
//                        dist[v] = nd;
//                        prev[v] = u;
//                        // push new tentative distance (may create stale entries; handled above)
//                        heap.insert(new DijkstraEntry(v, nd));
//                    }
//                }
//                e = e->next;
//            }
//        }
//
//        // print results
//        cout << "Dijkstra distances from ";
//        if (VertexArray[src].mehSchool) cout << VertexArray[src].mehSchool->schoolName;
//        else cout << "(src)";
//        cout << ":\n";
//
//        for (int i = 0; i < count; ++i)
//        {
//            if (VertexArray[i].mehSchool) cout << VertexArray[i].mehSchool->schoolName << " : ";
//            else cout << "(null) : ";
//
//            if (dist[i] >= INF / 2.0f) cout << "unreachable\n";
//            else cout << dist[i] << "\n";
//        }
//
//        delete[] dist;
//        delete[] prev;
//        delete[] visited;
//    }
//
//    void dfs()
//    {
//        bool* visited = new bool[count]();
//        for (int i = 0; i < count; i)
//        {
//            if (!visited[i])
//            {
//                dfsUtil(i, visited);
//            }
//        }
//        std::cout << std::endl;
//        delete[] visited;
//    }
//    void dfsUtil(int index, bool* visited)
//    {
//        visited[index] = true;
//        schoolGraphNode s = VertexArray[index];
//        if (s.mehSchool)
//        {
//            cout << s.mehSchool->schoolName << " ";
//        }
//        else
//        {
//            cout << "(null) ";
//        }
//        edgeSchool* edg = s.adjList;
//        while (edg)
//        {
//            int to = edg->toIndex;
//            if (to >= 0 && !visited[to])
//            {
//                dfsUtil(to, visited);
//            }
//            edg = edg->next;
//        }
//    }
//
//
//
//
//
//
//};


#endif