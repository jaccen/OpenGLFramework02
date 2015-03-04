/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Collision/BoundingBox/AABB/Aabb2D.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�v���C���[
    //! @brief �v���C���[�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BasePlayer : public C_ConnectMachine
    {
    public:
        /* �e�̏�� */
        struct S_GunData
        {
            std::string bulletId_;                                                                      ///< @brief �e��ID
            int32_t bulletPower_ = 1000;                                                                ///< @brief �e�̃p���[
            float bulletMovement_ = 5.0f;                                                               ///< @brief �e�̈ړ���
            int32_t shotInterval_ = 5;                                                                  ///< @brief �ˌ��̊Ԋu
            std::shared_ptr<Physics::Vector3> spOffsetFromShooter_;                                     ///< @brief �ˌ��҂���̃I�t�Z�b�g
            std::shared_ptr<Physics::Vector3> spDirection_;                                             ///< @brief ����
            bool autoDirectionFlag_ = false;                                                            ///< @brief ����������������t���O
        };


        enum eMoveType
        {
            ADVENT,
            INPUT,
        };


        C_BasePlayer(const std::string& rId, int32_t type);                                             // �R���X�g���N�^
        virtual ~C_BasePlayer() override = 0;                                                           // �f�X�g���N�^
        bool Update() override final;                                                                   // �X�V����
        void Draw() override final;                                                                     // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                                  // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                     // �Փ˂𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                                  // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                                  // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                    // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                                  // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                              // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                      // �{���Ƃ̏Փˎ�����
        virtual void Move() override;                                                                   // �ړ�����
        virtual void Shot() override;                                                                   // �ˌ�����
        virtual void Bomb();                                                                            // �{������
        virtual void AddConnectOption(C_BaseOption* pOption) override;                                  // �A�����Ă���I�v�V������ǉ�
        virtual void ResetConnect() override;                                                           // �A�������Z�b�g
        virtual void ConnectCheck();                                                                    // �A���̊m�F
        virtual void ConnectCheck(C_BaseOption* pOption);                                               // �A���̊m�F
        virtual void NewConnect() override;                                                             // �V�K�A��
        virtual void MoveLimitCheck() override;                                                         // �ړ��������m�F
        virtual void UpdateMoveLimitBoundingBox(C_BaseOption* pOption);                                 // �ړ��������E�{�b�N�X�̍X�V
        virtual void ResetMoveLimitBoundingBox();                                                       // �ړ��������E�{�b�N�X�����Z�b�g
        virtual void AddMoveSpeedLevel(int32_t moveSpeedLevel);                                         // �ړ����x�̃��x�������Z
        void AddConnectOptionCount(int32_t connectOptionCount);                                         // �I�v�V�����̐������Z
        State::C_StateMachine<C_BasePlayer>* GetStateMachine() const;                                   // �X�e�[�g�}�V�[�����擾
        int32_t GetConnectPetrifyFrame() const;                                                         // �A���̍d���t���[�������擾
        int32_t GetBombChargeFrame() const;                                                             // �{���̃`���[�W�t���[�������擾
        int32_t GetBombInvincibleFrame() const;                                                         // �{���̖��G�t���[�������擾
        bool IsBombChargeFlag() const;                                                                  // �{���̃`���[�W�t���O���擾
        const std::string& GetBombChargeEffectId() const;                                               // �{���̃`���[�W�G�t�F�N�g��ID
        const std::string& GetBombId() const;                                                           // �{����ID���擾
        void SetBombChargeFlag(bool bombChargeFlag);                                                    // �{���̃`���[�W�t���O��ݒ�
        bool IsFinishAdvent() const;                                                                    // �o�����I�������m�F
        void ChangeMove(eMoveType moveType);                                                            // �ړ���ύX
    protected:
        std::unique_ptr<State::C_StateMachine<C_BasePlayer>> upStateMachine_;                           ///< @brief �X�e�[�g�}�V�[��
        Camera::CameraPtr pCamera_;                                                                     ///< @brief �J����
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                                ///< @brief �e
        int32_t connectPetrifyFrame_ = 0;                                                               ///< @brief �A�����̍d���t���[����
        int32_t bombChargeFrame_ = 60;                                                                  ///< @brief �{���̃`���[�W�t���[����
        int32_t bombInvincibleFrame_ = 100;                                                             ///< @brief �{���̖��G�t���[����
        int32_t remainLife_ = 3;                                                                        ///< @brief �c�@
        int32_t moveSpeedLevel_ = 0;                                                                    ///< @brief �ړ��X�s�[�h�̃��x��
        float moveSpeedUpInterval_ = 0.3f;                                                              ///< @brief �ړ��X�s�[�h�̃A�b�v�Ԋu
        int32_t connectOptionCount_ = 0;                                                                ///< @brief �I�v�V������
        bool bombChargeFlag_ = false;                                                                   ///< @brief �{���̃`���[�W�t���O
        Collision::S_Aabb2D<float> moveLimitBoundingBox_;                                               ///< @brief �ړ��������E�{�b�N�X
        Input::KeyCode bombKeyCode_ = Input::KeyCode::SDL_SCANCODE_X;                                   ///< @brief �{���̃L�[�R�[�h
        Input::C_Gamepad::eButton bombGamepadButton_ = Input::C_Gamepad::BUTTON_FOUR_RIGHT;             ///< @brief �{���̃Q�[���p�b�h�̃{�^��

        virtual void DoUpdate();                                                                        // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                                      // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                       // ����J�̃��b�Z�[�W����
    };
}