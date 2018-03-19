/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:36:16 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 08:58:49 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECT_H
# define SECT_H

# define SYMBOL_REF_COLMAX 0x2
# define SYMBOL_REF_SECT_ROWMAX 0x4
# define SYMBOL_REF_OTHER_ROWMAX 0x3

# include <mach-o/nlist.h>
# include <libft.h>
# include <ft_printf.h>
# include <data.h>

enum 		symbol_colomn_name
{
	STRING,
	CHAR
};

enum 		symbol_row_ref
{
	UNDEFINED,
	ABSOLUTE,
	INDIRECT
};

enum 		symbol_row_ref_sect
{
	TEXT,
	DATA,
	BSS,
	COMMON
};

char 		*get_symbol64(char *buf, struct nlist_64 *nlist, int colomn);

#endif