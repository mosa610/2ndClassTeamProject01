#include "MusicManager.h"

MusicManager::~MusicManager()
{
	
}


void MusicManager::TRG_play(int index, bool isLoop)
{
	music::play(index, isLoop);
}

void MusicManager::STATE_play(int index, bool isLoop)
{
	if (GameLib::music::getState(index) == 0)
		music::play(index, isLoop);

	music::resume(index);
}

void MusicManager::Stop(int index)
{
	music::stop(index);
}

void MusicManager::Pause(int index)
{
	music::pause(index);
}