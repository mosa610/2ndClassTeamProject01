#pragma once

#include "Music.h"
#include "list"

using namespace GameLib;

class MusicManager
{
public:
	MusicManager()
	{
		// music::loadÇçsÇ§
		music::load(SE::AXE, L"Data/Sounds/SE/Axe.wav");
		music::load(SE::CHAINSOW, L"Data/Sounds/SE/Chainsow.wav");
		music::load(SE::FIRE, L"Data/Sounds/SE/Fire.wav");
		music::load(SE::HUMMER, L"Data/Sounds/SE/Hummer.wav");
		music::load(SE::DRILL, L"Data/Sounds/SE/Drill.wav");
		music::load(SE::EXPLOSION, L"Data/Sounds/SE/Explosion_4.wav");
		music::load(SE::RAIN, L"Data/Sounds/SE/Rain.wav");
		music::load(SE::THUNDER, L"Data/Sounds/SE/Thunder.wav");
		music::load(SE::COLLAPSE, L"Data/Sounds/SE/Collapse.wav");
		music::load(SE::ALARM, L"Data/Sounds/SE/Alarm.wav");
		music::load(SE::SELECT, L"Data/Sounds/SE/Select16.wav");


		music::load(BGM::TITLE, L"Data/Sounds/Title/Ozone_AdobeStock_356955431_preview.wav");
		music::load(BGM::GAME, L"Data/Sounds/Music/Free-Power-(Rock)_AdobeStock_680539019_preview.wav");
		music::load(BGM::CLEAR, L"Data/Sounds/GameClear/GameClearMagnificent.wav");
		music::load(BGM::OVER, L"Data/Sounds/GameOver/Game-Lose_AdobeStock_521816765_preview.wav");
		music::load(BGM::RESULT, L"Data/Sounds/Result/FORCE-CONTEST_AdobeStock_452589209_preview.wav");
	}
	~MusicManager() 
	{
		music::clear();
	}

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