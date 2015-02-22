/* �w�b�_�t�@�C�� */
#include "SpriteCreater.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../OpenGL/Manager/OpenGlManager.h"


//-------------------------------------------------------------
//!
//! @brief �X�v���C�g
//! @brief �X�v���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sprite
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreater::C_SpriteCreater()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreater::~C_SpriteCreater()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �J����
     *  @param  �e�N�X�`�����
     *  @param  �ő�X�v���C�g��
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SpriteCreater::Initialize(const Camera::CameraPtr& prCamera,
                                     const Texture::TextureDataPtr& prTextureData,
                                     uint32_t maxSpriteCount)
    {
        // GLSL�I�u�W�F�N�g���쐬���A�ێ�
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : ���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : �W�I���g���V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : �t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : �V�F�[�_�[�̃����N�Ɏ��s���܂����B\n");

                return false;
            }

            pGlslObject_ = pGlslObject;
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject_, Fixed::Shader::s_pGLSL_OBJECT_ID);

            // �T�u���[�`���̃C���f�b�N�X���擾
            subroutineIndices_[Camera::PERSPECTIVE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "PerspectiveProcess");
            subroutineIndices_[Camera::ORTHOGRAPHIC] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "OrthographicProcess");
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();

            // �T�u���[�`���̃C���f�b�N�X���擾
            subroutineIndices_[Camera::PERSPECTIVE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "PerspectiveProcess");
            subroutineIndices_[Camera::ORTHOGRAPHIC] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "OrthographicProcess");
        }

        // ���_�̃��������m��
        vertices_.resize(maxSpriteCount);

        // �v���~�e�B�u���쐬���A�擾
        if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(Fixed::Primitive::s_pSPRITE_ID))
        {
            uint32_t vertexAttributeElementCountList[] = { 3, 2, 1, 4, 2, 2, 2 };
            std::array<OpenGL::DataEnum, 7> vertexAttributeDataTypeList;
            vertexAttributeDataTypeList.fill(OpenGL::DataType::s_FLOAT);
            uint32_t vertexByteOffsetList[] = { 4, 4, 4, 4, 4, 4, 4 };
            bool vertexTransferFlagList[] = { true, true, true, true, true, true, true };

            pPointDatas_ = OpenGL::C_PrimitiveBuffer::s_Create(vertices_.data(),        
                                                               vertices_.size(),
                                                               7, 
                                                               vertexAttributeElementCountList,
                                                               vertexAttributeDataTypeList.data(),
                                                               OpenGL::Modify::s_DYNAMIC,
                                                               vertexByteOffsetList,
                                                               vertexTransferFlagList);

            OpenGL::C_PrimitiveBufferManager::s_GetInstance()->Entry(pPointDatas_, Fixed::Primitive::s_pSPRITE_ID);
        }
        else
        {
            pPointDatas_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(Fixed::Primitive::s_pSPRITE_ID).get();
        }

        // �J�����ƃe�N�X�`������ݒ�
        pCamera_ = prCamera;
        pTextureData_ = prTextureData;

        // �e�N�X�`�����j�b�g��ݒ�
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::Draw()
    {
        // ���_�̏�������
        pPointDatas_->RewriteVertices(vertices_.data(), drawSpriteCount_);

        // �V�F�[�_�[�̎g�p�J�n
        pGlslObject_->Begin();

        // �T�u���[�`����ݒ�
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[cameraType_], Shader::GLSL::Type::s_GEOMETRY);
        
        // ���j�t�H�[���ϐ���ݒ�
        SetUniformVariable();

        // �e�N�X�`���}�l�[�W���[��OpenGL�}�l�[�W���[���擾
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();
        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        // �u�����h��L�������A�u�����h�Ɏg�p����֐���ݒ�
        pOpenGlManager->EnableBlend(true);
        pOpenGlManager->SetBlendFunction(sourceFactor_, destinationFactor_);

        // �J�����O�𖳌���
        pOpenGlManager->EnableCulling(false);

        // �[�x�̃}�X�N��L����
        pOpenGlManager->EnableDepthMask(true);

        // �A�N�e�B�u�ȃe�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`�����o�C���h
        pTextureManager->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        // �X�v���C�g��`��
        pOpenGlManager->DrawPrimitive(OpenGL::Primitive::s_POINT, pPointDatas_->GetVertexArrayObjectHandle(), drawSpriteCount_);

        // �[�x�̃}�X�N�𖳌���
        pOpenGlManager->EnableDepthMask(false);

        // �J�����O��L����
        pOpenGlManager->EnableCulling(true);

        // �u�����h�𖳌���
        pOpenGlManager->EnableBlend(false);

        // �e�N�X�`�����A���o�C���h
        pTextureManager->Unbind(Texture::Type::s_2D);

        // �V�F�[�_�[�̎g�p�I��
        pGlslObject_->End();

        drawSpriteCount_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::Finalize()
    {
        // �_�̏���j��
        pPointDatas_.reset();

        // ���_���폜
        vertices_.clear();

        // �`�悷��X�v���C�g�̐������Z�b�g
        drawSpriteCount_ = 0;
        
        // GLSL�I�u�W�F�N�g�̊Ǘ���j��
        pGlslObject_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::Entry(const Vector3& rPosition,
                                const Vector2& rSize,                                   
                                float angle,                                            
                                const Vector4& rColor,                                  
                                const Vector2& rTextureUpperLeft,                       
                                const Vector2& rTextureLowerRight)
    {
        Entry(S_CreateData(rPosition, rSize, angle, rColor, rTextureUpperLeft, rTextureLowerRight));
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::Entry(const S_CreateData& rCreateData)
    {
        if (drawSpriteCount_ >= vertices_.size()) return;

        vertices_[drawSpriteCount_].position_ = rCreateData.position_;
        vertices_[drawSpriteCount_].size_ = rCreateData.size_;
        vertices_[drawSpriteCount_].angle_ = rCreateData.angle_;
        vertices_[drawSpriteCount_].color_ = rCreateData.color_;
        vertices_[drawSpriteCount_].textureLowerRight_ = rCreateData.textureLowerRight_;
        vertices_[drawSpriteCount_].textureUpperLeft_ = rCreateData.textureUpperLeft_;
        vertices_[drawSpriteCount_].textureSize_.width_ = static_cast<float>(pTextureData_->width_);
        vertices_[drawSpriteCount_].textureSize_.height_ = static_cast<float>(pTextureData_->height_);

        ++drawSpriteCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �r���{�[�h�̎�������������t���O��ݒ肷��
     *  @param  �r���{�[�h�̎�������������t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::SetAutoBillboardFlag(bool autoBillboardFlag)
    {
        autoBillboardFlag_ = autoBillboardFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �J������ݒ�
     *  @param  �J����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::SetCamera(const Camera::CameraPtr& prCamera)
    {
        pCamera_ = prCamera;
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̎�ނ�ݒ�
     *  @param  �J�����̎��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::SetCameraType(Camera::eType cameraType)
    {
        cameraType_ = cameraType;
    }


    /*************************************************************//**
     *
     *  @brief  �u�����h�̊֐���ݒ肷��
     *  @param  �V�����F�̗v�f
     *  @param  ���݂̐F�̗v�f
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::SetBlendFunction(OpenGL::BlendEnum sourceFactor, OpenGL::BlendEnum destinationFactor)
    {
        sourceFactor_ = sourceFactor;
        destinationFactor_ = destinationFactor;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t�H�[���ϐ���ݒ�
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreater::SetUniformVariable()
    {
        // �r���{�[�h������������t���O�������Ă���ꍇ�A
        // �r���[�s�񂩂�r���{�[�h������s������߂�
        if (autoBillboardFlag_ == true)
        {
            billboardMatrix_ = pCamera_->GetViewMatrix();

            std::swap(billboardMatrix_.a12_, billboardMatrix_.a21_);
            std::swap(billboardMatrix_.a13_, billboardMatrix_.a31_);
            std::swap(billboardMatrix_.a23_, billboardMatrix_.a32_);

            billboardMatrix_.a41_ = 0.0f;
            billboardMatrix_.a42_ = 0.0f;
            billboardMatrix_.a43_ = 0.0f;
        }

        // �e�s���ݒ�
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", pCamera_->GetViewProjectionMatrix());
        pGlslObject_->SetUniformMatrix4x4("billboardMatrix", billboardMatrix_);
    }
}