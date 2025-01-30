/*
** EPITECH PROJECT, 2024
** csfml
** File description:
** Pong Game
*/
#include "lib/my.h"

static void put_pixel(framebuffer_t *fb,
    unsigned int x, unsigned int y, sfColor color)
{
    int index;

    if (x < fb->width && y < fb->height) {
        index = (y * fb->width + x) * 4;
        fb->pixels[index] = color.r;
        fb->pixels[index + 1] = color.g;
        fb->pixels[index + 2] = color.b;
        fb->pixels[index + 3] = color.a;
    }
}

static void draw_rectangle(framebuffer_t *fb, sfVector2f position,
    sfVector2f size, sfColor color)
{
    for (unsigned int y = 0; y < size.y; ++y)
        for (unsigned int x = 0; x < size.x; ++x)
            put_pixel(fb, position.x + x, position.y + y, color);
}

static void clear_framebuffer(framebuffer_t *fb, sfColor color)
{
    for (unsigned int i = 0; i < fb->width * fb->height * 4; i += 4) {
        fb->pixels[i] = color.r;
        fb->pixels[i + 1] = color.g;
        fb->pixels[i + 2] = color.b;
        fb->pixels[i + 3] = color.a;
    }
}

static void move_paddle(paddle_t *paddle, float dy)
{
    paddle->position.y += dy * 2;
    if (paddle->position.y < 0)
        paddle->position.y = 0;
    if (paddle->position.y + paddle->size.y > 600)
        paddle->position.y = 600 - paddle->size.y;
}

static void handle_input(paddle_t *left_paddle, paddle_t *right_paddle)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        move_paddle(left_paddle, -5);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        move_paddle(left_paddle, 5);
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        move_paddle(right_paddle, -5);
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        move_paddle(right_paddle, 5);
}

void update_ball(ball_t *ball, paddle_t *left_paddle, paddle_t *right_paddle)
{
    sfFloatRect ball_bounds = {ball->position.x + ball->velocity.x,
        ball->position.y + ball->velocity.y, ball->size, ball->size};
    sfFloatRect right_bounds = {right_paddle->position.x,
        right_paddle->position.y, right_paddle->size.x, right_paddle->size.y};
    sfFloatRect left_bounds = {left_paddle->position.x,
        left_paddle->position.y, left_paddle->size.x, left_paddle->size.y};

    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;
    if (ball->position.y < 0 || ball->position.y + ball->size > 600)
        ball->velocity.y = -ball->velocity.y;
    if (sfFloatRect_intersects(&ball_bounds, &left_bounds, NULL) ||
        sfFloatRect_intersects(&ball_bounds, &right_bounds, NULL)) {
        ball->velocity.x = -ball->velocity.x;
        ball->velocity.x += (rand() % 2 - 1) * 2;
        ball->velocity.y += (rand() % 2 - 1) * 2;
        left_paddle->size.y += (rand() % 2 - 1) * 5;
        right_paddle->size.y += (rand() % 2 - 1) * 5;
    }
}

int evnt(sfEvent *event, sfRenderWindow *window)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            return 2;
    }
    return 0;
}

int print_window(app_t *app, paddle_t *left_paddle,
    paddle_t *right_paddle, ball_t *ball)
{
    handle_input(left_paddle, right_paddle);
    update_ball(ball, left_paddle, right_paddle);
    clear_framebuffer(app->framebuffer, sfBlack);
    draw_rectangle(app->framebuffer, left_paddle->position,
        left_paddle->size, left_paddle->color);
    draw_rectangle(app->framebuffer, right_paddle->position,
        right_paddle->size, right_paddle->color);
    draw_rectangle(app->framebuffer, ball->position,
        (sfVector2f){ball->size, ball->size}, ball->color);
    sfTexture_updateFromPixels(app->texture,
        app->framebuffer->pixels, 800, 600, 0, 0);
    sfRenderWindow_clear(app->window, sfBlack);
    sfRenderWindow_drawSprite(app->window, app->sprite, NULL);
    sfRenderWindow_display(app->window);
}

int main(void)
{
    unsigned int w = 800;
    unsigned int h = 600;
    app_t *app = app_init(w, h);
    paddle_t left_paddle = init_paddle(50, 250, 10, 100);
    paddle_t right_paddle = init_paddle(740, 250, 10, 100);
    ball_t ball = init_ball(10, 6, 6);

    srand(time(NULL));
    while (sfRenderWindow_isOpen(app->window)) {
        if (evnt(&app->event, app->window) == 2)
            sfRenderWindow_close(app->window);
        if (sfKeyboard_isKeyPressed(sfKeyR)) {
            sfRenderWindow_close(app->window);
            return main();
        }
        print_window(app, &left_paddle, &right_paddle, &ball);
    }
    free_app(app);
    return 0;
}
