/*
** EPITECH PROJECT, 2024
** bootstrap graph
** File description:
** struct_init
*/

#include "my.h"

framebuffer_t *framebuffer_create(unsigned int width,
    unsigned int height)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    fb->width = width;
    fb->height = height;
    fb->pixels = malloc(width * height * 4);
    return fb;
}

app_t *app_init(unsigned int w, unsigned int h)
{
    app_t *app = malloc(sizeof(app_t));
    sfVideoMode video_mode = {w, h, 32};

    app->window = sfRenderWindow_create(video_mode,
        "Pong Game", sfDefaultStyle, NULL);
    app->framebuffer = framebuffer_create(w, h);
    app->texture = sfTexture_create(w, h);
    app->sprite = sfSprite_create();
    sfSprite_setTexture(app->sprite, app->texture, sfTrue);
    sfRenderWindow_setFramerateLimit(app->window, 60);
    return app;
}

paddle_t init_paddle(float x, float y, float width, float height)
{
    paddle_t paddle;

    paddle.position = (sfVector2f){x, y};
    paddle.size = (sfVector2f){width, height};
    paddle.color = sfColor_fromRGB(255, 255, 255);
    return paddle;
}

ball_t init_ball(int size, float vx, float vy)
{
    ball_t ball;

    ball.position = (sfVector2f){400, 300};
    ball.velocity = (sfVector2f){vx, vy};
    ball.size = size;
    ball.color = sfColor_fromRGB(255, 0, 0);
    return ball;
}

void free_app(app_t *app)
{
    free(app->framebuffer->pixels);
    free(app->framebuffer);
    sfSprite_destroy(app->sprite);
    sfTexture_destroy(app->texture);
    sfRenderWindow_destroy(app->window);
    free(app);
}
