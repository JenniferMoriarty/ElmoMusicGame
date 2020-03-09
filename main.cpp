//Elmo Monster Music Program
//based off the pbs kids game found here: https://pbskids.org/sesame/games/monster-music/
//Programmed by Dr. Mo
//March 2020

/*instructions:
1) expand the "keyboard" so it has 8 keys and roughly matches the colors found on pbskids.org
You can use the frequencies found here: https://www.audiology.org/sites/default/files/ChasinConversionChart.pdf, or look up other scales on your own
 2) Replace all the numbers (other than color values) in your game loop and check color function with constants
 3) Be ready to answer all the code comment questions
 4) Spicy: get the notes to push down, and/or add the little note swirls that come out in the real game when pressed
 */

#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<iostream>
using namespace std;
 
#include<Windows.h> //because I was too lazy to download wav files for each scale note :/

const float FPS = 60;
const int SCREEN_W = 1000;
const int SCREEN_H = 600;


enum COLORS { NOTHING, RED, ORANGE, YELLOW }; //what number is attached to each word?

int checkColor(float x, float y);

int main()
{
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_mouse();
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* street = al_load_bitmap("street.jpg");

	bool redraw = true;
	float xPos = 400;
	float yPos = 400;
	int color[] = { false, false, false, false }; //why do I have 4 values in there but just 3 colors?

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (color[RED])
				Beep(262, 200); //Never ever do this again. In fact, never tell anyone I did this either.
			if (color[ORANGE])
				Beep(294, 200);
			if (color[YELLOW])
				Beep(330, 200);

			//what does this do?
			for (int i = 0; i < 4; i++)
				color[i] = false;

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			xPos = ev.mouse.x;
			yPos = ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			//this is redundant; the array is already reset in the timer section
			//if we were using something better than beep, this would be good to have... can you explain why?
			for (int i = 0; i < 4; i++)
				color[i] = false;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (checkColor(xPos, yPos) == RED)
				color[RED] = true;
			if (checkColor(xPos, yPos) == ORANGE)
				color[ORANGE] = true;
			if (checkColor(xPos, yPos) == YELLOW)
				color[YELLOW] = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//background image
			al_draw_bitmap(street, 0, 0, NULL);

			//draw color boxes

			al_draw_filled_rectangle(100, 450, 200, 600, al_map_rgb(250, 0, 0)); //red
			al_draw_filled_rectangle(200, 450, 300, 600, al_map_rgb(250, 100, 0)); //orange
			al_draw_filled_rectangle(300, 450, 400, 600, al_map_rgb(250, 150, 0)); //yellow

			//draw pointer
			al_draw_filled_circle(xPos, yPos, 10, al_map_rgb(200, 200, 0));
			al_draw_circle(xPos, yPos, 10, al_map_rgb(0, 0, 0), 5);


			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


int checkColor(float x, float y) {

	//how is this similar to the bounding box collision of pong/breakout?
	//how is it different?

	if (x >= 100 && x <= 200 && y >= 450 && y <= 600) {  //check if on red
		cout << "red" << endl; //optional- put in for debugging purposes
		return RED;
	}
	else if (x >= 200 && x <= 300 && y >= 450 && y <= 600) {//check if on orange
		cout << "orange" << endl;
		return ORANGE;
	}
	else if (x >= 300 && x <= 400 && y >= 450 && y <= 600) { //check if on yellow
		cout << "yellow" << endl;
		return YELLOW;
	}
	else
		return NOTHING;
}
