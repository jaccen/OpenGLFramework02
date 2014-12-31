/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"
#include <SDL_mixer.h>


//-------------------------------------------------------------
//!
//! @brief �T�E���h
//! @brief �T�E���h�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sound
{
    /* �ʖ� */
    using SoundEffect = Mix_Chunk;                                                                                          // SoundEffect�^
    using SoundEffectPtr = std::shared_ptr<SoundEffect>;                                                                    // SoundEffecPtr�^
    using Bgm = Mix_Music;                                                                                                  // Bgm�^
    using BgmPtr = std::shared_ptr<Bgm>;                                                                                    // BgmPtr�^


    namespace
    {
        /* �Đ��̎�� */
        namespace PlayType
        {
            const int32_t s_ONCE = 0;
            const int32_t s_LOOP = -1;
        }

        /* �`���l���֘A */
        namespace Channel
        {
            const int32_t s_MAX_COUNT = 16;
            const int32_t s_AUTO_ALLOCATE = -1;
            const int32_t s_ALL = -1;
        }

        /* �{�����[���֘A */
        namespace Volume
        {
            const int32_t s_MINIMUM = 0;
            const int32_t s_MAXIMUM = MIX_MAX_VOLUME;
        }

        /* ���� */
        namespace Distance
        {
            const uint8_t s_NEAREST = 0;
            const uint8_t s_FARTHEST = 255;
        }

        /* ���� */
        namespace Direction
        {
            const int16_t s_FRONT = 0;
            const int16_t s_RIGHT = 90;
            const int16_t s_BACK = 180;
            const int16_t s_LEFT = 270;
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �T�E���h�}�l�[�W���[
    //! @brief �T�E���h���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_SoundManager : public Singleton::C_Singleton<C_SoundManager>
    {
        friend C_Singleton<C_SoundManager>;                                                                                 // �V���O���g���N���X���t�����h��
    public:
        bool Initialize();                                                                                                  // ����������
        void Finalize();                                                                                                    // �I������
        bool LoadSoundEffect(const std::string& rFilePath);                                                                 // �T�E���h�G�t�F�N�g�̃��[�h����
        void ReleaseSoundEffect(const std::string& rFilePath);                                                              // �T�E���h�G�t�F�N�g�̉������
        void AllReleaseSoundEffect();                                                                                       // �S�ẴT�E���h�G�t�F�N�g�����
        bool PlaySoundEffect(const SoundEffectPtr& prSoundEffect,                                                           // �T�E���h�G�t�F�N�g���Đ�
                             int32_t allocateChannel = Channel::s_AUTO_ALLOCATE,
                             int32_t playCount = PlayType::s_ONCE,
                             int32_t* pGetAllocateChannel = nullptr);
        bool FadeInPlaySoundEffect(const SoundEffectPtr& prSoundEffect,                                                     // �T�E���h�G�t�F�N�g���t�F�[�h�C���ōĐ�
                                   int32_t allocateChannel = Channel::s_AUTO_ALLOCATE,
                                   int32_t playCount = PlayType::s_ONCE,
                                   int32_t fadeInTime = 1000,
                                   int32_t* pGetAllocateChannel = nullptr);
        void PauseSoundEffect(int32_t channel = Channel::s_ALL);                                                            // �T�E���h�G�t�F�N�g���ꎞ��~
        void ResumeSoundEffect(int32_t channel = Channel::s_ALL);                                                           // �T�E���h�G�t�F�N�g���ĂэĐ�
        void StopSoundEffect(int32_t channel = Channel::s_ALL);                                                             // �T�E���h�G�t�F�N�g���~
        void FadeOutStopSoundEffect(int32_t channel = Channel::s_ALL, int32_t fadeOutTime = 1000);                          // �T�E���h�G�t�F�N�g���t�F�[�h�A�E�g�Œ�~
        bool CheckPlayingSoundEffect(int32_t channel = Channel::s_ALL);                                                     // �T�E���h�G�t�F�N�g���Đ������m�F
        void SetChannelVolume(int32_t channel = Channel::s_ALL, int32_t volume = Volume::s_MAXIMUM);                        // �`���l���̃{�����[����ݒ�
        void SetSoundEffectVolume(const SoundEffectPtr& prSoundEffect, int32_t volume = Volume::s_MAXIMUM);                 // �T�E���h�G�t�F�N�g�̃{�����[����ݒ�
        bool SetSoundEffectDistance(int32_t channel, uint8_t distance = Distance::s_NEAREST);                               // �T�E���h�G�t�F�N�g�̋�����ݒ�
        bool SetSoundEffectPosition(int32_t channel,                                                                        // �T�E���h�G�t�F�N�g�̕����Ƌ�����ݒ�
                                    int16_t direction = Direction::s_FRONT,
                                    uint8_t distance = Distance::s_NEAREST);
        bool LoadBgm(const std::string& rFileName);                                                                         // BGM�̃��[�h����
        void ReleaseBgm(const std::string& rId);                                                                            // BGM�̉������
        void AllReleaseBgm();                                                                                               // �S�Ă�BGM�����
        bool PlayBgm(const BgmPtr& prBgm, int32_t playCount = PlayType::s_ONCE);                                            // BGM���Đ�
        bool FadeInPlayBgm(const BgmPtr& prBgm,                                                                             // BGM���t�F�[�h�C���ōĐ�
                           int32_t playCount = PlayType::s_ONCE,
                           int32_t fadeInTime = 1000);
        void PauseBgm();                                                                                                    // BGM���ꎞ��~
        void ResumeBgm();                                                                                                   // BGM���ĂэĐ�
        void StopBgm();                                                                                                     // BGM���~
        void FadeOutStopBgm(int32_t fadeOutTime = 1000);                                                                    // BGM���t�F�[�h�A�E�g�Œ�~
        void RewindBgm();                                                                                                   // BGM�������߂��čĐ�
        bool CheckPlayingBgm();                                                                                             // BGM���Đ������m�F
        void SetBgmVolume(int32_t volume = Volume::s_MAXIMUM);                                                              // BGM�̃{�����[����ݒ�
        bool SetBgmStartTime(double startTime);                                                                             // BGM�̊J�n���Ԃ�ݒ�
        void AllRelease();                                                                                                  // �T�E���h�G�t�F�N�g��BGM��S�ĉ��
        boost::optional<const SoundEffectPtr&> GetSoundEffect(const std::string& rFilePath) const;                          // �T�E���h�G�t�F�N�g���擾
        boost::optional<const BgmPtr&> GetBgm(const std::string& rFilePath) const;                                          // BGM���擾
    private:
        /* �O���錾 */
        class C_SoundManagerImpl;

        std::unique_ptr<C_SoundManagerImpl> upImpl_;                                                                        ///< @brief �������

        C_SoundManager();                                                                                                   // �R���X�g���N�^
        ~C_SoundManager() override;                                                                                         // �f�X�g���N�^
    };
}