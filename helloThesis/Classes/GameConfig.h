#ifndef _GAME_CONFIG_
#define _GAME_CONFIG_

#define TILE_SIZE	32 
#define DESIGN_SCREEN_WIDTH 1136
#define DESIGN_SCREEN_HEIGHT 640


#define PTM_RATIO 32
#define SET_DEBUG 1

#define TAG_OBJECT_PLAYER	1
#define TAG_OBJECT_PLAYER_BODY	2

#define TAG_OBJECT_GROUND           100
#define TAG_OBJECT_BARNORMAL        101
#define TAG_OBJECT_BARSLOPE         102
#define TAG_OBJECT_BACK             103

#define TAG_OBJECT_MAP              200

#define MOVING_DIRECTION_LEFT	-1
#define MOVING_DIRECTION_RIGHT	1
#define MOVING_DIRECTION_NO		0

class GameConfig{
public:
	static float scale;
    static float RANK_TABLE_WIDTH;
    static float RANK_TABLE_CELL_HEIGHT;
};
#endif