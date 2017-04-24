#ifndef ADDWINDOW_H_
#define ADDWINDOW_H_

#include "std_lib_facilities_4.h"
#include "window.h"
#include "graph.h"
#include "gui.h"
using namespace Graph_lib;

struct addWindow : Graph_lib::Window {
	public:
		addWindow():
			Window(Point(0,0),800,200,"Welcome to AGGIESNAP"), //positioning text and tags in the window
			view_button_pushed(false),
			error(4),
			Url(Point(150,18),400,25,"Enter URL/File Name"),
			tag1(Point(150,48),150,25,"Photo Tags:  Tag #01"),
			tag2(Point(150,78),150,25,"Tag #02"),
			tag3(Point(150,108),150,25,"Tag #03"),
			tag4(Point(150,138),150,25,"Tag #04"),
			tag5(Point(150,168),150,25,"Tag #05"),

			button_add_pic(Point(570,18),100,25,"Upload",cb_add_pic),
			button_view_pic(Point(680,18),100,25,"Browse",cb_view_pic),
			button_quit(Point(650,168),100,25,"Quit",cb_quit)
			{
				//attaching buttons and in/out_boxes  
				attach(button_add_pic);
				attach(button_quit);
				attach(button_view_pic);
				attach(Url);
				attach(tag1);
				attach(tag2);
				attach(tag3);
				attach(tag4);
				attach(tag5);

				// Default empty message
				msg = new Text(Point(40,180),"");
				attach(*msg);
			}
			
			bool wait_for_button_view_pic();
			
	private:
		static void cb_add_pic(Address,Address); 
		static void cb_view_pic(Address,Address);
		static void cb_quit(Address,Address);
		void displayError(int);
		
		void add_pic();
		void view_pic();
		void quit();
		
		bool view_button_pushed;
		Text *msg;
		int error;
		In_box Url,tag1,tag2,tag3,tag4,tag5;
		Button button_add_pic,button_view_pic,button_quit;
		string output, first_tag, second_tag, third_tag, fourth_tag, fifth_tag;
};	
#endif