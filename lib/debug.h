/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:11:03 by mo0k              #+#    #+#             */
/*   Updated: 2018/08/11 00:05:24 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <fcntl.h>
# include <ft_printf.h>

# define DEBUG 0

int g_fd;
//ajouter global flag_open

# define OPEN_DEBUG() (g_fd = open("/tmp/DEBUG", O_WRONLY | O_APPEND | O_CREAT, 0600)) // a modifer
# define CLOSE_DEBUG() (close(g_fd))
# define P_DEBUG(fmt) (DEBUG ? ft_dprintf(g_fd, fmt) : 0)
# define P_DEBUG_VARGS(fmt, ...) (DEBUG ? ft_dprintf(g_fd, fmt, __VA_ARGS__): 0)
# define P_DEBUG_FILE(fmt) ((DEBUG && OPEN_DEBUG() > 0) ? ft_dprintf(g_fd, fmt) && CLOSE_DEBUG() : 0)
# define P_DEBUG_FILE_VARGS(fmt, ...) \
				((DEBUG && OPEN_DEBUG() > 0) ? ft_dprintf(g_fd, fmt, __VA_ARGS__) && CLOSE_DEBUG() : 0)

#endif