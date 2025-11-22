#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CHARS 16
#define MAX_LEN 51

// Struct to hold character data
typedef struct {
    char symbol;
    
    char pattern[10]; 
} DigitalChar;

// Global data structures
DigitalChar CHAR_MAP[MAX_CHARS];
char POSSIBLE_TRANSITIONS[MAX_CHARS][MAX_CHARS];
int PRECEDENCE[256] = {0};


void initialize_char_map() {
    CHAR_MAP[0] = (DigitalChar){'0', " _ | ||_|"};
    CHAR_MAP[1] = (DigitalChar){'1', "     |  |"};
    CHAR_MAP[2] = (DigitalChar){'2', " _  _||_ "};
    CHAR_MAP[3] = (DigitalChar){'3', " _  _| _|"};
    CHAR_MAP[4] = (DigitalChar){'4', "   |_|  |"};
    CHAR_MAP[5] = (DigitalChar){'5', " _ |_  _|" };
    CHAR_MAP[6] = (DigitalChar){'6', " _ |_ |_|"};
    CHAR_MAP[7] = (DigitalChar){'7', " _   |  |"};
    CHAR_MAP[8] = (DigitalChar){'8', " _ |_||_|"};
    CHAR_MAP[9] = (DigitalChar){'9', " _ |_| _|"};
    CHAR_MAP[10] = (DigitalChar){'+', "    | -+-"};
    CHAR_MAP[11] = (DigitalChar){'-', "      ---"};
    CHAR_MAP[12] = (DigitalChar){'*', "   \\ / / \\"};
    CHAR_MAP[13] = (DigitalChar){'/', "     /  / "};
    CHAR_MAP[14] = (DigitalChar){'[', " _ |  |_ "};
    CHAR_MAP[15] = (DigitalChar){']', " _   |_| "};
}

void precompute_transitions() {
    for (int i = 0; i < MAX_CHARS; ++i) {
        int transition_count = 0;
        for (int j = 0; j < MAX_CHARS; ++j) {
            if (i == j) continue;

            int diff = 0;
            for (int k = 0; k < 9; ++k) {
                if (CHAR_MAP[i].pattern[k] != CHAR_MAP[j].pattern[k]) {
                    diff++;
                }
            }
            
            if (diff == 1) {
                POSSIBLE_TRANSITIONS[i][transition_count++] = CHAR_MAP[j].symbol;
            }
        }
        POSSIBLE_TRANSITIONS[i][transition_count] = '\0';
    }
}

char find_char_for_pattern(const char* p) {
    for (int i = 0; i < MAX_CHARS; ++i) {
        if (strcmp(p, CHAR_MAP[i].pattern) == 0) {
            return CHAR_MAP[i].symbol;
        }
    }
    return '\0';
}

int find_index_for_char(char symbol) {
    for (int i = 0; i < MAX_CHARS; ++i) {
        if (CHAR_MAP[i].symbol == symbol) {
            return i;
        }
    }
    return -1;
}

bool is_syntactically_valid(const char* eq) {
    int balance = 0;
    int len = strlen(eq);
    if (len == 0) return false;

    for (int i = 0; i < len; ++i) {
        char current = eq[i];
        if (current == '[') balance++;
        else if (current == ']') balance--;
        if (balance < 0) return false;

        bool is_op = strchr("+-*/", current);
        if (is_op) {
            if (i == 0 || i == len - 1) return false;
            if (strchr("+-*/[", eq[i - 1])) return false;
            if (strchr("+-*/]", eq[i + 1])) return false;
        }
        
        if (current == '0' && i + 1 < len && isdigit(eq[i + 1])) {
            if (i == 0 || !isdigit(eq[i-1])) return false;
        }
    }
    return balance == 0;
}

long long apply_op(long long a, long long b, char op, bool* success) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                *success = false;
                return 0;
            }
            return a / b;
    }
    return 0;
}

long long evaluate(const char* eq, bool* success) {
    long long values[MAX_LEN];
    int values_top = -1;
    char ops[MAX_LEN];
    int ops_top = -1;
    *success = true;

    for (int i = 0; eq[i] != '\0'; ++i) {
        if (isdigit(eq[i])) {
            long long val = 0;
            while (eq[i] != '\0' && isdigit(eq[i])) {
                val = (val * 10) + (eq[i] - '0');
                i++;
            }
            i--;
            values[++values_top] = val;
        } else if (eq[i] == '[') {
            ops[++ops_top] = eq[i];
        } else if (eq[i] == ']') {
            while (ops_top > -1 && ops[ops_top] != '[') {
                if (values_top < 1) { *success = false; return 0; }
                long long v2 = values[values_top--];
                long long v1 = values[values_top--];
                values[++values_top] = apply_op(v1, v2, ops[ops_top--], success);
                if (!(*success)) return 0;
            }
            if (ops_top > -1) ops_top--; else {*success = false; return 0;}
        } else {
            while (ops_top > -1 && ops[ops_top] != '[' && PRECEDENCE[(unsigned char)ops[ops_top]] >= PRECEDENCE[(unsigned char)eq[i]]) {
                 if (values_top < 1) { *success = false; return 0; }
                long long v2 = values[values_top--];
                long long v1 = values[values_top--];
                values[++values_top] = apply_op(v1, v2, ops[ops_top--], success);
                 if (!(*success)) return 0;
            }
            ops[++ops_top] = eq[i];
        }
    }

    while (ops_top > -1) {
        if (ops[ops_top] == '[') { *success = false; return 0; }
        if (values_top < 1) { *success = false; return 0; }
        long long v2 = values[values_top--];
        long long v1 = values[values_top--];
        values[++values_top] = apply_op(v1, v2, ops[ops_top--], success);
        if (!(*success)) return 0;
    }

    if (values_top != 0) { *success = false; return 0; }
    
    return values[0];
}


int main() {
    initialize_char_map();
    precompute_transitions();

    int n;
    scanf("%d", &n);
    while(getchar() != '\n');

    char lines[3][MAX_LEN * 4];
    for (int i = 0; i < 3; ++i) {
        fgets(lines[i], sizeof(lines[i]), stdin);
        lines[i][strcspn(lines[i], "\n")] = 0; 
    }

    char precedence_str[10];
    scanf("%s", precedence_str);
    for (int i = 0; i < strlen(precedence_str); ++i) {
        PRECEDENCE[(unsigned char)precedence_str[i]] = strlen(precedence_str) - i;
    }

    char initial_equation[MAX_LEN];
    for (int i = 0; i < n; ++i) {
        char current_pattern[10];
        snprintf(current_pattern, sizeof(current_pattern), "%.3s%.3s%.3s", 
                 &lines[0][i * 4], &lines[1][i * 4], &lines[2][i * 4]);
        initial_equation[i] = find_char_for_pattern(current_pattern);
    }
    initial_equation[n] = '\0';
    
    long long total_worth = 0;

    for (int i = 0; i < n; ++i) {
        int char_idx = find_index_for_char(initial_equation[i]);
        if (char_idx == -1) continue;

        for (int j = 0; POSSIBLE_TRANSITIONS[char_idx][j] != '\0'; ++j) {
            char new_char = POSSIBLE_TRANSITIONS[char_idx][j];
            
            char new_equation[MAX_LEN];
            strcpy(new_equation, initial_equation);
            new_equation[i] = new_char;

            if (is_syntactically_valid(new_equation)) {
                bool success = false;
                long long result = evaluate(new_equation, &success);
                if (success && result >= 0) {
                    total_worth += result;
                }
            }
        }
    }

    printf("%lld\n", total_worth);
    return 0;
}
