/* �w�b�_�t�@�C�� */
#include "SoundManager.h"
// #include "Common.h"
#include "../Debug/Helper/DebugHelper.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �T�E���h
//! @brief �T�E���h�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sound
{
    namespace
    {
        const int32_t s_ALLOCATE_CHANNEL_ERROR_VALUE = -1;                                               ///< @brief �`���l�����蓖�ẴG���[�l
        const int32_t s_PLAY_BGM_ERROR_VALUE = -1;                                                       ///< @brief BGM�Đ��̃G���[�l
    }

    //-------------------------------------------------------------
    //!
    //! @brief �T�E���h�}�l�[�W���[�C���v�������g
    //! @brief �T�E���h�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_SoundManager::C_SoundManagerImpl
    {
    public:
        C_SoundManagerImpl();                                                                           // �R���X�g���N�^
        ~C_SoundManagerImpl();                                                                          // �f�X�g���N�^
        void Finalize();                                                                                // �I������
        bool LoadSoundEffect(const std::string& rFilePath);                                             // �T�E���h�G�t�F�N�g�̃��[�h����
        void ReleaseSoundEffect(const std::string& rFilePath);                                          // �T�E���h�G�t�F�N�g�̉������
        void AllReleaseSoundEffect();                                                                   // �T�E���h�G�t�F�N�g��S�ĉ��
        bool LoadBgm(const std::string& rFilePath);                                                     // BGM�̃��[�h����
        void ReleaseBgm(const std::string& rFilePath);                                                  // BGM�̉������
        void AllReleaseBgm();                                                                           // BGM��S�ĉ��
        void AllRelease();                                                                              // �T�E���h�G�t�F�N�g��BGM��S�ĉ��
        void RepairAppositeVolume(int32_t* pVolume);                                                    // �K�؂ȃ{�����[���ɏC��
        void RepairAppositeDistance(uint8_t* pDistance);                                                // �K�؂ȋ����ɏC��
        boost::optional<const SoundEffectPtr&> GetSoundEffect(const std::string& rFilePath) const;      // �T�E���h�G�t�F�N�g�̎擾
        boost::optional<const BgmPtr&> GetBgm(const std::string& rFilePath) const;                      // BGM�̎擾
        void SetFinalizeFlag(bool finalizeFlag);                                                        // �I���������s���������f����t���O��ݒ�
    private:
        std::unordered_map<std::string, SoundEffectPtr> pSoundEffects_;                                 ///< @brief �T�E���h�G�t�F�N�g
        std::unordered_map<std::string, BgmPtr> pBgms_;                                                 ///< @brief BGM
        bool finalizeFlag_ = false;                                                                     ///< @brief �I���������s���������f����t���O
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SoundManager::C_SoundManagerImpl::C_SoundManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SoundManager::C_SoundManagerImpl::~C_SoundManagerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g��BGM�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::Finalize()
    {
        // �T�E���h�G�t�F�N�g��BGM��S�ĉ��
        AllRelease();

        // �~�L�T�[API�����
        ::Mix_CloseAudio();
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̃��[�h���s��
     *  @param  �t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::C_SoundManagerImpl::LoadSoundEffect(const std::string& rFilePath)
    {
        // ���ɓ����T�E���h�G�t�F�N�g�����[�h���Ă���ꍇ
        if (pSoundEffects_.find(rFilePath) != pSoundEffects_.end())
        {
            std::cout << "[ C_SoundManagerImpl::LoadSoundEffect ] : ���ɓ����T�E���h�G�t�F�N�g�����[�h���Ă��܂��B" << std::endl;
            std::cout << "                           �t�@�C���p�X : " << rFilePath << std::endl;

            return true;
        }

        // �T�E���h�G�t�F�N�g�����[�h
        SoundEffectPtr pTemporarySoundEffect(Mix_LoadWAV(rFilePath.c_str()),
                                             [](SoundEffect* pSoundEffect){ ::Mix_FreeChunk(pSoundEffect); });

        if (!pTemporarySoundEffect)
        {
            std::cout << "[ C_SoundManagerImpl::LoadSoundEffect ] : �T�E���h�G�t�F�N�g�̃��[�h�Ɏ��s���܂����B" << std::endl;
            std::cout << "                             �G���[���e : " << Mix_GetError() << std::endl;

            return false;
        }

        // �T�E���h�G�t�F�N�g��ێ�����
        pSoundEffects_.emplace(rFilePath, pTemporarySoundEffect);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g�̉�����s��
     *  @param  �t�@�C���p�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::ReleaseSoundEffect(const std::string& rFilePath)
    {
        // �T�E���h�G�t�F�N�g�̓��[�h����Ă��Ȃ��ꍇ
        if (pSoundEffects_.find(rFilePath) == pSoundEffects_.end())
        {
            std::cout << "[ C_SoundManagerImpl::ReleaseSoundEffect ] : �T�E���h�G�t�F�N�g�����[�h����Ă��܂���B" << std::endl;

            return;
        }

        // �T�E���h�G�t�F�N�g�̗v�f���폜
        pSoundEffects_.erase(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllReleaseSoundEffect()
    {
        pSoundEffects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̃��[�h���s��
     *  @param  �t�@�C���̃p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SoundManager::C_SoundManagerImpl::LoadBgm(const std::string& rFilePath)
    {
        // ���ɓ���BGM�����[�h���Ă���ꍇ
        if (pBgms_.find(rFilePath) != pBgms_.end())
        {
            std::cout << "[ C_SoungManagerImpl::LoadBGM ] : ���ɓ���BGM�����[�h���Ă��܂��B" << std::endl;
            std::cout << "                   �t�@�C���p�X : " << rFilePath << std::endl;

            return true;
        }

        // BGM�����[�h
        BgmPtr pTemporaryBgm(::Mix_LoadMUS(rFilePath.c_str()),
            [](Bgm* pBgm){ ::Mix_FreeMusic(pBgm); });

        if (!pTemporaryBgm)
        {
            PrintLog("[ C_SoungManagerImpl::LoadBGM ] : BGM�̃��[�h�Ɏ��s���܂����B\n");
            PrintLog("                     �G���[���e : %s\n", Mix_GetError());

            return false;
        }

        // BGM��ێ�����
        pBgms_.emplace(rFilePath, pTemporaryBgm);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGM�̉�����s��
     *  @param  �t�@�C�X�p�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::ReleaseBgm(const std::string& rFilePath)
    {
        // BGM�����[�h����Ă��Ȃ��ꍇ
        if (pBgms_.find(rFilePath) == pBgms_.end())
        {
            std::cout << "[ C_SoundManagerImpl::ReleaseBGM ] : BGM�����[�h����Ă��܂���B" << std::endl;

            return;
        }

        // BGM�̗v�f���폜
        pBgms_.erase(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGM��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllReleaseBgm()
    {
        pBgms_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g��BGM��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllRelease()
    {
        AllReleaseSoundEffect();
        AllReleaseBgm();
    }


    /*************************************************************//**
     *
     *  @brief  �K�؂ȃ{�����[���ɏC�����s��
     *  @param  �{�����[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::RepairAppositeVolume(int32_t* pVolume)
    {
        assert(pVolume);

        if ((*pVolume) < 0)
        {
            (*pVolume) = 0;
        }
        else if ((*pVolume) > Volume::s_MAXIMUM)
        {
            (*pVolume) = Volume::s_MAXIMUM;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �K�؂ȋ����ɏC�����s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::RepairAppositeDistance(uint8_t* pDistance)
    {
        assert(pDistance);

        if ((*pDistance) < Distance::s_NEAREST)
        {
            (*pDistance) = Distance::s_NEAREST;
        }
        else if ((*pDistance) > Distance::s_FARTHEST)
        {
            (*pDistance) = Distance::s_FARTHEST;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �T�E���h�G�t�F�N�g���擾����
     *  @param  �t�@�C���p�X
     *  @return ���[�h����Ă���ꍇ  �F�T�E���h�G�t�F�N�g
     *  @return ���[�h����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const SoundEffectPtr&> C_SoundManager::C_SoundManagerImpl::GetSoundEffect(const std::string& rFilePath) const
    {
        auto iterator = pSoundEffects_.find(rFilePath);
        if (iterator == pSoundEffects_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  BGM���擾����
     *  @param  �t�@�C���p�X
     *  @return BGM
     *
     ****************************************************************/
    boost::optional<const BgmPtr&> C_SoundManager::C_SoundManagerImpl::GetBgm(const std::string& rFilePath) const
    {
        auto iterator = pBgms_.find(rFilePath);
        if (iterator == pBgms_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s���������f����t���O��ݒ肷��
     *  @param  �I���������s���������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::SetFinalizeFlag(bool finalizeFlag)
    {
        finalizeFlag_ = finalizeFlag;
    }
}