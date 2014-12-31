/* �w�b�_�t�@�C�� */
#include "SoundManagerImpl.h"
#include "../Debug/Helper/DebugHelper.h"
#include <SDL.h>


//-------------------------------------------------------------
//!
//! @brief �T�E���h
//! @brief �T�E���h�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sound
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SoundManager::C_SoundManager() :

        // �������
        upImpl_(std::make_unique<C_SoundManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SoundManager::~C_SoundManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �~�L�T�[API���J���������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::Initialize()
    {
        // ����������Ă��Ȃ��ꍇ�A����������
        if (::SDL_WasInit(SDL_INIT_AUDIO) == 0) ::SDL_InitSubSystem(SDL_INIT_AUDIO);

        // �~�L�T�[API���J��
        const int32_t CHUNK_SIZE = 4096;

        if (::Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNK_SIZE) < 0)
        {
            PrintLog("[ C_SoundManager::Initialize ] : �~�b�N�X�I�[�f�B�I���J���̂Ɏ��s���܂����B\n");
            PrintLog("                    �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        // �����Đ�������ݒ�
        ::Mix_AllocateChannels(Channel::s_MAX_COUNT);

        // �I�������̃t���O��������
        upImpl_->SetFinalizeFlag(false);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g��BGM�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::Finalize()
    {
        upImpl_->Finalize();
        upImpl_->SetFinalizeFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̃��[�h���s��
     *  @param  �t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::LoadSoundEffect(const std::string& rFilePath)
    {
        if (upImpl_->LoadSoundEffect(rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̉�����s��
     *  @param  �t�@�C���p�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::ReleaseSoundEffect(const std::string& rFilePath)
    {
        upImpl_->ReleaseSoundEffect(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  �S�ẴT�E���h�G�t�F�N�g�̉�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::AllReleaseSoundEffect()
    {
        upImpl_->AllReleaseSoundEffect();
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̍Đ����s��
     *  @param  �T�E���h�G�t�F�N�g
     *  @param  ���蓖�Ă�`���l��( -1�̏ꍇ�͎������蓖�� )
     *  @param  �Đ���( -1�̏ꍇ�̓��[�v�Đ� )
     *  @param  ���蓖�Ă�ꂽ�`���l�����擾����|�C���^
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::PlaySoundEffect(const SoundEffectPtr& prSoundEffect,
        int32_t allocateChannel,
        int32_t playCount,
        int32_t* pGetAllocateChannel)
    {
        assert(prSoundEffect);

        // �T�E���h�G�t�F�N�g���Đ����A���蓖�Ă�ꂽ�`���l�����擾
        int32_t allocatedChannel = Mix_PlayChannel(allocateChannel, prSoundEffect.get(), playCount);

        if (allocatedChannel == s_ALLOCATE_CHANNEL_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::PlaySoundEffect ] : �`���l���̊��蓖�ĂɎ��s���܂����B\n");
            PrintLog("                         �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        // �|�C���^���ݒ肳��Ă���ꍇ�͊��蓖�Ă�ꂽ�`���l�����擾����
        if (pGetAllocateChannel != nullptr) *pGetAllocateChannel = allocatedChannel;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̃t�F�[�h�C���ł̍Đ����s��
     *  @param  �T�E���h�G�t�F�N�g
     *  @param  ���蓖�Ă�`���l��( -1�̏ꍇ�͎������蓖�� )
     *  @param  �Đ���( -1�̏ꍇ�̓��[�v�Đ� )
     *  @param  �t�F�[�h�C���̎���
     *  @param  ���蓖�Ă�ꂽ�`���l�����擾����|�C���^
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::FadeInPlaySoundEffect(const SoundEffectPtr& prSoundEffect,
        int32_t allocateChannel,
        int32_t playCount,
        int32_t fadeInTime,
        int32_t* pGetAllocateChannel)
    {
        assert(prSoundEffect);

        // �T�E���h�G�t�F�N�g���t�F�[�h�C���ōĐ����A���蓖�Ă�ꂽ�`���l�����擾
        int32_t allocatedChannel = Mix_FadeInChannel(allocateChannel, prSoundEffect.get(), playCount, fadeInTime);

        if (allocatedChannel == s_ALLOCATE_CHANNEL_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::FadeInPlaySoundEffect ] : �`���l���̊��蓖�ĂɎ��s���܂����B\n");
            PrintLog("                               �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        // �|�C���^���ݒ肳��Ă���ꍇ�͊��蓖�Ă�ꂽ�`���l�����擾����
        if (pGetAllocateChannel != nullptr) *pGetAllocateChannel = allocatedChannel;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̈ꎞ��~���s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĈꎞ��~ )
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::PauseSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_Pause(channel);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̍ĂэĐ����s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĈꎞ��~ )
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::ResumeSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_Resume(channel);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̒�~���s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĈꎞ��~ )
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::StopSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_HaltChannel(channel);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̃t�F�[�h�A�E�g�ł̒�~���s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĈꎞ��~ )
     *  @param  �t�F�[�h�A�E�g�̎���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::FadeOutStopSoundEffect(int32_t channel, int32_t fadeOutTime)
    {
        assert(channel < Channel::s_MAX_COUNT);
        assert(fadeOutTime >= 0);

        ::Mix_FadeOutChannel(channel, fadeOutTime);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g���Đ������m�F���s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĈꎞ��~ )
     *  @return �Đ����Ftrue
     *  @return ��~���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::CheckPlayingSoundEffect(int32_t channel)
    {
        if (::Mix_Playing(channel) == 0) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �`���l���̃{�����[���ݒ���s��
     *  @param  �`���l��( -1�̏ꍇ�͂��ׂĐݒ� )
     *  @param  �{�����[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::SetChannelVolume(int32_t channel, int32_t volume)
    {
        assert(channel < Channel::s_MAX_COUNT);

        // �K�؂ȃ{�����[���ɏC������
        upImpl_->RepairAppositeVolume(&volume);

        // �`���l���̃{�����[����ݒ�
        ::Mix_Volume(channel, volume);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̃{�����[���ݒ���s��
     *  @param  �T�E���h�G�t�F�N�g
     *  @param  �{�����[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::SetSoundEffectVolume(const SoundEffectPtr& prSoundEffect, int32_t volume)
    {
        assert(prSoundEffect);

        // �K�؂ȃ{�����[���ɏC������
        upImpl_->RepairAppositeVolume(&volume);

        // �T�E���h�G�t�F�N�g�̃{�����[����ݒ�
        ::Mix_VolumeChunk(prSoundEffect.get(), volume);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̋����̐ݒ���s��
     *  @param  �`���l��
     *  @param  ����( 0���ł��߂��A255���ł����� )
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::SetSoundEffectDistance(int32_t channel, uint8_t distance)
    {
        assert(channel < Channel::s_MAX_COUNT);

        // �K�؂ȋ����ɏC��
        upImpl_->RepairAppositeDistance(&distance);

        // �T�E���h�G�t�F�N�g�̋�����ݒ�
        if (::Mix_SetDistance(channel, distance) == 0)
        {
            PrintLog("[ C_SoundManager::SetSoundEffectDistance ] : �����̐ݒ�Ɏ��s���܂����B\n");
            PrintLog("                                �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̕����Ƌ����̐ݒ���s��
     *  @param  �`���l��
     *  @param  ����( 0���O�A90���E�A180�����A270���� )
     *  @param  ����( 0���ł��߂��A255���ł����� )
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::SetSoundEffectPosition(int32_t channel, int16_t direction, uint8_t distance)
    {
        assert(channel < Channel::s_MAX_COUNT);
        assert(direction >= 0 || direction <= 360);

        // �K�؂ȋ����ɏC��
        upImpl_->RepairAppositeDistance(&distance);

        // �T�E���h�G�t�F�N�g�̕����Ƌ�����ݒ�
        if (::Mix_SetPosition(channel, direction, distance) == 0)
        {
            PrintLog("[ C_SoundManager::SetSoundEffectPosition ] : �����Ƌ����̐ݒ�Ɏ��s���܂����B\n");
            PrintLog("                                �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̃��[�h���s��
     *  @param  �t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::LoadBgm(const std::string& rFilePath)
    {
        if (upImpl_->LoadBgm(rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̉�����s��
     *  @param  �t�@�C�X�p�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::ReleaseBgm(const std::string& rFilePath)
    {
        upImpl_->ReleaseBgm(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGM��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::AllReleaseBgm()
    {
        upImpl_->AllReleaseBgm();
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̍Đ����s��
     *  @param  BGM
     *  @param  �Đ���( -1�̏ꍇ�̓��[�v�Đ� )
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::PlayBgm(const BgmPtr& prBgm, int32_t playCount)
    {
        assert(prBgm);

        // BGM���Đ�
        if (::Mix_PlayMusic(prBgm.get(), playCount) == s_PLAY_BGM_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::PlayBGM ] : BGM�̍Đ��Ɏ��s���܂����B\n");
            PrintLog("                 �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̃t�F�[�h�C���ł̍Đ����s��
     *  @param  BGM
     *  @param  �Đ���( -1�̏ꍇ�̓��[�v�Đ� )
     *  @param  �t�F�[�h�C���̎���
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::FadeInPlayBgm(const BgmPtr& prBgm,
        int32_t playCount,
        int32_t fadeInTime)
    {
        assert(prBgm);

        // BGM���Đ�
        if (::Mix_FadeInMusic(prBgm.get(), playCount, fadeInTime) == s_PLAY_BGM_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::FadeInPlayBGM ] : �t�F�[�h�C���ł̍Đ��Ɏ��s���܂����B\n");
            PrintLog("                       �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̈ꎞ��~���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::PauseBgm()
    {
        // BGM���ꎞ��~
        ::Mix_PauseMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̍ĂэĐ����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::ResumeBgm()
    {
        // BGM���ĂэĐ�
        ::Mix_ResumeMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̒�~���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::StopBgm()
    {
        // BGM���~
        ::Mix_HaltMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̃t�F�[�h�A�E�g�ł̒�~���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::FadeOutStopBgm(int32_t fadeOutTime)
    {
        assert(fadeOutTime >= 0);

        // BGM���t�F�[�h�A�E�g�Œ�~
        ::Mix_FadeOutMusic(fadeOutTime);
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̊����߂��Đ����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::RewindBgm()
    {
        // BGM�������߂��čĐ�
        ::Mix_RewindMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGM���Đ������m�F���s��
     *  @param  �Ȃ�
     *  @return �Đ����Ftrue
     *  @return ��~���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::CheckPlayingBgm()
    {
        if (::Mix_PlayingMusic() == 0) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̃{�����[���ݒ���s��
     *  @param  �{�����[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::SetBgmVolume(int32_t volume)
    {
        // �K�؂ȃ{�����[���ɏC������
        upImpl_->RepairAppositeVolume(&volume);

        // BGM�̃{�����[����ݒ�
        ::Mix_VolumeMusic(volume);
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̊J�n���Ԃ̐ݒ���s��
     *  @param  �J�n����( �b�P�� )
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::SetBgmStartTime(double startTime)
    {
        const int32_t SET_POSITION_ERROR_VALUE = -1;

        if (::Mix_SetMusicPosition(startTime) == SET_POSITION_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::SetBgmStartTime ] : �J�n���Ԃ̐ݒ�Ɏ��s���܂����B\n");
            PrintLog("                         �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g��BGM��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::AllRelease()
    {
        upImpl_->AllRelease();
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̎擾���s��
     *  @param  �t�@�C���p�X
     *  @return �T�E���h�G�t�F�N�g
     *
     ****************************************************************/
    boost::optional<const SoundEffectPtr&> C_SoundManager::GetSoundEffect(const std::string& rFilePath) const
    {
        return upImpl_->GetSoundEffect(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̎擾���s��
     *  @param  �t�@�C���p�X
     *  @return BGM
     *
     ****************************************************************/
    boost::optional<const BgmPtr&> C_SoundManager::GetBgm(const std::string& rFilePath) const
    {
        return upImpl_->GetBgm(rFilePath);
    }
}