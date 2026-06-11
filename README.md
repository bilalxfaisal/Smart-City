<div align="center">

# Smart City
### Islamabad Urban Simulation System

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.x-8CC445?style=for-the-badge&logo=sfml&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Status](https://img.shields.io/badge/Status-Active-2E7D32?style=for-the-badge)
![Contributors](https://img.shields.io/badge/Contributors-3-0097A7?style=for-the-badge&logo=github&logoColor=white)

*A terminal-based C++ simulation of a smart city modelled on Islamabad,*
*managing six urban subsystems through a shared location graph with an SFML interactive city map.*

[Features](#features) · [Subsystems](#subsystems) · [Data Structures](#data-structures) · [Quick Start](#quick-start) · [Team](#team)

</div>

---

## Overview

**Smart City** is a terminal-based C++ simulation of a smart city modelled on Islamabad. It manages six city subsystems — transport, commercial, education, medical, public facilities, and population — all connected through a shared location graph. It includes an SFML-powered interactive city map with heatmap support and a Dijkstra-based shortest path finder that works across any two locations in the city.

No STL containers are used. Every data structure — linked lists, hash tables, stacks, queues, min-heap, max-heap, graphs, and trees — is implemented from scratch.

> Built as a team project by 3 contributors as part of a Data Structures course at FAST NUCES Islamabad.

---

## Features

### Shortest Path Finder
- Dijkstra's algorithm with a custom min-heap
- Works between any two city locations — sectors, hospitals, schools, malls, bus stops, houses
- Normal mode and Emergency mode with a 60% speed boost and priority lanes
- Found path can be visualized directly on the city map

### SFML City Map Visualizer
- Full Islamabad sector grid rendered in an interactive window (sectors D-5 through J-12)
- Left-click to zoom into any sector and see its locations
- Right-click to zoom back out
- Press H to toggle population heatmap — sectors colour from green (low) to red (high density)

### Global Search and Location Lookup
- Search any location by name or type across the entire city graph
- Results linked back to the subsystem they belong to

### CSV Bulk Import
- Hospitals, pharmacies, schools, and bus stops can be bulk-loaded from CSV files
- Parser handles quoted fields and maps records directly into the appropriate subsystem

---

## Subsystems

| Subsystem | Description |
|-----------|-------------|
| Transport | Companies, bus routes, bus stops, buses, route simulation |
| Commercial | Malls, stores, product categories, product search and purchase |
| Education | Schools, departments, classes, faculty, students — organized as an n-ary tree |
| Medical | Hospitals and pharmacies with doctor and patient management — max-heap ordered by bed capacity |
| Public Facilities | Mosques, parks, water coolers with spatial distribution visualizer |
| Population | Sectors, streets, houses, citizens — CNIC-keyed hash table with age, occupation, and density reports |

---

## Data Structures

All implemented from scratch with no STL containers.

| Structure | Used For |
|-----------|----------|
| Linked Lists | Location graph nodes, bus stop lists, hospital and pharmacy lists |
| Hash Tables with Chaining | Transport companies, bus routes, malls, stores, sectors, citizens |
| Polynomial Rolling Hash / DJB2 / Golden Ratio Hash | String and integer key hashing |
| Min-Heap | Dijkstra's priority queue in the location manager |
| Max-Heap | Hospital priority ordering by bed capacity |
| Custom Stack and Queue | Generic void* implementations used across subsystems |
| Graph with Adjacency Lists | City location graph, bus stop subgraph, transport, medical, and commercial subgraphs |
| N-ary Tree | School hierarchy — school, department, class |

---

## Quick Start

Compile with SFML linked:

```bash
git clone https://github.com/bilalxfaisal/Smart-City.git
cd Smart-City
g++ main.cpp -o SmartCity -lsfml-graphics -lsfml-window -lsfml-system
./SmartCity
```

On Windows, link the SFML .lib files and place the SFML .dll files in the same directory as the executable.

Navigate using the numbered menus. Enter 0 at any submenu to return to the main menu.

---

## Built With

- **[C++17](https://isocpp.org/)** — Core language
- **[SFML 2.x](https://www.sfml-dev.org/)** — Interactive city map visualizer
- **[CMake](https://cmake.org/)** — Build system

---

## Team

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/bilalxfaisal">
        <img src="https://github.com/bilalxfaisal.png" width="80" style="border-radius:50%" /><br/>
        <b>Muhammad Bilal Faisal</b>
      </a><br/>
      <a href="https://github.com/bilalxfaisal">@bilalxfaisal</a>
    </td>
    <td align="center">
      <a href="https://github.com/HashimK101">
        <img src="https://github.com/HashimK101.png" width="80" style="border-radius:50%" /><br/>
        <b>Hashim Khushal Khan</b>
      </a><br/>
      <a href="https://github.com/HashimK101">@HashimK101</a>
    </td>
    <td align="center">
      <a href="https://github.com/Hadiah-Batool">
        <img src="https://github.com/Hadiah-Batool.png" width="80" style="border-radius:50%" /><br/>
        <b>Hadiah Batool</b>
      </a><br/>
      <a href="https://github.com/Hadiah-Batool">@Hadiah-Batool</a>
    </td>
  </tr>
</table>

---

<div align="center">

*Built as a collaborative team project demonstrating custom data structures,*
*graph algorithms, and real-time visualization in C++.*

</div>
