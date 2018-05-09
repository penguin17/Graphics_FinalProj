#include "tracking.h"
#include <list>

tracking:: tracking() {
	tracking track;
	track.model =  (0,0,0);
	track.incrmnt = destination / 60;
	track.destination = destination;
	std::list <tracking> trackList;
	
}