/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:21:26 by aalfahal          #+#    #+#             */
/*   Updated: 2023/03/25 03:01:18 by aalfahal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdgt(char *s)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			x++;
		else if (s[i] == '+' && i == 0 \
		&& s[i + 1] >= '0' && s[i + 1] <= '9')
			x++;
		else
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	init_philo_forks(t_p *p)
{
	t_f	*forks;
	int	i;

	i = 1;
	forks = malloc(sizeof(t_f));
	memset(forks, 0, sizeof(t_m));
	forks->forks = malloc(sizeof(int) * p->p_num + 4);
	memset(forks->forks, 0, sizeof(int) * p->p_num + 4);
	forks->p_num = p->p_num;
	while (p->t_count < p->p_num)
		forks->forks[p->t_count++] = i++;
	i = 0;
	p->t_count = 1;
	while (i < p->p_num)
	{
		p->thread[i].meals = p->p_meals;
		p->thread[i].eaten_meals = 0;
		p->thread[i].td = p->p_td;
		p->thread[i].ts = p->p_ts;
		p->thread[i].te = p->p_te;
		p->thread[i].time = p->time;
		p->thread[i].fork = forks;
		p->thread[i++].id = p->t_count++;
	}
	p->fork = forks;
}

void	check_nums(t_p *p, char **av, int ac)
{
	if ((p->p_num == 0 && ft_strlen(av[1]) >= 2) \
	|| p->p_num > 200 || p->p_num <= 0)
		p->exit = 1;
	else if ((p->p_td == 0 && ft_strlen(av[2]) >= 2) || p->p_td < 0)
		p->exit = 1;
	else if ((p->p_te == 0 && ft_strlen(av[3]) >= 2) || p->p_te < 0)
		p->exit = 1;
	else if ((p->p_ts == 0 && ft_strlen(av[4]) >= 2) || p->p_ts < 0)
		p->exit = 1;
	else
		p->exit = 0;
	if (ac == 6 && ((p->p_meals == 0 && ft_strlen(av[5]) >= 2) \
	|| p->p_meals <= 0 || ft_isdgt(av[5])))
		p->exit = 1;
	if (p->exit == 1 && p->p_num < 0)
		p->p_num = 1;
	if (ft_isdgt(av[1]) || ft_isdgt(av[2]) \
	|| ft_isdgt(av[3]) || ft_isdgt(av[4]))
		p->exit = 1;
	p->thread = malloc(sizeof(t_m) * p->p_num);
	memset(p->thread, 0, sizeof(t_m) * p->p_num);
	p->t_count = 0;
	init_philo_forks(p);
	p->t_count = 0;
}

void	we_sleep(long long current_time, int val)
{
	while (get_time() - current_time < val)
		usleep(100);
	return ;
}
