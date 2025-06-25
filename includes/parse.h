/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:15:11 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/23 09:25:27 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"
# define TEX_NB 7
# define TEX_PATHS 5

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	PANIC_ERR,
}	t_parse_status;

typedef enum e_texture
{
	N = 0,
	S = 1,
	E = 2,
	W = 3,
	D = 4,
}	t_texture;

typedef struct s_img
{
	void	*img;
    char	*pixel_data;
    int		pixel_bits;
    int		line_size;
	int		endian;
}	t_img;

typedef struct s_parsing
{
	char		*file; 				// 읽은 파일 명
	int			endline; 			// 맵 파싱 때 제대로 모든 요소들이 있는 지 확인용
	char		*line; 				// 맵 파싱 떼, 맵을 스플릿하기 위해 파일 내용 저장하는 라인
	char		*temp;
	char		**file_content; 	// 스플릿 이후 반환된 배열
	char		*buff;
	char		player_caracter; 	// 플래이어가 어디를 바라보는 지 저장하는 변수
	int			check_sky;
	int			check_land;
}		t_parsing;

typedef struct s_texdata
{
	void		*tex_img[TEX_PATHS];
	int			tex_h[TEX_PATHS];
	int			tex_w[TEX_PATHS];
	char		*tex_paths[TEX_PATHS];
	char		*tex_addr[TEX_PATHS];
	int			floor[3];
	int			sky[3];
	int			tex_nb;
}	t_texdata;

#endif