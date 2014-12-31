/* �w�b�_�t�@�C�� */
#include "ConcaveTriangleMeshShape.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ���_���W
     *  @param  ���_��
     *
     ****************************************************************/
    C_ConcaveTriangleMeshShape::C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],
                                                           uint32_t vertexCount) : 

        // �O�p�`���b�V��
        upTriangleMesh_(std::make_unique<btTriangleMesh>())

    {
        // �O�p�`���b�V�����\�z�A���̃f�[�^����V�F�C�v���쐬
        for (size_t i = 0, polygonCount = vertexCount / 3; i < polygonCount; ++i)
        {
            upTriangleMesh_->addTriangle(vertexPositions[i], 
                                         vertexPositions[i + 1],
                                         vertexPositions[i + 2]);
        }

        upCollisionShape_ = std::make_unique<btBvhTriangleMeshShape>(upTriangleMesh_.get(), true);
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ���_���W
     *  @param  ���_��
     *  @param  �C���f�b�N�X
     *  @param  �O�p�`�̐�
     *
     ****************************************************************/
    C_ConcaveTriangleMeshShape::C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],
                                                           uint32_t vertexCount,
                                                           int32_t indices[],
                                                           uint32_t triangleCount) : 

        // �O�p�`���b�V��
        upTriangleMesh_(std::make_unique<btTriangleMesh>())

    {
        // �O�p�`���b�V�����\�z�A���̃f�[�^����V�F�C�v���쐬
        for (size_t i = 0; i < triangleCount; ++i)
        {
             upTriangleMesh_->addTriangle(vertexPositions[indices[i]], 
                                          vertexPositions[indices[i + 1]],
                                          vertexPositions[indices[i + 2]]);
        }

        upCollisionShape_ = std::make_unique<btBvhTriangleMeshShape>(upTriangleMesh_.get(), true);
    }

    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConcaveTriangleMeshShape::~C_ConcaveTriangleMeshShape()
    {
    }
}