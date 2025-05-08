# Truck Packing Optimization

This project is a knapsack-based truck packing system developed for academic purposes as part of the **Design and Analysis of Algorithms (DA)** course at **FEUP**.  
It reads truck and pallet data from CSV files and provides multiple algorithmic strategies to determine the most profitable set of pallets that can be loaded onto a truck without exceeding its weight capacity.

## Features

- Load dataset files (truck info and pallet list) from CSV
- Selectable optimization algorithms:
    - Brute Force (Exhaustive Search)
    - Dynamic Programming (0/1 Knapsack)
    - Greedy Approximation
    - Integer Linear Programming (using external solver)
- Interactive, menu-driven command-line interface
- Easily extensible with new algorithms
- Doxygen-based documentation

---

## Documentation

- Navigate to the **`docs/html`** folder and open `index.html` with a web browser to access the full, auto-generated Doxygen documentation.

---

## Project Structure

```
├── src/                      # C++ source code
│   ├── algorithm/            # Brute force, DP, greedy, ILP
│   ├── data_handling/        # CSVReader
│   ├── data_structures/      # Truck, Pallet
│   ├── ui/                   # Command-line menu system
│   └── main.cpp              # Entry point of the program
│
├── data/                     # Dataset CSV files
│
├── docs/                     # Documentation folder
│   └── html/                 # Doxygen HTML output
│
├── CMakeLists.txt            # CMake configuration file
└── README.md                 # Project documentation
```

---

## How to Compile and Run

### Requirements

- CMake 3.30 or higher
- A C++20-compatible compiler (e.g., g++ 11+, clang++)

---

### Building the Project

#### With CLion

Open the project and run via the IDE.

#### From the Terminal

In the root of the project directory, run:

```bash
cmake -S . -B build
cmake --build build
./build/DA
```

---

## Usage

Run the program:

```bash
./build/DA
```

You will be presented with an interactive menu:

```
Truck Packing Optimization Menu:
1. Select Dataset
2. Run Brute Force Algorithm
3. Run Dynamic Programming Algorithm
4. Run Greedy Approximation
5. Run ILP (Integer Linear Programming)
0. Exit
```

### Option 1: Select Dataset

Choose which dataset (e.g., 01–10) to load from the `datasets/` folder.

### Option 2–5: Run Algorithm

Execute the selected optimization algorithm to determine the most profitable set of pallets under the truck's weight constraint. The system will display:

- Algorithm Name
- Computation time
- Total profit
- Total weight
- Selected pallet IDs

### Option 0: Exit

Closes the program.

---

## Example Datasets

Each dataset includes:

- **TruckAndPallets_XX.csv**: Contains truck capacity and number of pallets.
- **Pallets_XX.csv**: Contains pallet ID, weight, and profit.

These files should be placed under the `datasets/` directory.

---

## Authors

- Developed by students of **FEUP**, for the **DA - Design of Algorithms** course 2025.
  - Diogo Soares Rocha - up201606166
  - Francisco João Gonçalves Calado Araújo - up201806326
