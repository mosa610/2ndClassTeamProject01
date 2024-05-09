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
		music::load(SE::AX, L"./Data/Sounds/SE/Axe.wav", 1.0f);
		music::load(SE::CHAINSOW, L"./Data/Sounds/SE/Chainsow.wav", 1.0f);
		music::load(SE::FIRER, L"./Data/Sounds/SE/Fire.wav", 1.0f);
		music::load(SE::HUMMER, L"./Data/Sounds/SE/Hummer.wav", 1.0f);
		music::load(SE::DRIL, L"./Data/Sounds/SE/Drill.wav", 1.0f);
		music::load(SE::EXPLOSION, L"./Data/Sounds/SE/Explosion_4.wav", 1.0f);
		music::load(SE::RAIN, L"./Data/Sounds/SE/Rain.wav", 1.0f);
		music::load(SE::THUNDER, L"./Data/Sounds/SE/Thunder.wav", 1.0f);
		music::load(SE::COLLAPSE, L"./Data/Sounds/SE/Collapse.wav", 1.0f);
		music::load(SE::ALARM, L"./Data/Sounds/SE/Alarm.wav", 1.0f);
		music::load(SE::SELECT, L"./Data/Sounds/SE/SelectPush_16.wav", 1.0f);


		music::load(BGM::TITLE, L"./Data/Sounds/Title/Ozone_AdobeStock_356955431_preview.wav");
		music::load(BGM::GAME, L"./Data/Sounds/Music/Free-Power-(Rock)_AdobeStock_680539019_preview.wav", 0.3f);
		music::load(BGM::CLEAR, L"./Data/Sounds/GameClear/GameClearMagnificent.wav");
		music::load(BGM::OVER, L"./Data/Sounds/GameOver/Game-Lose_AdobeStock_521816765_preview.wav");
		music::load(BGM::RESULT, L"./Data/Sounds/Result/FORCE-CONTEST_AdobeStock_452589209_preview.wav");
	}
	~MusicManager();

public:
	void TRG_play(int index, bool isLoop = false);
	void STATE_play(int index, bool isLoop = false);
	void Stop(int index);
	void Pause(int index);

public:
	static MusicManager& Instance()
	{
		static MusicManager instance;
		return instance;
	}
};