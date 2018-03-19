/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 14:58:44 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <stdlib.h>
# include <data.h>
#include <string.h>

typedef struct dylib	t_dylib; 

char 		*get_dylibname(t_lc *lc, unsigned int index);
char 		*get_infos_external(struct nlist_64 *nlist, char *buf);
char 		*get_seg64_name(t_lc *lc, unsigned int index);

#endif
