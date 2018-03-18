/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 14:34:38 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 18:03:15 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <libft.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

enum e_return
{
	ERROR_ARGS,
	ERROR_OPEN,
	ERROR_FSTAT,
	ERROR_MMAP
};

typedef t_list			*(*t_sfunc)(t_list*, t_list*);
typedef void		(*t_pfunc)(t_list*);

char					*g_stringtab;

typedef struct mach_header_64		t_header64;
typedef struct load_command			t_lc;
typedef struct segment_command_64	t_seg64;
typedef struct section_64			t_sect64;

typedef struct 			s_meta
{
	char 					buf[80];
	uint32_t				options;
	t_sfunc					sortfunc;
	t_pfunc					printfunc;
	t_lc					*seg64;
	t_lc					*seg;
	t_lc					*dylib;
	t_lc					*symtab;
	void					*ptr;
	size_t					ptr_size;
}							t_meta;

t_meta			g_meta;

#endif