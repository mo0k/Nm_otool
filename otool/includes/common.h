/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 14:38:54 by mo0k             ###   ########.fr       */
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

void		corrupted(char *str);

#endif
