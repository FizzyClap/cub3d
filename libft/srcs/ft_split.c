/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:31:52 by roespici          #+#    #+#             */
/*   Updated: 2024/11/13 06:58:05 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	len_word(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	countstrings(char *s, char c)
{
	size_t	i;
	size_t	strings;

	if (!s)
		return (0);
	i = 0;
	strings = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			strings++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (strings);
}

char	**ft_split(char *s, char c)
{
	size_t		i;
	int			j;
	char		**splits;
	int			length;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	splits = ft_calloc(sizeof(char *), (countstrings(s, c) + 1));
	if (!splits)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			length = len_word(s + i, c);
			splits[++j] = ft_substr(s, i, length);
			i += length;
		}
	}
	return (splits);
}
