// Header and function definitions
#include "overall.h"

// Get current value of counter
int currentCount() {
	string line;
	int count = 0;
	ifstream current("counter");
	if (current.is_open()) {
		getline(current, line);
		count = stoi(line);
		current.close();
	}
	return count;
}

// Update value of counter-------------------------------------------------------------------------------------
void updateCount() {
	// Get current value of counter
	int count = currentCount();

	// Update value of counter
	++count;

	// Write to file
	ofstream update("counter");
	if (update.is_open()) {
		update << count << endl;
		update.close();
	}
}

// Convert a string to lowercase
string to_lowercase(string str) {
	for (auto i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
//------------------------------------------------------------------------------------------------------------------
imageOutput get_img(int id) {
	ifstream pl("pl");
	string line;
	
	bool found = false;
    imageOutput image;
    vector<string> data;

    if (pl) { //if pl opened successfully
	
    	while (getline(pl, line) && found == false) {
    		int offset = 0, pos = 0;
  
    		while (line.find("^", offset) != string::npos) { //finding info-separating character "^"
    			pos = line.find("^", offset);
				//check for a match; break
    			if (line.substr(offset, pos-offset) != to_string(id) && found == false) {
    				break;
    			}
    			data.push_back(line.substr(offset, pos-offset));
    			offset = pos+1;
    			found = true; //pushback data between info-separating char.
    		}
    	}
    }

	if (found) {
		image.setAttributes(stoi(data[0]), data[1], data[2], stoi(data[3]), stoi(data[4]), vector<string> {data[5], data[6], data[7], data[8], data[9]});
	} else {
		image.setAttributes(0, "", "", 0, 0, vector<string> {"", "", "", "", ""});
	}
	return image;
}
//------------------------------------------------------------------------------------------------------------------
vector<int> search_imgs(string text) { //return it if it matches
	vector<int> results;

	if (text == "") { //dont allow empty searches
		return results;
	}
	vector<string> tags; //get all tags
	int offset = 0, pos = 0;
	
	while (text.find(",", offset) != string::npos) {
		pos = text.find(",", offset);

		tags.push_back(text.substr(offset, pos-offset));
		offset = pos+1;
	}
	tags.push_back(text.substr(offset, text.size()-offset));

	for (auto i = 1; i < currentCount(); ++i) { //go through all images
		imageOutput check = get_img(i);
		for (auto j = 0; j < tags.size(); ++j) {
			if (check.getTag(1) == tags[j] || check.getTag(2) == tags[j] || check.getTag(3) == tags[j] || check.getTag(4) == tags[j] || check.getTag(5) == tags[j]) {
				results.push_back(i); //if any tags match - push_back
			}
		}
	}
	vector<int>::iterator it; 						//remove duplicates if possible
	it = unique(results.begin(), results.end());
	results.resize(distance(results.begin(), it));
	return results;
}
//------------------------------------------------------------------------------------------------------------------
vector<int> default_imgs() {
	vector<int> results;
	for (int a = 1; a < currentCount(); ++a) {
		results.push_back(a);
	}
	return results;
}
//------------------------------------------------------------------------------------------------------------------
void updTags(int id, vector<string> tags) { //updates tags of given image
	stringstream data;
	for (auto i = 1; i < currentCount(); ++i) {
		imageOutput tmp = get_img(i);
		if (i == id) { //update the tags
			data << tmp.getID() << "^" << tmp.getName() << "^" << tmp.getExtension() << "^" << tmp.getDate() << "^" << tmp.getType() << "^" << tags[0] << "^" << tags[1] << "^" << tags[2] << "^" << tags[3] << "^" << tags[4] << "^\n";
		} else {
			data << tmp.getID() << "^" << tmp.getName() << "^" << tmp.getExtension() << "^" << tmp.getDate() << "^" << tmp.getType() << "^" << tmp.getTag(1) << "^" << tmp.getTag(2) << "^" << tmp.getTag(3) << "^" << tmp.getTag(4) << "^" << tmp.getTag(5) << "^\n";
		}
	}
	ofstream pl("pl");
	if (pl.is_open()) {
		pl << data.rdbuf();
	}
}
//-----------------------------------------------------------------------------------------------------------------