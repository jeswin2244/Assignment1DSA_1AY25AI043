
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];  
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, j;
    int max_degree = (a.degree > b.degree) ? a.degree : b.degree;

    result.degree = max_degree;

    for (i = 0; i <= max_degree; i++) {
        result.coef[i] = 0.0;
    }

    
    for (i = 0; i <= a.degree; i++) {
        int exponent = a.degree - i;
        result.coef[max_degree - exponent] += a.coef[i];
    }

    for (j = 0; j <= b.degree; j++) {
        int exponent = b.degree - j;
        result.coef[max_degree - exponent] += b.coef[j];
    }

    return result;
}

void display(polynomial p) {
    int i, exponent;
    int printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exponent = p.degree - i;

        if (c == 0.0f)
            continue;

        if (printed) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        if (c < 0)
            c = -c;

        if (exponent == 0) {
            printf("%g", c);
        } else if (exponent == 1) {
            if (c == 1.0f)
                printf("x");
            else
                printf("%gx", c);
        } else {
            if (c == 1.0f)
                printf("x^%d", exponent);
            else
                printf("%gx^%d", c, exponent);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

int main() {
    polynomial a, b, result;
    int i;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &a.degree);

    if (a.degree < 0 || a.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients from highest degree to constant:\n");
    for (i = 0; i <= a.degree; i++) {
        scanf("%f", &a.coef[i]);
    }

    printf("Enter degree of second polynomial: ");
    scanf("%d", &b.degree);

    if (b.degree < 0 || b.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients from highest degree to constant:\n");
    for (i = 0; i <= b.degree; i++) {
        scanf("%f", &b.coef[i]);
    }

    result = add(a, b);

    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(result);

    return 0;
}

