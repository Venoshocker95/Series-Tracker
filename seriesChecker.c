#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


struct mySeries
{
    char seriesName[30];
    char genre1[15];
    char genre2[15];
    int numEpisodes;
    int lastEpWatched;
    bool watchComplete;
};


// FUNCTION PROTOTYPES

bool fileChecker();
void makeFile();
void printLogo();
void printMenu();
void getChoice();
void addEntry();
void editEntry();
void removeEntry();
void viewList();
void cleanInput();
void toUpperCase(char*);
int getEntryCount();
struct mySeries *loadEntries(int *total);



int main()
{
    fileChecker();
    return 0;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Checks if the needed file exists or not, if it's not there 
|   makeFile() gets called
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
bool fileChecker()
{
    FILE *file = fopen("mySeriesList.txt", "r");

    if (file == NULL)
    {
        printf("FILE DOES NOT EXIST...CREATING FILE NOW...");
        Sleep(2000);

        makeFile();
    }
    else
    {
        Beep(1800, 500);
        printLogo();
    }
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   When called, an empty .txt file named "mySeriesList.txt"
|   appears in the same folder as the executable, then
|   printMenu() is called
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void makeFile()
{
    FILE *fptr;

    fptr = fopen("mySeriesList.txt", "w");

    fclose(fptr);

    printMenu();
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Prints-out the ASCII art
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void printLogo()
{
    system("cls");
    system("color 0a");

    printf("  ____  ____  ____  ____  ____  ____  ____  ____  ____  ____  ____\n");
    printf(" /\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\/\\   \\ \n");
    printf("/  \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \\___\\ \n");
    printf("\\  /   / /   / /   / /   / /   / /   / /   / /   / /   / /   / /   /\n");
    printf(" \\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\\/___/\n");

    printf("___  ___        _____           _\n");
    printf("|  \\/  |       /  ___|         (_)\n");
    printf("| .  . |_   _  \\ `--.  ___ _ __ _  ___  ___\n");
    printf("| |\\/| | | | |  `--. \\/ _ \\ '__| |/ _ \\/ __|\n");
    printf("| |  | | |_| | /\\__/ /  __/ |  | |  __/\\__ \\ \n");
    printf("\\_|  |_/\\__, | \\____/ \\___|_|  |_|\\___||___/ \n");
    printf("         __/ |                              \n");
    printf("        |___/                               \n");
    printf("                            _____ _               _\n");
    printf("                           /  __ \\ |             | |\n");
    printf("                           | /  \\/ |__   ___  ___| | _____ _ __\n");
    printf("                           | |   | '_ \\ / _ \\/ __| |/ / _ \\ '__|\n");
    printf("                           | \\__/\\ | | |  __/ (__|   <  __/ |\n");
    printf("                           \\_____/_| |_|\\___|\\___|_|\\_\\___|_|\n");

    Sleep(3000);

    printMenu();
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Prints-out the MAIN MENU, then calls getChoice()
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void printMenu()
{
    system("cls");

    printf("                 __  __    _    ___ _   _           __  __ _____ _   _ _   _\n");
    printf("                |  \\/  |  / \\  |_ _| \\ | |         |  \\/  | ____| \\ | | | | |\n");
    printf("                | |\\/| | / _ \\  | ||  \\| |  _____  | |\\/| |  _| |  \\| | | | |\n");
    printf("                | |  | |/ ___ \\ | || |\\  | |_____| | |  | | |___| |\\  | |_| |\n");
    printf("                |_|  |_/_/   \\_\\___|_| \\_|         |_|  |_|_____|_| \\_|\\___/\n");
    printf("\n");
    printf("A = Add Entry       E = Edit Entry      R = Remove Entry        V = View List       Q = Quit program    ---> ");

    getChoice(); // Call getChoice()
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Check for one of these char( 'A', 'E', 'R', 'Q') and
|   calls the correct function.
|   If the user char doesn't match any of the previous value, 
|   the user has to enter their choice again
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void getChoice()
{
    char usrChoice = '\0';

    for(;;)
    {
        scanf(" %c", &usrChoice);
        usrChoice = toupper(usrChoice);

        switch(usrChoice)
        {
            case 'A':
                addEntry();
                break;
            case 'E':
                editEntry();
                break;
            case 'R':
                removeEntry();
                break;
            case 'V':
                viewList();
                break;
            case 'Q':
                exit(0);
                break;
            default:
                printf("\n");
                printf("UNRECOGNIZED INPUT...");   
                Sleep(3000);
                printMenu();
                break;
        }

    }
    
    
}



void addEntry()
{ 
    system("cls");

    char buffer[31];
    struct mySeries newEntry;

    printf(" _   _ _______        __     _____ _   _ _____ ______   __\n");
    printf("| \\ | | ____\\ \\      / /    | ____| \\ | |_   _|  _ \\ \\ / /\n");
    printf("|  \\| |  _|  \\ \\ /\\ / /     |  _| |  \\| | | | | |_) \\ V /\n");
    printf("| |\\  | |___  \\ V  V /      | |___| |\\  | | | |  _ < | |\n");
    printf("|_| \\_|_____|  \\_/\\_/       |_____|_| \\_| |_| |_| \\_\\|_|\n");
    printf("\n");
    printf("TO CONFIRM PRESS ENTER TWICE\n\n");

    cleanInput();

    printf("SERIES NAME: ");
    fgets(newEntry.seriesName, sizeof(newEntry.seriesName), stdin);
    cleanInput();
    newEntry.seriesName[strcspn(newEntry.seriesName, "\n")] = '\0';
    toUpperCase(newEntry.seriesName);

    printf("\nGENRE #1: ");
    fgets(newEntry.genre1, sizeof(newEntry.genre1), stdin);
    cleanInput();
    newEntry.genre1[strcspn(newEntry.genre1, "\n")] = '\0';
    toUpperCase(newEntry.genre1);

    printf("\nGENRE #2: ");
    fgets(newEntry.genre2, sizeof(newEntry.genre2), stdin);
    cleanInput();
    newEntry.genre2[strcspn(newEntry.genre2, "\n")] = '\0';
    toUpperCase(newEntry.genre2);

    // Read and validate number of episodes
    while (1)
    {
        bool valid = true;
        printf("\nNUMBER OF EPISODES: ");
        fgets(buffer, sizeof(buffer), stdin);
        cleanInput();

        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++)
        {
            if (!isdigit((unsigned char)buffer[i]))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            newEntry.numEpisodes = atoi(buffer);
            break;
        }

        system("cls");
    }

    // Read and validate last episode watched
    while (1)
    {
        bool valid = true;
        printf("\nLAST EPISODE WATCHED: ");
        //cleanInput();
        fgets(buffer, sizeof(buffer), stdin);
        cleanInput();

        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++)
        {
            if (!isdigit((unsigned char)buffer[i]))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            newEntry.lastEpWatched = atoi(buffer);
            break;
        }

        system("cls");
    }

    // Set watch completion flag
    newEntry.watchComplete = (newEntry.numEpisodes == newEntry.lastEpWatched);

    // Save entry to file
    FILE *file = fopen("mySeriesList.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s|%s|%s|%04d|%04d|%d\n",
                newEntry.seriesName,
                newEntry.genre1,
                newEntry.genre2,
                newEntry.numEpisodes,
                newEntry.lastEpWatched,
                newEntry.watchComplete);
        fclose(file);
    }
    else
    {
        printf("Failed to open file for writing.\n");
    }

    printf("\nPLEASE WAIT...WRITING TO FILE...");
    Beep(1000, 100);
    Beep(1400, 100);
    Sleep(2000);

    printMenu();
}




void editEntry()
{
    system("cls");

    int total = 0;
    struct mySeries *entries = loadEntries(&total);

    if(entries == NULL || total == 0)
    {
        printf("NO SERIES FOUND...\n");
        Sleep(2000);
        printMenu();
        return;
    }

    printf(" _____ ____ ___ _____   _____ _   _ _____ ______   __\n");
    printf("| ____|  _ \\_ _|_   _| | ____| \\ | |_   _|  _ \\ \\ / /\n");
    printf("|  _| | | | | |  | |   |  _| |  \\| | | | | |_) \\ V /\n");
    printf("| |___| |_| | |  | |   | |___| |\\  | | | |  _ < | |\n");
    printf("|_____|____/___| |_|   |_____|_| \\_| |_| |_| \\_\\|_|\n");
    printf("\n");

    char searchName[30];
    printf("ENTER SERIES NAME TO EDIT: ");
    cleanInput();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    toUpperCase(searchName);

    int foundIndex = -1;
    for(int i= 0; i < total; i++)
    {
        if(strcmp(entries[i].seriesName, searchName) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        printf("SERIES NOT FOUND...");
        Sleep(2000);
        printMenu();
        return;
    }

    // Display series match
    printf("\nMATCH FOUND. CURRENT ENTRY DETAILS:\n\n");
    printf("Series Name       : %s\n", entries[foundIndex].seriesName);
    printf("Genre #1          : %s\n", entries[foundIndex].genre1);
    printf("Genre #2          : %s\n", entries[foundIndex].genre2);
    printf("Episodes Total    : %d\n", entries[foundIndex].numEpisodes);
    printf("Last Ep Watched   : %d\n", entries[foundIndex].lastEpWatched);
    printf("Watch Complete    : %s\n", entries[foundIndex].watchComplete ? "YES" : "NO");

    // Asks the user what part of the entry would he/she like to edit
    int editChoice = 0;
    char buffer[31];

    while(1)
    {
        printf("\nWHAT DO YOU WANT TO EDIT?\n");
        printf("1. Series Name\n");
        printf("2. Genre#1\n");
        printf("3. genre#2\n");
        printf("4. Total Episodes\n");
        printf("5. Last Episode Watched\n");
        printf("6. Cancel & Return to Main Menu\n");
        printf("ENTER CHOICE: ");
        fgets(buffer, sizeof(buffer), stdin);
        editChoice = atoi(buffer);

        switch (editChoice)
        {
            case 1:
                printf("New Series Name: ");
                memset(entries[foundIndex].seriesName, 0, sizeof(entries[foundIndex].seriesName));
                fgets(entries[foundIndex].seriesName, sizeof(entries[foundIndex].seriesName), stdin);
                entries[foundIndex].seriesName[strcspn(entries[foundIndex].seriesName, "\n")] = '\0';
                toUpperCase(entries[foundIndex].seriesName);
                break;
            case 2:
                printf("New Genre #1: ");
                memset(entries[foundIndex].genre1, 0, sizeof(entries[foundIndex].genre1));
                fgets(entries[foundIndex].genre1, sizeof(entries[foundIndex].genre1), stdin);
                entries[foundIndex].genre1[strcspn(entries[foundIndex].genre1, "\n")] = '\0';
                toUpperCase(entries[foundIndex].genre1);
                break;
            case 3:
                printf("New Genre #2: ");
                memset(entries[foundIndex].genre2, 0, sizeof(entries[foundIndex].genre2));
                fgets(entries[foundIndex].genre2, sizeof(entries[foundIndex].genre2), stdin);
                entries[foundIndex].genre2[strcspn(entries[foundIndex].genre2, "\n")] = '\0';
                toUpperCase(entries[foundIndex].genre2);
                break;
            case 4:
                printf("New Total Episodes: ");
                fgets(buffer, sizeof(buffer), stdin);
                entries[foundIndex].numEpisodes = atoi(buffer);
                break;
            case 5:
                printf("New Last Episode Watched: ");
                fgets(buffer, sizeof(buffer), stdin);
                entries[foundIndex].lastEpWatched = atoi(buffer);
                break;
            case 6:
                free(entries);
                printMenu();
                return;
            default:
                printf("Invalid option. Try again.\n");
                continue;
        }

        // Recalculate completion
        entries[foundIndex].watchComplete = (entries[foundIndex].numEpisodes == entries[foundIndex].lastEpWatched);
        break;
    }

    FILE *file = fopen("mySeriesList.txt", "w");
    if (file != NULL)
    {
        for (int i = 0; i < total; i++)
        {
            fprintf(file, "%s|%s|%s|%04d|%04d|%d\n",
                entries[i].seriesName,
                entries[i].genre1,
                entries[i].genre2,
                entries[i].numEpisodes,
                entries[i].lastEpWatched,
                entries[i].watchComplete);
        }
        fclose(file);

        printf("\nPLEASE WAIT... UPDATING FILE...");
        Beep(1000, 100);
        Beep(1400, 100);
        Sleep(2000);
    }
    else
    {
        printf("Error saving changes to file.\n");
    }

    free(entries);
    printMenu();
}




void removeEntry()
{
    system("cls");

    int total = 0;
    struct mySeries *entries = loadEntries(&total);

    if(entries == NULL || total == 0)
    {
        printf("NO SERIES FOUND...\n");
        Sleep(2000);
        printMenu();
        return;
    }

    // Print Logo
    printf(" ____  _____ __  __  _____     _______      _____ _   _ _____ ______   __\n");
    printf("|  _ \\| ____|  \\/  |/ _ \\ \\   / / ____|    | ____| \\ | |_   _|  _ \\ \\ / /\n");
    printf("| |_) |  _| | |\\/| | | | \\ \\ / /|  _|      |  _| |  \\| | | | | |_) \\ V /\n");
    printf("|  _ <| |___| |  | | |_| |\\ V / | |___     | |___| |\\  | | | |  _ < | |\n");
    printf("|_| \\_\\_____|_|  |_|\\___/  \\_/  |_____|    |_____|_| \\_| |_| |_| \\_\\|_|\n");
    printf("\n");

    char searchName[30];
    printf("ENTER SERIES NAME: ");
    cleanInput();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    toUpperCase(searchName);

    int foundIndex = -1;
    for(int i= 0; i < total; i++)
    {
        if(strcmp(entries[i].seriesName, searchName) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        printf("SERIES NOT FOUND...");
        Sleep(2000);
        printMenu();
        return;
    }

    // Display series match
    printf("\nMATCH FOUND. CURRENT ENTRY DETAILS:\n\n");
    printf("Series Name       : %s\n", entries[foundIndex].seriesName);
    printf("Genre #1          : %s\n", entries[foundIndex].genre1);
    printf("Genre #2          : %s\n", entries[foundIndex].genre2);
    printf("Episodes Total    : %d\n", entries[foundIndex].numEpisodes);
    printf("Last Ep Watched   : %d\n", entries[foundIndex].lastEpWatched);
    printf("Watch Complete    : %s\n", entries[foundIndex].watchComplete ? "YES" : "NO");
    printf("\n");

    printf("REMOVE THIS SERIES (Y = YES    N = NO)? ");
    char usrChoice = '\0';
    scanf(" %c", &usrChoice);
    usrChoice = toupper(usrChoice);

    switch(usrChoice)
    {
        case 'Y':
            // Shift entries left to overwrite the removed entry
            for(int i = foundIndex; i < total - 1; i++)
            {
                entries[i] = entries[i + 1];
            }
            total--;

            // Open file in write mode and overwrite all entries
            FILE *file = fopen("mySeriesList.txt", "w");
            if(file != NULL)
            {
                for(int i = 0; i < total; i++)
                {       
                    fprintf(file, "%s|%s|%s|%04d|%04d|%d\n",
                    entries[i].seriesName,
                    entries[i].genre1,
                    entries[i].genre2,
                    entries[i].numEpisodes,
                    entries[i].lastEpWatched,
                    entries[i].watchComplete);
                }
                fclose(file);
                printf("\nSERIES REMOVED SUCCESSFULLY!\n");
                Beep(1000, 100);
                Beep(1400, 100);
                Sleep(2000);
            }
            else
            {
                printf("ERROR WHILE SAVING CHANGES TO FILE.\n");
            }

            // Clean up
            free(entries);
            printMenu();
            break;
        case 'N':
            printMenu();
            break;
        default:
            printf("UNRECOGNIZED INPUT...");
            Sleep(2000);
            printMenu();
            break;
    }
    
}




void viewList()
{
    system("cls");

    // Starts a "fake" loading bar
    printf("LOADING SERIES LIST...\n\n");
    printf("[");
    for(int i = 0; i < 30; i++)
    {
        printf("|");
        Sleep(50);
    }
    printf("]");

    // "Loading finished" beeps
    Beep(1000, 80);
    Beep(1400, 80);

    Sleep(500);

    system("cls");

    // Print logo
    printf(" ____    ___     _______ ____    ____  _____ ____  ___ _____ ____  \n");
    printf("/ ___|  / \\ \\   / / ____|  _ \\  / ___|| ____|  _ \\|_ _| ____/ ___| \n");
    printf("\\___ \\ / _ \\ \\ / /|  _| | | | | \\___ \\|  _| | |_) || ||  _| \\___ \\ \n");
    printf(" ___) / ___ \\ V / | |___| |_| |  ___) | |___|  _ < | || |___ ___) |\n");
    printf("|____/_/   \\_\\_/  |_____|____/  |____/|_____|_| \\_\\___|_____|____/ \n");
    printf("\n");

    cleanInput();

    // Opening file in read mode
    FILE *file = fopen("mySeriesList.txt", "r");
    if(file == NULL)
    {
        printf("NO ENTRIES FOUND: YOUR LIST IS EMPTY...\n");
        Sleep(2000);
        printMenu();
        return;
    }

    // This variable will store a whole line of the document
    char line[256];
    while(fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n' || line[0] == '\0')
        continue;

        int pipeCount = 0;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '|') pipeCount++;
        }
        if (pipeCount < 5)
        continue;  // skip malformed lines
        
        char *token = strtok(line, "|");
        int field = 0;

        while(token != NULL)
        {
            switch(field)
            {
                case 0:
                    printf("Series name      : %s\n", token);
                    break;
                case 1:
                    printf("Genre #1         : %s\n", token);
                    break;
                case 2:
                    printf("Genre #2         : %s\n", token);
                    break;
                case 3:
                    printf("Total episodes   : %s\n", token);
                    break;
                case 4:
                    printf("Last ep. watched : %s\n", token);
                    break;
                case 5:
                    //printf("Watch complete   : %s\n", token);
                    if(atoi(token) == 0)
                    {
                        printf("Watch complete   : NO\n");
                        printf("\n");
                    }
                    else
                    {
                        printf("Watch complete   : YES\n");
                        printf("\n");
                    }
                    break;
                default:
                    break;
            }

            token = strtok(NULL, "|");
            field++;
        }

        // Simulates loading 
        Sleep(1000);
    }

    fclose(file);

    printf("\nPRESS ANY KEY TO RETURN TO MAIN MENU...");
    getchar();
    printMenu();
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Cleans STDIN to remove the possibility of '\n' skipping
|   input prompts
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void cleanInput()
{
    int ch = 0;
    while((ch = getchar()) != '\n' && ch != EOF); // flush any leftovers
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Switches the "string" variables of the series struct 
|   to upper case
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void toUpperCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   Counts the number of series written in the file
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
int getEntryCount()
{
    FILE *file = fopen("mySeriesList.txt", "r");

    if(file == NULL)
    {
        return 0;
    }

    int entryCount = 0;
    char ch;

    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\n')
        {
            entryCount++;
        }
    }

    fclose(file);
    return entryCount;
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
|   I'll be honest, I had no idea how to dynamically allocate
|   an array of structs so I asked Copilot...sorry :(
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
struct mySeries *loadEntries(int *total)
{
    *total = getEntryCount();
    if (*total == 0)
    {
        return NULL;
    }

    struct mySeries *entries = malloc(sizeof(struct mySeries) * (*total));
    if (entries == NULL)
    {
        return NULL;
    }

    FILE *file = fopen("mySeriesList.txt", "r");
    if (file == NULL)
    {
        free(entries);
        return NULL;
    }

    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n' || line[0] == '\0')
            continue;

        // Skips any malformed lines by counting separators
        int pipeCount = 0;
        for (int j = 0; line[j] != '\0'; j++)
        {
            if (line[j] == '|') pipeCount++;
        }
        if (pipeCount < 5)
            continue;

        char *token = strtok(line, "|");
        if (token != NULL) strcpy(entries[i].seriesName, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(entries[i].genre1, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(entries[i].genre2, token);

        token = strtok(NULL, "|");
        if (token != NULL) entries[i].numEpisodes = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) entries[i].lastEpWatched = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) entries[i].watchComplete = atoi(token);

        i++;
    }

    fclose(file);

    *total = i; // Just in case some entries were skipped
    return entries;
}