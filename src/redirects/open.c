/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:32:13 by jmeruma           #+#    #+#             */
/*   Updated: 2023/09/21 12:32:14 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	open_here_doc(char *end_of_file, char **path)
{
	int		fd;
	char	*hex;

	hex = ft_basetoa("0123456789abcdef", 16, (unsigned long)end_of_file);
	if (!hex)
		return (-1);
	*path = ft_strjoin("/tmp/here_doc", hex);
	if (*path == NULL)
		return (free(hex), -1);
	free(hex);
	fd = open(*path, O_RDONLY | O_CREAT | O_WRONLY, 0644);
	return (fd);
}

int	open_out_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	open_append_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	open_in_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	return (fd);
}
