/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:39 by szubair           #+#    #+#             */
/*   Updated: 2023/04/25 13:53:01 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	heredoc_ctrl_c(t_shell *shell, char *line)
{
	if (g_dupstdin == -1)
	{
		shell->last_exit_code = 1;
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		ft_lstclear(&shell->heredoc_contents, free);
		rl_on_new_line();
		ft_free2(&line);
		ft_close(&g_dupstdin);
		return (false);
	}
	return (true);
}

void	handle_ctrl_c(t_shell *shell)
{
	if (g_dupstdin == -1)
	{
		g_dupstdin = dup(0);
		shell->last_exit_code = 1;
	}
}

void free_all(t_shell *shell)
{
	while (shell->step->next)
	{
		t_exec *tmp = shell->step->content;
		ft_free_array(tmp->cmd->arg_arr);
		ft_free(tmp->cmd);
		ft_free(shell->step->content);
		ft_free(shell->step->next);
		ft_free(shell->step);
		ft_free(shell);
		shell->step = shell->step->next;
	}
}
void	free_exec_step_ctrl_d(void *exec_step_ptr)
{
	t_exec	*exec_step;
	
	exec_step = exec_step_ptr;
	printf("Hello I am inside free_exec_step cntr_d\n");
	
	if (exec_step != NULL)
	{
		//ft_free(exec_step->cmd->arg_arr[0]);
		ft_free_array(exec_step->cmd->arg_arr);
		ft_free(exec_step->cmd);
		ft_free(exec_step);
	}
}
void	free_steps_cntrld(t_list **step_lists)
{
	t_list	*steps;
	t_list	*temp;
	
	printf("Hello cntrl_d\n");

	while ((*step_lists) != NULL)
	{
		printf("I am getting inside free stps cntrl_d\n");
		steps = (*step_lists)->content;
		temp = (*step_lists)->next;

		if (steps != NULL)
			ft_lstclear(&steps, free_exec_step_ctrl_d);
		
		ft_free2(step_lists);
		ft_free(steps);
		(*step_lists) = temp;
		ft_free(temp);
	}
	*step_lists = NULL;
}

void	handle_ctrl_d(const char *line, t_shell *shell)
{
	if (line == NULL)
	{
		int x;
		ft_free_array(shell->env);
		ft_free_array(shell->declared_env);
		ft_free_array(shell->args);
		ft_lstclear(&shell->tokens, free_token);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_close(&g_dupstdin);
		ft_free2(&shell->fd);
		ft_free(shell->line);
		x = shell->last_exit_code;
		free_steps_cntrld(&shell->step);
		
		clear_history();
		get_next_line(-1);

		printf("Is it here I exit (8)\n");

		ft_free(shell);
		exit(x);
	}
}
