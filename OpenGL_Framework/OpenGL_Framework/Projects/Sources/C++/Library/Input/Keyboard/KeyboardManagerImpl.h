/* �w�b�_�t�@�C�� */
#include "KeyboardManager.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief �L�[�{�[�h�}�l�[�W���[�C���v�������g
    //! @brief �L�[�{�[�h�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_KeyboardManager::C_KeyboardManagerImpl
    {
    public:
        C_KeyboardManagerImpl();                                            // �R���X�g���N�^
        ~C_KeyboardManagerImpl();                                           // �f�X�g���N�^
        void Initialize();                                                  // ����������
        void Update();                                                      // �X�V����
        int32_t GetPressingCount(KeyCode keycode) const;                    // �����Ă���t���[�������擾
        int32_t GetReleasingCount(KeyCode keycode) const;                   // �����Ă���t���[�������擾
        const std::string& GetInputCharacter() const;                       // ���͂����������擾
        void SetInputCharacter(const std::string& rInputCharacter);         // ���͂���������ݒ�
    private:
        int32_t count_ = 0;                                                 ///< @brief ��
        const uint8_t* pAllState_ = nullptr;                                ///< @brief ���ׂĂ̏��
        std::vector<int32_t> pressingCounts_;                               ///< @brief �����Ă���t���[�����̃J�E���^
        std::vector<int32_t> releasingCounts_;                              ///< @brief �����Ă���t���[�����̃J�E���^
        std::string inputCharacter_;                                        ///< @brief ���͂�������     
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_KeyboardManager::C_KeyboardManagerImpl::C_KeyboardManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_KeyboardManager::C_KeyboardManagerImpl::~C_KeyboardManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::Initialize()
    {
        // �L�[�̐��Ə�Ԃ��擾
        pAllState_ = ::SDL_GetKeyboardState(&count_);

        // ���͂��Ǘ�����J�E���^�̔z��̃T�C�Y��ݒ�
        pressingCounts_.resize(count_, 0);
        releasingCounts_.resize(count_, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::Update()
    {
        for (int32_t i = 0; i < count_; ++i)
        {
            // ���͂���Ă���ꍇ
            if (pAllState_[i] == 1)
            {
                // �����Ă���t���[���������Z�b�g���A
                // ������Ă���t���[������1����
                if (releasingCounts_[i] > 0) releasingCounts_[i] = 0;

                ++pressingCounts_[i];
            }
            else
            {
                // ������Ă���t���[���������Z�b�g���A
                // ������Ă���t���[������1����
                if (pressingCounts_[i] > 0) pressingCounts_[i] = 0;

                ++releasingCounts_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �����Ă���t���[�������擾����
     *  @param  �X�L�����R�[�h
     *  @return �����Ă���t���[����
     *
     ****************************************************************/
    int32_t C_KeyboardManager::C_KeyboardManagerImpl::GetPressingCount(KeyCode keycode) const
    {
        return pressingCounts_.at(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  �����Ă���t���[�������擾����
     *  @param  �X�L�����R�[�h
     *  @return �����Ă���t���[����
     *
     ****************************************************************/
    int32_t C_KeyboardManager::C_KeyboardManagerImpl::GetReleasingCount(KeyCode keycode) const
    {
        return releasingCounts_.at(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  ���͂����������擾����
     *  @param  �Ȃ�
     *  @return ���͂�������
     *
     ****************************************************************/
    const std::string& C_KeyboardManager::C_KeyboardManagerImpl::GetInputCharacter() const
    {
        return inputCharacter_;
    }


    /*************************************************************//**
     *
     *  @brief  ���͂���������ݒ肷��
     *  @param  ���͂�������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::SetInputCharacter(const std::string& rInputCharacter)
    {
        inputCharacter_ = rInputCharacter;
    }
}