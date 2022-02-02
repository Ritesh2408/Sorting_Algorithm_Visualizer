#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

int n = 80;
float recHs[80];
bool sorted = false;

void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void dispSort(int index, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRectangleShape *shape = sfRectangleShape_create();
    for (int i = 0; i < n; i++)
    {
        sfRectangleShape_setFillColor(shape, sfWhite);
        sfRectangleShape_setPosition(shape, (sfVector2f){i * 12, 600 - recHs[i]});
        sfRectangleShape_setSize(shape,(sfVector2f){10,recHs[i]});
        sfRectangleShape_setFillColor(shape, sorted || i == index ? sfColor_fromRGB(138, 43, 226) : sfWhite);
        //sfRectangleShape_setRotation(shape, 180);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRenderWindow_display(window);
}

int partition(float A[], int low, int high, sfRenderWindow* window)
{
    float pivot = A[high];
    int i = (low-1);
    for (int j = low; j <= high-1; j++)
    {
        if (A[j]<pivot)
        {
            i++;
            swap(&A[i],&A[j]);
        }
        usleep(9000);
        dispSort(j,window);
        
    }
    swap(&A[i+1],&A[high]);
    return (i+1);
    
    
}

void quickSort(sfRenderWindow *window, float A[],int low,int high)
{
    if (low<high)
    {
        int pi = partition(A,low,high,window);
        quickSort(window,A,low,pi-1);
        quickSort(window,A,pi+1,high);
    }
    
}

int main()
{
    sfVideoMode mode = {960, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Quick Sort", sfResize | sfClose, NULL);
    for (int i = 0; i < n; i++)
    {
         recHs[i]=(rand()%500);
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
            quickSort(window,recHs,0,80);

        }
        
    sorted=true;
    dispSort(79,window);
    }
    return 0;
}