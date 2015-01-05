/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "BaseHitPoint.h"
#include "BasePower.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Math/Vector/Vector4.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Library/Common/CommonHelper.h"
#include "../../Library/Physics/PhysicsDefine.h"
#include <vector>


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
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief �R���W�����I�u�W�F�N�g
    //! @brief �Փˎ��������s���I�u�W�F�N�g
    //!
    //-------------------------------------------------------------
    class C_CollisionObject : public GameObject::C_GameObject
    {
    public:
        /* �t�B���^�̎�� */
        enum eFilterType
        {
            FILTER_TYPE_NOTHING = 0,                                                                        ///< @brief �Ȃ�
            FILTER_TYPE_PLAYER = ShiftBit(1),                                                               ///< @brief �v���C���[
            FILTER_TYPE_OPTION = ShiftBit(2),                                                               ///< @brief �I�v�V����
            FILTER_TYPE_ENEMY = ShiftBit(3),                                                                ///< @brief �G
            FILTER_TYPE_CONNECTMACHINE_BULLET = ShiftBit(4),                                                ///< @brief �A���@�B�̒e
            FILTER_TYPE_ENEMY_BULLET = ShiftBit(5),                                                         ///< @brief �G�̒e
            FILTER_TYPE_OBSTACLE = ShiftBit(6),                                                             ///< @brief ��Q��
            FILTER_TYPE_BOMB = ShiftBit(7),                                                                 ///< @brief �{��
        };


        C_CollisionObject(const std::string& rId, int32_t type);                                            // �R���X�g���N�^
        virtual ~C_CollisionObject() override;                                                              // �f�X�g���N�^
        virtual bool Update() override = 0;                                                                 // �X�V����
        virtual void Draw() override = 0;                                                                   // �`�揈��
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                                // ���b�Z�[�W����
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) = 0;                            // �Փ˂𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                                           // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                                           // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                             // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                                           // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                                       // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                               // �{���Ƃ̏Փˎ�����
        virtual void MoveLimitCheck() = 0;                                                                  // �ړ��������m�F
        bool CheckCollidedObjectId(const std::string& rId);                                                 // �Փ˂����I�u�W�F�N�g��ID�����݂��邩�m�F
        void EntryCollidedObjectId(const std::string& rId);                                                 // �Փ˂����I�u�W�F�N�g��ID��o�^
        void SetCollisionPoint(const Physics::Vector3& rCollisionPoint);                                    // �Փ˓_��ݒ�
    protected:
        Matrix4x4 modelMatrix_;                                                                             ///< @brief ���f���s��
        std::unique_ptr<C_BaseHitPoint> upHitPoint_;                                                        ///< @brief �q�b�g�|�C���g
        std::unique_ptr<C_BasePower> upPower_;                                                              ///< @brief �p���[
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                           ///< @brief GLSL�I�u�W�F�N�g
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                                                     ///< @brief ���j�t�H�[���o�b�t�@
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                                             ///< @brief ���j�t�H�[���u���b�N�̃C���f�b�N�X

        void ResetCollidedObjectId();                                                                       // �Փ˂����I�u�W�F�N�g��ID�����Z�b�g
        const Physics::Vector3& GetCollisionPoint() const;                                                  // �Փ˓_���擾
    private:
        std::vector<std::string> collidedObjectIdList_;                                                     ///< @brief �Փ˂����I�u�W�F�N�g��ID���X�g
        Physics::Vector3 collisionPoint_;                                                                   ///< @brief �Փ˓_
    };
}