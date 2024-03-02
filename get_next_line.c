/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjulfend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:21:34 by jjulfend          #+#    #+#             */
/*   Updated: 2024/03/02 11:21:39 by jjulfend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif
void print(char a)
{
    write(1, &a, 1);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	length_before_line(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

size_t	length_after_line(const char *str)
{
	int	i;

	i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    while (str[i] != '\0')
        i++;

	return (i);
}

char *strcpy_beforeline(char *dest, const char *src)
{
	int	i;

	i = 0;
		while (src[i] != '\n' && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
        dest[i] = src[i];
        i++;
		dest[i] = '\0';
	return (dest);
}

char *strcpy_afterline(char *dest, const char *src)
{
	int	i;
    int j;

	i = 0;
    j = 0;
		while (src[i] != '\n' && src[i] != '\0')
			i++;
        i++;
		while (src[i] != '\0')
		{
			dest[j] = src[i];
			i++;
            j++;
		}
		dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

int findnewline(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    if (str[i] == '\n')
        return (1);
    else
        return (0);
}

// char *get_before_line(char *value)
// {
//     char    *before_line;
//     int i;
//     printf("before line: %zu\n", length_before_line(value));
//     before_line = (char *) malloc(length_before_line(value));

//     while (value[i] != '\0')
//     {
//         if (value[i] == '\n')
//             break;
//         else
//             before_line[i] = value[i];
//             printf("before_line: %s\n", before_line);
//             i++;
//     }
    
//     return (before_line);
// }

char *get_next_line(int fd)
{
    char    *str;
    int i;
    char *value;
    char *before_line;
    static char *after_line;
    int bytesread;

    i = 0;
    if (after_line)
        value = after_line;
    else
        value = (char *) malloc(0);
    str = (char *) malloc(BUFFER_SIZE+1);
    
    bytesread = read(fd, str, BUFFER_SIZE);
    value = ft_strjoin(value, str);
    str[BUFFER_SIZE] = '\0';
    while (!findnewline(value) && bytesread != 0)
    {
        read(fd, str, BUFFER_SIZE);
        value = ft_strjoin(value, str);
    }
    
    // while (value[i] != '\0')
    //     {
    //         print(value[i]);
    //         i++;
    //     }
    i = 0;
    before_line = (char *) malloc(length_before_line(value) + 1);
    before_line = strcpy_beforeline(before_line, value);
    while (before_line[i] != '\0')
    {
        print(before_line[i]);
        i++;
    }
    i=0;
    after_line = (char *) malloc(length_after_line(value));
    after_line = strcpy_afterline(after_line, value);
    // while (after_line[i] != '\0')
    // {
    //     print(after_line[i]);
    //     i++;
    // }
    if (*before_line == '\0')
        return (NULL);
    return (before_line);
}

int main (void)
{
    int fd;

    fd = open("text", O_RDONLY);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    // printf("%d", BUFFER_SIZE);
}