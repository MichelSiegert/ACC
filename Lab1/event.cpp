#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>     
#include <random>

using namespace std;
//this is only necessary for getting random time points.
std::chrono::seconds generateRandomDuration() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 86400*4000);
	int randomSeconds = dis(gen);
	return std::chrono::seconds(randomSeconds);
}

// Function to generate a random time_point
std::chrono::system_clock::time_point generateRandomTimePoint() {
	return std::chrono::system_clock::now() - generateRandomDuration();
}

enum EventTypes 
{
	birthdays,
	bank_holidays,
	todo_reminders,
	repeating
};

class Event {
  public:             
	string name;
	EventTypes type;
	std::chrono::system_clock::time_point beginningDate;
	std::chrono::system_clock::time_point endingDate;
   bool operator<(Event other) const { return beginningDate < other.beginningDate;}
   bool isType(EventTypes other_type){
		return this->type == other_type;
	}
	bool isBetween(	std::chrono::system_clock::time_point start, std::chrono::system_clock::time_point end){
		return start < this->beginningDate  && this->beginningDate < end ||
		start < this-> endingDate  && this->endingDate < end;
	}
	friend std::ostream& operator<<(std::ostream& os, const Event& obj) {
		const auto time =  (std::chrono::system_clock::to_time_t(obj.beginningDate));
		os << obj.name << ": " << obj.type << ", " <<  std::ctime(&time);
		return os;
	}
};

int main() {  
	vector<Event> events{};
	vector<Event> birthdayEvents{};
	vector<Event> timedElements{};

	// Create 40 events, 10 of each type.
	for (int i = 0; i < 10; i++ ) {
		Event event;
		event.name = "Event " + std::to_string(i +  1);
		event.beginningDate = generateRandomTimePoint();
		event.endingDate = generateRandomTimePoint();
		event.type = repeating;
		events.push_back(event);
	}
	for (int i = 0; i < 10; i++ ) {
		Event event;
		event.name = "Event " + std::to_string(i +  11);
		event.beginningDate = generateRandomTimePoint();
		event.endingDate = generateRandomTimePoint();
		event.type = birthdays;
		events.push_back(event);
	}
	for (int i = 0; i < 10; i++ ) {
		Event event;
		event.name = "Event " + std::to_string(i +  21);
		event.beginningDate = generateRandomTimePoint();
		event.endingDate = generateRandomTimePoint();
		event.type = todo_reminders;
		events.push_back(event);
	}
	for (int i = 0; i < 10; i++ ) {
		Event event;
		event.name = "Event " + std::to_string(i +  31);
		event.beginningDate = generateRandomTimePoint();
		event.endingDate = generateRandomTimePoint();
		event.type = birthdays;
		events.push_back(event);
	}
	std::sort(events.begin(), events.end());
	for(const Event& event: events){
		cout << event << endl;
		}
		cout << "--------------------" << endl <<"Birthdays: " << endl;
	std::copy_if(events.begin(), events.end(), std::back_inserter(birthdayEvents),[](Event& e){
		return e.isType(birthdays);
	});
		for(const Event& event: birthdayEvents){
		cout << event << endl;
		}
		cout << "--------------------" << endl <<"Time Based: " << endl;
		
	std::chrono::system_clock::time_point start = generateRandomTimePoint();
	std::chrono::system_clock::time_point end = generateRandomTimePoint();
	std::copy_if(events.begin(), events.end(), std::back_inserter(timedElements), [start, end](Event& e){
		return e.isBetween(start, end);
	});
	for(const Event& event: timedElements){
		cout << event << endl;
		}
  return 0;
}