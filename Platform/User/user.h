// Copy right 2025 Margarita Kanukova 
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "/Github/Individual_project_Playlist/Platform/Playlist/playlist.h"

class Playlist;

class User {
	std::string _username;
	std::string _password;
	/*Playlist** _favorite;
	Playlist** _created;*/
public:
	User();
	User(const std::string& , const std::string& );
	User(const User&);

	void set_username(const std::string&);
	void set_password(const std::string&);

	const std::string get_username() const noexcept;
	const std::string get_password() const noexcept;

	bool operator==(const User&) const noexcept;

private:
	bool check_correct_username(const std::string&);
	bool check_correct_password(const std::string&);
};

#endif // !USER_H
