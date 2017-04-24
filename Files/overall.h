#include "std_lib_facilities_4.h"
#include "input_img.h"
#include "output_img.h"
#include <fstream>
#include <cstring>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

imageOutput get_img(int);

vector<int> default_imgs();

enum { FILE_LOCAL, FILE_URL };

int currentCount();
void updateCount();

string to_lowercase(string); //make string lowercase
vector<int> search_imgs(string);
//update tags
void updTags(int, vector<string>);