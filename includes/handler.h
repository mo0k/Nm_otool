/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:43:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 18:04:42 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# include <libft.h>
# include <ft_printf.h>
# include <sort.h>
# include <data.h>

# ifndef DEBUG
#  define DEBUG 1
# endif

void		handler64(void *ptr, t_meta *meta);
void		handler_systab(void* lc, void *ptr, t_meta *meta);


#endif