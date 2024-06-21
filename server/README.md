                                                Zappy Server
                                        Legrand Eva - Harkouk Yanis

# Introduction

The Zappy Server manages multiple clients that can take 2 roles, AI (player) or GUI.

The server manages the whole game, and sends appropriate informations to the clients according to their roles and the context.

All commands sent to the server must end with a new line.

# How to Launch

To launch the Zappy Server, here's the syntax to follow:

```bash
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq --immortal isImmortal
```

| flag       | argument   | details                                                                                |
|------------|------------|----------------------------------------------------------------------------------------|
| -p         | port       | the port number                                                                        |
| -x         | width      | the width of the world                                                                 |
| -y         | height     | the height of the world                                                                |
| -n         | nameX      | the name of the team X                                                                 |
| -c         | clientsNb  | the number of authorized clients per team                                              |
| -f         | freq       | the reciprocal of time unit for execution of actions (optional, set to 100 by default) |
| --immortal | isImmortal | the state of immortality for the players (optional, set to false by default)           |

# Immortal mode

In Immortal mode, the player does not consume food every 126 time units, and the server does not check if he has no more food in his inventory either.

# Server/AI Communication

To connect as an AI, the client must send a team's name.
He will then receive the map size and the number of slots still available for the chosen team.

The client can send up to 10 requests in a row without any response from the server.
Over 10, the server will no longer take them into account.

The server executes the client’s requests in the order they were received.
The requests are buffered and a command’s execution time only blocks the player in question.

# Server/GUI Commucation

To connect as a GUI, the client must send `GRAPHIC` to the server. Only one GUI connection is allowed.

The GUI will then receive the following informations, in order:
- msz X Y\n
- sgt T\n
- bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles
- tna N\n * nbr_teams
- pnw #n X Y O L N\n * nbr_players
- smg eni e X Y\n * nbr_eggs

# Server/AI Protocol

| action                       | command        | time limit | response                                 |
|------------------------------|----------------|------------|------------------------------------------|
| move up one tile             | Forward        | 7/f        | ok                                       |
| turn 90° right               | Right          | 7/f        | ok                                       |
| turn 90° left                | Left           | 7/f        | ok                                       |
| look around                  | Look           | 7/f        | [tile1, tile2,. . . ]                    |
| inventory                    | Inventory      | 1/f        | [linemate n, sibur n,. . . ]             |
| broadcast text               | Broadcast text | 7/f        | ok                                       |
| number of team unused slots  | Connect_nbr    | -          | value                                    |
| fork a player                | Fork           | 42/f       | ok                                       |
| eject players from this tile | Eject          | 7/f        | ok/ko                                    |
| death of a player            | -              | -          | dead                                     |
| take object                  | Take object    | 7/f        | ok/ko                                    |
| set object down              | Set object     | 7/f        | ok/ko                                    |
| start incantation            | Incantation    | 300/f      | Elevation underway - Current level: k/ko |

# Server/GUI Protocol

| symbol meaning                        |
|---------------------------------------|
| X width or horizontal position        |
| Y height or vertical position         |
| q0 resource 0 (food) quantity         |
| q1 resource 1 (linemate) quantity     |
| q2 resource 2 (deraumere) quantity    |
| q3 resource 3 (sibur) quantity        |
| q4 resource 4 (mendiane) quantity     |
| q5 resource 5 (phiras) quantity       |
| q6 resource 6 (thystame) quantity     |
| n player number                       |
| O orientation: 1(N), 2(E), 3(S), 4(W) |
| L player or incantation level         |
| e egg number                          |
| T time unit                           |
| N name of the team                    |
| R incantation result                  |
| M message                             |
| i resource number                     |

| server                                     | client    | details                                       |
|--------------------------------------------|-----------|-----------------------------------------------|
| msz X Y\n                                  | msz\n     | map size                                      |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n             | bct X Y\n | content of a tile                             |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles | mct\n     | content of the map (all the tiles)            |
| tna N\n * nbr_teams                        | tna\n     | name of all the teams                         |
| pnw #n X Y O L N\n                         |           | connection of a new player                    |
| ppo #n X Y O\n                             | ppo #n\n  | player’s position                             |
| plv #n L\n                                 | plv #n\n  | player’s level                                |
| pin #n X Y q0 q1 q2 q3 q4 q5 q6\n          | pin #n\n  | player’s inventory                            |
| pex #n\n                                   |           | expulsion                                     |
| pbc #n M\n                                 |           | broadcast                                     |
| pic X Y L #n #n . . . \n                   |           | start of an incantation (by the first player) |
| pie X Y R\n                                |           | end of an incantation                         |
| pfk #n\n                                   |           | egg laying by the player                      |
| pdr #n i\n                                 |           | resource dropping                             |
| pgt #n i\n                                 |           | resource collecting                           |
| pdi #n\n                                   |           | death of a player                             |
| enw #e #n X Y\n                            |           | an egg was laid by a player                   |
| ebo #e\n                                   |           | player connection for an egg                  |
| edi #e\n                                   |           | death of an egg                               |
| sgt T\n                                    | sgt\n     | time unit request                             |
| sst T\n                                    | sst T\n   | time unit modification                        |
| seg N\n                                    |           | end of game                                   |
| smg M\n                                    |           | message from the server                       |
| smg eni e X Y\n                            |           | egg spawn at the start                       |
| suc\n                                      |           | unknown command                               |
| sbp\n                                      |           | command parameter                             |

# Add an AI Command

To add a AI Command, you will need to add a new line in the following structure array:
```c
command_infos_ia_t cmd_list_ia[NB_IA_CMD] = {
    {EXIT_COMMAND, 0, 1, &exit_func},
    {INVENTORY_COMMAND, 1, 1, &inventory_command},
    {TAKE_COMMAND, 7, 2, &take_object},
    {SET_COMMAND, 7, 2, &set_object},
    {FORWARD_COMMAND, 7, 1, &move_forward},
    {LEFT_COMMAND, 7, 1, &turn_left},
    {RIGHT_COMMAND, 7, 1, &turn_right},
    {CONNECT_NBR_COMMAND, 0, 1, &connect_nbr},
    {FORK_COMMAND, 42, 1, &fork_player},
    {EJECT_COMMAND, 7, 1, &eject_from_tile},
    {LOOK_COMMAND, 7, 1, &look_around},
    {BROADCAST_COMMAND, 7, 2, &broadcast},
    {START_INCANTATION_COMMAND, 0, 1, &start_incantation},
    {END_INCANTATION_COMMAND, 300, 1, &end_incantation}
};
```

The parameters are, in order :
- A define for the command's name
- The time units before command's execution
- The number of arguments required for the command, including the command's name
- The address of the newly implemented function

> Don't forget to increment the NB_IA_COMMAND define.

# Add a GUI Command

To add a GUI Command, you will need to add a new line in the following structure array:
```c
command_infos_gui_t cmd_list_gui[NB_GUI_CMD] = {
    {EXIT_COMMAND, 1, &exit_func},
    {MSZ_COMMAND, 1, &msz_func},
    {BCT_COMMAND, 3, &bct_func},
    {MCT_COMMAND, 1, &mct_func},
    {TNA_COMMAND, 1, &tna_func},
    {PLV_COMMAND, 2, &plv_func},
    {PPO_COMMAND, 2, &ppo_func},
    {PIN_COMMAND, 2, &pin_func},
    {SGT_COMMAND, 1, &sgt_func},
    {SST_COMMAND, 2, &sst_func}
};
```
The parameters are, in order :
- A define for the command's name
- The number of arguments required for the command, including the command's name
- The address of the newly implemented function

> Don't forget to increment the NB_GUI_COMMAND define.
