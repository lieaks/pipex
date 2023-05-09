/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:52:35 by dly               #+#    #+#             */
/*   Updated: 2023/01/10 14:11:48 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_three(char *str1, char *str2, char *str3)
{
	char	*res;
	size_t	i;
	size_t	len;

	if (!str1 || !str2 || !str3)
		return (NULL);
	i = 0;
	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*str1)
		res[i++] = *str1++;
	while (*str2)
		res[i++] = *str2++;
	while (*str3)
		res[i++] = *str3++;
	return (res);
}
