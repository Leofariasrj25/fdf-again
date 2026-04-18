/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIBFT_H
# define TEST_LIBFT_H

# include <stdlib.h>

void	ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);

#endif