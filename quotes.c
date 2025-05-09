#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LINE_SIZE 1024
#define MAX_QUOTES 1000

#pragma warning(disable : 4996) // for Visual Studio

struct quote_entry
{
    int number;
    char quote[512];
    char person[256];
};

int parse_line(const char *line, struct quote_entry *entry)
{
    const char *ptr = line;

    // Read number
    if (sscanf(ptr, "%d,", &entry->number) != 1)
        return 1;

    // Move to first quote
    ptr = strchr(ptr, '"');
    if (!ptr)
        return 1;
    ptr++;

    // Read quote
    char *end_quote = strchr(ptr, '"');
    if (!end_quote)
        return 1;
    size_t quote_len = end_quote - ptr;
    strncpy(entry->quote, ptr, quote_len);
    entry->quote[quote_len] = '\0';

    // Move to person
    ptr = strchr(end_quote, ',');
    if (!ptr)
        return 1;
    ptr += 2;
    strncpy(entry->person, ptr, sizeof(entry->person) - 1);
    entry->person[strcspn(entry->person, "\r\n")] = '\0'; // clean newline

    return 0;
}

int main(void)
{
    FILE *pFile = fopen("quotes.txt", "r");
    if (!pFile)
    {
        printf("Could not open quotes.txt\n");
        return 1;
    }

    char buffer[LINE_SIZE];
    struct quote_entry entries[MAX_QUOTES];
    int count = 0;

    while (fgets(buffer, LINE_SIZE, pFile) && count < MAX_QUOTES)
    {
        if (parse_line(buffer, &entries[count]) == 0)
        {
            count++;
        }
        else
        {
            printf("Failed to parse line: %s\n", buffer);
        }
    }

    fclose(pFile);

    if (count == 0)
    {
        printf("No valid quotes found.\n");
        return 1;
    }

    // Get today's date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int day_seed = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
    int index = day_seed % count;

    struct quote_entry selected = entries[index];
    printf("*****************************************\n");
    printf("Quote of the Day:\n");
    printf("\"%s\"\n", selected.quote);
    printf("    - %s\n", selected.person);
    printf("*****************************************\n");

    char add[10];
    printf("Wanna add a quote to the database? (YES or NO): ");
    fgets(add, sizeof(add), stdin);
    add[strcspn(add, "\r\n")] = '\0'; // Remove newline

    // Convert to uppercase for comparison
    for (int i = 0; add[i]; i++)
    {
        add[i] = toupper(add[i]);
    }

    if (strcmp(add, "YES") == 0)
    {
        char newquote[512];
        char newperson[256];

        printf("Write your quote (Without \"): ");
        fgets(newquote, sizeof(newquote), stdin);
        newquote[strcspn(newquote, "\r\n")] = '\0';

        printf("Who made that quote?: ");
        fgets(newperson, sizeof(newperson), stdin);
        newperson[strcspn(newperson, "\r\n")] = '\0';

        FILE *appendFile = fopen("quotes.txt", "a");
        if (!appendFile)
        {
            printf("Could not open quotes.txt\n");
            return 1;
        }

        // Reopen file in read mode to check last character
        FILE *checkFile = fopen("quotes.txt", "rb");
        if (checkFile)
        {
            fseek(checkFile, -1, SEEK_END);
            int last_char = fgetc(checkFile);
            fclose(checkFile);

            if (last_char != '\n')
            {
                fputc('\n', appendFile); // add newline if missing
            }
        }

        fprintf(appendFile, "%d, \"%s\", %s\n", count + 1, newquote, newperson);

        fclose(appendFile);
        printf("Quote added successfully!\n");
    }

    return 0;
}

// got some inspiration from here:
// https://stackoverflow.com/questions/69065578/reading-data-from-file-into-structure-in-c-programming-language
