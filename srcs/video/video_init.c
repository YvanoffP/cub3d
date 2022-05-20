/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:24:35 by tpauvret          #+#    #+#             */
/*   Updated: 2022/05/20 19:39:09 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_tex(t_game *game)
{
	game->text->no->img.img = mlx_xpm_file_to_image(game->mlx,
			game->text->no->path, &game->text->no->img.width,
			&game->text->no->img.height);
	if (!game->text->no->img.img)
		exit_n_display("Failed to allocate north texture.\n");
	free(game->text->no->path);
	game->text->no->img.addr = mlx_get_data_addr(game->text->no->img.img,
			&game->text->no->img.bpp,
			&game->text->no->img.linelen, &game->text->no->img.endian);
	game->text->so->img.img = mlx_xpm_file_to_image(game->mlx,
			game->text->so->path, &game->text->so->img.width,
			&game->text->so->img.height);
	if (!game->text->so->img.img)
		exit_n_display("Failed to allocate south texture.\n");
	free(game->text->so->path);
	game->text->so->img.addr = mlx_get_data_addr(game->text->so->img.img,
			&game->text->so->img.bpp,
			&game->text->so->img.linelen, &game->text->so->img.endian);
}

void	load_tex_bis(t_game *game)
{
	game->text->we->img.img = mlx_xpm_file_to_image(game->mlx,
			game->text->we->path, &game->text->we->img.width,
			&game->text->we->img.height);
	if (!game->text->we->img.img)
		exit_n_display("Failed to allocate west texture.\n");
	free(game->text->we->path);
	game->text->we->img.addr = mlx_get_data_addr(game->text->we->img.img,
			&game->text->we->img.bpp,
			&game->text->we->img.linelen, &game->text->we->img.endian);
	game->text->ea->img.img = mlx_xpm_file_to_image(game->mlx,
			game->text->ea->path, &game->text->ea->img.width,
			&game->text->ea->img.height);
	if (!game->text->ea->img.img)
		exit_n_display("Failed to allocate east texture.\n");
	free(game->text->ea->path);
	game->text->ea->img.addr = mlx_get_data_addr(game->text->ea->img.img,
			&game->text->ea->img.bpp,
			&game->text->ea->img.linelen, &game->text->ea->img.endian);
}

void	load_tex_next(t_game *game)
{
	game->text->exit->img.img = mlx_xpm_file_to_image(game->mlx,
			game->text->exit->path, &game->text->exit->img.width,
			&game->text->exit->img.height);
	if (!game->text->exit->img.img)
		exit_n_display("Failed to allocate west texture.\n");
	free(game->text->exit->path);
	game->text->exit->img.addr = mlx_get_data_addr(game->text->exit->img.img,
			&game->text->exit->img.bpp,
			&game->text->exit->img.linelen, &game->text->exit->img.endian);
}

void	check_dim(t_game *game)
{
	if (!(game->text->no->img.width == game->text->no->img.height
			&& game->text->no->img.height == game->text->so->img.width
			&& game->text->so->img.width == game->text->so->img.height
			&& game->text->so->img.height == game->text->ea->img.width
			&& game->text->ea->img.width == game->text->ea->img.height
			&& game->text->ea->img.height == game->text->we->img.width
			&& game->text->we->img.width == game->text->exit->img.height
			&& game->text->exit->img.width == game->text->exit->img.height))
		exit_n_display("The textures do not possess the same dimensions.\n");
}

int	video_init(t_game *game)
{
	load_tex(game);
	load_tex_bis(game);
	load_tex_next(game);
	check_dim(game);
	return (1);
}
