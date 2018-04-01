/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:39:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/31 15:14:36 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <mach-o/fat.h>


# include <sort.h>
# include <print.h>
# include <get_opts.h>
# include <arch32.h>
# include <arch64.h>
# include <debug.h>

//void 			*g_symtab;

// undefined		u \
// absolute 		a  \
// text				t   \
// data				d    \ UPPER if n_type & N_EXT
// bss				b    /
// commun			c   /
//					S  /
// indirect			i /

# define ERROR_STR "./nm :"

void 						nm(void *ptr, t_meta *meta);


#endif