/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:09:47 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/04/24 14:12:18 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *str) //why can't we just use free()? -causing sigmentation fault
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_free2(void *str)
{
	if (*(void **)str != NULL)
		free(*(void **)str);
	*(void **)str = NULL;
}

void	ft_free_array(char **array)
{
	size_t	i;
	size_t	lst_s;

	if (!array)
		return ;
	lst_s = 0;
	while (array[lst_s])
		lst_s++;
	i = 0;
	while (i < lst_s)
	{
		ft_free(array[i]);
		i++;	
	}
	ft_free(array);
}

void	free_token(void *content)
{
	t_token	*token;

	token = NULL;
	if (content != NULL)
	{
		token = (t_token *) content;
		if(token->substr != NULL)
			ft_free(token->substr);
		if (token->sub_tokens != NULL)
			ft_lstclear(&token->sub_tokens, free_token);
		ft_free(token);
	}
}

