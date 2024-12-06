/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:30:21 by roespici          #+#    #+#             */
/*   Updated: 2024/10/25 10:35:13 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(char *src, int n)
{
	int		i;
	int		src_len;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	src_len = ft_strlen(src);
	len = n;
	if (src_len < n)
		len = src_len;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i] && i < len)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
