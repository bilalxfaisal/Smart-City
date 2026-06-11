# Smart City — Islamabad Simulation System

A terminal-based C++ simulation of a smart city modelled on Islamabad. The system manages six city subsystems — transport, commercial, education, medical, public facilities, and population — all connected through a shared location graph. It includes an SFML-powered interactive city map visualizer with heatmap support and a Dijkstra-based shortest path finder that works across any two locations in the city.

No STL containers are used. All data structures — linked lists, hash tables, stacks, queues, min-heap, max-heap, graphs, and trees — are implemented from scratch.

---

## Features

**Main Menu**

From the main menu you can enter any of the six subsystems, visualize the full city map, find the shortest path between any two locations, or search for a specific location by name or type.

**Transport System**

Add transport companies, define bus routes, assign bus stops to routes, and attach buses to companies. Simulates bus movement along routes. Bus stops are stored in a graph structure with adjacency lists, and routes are stored in a hash table keyed by route name. You can display the status of any company or visualize the full transport network.

**Commercial System**

Add malls, add stores to malls, organize products into categories within stores, search for products, and simulate a purchase. Malls are stored in a hash table using the Polynomial Rolling Hash. Stores within a mall use a separate hash table keyed by store name.

**Education System**

Add schools, departments within schools, classes within departments, faculty members, students, and subjects. Schools are organized as an n-ary tree. Students can be removed by name or ID and faculty members can be removed by ID. All school locations are registered in the shared city location graph.

**Medical System**

Add and remove hospitals and pharmacies. Add and remove doctors and patients from specific hospitals. Add and remove medicines from pharmacies. Hospitals are stored in a max-heap ordered by bed capacity for priority-based access. The medical subgraph connects hospitals and pharmacies in the city location graph.

**Public Facility System**

Add mosques, parks, and water coolers. Display all facilities by type. A dedicated visualizer shows the spatial distribution of public facilities across the city.

**Population System**

Add sectors, streets within sectors, houses within streets, and citizens within houses. Citizens are stored in a hash table keyed by CNIC for O(1) lookup. Search for any individual by CNIC. Generate reports on age distribution, occupation summary, and population density across sectors. Display all members of a house, all houses on a street, or a full listing of all sectors.

**Shortest Path Finder**

Find the shortest route between any two locations in the city — sectors (e.g., F-8, G-8), landmarks (e.g., BlueArea, Centaurus), hospitals, schools, malls, bus stops, or houses. Supports a normal mode that considers traffic weights and an emergency mode that applies a 60% speed boost with priority lanes. Uses Dijkstra's algorithm implemented with a custom min-heap. The found path can optionally be visualized on the city map.

**City Map Visualizer**

An SFML window renders the full Islamabad sector grid (sectors D-5 through J-12). Left-click zooms into any sector to see its locations. Right-click zooms back out. Press H to toggle heatmap mode, which colours sectors by population density from green (low) to red (high). Press Enter to exit heatmap mode.

**CSV Import**

Hospitals, pharmacies, schools, and bus stops can be bulk-loaded from CSV files instead of manual entry. The CSV handler parses files including quoted fields and maps each record into the appropriate system.

---

## Data Structures Used

All implemented from scratch with no STL containers.

- Linked lists: location graph nodes, bus stop lists, hospital/pharmacy lists, route lists
- Hash tables with chaining: transport companies, bus routes, malls, stores, sectors, citizens
- Polynomial Rolling Hash (two variants) and DJB2 hash for string keys; Golden Ratio hash for integer keys
- Min-heap: Dijkstra's priority queue in LocationManager
- Max-heap: hospital priority ordering in MedicalSystem
- Custom stack (myStack) and queue (myQueue) with void* generics
- Graph with adjacency lists: city location graph (intersections, hospitals, schools, malls, bus stops, houses), bus stop subgraph, transport subgraph, medical subgraph, commercial subgraph
- N-ary tree: school hierarchy (school → department → class)

---

## Build Requirements

- C++17 or later
- SFML 2.x (for the visualizer)
- A C++ compiler such as g++ or MSVC

The visualizer depends on SFML. If you only want the terminal simulation without the map window, the SFML dependency can be removed by stripping the visualizer include from Run.h.

---

## How to Run

Compile with SFML linked:

```bash
g++ main.cpp -o SmartCity -lsfml-graphics -lsfml-window -lsfml-system
./SmartCity
```

---

## Collaborators

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/Hashimk101">
        <img src="https://github.com/Hashimk101.png" width="80" style="border-radius:50%" /><br/>
        <b>Hashim Khushal Khan</b>
      </a><br/>
      <a href="https://github.com/Hashimk101">@Hashimk101</a>
    </td>
    <td align="center">
      <a href="https://github.com/Hadiah-Batool">
        <img src="https://github.com/Hadiah-Batool.png" width="80" style="border-radius:50%" /><br/>
        <b>Hadiah Batool</b>
      </a><br/>
      <a href="https://github.com/Hadiah-Batool">@Hadiah-Batool</a>
    </td>
    <td align="center">
      <a href="https://github.com/bilalxfaisal">
        <img src="https://github.com/bilalxfaisal.png" width="80" style="border-radius:50%" /><br/>
        <b>Muhammad Bilal Faisal</b>
      </a><br/>
      <a href="https://github.com/bilalxfaisal">@bilalxfaisal</a>
    </td>
  </tr>
</table>

---
