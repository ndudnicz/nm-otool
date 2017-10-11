/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:56:12 by ndudnicz          #+#    #+#             */
/*   Updated: 2016/01/19 15:09:52 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char*)s);
	else if (!*s)
		return (NULL);
	else
		return (ft_strchr(s + 1, c));
}
