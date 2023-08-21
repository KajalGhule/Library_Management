#include <stdio.h>
#include <string.h>
#include <conio.h>


#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 10
#define MAX_USERTYPE_SIZE 10
#define MAX_USERS 3
#define MAX_BOOKS 3

struct Date {
    int day;
    int month;
    int year;
};

// struct User {
//     int memberId;
//     char memberName[MAX_USERNAME_SIZE];
//     char email;
//     char password[MAX_PASSWORD_SIZE];
//     struct Date joinDate;
//     int isPaidUser;
//     float fineAmount;
//     char userType[MAX_USERTYPE_SIZE]; // Owner/Librarian/Member
// };

typedef struct {
    int memberId;
    char username[MAX_NAME_LENGTH];
    char email[15];
    char password[MAX_PASSWORD_LENGTH];
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
    char userType[MAX_USERTYPE_SIZE]; // Owner/Librarian/Member
} User;

struct Book{
    int bookId;
    char bookName[100];
    char authorName[50];
    char subject[50];
    float bookPrice;
    int isbn;
};

struct Library {
    struct Book books[MAX_BOOKS];
    int count;
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

User users[MAX_USERS];
int userCount = 0;

int signUp() {
    printf("inside sign-up function\n");
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return 0;
    }

    User newUser;
    printf("Enter a username: ");
    scanf("%s", &newUser.username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(newUser.username, users[i].username) == 0) {
            printf("Username already exists.\n");
            return 0;
        }
    }

    printf("Enter a password: ");
    scanf("%s", &newUser.password);

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
            return 0;
    }

    users[userCount++] = newUser;
    printf("*******************\n");
    printf("Sign-up successful!\n");
    printf("*******************\n");
    return 1;
}


void ownerMenu() {
    // Implement owner menu
    printf("Owner Menu\n");
}


void addNewBook(struct Library *library, const char *title) {
    for (int i = 0; i < library->count; i++) {
        if (strcmp(library->books[i].bookName, title) == 0) {
            printf("Book already exists. Increasing count.\n");
            return;
        }
    }
    
    if (library->count < MAX_BOOKS) {
        strcpy(library->books[library->count].bookName, title);
        printf("Enter Author Name: \n");
        scanf("%s", &library->books[library->count].authorName);
        printf("Enter Book subject: \n");
        scanf("%s", &library->books[library->count].subject);
        printf("Enter Book Price: \n");
        scanf("%f", &library->books[library->count].bookPrice);
        printf("Enter Book isbn: \n");
        scanf("%d", &library->books[library->count].isbn);
        library->count++;
        printf("Book added successfully.\n");
        printf("*******************\n");
    } else {
        printf("Library is full. Cannot add more books.\n");
        printf("*******************\n");
    }
}


void findBook(struct Library *library, const char *title) {
    for (int i = 0; i < library->count; i++) {
        if (strcmp(library->books[i].bookName, title) == 0) {
            printf("Book found:\n");
            printf("*********Books Details**********\n");
            printf("Book Name: %s\n", library->books[i].bookName);
            printf("Auther Name: %s\n", library->books[i].authorName);
            printf("Book Subject: %s\n", library->books[i].subject);
            printf("Book Price: %0.3f\n", library->books[i].bookPrice);
            printf("Book isbn: %d\n", library->books[i].isbn);
            printf("*******************\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void displayAllBooks(struct Library *library) {
    if (library->count == 0) {
        printf("Library is empty.\n");
        return;
    }

    printf("Books in the library:\n");
    for (int i = 0; i < library->count; i++) {
        printf("\n");
        printf("Book %d:\n", i + 1);
        printf("Book Name: %s\n", library->books[i].bookName);
        printf("Author Name: %s\n", library->books[i].authorName);
        printf("Book Price: %0.3f\n", library->books[i].bookPrice);
        printf("Book Subject: %s\n", library->books[i].subject);
        printf("Book isbn: %d\n", library->books[i].isbn);
        printf("\n");
    }
}

void librarianMenu() {
    // Implement librarian menu
    struct Library library;
    library.count = 0;
    char bookName[100];
    int choice;
    printf("*******************\n");
    printf("Librarian Menu\n");
    printf("*******************\n");
    do {
        printf("0. Exit\n");
        printf("1. Add New Book\n");
        printf("2. Find Book By Name\n");
        printf("3. Find All Books \n");
        printf("4. Issue Copy\n");
        printf("Enter Your Choice : \n");
        scanf("%d",&choice);
        printf("*******************\n");
        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            break;    
        case 1:
            printf("Enter Book Name\n");
            scanf("%s",&bookName);
            addNewBook(&library,bookName);
            printf("Book count: %d\n", library.count);
            // printf("%d",library.count);
            break;
        case 2:
            printf("Enter Book Name to search: \n");
            scanf("%s", &bookName);
            findBook(&library, bookName);
            break;
        case 3:
            displayAllBooks(&library);
            break;
        case 4:
            /* code */
            break;        
        default:
            break;
        }
    }while (choice != 0);
    
    
}

void memberMenu() {
    // Implement member menu
    printf("Member Menu\n");
}


 
int signIn() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", &username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0) {
            printf("Enter your password: ");
            scanf("%s", &password);

            if (strcmp(password, users[i].password) == 0) {
                printf("*******************\n");
                printf("Sign-in successful!\n");
                printf("*******************\n");
                // return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
        // Validate user and set user type
    if (strcmp(users[i].userType, "Owner") == 0) {
        ownerMenu();
        return 1;
    } else if (strcmp(users[i].userType, "Librarian") == 0) {
        librarianMenu();
        return 1;
    } else if (strcmp(users[i].userType, "Member") == 0) {
        memberMenu();
        return 1;
    } else {
        printf("Invalid user type.\n");
    }
    }

    printf("Username not found.\n");
    return 0;
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

