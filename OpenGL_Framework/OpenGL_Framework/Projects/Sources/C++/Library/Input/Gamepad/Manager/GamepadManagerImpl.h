/* �w�b�_�t�@�C�� */
#include "GamepadManager.h"
#include "../Factory/GamepadFactory.h"
#include <SDL.h>
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
    //! @brief �Q�[���p�b�h�}�l�[�W���[�C���v�������g
    //! @brief �Q�[���p�b�h�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_GamepadManager::C_GamepadManagerImpl
    {
    public:
        C_GamepadManagerImpl();                                                                                     // �R���X�g���N�^
        ~C_GamepadManagerImpl();                                                                                    // �f�X�g���N�^
        void Initialize();                                                                                          // ����������
        void Update();                                                                                              // �X�V����
        void Finalize();                                                                                            // �I������

        /* �Q�b�^�[ */
        int GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const;                         // �{�^���������Ă���t���[�������擾
        int GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const;                        // �{�^���𗣂��Ă���t���[�������擾
        int GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const;                               // �X�e�B�b�N��X�������擾
        int GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const;                               // �X�e�B�b�N��Y�������擾
        int GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const;                             // �X�e�B�b�N��|���Ă���t���[�������擾
        int GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const;                           // �X�e�B�b�N��|���Ă��Ȃ��t���[�������擾
    private:
        std::vector<std::unique_ptr<C_Gamepad>> upGamepads_;                                                        ///< @brief �Q�[���p�b�h
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GamepadManager::C_GamepadManagerImpl::C_GamepadManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GamepadManager::C_GamepadManagerImpl::~C_GamepadManagerImpl()
    {
        if (upGamepads_.empty() == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���p�b�h�̏������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Initialize()
    {
        // ����������Ă��Ȃ��ꍇ�A����������
        if (::SDL_WasInit(SDL_INIT_JOYSTICK) == 0) ::SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        // �����擾
        int32_t count = ::SDL_NumJoysticks();
        if (count == 0) return;

        // �Q�[���p�b�h�̃��������m��
        upGamepads_.reserve(count);

        // �t�@�N�g���𐶐�
        auto pFactory = std::make_unique<C_GamepadFactory>();

        for (int32_t i = 0; i < count; ++i)
        {
            // �Q�[���p�b�h�̏����擾
            GamepadData* pGamepadData = ::SDL_JoystickOpen(i);

            if (pGamepadData == nullptr)
            {
                std::cout << "[ C_GamepadManagerImpl::Initialize ] : �Q�[���p�b�h���J���̂Ɏ��s���܂����B" << std::endl;
                std::cout << "                          �G���[���e : " << ::SDL_GetError() << std::endl;

                break;
            }

            // ���O���擾���A�Q�[���p�b�h�𐶐�
            const char* pNAME = ::SDL_JoystickName(pGamepadData);
            upGamepads_.emplace_back(pFactory->Create(pNAME, pGamepadData));

#ifdef _DEBUG

            // �����o��
            std::cout << "[ C_GamepadManagerImpl::Initialize ] : Name         : " << pNAME << std::endl;
            std::cout << "                                       AxesNumber   : " << ::SDL_JoystickNumAxes(pGamepadData) << std::endl;
            std::cout << "                                       ButtonNumber : " << ::SDL_JoystickNumButtons(pGamepadData ) << std::endl;
            std::cout << "                                       BallNumber   : " << ::SDL_JoystickNumBalls(pGamepadData) << std::endl;
            std::cout << "                                       HatNumber    : " << ::SDL_JoystickNumHats(pGamepadData) << std::endl;

#endif

        }

        // �C�x���g�̃|�[�����O�𖳌��ɂ���
        if (::SDL_JoystickEventState(SDL_IGNORE) < 0)
        {
            std::cout << "[ C_GamepadManagerImpl::Initialize ] : �C�x���g�̃|�[�����O�̐ݒ�Ɏ��s���܂����B" << std::endl;
            std::cout << "                          �G���[���e : " << ::SDL_GetError() << std::endl;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���p�b�h�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Update()
    {
        // �q����Ă��Ȃ��ꍇ
        if (upGamepads_.size() == 0) return;

        // ���͏�Ԃ��X�V
        ::SDL_JoystickUpdate();

        // �X�V����
        for (auto& upGamepad : upGamepads_) upGamepad->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���p�b�h�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Finalize()
    {
        // �I������
        for (auto& upGamepad : upGamepads_) upGamepad->Finalize();

        // �Q�[���p�b�h��S�č폜
        upGamepads_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���������Ă���t���[�������擾����
     *  @param  �{�^��
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �{�^���������Ă���t���[����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetButtonPressingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���𗣂��Ă���t���[�������擾����
     *  @param  �{�^��
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �{�^���𗣂��Ă���t���[����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetButtonReleasingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��X�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��X����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickXComponent(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��Y�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��Y����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickYComponent(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��|���Ă���t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��|���Ă���t���[����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickPushingCount(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��|���Ă��Ȃ��t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��|���Ă��Ȃ��t���[����
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickReleasingCount(stick);
    }
}