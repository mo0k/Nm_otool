/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 14:34:38 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 22:35:00 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <libft.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct load_command			t_lc;
typedef struct mach_header_64		t_header64;
typedef struct segment_command_64	t_seg64;
typedef struct section_64			t_sect64;
typedef struct mach_header			t_header32;
typedef struct segment_command		t_seg32;
typedef struct section				t_sect32;

typedef struct 			s_meta
{
	uint32_t				options;
	void					*sect_text;
	void					*sect_data;
	uint8_t					swap;
	char					*filename;
	void					*ptr;
	size_t					size;
}							t_meta;

t_meta			*g_meta;

#endif