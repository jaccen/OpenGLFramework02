/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/Physics/PhysicsDefine.h"


/* �O���錾 */
class C_BasePower;
class C_ShotLogic;
class C_Shooter;
class C_MoveLogic;


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�K��
    //! @brief �K���̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseGun
    {
    public:
        C_BaseGun(C_Shooter* pShooter);                                                     // �R���X�g���N�^
        virtual ~C_BaseGun();                                                               // �f�X�g���N�^
        virtual void Shot() = 0;                                                            // �ˌ�����

        void SetShotLogic(C_ShotLogic* pShotLogic);                                         // �ˌ��̃��W�b�N��ݒ�
        void SetShotOffset(const Vector3& rShotOffset, bool defaultFlag = true);            // �ˌ��̃I�t�Z�b�g��ݒ�
        void SetBulletId(const std::string& rBulletId);                                     // �e��ID��ݒ�
        void SetBulletMoveLogic(C_MoveLogic* pBulletMoveLogic);                             // �e�̈ړ����W�b�N��ݒ�
        void SetBulletPower(C_BasePower* pBulletPower);                                     // �e�̍U���͂�ݒ�
        void SetAutoBulletFowardDirectionFlag(bool autoBulletFowardDirectionFlag);          // �e�̑O����������������t���O��ݒ�
    protected:
        C_Shooter* pShooter_ = nullptr;                                                     ///< @brief �ˌ���
        Physics::Vector3 offsetFromShooter_ = Physics::Vector3(0.0f, 0.0f, 0.0f);           ///< @brief �ˌ��҂���̃I�t�Z�b�g
        Physics::Vector3 direction_ = Physics::Vector3(0.0f, 0.0f, 0.0f);                   ///< @brief ����
        bool autoDirectionFlag_ = false;                                                    ///< @brief ����������������t���O
        std::unique_ptr<C_ShotLogic> upShotLogic_;                                          ///< @brief �ˌ��̃��W�b�N

        std::string bulletId_;                                                              ///< @brief �e��ID
        std::unique_ptr<C_BasePower> upBulletPower_;                                        ///< @brief �e�̍U����
        std::shared_ptr<C_MoveLogic> upBulletMoveLogic_;                                    ///< @brief �e�̈ړ����W�b�N
    };
}

