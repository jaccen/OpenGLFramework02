/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../CollisionShape.h"
#include "../../../PhysicsDefine.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief �R���o�b�N�X�n���V�F�C�v
    //! @brief �ʕ�`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_ConvexHullShape : public C_CollisionShape
    {
    public:
        C_ConvexHullShape(Vector3 vertexPositions[], int32_t vertexCount);          // �R���X�g���N�^
        ~C_ConvexHullShape() override;                                              // �f�X�g���N�^
        void AddVertexPosition(const Vector3& rVertexPosition);                     // ���_���W��ǉ�
    };
}