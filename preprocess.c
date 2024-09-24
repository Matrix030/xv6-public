#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// Buffer size for reading file contents
#define BUF_SIZE 1024

// Custom implementation of strchr (find first occurrence of char in string)
char *custom_strchr(const char *str, char c) {
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return 0;
}

// Custom implementation of strstr (find first occurrence of substring)
char *custom_strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    
    const char *p1, *p2;
    for (p1 = haystack; *p1; p1++) {
        for (p2 = needle; *p2 && *(p1 + (p2 - needle)) == *p2; p2++);
        if (!*p2) return (char *)p1;
    }
    return 0;
}

// Custom implementation of strncat (concatenate strings)
void custom_strncat(char *dest, const char *src, int n) {
    while (*dest) dest++;  // Move to end of dest
    while (n-- && (*dest++ = *src++));  // Copy n characters
    *dest = '\0';  // Null terminate
}

// Custom implementation of strcpy (copy string)
void custom_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0');
}

// Custom implementation of strlen (get length of string)
int custom_strlen(const char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}

// Custom implementation of memset (set buffer to a value)
void *custom_memset(void *s, int c, uint n) {
    char *p = (char *)s;
    while (n--) {
        *p++ = c;
    }
    return s;
}

// Custom implementation of strncmp (compare two strings)
int custom_strncmp(const char *s1, const char *s2, uint n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Function to replace variables in the text with their definitions
void replace_text(char *buffer, const char *var, const char *val) {
    char temp[BUF_SIZE];
    char *pos, *start = buffer;

    // Clear temp buffer
    custom_memset(temp, 0, sizeof(temp));

    // Loop through the buffer and replace occurrences of the variable
    while ((pos = custom_strstr(start, var)) != 0) {
        // Copy part before the variable
        custom_strncat(temp, start, pos - start);
        // Append the replacement value
        custom_strncat(temp, val, custom_strlen(val));
        // Move past the variable
        start = pos + custom_strlen(var);
    }

    // Copy any remaining part of the buffer
    custom_strncat(temp, start, custom_strlen(start));
    // Copy back the modified text to the buffer
    custom_strcpy(buffer, temp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: preprocess <input_file> -D<var1>=<val1> ...\n");
        exit();
    }

    // Open the input file
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(2, "Error: Could not open file %s\n", argv[1]);
        exit();
    }

    // Read the file content into buffer
    char buffer[BUF_SIZE];
    custom_memset(buffer, 0, sizeof(buffer));
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        printf(2, "Error: Could not read file\n");
        close(fd);
        exit();
    }
    buffer[n] = '\0';  // Ensure buffer is null-terminated
    close(fd);

    // Process command line arguments for -D<var>=<val>
    for (int i = 2; i < argc; i++) {
        if (custom_strncmp(argv[i], "-D", 2) == 0) {
            char *definition = argv[i] + 2;
            char *equal_sign = custom_strchr(definition, '=');
            if (!equal_sign) {
                printf(2, "Error: Invalid definition format %s\n", argv[i]);
                exit();
            }

            // Separate the variable and its value
            *equal_sign = '\0';
            char *var = definition;
            char *val = equal_sign + 1;

            // Replace occurrences of the variable in the text
            replace_text(buffer, var, val);
        }
    }

    // Print the processed text
    printf(1, "%s", buffer);

    exit();
}