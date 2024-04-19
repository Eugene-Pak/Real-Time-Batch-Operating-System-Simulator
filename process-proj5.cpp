#include <iostream>
#include "process-proj5.h"

Process::Process(int theId){
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
}

int Process::run(int currentSystemTime) const{
    cout << "running process id " << this->id
         << " at " << currentSystemTime << endl;
    cout << this->information << endl;
    return currentSystemTime + this->requiredTime;
}

bool Process::canComplete(int currentSystemTime) const{
    if ((currentSystemTime + this->requiredTime) <= this->deadline){
        return true;
    }
    return false;
}

int Process::getId() const{
    return this->id;
}

int Process::getSubmissionTime() const{
    return this->submissionTime;
}

bool Process::operator<(Process const &p) const{
    if (this->deadline < p.deadline){
        return true;
    }
    else if (p.deadline < this->deadline){
        return false;
    }
    if (this->requiredTime < p.requiredTime){
        return true;
    }
    else if (p.requiredTime < this->requiredTime){
        return false;
    }
    if (this->id < p.id){
        return true;
    }
    return false;
}

istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    is.get();
    getline(is, p.information);
    return is;
}