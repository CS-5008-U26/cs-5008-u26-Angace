/* Day2 - Homework - Task 4
* Accept an integer from the user,
* and then prints an integer approximation to the area of a circle whose radius is the given integer
# folumar according to area = pi * (radius^2)
*/

#include <stdio.h>
#include <math.h>

int main () {

    // Variable to store the radius entered by the user and the value of pi
    int radius;  // integer variable to store the radius entered by the user
    double pi = acos(-1); // Calculate the value of pi using the arccosine function

    // Prompt the user to enter the radius of the circle and read the input
    printf("Enter an ingerer radius: "); 
    scanf("%d", &radius); 

    // Calculate the area of the circle using the formula
    int area = (int)(pi) * (radius * radius);

    // Print the area of the circle as an integer
    printf("For a circle of radius %d.0 the area is : %d\n", radius, area);  // Print the area of the circle with two decimal places

    return 0;  // Return 0 to indicate that the program ended successfully
}