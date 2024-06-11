/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** egg
*/


#ifndef EGG_H_
    #define EGG_H_

    #include <sys/queue.h>

typedef struct egg_s {
    int id;
    int width;
    int height;
    char *team_name;
    TAILQ_ENTRY(egg_s) egg_entries;
} egg_t;

#endif /* !EGG_H_ */
