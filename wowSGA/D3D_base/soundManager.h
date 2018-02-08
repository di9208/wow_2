#pragma once
#include "singletonBase.h"

#include <map>
#include <string>
#include <windows.h>

//fmod.hpp �߰�
#include "inc/fmod.hpp"

//lib ��ũ
#pragma comment (lib, "lib/fmodex_vc.lib")

//�������� ä�� ���� ����(����)
#define EXTRA_SOUND_CHANNEL 5
#define SOUNDBUFFER 10

//�� ���� ����
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

	//���� �߰�
	void addSound(std::string keyName, std::string soundName, bool background = false, bool loop = false);

	//���
	void play(std::string keyName, float volume);

	//����
	void stop(std::string keyName);

	//����
	void pause(std::string keyName);

	//�ٽ� ���
	void resume(std::string keyName);

	//�����ִ�?
	bool isPauseSound(std::string keyName);

	//������̴�?
	bool isPlaySound(std::string keyName);

	//Fmod �ý����� ����
	void update(void);


	soundManager();
	~soundManager();
};

