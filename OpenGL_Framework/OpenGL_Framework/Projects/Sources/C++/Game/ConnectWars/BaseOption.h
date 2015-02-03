/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BasePlayer;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�I�v�V����
    //! @brief �I�v�V�����̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseOption : public C_ConnectMachine
    {
    public:
        C_BaseOption(const std::string& rId, int32_t type);                                         // �R���X�g���N�^
        virtual ~C_BaseOption() override = 0;                                                       // �f�X�g���N�^
        bool Update() override final;                                                               // �X�V����
        void Draw() override final;                                                                 // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                              // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                 // �Փˌ��o�𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                              // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                              // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                              // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                  // �{���Ƃ̏Փˎ�����
        virtual void Move() override;                                                               // �ړ�����
        virtual void Shot() override;                                                               // �ˌ�����
        virtual void AddConnectOption(C_BaseOption* pOption);                                       // �A�����Ă���I�v�V������ǉ�
        virtual void ResetConnect() override;                                                       // �A�������Z�b�g
        virtual void NewConnect() override;                                                         // �V�K�A��
        virtual void MoveLimitCheck() override;                                                     // �ړ��������m�F
        virtual void ConnectEffect();                                                               // �A�����̌���
        virtual void ResetEffect();                                                                 // ���ʂ����Z�b�g
        virtual void DispatchOwnCrash();                                                            // �����𔭑�
        virtual void OwnCrash();                                                                    // ��������
        State::C_StateMachine<C_BaseOption>* GetStateMachine() const;                               // �X�e�[�g�}�V�[�����擾
        const Physics::Vector3& GetOffsetFromPlayer() const;                                        // �v���C���[����̃I�t�Z�b�g���擾
        C_BasePlayer* GetPlayer() const;                                                            // �v���C���[���擾
        bool IsOnceConnectFlag() const;                                                             // ��x�A�����������f����t���O���擾
        bool IsConnectFlag() const;                                                                 // �A���t���O���擾
        bool IsDefeatedFlag() const;                                                                // ���j�t���O���擾
        int32_t GetDefeatedFrame() const;                                                           // ���j��Ԃ̃t���[�������擾
        const std::string& GetBombSelfCrashEffectId() const;                                        // �{���̎����G�t�F�N�g��ID���擾
        void SetOnceConnectFlag(bool onceConnectFlag);                                              // ��x�A�����������f����t���O��ݒ�
        void SetConnectFlag(bool connectFlag);                                                      // �A���t���O��ݒ�
        void SetOffsetFromPlayer(const Physics::Vector3& rOffsetFromPlayer);                        // �v���C���[����̃I�t�Z�b�g��ݒ�
        void SetPlayer(C_BasePlayer* pPlayer);                                                      // �v���C���[��ݒ�
        void SetDefeatedFlag(bool defeatedFlag);                                                    // ���j�t���O��ݒ�
    protected:
        std::unique_ptr<State::C_StateMachine<C_BaseOption>> upStateMachine_;                       ///< @brief �X�e�[�g�}�V�[��
        bool onceConnectFlag_ = false;                                                              ///< @brief ��x�A�����������f����t���O
        bool connectFlag_ = false;                                                                  ///< @brief �A������Ă��邩���f����t���O
        std::unique_ptr<Physics::Vector3> upOffsetFromPlayer_;                                      ///< @brief �v���C���[����̃I�t�Z�b�g
        C_BasePlayer* pPlayer_ = nullptr;                                                           ///< @brief �v���C���[
        bool defeatedFlag_ = false;                                                                 ///< @brief ���j�t���O
        int32_t defeatedFrame_ = 60;                                                                ///< @brief ���j��Ԃ̃t���[����
        int32_t ownCrashDelayFrame_ = 0;                                                            ///< @brief �����x���t���[����
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                            ///< @brief �e

        virtual void DoUpdate();                                                                    // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                                  // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                   // ����J�̃��b�Z�[�W����
    };
}