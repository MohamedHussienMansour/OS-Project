#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include "Input.h"
using namespace std;


class Sjf_Algoritm {
    vector<process> Ready_Processes;
    vector<process> Finished_Processes;
    map<int, vector<process>> Proceeses_indexedByArrivalTime;
    queue<int> ArrivalTimeOrdered;
    int numberProcess = 0;

public:
    void EnteringProcesses(int n) {
        numberProcess = n;
        for (int i = 0; i < n; i++) {
            int ArrivalTime, BurstTime;
            cin >> ArrivalTime >> BurstTime;

            Proceeses_indexedByArrivalTime[ArrivalTime].push_back(process(BurstTime, ArrivalTime));

            if (ArrivalTimeOrdered.empty() || ArrivalTime != ArrivalTimeOrdered.back()) {
                ArrivalTimeOrdered.push(ArrivalTime);
            }
        }
    }

    void ShowingProcesses() {
        for (const auto& proc : Proceeses_indexedByArrivalTime) {
            cout << "Arrival Time: " << proc.first << "\n";
            for (const auto& p : proc.second) {
                cout << "  Process: " << p.name
                     << ", Burst Time: " << p.burst_time
                     << ", Arrival Time: " << p.arrival_time << "\n";
            }
        }
    }

    void SJf_Algorithm() {
        int n = numberProcess;
        if (ArrivalTimeOrdered.empty()) return;

        int CurrentTime = ArrivalTimeOrdered.front();
        cout << "\nGantt Chart:\n";

        while (n > 0) {
            if (!ArrivalTimeOrdered.empty()) {
                int arrivalTime = ArrivalTimeOrdered.front();
                int count = Proceeses_indexedByArrivalTime[arrivalTime].size();
                for (int i = 0; i < count; ++i) {
                    Ready_Processes.push_back(Proceeses_indexedByArrivalTime[arrivalTime][i]);
                }
                ArrivalTimeOrdered.pop();
            }

            // Sort ready queue by burst time (SJF logic)
            sort(Ready_Processes.begin(), Ready_Processes.end(), [](const process& a, const process& b) {
                return a.copy_burst_time < b.copy_burst_time;
            });

            if (Ready_Processes.empty()) {
                cout << "| idle ";
                if (!ArrivalTimeOrdered.empty()) {
                    CurrentTime = ArrivalTimeOrdered.front();
                }
                continue;
            }

            process& current = Ready_Processes.front();
            if (!ArrivalTimeOrdered.empty() && ArrivalTimeOrdered.front() - CurrentTime < current.copy_burst_time) {
                int nextArrival = ArrivalTimeOrdered.front();
                int gap = nextArrival - CurrentTime;
                if (gap > 0) {
                    cout << "| " << current.name << " (" << gap << ") ";
                    current.copy_burst_time -= gap;
                    CurrentTime = nextArrival;
                }
            } else {
                // Full execution
                CurrentTime += current.copy_burst_time;
                current.finish_time = CurrentTime;
                current.turn_around_time = current.finish_time - current.arrival_time;
                current.waiting_time = current.turn_around_time - current.burst_time;
                current.copy_burst_time = 0;

                cout << "| " << current.name << " (" << current.burst_time << ") ";

                Finished_Processes.push_back(current);
                Ready_Processes.erase(Ready_Processes.begin());
                n--;
            }
        }
        cout << "|\n";

        // Final output
        cout << "\nProcess Results:\n";
        cout << "Name\tArrival\tBurst\tFinish\tWaiting\tTurnaround\n";
        for (const auto& p : Finished_Processes) {
            cout << p.name << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
                 << p.finish_time << "\t" << p.waiting_time << "\t" << p.turn_around_time << "\n";
        }
    }
};

int main() {
    Sjf_Algoritm scheduler;

    cout << "Enter number of processes: ";
    int n;
    cin >> n;

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    scheduler.EnteringProcesses(n);

    scheduler.ShowingProcesses();
    scheduler.SJf_Algorithm();

    return 0;
}
