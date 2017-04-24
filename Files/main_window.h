#ifndef VIEWWINDOW_H_
#define VIEWWINDOW_H_

#include "window.h"
#include "graph.h"
#include "gui.h"
#include "overall.h"
using namespace Graph_lib;

struct viewWindow : Graph_lib::Window {
	public:
		viewWindow() :
			Window(Point(0,0),1000,700,"Welcome to AggieSnap! >> Browse"),
			new_button_pushed(false),
			next_button_pushed(false),
			previous_button_pushed(false),
			search_button_pushed(false),
			reset_search_button_pushed(false),
			update_tags_button_pushed(false),
			cycleVals(default_imgs()),
			imgObj(),
			imgLoc(),
			
			tag1(Point(850, 177), 95, 25, "Current Tags : Tag #01"),
			tag2(Point(850, 257), 95, 25, "Tag #02"),
			tag3(Point(850, 337), 95, 25, "Tag #03"),
			tag4(Point(850, 417), 95, 25, "Tag #04"),
			tag5(Point(850, 497), 95, 25, "Tag #05"),
			search(Point(100,17), 140, 20, "Search Tags"),
			
			//button specifications
			button_next(Point(850, 97), 80, 25, "Next", cb_next),
			button_previous(Point(850, 17), 80, 25, "Previous", cb_previous),
			button_new_pic(Point(330, 17), 70, 20, "Upload", cb_new_pic),
			button_reset_search(Point(410,17),70,20,"Reset",cb_reset_tag_search),
			button_tag_search(Point(250, 17), 70, 20, "Search", cb_tag_search),
			button_quit(Point(490,17),70,20,"Quit",cb_quit),
			button_update_tags(Point(825,577),120,25,"Modify Tags",cb_update_tags) {	
				//attaching buttons
				attach(button_next);
				attach(button_previous);
				attach(button_new_pic);
				attach(button_tag_search);
				attach(button_reset_search);
				attach(button_quit);
				attach(button_update_tags);
				//more attaching
				attach(tag1);
				attach(tag2);
				attach(tag3);
				attach(tag4);
				attach(tag5);
				attach(search);

				if ((!next_button_pushed || !previous_button_pushed) && currentCount() != 1) {
					imgObj = get_img(1);
					imgLoc = "images/1." + imgObj.getExtension();
					img = new Image(Point(140,150), imgLoc);


					img->set_mask(Point(0,0),550,400); //mask image

					name = new Text(Point(190,600), imgObj.getShortName() + "." + imgObj.getExtension()); //get image name
					name->set_font_size(35);
					name->set_color(Color::dark_blue);

					time_t date = imgObj.getDate(); //get image info; show whether image is local or url

					if (imgObj.getType() == FILE_LOCAL) {
						datastring = "Added to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t 1 / " + to_string(cycleVals.size());
					} else {
						datastring = "Downloaded to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t 1 / " + to_string(cycleVals.size());
					}

					data = new Text(Point(190,635), datastring);
					data->set_font_size(17);

					tag1.put(to_string(imgObj.getTag(1))); //updating tags
					tag2.put(to_string(imgObj.getTag(2)));
					tag3.put(to_string(imgObj.getTag(3)));
					tag4.put(to_string(imgObj.getTag(4)));
					tag5.put(to_string(imgObj.getTag(5)));

					attach(*img);
					attach(*name);
					attach(*data);
					//if there are images in pl (photo library)
				} else {
					img = new Image(Point(300,275), "empty.jpg"); //setting default values

					name = new Text(Point(140,100), "");
					name->set_font_size(25);

					data = new Text(Point(140,125), "");

					tag1.put("");
					tag2.put("");
					tag3.put("");
					tag4.put("");
					tag5.put("");
					attach(*img);
					attach(*name);
					attach(*data);
				}
			}
		
		bool wait_for_button_new_pic();
		bool wait_for_button_next_pic();
		bool wait_for_button_previous_pic();
		bool wait_for_reset_search_button();
		bool wait_for_button_update_tags();
		int index = 0;
		
	private:
	//functions for call backs
		void next();
		void previous();
		void new_pic();
		void tag_search();
		void reset_tag_search();
		void redrawUpdate();
		void quit();
		void update_tags();
//button call backs
		static void cb_next(Address, Address);
		static void cb_previous(Address, Address);
		static void cb_new_pic(Address, Address);
		static void cb_tag_search(Address, Address);
		static void cb_reset_tag_search(Address, Address);
		static void cb_quit(Address, Address);
		static void cb_update_tags(Address, Address);
		
		
		In_box tag1, tag2, tag3, tag4, tag5;
		In_box search;
		Button button_next, button_previous, button_new_pic, button_tag_search, button_reset_search, button_quit, button_update_tags;
		string tags;
		Text *name, *data, *changes_saved;
		imageOutput imgObj;
		Image *img;
		string imgLoc, datastring;
		vector<int> cycleVals;
		//bools
		bool reset_search_button_pushed;
		bool update_tags_button_pushed;
		bool previous_button_pushed;
		bool search_button_pushed;
		bool new_button_pushed;
		bool next_button_pushed;
};

#endif