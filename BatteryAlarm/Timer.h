#pragma once

struct Timer
{
public:
	int id;
	int duration;
	Timer() :id(0), duration(0) {}
	Timer(int id, int duration) :id(id), duration(duration) {}
};