#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Count matches
int match(char text[], char word[]) {
    int max_count = 0;
    int word_len = strlen(word);
    int text_len = strlen(text);

    for (int i = 0; i < text_len; i++) {
        int count = 0;
        int j = i;
        
        // Check consecutive matches
        while (j + word_len <= text_len) {
            if (strncmp(&text[j], word, word_len) == 0) {
                count++;
                j = j + word_len;
            } else {
                break;
            }
        }
        
        if (count > max_count) {
            max_count = count;
        }
    }
    return max_count;
}

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc != 3) {
        printf("Usage: ./DNA database.csv sequence.txt\n");
        return 1;
    }

    // Read DNA sequence
    char dna[100000];
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        printf("Could not open %s\n", argv[2]);
        return 1;
    }
    if (fscanf(file, "%s", dna) != 1) {
        printf("Could not read DNA sequence\n");
        fclose(file);
        return 1;
    }
    fclose(file);

    // Open database
    FILE *csv = fopen(argv[1], "r");
    if (!csv) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    char line[1024];
    
    // Read header line
    if (fgets(line, 1024, csv) == NULL) {
        printf("Could not read database header\n");
        fclose(csv);
        return 1;
    }
    
    // Remove newline
    int len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    // Parse header to get STRs
    char *token = strtok(line, ",");
    if (token == NULL) {
        fclose(csv);
        return 1;
    }
    token = strtok(NULL, ","); // Skip "name"
    
    int counts[50];
    int num_strs = 0;

    // Count each STR in DNA
    while (token != NULL) {
        counts[num_strs] = match(dna, token);
        num_strs++;
        token = strtok(NULL, ",");
    }

    // Check each person
    while (fgets(line, 1024, csv)) {
        // Remove newline
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Get name
        char *name = strtok(line, ",");
        if (name == NULL) {
            continue;
        }
        
        int found_match = 1;

        // Compare counts
        for (int i = 0; i < num_strs; i++) {
            char *num_str = strtok(NULL, ",");
            if (num_str == NULL) {
                found_match = 0;
                break;
            }
            int person_count = atoi(num_str);
            
            if (person_count != counts[i]) {
                found_match = 0;
                break;
            }
        }

        // Found match
        if (found_match == 1) {
            printf("%s\n", name);
            fclose(csv);
            return 0;
        }
    }

    printf("No match\n");
    fclose(csv);
    return 0;
}
