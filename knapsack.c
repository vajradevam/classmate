#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int profit;
    int weight;
    float ratio;
} Item;

void heapify(Item arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].ratio > arr[largest].ratio)
        largest = left;

    if (right < n && arr[right].ratio > arr[largest].ratio)
        largest = right;

    if (largest != i) {
        Item temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapsort(Item arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        Item temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    int n, capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    Item items[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%d %d", &items[i].profit, &items[i].weight);
        items[i].id = i + 1;
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &capacity);

    heapsort(items, n);

    float totalProfit = 0;
    printf("\nItem No\tprofit\t\tWeight\t\tAmount to be taken\n");

    for (int i = n - 1; i >= 0; i--) {
        
        if (capacity >= items[i].weight) {
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].id, (float)items[i].profit, (float)items[i].weight, 1.0);
            totalProfit += items[i].profit;
            capacity -= items[i].weight;
        }
        
        else {
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].id, (float)items[i].profit, (float)items[i].weight, (float)capacity / items[i].weight);
            totalProfit += (float)capacity * items[i].ratio;
            capacity = 0;
            break;
        }
    }

    printf("Maximum profit: %.6f\n", totalProfit);
    return 0;
}