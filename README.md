# 🧠 RTOS Simulation with Gantt Chart (POSIX-based)

This project simulates a Real-Time Operating System (RTOS) environment using POSIX threads. It supports periodic tasks with hard deadlines, deadline miss detection, and generates a Gantt chart for visualizing task execution patterns — just like a real embedded RTOS would do.

---

## 🔧 Features

- ✅ Simulates periodic tasks using `pthread`
- ✅ Implements basic Rate Monotonic scheduling
- ✅ Logs task execution, duration, and deadline misses
- ✅ Generates Gantt charts using `matplotlib`
- ✅ Color-coded chart: red for missed deadlines
- ✅ CSV trace output for post-run analysis

---

## 🛠️ How to Run

### 1. Build the project:
```bash
make
