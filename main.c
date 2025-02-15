/*
Admin 'Pinewood'
    username: admin1
    password: pass1

Admin 'Ironbite'
    username: admin2
    password: pass2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//userinfo structure
typedef struct{
    char username[50];
    char password[20];
    int userID;
} User;

typedef struct{
        char itemName[50];
        int quantity;
        float price;
    } Item;

//orderinfo structre
typedef struct{
    int orderNumber;
    int userID;
    char vendor[50];
    int itemCount;
    Item items[10];
    char date[20];
    char paymentStatus[10];
    float totalBill;
} Order;

//menu structure
typedef struct{
    char itemName[50];
    float price;
    int orderedAmount;
} MenuItem;

#define MAX_USERS 100
#define MAX_ORDERS 1000
#define MAX_ITEMS 100

User users[MAX_USERS];
int userCount = 0;

Order orders[MAX_ORDERS];
int orderCount = 0;

MenuItem pinewoodMenu[MAX_ITEMS];
int pinewoodItemCount = 0;

MenuItem ironbiteMenu[MAX_ITEMS];
int ironbiteItemCount = 0;

// Admin credential
char admin1Username[] = "admin1";
char admin1Password[] = "pass1";
char admin2Username[] = "admin2";
char admin2Password[] = "pass2";


void registerUser()
{
    if (userCount >= MAX_USERS)
    {
        printf("User database is full!\n");
        return;
    }
    User newUser;
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb USER REGISTRATION \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t******************************\n\n");
    printf("\t\tEnter username and password to register \n\n");
    printf("\t\tUsername: ");
    scanf("%s", newUser.username);
    printf("\t\tPassword: ");
    scanf("%s", newUser.password);
    newUser.userID = userCount + 1;

    users[userCount++] = newUser;
    saveUsers();
    printf("\t\tRegistering your account...\n");
    printf("\n");
    sleep(2);
    printf("\t\tRegistration successful! \n\t\tYour user ID is: %d\n", newUser.userID);
}
int userLogin()
{
    char username[50], password[20];
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb USER LOGIN \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t*************************\n\n");
    printf("\t\tEnter your username and password to log in. \n\n");
    printf("\t\tUsername: ");
    scanf("%s", username);
    printf("\t\tPassword: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("\t\tLogin successful! Loading user dashboard...\n");
            return users[i].userID;
        }
    }
    printf("\t\tInvalid username or password.\n");
    return -1;
}
int adminLogin()
{
    char username[50], password[20];
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb ADMIN LOGIN \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t*************************\n\n");
    printf("\t\tEnter your username and password to log in. \n\n");
    printf("\t\tUsername: ");
    scanf("%s", username);
    printf("\t\tPassword: ");
    scanf("%s", password);

    if (strcmp(username, admin1Username) == 0 && strcmp(password, admin1Password) == 0)
    {
        printf("\t\tLogin successful for \"Pinewood\" vendor. \n\t\tLoading admin dashboard...\n");
        return 1;
    }
    else if (strcmp(username, admin2Username) == 0 && strcmp(password, admin2Password) == 0)
    {
        printf("\t\tLogin successful for \"Ironbite\" vendor. \n\t\tLoading admin dashboard...\n");
        return 2;
    }
    printf("\t\tInvalid admin credentials.\n");
    return -1;
}
void userMenu(int userID)
{
    int choice;
    while (1)
    {
        printf("\t\t#####################################################\n");
        printf("\t\t#########                                   #########\n");
        printf("\t\t#########  NSU CAFETERIA MANAGEMENT SYSTEM  #########\n");
        printf("\t\t#########                                   #########\n");
        printf("\t\t#####################################################\n");
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t                    USER DASHBOARD                   \n");
        printf("\t\t-----------------------------------------------------\n");
        printf("\n");
        printf("\t\t 1. Preorder Meals\n");
        printf("\t\t 2. View Order Receipt\n");
        printf("\t\t 3. Cancel an Order\n");
        printf("\t\t 4. Logout\n\n");
        printf("\t\t-----------------------------------------------------\n\n");

        printf("\t\tChoose an option: ");
        scanf("%d", &choice);
        getchar();

        system("cls");
        switch (choice)
        {
        case 1:
            preorder(userID);
            sleep(3);
            system("cls");
            break;
        case 2:
            viewReceipt(userID);
            sleep(5);
            system("cls");
            break;
        case 3:
            cancelOrder(userID);
            sleep(3);
            system("cls");
            break;
        case 4:
            printf("\t\tLogging out...\n");
            sleep(2);
            system("cls");
            return;
        default:
            printf("\t\tInvalid choice. Please try again.\n");
        }
    }
}
void preorder(int userID)
{
    int vendorChoice, itemChoice, quantity;
    Order newOrder;
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb VENDORS \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t*********************\n\n");
    printf("\t\t1. Pinewood\n");
    printf("\t\t2. Ironbite\n\n");
    printf("\t\t---------------------\n\n");
    printf("\t\tChoose an option: ");
    scanf("%d", &vendorChoice);

    MenuItem *menu;
    int *itemCount;
    if (vendorChoice == 1)
    {
        menu = pinewoodMenu;
        itemCount = &pinewoodItemCount;
    }
    else if (vendorChoice == 2)
    {
        menu = ironbiteMenu;
        itemCount = &ironbiteItemCount;
    }
    else
    {
        printf("\t\tInvalid vendor choice!\n");
        return;
    }

    newOrder.orderNumber = orderCount + 1;
    newOrder.userID = userID;
    strcpy(newOrder.vendor, vendorChoice == 1 ? "Pinewood" : "Ironbite");
    newOrder.itemCount = 0;
    newOrder.totalBill = 0.0;

    printf("\t\tEnter date (DD/MM/YYYY): ");
    scanf("%s", newOrder.date);
    printf("\n");
    strcpy(newOrder.paymentStatus, "Due");

    char choice;
    printf("\t\t#####################################################\n");
    printf("\t\t#########           Order & Smile!          #########\n");
    printf("\t\t#####################################################\n");
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb IRONBITE MENU \xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\n");
    printf("\n\t\tItem\t-\tPrice");
    printf("\n\t\t------------------------------\n\n");
    for (int i = 0; i < *itemCount; i++)
    {
        printf("\t\t%d. %s - \t$%2.2f\n", i + 1, menu[i].itemName, menu[i].price);
    }
    printf("\t\t------------------------------\n\n");
    do
    {
        printf("\t\tSelect item number: ");
        scanf("%d", &itemChoice);
        if (itemChoice < 1 || itemChoice > *itemCount)
        {
            printf("Invalid item selection.\n");
            continue;
        }

        printf("\t\tEnter quantity: ");
        scanf("%d", &quantity);


        int currentItem = newOrder.itemCount;
        strcpy(newOrder.items[currentItem].itemName, menu[itemChoice - 1].itemName);
        newOrder.items[currentItem].quantity = quantity;
        newOrder.items[currentItem].price = menu[itemChoice - 1].price;
        newOrder.itemCount++;

        // total bill
        newOrder.totalBill += menu[itemChoice - 1].price * quantity;

        menu[itemChoice - 1].orderedAmount += quantity;

        printf("\t\tDo you want to add another item? (y/n): ");
        scanf(" %c", &choice);
    }
    while (choice == 'y' || choice == 'Y');

    orders[orderCount++] = newOrder;

    saveOrders();
    printf("\t\tProcessing order...\n");
    sleep(3);
    printf("\n\t\t---------------------------------------------------------\n\n");
    printf("\t\tOrder placed successfully! \n\t\tYour order no: %d and total payable amount: $%.2f\n",
           newOrder.orderNumber, newOrder.totalBill);
}
void viewReceipt(int userID)
{
    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb ORDER RECEIPT \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t***************************\n\n");
    printf("\n\t\tUser ID: %d\n", userID);
    int found = 0;
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].userID == userID)
        {
            printf("\t\tOrder Number: %d\n", orders[i].orderNumber);
            printf("\t\tVendor: %s\n", orders[i].vendor);
            printf("\t\tDate: %s\n", orders[i].date);
            printf("\t\tItems Ordered:\n");
            for (int j = 0; j < orders[i].itemCount; j++)
            {
                printf("\t\t\t-%s : %dpcs\n",
                       orders[i].items[j].itemName,
                       orders[i].items[j].quantity);
            }

            printf("\t\tTotal Payable Amount: $%.2f\n", orders[i].totalBill);
            printf("\t\tPayment Status: %s\n", orders[i].paymentStatus);
            printf("\n\t\t---------------------------------\n");
            found = 1;
        }
    }
    if (!found)
    {
        printf("\t\tNo orders found for this User ID.\n");
    }
}
void cancelOrder(int userID)
{
    int orderNumber, found = 0;

    printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb CANCEL ORDER \xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t***************************\n\n");
    printf("\t\tEnter the order number you want to cancel: ");
    scanf("%d", &orderNumber);

    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].orderNumber == orderNumber && orders[i].userID == userID)
        {
            found = 1;

            MenuItem *menu = strcmp(orders[i].vendor, "Pinewood") == 0 ? pinewoodMenu : ironbiteMenu;
            int itemCount = strcmp(orders[i].vendor, "Pinewood") == 0 ? pinewoodItemCount : ironbiteItemCount;

            for (int j = 0; j < orders[i].itemCount; j++)
            {
                for (int k = 0; k < itemCount; k++)
                {
                    if (strcmp(menu[k].itemName, orders[i].items[j].itemName) == 0)
                    {
                        menu[k].orderedAmount -= orders[i].items[j].quantity;
                        break;
                    }
                }
            }

            for (int j = i; j < orderCount - 1; j++)
            {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            saveOrders();
            printf("\t\tCancelling your order...\n");
            sleep(2);
            printf("\t\tOrder canceled successfully.\n");
            return;
        }
    }

    if (!found)
    {
        printf("\t\tOrder not found or doesn't belong to you.\n");
    }
}
void adminMenu(int vendorID)
{
    int choice;
    while (1)
    {
        printf("\t\t#####################################################\n");
        printf("\t\t#########                                   #########\n");
        printf("\t\t#########  NSU CAFETERIA MANAGEMENT SYSTEM  #########\n");
        printf("\t\t#########                                   #########\n");
        printf("\t\t#####################################################\n");
        printf("\t\t-----------------------------------------------------\n");
        printf("\t\t                   ADMIN DASHBOARD                   \n");
        printf("\t\t-----------------------------------------------------\n");
        printf("\n");
        printf("\t\t 1. View Menu\n");
        printf("\t\t 2. Update Order Status\n");
        printf("\t\t 3. Edit Menu Items\n");
        printf("\t\t 4. Logout\n\n");
        printf("\t\t-----------------------------------------------------\n\n");

        printf("\t\tChoose an option: ");
        scanf("%d", &choice);
        getchar();

        system("cls");
        switch (choice)
        {
        case 1:
            if (vendorID == 1)
            {

                printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb PINEWOOD MENU \xdb\xdb\xdb\xdb\xdb\xdb\n");
                printf("\n\t\tItem\t-\tPrice");
                printf("\n\t\t-------------------------------\n\n");

                for (int i = 0; i < pinewoodItemCount; i++)
                {
                    printf("\t\t%d.%s - \t$%3.2f (Preordered: %d)\n",i+1,pinewoodMenu[i].itemName, pinewoodMenu[i].price, pinewoodMenu[i].orderedAmount);
                }
                printf("\n\t\t-------------------------------\n\n");
                printf("\n");
            }
            else
            {

                printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb IRONBITE MENU \xdb\xdb\xdb\xdb\xdb\xdb\n");
                printf("\n\t\tItem\t-\tPrice");
                printf("\n\t\t-------------------------------\n\n");
                for (int i = 0; i < ironbiteItemCount; i++)
                {
                    printf("\t\t%d.%s - \t$%3.2f (Preordered: %d)\n",i+1, ironbiteMenu[i].itemName, ironbiteMenu[i].price, ironbiteMenu[i].orderedAmount);
                }
                printf("\n\t\t-------------------------------\n\n");
                printf("\n");
            }

            break;
        case 2:
            orderStatus();
            sleep(4);
            system("cls");
            break;
        case 3:
            editMenu(vendorID);
            break;
        case 4:
            printf("\t\tLogging out...\n");
            sleep(2);
            system("cls");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void orderStatus()
{
    int orderID;
    printf("\t\tEnter Order ID: ");
    scanf("%d", &orderID);

    int found = 0;
    for (int i = 0; i < orderCount; i++)
    {
        if (orders[i].orderNumber == orderID)
        {
            found = 1;
            printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb ORDER DETAILS \xdb\xdb\xdb\xdb\xdb\xdb\n");
            printf("\t\t*************************\n\n");
            printf("\t\tOrder Number: %d\n", orders[i].orderNumber);
            printf("\t\tUser ID: %d\n", orders[i].userID);
            printf("\t\tVendor: %s\n", orders[i].vendor);
            printf("\t\tDate: %s\n", orders[i].date);
            printf("\t\tItems Ordered:\n");
            for (int j = 0; j < orders[i].itemCount; j++)
            {
                printf("\t\t\t- %s : %d pcs\n",
                       orders[i].items[j].itemName,
                       orders[i].items[j].quantity);
            }

            printf("\t\tTotal Payable Amount: $%.2f\n", orders[i].totalBill);
            printf("\t\tPayment Status: %s\n", orders[i].paymentStatus);
            printf("\t\t--------------------------------------------------\n");
            printf("\n\t\tUpdate Payment Status (Done): ");
            char paymentUpdate[10];
            scanf("%s", paymentUpdate);

            if (strcmp(paymentUpdate, "Done") == 0)
            {
                strcpy(orders[i].paymentStatus, "Done");
                printf("\t\tUpdating payment status...\n");
                sleep(3);
                printf("\t\tPayment status updated successfully.\n");
                saveOrders();
            }
            else
            {
                printf("\t\tPayment status unchanged.\n");
            }

            break;
        }
    }

    if (!found)
    {
        printf("\t\tOrder with ID %d not found.\n", orderID);
    }
}

void editMenu(int vendorID)
{
    int choice;
    do
    {
        printf("\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb MENU EDITING \xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
        printf("\t\t*****************************\n\n");
        printf("\t\t1. Add a New Item\n");
        printf("\t\t2. Delete an Item\n");
        printf("\t\t3. Change Item Price\n");
        printf("\t\t4. Back to Admin Dashboard\n");
        printf("\t\t---------------------------\n\n");

        printf("\t\tChoose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMenuItem(vendorID);
            sleep(1);
            system("cls");
            break;
        case 2:
            deleteMenuItem(vendorID);
            sleep(1);
            system("cls");
            break;
        case 3:
            updateMenuItemPrice(vendorID);
            sleep(1);
            system("cls");
            break;
        case 4:
            printf("\t\tReturning to Admin Dashboard...\n");
            sleep(2);
            system("cls");
            break;
        default:
            printf("\t\tInvalid choice! Please select a valid option.\n");
        }
    }
    while (choice != 4);
}

void addMenuItem(int vendorID)
{
    char newItemName[50];
    float newItemPrice;

    printf("\n\t\tEnter the name of the new item: ");
    getchar();
    gets(newItemName);
    printf("\t\tEnter the price of the new item: ");
    scanf("%f", &newItemPrice);

    if (vendorID == 1)
    {
        strcpy(pinewoodMenu[pinewoodItemCount].itemName, newItemName);
        pinewoodMenu[pinewoodItemCount].price = newItemPrice;
        pinewoodMenu[pinewoodItemCount].orderedAmount = 0;
        pinewoodItemCount++;
    }
    else if (vendorID == 2)
    {
        strcpy(ironbiteMenu[ironbiteItemCount].itemName, newItemName);
        ironbiteMenu[ironbiteItemCount].price = newItemPrice;
        ironbiteMenu[ironbiteItemCount].orderedAmount = 0;
        ironbiteItemCount++;
    }

    printf("\t\tNew item added successfully!\n");
}
void deleteMenuItem(int vendorID)
{
    char itemNameToDelete[50];
    int found = 0;

    printf("\n\t\tEnter the name of the item to delete: ");
    getchar();
    gets(itemNameToDelete);


    if (vendorID == 1)
    {
        for (int i = 0; i < pinewoodItemCount; i++)
        {
            if (strcmp(pinewoodMenu[i].itemName, itemNameToDelete) == 0)
            {
                for (int j = i; j < pinewoodItemCount - 1; j++)
                {
                    pinewoodMenu[j] = pinewoodMenu[j + 1];
                }
                pinewoodItemCount--;
                found = 1;
                printf("\t\tItem deleted successfully!\n");
                break;
            }
        }
    }
    else if (vendorID == 2)
    {
        for (int i = 0; i < ironbiteItemCount; i++)
        {
            if (strcmp(ironbiteMenu[i].itemName, itemNameToDelete) == 0)
            {
                for (int j = i; j < ironbiteItemCount - 1; j++)
                {
                    ironbiteMenu[j] = ironbiteMenu[j + 1];
                }
                ironbiteItemCount--;
                found = 1;
                printf("\t\tItem deleted successfully!\n");
                break;
            }
        }
    }

    if (!found)
    {
        printf("\t\tItem not found in the menu.\n");
    }
}
void updateMenuItemPrice(int vendorID)
{
    char itemNameToUpdate[50];
    float newPrice;
    int found = 0;

    printf("\n\t\tEnter the name of the item to update the price: ");
    getchar();
    gets(itemNameToUpdate);
    if (vendorID == 1)
    {
        for (int i = 0; i < pinewoodItemCount; i++)
        {
            if (strcmp(pinewoodMenu[i].itemName, itemNameToUpdate) == 0)
            {
                printf("\t\tEnter the new price: ");
                scanf("%f", &newPrice);
                pinewoodMenu[i].price = newPrice;
                found = 1;
                printf("\t\tItem price updated successfully!\n");
                break;
            }
        }
    }
    else if (vendorID == 2)
    {
        for (int i = 0; i < ironbiteItemCount; i++)
        {
            if (strcmp(ironbiteMenu[i].itemName, itemNameToUpdate) == 0)
            {
                printf("\t\tEnter the new price: ");
                scanf("%f", &newPrice);
                ironbiteMenu[i].price = newPrice;
                found = 1;
                printf("\t\tItem price updated successfully!\n");
                break;
            }
        }
    }

    if (!found)
    {
        printf("\t\tItem not found in the menu.\n");
    }
}
void loadUsers()
{
    FILE *file = fopen("userdatabase.txt", "r");
    if (!file) return;
    while (fscanf(file, "%s %s %d\n", users[userCount].username, users[userCount].password, &users[userCount].userID) != EOF)
    {
        userCount++;
    }
    fclose(file);
}
void saveUsers()
{
    FILE *file = fopen("userdatabase.txt", "w");
    if (!file) return;
    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s %d\n", users[i].username, users[i].password, users[i].userID);
    }
    fclose(file);
}
void loadOrders()
{
    FILE *file = fopen("orders.txt", "r");
    if (!file) return;

    while (!feof(file))
    {
        if (fscanf(file, "%d,%d,%[^,],%d,",
                   &orders[orderCount].orderNumber,
                   &orders[orderCount].userID,
                   orders[orderCount].vendor,
                   &orders[orderCount].itemCount) != 4)
        {
            break;
        }

        for (int i = 0; i < orders[orderCount].itemCount; i++)
        {
            if (fscanf(file, "%[^,],%d,%f,",
                       orders[orderCount].items[i].itemName,
                       &orders[orderCount].items[i].quantity,
                       &orders[orderCount].items[i].price) != 3)
            {
                break;
            }
        }

        if (fscanf(file, "%[^,],%[^,],%f\n",
                   orders[orderCount].date,
                   orders[orderCount].paymentStatus,
                   &orders[orderCount].totalBill) != 3)
        {
            break;
        }

        orderCount++;
    }

    fclose(file);
}
void saveOrders()
{
    FILE *file = fopen("orders.txt", "w");
    if (!file)
    {
        printf("Error: Could not open file for saving orders.\n");
        return;
    }

    for (int i = 0; i < orderCount; i++)
    {
        fprintf(file, "%d,%d,%s,%d,",
                orders[i].orderNumber,
                orders[i].userID,
                orders[i].vendor,
                orders[i].itemCount);

        for (int j = 0; j < orders[i].itemCount; j++)
        {
            fprintf(file, "%s,%d,%.2f,",
                    orders[i].items[j].itemName,
                    orders[i].items[j].quantity,
                    orders[i].items[j].price);
        }

        fprintf(file, "%s,%s,%.2f\n",
                orders[i].date,
                orders[i].paymentStatus,
                orders[i].totalBill);
    }

    fclose(file);
}
void loadMenu()
{

    FILE *file = fopen("pinewoodmenu.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %f %d\n", pinewoodMenu[pinewoodItemCount].itemName, &pinewoodMenu[pinewoodItemCount].price, &pinewoodMenu[pinewoodItemCount].orderedAmount) != EOF)
        {
            pinewoodItemCount++;
        }
        fclose(file);
    }


    file = fopen("ironbitemenu.txt", "r");
    if (file)
    {
        while (fscanf(file, "%s %f %d\n", ironbiteMenu[ironbiteItemCount].itemName, &ironbiteMenu[ironbiteItemCount].price, &ironbiteMenu[ironbiteItemCount].orderedAmount) != EOF)
        {
            ironbiteItemCount++;
        }
        fclose(file);
    }
}
void saveMenu()
{

    FILE *file = fopen("pinewoodmenu.txt", "w");
    if (file)
    {
        for (int i = 0; i < pinewoodItemCount; i++)
        {
            fprintf(file, "%s %.2f %d\n", pinewoodMenu[i].itemName, pinewoodMenu[i].price, pinewoodMenu[i].orderedAmount);
        }
        fclose(file);
    }


    file = fopen("ironbitemenu.txt", "w");
    if (file)
    {
        for (int i = 0; i < ironbiteItemCount; i++)
        {
            fprintf(file, "%s %.2f %d\n", ironbiteMenu[i].itemName, ironbiteMenu[i].price, ironbiteMenu[i].orderedAmount);
        }
        fclose(file);
    }
}

int main()
{
    loadUsers();
    loadOrders();
    loadMenu();

    int choice;
    while (1)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  "
               "NSU CAFETERIA MANAGEMENT SYSTEM  "
               "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n");

        printf("************************* W E L C O M E !!! ***********************\n\n");
        printf("\xdb\xdb\xdb\xdb 1. Register as a New User\n\n");
        printf("\xdb\xdb\xdb\xdb 2. User Login\n\n");
        printf("\xdb\xdb\xdb\xdb 3. Admin Login\n\n");
        printf("\xdb\xdb\xdb\xdb 4. Exit\n\n");
        printf("\n");

        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        system("cls");
        switch (choice)
        {
        case 1:
            registerUser();
            sleep(2);
            system("cls");
            break;
        case 2:
        {
            int userID = userLogin();
            if (userID != -1)
            {
                sleep(2);
                system("cls");
                userMenu(userID);
            }
        }
        break;
        case 3:
        {
            int vendorID = adminLogin();
            if (vendorID != -1)
            {
                sleep(2);
                system("cls");
                adminMenu(vendorID);
            }
        }

        break;
        case 4:
            printf("\t\t   T H A N K  YOU !\n");
            printf("\n");
            printf("#######################################################\n");
            printf("#  PROJECT TITLE : \"NSU CAFETORIA MANAGEMENT SYSTEM\"  #\n");
            printf("#  MD. MINHAZUL ISLAM                                 #\n");
            printf("#  NORTH SOUTH UNIVERSITY                             #\n");
            printf("#  SUMMER 2024                                        #\n");
            printf("#######################################################\n");
            printf("\n\n");
            printf("   P R O J E C T   E X E C U T I O N   E N D E D\n");
            saveUsers();
            saveOrders();
            saveMenu();
            return 1;
        default:
            printf("\t\tInvalid choice. Please try again.\n");
        }
    }
    return 0;
}
