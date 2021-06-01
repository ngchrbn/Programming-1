/*
    STUDENT NAME: NIYOMUKIZA RAMADHAN
    STUDENT ID: 20190812
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    char plan;
    string startTime, endTime, dateOfCall;
    cout << "Plan: ";
    cin >> plan;
    cout << "Call Start Time(in 24-hour format): ";
    cin.ignore();
    getline(cin, startTime);
    cout << "Call End Time(in 24-hour format): ";
    getline(cin, endTime);
    cout << "Date of Call(In format \"Thurs 15 4\" for e.g.): ";
    getline(cin, dateOfCall);

    /* The length of a time must be between minimum 5 and maximum 8
     * The length of a date of call must be between minimum 7 and maximum 11
     * If found error, terminates the execution
     * */
    if (startTime.length() < 5 || startTime.length() > 8 || endTime.length() < 5 || endTime.length() > 8)
    {
        cout << "\n==> Please correct the format to be in 24-hour format (15:23:11 for e.g.)" << endl;
        cout << ((startTime.length() < 5 || startTime.length() > 8) ? "Error in Call Start Time: " + startTime :
        "Error in Call End Time: " + endTime);
        return 1;
    }
    if (dateOfCall.length() < 7 || dateOfCall.length() > 11)
    {
        cout << "\n==>The date format is: Name-of-the-day day-of-the-month month" << endl;
        cout << "For e.g Thurs 22 4" << endl;
        cout << "Day of the week should be {Sat, Sun, Mon, Tues, Wed, Thurs, Fri}" << endl;
        return 1;
    }

    /* Extract the dayName, date and month for validation
     * Days of the week should be: Sat, Sun, Mon, Tues, Wed, Thurs, or Fri
     * A month must be between 1 and 12 and not negative
     * A day of the month must be between 1 and 31 and not negative
     * If found error, terminates the execution
     * */
    int spaceOne = dateOfCall.find(' ');
    string dayName = dateOfCall.substr(0, spaceOne);
    int spaceTwo = dateOfCall.find(' ', spaceOne+1);
    int date = stoi(dateOfCall.substr(spaceOne, (spaceTwo-spaceOne)));
    int month = stoi(dateOfCall.substr(spaceTwo));

    if (dayName != "Sat" && dayName != "Sun" &&
        dayName != "Mon" && dayName != "Tues" &&
        dayName != "Wed" && dayName != "Thurs" && dayName != "Fri")
    {
        cout << "\n==>Day of the week should be {Sat, Sun, Mon, Tues, Wed, Thurs, Fri}" << endl;
        cout << "You entered: " << dayName << endl;
        return 1;
    }
    if (date > 31 || date < 1)
    {
        cout << "\n==>A day of a month must be between 1 and 31" << endl;
        cout << "You entered: " << date;
        return 1;
    }
    if (month > 12 || month < 1)
    {
        cout << "\n==>A month of a year must be between 1 and 12" << endl;
        cout << "You entered: " << month;
        return 1;
    }

    /* Extract the start and end hour, start and end minutes, start and end seconds for validation
     * An hour must be between 0 and 23 and not negative
     * A minute or second must between 0 and 59 and not negative
     * If found, terminates the execution
     * */
    int delimiterStartOne = startTime.find(':');
    int delimiterEndOne = endTime.find(':');
    int startHour = stoi(startTime.substr(0, delimiterStartOne));
    int endHour = stoi(endTime.substr(0, delimiterEndOne));

    int delimiterStartTwo = startTime.find(':', delimiterStartOne+1);
    int delimiterEndTwo = endTime.find(':', delimiterEndOne+1);
    int startMinutes = stoi(startTime.substr(delimiterStartOne+1,
                                             (delimiterStartTwo - delimiterStartOne)));
    int endMinutes = stoi(endTime.substr(delimiterEndOne+1,
                                         (delimiterEndTwo - delimiterEndOne)));

    int startSeconds = stoi(startTime.substr(delimiterStartTwo+1));
    int endSeconds = stoi(endTime.substr(delimiterEndTwo+1));
    if (startHour > 23 || endHour > 23 ||
        startHour < 0 || endHour < 0)
    {
        cout << "\n==>An Hour cannot be greater than 23 or be negative" << endl;
        cout << ((startHour > 23 || startHour < 0) ? "Correct the call Start Time: " + startTime :
        "Correct the Call End Time: " + endTime);
        return 1;
    }
    if (startMinutes > 59 || endMinutes > 59 ||
        startMinutes < 0 || endMinutes < 0)
    {
        cout << "\n==>An Minute cannot be greater than 23 or be negative" << endl;
        cout << ((startMinutes > 23 || startMinutes < 0) ? "Correct the call Start Time: " + startTime :
                 "Correct the Call End Time: " + endTime);
        return 1;
    }
    if (startSeconds > 59 || endSeconds > 59 ||
        startSeconds < 0 || endSeconds < 0)
    {
        cout << "\n==>A Second cannot be greater than 59 or be negative" << endl;
        cout << ((startSeconds > 59 || startSeconds < 0) ? "Correct the call Start Time: " + startTime :
                 "Correct the Call End Time: " + endTime);
        return 1;
    }

    /* Calculate the duration after validating if the start Hour is not greater than the end Hour
     * If startHour is greater than endHour, terminates execution
     * */
    int durationHour = endHour - startHour;
    if (durationHour < 0) { // Checks if  start hour hour is greater than end hour
        cout << "\n==>The Start call Time Hour cannot be greater than call End Time Hour" << endl;
        cout << "Error: " << startTime;
        return 1;
    }
    int durationMinutes = endMinutes - startMinutes;

    double durationSecond =  static_cast<double>(1 * (endSeconds - startSeconds)) / 60;
    double duration = ceil((durationHour * 60) + durationMinutes + durationSecond);

    cout << "Call Info: " << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "End Time: " << endTime << endl;
    cout << "Date: " << dateOfCall << endl;
    cout << "Duration: " << duration << " minute(s)" << endl;

    cout << "Plan " << plan << ":" << endl;
    cout << setw(25) << left << "Call Time" <<
            setw(18) << right << "Call Day" <<
            setw(16) << right << "Duration" <<
            setw(11) << right << "Rate" << endl;

    double cost; // Hold the cost of the call

    /* For each plan, Calculate the cost depending on the factors of each plan
     * and the call information from the user*/
    switch (plan) {
        case 'A':
        {
            cout << setw(18) << right << "7:00 am to 5:00 pm" <<
                    setw(25) << right << "Sun-Thurs" <<
                    setw(16) << right << "<15 mins" <<
                    setw(11) << right << "0.6" << endl;
            cout << setw(18) << right << "7:00 am to 5:00 pm" <<
                 setw(25) << right << "Sun-Thurs" <<
                 setw(16) << right << ">=15 mins" <<
                 setw(11) << right << "0.8" << endl;
            cout << setw(18) << right << "5:01 pm to 6:59 am" <<
                 setw(25) << right << "Sun-Thurs" <<
                 setw(16) << right << "Any" <<
                 setw(11) << right << "0.45" << endl;
            cout << setw(18) << right << "Any" <<
                 setw(25) << right << "Fri-Sat" <<
                 setw(16) << right << "Any" <<
                 setw(11) << right << "0.25" << endl;

            if (dayName == "Fri" || dayName == "Sat")
            {
                cost = 0.25 * duration;
            }
            else if (startHour >= 7 && startHour <= 17)
            {
                if (duration < 15)
                    cost = 0.6 * duration;
                else
                    cost = 0.8 * duration;
            }
            else
                cost = 0.45 * duration;

            cout << "\n\nCall Rate: L.E " << cost;
            break;
        }
        case 'B':
        {
            cout << setw(18) << right << "7:00 am to 5:00 pm" <<
                 setw(25) << right << "Sun-Wed" <<
                 setw(16) << right << "<30 mins" <<
                 setw(11) << right << "0.6" << endl;
            cout << setw(18) << right << "7:00 am to 5:00 pm" <<
                 setw(25) << right << "Sun-Wed" <<
                 setw(16) << right << ">=30 mins" <<
                 setw(11) << right << "0.8" << endl;
            cout << setw(18) << right << "5:01 pm to 6:59 am" <<
                 setw(25) << right << "Sun-Wed" <<
                 setw(16) << right << "Any" <<
                 setw(11) << right << "0.45" << endl;
            cout << setw(18) << right << "Any" <<
                 setw(25) << right << "Thurs-Fri-Sat" <<
                 setw(16) << right << "Any" <<
                 setw(11) << right << "0.25" << endl;

            if (dayName == "Thurs" || dayName == "Fri" || dayName == "Sat")
            {
                cost = 0.25 * duration;
            }
            else if (startHour >= 7 && startHour <= 17)
            {
                if (duration < 30)
                    cost = 0.6 * duration;
                else
                    cost = 0.8 * duration;
            }
            else
                cost = 0.45 * duration;

            cout << "\n\nCall Rate: L.E " << ceil(cost);
            break;
        }
        default:
            cout << "The plan you entered doesn't exist!" << endl;
            return 1;
    }
}