#include <stdio.h> //standard input and output library
#include <stdlib.h> //Used to access the rand function (and memory allocation)
#include <string.h> //used for comaprisons and string manipultaion
#include <time.h> // Include for random number generation

// Define constants
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define ESPRESSO_MILK 0
#define ESPRESSO_SYRUP 0
float ESPRESSO_PRICE = 3.5;

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
#define CAPPUCCINO_SYRUP 0
float CAPPUCCINO_PRICE = 4.5;

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30
float MOCHA_PRICE = 5.5;

// defining password and minimum ingrediednts quantities for machine
#define ADMIN_PASSWORD "Admin123"
#define BEANS_THRESHOLD 50
#define WATER_THRESHOLD 150
#define MILK_THRESHOLD 300
#define SYRUP_THRESHOLD 50

// Declare global variables
float total_amount = 0;
int Beans = 1500;
int Water = 2500;
int Milk = 3500;
int Syrup = 1000;

// Function prototypes
void display_main_menu(); //function to display main menu
void order_coffee(); //function handeling coffee orders
void admin_mode(); //to access admin functions
void show_ingredients_sales(); //display ingredient quantities and total sales
void refill_ingredients(); //to refill ingredients with random values
void change_coffee_price(); //function to change prices of coffee

// Function to display the main menu
int main() { 
    srand(time(0)); // Seed the random number generator
    int option; //defining users input
    while (1) {
        display_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &option); //getting user's choice
        
        switch (option) { //setting infinite case loop depending on option
            case 1:
                order_coffee(); //to access order coffee menu
                break;
            case 2:
                admin_mode(); // to access administrative "menu"
                break;
            case 3:
                printf("Exiting the program.\n"); 
                return 0; //exits the program
            default:
                printf("Invalid choice. Please try again.\n"); //defines incorrect inputs
        }
    }
    return 0;
}

void display_main_menu() { //user output for menu choices
    printf("\nCoffee Machine Menu:\n");
    printf("1. Order a coffee\n");
    printf("2. Admin mode\n");
    printf("3. Exit\n");
}

// Function to display available coffee options and handle orders
void order_coffee() { //initializes ordering coffee function
    int option; //defining user input
    float cost = 0; //to store the cost of selected coffee
    int required_beans = 0, required_water = 0, required_milk = 0, required_syrup = 0; //used to store needed ingredient quntities
    float paid = 0; //store the amount of money paid
    int confirmed = 0; //variable to track order confirmation

    while (1) { //infinite loop showing coffee if ingredients are available
        printf("\nAvailable Coffee:\n");
        if (Beans >= ESPRESSO_BEANS && Water >= ESPRESSO_WATER) {
            printf("1. Espresso - %.2f AED\n", ESPRESSO_PRICE);
        } else {
            printf("1. Espresso - Unavailable due to insufficient ingredients\n");
        } //code to not display coffee if any insufficient ingredients

        if (Beans >= CAPPUCCINO_BEANS && Water >= CAPPUCCINO_WATER && Milk >= CAPPUCCINO_MILK) {
            printf("2. Cappuccino - %.2f AED\n", CAPPUCCINO_PRICE);
        } else {
            printf("2. Cappuccino - Unavailable due to insufficient ingredients\n");
        } //code to not display coffee if any insufficient ingredients

        if (Beans >= MOCHA_BEANS && Water >= MOCHA_WATER && Milk >= MOCHA_MILK && Syrup >= MOCHA_SYRUP) {
            printf("3. Mocha - %.2f AED\n", MOCHA_PRICE);
        } else {
            printf("3. Mocha - Unavailable due to insufficient ingredients\n");
        } //code to not display coffee if any insufficient ingredients

        printf("0. Exit\n"); //option to exit coffee menu
        printf("Choose a coffee option: "); 
        scanf("%d", &option); //get user's choice

 if (option == 0) {
            break;
        } //enacts the exit function if chosen

        // Set cost and required ingredients based on the selected coffee
        switch (option) { //espresso option while inputing stored values
            case 1: 
                cost = ESPRESSO_PRICE;
                required_beans = ESPRESSO_BEANS;
                required_water = ESPRESSO_WATER;
                required_milk = ESPRESSO_MILK;
                required_syrup = ESPRESSO_SYRUP;
                break;
            case 2: //cappucino option while inputing stored values
                cost = CAPPUCCINO_PRICE;
                required_beans = CAPPUCCINO_BEANS;
                required_water = CAPPUCCINO_WATER;
                required_milk = CAPPUCCINO_MILK;
                required_syrup = CAPPUCCINO_SYRUP;
                break;
            case 3: //mocha option while inputing stored values
                cost = MOCHA_PRICE;
                required_beans = MOCHA_BEANS;
                required_water = MOCHA_WATER;
                required_milk = MOCHA_MILK;
                required_syrup = MOCHA_SYRUP;
                break;
            default: //handles invalid option
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // Check ingredient availability
        if (Beans < required_beans || Water < required_water || Milk < required_milk || Syrup < required_syrup) {
            printf("Sorry, some ingredients are insufficient. Please choose a different option.\n");
            continue;
        }

 // Confirm order
        printf("You selected option %d. The price is %.2f AED. Confirm? (0 for yes, 1 for no): ", option, cost);
        scanf("%d", &confirmed);
        if (confirmed == 1) { //if not confirmed then return to menu
            continue;
        }

        // Handle payment
        while (paid < cost) { 
            float coin;
            printf("Insert a 1 or 0.5 AED coin: "); //prompt to insert coin
            scanf("%f", &coin);
            if (coin == 1.0 || coin == 0.5) { //ensures only correct values are inputted
                paid += coin; //updates the amount of money paid
            } else {
                printf("Invalid coin. Please insert a valid coin.\n");
            }
        }

        // Update ingredient quantities
        Beans -= required_beans;
        Water -= required_water;
        Milk -= required_milk;
        Syrup -= required_syrup;
        total_amount += cost;

        // Provide change if overpaid
        float change = paid - cost;
        if (change > 0) { //verifies if there even is change
            printf("Collect your change: %.2f AED\n", change); //shows change to the user
        }
        printf("Thank you for your purchase!\n");

// Alert if ingredients are below threshold
        if (Beans <= BEANS_THRESHOLD) { 
            printf("Alert: Low beans level!\n");
        }//checks if minimum amount has been reached and alerts user

        if (Water <= WATER_THRESHOLD) {
            printf("Alert: Low water level!\n");
        }//checks if minimum amount has been reached and alerts user

        if (Milk <= MILK_THRESHOLD) {
            printf("Alert: Low milk level!\n");
        } //checks if minimum amount has been reached and alerts user

        if (Syrup <= SYRUP_THRESHOLD) {
            printf("Alert: Low syrup level!\n");
        }//checks if minimum amount has been reached and alerts user

        break;
    }
}

// Function for admin mode
void admin_mode() {
    char password[20]; //buffer to enter admin passoword
    printf("Enter admin password: ");
    scanf("%s", password); //get spassword input
    if (strcmp(password, ADMIN_PASSWORD) != 0) { //checks if password is correct
        printf("Incorrect password.\n");
        return; //exits menu if wrong password
    }

    int option;
    while (1) { //display menu options
        printf("\nAdmin Menu:\n");
        printf("1. Show ingredient quantities and total sales\n");
        printf("2. Refill ingredients\n");
        printf("3. Change coffee price\n");
        printf("0. Exit admin mode\n");
        printf("Enter your choice: ");
        scanf("%d", &option); //get admin menu choice
 switch (option) {
            case 1:
                show_ingredients_sales(); //access ingredients and sales menu
                break;
            case 2:
                refill_ingredients(); //access random refill of ingredients options
                break;
            case 3:
                change_coffee_price(); //access change of coffee prices menu
                break;
            case 0:
                return; //exits menu
            default:
                printf("Invalid choice. Please try again.\n"); //resets switch case options
        }
    }
}

// Function to show ingredients and sales
void show_ingredients_sales() {
    printf("\nIngredient Quantities:\n");
    printf("Beans: %d grams\n", Beans);
    printf("Water: %d ml\n", Water);
    printf("Milk: %d ml\n", Milk);
    printf("Syrup: %d ml\n", Syrup);
    printf("Total Sales: %.2f AED\n", total_amount);
} 

// Function to refill ingredients with random quantities
void refill_ingredients() {
    // Randomly replenish each ingredient within a specified range
    Beans = 1000 + rand() % 501;   // Replenish between 1000 and 1500 grams
    Water = 2000 + rand() % 1001;  // Replenish between 2000 and 3000 ml
    Milk = 3000 + rand() % 1001;   // Replenish between 3000 and 4000 ml
    Syrup = 1000 + rand() % 501;   // Replenish between 1000 and 1500 ml
    printf("Ingredients have been refilled with random quantities.\n");
}
// Function to change coffee prices
void change_coffee_price() { //access coffe price change menu
    int option; //defines user choice
    float new_price; //used to store new prices
    printf("Choose coffee type to change price:\n");
    printf("1. Espresso\n");
    printf("2. Cappuccino\n");
    printf("3. Mocha\n");
    scanf("%d", &option); //user option menu

    switch (option) {
        case 1: //changes prices of espresso
            printf("Enter new price for Espresso: ");
            scanf("%f", &new_price); //input new price
            ESPRESSO_PRICE = new_price;
            printf("Espresso price updated to %.2f AED.\n", ESPRESSO_PRICE); //confirm update
            break;
        case 2: //changes prices of cappuccino
            printf("Enter new price for Cappuccino: ");
            scanf("%f", &new_price);//input new price
            CAPPUCCINO_PRICE = new_price;
            printf("Cappuccino price updated to %.2f AED.\n", CAPPUCCINO_PRICE); //confirm update
            break;
        case 3: //changes prices of mocha
            printf("Enter new price for Mocha: ");
            scanf("%f", &new_price); //input new price
            MOCHA_PRICE = new_price;
            printf("Mocha price updated to %.2f AED.\n", MOCHA_PRICE); //confirm update
            break;
        default: // resets incase of wrong input
            printf("Invalid choice.\n");}
}
