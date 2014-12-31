/* �w�b�_�t�@�C�� */
#include "CompoundShape.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CompoundShape::C_CompoundShape()
    {
        upCollisionShape_ = std::make_unique<btCompoundShape>();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CompoundShape::~C_CompoundShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �q�`���ǉ�����
     *  @param  �q�`��
     *  @param  �g�����X�t�H�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CompoundShape::AddChildShape(C_CollisionShape* pChildShape,
                                        const Transform& rTransform)
    {
        upChildShapes_.emplace_back(pChildShape);
        dynamic_cast<btCompoundShape*>(upCollisionShape_.get())->addChildShape(rTransform, pChildShape->GetCollisionShape());
    }
}