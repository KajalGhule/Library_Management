#include <stdio.h>


struct Date {
    int day;
    int month;
    int year;
};

struct User {
    char username[50];
    char password[50];
    char userType[20]; // Owner/Librarian/Member
};

struct Member {
    int memberId;
    char memberName[100];
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
};

void inputDate(struct Date *d) {
    printf("Enter day, month, and year: ");
    scanf("%d %d %d", &d->day, &d->month, &d->year);
}
//function is use for display data
void displayDate(struct Date *d) {
    printf("%d %d %d\n", d->day, d->month, d->year);
}

// Function to check if a year is a leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a month
int daysInMonth(int month, int year) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month];
}

//function to adding additional days in given date
void addDaysInDate(struct Date *d,int days) {
    d->day += days;
    while(d->day > daysInMonth(d->month,d->year))
    {
        d->day -= daysInMonth(d->month,d->year);
        d->month++;
        if (d->month > 12)
        {
            d->month = 1;
            d->year++;
        }
    }
}


//function to find difference between two dates
int daysDiffer(struct Date *d1, struct Date *d2) { 
    int daysDifference = 0;
    while (d1->day != d2->day || d1->month != d2->month || d1->year != d2->year)
    {
        daysDifference++;
        d1->day++;
        if(d1->day > daysInMonth(d1->month,d1->year)) {
            d1->day = 1;
            d1->month++;
            if (d1->month > 12)
            {
                d1->month = 1;
                d1->year++;
            }
        }
    }
    return daysDifference;
}

int main () {
    //inpute and display date
    struct Date d1, d2;
    printf("Enter Date1 ");
    inputDate(&d1);
    displayDate(&d1);
    
    printf("Enter Date2 ");
    inputDate(&d2);
    displayDate(&d2);

    //add days in given date
    int addDays;
    printf("Add days in given date is ");
    scanf("%d",&addDays);
    addDaysInDate(&d1,addDays);
    displayDate(&d1);
    
    //difference between days
    int DifferenceInDays = daysDiffer(&d1,&d2);
    printf(" Difference Between Given Days %d", DifferenceInDays);
}

