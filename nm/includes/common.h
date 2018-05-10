/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 12:04:17 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <stdlib.h>
# include <data.h>
# include <ft_printf.h>
# include <swap_bit.h>
#include  <string.h>

# define CHK_VAL(beg, end, cur) ((cur < beg || cur >= end))

typedef struct dylib	t_dylib; 

char 		*get_dylibname(t_lc *lc, unsigned int index);
char 		*get_infos_external32(struct nlist *nlist, char *buf);
char 		*get_infos_external64(struct nlist_64 *nlist, char *buf);
char 		*get_seg64_name(t_lc *lc, unsigned int index);
char 		*get_seg32_name(t_lc *lc, unsigned int index);
char 		*get_type_stab(uint8_t ntype);
void		corrupted(char *str);
#endif
