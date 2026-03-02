# 🧠📊 Lab03 — Analysis of Algorithms (Mathematical & Empirical Analysis)

**🏫 Yachay Tech University**  
**👤 Student:** Andres Basantes  
**👨‍🏫 Professor:** Prof. Pineda  
**🧪 Lab:** **Lab03 — Mathematical and Empirical Analysis**

---

## ✨ Overview 
In this lab we implemented and analyzed two main components:

1. **🗼 Towers of Hanoi (Recursive vs. Iterative)**
   - Implemented both versions in **C++**.
   - Verified **consistency** by checking that both methods produce the **same number of moves** for each *n*.
   - Collected **empirical runtimes** (without printing moves to avoid timing distortion).
   - The full mathematical analysis (recurrence, closed form, Θ-notation) is included in the attached PDF report.

2. **🎲 Linear Congruential Generator (LCG) — Empirical Study**
   - Implemented an **LCG** pseudo-random number generator.
   - Measured runtime for increasing *N* (expected ~linear growth).
   - Reported simple distribution indicators (mean in [0,1) and a basic chi-square over 10 bins).

📌 **Detailed analysis and conclusions are in the PDF report**: `AoA_Lab3.pdf`.

---



## 📁 Repository Contents
- **`lab03_main.cpp`** → C++ source code (Hanoi + LCG + benchmarking)
- **`lab03.exe`** → compiled executable (Windows)
- **`AoA_Lab3.pdf`** → final report (mathematical + empirical analysis)
- **`Screen 1.JPG`**, **`Screen 2.JPG`** → execution screenshots (evidence)

---

## ▶️ How to Run 
### ✅ Compile
```bash
g++ -O2 -std=c++17 lab03_main.cpp -o lab03
```

### ✅ Run benchmark 
```bash
.\lab03.exe
```

### ✅ Run with printed moves 
```bash
.\lab03.exe print 3
```

---

## 🖼️ Evidence 
You can view the execution evidence here:

![Screen 1](./Screen%201.JPG)  
![Screen 2](./Screen%202.JPG)

---


