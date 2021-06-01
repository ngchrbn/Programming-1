/*
    STUDENT NAME: NIYOMUKIZA RAMADHAN
    STUDENT ID: 20190812
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double temperature, speed, tWind_Chill; // Stores the temperature in celsius, speed in kph and tWind_Chill respectively
    cout << "Please enter the temperature in degrees Celsius: ";
    cin >> temperature; // Get the temperature
    
    /**
     * Checks if the temperature is between -50 and 5 inclusive. If yes, get the speed and checks also if it is
     * greater than or equal to 4. If yes, calculate the wind-chill with this formula:
     * TWind-chill = 13.12 + 0.6215T - 11.37Vpow(0.16) + 0.3965TVpow(0.16).
     * And return to the user with a precision of 2 for the wind-chill temperature
     * If No, output a message to the user that the speed must be greater or equal to 4.
     * If No, output a message to the user that the temperature must be between -50 and 5 inclusive
     */
     
    if (temperature < -50 || temperature > 5) {
        cout << "The temperature must be between -50 and 5 degree celsius" << endl;
    } else {
        cout << "Please enter the wind in kilometers per hour: ";
        cin >> speed; // Get the speed
        if (speed < 4) {
            cout << "The wind speed must be greater than or equal to 4 kilometers per hour" << endl;
        } else {
            tWind_Chill = 13.12 + (0.6215 * temperature) - (11.37 * pow(speed, 0.16))
                    + (0.3965 * temperature * pow(speed, 0.16)); // Calculates the wind-chill temperature
            cout << "The wind chill temperature is: " << fixed << setprecision(2) << tWind_Chill;
        }
    }
    return 0;
}
