/* �w�b�_�t�@�C�� */
#include "CollisionCallback.h"
#include "CollisionObject.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �ڐG( �Փ� )���̏������s��
     *  @param  �}�j�t�H�[���h�|�C���g
     *  @param  �{�f�B
     *  @param  ������̃{�f�B
     *  @return �Ȃ�
     *
     ****************************************************************/
    bool C_CollisionCallback::s_ContactProcess(btManifoldPoint& rManifoldPoint, void* pBody, void* pAnotherBody)
    {
        // �Փ˃I�u�W�F�N�g�փL���X�g���A�Ǝ��̃f�[�^���擾
        auto pCollisionObject = reinterpret_cast<btCollisionObject*>(pBody);
        auto pAnotherCollisionObject = reinterpret_cast<btCollisionObject*>(pAnotherBody);
        auto pUserData = reinterpret_cast<C_CollisionObject*>(pCollisionObject->getUserPointer());
        auto pAnotherUserData= reinterpret_cast<C_CollisionObject*>(pAnotherCollisionObject->getUserPointer());

        // ID���o�^����Ă��Ȃ��ꍇ�͏Փˎ��̏������s��
        if (pUserData->CheckCollidedObjectId(pAnotherUserData->GetId()) == false)
        {
            // ID��o�^
            pUserData->EntryCollidedObjectId(pAnotherUserData->GetId());
            pAnotherUserData->EntryCollidedObjectId(pUserData->GetId());

            // �Փ˓_��ݒ�
            pUserData->SetCollisionPoint(rManifoldPoint.getPositionWorldOnA());
            pAnotherUserData->SetCollisionPoint(rManifoldPoint.getPositionWorldOnB());

            // �Փˌ��m�𔭍s
            pUserData->DispatchCollision(pAnotherUserData);
        }

        return true;
    }
}