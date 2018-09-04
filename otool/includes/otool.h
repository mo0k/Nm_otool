/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:39:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 22:33:37 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/fat.h>
# include <open_file.h>
# include <get_opts.h>
# include <ft_printf.h>
# include "data.h"
# include "arch32.h"
# include "arch64.h"

//void 			*g_symtab;

// undefined		u \
// absolute 		a  \
// text				t   \
// data				d    \ UPPER if n_type & N_EXT
// bss				b    /
// commun			c   /
//					S  /
// indirect			i /

# define ERROR_STR "./otool :"

void 	otool(void *ptr, t_meta *meta);

#endif
