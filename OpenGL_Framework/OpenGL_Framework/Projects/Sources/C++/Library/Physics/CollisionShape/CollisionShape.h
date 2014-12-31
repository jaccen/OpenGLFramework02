/* ��d�C���N���[�h�h�~ */
#pragma once


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
    //! @brief �R���W�����V�F�C�v
    //! @brief �Փˌ`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_CollisionShape
    {
    public:
        C_CollisionShape();                                                 // �R���X�g���N�^
        virtual ~C_CollisionShape();                                        // �f�X�g���N�^
        btCollisionShape* GetCollisionShape() const;                        // �Փˌ`����擾
        int32_t GetShapeType() const;                                       // �`��̎�ނ��擾
        float GetCollisionMargin() const;                                   // �Փ˃}�[�W�����擾
        void SetCollisionMargin(float collisionMargin = 0.04f);             // �Փ˃}�[�W����ݒ�
    protected:
        std::unique_ptr<btCollisionShape> upCollisionShape_;                ///< @brief �Փˌ`��
    };
}