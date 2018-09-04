/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:36:16 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 21:21:21 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECT_H
# define SECT_H

# define SECT_COLMAX 0x3
# define SECT_ROWMAX 0x5
# define NOSECT_COLMAX 0x2
# define NOSECT_ROWMAX 0x5

typedef struct	s_info
{
	void *segname;
	void *sectname;
}				t_info;

enum			symbol_colomn_name
{
	SECTNAME,
	SYMBOL_CHAR,
	SEGNAME
};

enum			symbol_row_ref
{
	UNDEFINED,
	ABSOLUTE,
	INDIRECT
};

enum			symbol_row_ref_sect
{
	TEXT,
	DATA,
	BSS,
	COMMON
};

#endif
