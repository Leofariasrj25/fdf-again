/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:02:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 21:23:12 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "../libft.h"

static char	*ft_ctostr(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*get_conv_value(char fmt_chr, va_list lst)
{
	char	*value;

	value = NULL;
	if (fmt_chr == 'c')
		value = ft_ctostr(va_arg(lst, int));
	else if (fmt_chr == 's')
	{
		value = va_arg(lst, char *);
		if (!value)
			return (ft_strdup("(null)"));
		value = ft_strdup(value);
	}
	else if (fmt_chr == 'd' || fmt_chr == 'i')
		value = ft_itoa(va_arg(lst, int));
	else if (fmt_chr == 'u')
		value = ft_utoa(va_arg(lst, unsigned int));
	else if (fmt_chr == 'x')
		value = ft_hexstr(va_arg(lst, unsigned int), 'l');
	else if (fmt_chr == 'X')
		value = ft_hexstr(va_arg(lst, unsigned int), 'u');
	else if (fmt_chr == '%')
		value = ft_ctostr('%');
	else if (fmt_chr == 'p')
		value = ft_ptoa(va_arg(lst, void *));
	return (value);
}

static void	print_value(char *fvalue, char fmt_chr, int *size)
{
	if (fvalue[0] == '\0' && fmt_chr == 'c')
	{
		ft_putchar_fd(fvalue[0], 1);
		*size += 1;
	}
	else
	{
		ft_putstr_fd(fvalue, 1);
		*size = *size + ft_strlen(fvalue);
	}
	free(fvalue);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		args_lst;
	char		*fvalue;
	int			size;

	i = -1;
	size = 0;
	va_start(args_lst, str);
	while (str[++i] != '\0')
	{
		fvalue = NULL;
		if (str[i] == '%')
		{
			i++;
			fvalue = get_conv_value(str[i], args_lst);
			print_value(fvalue, str[i], &size);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			size++;
		}
	}
	va_end(args_lst);
	return (size);
}
