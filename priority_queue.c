#include <stdio.h>
#include <stdlib.h>

struct Job
{
    int id;
    int priority;
};

struct Job heap[100];
int n = 0;

// swap function
void swap(struct Job *a, struct Job *b)
{
    struct Job temp = *a;
    *a = *b;
    *b = temp;
}

// insert job
void insert(int id, int p)
{
    n = n + 1;

    heap[n].id = id;
    heap[n].priority = p;

    int i = n;

    while(i > 1 && heap[i].priority > heap[i/2].priority)
    {
        swap(&heap[i], &heap[i/2]);
        i = i / 2;
    }
}

// delete highest priority job
void deleteJob()
{
    if(n == 0)
    {
        printf("No job available\n");
        return;
    }

    printf("Executing Job: %d (Priority %d)\n",
           heap[1].id, heap[1].priority);

    heap[1] = heap[n];
    n--;

    int i = 1;

    while(2*i <= n)
    {
        int largest = i;
        int l = 2*i;
        int r = 2*i + 1;

        if(l <= n && heap[l].priority > heap[largest].priority)
            largest = l;

        if(r <= n && heap[r].priority > heap[largest].priority)
            largest = r;

        if(largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }
}

// display heap
void display()
{
    if(n == 0)
    {
        printf("Queue empty\n");
        return;
    }

    printf("Jobs in queue:\n");

    for(int i = 1; i <= n; i++)
    {
        printf("Job ID: %d Priority: %d\n",
               heap[i].id, heap[i].priority);
    }
}

int main()
{
    int choice, id, p;

    while(1)
    {
        printf("\n1.Insert Job");
        printf("\n2.Execute Job");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter job id: ");
                scanf("%d", &id);

                printf("Enter priority: ");
                scanf("%d", &p);

                insert(id, p);
                break;

            case 2:
                deleteJob();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Wrong choice\n");
        }
    }

    return 0;
}

// Time Complexity
// Insert → O(log n)
// Delete → O(log n)
// Display → O(n)

// 📌 Real Applications
// CPU scheduling in OS
// Task priority management
// Printer job scheduling
// Real-time systems
// Network packet handling

// Steps to Write Priority Queue (Heap) Code (Short)
// Define structure (Job) → id and priority
// Create heap array → to store jobs
// Write swap function → to exchange two jobs
// Insert function (heap insert) → add job and adjust using heap-up
// Delete function (heap delete) → remove highest priority job and adjust using heap-down
// Display function → print all jobs in queue
// Main function → menu (insert, delete, display, exit)