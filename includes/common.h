/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 20:42:51 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <stdlib.h>
# include <data.h>
#include 	<string.h>

typedef struct dylib	t_dylib; 

char 		*get_dylibname(t_lc *lc, unsigned int index);
char 		*get_infos_external32(struct nlist *nlist, char *buf);
char 		*get_infos_external64(struct nlist_64 *nlist, char *buf);
char 		*get_seg64_name(t_lc *lc, unsigned int index);
char 		*get_seg32_name(t_lc *lc, unsigned int index);
char 		*get_type_stab(uint8_t ntype);
uint32_t	swap_bit(uint32_t value);

#endif
