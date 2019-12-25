/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 02:31:16 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/21 01:00:15 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!(str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
		str[j++] = s1[i++];
	j = 0;
	while ( s2 && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (c == s[i])
		return (s + i);
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (ft_strdel(s1));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
