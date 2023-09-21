/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:32:08 by jmeruma           #+#    #+#             */
/*   Updated: 2023/09/21 12:32:09 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define INVALID -1

int	here_doc(char *end_of_file, t_infos *infos)
{
	int		fd;
	char	*path;
	char	*line;

	fd = open_here_doc(end_of_file, &path);
	if (fd == INVALID)
		return (INVALID);
	line = readline("Badeline>");
	while (line)
	{
		if (!ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1))
		{
			free(line);
			break ;
		}
		if (!find_env_var(line))
			line = search_env_var(line, infos, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("Badeline>");
	}
	return (here_doc_unlink_and_close(path, fd));
}
