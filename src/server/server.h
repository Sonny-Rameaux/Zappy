/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** ftp
*/

#ifndef FTP_H_
    #define FTP_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <fcntl.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <sys/queue.h>
    #include <sys/time.h>
    #include <signal.h>
    #include <fcntl.h>
    #include <time.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <uuid/uuid.h>
    #include <stdbool.h>
    #include <pthread.h>
    #include <math.h>
    #include <errno.h>

    #define MAX_CLIENTS 444
    #define BUFFER_SIZE 1024
    #define LOWER 1024
    #define UPPER 65536
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define UUID_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define ONE_SEC_IN_USEC (double)1000000
    #define SELECT_TO_USEC (double)(ONE_SEC_IN_USEC / (double)4)
    #define PI 3.1415926535897932

    #define PRSTR "clientsNB: %d, freq: %d, height: %d, width: %d, port: %d\n"
    #define DP_PARSE(n, f, h, w, p) printf(PRSTR, n, f, h, w, p)

    #define NCOSTR "New connection, fd: %d, ip: %s, port: %d\n"
    #define DP_NCO(fd, ip, p) printf(NCOSTR, fd, ip, p)

static volatile sig_atomic_t should_exit = 0;

typedef struct {
    char *buffer;
    char **tokens;
    int token_count;
    int token_start;
    int in_quotes;
} token_t;

enum Orientation {
    N = 1,
    E,
    S,
    W
};

typedef struct command_queue_s {
    char *data;
    struct command_queue_s *next;
} cmd_queue_t;

typedef struct client_info {
    struct sockaddr_in address;
    int sd;
    int logged_in;
    cmd_queue_t *cmd_queue;
    time_t last_command_time;
    double command_delay;
    char *team_name;
    int pos_x;
    int pos_y;
    int level;
    int is_graphic;
    double delay;
    enum Orientation orient;
    struct inv_s *inventory;
    time_t life_timer;
    double life_delay;
} client_info_t;

typedef struct parse_s {
    int port;
    int width;
    int height;
    int clientsNb;
    int freq;
    int egg_n;
    struct team_s **teams;
} par_t;

/* MAP */
typedef struct {
    struct inv_s *inventory;
} tile_t;

typedef struct {
    int width;
    int height;
    tile_t **tiles;
} map_t;

typedef struct login_s {
    int max_sd;
    fd_set readfds;
    client_info_t clients[MAX_CLIENTS];
    par_t *parsed;
    map_t *gui_map;
    int client_nbs;
    int graphic_connected;
    time_t refill_delay;
    struct incant_prereq_s *incant_data;
} log_t;

typedef struct command {
    const char *name;
    void (*func)(log_t *server, client_info_t *client, char **args);
} command_t;

/* my_utils */
int my_strlen(char const *str);
void my_putchar(char c);
void my_putstr(char const *str);
void my_putstr_fd(char const *str, int fd);
void my_putnbr_base(int nb, char const *base);

/* arr_func */
void my_show_word_array(char **arr, char *delim);
void free_arr(char **arr);
int size_arr(char **arr);

/* str_to_word_array */
char **str_to_word_array(char *str);
char **str_to_word_array_delim(char *str, char delimiter);

/* handle_command */
void handle_commands(char *buffer, log_t *logins, int i);
void parse_line(const char *line, char *username, char *uuid);

/* assign_team */
void assign_team(char *command, log_t *server, int i);

/* read_file */
char *read_file(char *filepath);
char *realloc_if_needed(char *string, size_t *allocated,
    size_t total, size_t *increase);

/* handle_client */
void handle_client_data(log_t *logins);

/* server */
void free_server(par_t *parsing);
void add_client_socket(
    int clientSocket,
    log_t *logins,
    struct sockaddr_in *clientSa
);
int has_all_digits(char *str);

/* bind_and_listen */
int bind_socket(int s, par_t *parsing);
int start_listening(int s);

/* handle_connexion */
void handle_connections(int s, par_t *parsing);

void select_client(log_t *logins, int s);

void read_client(log_t *logins, int i);

/* index */
int get_command_index(char *buffer);

/* quit */
void quit_command(log_t *logins, client_info_t *client, char **args);

/* file */
void transfer_file(FILE *file, int data_socket, int client_sd);
FILE *open_file(char *file_path);

/* accept_connect */
int accept_connec(int data_socket, int client_sd);
int connect_connec(int data_socket, struct sockaddr_in* client_addr);

/* msg */
void remove_char(char *str, char c);

/* login */
int is_whitespace(char c);
int get_uuid_from_username(const char *username, char *uuid_str);

/* tokenize */
char **tokenize(char *buffer, int *count);
void free_tokenize(char **arr, int count);
void add_null_terminator(char ***args, int *count);


/* verify_quoted */
int verify_quoted_args(char *buffer);

/* print_sd_info */
void print_clients_sd(log_t *log);

/* set_socket */
fd_set set_client_socket(log_t *logins, int i);

/* trim_input */
void trim_newline(char *str);
void remove_surrounding_quotes(char *str);

/* is_whitespace */
int is_whitespace(char c);

/* quotes */
char *delete_quotes(char *str);

/* array_to_string */
char *array_to_string(char **words, size_t num_words);
char *count_str(char **args);

/* help */
void help_cmd(log_t *logins, client_info_t *client, char **args);

/* messages */
void retrieve_messages(const char *sender_uuid,
    const char *receiver_uuid, client_info_t *client);
void store_message(const char *sender_uuid, const char *receiver_uuid,
    const char *message, time_t timestamp);

/* create */
void cmd_create(log_t *server, client_info_t *instance, char **args);

/* process_arguments */
void parse_arguments(int argc, char **argv, par_t *par);

/* map */
map_t *create_map(int width, int height);
void free_map(map_t *map);
tile_t *get_tile(map_t *map, int x, int y);
void shift_items(char *start_pos, size_t shift_length);

/* num */
bool is_digit(char c);
bool is_num(char *str);

/* queue */
char *pop_front(cmd_queue_t **headRef);
void free_list(cmd_queue_t *head);
void print_list(cmd_queue_t *head);
void append(cmd_queue_t **headRef, char *data);
cmd_queue_t *create_node(char *data);

/* fill_map */
void fill_map_with_resources(map_t *map);

/* broadcast */
void broadcast_command(log_t *server, client_info_t *sender, char **args);

/* copy_map */
map_t *copy_map(map_t *original);

/* parse_cmd */
char **parse_cmd(char *cmd, char *sep);

    #include "inventory/inventory.h"
    #include "commands/commands.h"
    #include "teams/teams.h"
    #include "incantation/incantation.h"

/* random.c */
int gen_randint(int max);

/* conds.c */
void check_players_win(log_t *logins);
void check_players_death(log_t *logins);

#endif /* !FTP_H_ */
