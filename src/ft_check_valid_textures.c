
#include "../inc/cub3d.h"

bool    check_valid_fc(t_info *info)
{
    int i;
    int fc;

    fc = 0;
    i = info->map_i;
    while (info->map[i][0] != '\n')
    {
        // man könnte auch noch hinzunehmen, dass jede Farbe nur genau einmal vorkommt!
        // Was genau brauchst du gespeichert Max? Unvollständig!
        if (info->map[i][0] == 'F')
            info->floor = info->map[i][2];
        else if (info->map[i][0] == 'C')
            info->ceiling = info->map[i][2];
        else
        { 
            printf("Invalid map: Only ceiling and floor allowed!\n");
            return (false);
        }
        fc++;
        info->map_i++;
        i = info->map_i;
    }
    if (fc != 2)
    {
        printf("Invalid map: There needs to be an ceiling and a floor!\n");
        return (false);
    }
    return (true);
}

bool    check_valid_textures(t_info *info)
{
    int i;
    int wall_orientations;

    wall_orientations = 0;
    i = info->map_i;
    //printf("String %s i %d\n", info->map[i], i);
    while (info->map[info->map_i][0] != '\n')
    {
        // man könnte auch noch hinzunehmen, dass jede Himmelsrichtung nur genau einmal vorkommt!
        // Was genau brauchst du gespeichert? Bezeichnung und Path?
        // richtige Endung der Texture noch abprüfen!!!
        if (info->map[i][0] == 'N' && info->map[i][1] == 'O')
            info->txt.path_no = ft_strdup(info->map[i]);
        else if (info->map[i][0] == 'E' && info->map[i][1] == 'A')
            info->txt.path_ea = ft_strdup(info->map[i]);
        else if (info->map[i][0] == 'S' && info->map[i][1] == 'O')
            info->txt.path_so = ft_strdup(info->map[i]);
        else if (info->map[i][0] == 'W' && info->map[i][1] == 'E')
            info->txt.path_we = ft_strdup(info->map[i]);
        else
        { 
            printf("Invalid map: Only cardinal directions allowed!\n");
            return (false);
        }
        wall_orientations++;
        //printf("map_i %d\n", info->map_i);
        //printf("String %s i %d\n", info->map[i], i);
        info->map_i++;
        i = info->map_i;
        //printf("String %s i %d\n", info->map[i], i);
    }
    //printf("num %d\n", wall_orientations);
    if (wall_orientations != 4)
    {
        printf("Invalid map: Only four cardinal directions allowed!\n");
        return (false);
    }
    return (true);
}
