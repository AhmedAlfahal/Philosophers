/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:21:34 by aalfahal          #+#    #+#             */
/*   Updated: 2023/03/26 06:04:50 by aalfahal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grep_fork(t_m *p, int left, int right)
{
	p->fork->forks[left] = 0;
	p->right_fork = 1;
	p->fork->forks[right] = 0;
	p->left_fork = 1;
	printing(p, 5);
}

void	put_fork(t_m *p)
{
	pthread_mutex_lock(&p->fork->fork_lock);
	if (p->id == p->fork->p_num && p->right_fork == 1 \
	&& p->left_fork == 1)
	{
		p->fork->forks[0] = p->id;
		p->fork->forks[p->id - 1] = p->id;
		p->right_fork = 0;
		p->left_fork = 0;
	}
	else if (p->right_fork == 1 && p->left_fork == 1)
	{
		p->fork->forks[p->id - 1] = p->id;
		p->fork->forks[p->id] = p->id;
		p->right_fork = 0;
		p->left_fork = 0;
	}
	pthread_mutex_unlock(&p->fork->fork_lock);
}

void	take_forks(t_m *p)
{
	pthread_mutex_lock(&p->fork->fork_lock);
	if (p->id == p->fork->p_num && p->fork->forks[0] != p->id \
	&& p->fork->forks[p->id - 1] != p->id && p->fork->forks[0] != 0 \
	&& p->fork->forks[p->id - 1] != 0)
		grep_fork(p, p->id - 1, 0);
	else if (p->id == p->fork->p_num && p->eaten_meals == 0 \
	&& p->fork->forks[p->id - 1] != 0 && p->fork->forks[0] != 0 \
	&& p->fork->p_num > 1)
		grep_fork(p, p->id - 1, 0);
	else if (p->id >= 1 && p->fork->forks[p->id - 1] != 0 \
	&& p->fork->forks[p->id] != 0 \
	&& p->fork->forks[p->id - 1] != p->id \
	&& p->fork->forks[p->id] != p->id)
		grep_fork(p, p->id - 1, p->id);
	else if (p->id >= 1 && p->eaten_meals == 0 \
	&& p->fork->forks[p->id - 1] != 0 && p->fork->forks[p->id] != 0)
		grep_fork(p, p->id - 1, p->id);
	pthread_mutex_unlock(&p->fork->fork_lock);
}

void	*printing(t_m *p, int msg)
{
	pthread_mutex_lock(&p->fork->print_lock);
	if (c_dead(p))
		return (pthread_mutex_unlock(&p->fork->print_lock), NULL);
	else if (msg == 1)
		printf("[%lld]	[%d]	is eating🍽\n", \
		get_time() - p->time, p->id);
	else if (msg == 2)
		printf("[%lld]	[%d]	is sleeping💤\n", \
		get_time() - p->time, p->id);
	else if (msg == 3)
		printf("[%lld]	[%d]	is thinking🤔\n", \
		get_time() - p->time, p->id);
	else if (msg == 5)
		printf("[%lld]	[%d]	has taken forks🍴\n", \
		get_time() - p->time, p->id);
	pthread_mutex_unlock(&p->fork->print_lock);
	return (NULL);
}

void	*check_dead(t_m *p)
{
	if ((get_time() - p->last_time >= p->td && p->last_time != 0) \
	|| (p->last_time == 0 && get_time() - p->time >= p->td))
	{
		pthread_mutex_lock(&p->fork->dead_lock);
		if (p->fork->dead == 1)
			return (pthread_mutex_unlock(&p->fork->dead_lock), NULL);
		p->fork->dead = 1;
		pthread_mutex_unlock(&p->fork->dead_lock);
		pthread_mutex_lock(&p->fork->print_lock);
		printf("[%lld]	[%d]	is Dead💀\n", \
		get_time() - p->time, p->id);
		pthread_mutex_unlock(&p->fork->print_lock);
	}
	return (NULL);
}
