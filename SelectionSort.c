#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

int n = 80;
float recHs[80];
bool sorted = false;

void dispSort(int index, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRectangleShape *shape = sfRectangleShape_create();
    for (int i = 0; i < n; i++)
    {
        sfRectangleShape_setFillColor(shape, sfWhite);
        sfRectangleShape_setPosition(shape, (sfVector2f){i * 12, 600 - recHs[i]});
        sfRectangleShape_setSize(shape,(sfVector2f){10,recHs[i]});
        sfRectangleShape_setFillColor(shape, sorted || i == index ? sfBlue : sfWhite);
        //sfRectangleShape_setRotation(shape, 180);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRenderWindow_display(window);
}

void selectionSort(sfRenderWindow *window)
{
    //usleep(5000000);
    int i, min_index, j;
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j=i+1;j<n;j++)
        {
            if (recHs[j]<recHs[min_index])
            {
                min_index=j;
            }
            dispSort(j,window);
        }
        if (min_index!=i)
        {
            int temp = recHs[min_index];
            recHs[min_index]=recHs[i];
            recHs[i]=temp;
        }
        

    }

    sorted = true;

    dispSort(i, window);
}

int main()
{
    sfVideoMode mode = {960, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Selection Sort", sfResize | sfClose, NULL);
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
            selectionSort(window);
        }
    }
    return 0;
}
