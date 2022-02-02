#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

int n = 80;
int recHs[80];
bool sorted = false;

void dispSort(int index, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRectangleShape *shape = sfRectangleShape_create();
    for (int i = 0; i < n; i++)
    {
        sfRectangleShape_setFillColor(shape, sfWhite);
        sfRectangleShape_setPosition(shape, (sfVector2f){i * 12, 600 - recHs[i]});
        sfRectangleShape_setSize(shape, (sfVector2f){10, recHs[i]});
        sfRectangleShape_setFillColor(shape, sorted || i == index ? sfRed : sfWhite);
        //sfRectangleShape_setRotation(shape, 180);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRenderWindow_display(window);
}
//To get max value from array
int maxElement(int arr[], int n,sfRenderWindow* window)
{
    int maxE = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxE)
        {
            maxE = arr[i];
        }
        dispSort(i,window);
    }
    return maxE;
}
void countSort(int arr[], int n, int exp, sfRenderWindow* window)
{
    int i;
    int output[n]; // output array
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++){
        count[(arr[i] / exp) % 10]++;
        }
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        //dispSort(i,window);
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixSort(int arr[], int n, sfRenderWindow *window)
{
    //usleep(5000000);
    // Find the maximum number to know number of digits
    int m = maxElement(arr, n,window);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        usleep(1000000);
        countSort(arr, n, exp,window);
        dispSort(exp, window);
    }
    sorted = true;
    dispSort(79, window);
}

int main()
{
    sfVideoMode mode = {960, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Radix Sort", sfResize | sfClose, NULL);
    for (int i = 0; i < n; i++)
    {
        recHs[i] = (int)(rand() % 500);
    }

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
        }

        if (!sorted)
        {
            dispSort(0, window);
            radixSort(recHs,80,window);
        }
    }
    return 0;
}
