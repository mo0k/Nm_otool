/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 14:34:38 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:42:30 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

enum e_return
{
	SUCCESS = 0,
	ERROR_ARGS,
	ERROR_OPEN,
	ERROR_FSTAT,
	ERROR_MMAP
};

char					*g_stringtab;

typedef struct			s_opts
{
	uint8_t				reverse;
	uint8_t				ascii;
	uint8_t				nosort;
	uint8_t				hexa;
	uint8_t				just_symbol_names;
}						t_opts;

typedef void			(*t_pfunc)(t_list*);
typedef t_list			*(*t_sfunc)(t_list*, t_list*);

typedef struct				s_meta
{
	t_opts					options;
	t_sfunc					sortfunc;
	t_pfunc					printfunc;
	void					*ptr;
	size_t					ptr_size;
}							t_meta;

#endif