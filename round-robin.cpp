#include <iostream>
#include<vector>
#include <queue> 
#include "process.h"
using namespace std;

class round_robin {
public:
    vector<process> &processes;
    queue<process*> ready;    
    int time;
    bool is_busy;
    process *curr_process;
    int quantum;
    int time_slice;

    round_robin(vector<process> &processes_ref, int q) : processes(processes_ref), quantum(q) {
        time = 0;
        is_busy = false;
        curr_process = nullptr;
        time_slice = 0;
    }

    bool all_finished() {
        for (auto &p : processes) {
            if (p.burst_time > 0) return false;
        }
        return true;
    }

    int get_process() {
      // if all process finished wait for another process (live mode)
        if (all_finished()) return -2;

        // Add  new arrived procees to the ready queue
        for (auto &p : processes) {
            if (p.arrival_time == time) ready.push(&p);
        }

        // if processor is empty or time(time consumed in one cycle) become  == quantum time
        if (!is_busy || time_slice == quantum) {
            // if there is process in cpu and its burst time more than one
            if (curr_process && curr_process->burst_time > 0) {

              //  put the current process to back of queue
                ready.push(curr_process);
            }
            // if ready queue not empty 
            if (!ready.empty()) {
                curr_process = ready.front();
                ready.pop();
                is_busy = true;
                time_slice = 0;
            } else {
                curr_process = nullptr;
                is_busy = false;
            }
        }

        // Execute current process if there is one
        if (is_busy && curr_process) {
          int current_id =curr_process->pid;
            curr_process->burst_time--;
            time_slice++;

            if (curr_process->burst_time == 0) {
                // cout<<"this irs "<<curr_process->pid <<endl;
                curr_process->finish_time = time + 1;
                curr_process->calculate_turn_time();
                curr_process->calculate_waiting_time();
                curr_process = nullptr;
                is_busy = false;
                time_slice = 0;
                time++;
                return current_id;

            }

            time++;
            return curr_process ? current_id: -1;
        }

        // CPU idle
        time++;
        return -1;
    }
};
int main() {
  vector<process> p = {
      process(1, 0, 3, 2),
      process(2, 2, 6, 1),
      process(3, 5, 1, 3),
      // process(4, 9, 2, 2),
      // process(5, 12, 4, 2)
  };

  round_robin rr(p, 2); // q = 2
  int temp = 0;
  int cnt = 0;

  while (temp != -2) {
      temp = rr.get_process();
      if (temp == -2) {
        
        continue;
      } 
      if (temp == -1)
          cout << "TIMESTEP " << cnt << " : Idle" << endl;
      else
          cout << "TIMESTEP " << cnt << " : " << temp << endl;
      cnt++;
  }

  float avg_tat = 0, avg_wt = 0;
  for (auto &proc : p) {
      avg_wt += proc.waiting_time;
      avg_tat += proc.turn_around_time;
  }

  cout << "avg turn around = " << avg_tat / p.size() << endl;
  cout << "avg waiting = " << avg_wt / p.size() << endl;
}
