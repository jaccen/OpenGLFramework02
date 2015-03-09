/* �w�b�_�t�@�C�� */
#include "BaseShield.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"


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
    //! @brief �x�[�X�V�[���h
    //! @brief �V�[���h�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_NormalShield : public C_BaseShield
    {
    public:
        C_NormalShield(const std::string& rId,                                              // �R���X�g���N�^
                       int32_t type,
                       int32_t shooterType,
                       C_CollisionObject* pTarget);  
        ~C_NormalShield() override;                                                         // �f�X�g���N�^
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                                      ///< @brief �X�v���C�g�N���G�C�^�[
        Sprite::S_CreateData spriteCreateData_;                                             ///< @brief �X�v���C�g�̍쐬���

        void DoDraw() override;                                                             // ����J�̕`�揈��
    };
}