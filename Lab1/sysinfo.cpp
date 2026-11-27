#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    cout << "==========================================" << endl;
    cout << "        Lab 1: Computer Information       " << endl;
    cout << "==========================================" << endl;

    cout << "\n[1] CPU Name:" << endl;
    ifstream cpuinfo("/proc/cpuinfo");
    string line;
    bool foundCpu = false;
    while (getline(cpuinfo, line)) {
        if (line.find("model name") != string::npos) {
            cout << "  " << line << endl;
            foundCpu = true;
            break;
        }
    }
    if (!foundCpu) {
        system("lscpu | grep -i 'model name' || uname -p");
    }

    cout << "\n[2] Memory Information:" << endl;
    ifstream meminfo("/proc/meminfo");
    int memCount = 0;
    while (getline(meminfo, line) && memCount < 3) {
        cout << "  " << line << endl;
        memCount++;
    }

    cout << "\n[3] Operating System Name & Version:" << endl;
    ifstream osrelease("/etc/os-release");
    bool foundOs = false;
    while (getline(osrelease, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
            string osName = line.substr(12);
            if (!osName.empty() && osName.front() == '"' && osName.back() == '"') {
                osName = osName.substr(1, osName.size() - 2);
            }
            cout << "  OS: " << osName << endl;
            foundOs = true;
            break;
        }
    }
    if (!foundOs) {
        system("uname -sr");
    }

    cout << "\n[4] Storage Information:" << endl;
    system("df -h --total | grep -E 'Filesystem|/$|total'");

    cout << "\n[5] Running Processes (Top 15):" << endl;
    system("ps -eo pid,ppid,comm --no-headers | head -n 15");

    cout << "\n==========================================" << endl;
    return 0;
}