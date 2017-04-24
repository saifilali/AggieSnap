class imageOutput {
	int id = 0, type = 0, date = 0;
	vector<string> tag;
	string name, extension;

	public:
		void printInfo();
		void setAttributes(int, string, string, int, int, vector<string>);

		string getName() { return name; } //get functions
		string getExtension() { return extension; }
		string getShortName();
		string getTag(int num) { return tag[(num-1)]; }
		int getDate() { return date; }
		int getType() { return type; }
		int getID() { return id; }
};