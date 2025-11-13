# Version Control Core – Mini Git Simulation (C & Data Structures)

A lightweight **version control system** inspired by Git, implemented entirely in **C**.  
This project demonstrates how **commits**, **branches**, and **merges** can be simulated using **graph** and **linked list** data structures — helping students understand the internal logic behind real version control systems.

---

## Features

- **Initialize Repository** – Creates a repository with a root commit and master branch.  
- **Create Commits** – Adds new commit nodes with unique IDs, timestamps, and messages.  
- **Branch Management** – Create, switch, and list branches dynamically.  
- **Merge Branches** – Simulates merging of two branches (creates DAG structure).  
- **View Commit History** – Displays linear history for current branch.  
- **Visualize Commit Graph (DAG)** – Prints parent-child relationships of commits.  
- **Modular MVC Architecture** – Clean separation of logic into multiple `.c` and `.h` files.  

---

## Project Structure
```
VersionControlCore/
│
├── include/ # Header files (declarations)
│ ├── commit.h
│ ├── repo.h
│ ├── branch.h
│ ├── merge.h
│ ├── graph.h
│ ├── utils.h
│
├── src/ # Source files (implementations)
│ ├── commit.c
│ ├── repo.c
│ ├── branch.c
│ ├── merge.c
│ ├── graph.c
│ ├── utils.c
│
├── main.c # Console-based interface (Controller + View)
├── Makefile # Build automation
└── README.md # Documentation
```
---

## How to Build and Run

1.  **Build the Project**
    ```bash
    make
    ```
2.  **Run the Simulation**
    ```bash
    make run
    ```
3.  **Clean the Build**
    ```bash
    make clean
    ```

## Menu Options

| Option | Description |
| :--- | :--- |
| 1 | Create Commit |
| 2 | View Commit History |
| 3 | Create Branch |
| 4 | Switch Branch |
| 5 | List Branches |
| 6 | Merge Branches |
| 7 | Visualize Commit Graph |
| 8 | Exit |

## Data Structures Used

| Data Structure | Purpose |
| :--- | :--- |
| **Graph (DAG)** | Models commit relationships (edges = parent links). |
| **Linked List** | Maintains sequential commit history per branch. |
| **Structs** | Defines commits, branches, and repository state. |
| **Hash Table** (optional) | For quick lookup by commit ID. |

## Author

* **Project Title:** Version Control Core – A Mini Git Simulation
* **Developer:** Adharsh and Koushik
* **Course:** B.E. II Year – Data Structures (Course-Based Project)
* **Institution:** Vasavi College of Engineering