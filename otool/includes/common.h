/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 22:55:51 by mo0k             ###   ########.fr       */
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

# define BEG(x) (x->ptr)
# define END(x) (x->ptr + x->size)
# define CHK_VAL(file, cur) ((cur < BEG(file) || cur >= END(file)))

void		corrupted(char *str);

#endif
