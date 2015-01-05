/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Collision/BoundingBox/AABB/Aabb2D.h"


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


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�v���C���[
    //! @brief �v���C���[�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BasePlayer : public C_ConnectMachine
    {
    public:
        /** �v���C���[�̏�� */
        struct S_PlayerData
        {
            int32_t hitPoint_ = 5000;                                                           ///< @brief �q�b�g�|�C���g
            int32_t remainLife_ = 3;                                                            ///< @brief �c�@
            float radius_ = 0.9f;                                                               ///< @brief ���a
            float movement_ = 0.2f;                                                             ///< @brief �ړ���
            int32_t moveSpeedLevel_ = 0;                                                        ///< @brief �ړ��X�s�[�h���x��
            int32_t gunLevel_ = 0;                                                              ///< @brief �e���x��
            int32_t connectPetrifyFrame_ = 10;                                                  ///< @brief �A�����̍d���t���[����
            int32_t bombChargeFrame_ = 60;                                                      ///< @brief �{���̃`���[�W�t���[���� 
            int32_t bombInvincibleFrame_ = 100;                                                 ///< @brief �{���̖��G�t���[����
        };


        C_BasePlayer(const std::string& rId, int32_t type);                                     // �R���X�g���N�^
        virtual ~C_BasePlayer() override;                                                       // �f�X�g���N�^
        bool Update() override final;                                                           // �X�V����
        void Draw() override final;                                                             // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                          // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;             // �Փ˂𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                          // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                          // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                            // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                          // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                      // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                              // �{���Ƃ̏Փˎ�����
        virtual void Move() override;                                                           // �ړ�����
        virtual void Shot() override;                                                           // �ˌ�����
        virtual void Bomb();                                                                    // �{������
        virtual void AddConnectOption(C_BaseOption* pOption) override;                          // �A�����Ă���I�v�V������ǉ�
        virtual void ResetConnect() override;                                                   // �A�������Z�b�g
        virtual void ConnectCheck();                                                            // �A���̊m�F
        virtual void ConnectCheck(C_BaseOption* pOption);                                       // �A���̊m�F
        virtual void NewConnect() override;                                                     // �V�K�A��
        virtual void MoveLimitCheck() override;                                                 // �ړ��������m�F
        virtual void UpdateMoveLimitBoundingBox(C_BaseOption* pOption);                         // �ړ��������E�{�b�N�X�̍X�V
        virtual void ResetMoveLimitBoundingBox();                                               // �ړ��������E�{�b�N�X�����Z�b�g
        virtual void AddMoveSpeedLevel(int32_t moveSpeedLevel);                                 // �ړ����x�̃��x�������Z
        virtual void AddGunLevel(int32_t powerLevel);                                           // �e�̃��x�������Z
        void AddOptionCount(int32_t optionCount);                                               // �I�v�V�����̐������Z
        State::C_StateMachine<C_BasePlayer>* GetStateMachine() const;                           // �X�e�[�g�}�V�[�����擾
        //const AABB2D& GetMoveLimitBoundingBox() const;                                        // �ړ��������E�{�b�N�X���擾
        int32_t GetGunLevel() const;                                                            // �e�̃��x�����擾
        int32_t GetConnectPetrifyFrame() const;                                                 // �A���̍d���t���[�������擾
        int32_t GetBombChargeFrame() const;                                                     // �{���̃`���[�W�t���[�������擾
        int32_t GetBombInvincibleFrame() const;                                                 // �{���̖��G�t���[�������擾
        bool IsBombChargeFlag() const;                                                          // �{���̃`���[�W�t���O
        const std::string& GetBombChargeEffectId() const;                                       // �{���̃`���[�W�G�t�F�N�g��ID
        const std::string& GetBombId() const;                                                   // �{����ID���擾
        int32_t GetOptionCount() const;                                                         // �I�v�V�����̐����擾
        //void SetMoveLimitBoundingBox(const AABB2D& rMoveLimitBoundingBox);                    // �ړ��������E�{�b�N�X��ݒ�
        void SetBombChargeFlag(bool bombChargeFlag);                                            // �{���̃`���[�W�t���O��ݒ�
    protected:
        std::unique_ptr<State::C_StateMachine<C_BasePlayer>> upStateMachine_;                   ///< @brief �X�e�[�g�}�V�[��
        OpenGL::PrimitiveBufferPtr pModelData_;                                                 ///< @brief ���f�����
        Camera::CameraPtr pCamera_;                                                             ///< @brief �J����
        int32_t connectPetrifyFrame_ = 0;                                                       ///< @brief �A�����̍d���t���[����
        int32_t bombChargeFrame_ = 60;                                                          ///< @brief �{���̃`���[�W�t���[����
        int32_t bombInvincibleFrame_ = 100;                                                     ///< @brief �{���̖��G�t���[����
        int32_t remainLife_ = 3;                                                                ///< @brief �c�@
        int32_t moveSpeedLevel_ = 0;                                                            ///< @brief �ړ��X�s�[�h�̃��x��
        int32_t gunLevel_ = 0;                                                                  ///< @brief �e�̃��x��
        int32_t optionCount_ = 0;                                                               ///< @brief �I�v�V������
        bool bombChargeFlag_ = false;                                                           ///< @brief �{���̃`���[�W�t���O
        bool bombEnableFlag_ = false;                                                           ///< @brief �{�����L�������f����t���O
        Collision::S_Aabb2D<float> moveLimitBoundingBox_;                                       ///< @brief �ړ��������E�{�b�N�X


        //std::string bombChargeEffectId_ = GameObjectDefine::Id::s_BOMB_CHARGE_EFFECT;           ///< @brief �{���̃`���[�W�G�t�F�N�g��ID
        //std::string bombId_ = GameObjectDefine::Id::s_NORMAL_BOMB;                              ///< @brief �{����ID
        //std::deque<std::unique_ptr<C_BaseGun>> upGuns_;                                         ///< @brief �e

        virtual void DoUpdate();                                                                // ����J�̍X�V����
        virtual void DoDraw();                                                                  // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                               // ����J�̃��b�Z�[�W����
    };
}