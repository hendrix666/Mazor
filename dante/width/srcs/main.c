/*
** resolve.c for resolve in mery_h/test/dante/tournoi/srcs
**
** Made by Henry Fumery
** Login   <fumery_h@epitech.eu>
**
** Started on  Mon May 16 22:22:55 2016 Henry Fumery
** Last update Mon May 16 22:22:55 2016 Henry Fumery
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"../my_r.h"

void printf_red(char point) {
  printf("\033[1;31m");
  printf("%c", point);
  printf("\033[0m");
}

void	print_maze(t_map *map, int larg, int haut)
{
  int	i;
  int	j = 0;

  while (j != haut)
  {
    i = 0;
    while (i != larg)
	  {
      (map->map[j][i] == 'O') ? printf_red('O') : printf("%c", map->map[j][i]); 
	    i++;
	  }
    printf("\n");
    j++;
  }
}

void	change_posr(t_map *map, int nb)
{
  if (nb == 1)
    map->x -= 1;
  else if (nb == 2)
    map->y -= 1;
  else if (nb == 3)
    map->x += 1;
  else
    map->y += 1;
  map->seen[map->y][map->x] = 1;
  // return (map);
}

void	resolve_maze(t_map *map, int haut, int larg)
{
  int	nb_rand;
  int	dir;

  srand(time(NULL));
  
  map->x = 0;
  map->y = 0;
  map->seen[map->y][map->x] = 1;
  map->cmp_lab = (larg * haut);

  while ((map->x != larg - 2 || map->y != larg - 1)
    && (map->x != larg-1 || map->y != larg - 2))
  {
    nb_rand = rand() % 4 + 1;
    dir = check_posr(nb_rand, map, haut, larg);
    while (dir == 0)
	  {
	    nb_rand = rand() % 4 + 1;
	    dir = check_posr(nb_rand, map, haut, larg);
	  }
    map = find_path(map, dir);
    change_posr(map, dir);
    map = saver(map, haut, larg, dir);
  }
  map = draw_path(map, larg, haut);
  free_all(map, haut, larg);
}

int	main(int ac, char **av)
{
  t_map		*map;
  char		*line = NULL;
  FILE		*fd;
  size_t	len = 0;

  if (ac == 2)
  {
    fd = fopen(av[1], "r");
    if (fd == NULL)
	    return (EXIT_FAILURE);
    map = get_content(line, fd, len, av[1]);
    map->cmp_save = 0;
    map->my_signal = 0;
    resolve_maze(map, map->y, map->x);
    if (line)
	    free(line);
    fclose(fd);
  } 
  else {
    printf("You need to pass filename as first argument.\n");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
