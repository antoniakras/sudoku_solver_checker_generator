# 🧩 Sudoku Solver, Checker & Generator

## 📖 About

A **C++ project** implementing a complete Sudoku backend system with three main components:

- **Solver** – Uses a **backtracking algorithm** to fill empty cells while satisfying Sudoku constraints.  
- **Checker** – Validates completed puzzles for correctness according to rows, columns, and 3x3 subgrids.  
- **Generator** – Creates uniquely solvable Sudoku puzzles of varying difficulty.

---

## ✨ Features & Technical Highlights

- **Solver**
  - Recursive **backtracking with pruning** for efficient solution exploration.
  - Validates constraints at each step:
    - Row uniqueness
    - Column uniqueness
    - 3x3 subgrid uniqueness
  - Handles input puzzles via text files and outputs solutions to console or file.

- **Checker**
  - Confirms solution validity for all rows, columns, and subgrids.
  - Returns Valid or Invalid status.
  
- **Generator**
  - Produces puzzles with **unique solutions**.
  - Supports multiple difficulty levels by controlling number of prefilled cells and solution complexity.
  - Uses the solver itself to ensure puzzle solvability.

- **Modular Design**
  - Separate classes/functions for solver, checker, and generator.
  - Enables **reusability, maintainability, and easy testing**.

- **File I/O**
  - Reads puzzles and solutions from text files.
  - Supports flexible input/output formats for testing and integration.

- **Error Handling**
  - Detects invalid or malformed puzzles before processing.

---

## 🧠 Algorithmic Approach & Complexity

**Sudoku Solver (Backtracking):**
1. Start from the first empty cell.
2. Attempt to place numbers 1–9 sequentially.
3. For each number, check if it satisfies Sudoku constraints:
   - Unique in row
   - Unique in column
   - Unique in 3x3 subgrid
4. If valid, recursively move to the next empty cell.
5. If no number is valid, **backtrack** to the previous cell.
6. Repeat until the grid is filled or determined unsolvable.

**Time Complexity:** O(9^(N)), where N is the number of empty cells.  
**Space Complexity:** O(N) due to recursion stack.

**Checker:**
- Iterates through rows, columns, and subgrids.
- Confirms uniqueness constraints in O(81) = O(1) time (fixed-size grid).

**Generator:**
- Starts from a complete solved grid (using the solver).
- Removes numbers strategically to achieve the desired difficulty.
- Validates that the puzzle remains uniquely solvable via the solver.

---

## 🛠️ Setup & Run

1. Clone the repository:
   ```bash
   git clone https://github.com/antoniakras/sudoku_solver_checker_generator.git
   cd sudoku_solver_checker_generator
   make
   ./sudoku -c
   
   Reads a puzzle from input (stdin or file).
   Checks if the puzzle is correct and prints the sudoku
   
   ./sudoku -g <N> -u
   
   Generates a Sudoku puzzle with N prefilled elements.
   
   -g specifies generator mode and -u ensures the puzzle has a unique solution.
   
   ./sudoku
    Runs without parameters.
    
    Reads a puzzle from input.
    
    Prints the puzzle.
    
    Solves the puzzle using backtracking.
    
    Checks if the solution is valid and prints it.
    
     Determines if the puzzle has a unique solution, multiple solutions, or no solution.


