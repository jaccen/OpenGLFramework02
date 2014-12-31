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
    //! @brief �R���P�[�u�g���C�A���O�����b�V���V�F�C�v
    //! @brief ���ʎO�p���b�V���`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_ConcaveTriangleMeshShape : public C_CollisionShape
    {
    public:
        C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],               // �R���X�g���N�^
                                   uint32_t vertexCount);
        C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],               // �R���X�g���N�^
                                   uint32_t vertexCount,
                                   int32_t indices[],
                                   uint32_t triangleCount);
        ~C_ConcaveTriangleMeshShape() override;                             // �f�X�g���N�^
    private:
        std::unique_ptr<btTriangleMesh> upTriangleMesh_;                    ///< @brief �O�p�`���b�V��
    };
}