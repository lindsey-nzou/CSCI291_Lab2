#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants
#define NUM_TEAMS 5         // Maximum number of teams that can be enrolled
#define SQUAD_SIZE 20       // Maximum number of players per team
#define MAX_NAME_LENGTH 25  // Maximum length of a player's name
#define MAX_CLUB_LENGTH 20  // Maximum length of a club's name
#define MAX_POSITION_LENGTH 15 // Maximum length of a player's position

// Struct Definitions
typedef struct {
    int day, month, year; // Stores the day, month, and year of birth for a player
} age_t;

typedef struct {
    char name[MAX_NAME_LENGTH];   // Player's full name
    int kit_number;               // Player's unique kit number
    char club[MAX_CLUB_LENGTH];   // Name of the club
    age_t dob;                    // Player's date of birth
    char position[MAX_POSITION_LENGTH]; // Player's position (e.g., midfielder)
} player_t;

typedef struct {
    char name[MAX_CLUB_LENGTH];   // Club name
    player_t players[SQUAD_SIZE]; // Array of players in the club
    int active_size;              // Number of currently enrolled players in the team
} team_t;

// Global Variables
team_t teams[NUM_TEAMS];          // Array to store the details of all teams
int enrolled_teams = 0;           // Tracks the number of enrolled teams

// Function Prototypes
void display_menu();              // Displays the menu options
void enroll_club();               // Enrolls a new club
void add_player();                // Adds a player to a specific club
void search_update();             // Searches and updates player information
void display_club_statistics();   // Displays statistics for all clubs
void handle_error(char message[MAX_NAME_LENGTH]); // Handles error messages

// Helper Functions
void to_lowercase(char str[MAX_NAME_LENGTH]); // Converts a string to lowercase

int main() {
    int choice; // Variable to store the user's menu choice

    // Loop until the user exits the program
    do {
        display_menu(); // Show the menu options
        printf("Enter your choice: ");
        scanf("%d", &choice); // Get the user's choice

        // Perform actions based on the user's choice
        switch (choice) {
            case 1:
                enroll_club();
                break;
            case 2:
                add_player();
                break;
            case 3:
                search_update();
                break;
            case 4:
                display_club_statistics();
                break;
            default:
                handle_error("Exiting program. Thank you!"); // Display exit message
                break;
        }
    } while (choice >= 1 && choice <= 4); // Continue until an invalid choice is entered

    return 0;
}

// Displays the menu options
void display_menu() {
    printf("\n--- League Team Management ---\n");
    printf("1. Enroll a Club\n");
    printf("2. Add Player\n");
    printf("3. Search and Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("Other. Exit\n");
}

// Enrolls a new club
void enroll_club() {
    // Check if the maximum number of clubs has been reached
    if (enrolled_teams >= NUM_TEAMS) {
        handle_error("Maximum number of teams enrolled!");
        return;
    }

    // Prompt the user for the club name
    printf("Enter the name of the club: ");
    getchar(); // Clear the newline character left in the input buffer
    fgets(teams[enrolled_teams].name, MAX_CLUB_LENGTH, stdin); // Get the club name
    teams[enrolled_teams].name[strcspn(teams[enrolled_teams].name, "\n")] = '\0'; // Remove newline
    teams[enrolled_teams].active_size = 0; // Initialize the number of players to 0
    enrolled_teams++; // Increment the count of enrolled teams

    printf("Club enrolled successfully!\n");
}

// Adds a player to a specific club
void add_player() {
    // Check if any clubs are enrolled
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled. Please enroll a club first.");
        return;
    }

    // Display the list of enrolled clubs
    printf("Select a club:\n");
    for (int i = 0; i < enrolled_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    int club_index;
    printf("Enter the club number: ");
    scanf("%d", &club_index); // Get the user's choice of club

    // Validate the club selection
    if (club_index < 1 || club_index > enrolled_teams) {
        handle_error("Invalid club selection.");
        return;
    }
    club_index--; // Convert to array index (0-based)

    // Check if the team is full
    if (teams[club_index].active_size >= SQUAD_SIZE) {
        handle_error("Squad is full for this club.");
        return;
    }

    player_t new_player; // Temporary structure to hold the new player's details

    // Prompt the user for the player's details
    printf("Enter player name: ");
    getchar(); // Clear the newline character
    fgets(new_player.name, MAX_NAME_LENGTH, stdin);
    new_player.name[strcspn(new_player.name, "\n")] = '\0'; // Remove newline

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    if (new_player.kit_number < 1 || new_player.kit_number > 99) {
        handle_error("Invalid kit number.");
        return;
    }

    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year);

    printf("Enter position: ");
    getchar(); // Clear the newline character
    fgets(new_player.position, MAX_POSITION_LENGTH, stdin);
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; // Remove newline

    // Check for duplicates in the player's name or kit number
    for (int i = 0; i < teams[club_index].active_size; i++) {
        if (strcmp(teams[club_index].players[i].name, new_player.name) == 0 || 
            teams[club_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate player name or kit number found!");
            return;
        }
    }

    // Add the new player to the team's array
    teams[club_index].players[teams[club_index].active_size] = new_player;
    teams[club_index].active_size++; // Increment the active size of the team
    printf("Player added successfully!\n");
}

// Searches for a player by name and allows updating their information
void search_update() {
    char query[MAX_NAME_LENGTH];
    printf("Enter player name to search: ");
    getchar(); // Clear the newline character
    fgets(query, MAX_NAME_LENGTH, stdin);
    query[strcspn(query, "\n")] = '\0'; // Remove newline

    // Search all teams for the player
    for (int i = 0; i < enrolled_teams; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            char player_name[MAX_NAME_LENGTH];
            strcpy(player_name, teams[i].players[j].name); // Copy the player's name
            to_lowercase(player_name); // Convert to lowercase for comparison
            to_lowercase(query);

            if (strcmp(player_name, query) == 0) { // Check if names match
                printf("Player found: %s\n", teams[i].players[j].name);
                printf("Enter new kit number (1-99): ");
                int new_kit_number;
                scanf("%d", &new_kit_number);
                teams[i].players[j].kit_number = new_kit_number; // Update the kit number
                printf("Player details updated successfully!\n");
                return;
            }
        }
    }
    handle_error("Player not found."); // If no match is found
}

// Displays statistics for all clubs
void display_club_statistics() {
    for (int i = 0; i < enrolled_teams; i++) {
        printf("\nClub: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].active_size);
        for (int j = 0; j < teams[i].active_size; j++) {
            printf("Player Name: %s, Kit Number: %d, Position: %s\n",
                   teams[i].players[j].name, teams[i].players[j].kit_number,
                   teams[i].players[j].position);
        }
    }
}

// Handles and displays error messages
void handle_error(char message[MAX_NAME_LENGTH]) {
    printf("Error: %s\n", message);
}

// Converts a string to lowercase
void to_lowercase(char str[MAX_NAME_LENGTH]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32; // Convert uppercase to lowercase
        }
    }
}
