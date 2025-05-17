# 🧠 OS Project – CPU Scheduling Algorithms

## 📘 Overview

This project implements **six popular CPU scheduling algorithms** used in operating systems to manage process execution:

1. 🟦 **First-Come, First-Served (FCFS)**
2. 🟨 **Shortest Job First – Non-Preemptive (SJF Non)**
3. 🟨 **Shortest Job First – Preemptive (SJF Preemptive)**
4. 🟥 **Priority Scheduling – Non-Preemptive**
5. 🟥 **Priority Scheduling – Preemptive**
6. 🌀 **Round Robin**

Each algorithm follows a unified structure, differing only in their **scheduling logic** and **decision-making criteria**.

---

## 🏗️ Common Structure

All scheduler classes:

- Maintain a reference to the process list
- Track current simulation time
- Provide all_finished() to check for completion
- Implement get_process() to decide which process runs next

---

## 🧮 Algorithm Implementations

### 1️⃣ FCFS – First-Come, First-Served  
📌 **Concept**: Executes processes in order of arrival  
🔧 **Logic**:
- Uses a simple FIFO queue
- Runs each process to completion before switching

---

### 2️⃣ SJF – Non-Preemptive  
📌 **Concept**: Always picks the shortest job available  
🔧 **Logic**:
- Ready queue sorted by burst time
- CPU stays with selected process until it finishes

---

### 3️⃣ SJF – Preemptive  
📌 **Concept**: Interrupts current process if a shorter job arrives  
🔧 **Logic**:
- Re-sorts ready queue on process arrival
- Always runs the shortest available job
- May preempt current process mid-execution

---

### 4️⃣ Priority – Non-Preemptive  
📌 **Concept**: Runs the highest priority process until it finishes  
🔧 **Logic**:
- Similar to SJF Non, but sorted by priority instead
- CPU only switches when current process completes

---

### 5️⃣ Priority – Preemptive  
📌 **Concept**: Interrupts if a higher priority process arrives  
🔧 **Logic**:
- Ready queue re-sorted by priority on arrivals
- May preempt the running process

---

## 🔁 Round Robin Scheduling

📌 **Concept**: Time-sliced, fair scheduling with equal CPU time per process  
⚙️ **Key Parameters**:
- quantum: CPU time slice
- time_slice: Tracks time for current process

🧠 **Behavior**:
- Processes cycle through in FIFO order
- Preemption occurs when:
  - Quantum expires
  - Process finishes
  - CPU becomes idle

🔍 **Highlights**:
- Tracks CPU state using is_busy
- Ensures fairness across all processes
- Interrupted processes are sent to the back of the queue

---

## 🧱 Process Class

📁 **File**: process.h / process.cpp  
🧬 **Attributes**:
- pid, arrival_time, burst_time, priority
- Timing: waiting_time, turn_around_time, finish_time

🔧 **Methods**:
- calculate_waiting_time()
- calculate_turn_time()
- Maintains original burst time for resets

---

## 🖥️ GUI Application Overview

Built with **Qt**, the GUI provides a real-time, interactive visualization of scheduling algorithms.

### 🧩 Components

#### 1. SchedulerGUI  
- Algorithm selector  
- Process table  
- Simulation controls (Start/Reset)  
- Live mode toggle  

#### 2. GanttChartWindow  
- Dynamic Gantt chart showing process execution  
- Real-time updates as simulation runs  

#### 3. SimulationWorker  
- Runs selected scheduling algorithm on background thread  
- Sends signals to update UI components  
- Supports live/instant execution modes  

---

### ⭐ Features

- 🧠 Adaptive UI: Shows/hides priority or quantum fields based on algorithm  
- 📊 Real-time process table updates  
- 🖼️ Visual Gantt chart with process IDs  
- 📈 Metrics: Waiting time, turnaround time (individual & average)  
- 🧵 Thread-safe execution using Qt signals/slots  
- 🎯 Polymorphic algorithm execution  

---

## ⚙️ How It Works

1. User adds processes via the GUI  
2. Chooses scheduling algorithm  
3. Starts the simulation (Live/Instant)  
4. Worker thread simulates execution  
5. Results shown in Gantt chart + stats  

---

## 🏁 Summary

This project combines core OS scheduling concepts with modern GUI features for a comprehensive learning and visualization tool.  
It demonstrates:

- ✨ Clear architectural separation  
- 🔄 Real-time simulations  
- 📚 Accurate scheduling logic  
