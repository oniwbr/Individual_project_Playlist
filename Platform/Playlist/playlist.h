// Copy right 2025 Margarita Kanukova

#ifndef PLAYLIST_H
#define PLAYLIST_H

enum State { Private, Public };
class PLaylist {
	int _id;
	char* _name;
	/*Date _date_of_creation;*/
	/*User* _author;*/
	int _number_of_songs;
	/*Time _druation_of_songs;*/
	State _state;
	/*Song** _songs;*/
};

#endif // !PLAYLIST_H