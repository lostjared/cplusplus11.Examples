/*
 
  Coded by Jared Bruni (http://lostsidedead.com)
 
   My version of a Stop watch class.
   Wrote this after reading Chapter 3 of "Optimized C++"
   I will use my version of the class for timing my code
 
   You can find the book here:
   https://www.amazon.com/gp/product/1491922060/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1
 
*/
 

#ifndef __STOP_WATCH__H__
#define __STOP_WATCH__H__
#include<iostream>
#include<string>
#include<chrono>


class SystemClock {
public:
	// add any system clock specifics
	SystemClock() {}
	
	// start the timer
	void start() {
		start_time = std::chrono::system_clock::now();
	}
	// stop the timer
	void stop() {
		stop_time = std::chrono::system_clock::now();
		
	}
	// echo time difference
	void echo(std::string name) {
		std::cout << "Stopwatch [" << name << "]\n";
		std::cout << "Timer was active for : " << std::chrono::duration_cast<std::chrono::milliseconds>(stop_time-start_time).count() << " Milliseconds\n";
	}
	
	unsigned long timePassed() {
        auto now = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count();
	}
	
private:
	std::chrono::system_clock::time_point start_time, stop_time;
};

class HighResolutionClock {
public:
	// add any resolution clock specifics
	HighResolutionClock() {}
	// start the timer
	void start() {
		start_time = std::chrono::high_resolution_clock::now();
	}
	// sto the timer
	void stop() {
		stop_time = std::chrono::high_resolution_clock::now();
	}
	// echo difference
	void echo(std::string name) {
		std::cout << "Stopwatch [" << name << "]\n";
		std::cout << "Timer was active for : " << std::chrono::duration_cast<std::chrono::microseconds>(stop_time-start_time).count() << " Microseconds\n";
	}
	
	unsigned long timePassed() {
        auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(now-start_time).count();
	}
	
private:
	std::chrono::high_resolution_clock::time_point start_time, stop_time;

};

// other clock interfaces here..


// Timer template
template<typename T> class StopWatch {
	
public:
	explicit StopWatch(std::string name);
	~StopWatch();
	
	void Start(std::string name);
	void Stop();
	void Echo(std::string name);
	unsigned long TimePassed();
private:
	std::string time_name;
	T clock_interface;
	
};


// Constructor
template<typename T>
StopWatch<T>::StopWatch(std::string name) : time_name(name) {
	Start(name);
}

// Destructor
template<typename T>
StopWatch<T>::~StopWatch() {
	Stop();
}

// Start The tImer
template<typename T>
void StopWatch<T>::Start(std::string name) {
	time_name = name;
	clock_interface.start();
}

// Stop The Timer
template<typename T>
void StopWatch<T>::Stop() {
	clock_interface.stop();
	Echo(time_name);
}
// Echo Difference
template<typename T>
void StopWatch<T>::Echo(std::string name) {
	clock_interface.echo(name);
}

// how many ticks?
template<typename T>
unsigned long StopWatch<T>::TimePassed() {
	return clock_interface.timePassed();
}

#endif