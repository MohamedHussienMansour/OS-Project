# OS-Project
# CPU Scheduling Algorithms Documentation

## Overview

This project implements five CPU scheduling algorithms:
1. First-Come, First-Served (FCFS)
2. Shortest Job First - Non-Preemptive (SJF Non)
3. Shortest Job First - Preemptive (SJF Preemptive)
4. Priority Scheduling - Non-Preemptive
5. Priority Scheduling - Preemptive

All implementations share a similar structure but differ in their scheduling logic.

## Common Structure

All scheduler classes:
- Maintain a reference to the process list
- Track current simulation time
- Provide `all_finished()` to check completion
- Implement `get_process()` to determine which process runs at each time unit

## Algorithm Implementations

### 1. FCFS (First-Come, First-Served)
- **Concept**: Processes execute in order of arrival
- **Implementation**:
  - Uses a queue for ready processes
  - Always selects the front process
  - Runs each process to completion before moving to next

### 2. SJF Non-Preemptive
- **Concept**: Always runs the shortest available job to completion
- **Implementation**:
  - Maintains a ready queue sorted by burst time
  - Only selects new process when CPU becomes idle
  - Runs selected process to completion

### 3. SJF Preemptive
- **Concept**: Can interrupt current process if a shorter job arrives
- **Implementation**:
  - Re-sorts ready queue whenever new processes arrive
  - Always runs the shortest available job
  - May preempt current process if a shorter one arrives

### 4. Priority Non-Preemptive
- **Concept**: Runs highest priority job to completion
- **Implementation**:
  - Similar to SJF Non but sorts by priority
  - Only selects new process when CPU becomes idle
  - Runs selected process to completion

### 5. Priority Preemptive
- **Concept**: Can interrupt current process if higher priority job arrives
- **Implementation**:
  - Re-sorts ready queue by priority when new processes arrive
  - Always runs highest priority available job
  - May preempt current process if higher priority job arrives

## Key Differences

- **Preemptive vs Non-Preemptive**: Preemptive versions re-evaluate scheduling decisions at each time unit, while non-preemptive versions only when CPU becomes idle
- **Scheduling Criteria**: SJF uses burst time, Priority uses priority value
- **Data Structures**: FCFS uses a queue, others use sorted vectors

All implementations track process completion times and calculate turnaround/waiting times when processes finish.
## Round Robin Scheduling Algorithm

### Concept
- **Time-sliced scheduling**: Each process gets equal CPU time (quantum) in cyclic order
- **Fair allocation**: Prevents long processes from monopolizing CPU
- **Preemptive**: Can interrupt current process when quantum expires

### Implementation Highlights
1. **Key Parameters**:
   - `quantum`: Fixed time slice for each process
   - `time_slice`: Tracks how long current process has run

2. **Core Logic**:
   - Processes cycle through ready queue in FIFO order
   - Runs current process until either:
     * Quantum expires (time_slice == quantum)
     * Process completes (burst_time == 0)
   - Interrupted processes return to queue end

3. **Special Handling**:
   - Tracks CPU state with `is_busy` flag
   - Manages process transitions at quantum boundaries
   - Updates process metrics upon completion

4. **Behavior**:
   - New arrivals added to queue when they arrive
   - Always gives CPU to next ready process when:
     * Quantum expires
     * Current process finishes
     * CPU becomes idle

This implementation provides fair CPU allocation while maintaining the preemptive nature of round robin scheduling. The quantum parameter allows tuning the balance between responsiveness and overhead from context switches.
## Process Class and GUI Application Overview

### Process Class (`process.h/cpp`)
**Core Data Structure**:
- Represents a single process with essential scheduling attributes:
  - `pid`: Process identifier
  - `burst_time`: Total CPU time required
  - `arrival_time`: When process enters ready queue  
  - `priority`: For priority-based scheduling
  - `copy_burst_time`: Preserves original burst time
  - Timing metrics: `waiting_time`, `turn_around_time`, `finish_time`

**Key Methods**:
- `calculate_waiting_time()`: Computes time spent waiting
- `calculate_turn_time()`: Computes total completion time
- Preserves original burst time for simulation resets

### GUI Application Architecture

**Main Components**:
1. **SchedulerGUI (Main Window)**:
   - Algorithm selection (FCFS, SJF, Priority, Round Robin)
   - Process management table
   - Simulation controls (Start/Reset)
   - Live mode toggle

2. **GanttChartWindow**:
   - Visualizes process execution timeline
   - Dynamically updates during simulation
   - Rectangles represent process execution periods

3. **SimulationWorker**:
   - Runs scheduling algorithms in background thread
   - Supports all 6 scheduling variants
   - Emits signals for GUI updates
   - Handles live mode pacing

**Key Features**:
- Dynamic UI adaptation (shows/hides quantum/priority fields as needed)
- Process table with real-time remaining time updates
- Gantt chart visualization with process IDs
- Metrics calculation (average wait/turnaround times)
- Thread-safe simulation execution

**Workflow**:
1. User adds processes with parameters
2. Selects scheduling algorithm
3. Starts simulation (live or instant)
4. Worker executes algorithm, updates GUI via signals
5. Results displayed in Gantt chart and metrics

**Technical Highlights**:
- Qt signals/slots for thread-safe GUI updates
- QGraphicsScene for Gantt chart rendering
- Atomic flag for simulation interruption
- Polymorphic algorithm execution via worker

The application provides an interactive way to visualize and compare CPU scheduling algorithms while maintaining clean separation between simulation logic and presentation.
