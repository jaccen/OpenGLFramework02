/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"
#include <chrono>
#include <functional>


//-------------------------------------------------------------
//!
//! @brief �^�C�}�[
//! @brief �^�C�}�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Timer
{
    namespace
    {
        /* �f�t�H���g */
        namespace Default
        {
            const int16_t s_FPS = 60;
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �^�C���}�l�[�W���[
    //! @brief �^�C�}�[���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_TimeManager : public Singleton::C_Singleton<C_TimeManager>
    {
        friend C_Singleton<C_TimeManager>;                                  //�V���O���g���N���X���t�����h��
    public:
        void Initialize();                                                  // ����������
        void Update();                                                      // �X�V����
        float MeasureProcess(const std::function<void()>& rFunction);       // �������x���v��
        void EnableFrameSkip(bool validFlag = true);                        // �t���[���X�L�b�v��L����
        int16_t GetFps() const;                                             // FPS���擾
        float GetNowFps() const;                                            // ���݂�FPS���擾
        float GetTime() const;                                              // �v���O�������J�n���Ă���̎��Ԃ��擾
        float GetDeltaTime() const;                                         // 1�t���[���̍���( �o�� )���Ԃ��擾
        uint32_t GetFrameCount() const;                                     // �Q�[�����J�n���Ă���o�߂����t���[�������擾
        bool IsDrawFlag() const;                                            // �`��t���O���擾
        float GetTimeScale() const;                                         // ���Ԃ̃X�P�[�����擾
        void SetFps(int16_t fps = Default::s_FPS);                          // FPS��ݒ�
        void SetTimeScale(float timeScale = 1.0f);                          // ���Ԃ̃X�P�[����ݒ�
        void SetWaitFlag(bool waitFlag = true);                             // �ҋ@���������邩���f����t���O��ݒ�
    private:
        /* �O���錾 */
        class C_TimeManagerImpl;

        std::unique_ptr<C_TimeManagerImpl> upImpl_;                         ///< @brief �������

        C_TimeManager();                                                    // �R���X�g���N�^
        ~C_TimeManager() override;                                          // �f�X�g���N�^
    };
}