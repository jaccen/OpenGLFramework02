/* �w�b�_�t�@�C�� */
#include "Space.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"


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
    C_Space::C_Space(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        // �v���C���[�̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPACE));
        auto pSpaceData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPACE).get();

        // ���f���s����쐬
        float radius = static_cast<float>((*pSpaceData)["SpaceData"]["Radius"].GetValue<JSON::Real>());
        modelMatrix_ = Matrix4x4::s_CreateScaling(radius, radius, radius);

        // ���f�������擾
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE).get();

        // GLSL�I�u�W�F�N�g���擾
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG).get();

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
    C_Space::~C_Space()
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
    void C_Space::DoUpdate()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Space::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        // �}�e���A����ݒ�
        pGlslObject_->SetUniformVector3("material.diffuse", Vector3(0.5f, 1.0f, 0.5f));
        pGlslObject_->SetUniformVector3("material.ambient", Vector3(0.1f, 0.1f, 0.1f));
        pGlslObject_->SetUniformVector3("material.specular", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniform1f("material.shininess", 100.0f);
        pGlslObject_->SetUniformVector3("light.position", Vector3(0.0f, 100.0f, 0.0f));
        pGlslObject_->SetUniformVector3("light.diffuse", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.ambient", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.specular", Vector3(0.9f, 0.9f, 0.9f));

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

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
    bool C_Space::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}