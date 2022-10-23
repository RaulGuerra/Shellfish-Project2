This branch contains:
sc program
renice program
ps -l functionality
Process priority levels

This branch focuses on adding process priority to FreeNOS. Process priority levels are added to process.cpp, and accessed via processctrl. ProcessClient implements setter and getter functionality which calls processctl, ProcessClient is then used by renice and ps -l to set priority level of processes and print them out respectivly. The scheduler has been modified using an ML algorithm to use these priority levels to determine which process should run.

Video demonstration: https://youtu.be/40Rz2-Cy_Y8
