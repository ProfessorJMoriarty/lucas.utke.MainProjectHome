#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <list>

#include "Globals.h"
#include "GameObject.h"
#include "FootSoldier.h"
#include "Terrain.h"
#include "Player.h"
#include "Tree.h"
#include "Units.h"
#include "Gun.h"
#include "Bullet.h"
#include "Background.h"
#include "Bird.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

using namespace std;

bool keys[] = { false, false, false, false, false, false, false, false, false, false };
enum KEYS { UP, DOWN, LEFT, RIGHT, MOUSE_BUTTON, NUM_1, NUM_2, NUM_3, ENTER, SHIFT };

//Terrain creation
void NewMap(ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, int Map[MAPH][MAPW], double cameraXPos, double cameraYPos);

//within NewMap
void AllegroOverlay(int Map[MAPH][MAPW], ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, double cameraXPos, double cameraYPos);
void Render(ALLEGRO_BITMAP *TerrainImage, int game_x, int game_y, int image_x, int image_y, int size_x, int size_y, double cameraXPos, double cameraYPos, bool collision);

void CreateIsland(int Island[ISLANDH][ISLANDW]);

//island generation specifics
void IslandBasic(int Island[ISLANDH][ISLANDW]);
void IslandCornering(int Island[ISLANDH][ISLANDW]);
void IslandDetailing(int Island[ISLANDH][ISLANDW]);

void MapDecor(int Map[MAPH][MAPW]);
void MapBase(int Map[MAPH][MAPW]);

void ChangeState(int &state, int newState, ALLEGRO_BITMAP *PlayerImage, double &PlayerPosX, double &PlayerPosY, double &cameraXPos, double &cameraYPos, ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, Player *player);

std::list<GameObject *> objects;//used in object creation
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

Background *TitleScreen;
ALLEGRO_SAMPLE_INSTANCE *songInstance;

int main(int argc, char **argv) {

	//==============================================
	//SHELL VARIABLES
	//==============================================

	bool redraw = true;
	bool doexit = false;
	bool render = false;

	double mousex = 0;
	double mousey = 0;

	double gameTime = 0;
	double frames = 0;
	double gameFPS = 0;

	int frametimer = 0;
	int secondtimer = 0;

	double cameraXDir = 0;
	double cameraYDir = 0;

	double cameraXPos = 0;
	double cameraYPos = 0;

	double PlayerPosX = cameraXPos + (SCREENW / 2);
	double PlayerPosY = cameraYPos + (SCREENH / 2);

	double MouseAngle = 0;
	int countercoltest = 0;

	//==============================================
	//PROJECT VARIABLES
	//==============================================
	Player *player;

	player = new Player();

	int state = -1;

	ALLEGRO_BITMAP *FootSoldierImage = NULL;
	ALLEGRO_BITMAP *TerrainImage = NULL;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *TitleScreenImage = NULL;
	ALLEGRO_BITMAP *PlayerImage = NULL;
	ALLEGRO_BITMAP *GunImage = NULL;
	ALLEGRO_BITMAP *BulletImage = NULL;

	ALLEGRO_BITMAP *Tree_1_Image = NULL;
	ALLEGRO_BITMAP *Tree_2_Image = NULL;
	ALLEGRO_BITMAP *Tree_3_Image = NULL;
	ALLEGRO_BITMAP *Tree_4_Image = NULL;
	ALLEGRO_BITMAP *Tree_5_Image = NULL;
	ALLEGRO_BITMAP *BirdImage = NULL;

	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE *shot = NULL;

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18;

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(SCREENW, SCREENH);		//create our display object

	if (!display)										//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_install_mouse();

	//==============================================
	//PROJECT INIT
	//==============================================
	//insert font types, images, sounds, state images, etc
	font18 = al_load_font("arial.ttf", 18, 0);
	al_reserve_samples(15);

	bgImage = al_load_bitmap("ParaSkyImage.png");

	Background *bg = new Background(bgImage);
	objects.push_back(bg);

	//bg = new Background(mgImage, 3);//possible later use (used in Space Shooter)
	//objects.push_back(bg);

	//bg = new Background(fgImage, 5);
	//objects.push_back(bg);

	FootSoldierImage = al_load_bitmap("FootSoldierImage.png");//("AnimTestingImage.png");
	al_convert_mask_to_alpha(FootSoldierImage, al_map_rgb(255, 0, 255));

	TerrainImage = al_load_bitmap("TerrainImageS2.png");
	al_convert_mask_to_alpha(TerrainImage, al_map_rgb(255, 255, 255));

	PlayerImage = al_load_bitmap("PlayerImage.png");
	al_convert_mask_to_alpha(PlayerImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(PlayerImage, al_map_rgb(181, 230, 29));
	//player->Init(PlayerImage, PlayerPosX, PlayerPosY, DIMW, DIMH, 0, 0, PLAYERVELX, PLAYERVELY);
	//objects.push_back(player);//brings player to front of images

	GunImage = al_load_bitmap("GunImage.png");
	al_convert_mask_to_alpha(GunImage, al_map_rgb(255, 255, 255));

	BulletImage = al_load_bitmap("BulletImage.png");
	al_convert_mask_to_alpha(BulletImage, al_map_rgb(255, 255, 255));

	Tree_1_Image = al_load_bitmap("Tree_1.png");//trees
	al_convert_mask_to_alpha(Tree_1_Image, al_map_rgb(255, 255, 255));
	Tree_2_Image = al_load_bitmap("Tree_2.png");
	al_convert_mask_to_alpha(Tree_2_Image, al_map_rgb(255, 255, 255));
	Tree_3_Image = al_load_bitmap("Tree_3.png");
	al_convert_mask_to_alpha(Tree_3_Image, al_map_rgb(255, 255, 255));
	Tree_4_Image = al_load_bitmap("Tree_4.png");
	al_convert_mask_to_alpha(Tree_4_Image, al_map_rgb(255, 255, 255));
	Tree_5_Image = al_load_bitmap("Tree_5.png");
	al_convert_mask_to_alpha(Tree_5_Image, al_map_rgb(255, 255, 255));

	BirdImage = al_load_bitmap("BirdImage.png");
	al_convert_mask_to_alpha(BirdImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BirdImage, al_map_rgb(181, 230, 29));

	TitleScreenImage = al_load_bitmap("TitleScreenImage.png");
	TitleScreen = new Background(TitleScreenImage);

	shot = al_load_sample("Gunshot.wav");
	song = al_load_sample("Titan.mp3");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	ChangeState(state, TITLE, PlayerImage, PlayerPosX, PlayerPosY, cameraXPos, cameraYPos, TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, player);

	srand(time(NULL));
	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.000 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_flip_display();

	al_start_timer(timer);
	gameTime = al_current_time();

	//game loop begin
	while (!doexit)
	{


		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		frametimer++;
		if (frametimer == FPS)
		{
			secondtimer++;
			frametimer = 0;
			//cout << secondtimer << endl;
			//cout << "(" << cameraXPos << ", " << cameraYPos << ")" << endl;
		}

		//==============================================
		//INPUT
		//==============================================
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)//update mouse position
		{
			mousex = ev.mouse.x;
			mousey = ev.mouse.y;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = true;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = true;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				if (state == TITLE) {
					ChangeState(state, PLAYING, PlayerImage, PlayerPosX, PlayerPosY, cameraXPos, cameraYPos, TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, player);
				}
				else if (state == PLAYING)
					ChangeState(state, TITLE, PlayerImage, PlayerPosX, PlayerPosY, cameraXPos, cameraYPos, TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, player);
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = true;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			keys[MOUSE_BUTTON] = true;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = false;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = false;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = false;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			keys[MOUSE_BUTTON] = false;
		}
		//==============================================
		//GAME UPDATE
		//==============================================

		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if (state == PLAYING)//if playing, receive movement and other stuff
			{
				//updating camerapos/dir and mouseangle, + others later
				MouseAngle = atan2(mousey - player->GetY(), mousex - player->GetX()) * 180 / PI;//calculating MouseAngle for bullets and guns
				if (MouseAngle < 0)
					MouseAngle *= -1;
				else if (MouseAngle > 0) {
					MouseAngle = 360 - MouseAngle;
				}
				//camera control
				if ((cameraXPos - -PLAYERVELX*(player->GetX() - (SCREENW / 2)) / 100) > 0 && (cameraXPos + SCREENW - -PLAYERVELX*(player->GetX() - (SCREENW / 2)) / 100) < WORLDW)//to stop camera from exceeding mapsize
					cameraXDir = -PLAYERVELX*(player->GetX() - (SCREENW / 2)) / 100;//velocity of camera is dependent on distance from player
				else
					cameraXDir = 0;

				if ((cameraYPos - -PLAYERVELY*(player->GetY() - (SCREENH / 2)) / 100) > 0 && (cameraYPos + SCREENW - -PLAYERVELY*(player->GetY() - (SCREENH / 2)) / 100) < WORLDH)
					cameraYDir = -PLAYERVELY*(player->GetY() - (SCREENH / 2)) / 100;
				else
					cameraYDir = 0;

				cameraXPos -= cameraXDir;
				cameraYPos -= cameraYDir;

				//cout << "( " << cameraXPos << ", " << cameraYPos << " )" << endl;
				//keyboard/mouse commands
				if (keys[MOUSE_BUTTON] && keys[SHIFT])
				{
					Bullet *bullet = new Bullet();
					bullet->Init(BulletImage, player->GetX() + 25, player->GetY() + 25, 16, 16, MouseAngle, sin((MouseAngle + 90) / 180 * PI), cos((MouseAngle + 90) / 180 * PI));
					objects.push_back(bullet);
					al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					//keys[MOUSE_BUTTON] = false;
				}
				else if (keys[MOUSE_BUTTON])
				{
					player->SetX(mousex);
					player->SetY(mousey);
					cout << "( " << mousex + cameraXPos << ", " << mousey + cameraYPos << " )" << endl;
					//keys[MOUSE_BUTTON] = false;
				}
				if (keys[SHIFT])
				{
					player->ResetAnimation(1);
					player->ResetAnimation(0);
					Gun *gun = new Gun();
					gun->Init(GunImage, player->GetX(), player->GetY(), DIMW, DIMH, MouseAngle);
					objects.push_back(gun);
				}
				else {
					if (keys[UP]) {//player movement
						player->MoveUp();
					}
					else if (keys[DOWN]) {
						player->MoveDown();
					}
					else {
						player->ResetAnimation(1);
					}

					if (keys[LEFT]) {
						player->MoveLeft();
					}
					else if (keys[RIGHT]) {
						player->MoveRight();
					}
					else {
						player->ResetAnimation(0);
					}
				}


				if (keys[NUM_1])//temp
				{
					ChangeState(state, PLAYING, PlayerImage, PlayerPosX, PlayerPosY, cameraXPos, cameraYPos, TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, player);

					keys[NUM_1] = false;
				}

				if (keys[NUM_2])//temp
				{
					Bird *bird = new Bird();
					bird->Init(BirdImage, mousex, mousey, 26, 26, 0, 0, 10, 10);
					objects.push_back(bird);
					//keys[NUM_2] = false;
				}



				//collisions
				for (iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if (!(*iter)->Collidable() || (*iter)->GetID() == TERRAIN_EMPTY) continue;//checks whether collidable or whether terrain. if terrain is checked, due to it being a large #, will crash game. 

					for (iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						//if (sqrt(((*iter)->GetX() - (*iter2)->GetX())*((*iter)->GetX() - (*iter2)->GetX()) + ((*iter)->GetY() - (*iter2)->GetY())*((*iter)->GetY() - (*iter2)->GetY())) >= COL_RANGEX / 2) continue;
						if ((*iter2)->GetID() == TERRAIN_EMPTY) continue;

						//if ((*iter)->GetID() == TERRAIN_FULL && (*iter2)->GetID() == TERRAIN_EMPTY) continue;

						if ((*iter)->GetID() == (*iter2)->GetID()) continue;//if same type of object

						if (!(*iter2)->Collidable()) continue;//if object isnt collidable/alive, stop here

						if ((*iter)->GetX() == (*iter2)->GetX() && //if in same position (ie same object)
							(*iter)->GetY() == (*iter2)->GetY()) continue;


						if ((*iter)->CheckCollisions((*iter2)))
						{
							(*iter)->Collided((*iter2));
							(*iter2)->Collided((*iter));
							//cout << "collision of " << (*iter)->GetID() << " with " << (*iter2)->GetID() << endl << endl;
							//countercoltest++;
							//cout << "COLLISION" << countercoltest << endl;
						}
					}
				}

				//update
				for (iter = objects.begin(); iter != objects.end(); ++iter)
				{
					(*iter)->Update(cameraXDir, cameraYDir);
				}

			}
			//=====================(PLAYING end)
			//cull the dead
			for (iter = objects.begin(); iter != objects.end();)
			{
				if (!(*iter)->GetAlive())
				{
					delete (*iter);
					iter = objects.erase(iter);
				}
				else
					iter++;
			}
		}

		//==============================================
		//RENDER
		//==============================================
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS);	//display FPS on screen

			//BEGIN PROJECT RENDER================
			if (state == TITLE)
				TitleScreen->Render();
			else if (PLAYING) {
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Render();
				}
			}
			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end gameloop

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================
	for (iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	TitleScreen->Destroy();
	delete TitleScreen;

	al_destroy_bitmap(FootSoldierImage);
	al_destroy_bitmap(TerrainImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(TitleScreenImage);
	al_destroy_bitmap(PlayerImage);
	al_destroy_bitmap(GunImage);
	al_destroy_bitmap(BulletImage);

	al_destroy_bitmap(Tree_1_Image);
	al_destroy_bitmap(Tree_2_Image);
	al_destroy_bitmap(Tree_3_Image);
	al_destroy_bitmap(Tree_4_Image);
	al_destroy_bitmap(Tree_5_Image);

	al_destroy_sample(shot);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}
void ChangeState(int &state, int newState, ALLEGRO_BITMAP *PlayerImage, double &PlayerPosX, double &PlayerPosY, double &cameraXPos, double &cameraYPos, ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, Player *player)
{
	int counter = 0;
	bool flag1 = false;
	if (state == TITLE)
	{
	}
	else if (state == PLAYING)
	{
		for (iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if ((*iter)->GetID() != PLAYER && (*iter)->GetID() != MISC)
				(*iter)->SetAlive(false);
		}

		al_stop_sample_instance(songInstance);
	}
	else if (state == LOST)
	{
	}

	state = newState;

	if (state == TITLE)
	{
	}
	else if (state == PLAYING)
	{
		int Map[MAPH][MAPW] = {};//matrix setup here!

		NewMap(TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, Map, cameraXPos, cameraYPos);//function to create game map

		for (int y = 0; y <= MAPH; y++) {
			for (int x = 0; x <= MAPW; x++) {
				if (Map[y][x] == TIER_1) {
					PlayerPosX = x*DIMW - cameraXPos;
					PlayerPosY = y*DIMH - cameraYPos;
					//cameraXPos = PlayerPosX - (SCREENW / 2);
					//cameraYPos = PlayerPosY - (SCREENH / 2);
					y = MAPH + 1, x = MAPW + 1;//exit
				}
			}
		}

		player->Init(PlayerImage, PlayerPosX, PlayerPosY, 38, DIMH, 0, 0, PLAYERVELX, PLAYERVELY);

		for (iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if ((*iter)->GetID() == PLAYER)
				iter = objects.erase(iter);
		}
		objects.push_back(player);

		al_play_sample_instance(songInstance);
	}
	else if (state == LOST)
	{
	}
}

void NewMap(ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, int Map[MAPH][MAPW], double cameraXPos, double cameraYPos)
{
	int Island[ISLANDH][ISLANDW] = {};

	int x = 1;
	int y = 1;
	bool create = true;
	/*
	for (int a = 0; a < 10000; a++) {

		x = rand() % MAPW + 1;//sets random coordinate
		y = rand() % MAPH + 1;

		if (y + ISLANDH <= MAPH &&//checks whether its within Map
			x + ISLANDW <= MAPW) {

			for (int y1 = 0; y1 < ISLANDH; y1++) {//checks whether other Islands are within it
				for (int x1 = 0; x1 < ISLANDW; x1++) {
					if (Map[y1 + y][x1 + x] != 0)
						create = false;
				}
			}

			if (create == true) {
				CreateIsland(Island);//creates Island
				for (int r_y = 0; r_y < ISLANDH; r_y++) {
					for (int r_x = 0; r_x < ISLANDW; r_x++) {
						Map[r_y + y][r_x + x] = Island[r_y][r_x];//copies Island
					}
				}
			}
		}
		create = true;
	}
	//creates foliage and map bottom
	//MapDecor(Map);
	//MapBase(Map);
	*/

	//copies in Islands 
	for (int y = 0; y + ISLANDH <= MAPH; y += ISLANDH) {
		for (int x = 0; x + ISLANDW <= MAPW; x += ISLANDW) {

			CreateIsland(Island);//creates Island
			for (int r_y = 0; r_y < ISLANDH; r_y++) {
				for (int r_x = 0; r_x < ISLANDW; r_x++) {
					Map[r_y + y][r_x + x] = Island[r_y][r_x];//copies Island
				}
			}
	//		x += 10;
		}
	//	y += 10;
	}

	//CreateFog(Map); ??

	//sets ground to be displayed (matrix to console conversion)
	cout << "ALLEGRO OVERLAY" << endl;
	AllegroOverlay(Map, TerrainImage, Tree_1_Image, Tree_2_Image, Tree_3_Image, Tree_4_Image, Tree_5_Image, bgImage, BirdImage, cameraXPos, cameraYPos);
}


void CreateIsland(int Island[ISLANDH][ISLANDW])
{
	IslandBasic(Island);//creates tiers
	//IslandCornering(Island);//adds in corners
	//IslandDetailing(Island);//creates shadows, backwall
	//actual Island changing now done
	/*for (int y = 0; y <= ISLANDH; y++){//setting up for Allegro Overlay+later tier work
		for (int x = 0; x <= ISLANDW; x++){
			if (Island[y][x] == 1){ Island[y][x] = TIER_1; }
			if (Island[y][x] == 2){ Island[y][x] = TIER_2; }
		}
	}*/
}

void IslandBasic(int Island[ISLANDH][ISLANDW]) {
	
	//refreshing matrix
	for (int y = 0; y < ISLANDH; y++) {
		for (int x = 0; x < ISLANDW; x++) {
			Island[y][x] = 0;
		}
	}

	//creating grass
	int path_h = ISLANDH/2;
	int path_w = ISLANDW/2;

	for (int a = 0; a < 20; a++) {

		int direction = rand() % 4 + 1;

		if (direction == 1) {//up		
			path_h -= 1;
		}
		else if (direction == 2) {//down
			path_h += 1;
		}
		else if (direction == 3) {//left
			path_w -= 1;
		}
		else if (direction == 4) {//right
			path_w += 1;
		}

		if (path_h < ISLANDH && path_h > 0 && path_w < ISLANDW && path_w > 0)
			Island[path_h][path_w] = GRASS_FLOOR_1;
	}
	//adding in brick within grass
	for (int y = 0; y + 2 <= ISLANDH; y += 2) {
		for (int x = 0; x + 2 <= ISLANDW; x += 2) {
			if (rand() % 4 + 1 == 1) {
				if (Island[y][x] == GRASS_FLOOR_1)
					Island[y][x] = BRICK_FLOOR_1;
				if (Island[y + 1][x] == GRASS_FLOOR_1)
					Island[y + 1][x] = BRICK_FLOOR_1;
				if (Island[y][x + 1] == GRASS_FLOOR_1)
					Island[y][x + 1] = BRICK_FLOOR_1;
				if (Island[y + 1][x + 1] == GRASS_FLOOR_1)
					Island[y + 1][x + 1] = BRICK_FLOOR_1;
			}
		}
	}
	//adding in scaffold within brick
	for (int y = 0; y <= ISLANDH; y ++) {
		for (int x = 0; x <= ISLANDW; x ++) {
			if (rand() % 4 + 1 == 1) {
				if (Island[y][x] == BRICK_FLOOR_1)
					Island[y][x] = SCAFFOLD_FLOOR_1;
			}
		}
	}
	//adding in mixed blocks
	//adding in base
	//adding in detailing?

}


/*void IslandBasic(int Island[ISLANDH][ISLANDW])
{
	//refreshing matrix
	for (int y = 0; y < ISLANDH; y++){
		for (int x = 0; x < ISLANDW; x++){//setting tiers up	(0)
			Island[y][x] = 0;
		}
	}
	//creating box of 1's
	for (int y = ISLANDBORDERH; y < ISLANDH - ISLANDBORDERH; y++){
		for (int x = ISLANDBORDERW; x < ISLANDW - ISLANDBORDERW; x++){//setting tiers up	(1)
			Island[y][x] = 1;
		}
	}
	//growing 2's on 1's
	for (int y = ISLANDBORDERH; y < ISLANDH - ISLANDBORDERH; y++){
		for (int x = ISLANDBORDERW; x < ISLANDW - ISLANDBORDERW; x++){//setting tiers up	(2)
			int chance = rand() % 6;
			if (chance == 1)
				Island[y][x] = 2;
		}
	}
	//eliminating growth in front
	for (int x = ISLANDBORDERW; x < ISLANDW - ISLANDBORDERW; x++){//setting tiers up	(3)
		Island[ISLANDH - ISLANDBORDERH - 1][x] = 1;
	}

	//clearing errors (extends cliffs to fit top-down perspective)
	for (int y = ISLANDBORDERH; y < ISLANDH - ISLANDBORDERH; y++){
		for (int x = ISLANDBORDERW; x < ISLANDW - ISLANDBORDERW; x++){
			if (Island[y][x] == 2)
			{
				for (int a = y; a > 0; a--)
				{
					if (Island[a][x] == 1){ Island[a][x] = 2; }
				}
			}
		}
	}
	for (int y = 0; y < ISLANDH; y++){//cue expansion!
		for (int x = 0; x < ISLANDW; x++){
			if (Island[y][x] == 2){
				Island[y - CLIFFH][x] = 2;
				for (int a = 0; a <= CLIFFH - 1; a++){
					Island[y - a][x] = WALL;
				}
			}
		}
	}

	for (int y = 0; y <= ISLANDH; y++){//setting cliff edges
		for (int x = 0; x <= ISLANDW; x++){
			if (Island[y][x] == WALL  &&
				Island[y - 1][x] == 2){
				Island[y][x] = WALL_END_T2;
			}
		}
	}


}*/
/*
void IslandCornering(int Island[ISLANDH][ISLANDW])
{

	for (int y = 0; y < ISLANDH; y++) {//wall cornering!
		for (int x = 0; x < ISLANDW; x++) {

			if (Island[y][x] == WALL_END_T2 &&
				Island[y][x + 1] == 2)
				Island[y][x] = WALL_COR_TOP_LEFT_T2;

			if (Island[y][x] == WALL_END_T2 &&
				Island[y][x - 1] == 2)
				Island[y][x] = WALL_COR_TOP_RIGHT_T2;

			if (Island[y][x] == 1 &&
				Island[y + 1][x] == 0 &&
				Island[y][x + 1] == 0 &&
				Island[y - 1][x] != WALL)
				Island[y][x] = WALL_COR_TOP_RIGHT_T1;

			if (Island[y][x] == 1 &&
				Island[y + 1][x] == 0 &&
				Island[y][x - 1] == 0 &&
				Island[y - 1][x] != WALL)
				Island[y][x] = WALL_COR_TOP_LEFT_T1;

		}
	}
	for (int y = 0; y < ISLANDH; y++) {//wall cornering(2)!
		for (int x = 0; x < ISLANDW; x++) {
			if (Island[y][x] == WALL_COR_TOP_RIGHT_T2 &&
				Island[y + 1][x] == WALL)
			{
				Island[y + 1][x] = WALL_COR_RIGHT;
			}
			if (Island[y][x] == WALL_COR_TOP_LEFT_T2 &&
				Island[y + 1][x] == WALL)
			{
				Island[y + 1][x] = WALL_COR_LEFT;
			}

			if (Island[y][x] == WALL_COR_LEFT &&
				Island[y + 1][x] == WALL)
			{
				Island[y + 1][x] = WALL_COR_LEFT;
			}
			if (Island[y][x] == WALL_COR_RIGHT &&
				Island[y + 1][x] == WALL)
			{
				Island[y + 1][x] = WALL_COR_RIGHT;
			}
		}
	}
	for (int y = 0; y < ISLANDH; y++) {//wall cornering(3)!
		for (int x = 0; x < ISLANDW; x++) {
			if (Island[y][x] == WALL_COR_LEFT &&
				Island[y + 1][x] == 1) {
				Island[y][x] = WALL_COR_LEFT;
				Island[y + 1][x] = WALL_COR_BOT_LEFT_T1;
			}
			if (Island[y][x] == WALL_COR_LEFT &&
				Island[y + 1][x] == 2) {
				Island[y][x] = WALL_COR_LEFT;
				Island[y + 1][x] = WALL_COR_BOT_LEFT_T2;
			}
			if (Island[y][x] == WALL_COR_RIGHT &&
				Island[y + 1][x] == 1) {
				Island[y][x] = WALL_COR_RIGHT;
				Island[y + 1][x] = WALL_COR_BOT_RIGHT_T1;
			}
			if (Island[y][x] == WALL_COR_RIGHT &&
				Island[y + 1][x] == 2) {
				Island[y][x] = WALL_COR_RIGHT;
				Island[y + 1][x] = WALL_COR_BOT_RIGHT_T2;
			}
		}
	}
}

void IslandDetailing(int Island[ISLANDH][ISLANDW])
{

	for (int y = 0; y <= ISLANDH; y++) {// shadowing (1)
		for (int x = 0; x <= ISLANDW; x++) {
			if (Island[y][x] == 1 &&
				(Island[y][x + 1] == 2 ||
					Island[y][x + 1] == WALL ||
					Island[y][x + 1] == WALL_END_T2 ||
					Island[y][x + 1] == WALL_COR_LEFT ||
					Island[y][x + 1] == WALL_COR_TOP_LEFT_T2))
				Island[y][x] = DETAIL_SHADOW_T1_1;

			if (Island[y][x] == WALL_COR_BOT_LEFT_T1 &&
				Island[y][x - 1] == 1)
				Island[y][x - 1] = DETAIL_SHADOW_T1_2;

			if (Island[y][x] == WALL_COR_TOP_LEFT_T1 &&
				(Island[y][x + 1] == WALL))
				Island[y][x] = DETAIL_SHADOW_COR_T1_2;

			if (Island[y][x] == WALL_COR_TOP_LEFT_T1 &&
				Island[y][x + 1] == WALL_COR_BOT_LEFT_T1)
				Island[y][x] = DETAIL_SHADOW_COR_T1_1;

			if (Island[y][x] == WALL_COR_BOT_RIGHT_T1 &&
				Island[y][x + 1] == WALL_COR_BOT_LEFT_T1)
				Island[y][x] = DETAIL_SHADOW_COR_T1_3;
		}
	}

	for (int y = 0; y <= ISLANDH; y++) {// back rounding (2)
		for (int x = 0; x <= ISLANDW; x++) {
			if (Island[y][x] == 2 && Island[y][x + 1] == 0 && Island[y][x - 1] == 0)
				Island[y][x] = 0;
			if (Island[y][x] == 2 && Island[y][x - 1] == 0 && Island[y][x + 1] != 0 && Island[y - 1][x] == 0)
				Island[y][x] = WALL_BACK_LEFT_T2;
			if (Island[y][x] == 2 && Island[y][x + 1] == 0 && Island[y][x - 1] != 0 && Island[y - 1][x] == 0)
				Island[y][x] = WALL_BACK_RIGHT_T2;

			if (Island[y][x] == 1 && Island[y][x - 1] == 0 && Island[y][x + 1] != 0 && Island[y - 1][x] == 0)
				Island[y][x] = WALL_BACK_LEFT_T1;
			if (Island[y][x] == 1 && Island[y][x + 1] == 0 && Island[y][x - 1] != 0 && Island[y - 1][x] == 0)
				Island[y][x] = WALL_BACK_RIGHT_T1;
		}
	}

	for (int y = 0; y <= ISLANDH; y++) {// back rounding (3)
		for (int x = 0; x <= ISLANDW; x++) {
			if (Island[y][x] == WALL_BACK_LEFT_T2 && Island[y][x + 1] == WALL_BACK_RIGHT_T2) {
				Island[y][x] = 2;
				Island[y][x + 1] = 2;
			}
			if (Island[y][x] == WALL_BACK_LEFT_T2 && (Island[y][x + 1] == 1 ||
				Island[y][x + 1] == DETAIL_SHADOW_T1_1 ||
				Island[y][x + 1] == DETAIL_SHADOW_T1_2))
				Island[y][x] = 2;
			if (Island[y][x] == WALL_BACK_RIGHT_T2 && (Island[y][x - 1] == 1 ||
				Island[y][x - 1] == DETAIL_SHADOW_T1_1 ||
				Island[y][x - 1] == DETAIL_SHADOW_T1_2))
				Island[y][x] = 2;
		}
	}

	for (int y = 0; y <= ISLANDH; y++) {// back rounding (4)
		for (int x = 0; x <= ISLANDW; x++) {
			if (Island[y][x] == 2 && Island[y - 1][x] == 0 &&
				(Island[y][x + 1] == 1 ||
					Island[y][x + 1] == DETAIL_SHADOW_T1_1 ||
					Island[y][x + 1] == DETAIL_SHADOW_T1_2 ||
					Island[y][x - 1] == 1 ||
					Island[y][x - 1] == DETAIL_SHADOW_T1_1 ||
					Island[y][x - 1] == DETAIL_SHADOW_T1_2))
				Island[y - 1][x] = 2;
			if (Island[y][x] == WALL_END_T2 && Island[y - 1][x] == 0)
				Island[y - 1][x] = 2;
		}
	}
}

void MapDecor(int Map[MAPH][MAPW])
{
	for (int y = 0; y <= MAPH; y++) {
		for (int x = 0; x <= MAPW; x++) {//island shadowing

			if ((Map[y][x] == TIER_1
				|| Map[y][x] == WALL_COR_BOT_LEFT_T1
				|| Map[y][x] == DETAIL_SHADOW_T1_1
				|| Map[y][x] == DETAIL_SHADOW_T1_2
				|| Map[y][x] == DETAIL_SHADOW_COR_T1_1
				|| Map[y][x] == DETAIL_SHADOW_COR_T1_2) &&
				(Map[y][x - 1] == 0
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_1
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_2
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_1)) {

				Map[y + BIG_CLIFFH][x - 1] = DETAIL_SHADOW_BASE_1;
			}
			else if (Map[y][x] == WALL_BACK_LEFT_T1 &&
				(Map[y][x - 1] == 0
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_1
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_2
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_1)) {

				Map[y + BIG_CLIFFH][x - 1] = DETAIL_SHADOW_BASE_COR_2;
			}
			else if (Map[y][x] == WALL_COR_TOP_LEFT_T1 &&
				(Map[y][x - 1] == 0
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_1
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_COR_2
					|| Map[y][x - 1] == DETAIL_SHADOW_BASE_1)) {

				Map[y + BIG_CLIFFH][x - 1] = DETAIL_SHADOW_BASE_COR_1;
			}
			else if (Map[y][x] == TIER_2 && Map[y][x - 1] == 0 &&
				(Map[y + BIG_CLIFFH + CLIFFH][x - 1] == 0
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_COR_1
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_COR_2
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_1)) {

				Map[y + BIG_CLIFFH + CLIFFH][x - 1] = DETAIL_SHADOW_BASE_1;
			}
			else if (Map[y][x] == WALL_BACK_LEFT_T2 &&
				(Map[y + BIG_CLIFFH + CLIFFH][x - 1] == 0
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_COR_1
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_COR_2
					|| Map[y + BIG_CLIFFH + CLIFFH][x - 1] == DETAIL_SHADOW_BASE_1)) {

				Map[y + BIG_CLIFFH + CLIFFH][x - 1] = DETAIL_SHADOW_BASE_COR_2;
			}
		}
	}

	for (int y = 0; y <= MAPH; y++) {
		for (int x = 0; x <= MAPW; x++) {//island shadowing
			if (Map[y][x] == DETAIL_SHADOW_BASE_1 &&
				Map[y + 1][x] != DETAIL_SHADOW_BASE_1 &&
				Map[y + 2][x] == DETAIL_SHADOW_BASE_1)
				Map[y + 1][x] = DETAIL_SHADOW_BASE_1;
			if (Map[y][x] == DETAIL_SHADOW_BASE_1 &&
				Map[y + 1][x] != DETAIL_SHADOW_BASE_1 &&
				Map[y + 2][x] != DETAIL_SHADOW_BASE_1 &&
				Map[y + 3][x] == DETAIL_SHADOW_BASE_1) {
				Map[y + 1][x] = DETAIL_SHADOW_BASE_1;
				Map[y + 2][x] = DETAIL_SHADOW_BASE_1;
			}
		}
	}


	int chance = 0;
	for (int y = 0; y <= MAPH; y++) {//island tree seeding
		for (int x = 0; x <= MAPW; x++) {

			chance = rand() % 5 + 1;

			if ((Map[y][x - 1] == TIER_1 || Map[y][x - 1] == DETAIL_SHADOW_T1_1 || Map[y][x - 1] == DETAIL_SHADOW_T1_2 || Map[y][x - 1] == DETAIL_SHADOW_COR_T1_1 || Map[y][x - 1] == DETAIL_SHADOW_COR_T1_2 || Map[y][x - 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y + 1][x - 1] == TIER_1 || Map[y + 1][x - 1] == DETAIL_SHADOW_T1_1 || Map[y + 1][x - 1] == DETAIL_SHADOW_T1_2 || Map[y + 1][x - 1] == DETAIL_SHADOW_COR_T1_1 || Map[y + 1][x - 1] == DETAIL_SHADOW_COR_T1_2 || Map[y + 1][x - 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y - 1][x - 1] == TIER_1 || Map[y - 1][x - 1] == DETAIL_SHADOW_T1_1 || Map[y - 1][x - 1] == DETAIL_SHADOW_T1_2 || Map[y - 1][x - 1] == DETAIL_SHADOW_COR_T1_1 || Map[y - 1][x - 1] == DETAIL_SHADOW_COR_T1_2 || Map[y - 1][x - 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y][x + 1] == TIER_1 || Map[y][x + 1] == DETAIL_SHADOW_T1_1 || Map[y][x + 1] == DETAIL_SHADOW_T1_2 || Map[y][x + 1] == DETAIL_SHADOW_COR_T1_1 || Map[y][x + 1] == DETAIL_SHADOW_COR_T1_2 || Map[y][x + 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y + 1][x + 1] == TIER_1 || Map[y + 1][x + 1] == DETAIL_SHADOW_T1_1 || Map[y + 1][x + 1] == DETAIL_SHADOW_T1_2 || Map[y + 1][x + 1] == DETAIL_SHADOW_COR_T1_1 || Map[y + 1][x + 1] == DETAIL_SHADOW_COR_T1_2 || Map[y + 1][x + 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y - 1][x + 1] == TIER_1 || Map[y - 1][x + 1] == DETAIL_SHADOW_T1_1 || Map[y - 1][x + 1] == DETAIL_SHADOW_T1_2 || Map[y - 1][x + 1] == DETAIL_SHADOW_COR_T1_1 || Map[y - 1][x + 1] == DETAIL_SHADOW_COR_T1_2 || Map[y - 1][x + 1] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y + 1][x] == TIER_1 || Map[y + 1][x] == DETAIL_SHADOW_T1_1 || Map[y + 1][x] == DETAIL_SHADOW_T1_2 || Map[y + 1][x] == DETAIL_SHADOW_COR_T1_1 || Map[y + 1][x] == DETAIL_SHADOW_COR_T1_2 || Map[y + 1][x] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y - 1][x] == TIER_1 || Map[y - 1][x] == DETAIL_SHADOW_T1_1 || Map[y - 1][x] == DETAIL_SHADOW_T1_2 || Map[y - 1][x] == DETAIL_SHADOW_COR_T1_1 || Map[y - 1][x] == DETAIL_SHADOW_COR_T1_2 || Map[y - 1][x] == DETAIL_SHADOW_COR_T1_3) &&
				(Map[y][x] == TIER_1 || Map[y][x] == DETAIL_SHADOW_T1_1 || Map[y][x] == DETAIL_SHADOW_T1_2 || Map[y][x] == DETAIL_SHADOW_COR_T1_1 || Map[y][x] == DETAIL_SHADOW_COR_T1_2 || Map[y][x] == DETAIL_SHADOW_COR_T1_3)) {

				if (chance == 1 && Map[y][x - 2] == TIER_1 || Map[y][x - 2] == DETAIL_SHADOW_T1_1 || Map[y][x - 2] == DETAIL_SHADOW_T1_2 || Map[y][x - 2] == DETAIL_SHADOW_COR_T1_1 || Map[y][x - 2] == DETAIL_SHADOW_COR_T1_2 || Map[y][x - 2] == DETAIL_SHADOW_COR_T1_3)
					Map[y][x] = TREE_SEED_1;
				else if (chance == 2)
					Map[y][x] = TREE_SEED_2;
				else if (chance == 3)
					Map[y][x] = TREE_SEED_3;
				else if (chance == 4)
					Map[y][x] = TREE_SEED_4;
				else if (chance == 5)
					Map[y][x] = TREE_SEED_5;
			}
		}
	}
}
void MapBase(int Map[MAPH][MAPW])
{
	for (int y = 0; y <= MAPH; y++) {//creation of fadeaway (1)
		for (int x = 0; x <= MAPW; x++) {

			if ((Map[y][x] == WALL ||
				Map[y][x] == TIER_1 ||
				Map[y][x] == WALL_COR_BOT_LEFT_T1 ||
				Map[y][x] == WALL_COR_BOT_RIGHT_T1 ||
				Map[y][x] == BUSH_SEED_1 ||
				Map[y][x] == BIRD_SEED_1) &&
				Map[y + 1][x] == 0)
				Map[y + 1][x] = FADE_1;
		}
	}

	for (int y = 0; y <= MAPH; y++) {//creation of fadeaway (2)
		for (int x = 0; x <= MAPW; x++) {
			if (Map[y][x] == FADE_1) {
				for (int a = 1; a < (BIG_CLIFFH); a++) { //rand() % 4 + 2
					if (Map[y + a][x] == 0 && y + a <= MAPH)
						Map[y + a][x] = FADE_2;
				}
			}
		}
	}

	for (int y = 0; y <= MAPH; y++) {//creation of fadeaway (3)
		for (int x = 0; x <= MAPW; x++) {


			if (Map[y][x] == WALL_COR_RIGHT && Map[y + 1][x] == FADE_2)
				Map[y + 1][x] = WALL_COR_RIGHT;

			if (Map[y][x] == WALL_COR_LEFT && Map[y + 1][x] == FADE_2)
				Map[y + 1][x] = WALL_COR_LEFT;

			if (Map[y][x] == WALL_COR_LEFT && Map[y + 1][x] == 0)
				Map[y + 1][x] = WALL_COR_BOT_LEFT_T0;

			if (Map[y][x] == WALL_COR_RIGHT && Map[y + 1][x] == 0)
				Map[y + 1][x] = WALL_COR_BOT_RIGHT_T0;
		}
	}

	for (int y = 0; y <= MAPH; y++) {//creation of fadeaway (4)
		for (int x = 0; x <= MAPW; x++) {
			if (Map[y][x] == FADE_2 && Map[y + 1][x] == 0)
				Map[y][x] = FADE_END;
		}
	}

	int a = 1;

	for (int y = 0; y <= MAPH; y++) {//creation of fadeaway (5)
		for (int x = 0; x <= MAPW; x++) {
			if (Map[y][x] == WALL_COR_TOP_LEFT_T1) {
				a = 1;
				while ((Map[y + a][x + 1] != FADE_END) && (Map[y + a][x + 1] != TIER_2) && (Map[y + a][x + 1] != TIER_1)) {
					Map[y + a][x] = WALL_COR_LEFT;
					a++;
				}
				Map[y + a][x] = WALL_COR_BOT_LEFT_T0;
				a = 1;
			}

			if (Map[y][x] == WALL_COR_TOP_RIGHT_T1) {
				a = 1;
				while ((Map[y + a][x - 1] != FADE_END) && (Map[y + a][x - 1] != TIER_2) && (Map[y + a][x - 1] != TIER_1)) {
					Map[y + a][x] = WALL_COR_RIGHT;
					a++;
				}
				Map[y + a][x] = WALL_COR_BOT_RIGHT_T0;
				a = 1;
			}
		}
	}
}*/

void AllegroOverlay(int Map[MAPH][MAPW], ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, double cameraXPos, double cameraYPos) {
	for (int y = 0; y <= MAPH; y++) {
		for (int x = 0; x <= MAPW; x++) {

			if (Map[y][x] == SCAFFOLD_FLOOR_1) {
				Render(TerrainImage, x, y, 0, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == SCAFFOLD_BASE_1) {
				Render(TerrainImage, x, y, 0, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == BRICK_FLOOR_1) {
				Render(TerrainImage, x, y, 1, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == BRICK_BASE_1) {
				Render(TerrainImage, x, y, 1, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == GRASS_FLOOR_1) {
				Render(TerrainImage, x, y, 5, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == GRASS_BASE_1) {
				Render(TerrainImage, x, y, 5, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
		}
	}
	/*
		const int MIX_SCAFFOLD_BRICK_LEFT_FLOOR_1 = 35;
		const int MIX_SCAFFOLD_BRICK_RIGHT_FLOOR_1 = 40;
		const int MIX_SCAFFOLD_BRICK_LEFT_BASE_1 = 45;
		const int MIX_SCAFFOLD_BRICK_RIGHT_BASE_1 = 50;

		const int MIX_GRASS_BRICK_LEFT_FLOOR_1 = 55;
		const int MIX_GRASS_BRICK_RIGHT_FLOOR_1 = 60;
		const int MIX_GRASS_BRICK_LEFT_BASE_1 = 65;
		const int MIX_GRASS_BRICK_RIGHT_BASE_1 = 70;*/
}

/*
void AllegroOverlay(int Map[MAPH][MAPW], ALLEGRO_BITMAP *TerrainImage, ALLEGRO_BITMAP *Tree_1_Image, ALLEGRO_BITMAP *Tree_2_Image, ALLEGRO_BITMAP *Tree_3_Image, ALLEGRO_BITMAP *Tree_4_Image, ALLEGRO_BITMAP *Tree_5_Image, ALLEGRO_BITMAP *bgImage, ALLEGRO_BITMAP *BirdImage, double cameraXPos, double cameraYPos)
{
	//Render(bgImage, 0, 0, 0, 0, 5000, 5000, cameraXPos, cameraYPos, false);

	for (int y = 0; y <= MAPH; y++){
		for (int x = 0; x <= MAPW; x++){
			if (Map[y][x] == DETAIL_SHADOW_BASE_1){
				Render(TerrainImage, x, y, 0, 3, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_BASE_COR_1){
				Render(TerrainImage, x, y, 0, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_BASE_COR_2){
				Render(TerrainImage, x, y, 1, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
		}
	}
	int chance = 0;
	for (int y = 0; y <= MAPH - (FLAG_1_y / DIMH); y++){
		for (int x = 0; x <= MAPW - ((FOL_1_x / 2) / DIMW); x++){

			if (rand() % 4 + 1 == 1 && Map[y][x] == 0){

				chance = rand() % 8 + 1;
				if (chance == 1 &&
					Map[y][(x + ((FOL_1_x / 2) / DIMW)) + (FOL_1_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_1_x / 2) / DIMW)) - (FOL_1_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_1_x / 2) / DIMW)) + ((FOL_1_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_1_x / 2) / DIMW)) - ((FOL_1_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_1_x / 2) / DIMW), y + (FOL_1_y / DIMW), 0, 5, FOL_1_x, FOL_1_y);
					Render(TerrainImage, x, y, 0, 5, FOL_1_x, FOL_1_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 2 &&
					Map[y][(x + ((FOL_2_x / 2) / DIMW)) + (FOL_2_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_2_x / 2) / DIMW)) - (FOL_2_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_2_x / 2) / DIMW)) + ((FOL_2_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_2_x / 2) / DIMW)) - ((FOL_2_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_2_x / 2) / DIMW), y + (FOL_2_y / DIMW), 3, 5, FOL_2_x, FOL_2_y);
					Render(TerrainImage, x, y, 3, 5, FOL_2_x, FOL_2_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 3 &&
					Map[y][(x + ((FOL_3_x / 2) / DIMW)) + (FOL_3_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_3_x / 2) / DIMW)) - (FOL_3_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_3_x / 2) / DIMW)) + ((FOL_3_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_3_x / 2) / DIMW)) - ((FOL_3_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_3_x / 2) / DIMW), y + (FOL_3_y / DIMW), 6, 5, FOL_3_x, FOL_3_y);
					Render(TerrainImage, x, y, 6, 5, FOL_3_x, FOL_3_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 4 &&
					Map[y][(x + ((FOL_4_x / 2) / DIMW)) + (FOL_4_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_4_x / 2) / DIMW)) - (FOL_4_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_4_x / 2) / DIMW)) + ((FOL_4_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_4_x / 2) / DIMW)) - ((FOL_4_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_4_x / 2) / DIMW), y + (FOL_4_y / DIMW), 10, 5, FOL_4_x, FOL_4_y);
					Render(TerrainImage, x, y, 10, 5, FOL_4_x, FOL_4_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 5 &&
					Map[y][(x + ((FOL_5_x / 2) / DIMW)) + (FOL_5_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_5_x / 2) / DIMW)) - (FOL_5_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_5_x / 2) / DIMW)) + ((FOL_5_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_5_x / 2) / DIMW)) - ((FOL_5_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_5_x / 2) / DIMW), y + (FOL_5_y / DIMW), 13, 5, FOL_5_x, FOL_5_y);
					Render(TerrainImage, x, y, 13, 5, FOL_5_x, FOL_5_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 6 &&
					Map[y][(x + ((FOL_6_x / 2) / DIMW)) + (FOL_6_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_6_x / 2) / DIMW)) - (FOL_6_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_6_x / 2) / DIMW)) + ((FOL_6_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_6_x / 2) / DIMW)) - ((FOL_6_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_6_x / 2) / DIMW), y + (FOL_6_y / DIMW), 16, 5, FOL_6_x, FOL_6_y);
					Render(TerrainImage, x, y, 16, 5, FOL_6_x, FOL_6_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 7 &&
					Map[y][(x + ((FOL_7_x / 2) / DIMW)) + (FOL_7_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_7_x / 2) / DIMW)) - (FOL_7_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_7_x / 2) / DIMW)) + ((FOL_7_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_7_x / 2) / DIMW)) - ((FOL_7_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_7_x / 2) / DIMW), y + (FOL_7_y / DIMW), 18, 5, FOL_7_x, FOL_7_y);
					Render(TerrainImage, x, y, 18, 5, FOL_7_x, FOL_7_y, cameraXPos, cameraYPos, false);
					x++;
				}
				else if (chance == 8 &&
					Map[y][(x + ((FOL_8_x / 2) / DIMW)) + (FOL_8_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_8_x / 2) / DIMW)) - (FOL_8_x / DIMW)] == 0 &&
					Map[y][(x + ((FOL_8_x / 2) / DIMW)) + ((FOL_8_x / DIMW) / 2)] == 0 &&
					Map[y][(x + ((FOL_8_x / 2) / DIMW)) - ((FOL_8_x / DIMW) / 2)] == 0){
					//Render(TerrainImage, x + ((FOL_8_x / 2) / DIMW), y + (FOL_8_y / DIMW), 20, 5, FOL_8_x, FOL_8_y);
					Render(TerrainImage, x, y, 20, 5, FOL_8_x, FOL_8_y, cameraXPos, cameraYPos, false);
					x++;
				}
			}//tree spawning end
			else if (rand() % 100 + 1 == 1 && Map[y][x] == 0 &&//spawns in flags below the game map
				Map[y][x + (FLAG_1_x / DIMW)] == 0 &&
				Map[y + (FLAG_1_y / DIMH)][x] == 0 &&
				Map[y][x - (FLAG_1_x / DIMW)] == 0){
				//Render(TerrainImage, x + (FLAG_1_x/2)/DIMW, y+(FLAG_1_y)/DIMW, 23, 5, FLAG_1_x, FLAG_1_y);
				Render(TerrainImage, x, y, 23, 5, FLAG_1_x, FLAG_1_y, cameraXPos, cameraYPos, false);
				x++;
			}
			else if (Map[y][x] == WALL){
				Render(TerrainImage, x, y, rand() % 3 + 8, 0, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}
			else if (Map[y][x] == WALL_END_T2){
				Render(TerrainImage, x, y, 1, 0, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}


			else if (Map[y][x] == WALL_COR_LEFT){
				Render(TerrainImage, x, y, 1, 3, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_COR_RIGHT){
				Render(TerrainImage, x, y, 2, 3, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}


			else if (Map[y][x] == WALL_COR_TOP_LEFT_T2){
				Render(TerrainImage, x, y, 2, 1, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}
			else if (Map[y][x] == WALL_COR_TOP_RIGHT_T2){
				Render(TerrainImage, x, y, 3, 1, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}


			else if (Map[y][x] == WALL_COR_TOP_LEFT_T1){
				Render(TerrainImage, x, y, 2, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_COR_TOP_RIGHT_T1){
				Render(TerrainImage, x, y, 3, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}


			else if (Map[y][x] == WALL_COR_BOT_LEFT_T1){
				Render(TerrainImage, x, y, 4, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_COR_BOT_RIGHT_T1){
				Render(TerrainImage, x, y, 5, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_COR_BOT_LEFT_T2){
				Render(TerrainImage, x, y, 4, 1, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}
			else if (Map[y][x] == WALL_COR_BOT_RIGHT_T2){
				Render(TerrainImage, x, y, 5, 1, DIMW, DIMH, cameraXPos, cameraYPos, true);
			}

			else if (Map[y][x] == WALL_COR_BOT_LEFT_T0){
				Render(TerrainImage, x, y, 6, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_COR_BOT_RIGHT_T0){
				Render(TerrainImage, x, y, 7, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}


			else if (Map[y][x] == TIER_1){
				Render(TerrainImage, x, y, 0, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);//(rand() % 2), 0);
			}
			else if (Map[y][x] == TIER_2){
				Render(TerrainImage, x, y, 0, 1, DIMW, DIMH, cameraXPos, cameraYPos, true);//(rand() % 2), 1);
			}

			else if (Map[y][x] == FADE_1){
				Render(TerrainImage, x, y, (rand() % 2 + 3), 3, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}

			else if (Map[y][x] == FADE_2){
				Render(TerrainImage, x, y, 1, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == FADE_END){
				Render(TerrainImage, x, y, rand() % 3 + 8, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}

			else if (Map[y][x] == WALL_BACK_LEFT_T2){
				Render(TerrainImage, x, y, 6, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_BACK_RIGHT_T2){
				Render(TerrainImage, x, y, 7, 1, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_BACK_LEFT_T1){
				Render(TerrainImage, x, y, 6, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == WALL_BACK_RIGHT_T1){
				Render(TerrainImage, x, y, 7, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}


			else if (Map[y][x] == DETAIL_SHADOW_T1_1){
				Render(TerrainImage, x, y, 1, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_T1_2){
				Render(TerrainImage, x, y, 2, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_COR_T1_1){
				Render(TerrainImage, x, y, 3, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_COR_T1_2){
				Render(TerrainImage, x, y, 4, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == DETAIL_SHADOW_COR_T1_3){
				Render(TerrainImage, x, y, 5, 2, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
			else if (Map[y][x] == BUSH_SEED_1 ||
				Map[y][x] == TREE_SEED_1 ||
				Map[y][x] == TREE_SEED_2 ||
				Map[y][x] == TREE_SEED_3 ||
				Map[y][x] == TREE_SEED_4 ||
				Map[y][x] == TREE_SEED_5 ||
				Map[y][x] == BIRD_SEED_1){
				Render(TerrainImage, x, y, 0, 0, DIMW, DIMH, cameraXPos, cameraYPos, false);
			}
		}
	}

	for (int y = 0; y <= MAPH; y++){
		for (int x = 0; x <= MAPW; x++){

			if (Map[y][x] == TREE_SEED_1){
				Tree *tree = new Tree();
				tree->Init(Tree_1_Image, 1, x*DIMW - cameraXPos, y*DIMH - cameraYPos);
				objects.push_back(tree);
			}
			else if (Map[y][x] == TREE_SEED_2){
				Tree *tree = new Tree();
				tree->Init(Tree_2_Image, 2, x*DIMW - cameraXPos, y*DIMH - cameraYPos);
				objects.push_back(tree);
			}
			else if (Map[y][x] == TREE_SEED_3){
				Tree *tree = new Tree();
				tree->Init(Tree_3_Image, 3, x*DIMW - cameraXPos, y*DIMH - cameraYPos);
				objects.push_back(tree);
			}
			else if (Map[y][x] == TREE_SEED_4){
				Tree *tree = new Tree();
				tree->Init(Tree_4_Image, 4, x*DIMW - cameraXPos, y*DIMH - cameraYPos);
				objects.push_back(tree);
			}
			else if (Map[y][x] == TREE_SEED_5){
				Tree *tree = new Tree();
				tree->Init(Tree_5_Image, 5, x*DIMW - cameraXPos, y*DIMH - cameraYPos);
				objects.push_back(tree);
			}
			else if (Map[y][x] == BIRD_SEED_1){
				Bird *bird = new Bird();
				bird->Init(BirdImage, x*DIMW - cameraXPos, y*DIMH - cameraYPos, 26, 26, 0, 0, 10, 10);
				objects.push_back(bird);
			}
			else if (Map[y][x] == BUSH_SEED_1){
				Render(TerrainImage, x, y, rand() % 4 + 5, 3, x*DIMW - cameraXPos, y*DIMH - cameraYPos, cameraXPos, cameraYPos, false);
			}
		}
	}
}
*/
void Render(ALLEGRO_BITMAP *Image, int game_x, int game_y, int image_x, int image_y, int size_x, int size_y, double cameraXPos, double cameraYPos, bool collision)
{
	Terrain *terrain = new Terrain();
	terrain->Init(Image, (game_x*DIMW) - cameraXPos, (game_y*DIMH) - cameraYPos, WALL_DISP*image_x, WALL_DISP*image_y, size_x, size_y, collision);
	objects.push_back(terrain);
}