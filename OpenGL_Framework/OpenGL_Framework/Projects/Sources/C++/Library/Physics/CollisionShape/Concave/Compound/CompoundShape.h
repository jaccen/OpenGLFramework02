/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../CollisionShape.h"
#include "../../../PhysicsDefine.h"
#include <deque>


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
    //! @brief �R���p�E���h�V�F�C�v
    //! @brief �����`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_CompoundShape : public C_CollisionShape
    {
    public:
        C_CompoundShape();                                                      // �R���X�g���N�^
        ~C_CompoundShape() override;                                            // �f�X�g���N�^
        void AddChildShape(C_CollisionShape* pChildShape,                       // �q�`���ǉ�
                           const Transform& rTransform);
    private:
        std::deque<std::unique_ptr<C_CollisionShape>> upChildShapes_;           ///< @brief �q�`��
    };
}