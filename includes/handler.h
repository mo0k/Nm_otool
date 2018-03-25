/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:43:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 22:11:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# include <mach-o/fat.h>
# include <libft.h>
# include <ft_printf.h>
# include <sort.h>
# include <data.h>
# include <common.h>
# include <nm.h>

# define SWAP(f, v) ((f) ? swap_bit(v) : v)

# ifndef DEBUG
#  define DEBUG 1
# endif

void		handler64(void *ptr, t_meta *meta);
void		handler32(void *ptr, t_meta *meta);
void		handler_systab64(void* lc, void *ptr, t_meta *meta);
void		handler_systab32(void* lc, void *ptr, t_meta *meta);
void		handler_fat32(void *ptr, t_meta *meta);


#endif