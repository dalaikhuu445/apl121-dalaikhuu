#include <stdio.h>

#define DAYS 7
#define MAX_RIDES 20
#define MAX_BALANCE 100000

/* Сургалтын тариф:
   эхний суулт 1000₮, дараагийн суулт бүр 500₮.
   0 суулт бол 0₮. */
int dailyCost(int rides) {
    if (rides == 0) {
        return 0;
    }
    return 1000 + (rides - 1) * 500;
}

int main(void) {
    int balance;
    int rides;
    int day;
    int cost;
    int totalPaid = 0;
    int totalRidesPaid = 0;
    int firstRechargeDay = 0;
    int paid;
    int dailyCosts[DAYS] = {0};

    do {
        printf("Ehnii uldegdel (0-%d): ", MAX_BALANCE);
        if (scanf("%d", &balance) != 1) {
            printf("Too oruulna uu.\n");
            return 1;
        }
        if (balance < 0 || balance > MAX_BALANCE) {
            printf("Buruu utga! 0-%d hoorond oruul.\n", MAX_BALANCE);
        }
    } while (balance < 0 || balance > MAX_BALANCE);

    printf("\n%-8s %-10s %-12s %-12s %-10s\n",
           "Udur", "Suult", "Zardal", "Uldegdel", "Tuluv");

    for (day = 1; day <= DAYS; day++) {
        do {
            printf("%d-r udriin suultiin too (0-%d): ", day, MAX_RIDES);
            if (scanf("%d", &rides) != 1) {
                printf("Too oruulna uu.\n");
                return 1;
            }
            if (rides < 0 || rides > MAX_RIDES) {
                printf("Buruu utga! 0-%d hoorond oruul.\n", MAX_RIDES);
            }
        } while (rides < 0 || rides > MAX_RIDES);

        cost = dailyCost(rides);
        dailyCosts[day - 1] = cost;

        /* && логик үйлдэл */
        paid = (balance >= cost && rides >= 0);

        if (paid) {
            balance -= cost;
            totalPaid += cost;
            totalRidesPaid += rides;
            printf("%-8d %-10d %-12d %-12d %-10s\n",
                   day, rides, cost, balance, "Tulugdsun");
        } else {
            /* || логик үйлдэл */
            if (firstRechargeDay == 0 || firstRechargeDay < 0) {
                firstRechargeDay = day;
            }
            printf("%-8d %-10d %-12d %-12d %-10s\n",
                   day, rides, cost, balance, "Mungu hurehgui");
        }
    }

    /* Эхний 3 өдрийн тооцоолсон зардлыг өсөхөөр эрэмбэлнэ. */
    {
        int a = dailyCosts[0], b = dailyCosts[1], c = dailyCosts[2];
        int temp;

        if (a > b) { temp = a; a = b; b = temp; }
        if (a > c) { temp = a; a = c; c = temp; }
        if (b > c) { temp = b; b = c; c = temp; }

        printf("\n--- 7 honogiin dun ---\n");
        printf("Niit tulugdsun zardal: %d tugrug\n", totalPaid);
        printf("Tulugdsun suultiin too: %d\n", totalRidesPaid);
        printf("Etssiin uldegdel: %d tugrug\n", balance);

        if (firstRechargeDay == 0) {
            printf("Tsenegleh shaardlaga garaagui.\n");
        } else {
            printf("Tsenegleh shaardlagatai anhnii odor: %d\n",
                   firstRechargeDay);
        }
        printf("Ehnii 3 udriin zardal (bagaas ih): %d, %d, %d\n",
               a, b, c);
    }

    return 0;
}
