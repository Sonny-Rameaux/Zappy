/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "../server.h"

    #define PF dprintf

    #define BCKR_OUTPUT(fd) PF(fd, "\r\n")
    #define SBP_OUTPUT(fd) PF(fd, "sbp\r\n")
    #define OK_OUTPUT(fd) PF(fd, "ok\r\n")
    #define KO_OUTPUT(fd) PF(fd, "ko\r\n")

    #define MSZ_OUTPUT(fd, x, y) PF(fd, "msz %d %d\r\n", x, y)
    #define TNA_OUTPUT(fd, team_name) PF(fd, "tna %s\n", team_name)
    #define SGT_OUTPUT(fd, f) PF(fd, "sgt %d\r\n", f)
    #define SST_OUTPUT(fd, f) PF(fd, "sst %d\r\n", f)
    #define PPO_OUTPUT(f, n, x, y, o) PF(f, "ppo %d %d %d %s\r\n", n, x, y, o)
    #define PLV_OUTPUT(fd, n, l) PF(fd, "plv %d %d\r\n", n, l)
    #define PIN_OUTPUT(f, n, x, y, i) PF(f, "pin %d %d %d %s\r\n", n, x, y, i)

typedef struct {
    char *buff;
    size_t *offset;
} buffer_info_t;

/* msz.c */
void msz_command(log_t *server, client_info_t *client, char **args);

/* bct.c */
void send_bct_msg(int sd, int x, int y, map_t *map);
void bct_command(log_t *server, client_info_t *client, char **args);

/* mct.c */
void mct_command(log_t *server, client_info_t *client, char **args);

/* tna.c */
void tna_command(log_t *server, client_info_t *client, char **args);

/* sgt.c */
void sgt_command(log_t *server, client_info_t *client, char **args);

/* sst.c */
void sst_command(log_t *server, client_info_t *client, char **args);

/* ppo.c */
void ppo_command(log_t *server, client_info_t *client, char **args);

/* plv.c */
void plv_command(log_t *server, client_info_t *client, char **args);

/* pin.c */
void pin_command(log_t *server, client_info_t *client, char **args);

/* utils.c */
char *orientation_to_str(enum Orientation o);

/* forward.c */
void forward_command(log_t *server, client_info_t *client, char **args);

/* inventory.c */
void inventory_command(log_t *server, client_info_t *client, char **args);

/* take.c */
void take_command(log_t *server, client_info_t *client, char **args);
bool bad_tile_ts(int x, int y, log_t *server);

/* set.c */
void set_command(log_t *server, client_info_t *client, char **args);

/* turn */
void right_command(log_t *server, client_info_t *client, char **args);
void left_command(log_t *server, client_info_t *client, char **args);

/* look */
void look(log_t *server, client_info_t *client, char **args);

/* loop */
void loop_down(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info);
void loop_up(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info);
void loop_right(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info);
void loop_left(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info);

/* eject.c */
void eject_command(log_t *server, client_info_t *client, char **args);

/* connect_nbr.c */
void connect_nbr_command(log_t *server, client_info_t *client, char **args);

/* fork.c */
void fork_command(log_t *server, client_info_t *client, char **args);

/* debug */
void debug_command(log_t *server, client_info_t *client, char **args);

/* smg.c */
void smg(int graph, char *msg);

/* broadcast */
// int get_dir(client_info_t *rcvr, int sdr_x, int sdr_y, map_t *map);
int get_dir(client_info_t *receiver, client_info_t *sender, map_t *map);

/* ppa.c */
void ppa_command(log_t *server, client_info_t *client, char **args);

/* epa.c */
void epa_command(log_t *server, client_info_t *client, char **args);

#endif /* !COMMANDS_H_ */
