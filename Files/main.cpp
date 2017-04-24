#include "graph.h"
#include "main_window.h"
#include "start_window.h"

using namespace Graph_lib;

int main() {
	try {
		bool win_next = false;
		bool view_win_next = true;
		int show_wind = 0;
		//1 viewing image/ 0 adding image
	  
		while (win_next || view_win_next) { //loop until button or window closes

			if (win_next) {
				show_wind = 1;
			}

			if (view_win_next) {
				show_wind = 0;
			}
			
			win_next = false;
			view_win_next = false;
			
			if (show_wind == 0) {
				addWindow addWin;
				addWin.show();
				win_next = addWin.wait_for_button_view_pic();
			} else if (show_wind == 1) {
				viewWindow viewWin;
				viewWin.show();
				view_win_next = viewWin.wait_for_button_new_pic();
			} 
		}
		return 0;
	//catches
	} 
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
		
	return 1;
} catch (...) {
	cerr << "Error: Some exception" << endl;
		
	return 2;
}
}