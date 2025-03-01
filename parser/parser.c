#include "parser.h"

bool	parse_scene(t_scene *scene, char *filename)
{
	char 	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	while (true)
	{
		line = get_next_line(fd);
	}
	scene = (t_scene){};
	return (scene);
}
