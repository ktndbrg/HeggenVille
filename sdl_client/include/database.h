#ifndef DATABASE
#define DATABASE

/* Player_List */
typedef struct player_s {
	int id;
	int health;
	float pos_x;
	float dir_x;
	int sprite_state;
	int sprite_dir;
	float state_timer;
	int target_id;
	struct player_s *node;
} player_t;
extern player_t player_list[4];

/* Enemy_List */
typedef player_t enemy_t;
extern enemy_t *enemy_list_root;

/* Bullet_List */
typedef struct bullet_s {
	int id;
	float pos_x;
	float dir_x;
	int sprite_state;
	float state_timer;
} bullet_t;
extern bullet_t bullet_list[10];

enemy_t* DB_AddEnemy (void);
enemy_t* DB_GetLastEnemy (enemy_t *node);
enemy_t* DB_GetEnemyID (enemy_t *node, int id);
enemy_t* DB_GetEnemyIDPrevious (enemy_t *node, int id);

void DB_AddBullet (float pos_x, int dir);

#endif
