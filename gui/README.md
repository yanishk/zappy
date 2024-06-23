# Zappy GUI

#### Mathis Brehm - Timothée Plisson

# Introduction





The Zappy GUI's role is to display the information sent by the server.

The GUI has two parts:
 - a client part
 - a display part

<br>
The client part retrieves information sent by the server and passes it to the display part.
The display part allows for the display of information retrieved by the client.

# How to Launch

To launch the Zappy GUI, here's the syntax to follow:

```bash
./zappy_gui -p port -h IP -a
```

| flag       | argument   | details                                                                                |
|------------|------------|----------------------------------------------------------------------------------------|
| -p         | port       | the port number                                                                        |
| -h         | ip         | Server IP address                                                                      |
| -a         |            | enable the game animations                                                             |

# Server/GUI Commucation

To connect the GUI to the server, the client must send `GRAPHIC` to the server. Only one GUI connection is allowed.

The GUI client will then receive the following informations, in order:
- msz X Y\n
- sgt T\n
- bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles
- tna N\n * nbr_teams
- pnw #n X Y O L N\n * nbr_players
- smg eni e X Y\n * nbr_eggs

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
| smg eni e X Y\n                            |           | egg spawn at the start                        |
| suc\n                                      |           | unknown command                               |
| sbp\n                                      |           | command parameter                             |
