/* �w�b�_�t�@�C�� */
#include "Earth.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/Material/Material/Phong/PhongMaterial.h"
#include "../../Library/Light/Light/Point/PointLight.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


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
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_Earth::C_Earth(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE).get();

        // �e�N�X�`���f�[�^���擾
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pEARTH));
        pTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pEARTH).get();

        // GLSL�I�u�W�F�N�g���擾
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE).get();

        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->End();

        // ���j�t�H�[���o�b�t�@�ƃC���f�b�N�X���擾
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Earth::~C_Earth()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    void C_Earth::DoUpdate()
    {
        rotation_.x_ += static_cast<float>(Math::s_ONE_RADIAN * 0.01);
        rotation_.y_ += static_cast<float>(Math::s_ONE_RADIAN * 0.1);
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Earth::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        modelMatrix_ = Matrix4x4::s_CreateTRS(position_, rotation_, scale_);
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        // �A�N�e�B�u�ȃe�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`�����o�C���h
        pTextureManager->SetActiveUnit(0);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Earth::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}