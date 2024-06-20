                                                Zappy Server
                                        Legrand Eva - Harkouk Yanis

# Introduction

The Zappy Server manages multiple clients that can take 2 roles, player or GUI (only one GUI is allowed).

The server manages the whole game, and sends appropriate informations to the clients according to their roles and the context.

# How to Launch

To launch the Zappy Server, here's the syntax to follow:

```bash
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq --immortal isImmortal
```

- port is the port number
- width is the width of the world
- height is the height of the world
- nameX is the name of the team X
- clientsNb is the number of authorized clients per team
- freq is the reciprocal of time unit for execution of actions (optional, set to 100 by default)
- isImmortal is the state of immortality for the players (optional, set to false by default)

# Immortal mode

In Immortal mode, the player does not consume food every 126 time units, and the server does not check if he has no more food in his inventory either.

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
