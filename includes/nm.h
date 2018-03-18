/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:39:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 18:08:25 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>

# include <sort.h>
# include <print.h>
# include <get_opts.h>
# include <handler.h>

# define DEBUG 1
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

#endif