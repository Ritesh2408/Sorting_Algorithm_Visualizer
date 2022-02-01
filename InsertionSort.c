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
        sfRectangleShape_setFillColor(shape, sorted || i == index ? sfGreen : sfWhite);
        //sfRectangleShape_setRotation(shape, 180);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRenderWindow_display(window);
}

void insertionSort(sfRenderWindow *window)
{
    //usleep(5000000);
    int i, key, j;
    for (i = 0; i < n; i++)
    {
        key = recHs[i];
        j = i - 1;

        while (j >= 0 && recHs[j] > key)
        {
            recHs[j + 1] = recHs[j];
            j = j - 1;
            dispSort(j, window);
        }
        recHs[j + 1] = key;
    }

    sorted = true;

    dispSort(i, window);
}

int main()
{
    sfVideoMode mode = {960, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Insertion Sort", sfResize | sfClose, NULL);
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
            insertionSort(window);
        }
    }
    return 0;
}
