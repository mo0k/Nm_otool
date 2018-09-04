/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:51:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 21:26:49 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCH64_H
# define ARCH64_H

# include <mach-o/nlist.h>
# include <libft.h>
# include <ft_printf.h>
# include <data.h>
# include <nm.h>
# include <swap_bit.h>
# include <common.h>
# include <symbol.h>
# include <sort.h>

void		handler64(void *ptr, t_meta *meta);
void		handler_symtab64(void* lc, void *ptr, t_meta *meta);
char		*get_seg64_name(t_lc *lc, unsigned int index);
char		*get_symbol64(char *buf, struct nlist_64 *nlist, int colomn);

#endif
