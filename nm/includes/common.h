/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:02:32 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 23:37:09 by mo0k             ###   ########.fr       */
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
# include <symbol.h>
# include <sort.h>
#include  <string.h>

# define BEG(x) (x->ptr)
# define END(x) (x->ptr + x->size)
# define CHK_VAL(file, cur) ((cur < BEG(file) || cur >= END(file)))

typedef struct dylib	t_dylib; 

char 		*get_dylibname(t_lc *lc, unsigned int index);
char 		*get_infos_external32(struct nlist *nlist, char *buf);
char 		*get_infos_external64(struct nlist_64 *nlist, char *buf);
char 		*get_seg64_name(t_lc *lc, unsigned int index);
char 		*get_seg32_name(t_lc *lc, unsigned int index);
char 		*get_type_stab(uint8_t ntype);
char		*get_symbol_sect_nofound(char *buf, t_info *info,
												int colomn, int is_external);
void		get_ptr_lc(t_meta *meta, t_lc *lc, enum e_archtype archtype, uint8_t *flag);
void		sort_display_clean(t_list **list, t_meta *meta);
void		del(void *elem, size_t size);
char 		*get_ref(int row, int column);
void		corrupted();

#endif
