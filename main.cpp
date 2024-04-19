/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: main.cpp
 * Name: Eugene Pak
 * Version 2.5
 * Due: 4/12/24
 * This project reads in amount of processes to be handled. It then uses the array heap
 * class to organize the processes into priority, running them during their submission
 * time before their deadline. If they cannot be ran in time for the deadline, the
 * process will be skipped.
 */

#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"


/* main
 * This project reads in instruction letters to create a binary search tree with
 * inserts and removes until the letter q is read. When the letter i is read, the
 * word that follows is inserted into the tree. When the letter r is read, the word
 * that follows is removed from the tree. When the letter e is read, a stream of
 * words is read and encrypted into a path of keys. When the letter d is read, a
 * stream of keys are read and decrypted into a stream of words.
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 */
int main() {
    int loop;
    int sysTime = 0, id = 0, skip = 0, run = 0;
    ArrayHeap<Process> array;
    cin >> loop;
    for (int i = 0; i < loop; i++){
        Process p(id);
        cin >> p;
        id++;
        if (i == 0){
            sysTime = p.getSubmissionTime();
            array.insert(p);
        }
        else if (p.getSubmissionTime() > sysTime){
            if (array.getNumItems() > 0){
                while (array.getNumItems() > 0 && p.getSubmissionTime() > sysTime){
                    if (array.getMinItem().canComplete(sysTime)){
                        sysTime = array.getMinItem().run(sysTime);
                        run++;
                    }
                    else {
                        cout << "skipping process id " << array.getMinItem().getId()
                             << " at " << sysTime << endl;
                        sysTime++;
                        skip++;
                    }
                    array.removeMinItem();
                }
                array.insert(p);
                if (sysTime < array.getMinItem().getSubmissionTime()){
                    sysTime = array.getMinItem().getSubmissionTime();
                }
            }
        }
        else {
            array.insert(p);
        }
    }
    while (array.getNumItems() > 0){
        if (sysTime < array.getMinItem().getSubmissionTime()){
            sysTime = array.getMinItem().getSubmissionTime();
        }
        if (array.getMinItem().canComplete(sysTime)){
            sysTime = array.getMinItem().run(sysTime);
            run++;
        }
        else {
            cout << "skipping process id " << array.getMinItem().getId()
                 << " at " << sysTime << endl;
            sysTime++;
            skip++;
        }
        array.removeMinItem();
    }
    cout << "final clock is                 " << sysTime << endl;
    cout << "number of processes run is     " << run << endl;
    cout << "number of processes skipped is " << skip << endl;
    return 0;
}
