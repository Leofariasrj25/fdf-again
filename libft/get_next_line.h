/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:28:47 by lfarias-          #+#    #+#             */
/*   Updated: 2022/06/02 16:41:54 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# define LF '\n'
# define EOS '\0'
# define MAX_FD	4096

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_str_buffer
{
	char				*content;
	size_t				start;
	size_t				len;
	size_t				lf_count;
	struct s_str_buffer	*next;
}	t_str_buff;

char		*get_next_line(int fd);
t_str_buff	*create_node(void *content, size_t size, size_t lf_count);
void		add_node(t_str_buff **str_bf, t_str_buff *node);
t_str_buff	*next_node(t_str_buff *node);
int			get_strlen(t_str_buff **str_bf);
size_t		count_lf(char *read_bf, size_t bytes_read);
int			check_list(t_str_buff **list);
#endif
