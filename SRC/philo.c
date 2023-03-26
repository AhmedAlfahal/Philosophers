/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:25:47 by aalfahal          #+#    #+#             */
/*   Updated: 2023/03/25 03:02:16 by aalfahal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pre_rotine(t_p *p)
{
	while (p->t_count < p->p_num)
	{
		pthread_create(&p->thread[p->t_count].thread \
		, NULL, eat, (void *)&p->thread[p->t_count]);
		p->t_count++;
	}
	while (1)
	{
		if (check_meals(p))
			break ;
		pthread_mutex_lock(&p->fork->dead_lock);
		if (p->fork->dead == 1)
		{
			pthread_mutex_unlock(&p->fork->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&p->fork->dead_lock);
		usleep(100);
	}
	p->t_count = 0;
	while (p->t_count < p->p_num)
		pthread_join(p->thread[p->t_count++].thread, NULL);
}

static int	val(const char *va, int sgn, int n)
{
	long	res;

	res = 0;
	while (va[n] == '0' && va[n] != '\0')
		n++;
	while (va[n] != '\0' && va[n] >= '0' && va[n] <= '9')
	{
		res = (res * 10) + (va[n] - '0');
			n++;
		if ((res > 2147483647 && sgn == 1) || (res > 2147483648 && sgn == -1))
			return (0);
	}
	return (res);
}

static int	ft_ai(const char *str)
{
	int					i;
	int					sgn;
	long long			res;

	i = 0;
	sgn = 1;
	res = 0;
	while (str[i] == ' ' || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if ((str[i] == '-' || str[i] == '+')
			&& (str[i + 1] == '-' || str[i + 1] == '+'))
			return (0);
		else if (str[i] == '-')
				sgn = -1;
			i++;
	}
	res = val (str, sgn, i);
	return (res * sgn);
}

static void	pars_nums(t_p *p, char **av, int ac)
{
	t_m	*m;

	m = NULL;
	p->thread = m;
	p->t_count = 0;
	p->time = get_time();
	p->p_num = ft_ai(av[1]);
	p->p_td = ft_ai(av[2]);
	p->p_te = ft_ai(av[3]);
	p->p_ts = ft_ai(av[4]);
	if (ac == 6)
		p->p_meals = ft_ai(av[5]);
	else
		p->p_meals = INT_MAX;
	check_nums(p, av, ac);
	pthread_mutex_init(&p->fork->fork_lock, NULL);
	pthread_mutex_init(&p->fork->print_lock, NULL);
	pthread_mutex_init(&p->fork->dead_lock, NULL);
	p->fork->dead = 0;
	p->t_count = 0;
}

int	main(int ac, char **av)
{
	t_p	p;

	if (ac == 5 || ac == 6)
	{
		pars_nums(&p, av, ac);
		if (p.exit)
		{
			pthread_mutex_destroy(&p.fork->fork_lock);
			pthread_mutex_destroy(&p.fork->print_lock);
			pthread_mutex_destroy(&p.fork->dead_lock);
			return (free(p.fork->forks), free(p.fork), \
			free(p.thread), write(2, "Error\n", 7), p.exit);
		}
		pre_rotine(&p);
		pthread_mutex_destroy(&p.fork->fork_lock);
		pthread_mutex_destroy(&p.fork->print_lock);
		pthread_mutex_destroy(&p.fork->dead_lock);
		return (free(p.fork->forks), free(p.fork), free(p.thread), p.exit);
	}
	printf("Only 5 or 6:\n[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\
	[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}
