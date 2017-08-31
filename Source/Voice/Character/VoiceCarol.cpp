#include "VoiceCarol.h"
#include "../../Parameter.h"
#include "DxLib.h"

void VoiceCarol::Load() {
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/carol/summon1-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/carol/summon1-2.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/carol/summon1-3.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/carol/summon1-4.mp3"));

	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/carol/summon2-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/carol/summon2-2.mp3"));
	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/carol/summon2-3.mp3"));

	mVoice[Parameter::VOICE_SUMMON3].push_back(LoadSoundMem("Data/voice/carol/summon3-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON3].push_back(LoadSoundMem("Data/voice/carol/summon3-2.mp3"));

	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack1.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack2.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack3.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack4.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack5.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack6.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack7.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack8.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack9.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack10.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack11.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/carol/patack12.mp3"));

	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/carol/matack1.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/carol/matack2.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/carol/matack3.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/carol/matack4.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/carol/matack5.mp3"));

	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/carol/damage1-1.mp3"));
	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/carol/damage1-2.mp3"));
	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/carol/damage1-3.mp3"));

	mVoice[Parameter::VOICE_DAMAGE2].push_back(LoadSoundMem("Data/voice/carol/damage2-1.mp3"));
	mVoice[Parameter::VOICE_DAMAGE2].push_back(LoadSoundMem("Data/voice/carol/damage2-2.mp3"));

	mVoice[Parameter::VOICE_REVERSAL].push_back(LoadSoundMem("Data/voice/carol/reversal1.mp3"));
	mVoice[Parameter::VOICE_REVERSAL].push_back(LoadSoundMem("Data/voice/carol/reversal2.mp3"));

	mVoice[Parameter::VOICE_AFTERDOWN].push_back(LoadSoundMem("Data/voice/carol/afterdown1.mp3"));
	mVoice[Parameter::VOICE_AFTERDOWN].push_back(LoadSoundMem("Data/voice/carol/afterdown3.mp3"));

	mVoice[Parameter::VOICE_AFTERCOMBO].push_back(LoadSoundMem("Data/voice/carol/aftercombo1.mp3"));
	mVoice[Parameter::VOICE_AFTERCOMBO].push_back(LoadSoundMem("Data/voice/carol/aftercombo2.mp3"));

	mVoice[Parameter::VOICE_THROW].push_back(LoadSoundMem("Data/voice/carol/throw.mp3"));
	mVoice[Parameter::VOICE_ESCAPE].push_back(LoadSoundMem("Data/voice/carol/escape2.mp3"));

	mVoice[Parameter::VOICE_JUMP].push_back(LoadSoundMem("Data/voice/carol/jump1.mp3"));

	mVoice[Parameter::VOICE_DASH].push_back(LoadSoundMem("Data/voice/carol/dash1.mp3"));

	mVoice[Parameter::VOICE_BACKSTEP].push_back(LoadSoundMem("Data/voice/carol/backstep1.mp3"));
	mVoice[Parameter::VOICE_BACKSTEP].push_back(LoadSoundMem("Data/voice/carol/backstep2.mp3"));

	mVoice[Parameter::VOICE_BURST].push_back(LoadSoundMem("Data/voice/carol/burst1.mp3"));
	mVoice[Parameter::VOICE_BURST].push_back(LoadSoundMem("Data/voice/carol/burst2.mp3"));

	mVoice[Parameter::VOICE_CD].push_back(LoadSoundMem("Data/voice/carol/cd1.mp3"));
	mVoice[Parameter::VOICE_CD].push_back(LoadSoundMem("Data/voice/carol/cd2.mp3"));

	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/carol/wait.mp3"));
	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/carol/wait2.mp3"));
	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/carol/wait3.mp3"));
}