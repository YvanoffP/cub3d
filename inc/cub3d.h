#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../mlx/mlx.h"
# include "../srcs/get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define WALL '1'

# define NORTH 90
# define SOUTH 270
# define EAST 0
# define WEST 180
# define WIN_W 1280
# define WIN_H 640
# define FOV 60.0
# define TILE 64
# define WALL_RES 64
# define RATIO TILE * ((WIN_W/2) / tan(deg_to_rad(FOV / 2)))

# define ESCAPE 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define Z 6
# define Q 12
# define S 1
# define D 0
# define W 13
# define A 2

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 10
# define STRUCTURENOTIFYMASK 10001

# define MS 10
# define ROTATION 5.0

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
	int			width;
	int			height;
}				t_img;


typedef struct s_rays
{
	double	ang;
	double	h_hit_x;
	double	v_hit_y;
	double	tan;
	double	hit_x;
	double	hit_y;
	double	step_x;
	double	step_y;
	double	text_x;
	double	text_y;
	double	dist;
	double	length;
}			t_rays;

typedef struct s_window
{
	void                    *mlx_win;
    struct s_img            img;
}           t_window;

typedef struct	s_keys
{
	int			movefor;
	int			moveback;
	int			moveleft;
	int			moveright;
	int			turnleft;
	int			turnright;
}				t_keys;

typedef struct s_texture_pack
{
	struct s_texture *no;
	struct s_texture *so;
	struct s_texture *ea;
	struct s_texture *we;
	struct s_texture *wall;
	struct s_texture *ceiling;
	struct s_texture *floor;
}			t_texture_pack;

typedef struct s_texture
{
	char	        *path;
    struct s_img    img;
	int		        R;
	int		        G;
	int		        B;
}			t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	next_x;
	double	next_y;
	double	height;
	double	vis;
}			t_player;

typedef struct s_parse
{
    int fd;
    int spawn;
    int wall_err;
    int path_err;
    int id_err;
    int rgb_err;
}           t_parse;

typedef struct s_game
{
	char					**map;
	int						column;
	int						flag_hori;
    void                    *mlx;
	int						map_pos_x;
	int						map_pos_y;
    int                     map_w;
    int                     map_h;
	int						start;
	int						end;
	double					h_res;
	double					v_res;
	int						color;
	t_texture_pack			*text;
    t_window         		*win;
    t_img            		*img;
    t_keys           		keys;
	t_player				p;
	t_rays					rays;
}			t_game;

//PARSING - parsing.c
int		parsing(char *path, t_game *game);
void	init_parse(t_parse *control);
int     error_message(char *msg, int ret);

//PARSING - collect_map.c
void	realloc_string(char **map, int row, int len);
char	**format_map(char **map);
char	**alloc_n_fill_array(char **tab);
int		init_collect(int *row, char ***tmp, char ***tab, char *line);
char	**collect_map(char *line, int fd);

//PARSING - file_format.c
int		check_file_format(char *str, char *str2, int start);
int		file_format(char *path, t_parse *control);
int     check_texture_format(t_game *game);

//PARSING - game_infos.c
int		check_all_datas(t_game *game);
int		first_wall_line(char *line);
int		collect_data(char *l, t_game *game);
int		game_infos(t_game *game, t_parse *control);

//PARSING - tools.c
int		is_w_space(char c);
void	skip_white_space(char *str, int *i);
void	vertical_skip_white_space(char **str, int *i, int x);
void	free_map(t_game *game, char **map);
void	dup_array(char **tab, char **tmp);

//PARSING - map_checker.c
int		control_axis_x(char **map, int y, int max_y);
int		control_axis_x(char **map, int x, int max_x);
void	get_max(char **map, int *max_y, int *max_x);
int     check_map(char **map, t_game *game, t_parse *control);

//PARSING - player.c
void	get_player_infos(t_game *game);
int		find_player_pos(char **map, t_game *game, t_parse *control);

//INIT - init.c
void	init_texture_pk_dir(t_game *game);
void	init_texture_pk_dir_next(t_game *game);
void	set_texture_pack(t_game *game);
void	init_game(t_game *game);

//MAIN - main.c
void	exit_n_display(char *str);
void	destroy_struct(t_game *game, char *str);

//VIDEO - video_init.c
void    load_tex(t_game *game);
void    load_tex_bis(t_game *game);
void    check_dim(t_game *game);
int     video_init(t_game *game);

//VIDEO - window_init.c
void	init_graphics(t_game *game);
void    window_init(t_game *game);

//MAIN - hooks.c
void    set_hooks(t_game *game);
int     pressed(int keycode, t_keys *keys);
int     released(int keycode, t_keys *keys);

//ENGINE - engine.c
void	create_image(t_game *game);
void	draw_background(t_game *game);
int     engine(t_game *game);

//ENGINE - raycasting.c
void	digital_differential_analyzer(t_game *game);
double	vertical_raycasting(t_game *game);
double	horizontal_raycasting(t_game *game);
void	raycasting(t_game *game);

//ENGINE - engine_tools.c
double	deg_to_rad(double value);
double	square(double value);
void	put_pixel(t_img *img, int x, int y, int color);
void	define_color(t_texture *color, t_texture *zone);
int     color_picker(unsigned char red, unsigned char green, unsigned char blue);

//ENGINE - motion.c
void	move_if_allowed(t_game *game);
void	player_rotation(t_game *game);
void	player_move(t_game *game);

//ENGINE - draw.c
void	draw_wall(t_game *game);
void	draw(t_game *game);

#endif
