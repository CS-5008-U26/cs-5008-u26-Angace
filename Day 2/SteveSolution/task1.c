#include <stdio.h>

int main() 
{ 
    char s[100];
    int rate;
    int hour;

    while (1)
    {
        printf("Enter an hourly rate: ");
        scanf("%d", &rate);
        if (rate <= 0) 
        { 
            break; 
        }

        printf("Enter the number of hours worked: ");
        scanf("%d", &hour);
        if (hour <= 0) {
            break; 
        }

        if (hour <= 40) {
            printf("You should be paid %d\n", rate * hour);
        } else {
            printf("You should be paid %d\n", (rate * 40) + (rate * 1.5) * (hour - 40));
        }
    }

    fgets(s,100,stdin); // pause the console and still see it before it disappears
}

