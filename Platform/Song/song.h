//Copy right 2025 Margarita Kanukova
#ifndef SONG_H
#define SONG_H
#include <iostream>
#include "\Github\Individual_project_Playlist\Platform\Time\ctime.h"

class Song {
	std::string _name;
	std::string _author;
	CTime _duration_of_song;
	std::string _album;
};
#endif // !SONG_H