/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "BaseBackground.h"


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
    //! @brief �A�[�X
    //! @brief �n����\���N���X
    //!
    //-------------------------------------------------------------
    class C_Earth : public C_BaseBackground
    {
    public:
        C_Earth(const std::string& rId, int32_t type);                          // �R���X�g���N�^
        virtual ~C_Earth();                                                     // �f�X�g���N�^
    private:
        OpenGL::PrimitiveBufferPtr pModelData_;                                 ///< @brief ���f�����
        Texture::TextureDataPtr pTextureData_;                                  ///< @brief �e�N�X�`���f�[�^
        Matrix4x4 modelMatrix_;                                                 ///< @brief ���f���s��

        virtual void DoUpdate() override;                                       // ����J�̍X�V����
        virtual void DoDraw() override;                                         // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) override;      // ����J�̃��b�Z�[�W����
    };
}