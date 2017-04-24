#include "start_window.h"
#include "input_img.h"

void addWindow::cb_add_pic(Address,Address pw) //callback functions
{
	reference_to<addWindow>(pw).add_pic() ;
}

void addWindow::cb_view_pic(Address,Address pw)
{
	reference_to<addWindow>(pw).view_pic() ;
}

void addWindow::cb_quit(Address,Address pw)
{
	reference_to<addWindow>(pw).quit() ;
}
//callback actions-------------------------------------------------------------------------------------------------------------------------------------
void addWindow::add_pic() //add picture to photo lib
{
	input_img image;
	
	error = image.acceptInput(Url.get_string(), vector<string> {tag1.get_string(), tag2.get_string(), tag3.get_string(), tag4.get_string(), tag5.get_string()});

	displayError(error);
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void addWindow::displayError(int errorNum) { //display err msg and detach previous one
	string msgContent;

	detach(*msg);
//image uploaded and the fields are reset or something went wrong and an error message will display base don what it was-----------------------------------
	if (errorNum == 0) {
		msg = new Text(Point(320,108),"Image Uploaded Successfully!");
		msg->set_color(Color::dark_green);
		msg->set_font_size(18);

		Url.put(""); //reset input boxes
		tag1.put("");
		tag2.put("");
		tag3.put("");
		tag4.put("");
		tag5.put("");

	} else {
		if (errorNum == 1) {
			msg = new Text(Point(320, 108), "Uploading Fail : Invalid extension. Try again!");
		} else if (errorNum == 2) {
			msg = new Text(Point(320, 108), "Uploading Fail : Invalid URL. Try again!");
		} else if (errorNum == 3) {
			msg = new Text(Point(320, 108), "Uploading Fail : Invalid Local image. Try again!");
		} else if (errorNum == 4) {
			msg = new Text(Point(320, 108), "Unknown Error, please try again!");
		}
		msg->set_color(Color::dark_red);
		msg->set_font_size(18);
	}
	attach(*msg);
	Fl::redraw();
}
//------------------------------------------------------------------------------------------------------------------------------------------------

bool addWindow::wait_for_button_view_pic() //wait until user presses button
{
    show();
    view_button_pushed = false;
    Fl::run();
    return view_button_pushed;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void addWindow::view_pic() { //go to main window when button pushed
	hide();
	view_button_pushed = true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void addWindow::quit() { //quit button leaves the program
	exit(EXIT_SUCCESS);
}
