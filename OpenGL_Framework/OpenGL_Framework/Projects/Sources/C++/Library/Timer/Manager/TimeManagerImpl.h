/* �w�b�_�t�@�C�� */
#include "TimeManager.h"
#include <thread>
#include <chrono>


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
        const int16_t s_AVERAGE_SAMPLE_NUMBER = 30;                                         ///< @brief ���ς��v�Z����T���v����
        const int32_t s_ONE_TOUSAND_MILLISECONDS = 1000;                                    ///< @brief 1000�~���b( 1�b )
        const float s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS = 0.001f;                         ///< @brief 1000�~���b�̋t��
    }


    //-------------------------------------------------------------
    //!
    //! @brief �^�C���}�l�[�W���[�C���v�������g
    //! @brief �^�C�}�[�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_TimeManager::C_TimeManagerImpl
    {
    public:
        C_TimeManagerImpl();                                                                // �R���X�g���N�^
        ~C_TimeManagerImpl();                                                               // �f�X�g���N�^
        void Initialize();                                                                  // ����������
        void Update();                                                                      // �X�V����
        void EnableFrameSkip(bool validFlag);                                               // �t���[���X�L�b�v��L����
        int16_t GetFps() const;                                                             // FPS���擾
        float GetNowFps() const;                                                            // ���݂�FPS���擾
        uint64_t GetTime() const;                                                           // �v���O�������J�n���Ă���̎��Ԃ��擾
        uint64_t GetDeltaTime() const;                                                      // 1�t���[���̍���( �o�� )���Ԃ��擾
        uint32_t GetFrameCount() const;                                                     // �t���[�����̃J�E���^���擾
        bool IsDrawFlag() const;                                                            // �`��t���O���擾
        float GetTimeScale() const;                                                         // ���Ԃ̃X�P�[�����擾
        void SetFps(int16_t fps);                                                           // FPS��ݒ�
        void SetTimeScale(float timeScale);                                                 // ���Ԃ̃X�P�[����ݒ�
        void SetWaitFlag(bool waitFlag);                                                    // �ҋ@���������邩���f����t���O
    private:
        /* �^�ϊ� */
        using Milliseconds = std::chrono::milliseconds;                                     // Milliseconds�^��錾

        std::chrono::time_point<std::chrono::system_clock> startTimePoint_;                 ///< @brief �J�n���̃^�C���|�C���g
        uint64_t startTime_ = 0;                                                            ///< @brief ����J�n����
        uint64_t endTime_ = 0;                                                              ///< @brief ����I������
        uint64_t deltaTime_ = 0;                                                            ///< @brief ��������
        int32_t loopCount_ = 1;                                                             ///< @brief ���[�v�̉񐔂𐔂���J�E���^
        uint32_t frameCount_ = 1;                                                           ///< @brief �t���[�����̃J�E���^
        int16_t fps_ = Default::s_FPS;                                                      ///< @brief FPS
        float nowFps_ = 0.0;                                                                ///< @brief ���݂�FPS
        bool drawFlag_ = true;                                                              ///< @brief �`��𔻒f����t���O
        bool frameSkipFlag_ = true;                                                         ///< @brief �t���[���X�L�b�v���s�������f����t���O
        float timeScale_ = 1.0;                                                             ///< @brief ���Ԃ̃X�P�[��
        bool waitFlag_ = true;                                                              ///< @brief �ҋ@���������邩���f����t���O

        void Wait();                                                                        // �ҋ@����
        void Calculate();                                                                   // �v�Z����
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TimeManager::C_TimeManagerImpl::C_TimeManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TimeManager::C_TimeManagerImpl::~C_TimeManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Initialize()
    {
        // �J�n���̃^�C���|�C���g���擾
        startTimePoint_ = std::chrono::high_resolution_clock::now();

        // ����J�n���Ԃ��擾
        startTime_ = GetTime();
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Update()
    {
        // �ҋ@����
        Wait();

        // �v�Z����
        Calculate();
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���X�L�b�v��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::EnableFrameSkip(bool validFlag)
    {
        frameSkipFlag_ = validFlag;
        if (frameSkipFlag_ == false) drawFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  FPS���擾����
     *  @param  �Ȃ�
     *  @return FPS
     *
     ****************************************************************/
    int16_t C_TimeManager::C_TimeManagerImpl::GetFps() const
    {
        return fps_;
    }


    /*************************************************************//**
     *
     *  @brief  ���݂�FPS���擾����
     *  @param  �Ȃ�
     *  @return ���݂�FPS
     *
     ****************************************************************/
    float C_TimeManager::C_TimeManagerImpl::GetNowFps() const
    {
        return nowFps_;
    }


    /*************************************************************//**
     *
     *  @brief  �v���O�������J�n���Ă���̎��Ԃ��擾����
     *  @param  �Ȃ�
     *  @return �v���O�������J�n���Ă���̎���
     *
     ****************************************************************/
    uint64_t C_TimeManager::C_TimeManagerImpl::GetTime() const
    {
        return std::chrono::duration_cast<Milliseconds>(std::chrono::high_resolution_clock::now() - startTimePoint_).count();
    }


    /*************************************************************//**
     *
     *  @brief  1�t���[���̍���( �o�� )���Ԃ��擾����
     *  @param  �Ȃ�
     *  @return ��������( �b�P�� )
     *
     ****************************************************************/
    uint64_t C_TimeManager::C_TimeManagerImpl::GetDeltaTime() const
    {
        return deltaTime_;
    }


    /*************************************************************//**
     *
     *  @brief  �t���[�����̃J�E���^���擾����
     *  @param  �Ȃ�
     *  @return �t���[�����̃J�E���^
     *
     ****************************************************************/
    uint32_t C_TimeManager::C_TimeManagerImpl::GetFrameCount() const
    {
        return frameCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �`��t���O���擾����
     *  @param  �Ȃ�
     *  @return �`��t���O
     *
     ****************************************************************/
    bool C_TimeManager::C_TimeManagerImpl::IsDrawFlag() const
    {
        return drawFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ���Ԃ̃X�P�[�����擾����
     *  @param  �Ȃ�
     *  @return ���Ԃ̃X�P�[��
     *
     ****************************************************************/
    float C_TimeManager::C_TimeManagerImpl::GetTimeScale() const
    {
        return timeScale_;
    }


    /*************************************************************//**
     *
     *  @brief  FPS��ݒ肷��
     *  @param  FPS
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetFps(int16_t fps)
    {
        assert(fps > 0);

        fps_ = fps;
    }


    /*************************************************************//**
     *
     *  @brief  ���Ԃ̃X�P�[����ݒ肷��
     *  @param  ���Ԃ̃X�P�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetTimeScale(float timeScale)
    {
        timeScale_ = timeScale;
    }


    /*************************************************************//**
     *
     *  @brief  �ҋ@���������邩���f����t���O��ݒ肷��
     *  @param  �ҋ@���������邩���f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetWaitFlag(bool waitFlag)
    {
        waitFlag_ = waitFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �ҋ@�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Wait()
    {
        // �ȑO�̏I�����Ԃ�ێ����A�I�����Ԃ��擾
        uint64_t beforeEndTime = endTime_;
        endTime_ = GetTime();

        // 1�t���[���̍���( �o�� )���Ԃ����߂�
        deltaTime_ = endTime_ - beforeEndTime;

        if (waitFlag_ == true)
        {
            // ����J�n���Ԃ���̌o�ߎ��Ԃ����߂�
            uint64_t elapsedTime = endTime_ - startTime_;

            // �ҋ@���Ԃ����߂�
            int32_t waitTime = loopCount_ * s_ONE_TOUSAND_MILLISECONDS / fps_ - static_cast<int32_t>(elapsedTime);

            // �ҋ@���Ԃ�����ꍇ
            if (waitTime > 0)
            {
                // �`��t���O���グ��
                drawFlag_ = true;

                // �ҋ@���ԕ������҂�
                std::this_thread::sleep_for(Milliseconds(waitTime));
            }
            else
            {
                // �t���[���X�L�b�v�L�����͕`��t���O��������
                if (frameSkipFlag_ == true) drawFlag_ = false;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �o�ߎ��ԂȂǂ̌v�Z���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Calculate()
    {
        // ���ώ��Ԃ����߂�T���v�����̉񐔕��A���[�v���񂵂��ꍇ
        if (loopCount_ >= s_AVERAGE_SAMPLE_NUMBER)
        {
            // ���݂̎��Ԃ��擾
            uint64_t nowTime = GetTime();

            // �o�ߎ��Ԃ����߂�
            float elapsedTime = static_cast<float>(nowTime - startTime_);

            // ���݂�FPS�����߂�
            nowFps_ = static_cast<float>(s_ONE_TOUSAND_MILLISECONDS) / (elapsedTime / static_cast<float>(s_AVERAGE_SAMPLE_NUMBER));

            // ���[�v�𐔂���J�E���^�����Z�b�g
            loopCount_ = 1;

            // ����J�n���Ԃ��X�V
            startTime_ = nowTime;
        }
        else
        {
            // ���[�v�̉񐔂�1����
            ++loopCount_;
        }

        // �t���[�����̃J�E���^��1����
        ++frameCount_;
    }
}