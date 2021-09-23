#pragma once

class room {
	std::string room_name;
public:
	room(const std::string& room_name_ = std::string()) : room_name(room_name_) {}
};

class speaker {
	std::string speaker_name;
public:
	speaker(const std::string& speaker_name_ = std::string()) : speaker_name(speaker_name_) {}
	
	operator std::string() const {
		return speaker_name;
	}
};


class attendencees {
	std::vector<std::string> attendencees_data;
public:
	/*
	attendencees(const std::vector<speaker>& n) {
		for (const std::string& s : n) {
			attendencees_data.push_back(s);
		}
	}
	*/
	
	attendencees(const std::vector<speaker>& attendencees_data_ = std::vector<speaker>()) {
		for (const auto& a : attendencees_data_) {
			attendencees_data.push_back(a);
		}
	}
	
};

// NO DI
class cppcon_talk {
private: /*Tightly coupled*/
	room room_{"hamar 1"};
	speaker speaker_{"David"};
	attendencees attendencees_{};
};

// DI

class cppcon_talk_DI {
public:
	cppcon_talk_DI(int ii, room&& r, std::unique_ptr<speaker> s, attendencees a) : i(ii), room_(r), attendencees_(a) {
		speaker_ = std::move(s);
	}
private:
	int i;
	room room_{};
	std::unique_ptr<speaker> speaker_{};
	attendencees attendencees_{};
};

class A {
public:
	A(std::string s) {
		assert(s == "David");
	}
};