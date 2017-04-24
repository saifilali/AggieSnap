#include "std_lib_facilities_4.h"

class input_img{
	int type = 0, id = 0;
	string loc, exten, name;
	vector<string> tag;
	public:
	
		string getLoc() { return loc; }
		string getName() { return name; }
		string getExtension() { return exten; }
		string getTag(int num) { return tag[(num-1)]; }
		int getID() { return id; }
		int getType() { return type; }
		
		void addEntry();
		int acceptInput(string, vector<string>);
		void printInfo();

	private:
		
		void setProperties(string);
		int save_img();
		bool validExtension(string);
};