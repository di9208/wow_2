#pragma once
#include "singletonBase.h"

#include <map>
#include <string>
#include <windows.h>

//fmod.hpp 추가
#include "inc/fmod.hpp"

//lib 링크
#pragma comment (lib, "lib/fmodex_vc.lib")

//여유분의 채널 갯수 설정(버퍼)
#define EXTRA_SOUND_CHANNEL 5
#define SOUNDBUFFER 10

//총 사운드 갯수
#define TOTAL_SOUND_CHANNEL SOUNDBUFFER + EXTRA_SOUND_CHANNEL
#define g_pSoundManager soundManager::getSingleton()

using namespace FMOD;

class soundManager : public singletonBase <soundManager>
{
private:
	typedef std::map<std::string, Sound**> arrSounds;
	typedef std::map<std::string, Sound**>::iterator arrSoundsIter;
	typedef std::map<std::string, Channel**> arrChannels;
	typedef std::map<std::string, Channel**>::iterator arrChannelIter;

private:
	System* _system;
	Sound** _sound;

	Channel** _channel;

	arrSounds _mTotalSounds;


public:
	void Setup(void);
	void release(void);

	//사운드 추가
	void addSound(std::string keyName, std::string soundName, bool background = false, bool loop = false);

	//재생
	void play(std::string keyName, float volume);

	//종료
	void stop(std::string keyName);

	//정지
	void pause(std::string keyName);

	//다시 재생
	void resume(std::string keyName);

	//멈춰있니?
	bool isPauseSound(std::string keyName);

	//재생중이니?
	bool isPlaySound(std::string keyName);

	//Fmod 시스템을 갱신
	void update(void);


	soundManager();
	~soundManager();
};

