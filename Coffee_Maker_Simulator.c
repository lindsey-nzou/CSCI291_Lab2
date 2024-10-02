#include <stdio.h>
#include <math.h>

//define the constants
#define Espresso_Beans 8
#define Espresso_Water 30
#define Espresso_Milk 0
#define Espresso_Syrup 0
#define Espresso_Price 3.5

#define Cappuccino_Beans 8
#define Cappuccino_Water 30
#define Cappuccino_Milk 70
#define Cappuccino_Syrup 0
#define Cappuccino_Price 4.5

#define Mocha_Beans 8
#define Mocha_Water 39
#define Mocha_Milk 160
#define Mocha_Syrup 30
#define Mocha_Price 5.5

// define password and ingredient threshold
#define Admin_Password Admin123
#define Beans_Threshold 50
#define Water_Threshold 150
#define Milk_Threshold 300
#define Syrup_Threshold 50

//declare global variables
float total_amount = 0;
int Beans = 1500;
int Water = 2500;
int Milk = 3500;
int Syrup = 1000;


//function to display menu
void display_menu(){
    printf("1. Order from Coffee Maker Menu\n");
    printf("2. Admin mode \n");
    printf("1. Exit application \n");
}


void coffee_maker_menu(){

//function to display coffee menu
printf ("Coffee Maker Menu \n");


//use if, else statements to determine whether to show coffee or display unavailability
if (Beans >= Espresso_Beans && Water >= Espresso_Water ) {  //conditional to ensure ingredients amount
    printf("Espresso - %.2f AED\n", Espresso_Price); //display if meets criteria
} else {
    printf("Espresso - Unavailable due to insufficient ingredients \n"); //display if criteria isnt met
}
    
if (Water >= Cappuccino_Water && Beans >= Cappuccino_Beans && Milk >= Cappuccino_Milk) {
    printf("Cappucino - %.2f AED\n", Cappuccino_Price );
} else {
    printf("Cappuccino - Unavailable due to insufficient ingredients");
}

if (Beans >= Mocha_Beans && Water >= Mocha_Water && Milk >= Mocha_Water && Syrup >= Mocha_Syrup){
    printf("Mocha - %.2f AED\n", Mocha_Price);
} else {
    printf("Mocha - Uniavailable due to insufficient ingredients");
}
printf("0. Exit\n");
}
    
//function for ordering a coffee

void ordering_coffee()
{
int option;
float cost;
int required_beans = 0;
int required_water = 0;
int required_milk = 0;
int required_syrup = 0;
float paid = 0;

// setting display functions to 0
while (1) {
    coffee_maker_menu();
    printf("Choose a coffee option: ");
    scanf("%d", &option);
    if (option = 0){
        break;
    } else if (option = 1){
        cost = Espresso_Price;
        required_beans = Espresso_Beans;
        required_beans = Espresso_Milk;

    } else if (option = 2){
        cost = Cappuccino_Price;
        required_beans = Cappuccino_Beans;
        required_beans = Cappuccino_Milk;
        required_syrup = Cappuccino_Syrup;
        
    } else if (option = 3){
        cost = Mocha_Price;
        required_beans = Mocha_Beans;
        required_beans = Mocha_Milk;
        required_syrup = Mocha_Syrup;
        required_water = Mocha_Syrup;
    } else {
        printf("Error. Please choose a coffee option. \n");
        continue;
    }

printf("Your chosen coffee order ");
if (option = 1) {
    printf("Espresso");
} else if (option = 2){
    printf("Cappuccino");
} else if (option = 3) {
    printf("Mocha");
}


if (Beans < required_beans || Water < required_water || Milk < required_milk || Syrup < required_syrup){
    printf("Sorry, some ingredients are no longer available. Please try again later. \n");
    continue;
}

printf("You have chosen to order a %d coffee. The proce will be %.2f Aed. \n", option, cost);
printf("Are you sure this is what you want to order? (click 1 for yes and 0 for no): ");
int agreed;
scanf("%d", &agreed);

if (agreed==0){
    continue;
}

while (paid < cost){
    printf("Insert a 1 or 0.5 Aed coins to pay: ");
    float coin;
    scanf("%f", &coin);

    if (coin != 1 && coin != 0.5){
        printf("Invalid payment, please insert a 1 or 0.5 coin to pay. \n");
        continue;
        }

        paid += coin;
}

Beans -= required_beans;
Water -= required_water;
Milk -= required_milk;
Syrup -= required_milk;

paid -= cost;

printf("Thank you for your payment of %.2f Aed for your coffee.\n", paid);
printf("You have %.2f Aed change, please collect it.\n", paid-cost);

if (Beans <= Beans_Threshold){
    printf("Alert! Low amount of beans! \n");
}

if (Water <= Water_Threshold){
    printf("Alert! Low amount of water! \n");
}

if (Syrup <= Syrup_Threshold){
    printf("Alert! Low amount of Syrup! \n");
}

if (Milk <= Milk_Threshold){
    printf("Alert! Low amount of Milk! \n");
}
}