/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:08 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 22:10:36 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

char	*ft_ptoa(void *ptr)
{
	unsigned long long	p_addr;
	char				*str_addr;
	char				*hex_addr;

	p_addr = (unsigned long long) ptr;
	hex_addr = ft_hexstr(p_addr, 'l');
	str_addr = ft_strjoin("0x", hex_addr);
	free(hex_addr);
	return (str_addr);
}
