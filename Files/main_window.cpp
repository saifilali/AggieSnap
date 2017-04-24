#include "main_window.h"

void viewWindow::cb_next(Address, Address pw) { //making buttons
	reference_to<viewWindow>(pw).next();
}

void viewWindow::cb_previous(Address, Address pw) {
	reference_to<viewWindow>(pw).previous();
}

void viewWindow::cb_quit(Address,Address pw) {
	reference_to<viewWindow>(pw).quit();
}

void viewWindow::cb_update_tags(Address,Address pw) {
	reference_to<viewWindow>(pw).update_tags();
}

void viewWindow::cb_new_pic(Address,Address pw) {
	reference_to<viewWindow>(pw).new_pic();
}

void viewWindow::cb_tag_search(Address,Address pw) {
	reference_to<viewWindow>(pw).tag_search();
}

void viewWindow::cb_reset_tag_search(Address,Address pw) {
	reference_to<viewWindow>(pw).reset_tag_search();
}

//------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::next() {
	if (cycleVals.size() != 0) { //given pictures to search through increment index
		++index;
		if (index>cycleVals.size()-1) {
			index = 0;
		}
		redrawUpdate(); //redraw

		next_button_pushed = true;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::previous() {
	if (cycleVals.size() != 0) { //given pictures to cycle through, decrement by 1
		--index;

		if (index == -1) { //if out of range
			index = cycleVals.size()-1;
		}
		redrawUpdate();

		previous_button_pushed = true;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::new_pic() {
	hide();
	new_button_pushed = true; //go to the next screen
}

//------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::tag_search() {
	tags = to_lowercase(search.get_string()); //filter based on tags
	cycleVals = search_imgs(tags);
	index = 0;

	if (cycleVals.size() == 0) { //detach information
		detach(*img);
		detach(*name);
		detach(*data);
		detach(*changes_saved);

		img = new Image(Point(300,275), "no_results.jpg");
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
	} else {
		redrawUpdate();
	}

	search_button_pushed = true;
	Fl::redraw();
}

void viewWindow::reset_tag_search() { //reset tag search
	search.put(""); //put "" in search box

	cycleVals = default_imgs(); //cycle default images
	if (currentCount() != 1) {
		redrawUpdate();
	} else {
		detach(*img);
		detach(*name);
		detach(*data);
		detach(*changes_saved); //detach info

		img = new Image(Point(300,275), "empty.jpg");

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

	search_button_pushed = false;
	Fl::redraw();
}
//---------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::quit() { //quit
	exit(EXIT_SUCCESS);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void viewWindow::update_tags() {
	if (cycleVals.size() != 0) {
		detach(*changes_saved);

		updTags(index+1, {tag1.get_string(), tag2.get_string(), tag3.get_string(), tag4.get_string(), tag5.get_string()});

		update_tags_button_pushed = true;
		changes_saved = new Text(Point(600,680),"Modified Successfully"); //gui for tag modification button
		changes_saved->set_font_size(35);
		changes_saved->set_color(Color::green);

		attach(*changes_saved);
		Fl::redraw();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------

bool viewWindow::wait_for_button_new_pic() {
    show();
    new_button_pushed = false;
    Fl::run();
    return new_button_pushed;
}


bool viewWindow::wait_for_button_next_pic() {
    next_button_pushed = false;
    return next_button_pushed;
}

bool viewWindow::wait_for_button_previous_pic() {
    previous_button_pushed = false;
    return previous_button_pushed;
}

bool viewWindow::wait_for_reset_search_button() {
	reset_search_button_pushed = false;
	return reset_search_button_pushed;
}

bool viewWindow::wait_for_button_update_tags() {
	update_tags_button_pushed = false;
	return update_tags_button_pushed;
}

//---------------------------------------------------------------------------------------------------------------------------------------
void viewWindow::redrawUpdate() {
	detach(*img);
	detach(*name);
	detach(*data);
	detach(*changes_saved);

	imgObj = get_img(cycleVals[index]);
	imgLoc = "images/" + to_string(imgObj.getID()) + "." + imgObj.getExtension(); //next images info
	img = new Image(Point(140,150), imgLoc);

	img->set_mask(Point(0,0),550,400); //mask image
	name = new Text(Point(190,600), imgObj.getShortName() + "." + imgObj.getExtension()); //get image name
	name->set_font_size(35);
	name->set_color(Color::dark_blue);

	time_t date = imgObj.getDate(); //get image info and show if it was local or url

	if (imgObj.getType() == FILE_LOCAL) {
		datastring = "Locally Uploaded to directory on Date & Time : " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t " + to_string(index+1) + " / " + to_string(cycleVals.size());
	} else {
		datastring = "Downloaded to directory on Date & Time : " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t " + to_string(index+1) + " / " + to_string(cycleVals.size());
	}

	data = new Text(Point(190,635), datastring);
	data->set_font_size(17);

	tag1.put(to_string(imgObj.getTag(1))); //updating tag information
	tag2.put(to_string(imgObj.getTag(2)));
	tag3.put(to_string(imgObj.getTag(3)));
	tag4.put(to_string(imgObj.getTag(4)));
	tag5.put(to_string(imgObj.getTag(5)));

	attach(*img);
	attach(*name);
	attach(*data);
	Fl::redraw();
}