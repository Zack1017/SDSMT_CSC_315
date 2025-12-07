# Programming Assignment 3 
**Language:** C++20  
**Build System:** CMake  
**Executable:** `project3`

### Grade Level: A
This project demonstrates all five major algorithm design techniques required for Programming Assignment 3. When the program runs, it will automatically execute example test cases (from the assignment PDF) for each algorithm and then enter an interactive user menu for custom input.

### Las Vegas Algorithm Justification & Runtime Analysis

The Randomized Binary Search implemented in this project is classified as a Las Vegas algorithm because:

- It always returns the correct answer
- Randomness only affects the execution path, not correctness
- If the value is found, the returned index is guaranteed to be correct
- If the value is not in the array, the algorithm correctly returns `-1`

The randomness is used only to select the midpoint within the current search range:
```cpp
mid = random(left, right)
```
Rather than always choosing the deterministic center as in standard binary search.
#### Expected Runtime: O(log n)

Even though the midpoint is chosen randomly, the expected runtime remains O(log n) because:

* Each random midpoint still partitions the array into two smaller subarrays

* On average, the remaining search space is reduced by a constant fraction

* This leads to the same expected logarithmic depth as standard binary search

#### Recurrence Relation:
```
T(n)=T(n/2)+O(1)=> T(n)=O(log n)
```
---

### Build Instructions

From the project root directory:

```
mkdir build
cd build
cmake ..
make
```

Run the program:
```
./project3
```
