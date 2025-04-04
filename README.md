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
```

### Running the Program

To run the program use:

```bash
./build/DA
```

Once the program starts, you'll be presented with an interactive, menu-driven command-line interface.

```
Route Planning Analysis Tool Menu:
1. Print All Locations
2. Independent Route Planning
3. Restricted Route Planning
4. Environmentally-Friendly Route Planning
0. Exit
Enter your choice:
```

You can enter the number for the option that you want.

#### Option 1: Print All Locations

This option will display a list of all the available locations in the graph.

#### Option 2: Independent Route Planning

You can plan a route between two locations, with no restrictions applied. You’ll be prompted for a starting location and destination.

#### Option 3: Restricted Route Planning

You can plan a route with specific restrictions such as blocked paths or mandatory stop points. You’ll be asked for the details of these restrictions.

#### Option 4: Environmentally-Friendly Route Planning

Plan a route that combines both driving and walking. This functionality allows users to:

- Drive the first section of the route to the parking area.

- Walk the remaining distance to the destination.

- Place restrictions in certain paths or location that you don't want to go.

The user will also be asked to input the max time they want to be walking. In case no route is found within that constrain, two approximated possible solutions will be presented that are the closest to that time.

#### Option 0: Exit the program

The program will exit.

#### Notes about restricting the path

There are three types of restrictions that can be asked to the user.

- ***Avoid nodes***: You enter the nodes id that you want to avoid divided by a space. For example, if you want to avoid the nodes 2, 4  and 7, you would input:
  ```
  2 4 7
  ```
- ***Avoid Segments***: You can enter the segments that you wan to avoid by writing the one of the nodes id follow by a comma follow by the other node id of that segment. For example, if you want to avoid the streets of node 2 to 5 and 8 to 6, you would input:
  ```
  2,5 8,6
  ```
- ***Stop nodes***: You can enter nodes that you want to make stops. **The order is important**, since the path will go from the start to each of the nodes that you have input and then to the finish line. For example, if you want to start at node 2 and go to 3 then 6 then 4 then 8 and finish in 7, when ask:
  ```
  Choose the locations to make stops, in order, during path (Id number): 
  ```
  You would input:
  ```
  3 6 4 8
  ```
