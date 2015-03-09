/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Shooter.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Json/Object/JsonObject.h"


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
    class C_BaseOption;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseShield;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�G�l�~�[
    //! @brief �G�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseEnemy : public C_Shooter
    {
    public:
        C_BaseEnemy(const std::string& rId, int32_t type);                                  // �R���X�g���N�^
        virtual ~C_BaseEnemy() override;                                                    // �f�X�g���N�^
        bool Update() override final;                                                       // �X�V����
        void Draw() override final;                                                         // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                      // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;         // �Փˌ��m�𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                      // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                      // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                        // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                      // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                  // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                          // �{���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseShield* pShiled) override;                      // �V�[���h�Ƃ̏Փˎ�����
        virtual void Move() = 0;                                                            // �ړ�����
        virtual void Shot();                                                                // �ˌ�����
        virtual void SetCreateDataWithJson(JSON::JsonObject* pJsonObject) = 0;              // JSON�I�u�W�F�N�g����f�[�^��ݒ�
        void SetMaterial(const Material::MaterialPtr& prMaterial) override;                 // �}�e���A����ݒ�
        void SetLight(const Light::LightPtr& prLight) override;                             // ���C�g��ݒ�
        virtual bool IsFinishAdvent() const;                                                // �o�����I�����Ă��邩�m�F
        State::C_StateMachine<C_BaseEnemy>* GetStateMachine() const;                        // �X�e�[�g�}�V�[�����擾
    protected:
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                    ///< @brief �e
        std::unique_ptr<State::C_StateMachine<C_BaseEnemy>> upStateMachine_;                ///< @brief �X�e�[�g�}�V�[��
        Vector3 scale_;                                                                     ///< @brief �X�P�[��

        virtual void DoUpdate() = 0;                                                        // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                          // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;                       // ����J�̃��b�Z�[�W����
    };
}