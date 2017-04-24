#include "overall.h"

int input_img::acceptInput(string loc, vector<string> tag) { //user input and check if exten is valid
	int error = 0;

	this->loc = loc; //location
	this->tag = tag; //tags

	if ((loc.substr(0, 4) == "www." || loc.substr(0, 8) == "https://") || loc.substr(0, 7) == "http://") { //is the file local or from a url
		type = FILE_URL;
	} else {
		type = FILE_LOCAL;
	}

	if (!validExtension(loc)) { //is extension valid?
		return 1;
	}

	setProperties(loc); //attach attributes

	error = save_img(); //copy an image from url or local
	if (error != 0) {
		return error;
	}

	addEntry(); //add image to database

	return 0;
}

void input_img::printInfo() {
	cout << "------\nlocation:\t" << loc << "\nname:\t" << name << "\nextension:\t" << exten << "\ntype:\t" << type << "\n------" << endl;
}

void input_img::addEntry() {
	ofstream pl("pl", ios::app); //adding image an updating tracker pl- photo library
	if (pl.is_open()) {
		pl << getID() << "^" << getName() << "^" << getExtension() << "^" << time(0)-(3600*6) << "^" << getType() << "^" << to_lowercase(getTag(1)) << "^" << to_lowercase(getTag(2)) << "^" << to_lowercase(getTag(3)) << "^" << to_lowercase(getTag(4)) << "^" << to_lowercase(getTag(5)) << "^\n";
	}
}

bool input_img::validExtension(string file) { //checking extension
	int pos = 1;
	string section, ext;
	vector <string>exts = {"jpg", "gif", "jpeg", "bm", "bmp", "pbm", "pgm", "png", "ppm", "xbm", "xpm"};

	while (1) { //search for a period character by character then copy the infor after the period (should be extension)
		try {
			section = file.substr(file.length()-pos, pos);

			if (section.substr(0, 1) == ".") { //record extension
				ext = section.substr(1, section.length() - 1);
				break;
			}
			pos++;
		} catch (exception &e) {
			return 0;
		}
	}

	for (int i = 0; i < exts.size(); ++i) { //handle uppercase and lowercase extensions
		if (to_lowercase(ext) == exts[i]) {
			return 1;
		}
	}
	return 0;
}

void input_img::setProperties(string file) {
	int pos = 1;
	bool ext_found = false;
	string section, ext, name;
	
	while (1) { //find first period again
		try {
			section = file.substr(file.length()-pos, pos);

			if (section.substr(0, 1) == "." && ext_found == false) {
				ext = to_lowercase(section.substr(1, section.length() - 1));

				this->exten = ext;

				ext_found = true;
			}

			if (section.substr(0, 1) == "/" || pos == file.length()) { //record exten for local or url
				if (getType() == FILE_URL) {
					name = section.substr(1, section.length()-ext.length()-2);
				} else {
					name = section.substr(0, section.length()-ext.length()-1);
				}

				if (name[0] == '/') {
					name = name.substr(1, name.length()-1);
				}

				this->name = name;
				break;
			}

			pos++; //if period not found, ++
		} catch (exception &e) {
			cerr << e.what() << endl;
			exit (EXIT_FAILURE);
		}
	}

	id = currentCount(); //make image's "id" the count
}

int input_img::save_img() { //saving image from url or local
	int error = 0;
	string comm;

	if (getType() == FILE_URL) {
		//fake self as browser
		comm = "wget -U 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1.6) Gecko/20070802 SeaMonkey/1.1.4' --no-check-certificate " + getLoc() + " -O images/" + to_string(getID()) + "." + getExtension() + " >/dev/null 2>&1";
	} else  { //local
		comm = "cp " + getLoc() +  " images/" + to_string(getID()) + "." + getExtension() + " >/dev/null 2>&1";
	}

	error = system(comm.c_str());

	if (error != 0 && getType() == FILE_LOCAL) {
		return 3;
	}

	updateCount(); //update the counter

	return 0;
}