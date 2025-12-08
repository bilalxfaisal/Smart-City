#include "../utils/Nodes.h"
#include "Mall.h"
#ifndef COMMERCIALSYSTEM_H
#define COMMERCIALSYSTEM_H
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class CommercialSystem
{
private:
    Mall** mallsTable;
    int mallCount;
    int mallTableSize;
	Location* headMallLocation = nullptr;

public:

	CommercialSystem() {
		mallCount = 0;
		mallTableSize = 100;
		mallsTable = new Mall * [mallTableSize]();
		for (int i = 0; i < mallTableSize; i++) {
			mallsTable[i] = nullptr;
		}
	}
    // Add to CommercialSystem class public section:

    void connectMallsSubgraph() {
        cout << "\n[INFO] Connecting malls subgraph...\n";

        if (!headMallLocation) {
            cout << "[WARNING] No malls to connect.\n";
            return;
        }

        int connectedCount = 0;
        Location* m1 = headMallLocation;

        while (m1) {
            Location* m2 = headMallLocation;
            while (m2) {
                if (m1 != m2) {
                    float dist = sqrt(
                        pow(m2->x - m1->x, 2) +
                        pow(m2->y - m1->y, 2)
                    );

                    // Connect malls within 300 units
                    if (dist < 300.0f && dist > 0) {
                        bool edgeExists = false;
                        Edge* e = m1->adjList;
                        while (e) {
                            if (e->destination == m2) {
                                edgeExists = true;
                                break;
                            }
                            e = e->nextEdge;
                        }

                        if (!edgeExists) {
                            Edge* newEdge1 = new Edge(dist, m2);
                            newEdge1->nextEdge = m1->adjList;
                            m1->adjList = newEdge1;

                            Edge* newEdge2 = new Edge(dist, m1);
                            newEdge2->nextEdge = m2->adjList;
                            m2->adjList = newEdge2;

                            connectedCount++;
                        }
                    }
                }
                m2 = m2->next;
            }
            m1 = m1->next;
        }

        cout << "[SUCCESS] Connected " << connectedCount << " mall pairs.\n";
    }

    // Find shortest path between two malls
    PathNode* findShortestPathBetweenMalls(string mall1Name, string mall2Name) {
        // Find malls
        int idx1 = Polynomial_Rolling_Hash_V1(mall1Name) % mallTableSize;
        int idx2 = Polynomial_Rolling_Hash_V1(mall2Name) % mallTableSize;

        Mall* m1 = mallsTable[idx1];
        while (m1 && m1->getMallName() != mall1Name) {
            m1 = m1->nextMall;
        }

        Mall* m2 = mallsTable[idx2];
        while (m2 && m2->getMallName() != mall2Name) {
            m2 = m2->nextMall;
        }

        if (!m1 || !m2) {
            cout << "[ERROR] One or both malls not found.\n";
            return nullptr;
        }

        Location* start = &(m1->getLocation());
        Location* end = &(m2->getLocation());

        // Reset graph
        Location* loc = headMallLocation;
        while (loc) {
            loc->minDist = std::numeric_limits<float>::max();
            loc->visited = false;
            loc->parent = nullptr;
            loc = loc->next;
        }

        // Dijkstra
        MinHeap pq(1000);
        start->minDist = 0;
        pq.push(start, 0);

        while (!pq.isEmpty()) {
            Location* u = pq.extractMin();
            if (u == end) break;
            if (u->visited) continue;
            u->visited = true;

            Edge* e = u->adjList;
            while (e) {
                Location* v = e->destination;
                float weight = e->weight;
                if (!v->visited && u->minDist + weight < v->minDist) {
                    v->minDist = u->minDist + weight;
                    v->parent = u;
                    pq.push(v, v->minDist);
                }
                e = e->nextEdge;
            }
        }

        if (end->minDist == std::numeric_limits<float>::max()) {
            cout << "[ERROR] No path found between malls.\n";
            return nullptr;
        }

        // Build path
        PathNode* pathHead = nullptr;
        Location* crawler = end;
        while (crawler) {
            PathNode* newNode = new PathNode(crawler);
            newNode->next = pathHead;
            pathHead = newNode;
            crawler = crawler->parent;
        }

        return pathHead;
    }

	void resizeMallMap() 
	{
		int newSize = mallTableSize * 2;
		Mall** newTable = new Mall * [newSize]();
		for (int i = 0; i < newSize; i++) {
			newTable[i] = nullptr;
		}
		for (int i = 0; i < mallTableSize; i++) {
			Mall* current = mallsTable[i];
			while (current != nullptr) {
				Mall* nextMall = current->nextMall;
				int index = Polynomial_Rolling_Hash_V1(current->getMallName()) % newSize;
				if (newTable[index]) {
					current->nextMall = newTable[index];
					newTable[index] = current;
				}
				else {
					current->nextMall = nullptr;
					newTable[index] = current;
				}
				current = nextMall;
			}
		}
		delete[] mallsTable;
		mallsTable = newTable;
		mallTableSize = newSize;
	}
    bool addMall(Mall& m1)
    {
        Mall* toAdd = new Mall(m1);
        if (mallCount >= mallTableSize)
        {
            resizeMallMap();
		}

		// add Location to location list for graph
		addLocationToLinkedList(toAdd->getLocation());

        int index = Polynomial_Rolling_Hash_V1(toAdd->getMallName());
        index = index % mallTableSize;
        if (mallsTable[index])
        {
            toAdd->nextMall = mallsTable[index];
            mallsTable[index] = toAdd;
            return true;
        }
        else
        {
            mallsTable[index] = toAdd;
            mallCount++;
            return true;
        }
        return false;
    }

    void deleteMall(string& mallName) {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        if (mallsTable[index] == nullptr) return;

        Mall* current = mallsTable[index];
        Mall* previous = nullptr;

        while (current != nullptr) {
            if (current->getMallName() == mallName) {
				// delete location from linked list
				removeLocationFromLinkedList(current->getLocation());
                if (previous == nullptr) {
                    mallsTable[index] = current->nextMall;
                }
                else {
                    previous->nextMall = current->nextMall;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
    }

    bool addStoreToMall(string& mallName, Store& store)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                current->addStore(store);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    bool addCategoryToStoreInMall(string mallName, string storeName, string categoryName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->addCategoryToStore(storeName, categoryName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    bool removeStoreFromMall(string& mallName, string& storeName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                current->removeStore(storeName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }
    bool addProductToStore(string& mallName, string& storeName, string& categoryName, Product& product)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->addProductToStore(storeName, categoryName, product);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found.";
        return false;
    }
    bool removeProduct(string& mallName, string& storeName, string& categoryName, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->removeProductFromStore(storeName, categoryName, productName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    void findProductInStore(string& mallName, string& storeName, string& category, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                Product* prod = current->findProductInStore(storeName, category, productName);
                if (prod) {
                    cout << "Product found: ";
                    prod->displayProduct();
                }
                else {
                    cout << "Product not found in the specified store and category." << endl;
                }
                return;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
    }

    void displayProductsInMallFromStore(string mallName, string storeName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                current->displayProductsInStore(storeName);
                return;
            }
            current = current->nextMall;
        }
        cout << "Mall not found." << endl;
        return;
    }

    void displayAllProductsInCategoryFromStore(string& mallName, string& storeName, string& category)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                current->displayProductsInStoreFromCategory(storeName, category);
                return;
            }
            current = current->nextMall;
        }
        cout << "Mall not found." << endl;
        return;
    }

    bool buyProduct(string& mallName, string& storeName, string& category, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                bool success = current->buyProductFromStore(storeName, category, productName);
                if (success)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    void addLocationToLinkedList(Location& mallLocation) {
        // Ensure the location doesn't already exist in the list
        Location* temp = headMallLocation;
        while (temp) {
            if (temp == &mallLocation) {
                // Already in list, don't add again
                return;
            }
            temp = temp->next;
        }

        // Add to beginning of list (more efficient than traversing to end)
        mallLocation.next = headMallLocation;
        headMallLocation = &mallLocation;
    }

    void removeLocationFromLinkedList(Location& mallLocation) {
        if (!headMallLocation) return;
        
        // Check if it's the head
        if (headMallLocation == &mallLocation) {
            headMallLocation = headMallLocation->next;
            mallLocation.next = nullptr; // Clean up the removed node
            return;
        }
        
        // Search for the location
        Location* temp = headMallLocation;
        while (temp->next) {
            if (temp->next == &mallLocation) {
                temp->next = mallLocation.next;
                mallLocation.next = nullptr; // Clean up the removed node
                return;
            }
            temp = temp->next;
        }
        
        // Location not found - could log this for debugging
        // cout << "Warning: Location not found in list\n";
	}

    Location* getMallLocationHead() {
        return headMallLocation;
	}
    void display() const {
        cout << "=== Commercial System ===" << endl;
        cout << "Total Malls: " << mallCount << endl;

        for (int i = 0; i < mallTableSize; i++) {
            if (mallsTable[i] != nullptr) {
                Mall* current = mallsTable[i];
                while (current != nullptr) {
                    current->displayMall();
					current->getLocation().display(); // Display mall location
                    current = current->nextMall; // Move to next mall
                }
            }
        }
        cout << "==========================" << endl;
    }
};
#endif // !COMMERCIALSYSTEM_H
