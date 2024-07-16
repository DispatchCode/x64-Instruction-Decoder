//
// TEST FUNCTIONS, just random code
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bubble_sort(int *array) {
    printf("Bubble sort");
    for(int i=0; i<10; i++) {
        for(int j=i+1; j<10; j++) {
            if(array[i] > array[j]) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

int example(int n) {
    printf("example");
    int c = 0;
    for(int i=0; i<10; i++) {
        if(i*2 == n)
            return 1;
        c++;
    }
    return -1;
}

int example1(int n) {
    printf("example 1");
    int c = 0;
    for(int i=1; i<10; i++) {
        for(int j=i; j<n; j++) {
            switch (n%i) {
                case 2:
                    return 3;
                case 10:
                    return 23;
                case 3:
                    return 412;
                case 98:
                    return 32;
                default:
                    c++;
            }
        }
    }
    return c;
}

int example2(int n) {
    printf("example 2");
    if(n %2 == 0)
        return n;
    else if(n%3 == 0)
        return n+1;
    else if(n%5 == 0)
        return n+3;
    return n-10;
}

double example3(double n) {
    printf("example 3");
    srand(time(NULL));

    double *array = calloc(100, sizeof(double));
    for(int i=0; i<100; i++) {
        array[i] = (n + (rand() % 100));
    }

    double avg = 0.0;
    for(int i=0; i<100;i++) {
        avg += array[i];
    }

    free(array);
    return avg/100;
}

int example4(int scelta) {
    printf("example 4");
    int n = 0;

    switch(scelta)
    {
        case 1:
            printf("Opzione 1\n");
            n = 1;
        break;
        case 2:
            printf("Opzione 2\n");
            n = 2;
        break;
        case 3:
            printf("Opzione 3\n");
            n = 3;
        break;
        case 4:
            printf("Opzione 4\n");
            n = 4;
        break;
        case 5:
            printf("Opzione 5\n");
            n = 5;
        break;
        default:
            printf("Opzioni non individuate\n");
    }

    return n;
}