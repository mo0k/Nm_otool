/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:39:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 21:27:21 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/fat.h>

# include <libft.h>
# include <open_file.h>
# include <sort.h>
# include <print.h>
# include <get_opts.h>
# include <arch32.h>
# include <arch64.h>

# define ERROR_STR "./nm :"
# define NBR_ARCH 5

void 	nm(void *ptr, t_meta *meta);

#endif
