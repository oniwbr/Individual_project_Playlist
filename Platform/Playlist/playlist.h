// Copyright 2025 Margarita Kanukova

#ifndef PLATFORM_PLAYLIST_PLAYLIST_H_
#define PLATFORM_PLAYLIST_PLAYLIST_H_
#include <iostream>
#include "/Github/Individual_project_Playlist/Platform/Date/date.h"
#include "/Github/Individual_project_Playlist/Platform/User/user.h"
#include "/Github/Individual_project_Playlist/Platform/Time/ctime.h"
#include "/Github/Individual_project_Playlist/Platform/Song/song.h"

class User;

enum States { Private, Public };
class Playlist {
	std::string _name;
	Date _date_of_creation;
	User* _username;
	int _number_of_songs;
	CTime _druation_of_songs;
	States _state;
	Song** _songs;
};

#endif  // PLATFORM_PLAYLIST_PLAYLIST_H_
