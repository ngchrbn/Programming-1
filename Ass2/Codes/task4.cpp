/*
    STUDENT NAME: NIYOMUKIZA RAMADHAN
    STUDENT ID: 20190812
*/

#include <iostream>

#define MAX_PARKING_FEES 25
#define MAX_ACCOMMODATION 500
#define MAX_BREAKFAST_FEES 40
#define MAX_LUNCH_FEES 60
#define MAX_DINNER_FEES 80
#define MAX_PER_KILOMETER 0.775
#define MAX_TAXI_PER_DAY 100

using namespace std;

double * getTripInfo();

int getTravelMode();

int getDays();

int *getTimeInfo();

double *getTravelModeCost(int travelMode);

double *getRefund(int numDays, const int *pInt, int mode, const double *pDouble, const double *pDouble1);

int main()
{
    int numDays = getDays();
    int *timePtr = getTimeInfo();
    int travelMode = getTravelMode();
    double *travelModePtr = getTravelModeCost(travelMode);
    cout << travelModePtr << endl;
    double *tripInfoPtr = getTripInfo();

    double *totalPtr = getRefund(numDays, timePtr, travelMode, travelModePtr, tripInfoPtr);
    cout << "\n\nThe total expenses paid by the employee (not including non-permissible meals) : "
        << *(totalPtr+2) << " EGP" << endl;
    cout << "\n\nFor this trip, the refund sum will be: " << *(totalPtr) << " EGP"<<  endl;
    cout << "\n\nFor this trip, the rejected sum will be: " << *(totalPtr+1) << " EGP" << endl;


    return 0;
}

double *getRefund(int numDays, const int *pInt, int mode, const double *pDouble, const double *pDouble1) {
    double refundSum = 0, rejectedSum = 0;
    static double result[3];
    if (mode == 1)
    {
        refundSum += pDouble[0];
    }

    else if (mode == 2)
    {
        refundSum += pDouble[0] + (((MAX_PARKING_FEES*numDays) > pDouble[1]) ? pDouble[1] : (MAX_PARKING_FEES*numDays));
        rejectedSum += ((MAX_PARKING_FEES*numDays) > pDouble[1]) ? 0 : (pDouble[1] - (MAX_PARKING_FEES*numDays));
    }
    else if (mode == 3)
    {
        refundSum += pDouble[0]*MAX_PER_KILOMETER + (((MAX_PARKING_FEES*numDays) > pDouble[1]) ? pDouble[1] : (MAX_PARKING_FEES*numDays));
        rejectedSum += ((MAX_PARKING_FEES*numDays) > pDouble[1]) ? 0 : (pDouble[1] - (MAX_PARKING_FEES*numDays));
    }
    // For the conferences and accommodations
    refundSum += pDouble1[0] + ((MAX_ACCOMMODATION*numDays > pDouble1[1]) ? pDouble1[1]: (MAX_ACCOMMODATION*numDays));
    rejectedSum += ((MAX_ACCOMMODATION*numDays > pDouble1[1]) ? 0 : (pDouble1[1] - MAX_ACCOMMODATION*numDays));

    // For breakfast, lunch and dinners for first day
    double breakfastRefSum = 0, lunchRefundSum = 0, dinnerRefundSum = 0;
    if (pInt[0] < 8)
        breakfastRefSum += MAX_BREAKFAST_FEES;
    if (pInt[0] < 12)
        lunchRefundSum += MAX_LUNCH_FEES;
    if (pInt[0] < 18)
        dinnerRefundSum += MAX_DINNER_FEES;

    refundSum += ((breakfastRefSum + lunchRefundSum + dinnerRefundSum) > (pDouble1[2] + pDouble1[3] + pDouble1[4])) ?
        (pDouble1[2] + pDouble1[3] + pDouble1[4]) : (breakfastRefSum + lunchRefundSum + dinnerRefundSum);
    rejectedSum += ((breakfastRefSum + lunchRefundSum + dinnerRefundSum) > (pDouble1[2] + pDouble1[3] + pDouble1[4])) ?
            0 : ((pDouble1[2] + pDouble1[3] + pDouble1[4]) - (breakfastRefSum + lunchRefundSum + dinnerRefundSum));

    // For breakfast, lunch and dinners for last day
    double lBreakfastRefSum = 0, lLunchRefundSum = 0, lDinnerRefundSum = 0;
    if (pInt[1] > 9)
        lBreakfastRefSum += MAX_BREAKFAST_FEES;
    if (pInt[1] > 13)
        lLunchRefundSum += MAX_LUNCH_FEES;
    if (pInt[1] > 19)
        lDinnerRefundSum += MAX_DINNER_FEES;

    refundSum += ((lBreakfastRefSum + lLunchRefundSum + lDinnerRefundSum) > (pDouble1[5] + pDouble1[6] + pDouble1[7])) ?
                 (pDouble1[5] + pDouble1[6] + pDouble1[7]) : (lBreakfastRefSum + lLunchRefundSum + lDinnerRefundSum);
    rejectedSum += ((lBreakfastRefSum + lLunchRefundSum + lDinnerRefundSum) > (pDouble1[5] + pDouble1[6] + pDouble1[7])) ?
                   0 : ((pDouble1[5] + pDouble1[6] + pDouble1[7]) - (lBreakfastRefSum + lLunchRefundSum + lDinnerRefundSum));

    // For the taxi
    refundSum += (((MAX_TAXI_PER_DAY * numDays) > pDouble1[8]) ? pDouble1[8] :
                  (MAX_TAXI_PER_DAY * numDays) );
    rejectedSum += (((MAX_TAXI_PER_DAY * numDays) > pDouble1[8]) ? 0 :
                    (pDouble1[8] - (MAX_TAXI_PER_DAY * numDays)));

    result[0] = refundSum;
    result[1] = rejectedSum;

    // This calculates the reject amount for the non-permissible meals
    result[2] = refundSum - (((breakfastRefSum + lunchRefundSum + dinnerRefundSum) > (pDouble1[2] + pDouble1[3] + pDouble1[4])) ?
                0 : ((pDouble1[2] + pDouble1[3] + pDouble1[4]) - (breakfastRefSum + lunchRefundSum + dinnerRefundSum)));
    return result;
}


double *getTravelModeCost(int travelMode) {

    double planeTicketCost, carRentalFees, numKilometers, parkingFees;
    if (travelMode == 1)
    {
        cout << "Enter plane ticket cost: ";
        cin >> planeTicketCost;

        static double travelModeCosts[1];
        travelModeCosts[0] = planeTicketCost;
        return travelModeCosts;
    }
    else if (travelMode == 2)
    {
        cout << "Enter car rental fees: ";
        cin >> carRentalFees;
    }
    else if (travelMode == 3)
    {
        cout << "Enter the number of kilometers: ";
        cin >> numKilometers;
        while (numKilometers < 0)
        {
            cout << "\n==>Kilometers cannot be negative!";
            cout << "\nEnter the number of kilometers: ";
            cin >> numKilometers;
        }
    }

    if (travelMode == 2 || travelMode == 3)
    {
        cout << "Enter the parking fees: ";
        cin >> parkingFees;

        static double travelModeCosts[2];
        if (travelMode == 2)
        {
            travelModeCosts[0] = carRentalFees;
            travelModeCosts[1] = parkingFees;
        }
        else {
            travelModeCosts[0] = numKilometers;
            travelModeCosts[1] = parkingFees;
        }
        return travelModeCosts;
    }
    return nullptr;
}

int *getTimeInfo() {
    static int timeInfo[2];
    int departureTime, arrivalTime;
    cout << "Enter Departure time (24 hours format): ";
    cin >> departureTime;
    while(departureTime < 0 || departureTime > 23)
    {
        cout << "\n==>Time must be in 24-hour format!";
        cout << "\nEnter Departure time (24 hours format): ";
        cin >> departureTime;
    }
    timeInfo[0] = departureTime;

    cout << "Enter Arrival time (24 hours format): ";
    cin >> arrivalTime;
    while(arrivalTime < 0 || arrivalTime > 23)
    {
        cout << "\n==>Time must be in 24-hour format!";
        cout << "\nEnter Arrival time (24 hours format): ";
        cin >> arrivalTime;
    }
    timeInfo[1] = arrivalTime;
    return timeInfo;
}

int getDays() {
    int numDays;
    cout << "How many days did you spend on the trip? ";
    cin >> numDays;
    return numDays;
}

double * getTripInfo()
{
    static double tripInfo[9];

    char attended;
    cout << "Did you attend any conferences or seminar that you had to pay? ";
    cin >> attended;
    while(attended != 'Y' && attended != 'N')
    {
        cout << "\n==>You have to choose between Y or N!";
        cout << "\nEnter your choice: ";
        cin >> attended;
    }
    if (attended == 'Y')
    {
        double conferenceFees;
        cout << "Enter conference or seminars fees: ";
        cin >> conferenceFees;
        tripInfo[0] = conferenceFees;
    }
    else if (attended == 'N') tripInfo[0] = 0.0;

    double accommodationFees;
    cout << "Enter Accommodation fees: ";
    cin >> accommodationFees;
    tripInfo[1] = accommodationFees;

    double fBreakfastFees, fLunchFees, fDinnerFees, lBreakfastFees, lLunchFees, lDinnerFees;
    cout << "Breakfasts, Meals, and dinners" << endl;
    cout << "For the first day: " << endl;
    cout << "Enter Breakfast fees (enter 0 if no taken):";
    cin >> fBreakfastFees;
    tripInfo[2] = fBreakfastFees;
    cout << "Enter Lunch fees (enter 0 if no taken):";
    cin >> fLunchFees;
    tripInfo[3] = fLunchFees;
    cout << "Enter Dinner fees (enter 0 if no taken):";
    cin >> fDinnerFees;
    tripInfo[4] = fDinnerFees;

    cout << "For the last day: " << endl;
    cout << "Enter Breakfast fees (enter 0 if no taken):";
    cin >> lBreakfastFees;
    tripInfo[5] = lBreakfastFees;
    cout << "Enter Lunch fees (enter 0 if no taken):";
    cin >> lLunchFees;
    tripInfo[6] = lLunchFees;
    cout << "Enter Dinner fees (enter 0 if no taken):";
    cin >> lDinnerFees;
    tripInfo[7] = lDinnerFees;

    double taxiFees;
    cout << "Enter the fees for the taxis you took: ";
    cin >> taxiFees;
    tripInfo[8] = taxiFees;

    return tripInfo;
}

int getTravelMode() {
    int choice;
    cout << "\n1. Travelled by plane."
        << "\n2. Travelled on a rented car"
        << "\n3. Travelled with your own car";
    cout << "\nYour choice: ";
    cin >> choice;
    while (choice <0 || choice > 3)
    {
        cout << "\n==> You must choose from those options!";
        cout << "\n1. Travelled by plane."
             << "\n2. Travelled on a rented car"
             << "\n3. Travelled with your own car";
        cin >> choice;
    }
    return choice;
}
