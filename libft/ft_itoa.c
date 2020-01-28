/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 11:31:24 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/01 18:00:27 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[j] != '\0')
		j++;
	j--;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		j--;
		i++;
	}
	return (str);
}

static int	size(long int nbr)
{
	int j;

	j = 0;
	if (nbr == 0)
		j++;
	while (nbr > 0)
	{
		nbr /= 10;
		j++;
	}
	return (j);
}

static char	*mkchr(char *str, long int nbr, int signe)
{
	int i;

	i = 0;
	if (nbr == 0)
		str[i++] = 48;
	while (nbr > 0)
	{
		str[i] = (nbr % 10) + 48;
		nbr /= 10;
		i++;
	}
	if (signe > 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

char		*ft_itoa(int c)
{
	char		*str;
	int			signe;
	long int	nbr;

	nbr = c;
	signe = 0;
	if (nbr < 0)
	{
		signe++;
		nbr *= -1;
	}
	if (!(str = malloc(sizeof(char) * (size(nbr) + 1 + signe))))
		return (0);
	return (mkchr(str, nbr, signe));
}
