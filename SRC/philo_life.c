/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:34:35 by aalfahal          #+#    #+#             */
/*   Updated: 2023/03/26 01:29:57 by aalfahal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->p_num)
	{
		if (p->thread[i++].meals != 0)
			return (1);
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	c_dead(t_m *p)
{
	pthread_mutex_lock(&p->fork->dead_lock);
	if (p->fork->dead == 1)
		return (pthread_mutex_unlock(&p->fork->dead_lock), 1);
	else
		return (pthread_mutex_unlock(&p->fork->dead_lock), 0);
}

void	*eat(void *philo)
{
	t_m	*p;

	p = (t_m *) philo;
	while (p->eaten_meals < p->meals && !c_dead(p))
	{
		take_forks(p);
		check_dead(p);
		if (c_dead(p))
			return (NULL);
		if (p->right_fork == 1 && p->left_fork == 1 && !c_dead(p))
		{
			p->last_time = get_time();
			printing(p, 1);
			we_sleep(get_time(), p->te);
			p->eaten_meals++;
			put_fork(p);
			printing(p, 2);
			we_sleep(get_time(), p->ts);
			printing(p, 3);
		}
	}
	return (NULL);
}
