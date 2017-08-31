#include "VoiceEin.h"
#include "../../Parameter.h"
#include "DxLib.h"

void VoiceEin::Load() {
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/ein/summon1-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/ein/summon1-2.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/ein/summon1-3.mp3"));
	mVoice[Parameter::VOICE_SUMMON1].push_back(LoadSoundMem("Data/voice/ein/summon1-4.mp3"));

	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/ein/summon2-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/ein/summon2-2.mp3"));
	mVoice[Parameter::VOICE_SUMMON2].push_back(LoadSoundMem("Data/voice/ein/summon2-3.mp3"));

	mVoice[Parameter::VOICE_SUMMON3].push_back(LoadSoundMem("Data/voice/ein/summon3-1.mp3"));
	mVoice[Parameter::VOICE_SUMMON3].push_back(LoadSoundMem("Data/voice/ein/summon3-2.mp3"));

	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack1.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack2.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack3.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack4.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack5.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack6.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack7.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack8.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack9.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack10.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack11.mp3"));
	mVoice[Parameter::VOICE_PATACK].push_back(LoadSoundMem("Data/voice/ein/patack12.mp3"));

	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/ein/matack1.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/ein/matack2.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/ein/matack3.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/ein/matack4.mp3"));
	mVoice[Parameter::VOICE_MATACK].push_back(LoadSoundMem("Data/voice/ein/matack5.mp3"));

	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/ein/damage1-1.mp3"));
	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/ein/damage1-2.mp3"));
	mVoice[Parameter::VOICE_DAMAGE1].push_back(LoadSoundMem("Data/voice/ein/damage1-3.mp3"));

	mVoice[Parameter::VOICE_DAMAGE2].push_back(LoadSoundMem("Data/voice/ein/damage2-1.mp3"));
	mVoice[Parameter::VOICE_DAMAGE2].push_back(LoadSoundMem("Data/voice/ein/damage2-2.mp3"));

	mVoice[Parameter::VOICE_REVERSAL].push_back(LoadSoundMem("Data/voice/ein/reversal1.mp3"));
	mVoice[Parameter::VOICE_REVERSAL].push_back(LoadSoundMem("Data/voice/ein/reversal2.mp3"));

	mVoice[Parameter::VOICE_AFTERDOWN].push_back(LoadSoundMem("Data/voice/ein/afterdown1.mp3"));
	mVoice[Parameter::VOICE_AFTERDOWN].push_back(LoadSoundMem("Data/voice/ein/afterdown3.mp3"));

	mVoice[Parameter::VOICE_AFTERCOMBO].push_back(LoadSoundMem("Data/voice/ein/aftercombo1.mp3"));
	mVoice[Parameter::VOICE_AFTERCOMBO].push_back(LoadSoundMem("Data/voice/ein/aftercombo2.mp3"));

	mVoice[Parameter::VOICE_THROW].push_back(LoadSoundMem("Data/voice/ein/throw.mp3"));
	mVoice[Parameter::VOICE_ESCAPE].push_back(LoadSoundMem("Data/voice/ein/escape2.mp3"));

	mVoice[Parameter::VOICE_JUMP].push_back(LoadSoundMem("Data/voice/ein/jump1.mp3"));

	mVoice[Parameter::VOICE_DASH].push_back(LoadSoundMem("Data/voice/ein/dash1.mp3"));

	mVoice[Parameter::VOICE_BACKSTEP].push_back(LoadSoundMem("Data/voice/ein/backstep1.mp3"));
	mVoice[Parameter::VOICE_BACKSTEP].push_back(LoadSoundMem("Data/voice/ein/backstep2.mp3"));

	mVoice[Parameter::VOICE_BURST].push_back(LoadSoundMem("Data/voice/ein/burst1.mp3"));
	mVoice[Parameter::VOICE_BURST].push_back(LoadSoundMem("Data/voice/ein/burst2.mp3"));

	mVoice[Parameter::VOICE_CD].push_back(LoadSoundMem("Data/voice/ein/cd1.mp3"));
	mVoice[Parameter::VOICE_CD].push_back(LoadSoundMem("Data/voice/ein/cd2.mp3"));

	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/ein/wait.mp3"));
	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/ein/wait2.mp3"));
	mVoice[Parameter::VOICE_WAIT].push_back(LoadSoundMem("Data/voice/ein/wait3.mp3"));
}