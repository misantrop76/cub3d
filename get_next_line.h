/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 17:29:45 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 18:47:27 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **line);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strndup(char *s, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
char	*ft_strdel(char *str);

#endif
