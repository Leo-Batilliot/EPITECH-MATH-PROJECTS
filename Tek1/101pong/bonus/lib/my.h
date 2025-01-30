/*
** EPITECH PROJECT, 2024
** myh
** File description:
** task 02
*/
#ifndef TEST_H
    #define TEST_H
    #include <stdlib.h>
    #include <SFML/Graphics.h>
    #include <time.h>

typedef struct framebuffer {
    sfUint8 *pixels;
    int width;
    unsigned int height;
} framebuffer_t;

typedef struct {
    sfVector2f position;
    sfVector2f size;
    sfColor color;
} paddle_t;

typedef struct {
    sfVector2f position;
    sfVector2f velocity;
    int size;
    sfColor color;
} ball_t;

typedef struct {
    sfRenderWindow *window;
    sfTexture *texture;
    sfSprite *sprite;
    framebuffer_t *framebuffer;
    sfEvent event;
} app_t;
void free_app(app_t *app);
ball_t init_ball(int size, float vx, float vy);
paddle_t init_paddle(float x, float y, float width, float height);
app_t *app_init(unsigned int w, unsigned int h);
framebuffer_t *framebuffer_create(unsigned int, unsigned int);

#endif /* TEST_H */
