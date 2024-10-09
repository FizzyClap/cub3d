/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:27:51 by roespici          #+#    #+#             */
/*   Updated: 2024/10/09 16:23:02 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strisnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			break ;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
