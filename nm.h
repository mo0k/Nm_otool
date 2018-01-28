/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:39:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:37:34 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <libft.h>
# include "data.h"
# include "options.h"
# include "sort.h"

# define OPTIONS "prxj"
# define ERROR_STR "./nm :"

#endif