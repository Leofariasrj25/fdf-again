/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:39:04 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/17 16:06:40 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char *str, char sep)
{
	int		word_count;
	int		w_found;

	word_count = 0;
	w_found = 0;
	while (*str != '\0')
	{
		if (*str != sep && !w_found)
		{
			word_count++;
			w_found = 1;
		}
		else if (*str == sep)
			w_found = 0;
		str++;
	}
	return (word_count);
}

static int	word_size(char *str, char sep)
{
	int	word_size;

	word_size = 0;
	while (*str != '\0')
	{
		if (*str != sep)
		{
			word_size++;
			str++;
		}
		else
			break ;
	}
	return (word_size);
}

static char	**clean_split(char **strs)
{
	int	i;

	i = -1;
	while (strs[i++])
		free(strs[i]);
	free(strs);
	return (NULL);
}

static char	*create_word(char **words, char *str, int str_size)
{
	char	**aux_words;
	char	*word;

	aux_words = words;
	while (*aux_words)
		aux_words++;
	word = ft_calloc(str_size + 1, sizeof(char));
	if (!word)
	{
		return (NULL);
	}
	ft_strlcpy(word, str, str_size + 1);
	*aux_words = word;
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	size_t	i;
	size_t	word_s;

	if (!str)
		return (NULL);
	strs = ft_calloc(word_counter((char *) str, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	word_s = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word_s = word_size((char *) &str[i], c);
			if (!create_word(strs, (char *) &str[i], (int) word_s))
				clean_split(strs);
			i += word_s;
		}
		else
			i++;
	}
	return (strs);
}
/*int main(void)
{
	char **strs = ft_split("Oi-Meu-Nome-E-Leo", '-');
		for (int i = 0; i < 5; i++) {
			if (strs[i] != NULL)
				printf("%s\n", strs[i]);
			else
				printf("null\n");
		}
}*/
