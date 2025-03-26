# Environment-Friendly Route Planning

This project is a graph-based route planning system designed to simulate and analyze city navigation. It offers walking, driving, and hybrid (multi-modal) routing capabilities while allowing restrictions such as blocked paths and required stop points.

It was developed for academic purposes as part of the DA (Design and Analysis of Algorithms) course at FEUP.

## Features

- Load city data from CSV files (locations and distances)
- Walking, driving, or hybrid routing options
- Environment-friendly route planning
- Ability to avoid nodes and segments dynamically
- Multi-stop route computation (with required intermediate locations)
- Interactive, menu-driven command-line interface
- Efficient algorithms based on Dijkstra's algorithm


- ### Documentation

  - Inside the **'docs/html'** folder, find **index.html** and open with browser to access the full documentation of the project

## Project Structure

- ├── src/ # Source code, organized by module │ 
   - ├── algorithm/ # Dijkstra
   - ├── data_handling/ # CSVReader │ 
   - ├── data_structures/ # Graph, Vertex, Edge, Location, Mutable Priority Queue │ 
   - ├── route_planning/ # Route logics │ 
   - ├── ui/ # Menu system
   - ├── utils/ # Utility functions
   - main.cpp # Entry point of the program
- ├── data/ # CSV input files 
- ├── docs/ # Doxygen configuration and output │ 
  - └── html/ # Generated HTML documentation

## How to Compile and Run

### Requirements

- CMake 3.30 or higher
- A C++20-compatible compiler

### Building the Project

#### With Clion

Build and run the project

#### Without Clion

From the project root directory, run the following commands:

```bash
cmake -S . -B build
cmake --build build
./build/DA
