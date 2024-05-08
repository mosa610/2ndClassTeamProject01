#pragma once
#include <iostream>
#include "../GameLib/game_lib.h"

#include "list"

using namespace GameLib;

class MusicManager
{
public:
	MusicManager()
	{
		// music::load‚ğs‚¤

	}
	~MusicManager() {}

public:
	void TRG_play(int index, bool isLoop);
	void STATE_play(int index, bool isLoop);
	void Stop(int index);
	void Pause(int index);

public:
	static MusicManager& Instance()
	{
		static MusicManager instance;
		return instance;
	}
};