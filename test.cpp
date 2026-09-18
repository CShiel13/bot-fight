// fcfs_demo.cpp - First Come First Served Scheduling (Beginner Version)
#include <iostream>   // for printing to the terminal
#include <vector>     // for using std::vector (a resizable array)
#include <iomanip>    // for formatting output nicely

// A struct is like a container that holds multiple pieces of data.
// Each process has an ID, arrival time, burst time, etc.
struct Process {
    int id;          // process number (1, 2, 3...)
    int arrival;     // time when the process arrives
    int burst;       // CPU burst time (how long it needs)
    int completion;  // we will calculate: when it finishes
    int turnaround;  // completion - arrival
    int wait;        // turnaround - burst
};

int main() {
    // Create a vector (list) of Process structs with sample data.
    // This is like an array of processes.
    std::vector<Process> processes = {
        {1, 0, 24, 0, 0, 0},   // P1: id=1, arrival=0, burst=24
        {2, 1, 3, 0, 0, 0},    // P2: id=2, arrival=1, burst=3
        {3, 2, 3, 0, 0, 0}     // P3: id=3, arrival=2, burst=3
    };

    int currentTime = 0;   // virtual clock

    // Loop through each process in order (FCFS is first-come, first-served)
    for (auto& p : processes) {
        // If the CPU is idle before this process arrives, jump to arrival time
        if (currentTime < p.arrival) {
            currentTime = p.arrival;
        }

        // Calculate its completion time
        p.completion = currentTime + p.burst;
        // Turnaround = finish time - arrival time
        p.turnaround = p.completion - p.arrival;
        // Wait time = turnaround - burst (time spent waiting in ready queue)
        p.wait = p.turnaround - p.burst;

        // Move the clock forward
        currentTime = p.completion;
    }

    // Print the results as a table
    std::cout << "FCFS Scheduling Results\n";
    std::cout << "Process\tArrival\tBurst\tCompletion\tTurnaround\tWait\n";
    double totalWait = 0, totalTurnaround = 0;

    for (const auto& p : processes) {
        std::cout << "P" << p.id << "\t"
                  << p.arrival << "\t"
                  << p.burst << "\t"
                  << p.completion << "\t\t"
                  << p.turnaround << "\t\t"
                  << p.wait << "\n";
        totalWait += p.wait;
        totalTurnaround += p.turnaround;
    }

    std::cout << "\nAverage Waiting Time: " << totalWait / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << totalTurnaround / processes.size() << "\n";

    return 0;
}