#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>      
#include <SFML/Graphics.h>
int randomh = 0, part = 1;
int itera = 0;
int major = 0, cont = 0, lims = 799;
struct data
{
        int height;
        int posx;
} line[800];

int main()
{       // setting windows screen
        sfVideoMode mode = {800, 600, 32};
        sfRenderWindow *window = sfRenderWindow_create(mode, "Bubble Sort", sfResize | sfClose, NULL);
        sfRectangleShape *shape = sfRectangleShape_create();
        sfRectangleShape_setFillColor(shape, sfGreen);
        while (sfRenderWindow_isOpen(window))
        {
                sfEvent event;
                while (sfRenderWindow_pollEvent(window, &event))   //for closing window
                {
                        if (event.type == sfEvtClosed)
                        {
                                sfRenderWindow_close(window);
                        }
                }
                if (part == 2)                                          // Bubble Sort Logic
                {
                        if (line[itera].height > line[itera + 1].height)
                        {

                                major = line[itera+1].height;
                                line[itera+1].height = line[itera].height;
                                line[itera].height = major;
                        }
                }
                // Generating random numbers as array input
                if (part == 1)
                {
                        for (int i = 0; i < 800; i++)
                        {
                                randomh = 1 + rand() % (600);
                                line[i].posx = i;
                                line[i].height = randomh;
                                if (i == 799)
                                {
                                        part = 2;
                                }
                        }
                }
                // Visualising everything in the window
                sfRenderWindow_clear(window, sfBlack);
                for (int i = 0; i < 800; i++)
                {
                        sfRectangleShape_setFillColor(shape, sfGreen);
                        if (i == itera)
                        {
                                sfRectangleShape_setFillColor(shape, sfRed);
                        }
                        
                        sfRectangleShape_setPosition(shape, (sfVector2f){line[i].posx, 600});
                        sfRectangleShape_setSize(shape, (sfVector2f){2, line[i].height});
                        sfRectangleShape_setRotation(shape, 180);
                        sfRenderWindow_drawRectangleShape(window, shape, NULL);
                }

                sfRenderWindow_display(window);
                itera++;
                if (itera >= lims)
                {
                        itera = 0;
                        cont++;
                        lims--;
                }
        }

        return 0;
}
