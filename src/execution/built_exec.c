/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 16:18:34 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/26 16:40:03 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

// bool	blt_dup_redirects(t_command *cmd, t_infos *infos)
// {
// 	int	priority;
// 	int	check_read;
// 	int	check_write;

// 	check_read = NO_FILE;
// 	check_write = NO_FILE;
// 	priority = check_read_priority(cmd);
// 	if (priority != 0)
// 	{
// 		if (!start_heredoc(cmd, infos, &check_read, priority))
// 			return (false);
// 		if (!start_read(cmd, infos, &check_read, priority))
// 			return (false);
// 	}
// 	if (!start_write(cmd, infos, &check_write))
// 		return (false);
// 	close(infos->read_fd);
// 	return (true);
// }