/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_none.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 21:56:57 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

char *get_type_stab(uint8_t ntype)
{
	int				i;
	static int		tab_i[] = {0X20, 0x22, 0x24, 0x26, 0x28, 0x2e, 0x32, 0x3c,
	0x40, 0x44, 0x4e, 0x60, 0x64, 0x66, 0x80, 0x82,
	0x84, 0x86, 0x88, 0x8A, 0xa0, 0xa2, 0xa4, 0xc0,
	0xc2, 0xe0, 0xe2, 0xe4, 0xe8, 0xfe};
	static char		*tab_s[] = {"GSYM", "FNAME", "FUN", "STSYM", "LCSYM",
								"BNSYM", "AST", "OPT", "RSYM", "SLINE",
								"ENSYM", "SSYM", "SO", "OSO", "LSYM",
								"BINCL", "SOL", "PARAMS", "VERSION", "OLEVEL",
								"PSYM", "EINCL", "ENTRY", "LBRAC", "EXCL",
								"RBRAC", "BCOMM", "ECOMM", "ECOML", "LENG"};

	i = -0x1;
	while (++i < 30)
		if (ntype == tab_i[i])
			return (tab_s[i]);
	return (NULL);
}
void						print_option_none(t_list *list)
{
	struct nlist_64*			elem;
	char 						buf[85];

	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_A))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	if (elem->n_value)
		printf("%016llx ", elem->n_value);
	else
		printf("%16s ", "");
	if (elem->n_type & N_STAB)
		printf("%s %02x %04x %5s %s\n", get_symbol64(buf, elem, CHAR)
			 			, 	elem->n_sect
						,	elem->n_desc
						, get_type_stab(elem->n_type)
						, g_stringtab + elem->n_un.n_strx);
	else
		printf("%s %s\n", get_symbol64(buf, elem, CHAR)
					, g_stringtab + elem->n_un.n_strx);
}