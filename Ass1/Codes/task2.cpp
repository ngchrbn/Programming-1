/*
    STUDENT NAME: NIYOMUKIZA RAMADHAN
    STUDENT ID: 20190812
*/
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int centerX, centerY, pointX, pointY;
    double distance; // distance between two points
    double radius; // radius r of the circle
    cout << "Enter coordinates of the center of the circle: ";
    cin >> centerX >> centerY;
    cout << "Enter the radius of the circle: ";
    cin >> radius;
    cout << "Enter coordinates of the point: ";
    cin >> pointX >> pointY;

    /* A point must be greater than 0
     * A radius must be greater than 0
     * If found error, terminates the execution
     */
    if (centerX < 0 || centerY < 0 ||
        pointX < 0 || pointY < 0) {
        cout << "\n==>A point cannot be negative";
        return 1;
    }
    if (radius < 0)
    {
        cout << "\n==>A radius cannot be negative";
        return 1;
    }
    // Calculate the distance between the two points
    distance = sqrt(pow((centerX - pointX), 2)
            + pow((centerY - pointY), 2));

    /*
     * if distance = radius, then the point is on the outer edge of the circle
     * if distance > radius, then the point is outside of the circle
     * if distance < radius, then the point is inside of the circle
     * As comparison between double and float is tricky,so we allow for an error
     * margin of 0.01, such that when the difference between distance and the radius
     * is less than 0.01, they are considered equal.
     */

    double difference = abs(distance - radius); // Difference between distance and radius
    if (distance == radius || (difference < 0.01)) {
        cout << "\nOn the circle" << endl;
    } else if (distance >radius) {
        cout << "\nOutside the circle" << endl;
    } else {
        cout << "\nInside the circle" << endl;
    }
    return 0;
}