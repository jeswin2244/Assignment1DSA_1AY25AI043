
#include <stdio.h>
#define MAX 20
#define MAX_TERMS (MAX * MAX)

typedef struct {
    int row, col, value;
} term;

void display_triples(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms == 0)
        return;

    
    for (i = 1; i <= num_terms; i++) {
        row_terms[a[i].col]++;
    }

    
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", starting_pos[i]);
    }
    printf("\n");

    for (i = 1; i <= num_terms; i++) {
        j = a[i].col;

        int pos = starting_pos[j]++;

        b[pos].row = a[i].col;
        b[pos].col = a[i].row;
        b[pos].value = a[i].value;
    }
}

int main(void) {
    term a[MAX_TERMS + 1], b[MAX_TERMS + 1];
    int matrix[MAX][MAX] = {0};
    int rows, cols, i, j, k = 1;

    printf("Enter number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || rows > MAX ||
        cols <= 0 || cols > MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid matrix input.\n");
                return 1;
            }

            if (matrix[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    display_triples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display_triples(b);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}

