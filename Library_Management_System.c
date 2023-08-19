#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <string.h>

#define MAX_USERNAME_SIZE 50
#define MAX_PASSWORD_SIZE 10
#define MAX_USERTYPE_SIZE 10
struct Date {
    int day;
    int month;
    int year;
};

struct User_Creaditial {
    char userEmail;
    char password[MAX_PASSWORD_SIZE];
    
};

struct User {
    int memberId;
    char memberName[MAX_USERNAME_SIZE];
    char email;
    char password[MAX_PASSWORD_SIZE];
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
    char userType[MAX_USERTYPE_SIZE]; // Owner/Librarian/Member
};

struct User users[5];

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

//function to Sign Up
int signUp() {
    
    struct User newUser;
    newUser.memberId = 0;
    printf("Enter user Email\n");
    scanf("%s",&newUser.email);
    for(int i=0; i<5; i++) {
        // printf("inside for loop\n");
        int result = strcmp(&newUser.email, &users[i].email);
        if(result == 0) {
            printf("User is already exit");
            return 0;
        }
        
    }

    printf("Enter user Password\n");
    scanf("%s",&newUser.password);

    printf("Enter user Name\n");
    scanf("%s",&newUser.memberName);
    
    printf("Enter user isPaidUser \n");
    scanf("%d",&newUser.isPaidUser);
    
    printf("Enter user amount\n");
    scanf("%f",&newUser.fineAmount);
    
    int userTypeChoice;

    printf("Select the user type:\n");
    printf("1. Member\n");
    printf("2. Owner\n");
    printf("3. Librarian\n");
    printf("Enter your choice: ");
    scanf("%d", &userTypeChoice);
    

    switch (userTypeChoice) {
        case 1:
            strcpy(newUser.userType, "Member");
            break;
        case 2:
            strcpy(newUser.userType, "Owner");
            break;
        case 3:
            strcpy(newUser.userType, "Librarian");
            break;
        default:
            printf("Invalid user type selection.\n");
            break;
    }
    printf("Sign up successfully !!\n");
    return 1;
}

void ownerMenu() {
    printf("Inside owner menu");
}

void librarianMenu() {
    printf("####");
}

void memberMenu() {
    printf("*****");
}

//function to sign in
int signIn() {
    char email;
    char password[MAX_PASSWORD_SIZE];

    printf("Enter your email: ");
    scanf("%s", &email);

    for (int i = 0; i < 5; i++) {
        if (strcmp(email, users[i].email) == 0) {
            printf("Enter your password: ");
            scanf("%s", &password);

            if (strcmp(password, users[i].password) == 0) {
                printf("Sign-in successful!\n");
                if (strcmp(users[i].userType, "Owner") == 0) {
                        ownerMenu();
                } else if (strcmp(users[i].userType, "Librarian") == 0) {
                        librarianMenu();
                } else if (strcmp(users[i].userType, "Member") == 0) {
                        memberMenu();
                } else {
                    printf("Invalid user type.\n");
                }
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
}




int main () {
    //inpute and display date
    struct Date d1, d2;
    // printf("Enter Date1 ");
    // inputDate(&d1);
    // displayDate(&d1);
    
    // printf("Enter Date2 ");
    // inputDate(&d2);
    // displayDate(&d2);

    int differenceInDays;
    int addDays;
    int choice;
    do {
       
        printf("0. Exit\n");
        printf("1. Sign In\n");
        printf("2. Sign Up\n");
        printf("3. Find difference between days\n");
        printf("4. add days in given date\n");
        // printf("");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 0:
             printf("Exiting....");
             break;    
        case 1:
            signIn();
            break;
        case 2:
            signUp();
            break;
        case 3:
            //difference between days
            differenceInDays = daysDiffer(&d1,&d2);
            printf(" Difference Between Given Days %d", differenceInDays);  
            break;  
        case 4:
            //add days in given date
            
            printf("Add days in given date is ");
            scanf("%d",&addDays);
            addDaysInDate(&d1,addDays);
            displayDate(&d1);
        default:
             printf("Invalid Choice...Enter Valid choice");
            break;
        }
    }while (choice != 0);
    
}

