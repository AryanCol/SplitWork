#include <string>
#include <iostream>
#include<ctime>
using namespace std;

class User {
private:
    int userId;
    std::string userName;
    std::string userEmail;

public:
    User();
    ~User();
    
};
class Date{
    public:
    int month;
    int year;
    int day;
};
class Task {
private:
    int taskId;
    std::string taskName;
    std::string taskDesc;

public:
    Task();
    ~Task();
    
};


class Deadline: public Date {
private:
    User user;
    Task task;

public:
    Deadline() {}
    ~Deadline() {}

    int calculateTimeBetweenDeadlines(const Deadline& other) {
        std::tm tmThis = {0};
        tmThis.tm_year = this->year - 1900;
        tmThis.tm_mon = this->month - 1;
        tmThis.tm_mday = this->day;
        std::time_t timeThis = std::mktime(&tmThis);

        std::tm tmOther = {0};
        tmOther.tm_year = other.year - 1900;
        tmOther.tm_mon = other.month - 1;
        tmOther.tm_mday = other.day;
        std::time_t timeOther = std::mktime(&tmOther);

        double diffSeconds = std::difftime(timeThis, timeOther);

        int diffDays = static_cast<int>(diffSeconds / (60 * 60 * 24));

        return std::abs(diffDays);
    }

    int calculateTimeLeft() {
        
        std::time_t now = std::time(nullptr);
        std::tm* tmNow = std::localtime(&now);

        
        std::tm tmCurrent = {0};
        tmCurrent.tm_year = tmNow->tm_year;
        tmCurrent.tm_mon = tmNow->tm_mon;
        tmCurrent.tm_mday = tmNow->tm_mday;
        std::time_t timeCurrent = std::mktime(&tmCurrent);

        
        std::tm tmDue = {0};
        tmDue.tm_year = this->year - 1900;
        tmDue.tm_mon = this->month - 1;
        tmDue.tm_mday = this->day;
        std::time_t timeDue = std::mktime(&tmDue);

        
        double diffSeconds = std::difftime(timeDue, timeCurrent);

        
        int diffDays = static_cast<int>(diffSeconds / (60 * 60 * 24));

        return diffDays;
    }
};


int main(){

    return 0;
}