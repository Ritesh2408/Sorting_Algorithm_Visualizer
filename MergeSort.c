#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
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
        sfRectangleShape_setFillColor(shape, sorted || i == index ? sfCyan : sfWhite);
        //sfRectangleShape_setRotation(shape, 180);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRenderWindow_display(window);
}

void merge(float A[], int l, int mid, int h)
{
    int i = l, j = mid + 1, k = l;
    float B[100];

    while (i <= mid && j <= h)
    {
        if (A[i] < A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
    }
    for (; i <= mid; i++)
    {
        B[k++] = A[i];
    }
    for (; j <= h; j++)
    {
        B[k++] = A[j];
    }
    for (i = l; i <= h; i++)
    {
        A[i] = B[i];
    }
}

void mergeSort(sfRenderWindow *window, float A[], int n)
{
    int p, l, h, mid, i;
    for (p = 2; p <= n; p = p * 2)
    {
        for (i = 0; i + p - 1 < n; i = i + p)
        {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            merge(A, l, mid, h);
            usleep(60000);
            dispSort(i,window);
        }
        if (n - i > p / 2)
        {
            l = i;
            h = i + p - 1;
            mid = (l + h) / 2;
            merge(A, l, mid, n - 1);
        }
        usleep(7000);
        dispSort(p,window);
    }
    if (p / 2 < n)
    {
        merge(A, 0, p / 2 - 1, n - 1);
    }
    sorted = true;
    dispSort(79,window);
}


int main()
{
    sfVideoMode mode = {960, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Merge Sort", sfResize | sfClose, NULL);
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
            mergeSort(window,recHs,80);

        }
    }
    return 0;
}