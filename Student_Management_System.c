#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void getPassword(char *password, int maxLength);
typedef struct
{
    int id;
    char name[50];
    int age;
    char course[50];
    char category[20];
    int totalFees;
} Student;

typedef struct
{
    int id;
    char name[100];
    char password[30];
    int mobileNumber;
    char username[30];
} Employee;

// Fee structure based on category
int calculateFees(char category[])
{
    if (strcmp(category, "OPEN") == 0)
        return 192945;
    else if (strcmp(category, "OPEN OMS") == 0)
        return 193445;
    else if (strcmp(category, "OBC") == 0)
        return 111641;
    else if (strcmp(category, "EBC") == 0)
        return 111641;
    else if (strcmp(category, "EWS") == 0)
        return 111641;
    else if (strcmp(category, "SEBC") == 0)
        return 111641;
    else if (strcmp(category, "TFWS") == 0)
        return 30337;
    else if (strcmp(category, "VJ/DT/NT") == 0)
        return 30337;
    else if (strcmp(category, "SBC") == 0)
        return 30337;
    else if (strcmp(category, "SC") == 0)
        return 5945;
    else if (strcmp(category, "ST") == 0)
        return 5945;
    else if (strcmp(category, "OBC-GIRLS") == 0)
        return 30337;
    else if (strcmp(category, "EBC-GIRLS") == 0)
        return 30337;
    else if (strcmp(category, "EWS-GIRLS") == 0)
        return 30337;
    else if (strcmp(category, "SEBC-GIRLS") == 0)
        return 30337;
    else if (strcmp(category, "PH/PWD/ORPHAN") == 0)
        return 28977;
    else if (strcmp(category, "OVER and ABOVE") == 0)
        return 0;
    else if (strcmp(category, "J & K & GOI") == 0)
        return 30445;
    else if (strcmp(category, "J and K-PMSSS") == 0)
        return 6445;
    else
        return 0; // Default case
}

void showCategories()
{
    printf("\n=== Available Categories ===\n");
    printf("1. OPEN\n2. OPEN OMS\n3. OBC\n4. EBC\n5. EWS\n6. SEBC\n");
    printf("7. TFWS\n8. VJ/DT/NT\n9. SBC\n10. SC\n11. ST\n");
    printf("12. OBC-GIRLS\n13. EBC-GIRLS\n14. EWS-GIRLS\n15. SEBC-GIRLS\n");
    printf("16. PH/PWD/ORPHAN\n17. OVER and ABOVE\n18. J & K & GOI\n19. J and K-PMSSS\n");
}

void getCategoryFromChoice(int choice, char category[])
{
    switch (choice)
    {
    case 1:
        strcpy(category, "OPEN");
        break;
    case 2:
        strcpy(category, "OPEN OMS");
        break;
    case 3:
        strcpy(category, "OBC");
        break;
    case 4:
        strcpy(category, "EBC");
        break;
    case 5:
        strcpy(category, "EWS");
        break;
    case 6:
        strcpy(category, "SEBC");
        break;
    case 7:
        strcpy(category, "TFWS");
        break;
    case 8:
        strcpy(category, "VJ/DT/NT");
        break;
    case 9:
        strcpy(category, "SBC");
        break;
    case 10:
        strcpy(category, "SC");
        break;
    case 11:
        strcpy(category, "ST");
        break;
    case 12:
        strcpy(category, "OBC-GIRLS");
        break;
    case 13:
        strcpy(category, "EBC-GIRLS");
        break;
    case 14:
        strcpy(category, "EWS-GIRLS");
        break;
    case 15:
        strcpy(category, "SEBC-GIRLS");
        break;
    case 16:
        strcpy(category, "PH/PWD/ORPHAN");
        break;
    case 17:
        strcpy(category, "OVER and ABOVE");
        break;
    case 18:
        strcpy(category, "J & K & GOI");
        break;
    case 19:
        strcpy(category, "J and K-PMSSS");
        break;
    default:
        strcpy(category, "OPEN");
        break;
    }
}

void registration()
{
    Employee ep1;
    char pass1[30], pass2[30];
    FILE *res = fopen("registration.csv", "a");

    printf("Enter your Employee ID: ");
    scanf("%d", &ep1.id);
    printf("Enter your Name: ");
    scanf(" %[^\n]", ep1.name);
    printf("Enter your username: ");
    scanf(" %[^\n]", ep1.username);
    printf("Enter employee Mobile Number: ");
    scanf("%d", &ep1.mobileNumber);

    while (1)
    {
        printf("Enter your password: ");
        getPassword(pass1, 30);

        printf("Re-enter your password: ");
        getPassword(pass2, 30);

        if (strcmp(pass1, pass2) == 0)
        {
            strcpy(ep1.password, pass1);
            fprintf(res, "%d,%s,%s,%d,%s\n", ep1.id, ep1.name, ep1.username, ep1.mobileNumber, ep1.password);
            break;
        }
        printf("Password mismatch! Try again.\n");
    }
    fclose(res);
}
void forgotPassword()
{
    char username[30], newPassword[30];
    printf("Enter your username: ");
    scanf("%s", username);

    FILE *res = fopen("registration.csv", "r");
    if (!res) {
        printf("Could not open registration.csv!\n");
        return;
    }
    Employee ep;
    int found = 0;

    // Read all employees into memory
    Employee employees[1000];
    int count = 0;
    while (fscanf(res, "%d,%99[^,],%29[^,],%d,%29[^\n]", &ep.id, ep.name, ep.username, &ep.mobileNumber, ep.password) != EOF)
    {
        employees[count++] = ep;
    }
    fclose(res);

    // Find the user and update password
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].username, username) == 0) {
            found = 1;
            printf("Enter new password: ");
            getPassword(newPassword, 30);
            strcpy(employees[i].password, newPassword);
            break;
        }
    }

    if (found)
    {
        // Write all employees back to file
        res = fopen("registration.csv", "w");
        if (!res) {
            printf("Could not open registration.csv for writing!\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(res, "%d,%s,%s,%d,%s\n", employees[i].id, employees[i].name, employees[i].username, employees[i].mobileNumber, employees[i].password);
        }
        fclose(res);
        printf("Password updated successfully!\n");
    }
    else
    {
        printf("Username not found!\n");
    }
}



void getPassword(char *password, int maxLength)
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch(); 
        if (ch == 13)
        { 
            break;
        }
        else if (ch == 8)
        { 
            if (i > 0)
            {
                i--;
                printf("\b \b"); 
            }
        }
        else if (i < maxLength - 1)
        {
            password[i++] = ch;
            printf("*"); 
        }
    }
    password[i] = '\0'; 
    printf("\n");
}

int login(char uname[30], char pass[30])
{
    char data[500];
    FILE *res = fopen("registration.csv", "r");
    Employee ep;
    int found = 0;

    while (fgets(data, sizeof(data), res))
    {
        sscanf(data, "%d,%99[^,],%29[^,],%d,%29[^\n]", &ep.id, ep.name, ep.username, &ep.mobileNumber, ep.password);
        if (strcmp(uname, ep.username) == 0 && strcmp(pass, ep.password) == 0)
        {
            printf("\n<-- You are logged in -->\n");
            fclose(res);
            return 1;
        }
    }
    fclose(res);

    printf("Something went wrong!\n");
    char var;
    printf("Do you want to register first? (Y/N): ");
    scanf(" %c", &var);
    if (var == 'y' || var == 'Y')
    {
        registration();
    }
    else
    {
        char user[30], pass3[30];
        printf("Enter Username again: ");
        scanf("%s", user);
        printf("Enter Password again: ");
        getPassword(pass3, 30);
        printf("\n<-- You are logged in -->\n");
        return login(user, pass3);
    }
    return 0;
}

void showMenu()

{
    printf("=========================================\n");
    printf("      Student Management System in C\n");
    printf("=========================================\n");
    printf("[1] Add A New Student\n");
    printf("[2] Show All Students\n");
    printf("[3] Search Students by ID\n");
    printf("[4] Edit Student\n");
    printf("[5] Delete Student\n");
    printf("[6] Delete All Students\n");
    printf("[7] Calculate Fees by Category\n");
    printf("[8] User Guidelines\n");
    printf("[9] About Us\n");
    printf("[0] Exit\n");
}

void AddStudent()
{
    FILE *fp = fopen("file1.csv", "a");
    Student s;
    int categoryChoice;

    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    showCategories();
    printf("Select Category (1-19): ");
    scanf("%d", &categoryChoice);
    getCategoryFromChoice(categoryChoice, s.category);

    s.totalFees = calculateFees(s.category);

    fprintf(fp, "%d,%s,%d,%s,%s,%d\n", s.id, s.name, s.age, s.course, s.category, s.totalFees);
    fclose(fp);
    printf("Student added successfully.\n");
    printf("Category: %s | Total Fees: Rs. %d\n", s.category, s.totalFees);
}

void ShowAllStudents()
{
    FILE *fp = fopen("file1.csv", "r");
    Student s;
    char row[500];
    int number = 1;

    printf("\n=== All Students ===\n");
    while (fgets(row, sizeof(row), fp))
    {
        sscanf(row, "%d,%49[^,],%d,%49[^,],%19[^,],%d", &s.id, s.name, &s.age, s.course, s.category, &s.totalFees);
        printf("Student %d: ID: %d | Name: %s | Age: %d | Course: %s | Category: %s | Fees: Rs. %d\n",
               number++, s.id, s.name, s.age, s.course, s.category, s.totalFees);
    }
    fclose(fp);
}

void SearchStudent(int ID)
{
    FILE *fp = fopen("file1.csv", "r");
    Student s;
    char row[500];
    int found = 0;
    while (fgets(row, sizeof(row), fp))
    {
        sscanf(row, "%d,%49[^,],%d,%49[^,],%19[^,],%d", &s.id, s.name, &s.age, s.course, s.category, &s.totalFees);
        if (s.id == ID)
        {
            printf("Student found: ID: %d | Name: %s | Age: %d | Course: %s | Category: %s | Fees: Rs. %d\n",
                   s.id, s.name, s.age, s.course, s.category, s.totalFees);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Student not found.\n");
}

void EditStudent(int ID)
{
    FILE *fp = fopen("file1.csv", "r");
    FILE *fp1 = fopen("temp.csv", "w");
    Student s;
    char row[500];
    int found = 0;
    int categoryChoice;

    while (fgets(row, sizeof(row), fp))
    {
        sscanf(row, "%d,%49[^,],%d,%49[^,],%19[^,],%d", &s.id, s.name, &s.age, s.course, s.category, &s.totalFees);
        if (s.id == ID)
        {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new age: ");
            scanf("%d", &s.age);
            printf("Enter new course: ");
            scanf(" %[^\n]", s.course);

            showCategories();
            printf("Select new Category (1-19): ");
            scanf("%d", &categoryChoice);
            getCategoryFromChoice(categoryChoice, s.category);
            s.totalFees = calculateFees(s.category);
        }
        fprintf(fp1, "%d,%s,%d,%s,%s,%d\n", s.id, s.name, s.age, s.course, s.category, s.totalFees);
    }
    fclose(fp);
    fclose(fp1);
    remove("file1.csv");
    rename("temp.csv", "file1.csv");
    if (found)
        printf("Student information updated successfully.\n");
    else
        printf("Student not found.\n");
}

void DeleteStudent(int ID)
{
    FILE *fp = fopen("file1.csv", "r");
    FILE *fp1 = fopen("temp.csv", "w");
    Student s;
    char row[500];
    int found = 0;

    while (fgets(row, sizeof(row), fp))
    {
        sscanf(row, "%d,%49[^,],%d,%49[^,],%19[^,],%d", &s.id, s.name, &s.age, s.course, s.category, &s.totalFees);
        if (s.id == ID)
        {
            found = 1;
            continue;
        }
        fprintf(fp1, "%d,%s,%d,%s,%s,%d\n", s.id, s.name, s.age, s.course, s.category, s.totalFees);
    }
    fclose(fp);
    fclose(fp1);
    remove("file1.csv");
    rename("temp.csv", "file1.csv");
    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

void DeleteAllStudents()
{
    FILE *fp = fopen("file1.csv", "w");
    fclose(fp);
    printf("All student data deleted.\n");
}

void calculateFeesByCategory()
{
    int categoryChoice;
    char category[20];
    int fees;

    printf("\n=== Fee Calculator ===\n");
    showCategories();
    printf("Select Category to check fees (1-19): ");
    scanf("%d", &categoryChoice);

    getCategoryFromChoice(categoryChoice, category);
    fees = calculateFees(category);

    printf("\nCategory: %s\n", category);
    printf("Total Fees: Rs. %d\n", fees);

    // Show breakdown
    printf("\n=== Fee Breakdown ===\n");
    if (strcmp(category, "OPEN") == 0)
    {
        printf("Tuition Fees: Rs. 162608\n");
        printf("Development Fees: Rs. 24392\n");
        printf("Eligibility Fees: Rs. 600\n");
        printf("Exam Fees: Rs. 2200\n");
        printf("Misc. Univ Fees: Rs. 3145\n");
    }
    else if (strcmp(category, "SC") == 0 || strcmp(category, "ST") == 0)
    {
        printf("Tuition Fees: Rs. 0 (Exempted)\n");
        printf("Development Fees: Rs. 0 (Exempted)\n");
        printf("Eligibility Fees: Rs. 600\n");
        printf("Exam Fees: Rs. 2200\n");
        printf("Misc. Univ Fees: Rs. 3145\n");
    }
    // Add more breakdowns as needed
    printf("Total: Rs. %d\n", fees);
}

void showGuidelines()
{
    printf("-> Use menu numbers to navigate options.\n");
    printf("-> Enter correct student information.\n");
    printf("-> Select appropriate category for fee calculation.\n");
    printf("-> Use option [6] to delete all data.\n");
    printf("-> Use option [7] to calculate fees by category.\n");
}

void AboutUs()
{
    printf("Student Management System with Fee Calculator\n");
    printf("Developed in C Language\n");
    printf("Features: Student Management + Fee calculation based on Category\n");
    printf("By [Your Name]\n");
}

int main()
{
    while (1)
    {
        int initialization;
        printf("[1] Register\n[2] Login\n[3] Forgot password\n[0] Exit\nEnter your choice: ");
        scanf("%d", &initialization);

        if (initialization == 1)
        {
            registration();
        }
        else if (initialization == 2)
        {
            char user[30], pass[30];
            printf("Enter Username: ");
            scanf("%s", user);
            printf("Enter Password: ");
            getPassword(pass, 30);

            if (login(user, pass))
            {
                int choice;
                do
                {
                    showMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        AddStudent();
                        break;
                    case 2:
                        ShowAllStudents();
                        break;
                    case 3:
                    {
                        int id;
                        printf("Enter Student ID: ");
                        scanf("%d", &id);
                        SearchStudent(id);
                        break;
                    }
                    case 4:
                    {
                        int id;
                        printf("Enter Student ID to edit: ");
                        scanf("%d", &id);
                        EditStudent(id);
                        break;
                    }
                    case 5:
                    {
                        int id;
                        printf("Enter Student ID to delete: ");
                        scanf("%d", &id);
                        DeleteStudent(id);
                        break;
                    }
                    case 6:
                    {
                        char confirm;
                        printf("Are you sure you want to delete all data? (Y/N): ");
                        scanf(" %c", &confirm);
                        if (confirm == 'Y' || confirm == 'y')
                            DeleteAllStudents();
                        break;
                    }
                    case 7:
                        calculateFeesByCategory();
                        break;
                    case 8:
                        showGuidelines();
                        break;
                    case 9:
                        AboutUs();
                        break;
                    }
                } while (choice != 0);

            }
        }
        else if(initialization == 3)
        {
            forgotPassword();
        }
        else if (initialization == 0)
        {
            printf("Exiting program. Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice! Please try again.\n");
        }
        // printf("Exiting program. Goodbye!\n");
        char exitChoice;
        printf("Do you want to exit? (Y/N): ");
        scanf(" %c", &exitChoice);
        if (exitChoice == 'Y' || exitChoice == 'y')
        {
            printf("Exiting program. Goodbye!\n");
            break;
        }
    }
    return 0;
}