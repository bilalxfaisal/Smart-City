#include "SFML/Graphics.hpp"
#include "include/visualizer/Visualizer.h"
#include <cmath>

// Helper function to calculate Euclidean distance
float calculateDistance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

// Function to create a small simulated graph with schools and intersections
Location* createSimulatedGraph() {
    const int SECTOR_SIZE = 90;
    const int START_X = 80;
    const int START_Y = 50;

    Location* head = nullptr;

    // === Create some intersections (corners) ===

    // F-8 corners (sector at row 2, col 3)
    Location* f8_tl = new Location(START_X + 3 * SECTOR_SIZE, START_Y + 2 * SECTOR_SIZE,
        "F8-TopLeft", "Intersection");
    Location* f8_tr = new Location(START_X + 4 * SECTOR_SIZE, START_Y + 2 * SECTOR_SIZE,
        "F8-TopRight", "Intersection");
    Location* f8_bl = new Location(START_X + 3 * SECTOR_SIZE, START_Y + 3 * SECTOR_SIZE,
        "F8-BottomLeft", "Intersection");
    Location* f8_br = new Location(START_X + 4 * SECTOR_SIZE, START_Y + 3 * SECTOR_SIZE,
        "F8-BottomRight", "Intersection");

    // G-9 corners (sector at row 3, col 4)
    Location* g9_tl = new Location(START_X + 4 * SECTOR_SIZE, START_Y + 3 * SECTOR_SIZE,
        "G9-TopLeft", "Intersection");
    Location* g9_tr = new Location(START_X + 5 * SECTOR_SIZE, START_Y + 3 * SECTOR_SIZE,
        "G9-TopRight", "Intersection");
    Location* g9_bl = new Location(START_X + 4 * SECTOR_SIZE, START_Y + 4 * SECTOR_SIZE,
        "G9-BottomLeft", "Intersection");
    Location* g9_br = new Location(START_X + 5 * SECTOR_SIZE, START_Y + 4 * SECTOR_SIZE,
        "G9-BottomRight", "Intersection");

    // E-7 corners (sector at row 1, col 2)
    Location* e7_tl = new Location(START_X + 2 * SECTOR_SIZE, START_Y + 1 * SECTOR_SIZE,
        "E7-TopLeft", "Intersection");
    Location* e7_tr = new Location(START_X + 3 * SECTOR_SIZE, START_Y + 1 * SECTOR_SIZE,
        "E7-TopRight", "Intersection");
    Location* e7_bl = new Location(START_X + 2 * SECTOR_SIZE, START_Y + 2 * SECTOR_SIZE,
        "E7-BottomLeft", "Intersection");
    Location* e7_br = new Location(START_X + 3 * SECTOR_SIZE, START_Y + 2 * SECTOR_SIZE,
        "E7-BottomRight", "Intersection");

    // === Create some schools ===

    // PIMS in F-8 (middle of sector)
    Location* pims = new Location(START_X + 3 * SECTOR_SIZE + 45, START_Y + 2 * SECTOR_SIZE + 45,
        "PIMS", "School");

    // Islamabad College in G-9
    Location* ic = new Location(START_X + 4 * SECTOR_SIZE + 50, START_Y + 3 * SECTOR_SIZE + 50,
        "Islamabad College", "School");

    // Beaconhouse in E-7
    Location* beaconhouse = new Location(START_X + 2 * SECTOR_SIZE + 40, START_Y + 1 * SECTOR_SIZE + 40,
        "Beaconhouse", "School");

    // === Build the linked list ===
    head = f8_tl;
    f8_tl->next = f8_tr;
    f8_tr->next = f8_bl;
    f8_bl->next = f8_br;
    f8_br->next = g9_tl;
    g9_tl->next = g9_tr;
    g9_tr->next = g9_bl;
    g9_bl->next = g9_br;
    g9_br->next = e7_tl;
    e7_tl->next = e7_tr;
    e7_tr->next = e7_bl;
    e7_bl->next = e7_br;
    e7_br->next = pims;
    pims->next = ic;
    ic->next = beaconhouse;
    beaconhouse->next = nullptr;

    // === Create edges (connections) ===

    // F-8 square connections
    float dist;

    dist = calculateDistance(f8_tl->x, f8_tl->y, f8_tr->x, f8_tr->y);
    f8_tl->addEdge(f8_tr, dist);
    f8_tr->addEdge(f8_tl, dist);

    dist = calculateDistance(f8_tl->x, f8_tl->y, f8_bl->x, f8_bl->y);
    f8_tl->addEdge(f8_bl, dist);
    f8_bl->addEdge(f8_tl, dist);

    dist = calculateDistance(f8_tr->x, f8_tr->y, f8_br->x, f8_br->y);
    f8_tr->addEdge(f8_br, dist);
    f8_br->addEdge(f8_tr, dist);

    dist = calculateDistance(f8_bl->x, f8_bl->y, f8_br->x, f8_br->y);
    f8_bl->addEdge(f8_br, dist);
    f8_br->addEdge(f8_bl, dist);

    // G-9 square connections (note: g9_tl is same as f8_br)
    dist = calculateDistance(g9_tl->x, g9_tl->y, g9_tr->x, g9_tr->y);
    g9_tl->addEdge(g9_tr, dist);
    g9_tr->addEdge(g9_tl, dist);

    dist = calculateDistance(g9_tl->x, g9_tl->y, g9_bl->x, g9_bl->y);
    g9_tl->addEdge(g9_bl, dist);
    g9_bl->addEdge(g9_tl, dist);

    dist = calculateDistance(g9_tr->x, g9_tr->y, g9_br->x, g9_br->y);
    g9_tr->addEdge(g9_br, dist);
    g9_br->addEdge(g9_tr, dist);

    dist = calculateDistance(g9_bl->x, g9_bl->y, g9_br->x, g9_br->y);
    g9_bl->addEdge(g9_br, dist);
    g9_br->addEdge(g9_bl, dist);

    // E-7 square connections
    dist = calculateDistance(e7_tl->x, e7_tl->y, e7_tr->x, e7_tr->y);
    e7_tl->addEdge(e7_tr, dist);
    e7_tr->addEdge(e7_tl, dist);

    dist = calculateDistance(e7_tl->x, e7_tl->y, e7_bl->x, e7_bl->y);
    e7_tl->addEdge(e7_bl, dist);
    e7_bl->addEdge(e7_tl, dist);

    dist = calculateDistance(e7_tr->x, e7_tr->y, e7_br->x, e7_br->y);
    e7_tr->addEdge(e7_br, dist);
    e7_br->addEdge(e7_tr, dist);

    dist = calculateDistance(e7_bl->x, e7_bl->y, e7_br->x, e7_br->y);
    e7_bl->addEdge(e7_br, dist);
    e7_br->addEdge(e7_bl, dist);

    // Connect E-7 to F-8 (they share an edge)
    dist = calculateDistance(e7_br->x, e7_br->y, f8_tl->x, f8_tl->y);
    e7_br->addEdge(f8_tl, dist);
    f8_tl->addEdge(e7_br, dist);

    dist = calculateDistance(e7_tr->x, e7_tr->y, f8_tl->x, f8_tl->y);
    e7_tr->addEdge(f8_tl, dist);
    f8_tl->addEdge(e7_tr, dist);

    // Connect schools to nearby intersections

    // PIMS to F-8 corners
    dist = calculateDistance(pims->x, pims->y, f8_tl->x, f8_tl->y);
    pims->addEdge(f8_tl, dist);
    f8_tl->addEdge(pims, dist);

    dist = calculateDistance(pims->x, pims->y, f8_tr->x, f8_tr->y);
    pims->addEdge(f8_tr, dist);
    f8_tr->addEdge(pims, dist);

    dist = calculateDistance(pims->x, pims->y, f8_bl->x, f8_bl->y);
    pims->addEdge(f8_bl, dist);
    f8_bl->addEdge(pims, dist);

    dist = calculateDistance(pims->x, pims->y, f8_br->x, f8_br->y);
    pims->addEdge(f8_br, dist);
    f8_br->addEdge(pims, dist);

    // Islamabad College to G-9 corners
    dist = calculateDistance(ic->x, ic->y, g9_tl->x, g9_tl->y);
    ic->addEdge(g9_tl, dist);
    g9_tl->addEdge(ic, dist);

    dist = calculateDistance(ic->x, ic->y, g9_tr->x, g9_tr->y);
    ic->addEdge(g9_tr, dist);
    g9_tr->addEdge(ic, dist);

    dist = calculateDistance(ic->x, ic->y, g9_bl->x, g9_bl->y);
    ic->addEdge(g9_bl, dist);
    g9_bl->addEdge(ic, dist);

    dist = calculateDistance(ic->x, ic->y, g9_br->x, g9_br->y);
    ic->addEdge(g9_br, dist);
    g9_br->addEdge(ic, dist);

    // Beaconhouse to E-7 corners
    dist = calculateDistance(beaconhouse->x, beaconhouse->y, e7_tl->x, e7_tl->y);
    beaconhouse->addEdge(e7_tl, dist);
    e7_tl->addEdge(beaconhouse, dist);

    dist = calculateDistance(beaconhouse->x, beaconhouse->y, e7_tr->x, e7_tr->y);
    beaconhouse->addEdge(e7_tr, dist);
    e7_tr->addEdge(beaconhouse, dist);

    dist = calculateDistance(beaconhouse->x, beaconhouse->y, e7_bl->x, e7_bl->y);
    beaconhouse->addEdge(e7_bl, dist);
    e7_bl->addEdge(beaconhouse, dist);

    dist = calculateDistance(beaconhouse->x, beaconhouse->y, e7_br->x, e7_br->y);
    beaconhouse->addEdge(e7_br, dist);
    e7_br->addEdge(beaconhouse, dist);

    // Connect PIMS to Islamabad College (direct school-to-school connection)
    dist = calculateDistance(pims->x, pims->y, ic->x, ic->y);
    pims->addEdge(ic, dist);
    ic->addEdge(pims, dist);

    return head;
}

int main() {
    // Create simulated graph with schools and intersections
    Location* locationHead = createSimulatedGraph();

    // Create visualizer and set the data
    Visualizer viz;
    viz.setLocationHead(locationHead);

    // Run the visualization (handles window, events, rendering)
    viz.run();

    // Cleanup
    Location* curr = locationHead;
    while (curr) {
        Location* next = curr->next;

        // Delete edges
        Edge* edge = curr->adjList;
        while (edge) {
            Edge* nextEdge = edge->nextEdge;
            delete edge;
            edge = nextEdge;
        }

        delete curr;
        curr = next;
    }

    return 0;
}