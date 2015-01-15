/* �w�b�_�t�@�C�� */
#include "LoadScene.h"
#include "ConnectWarsDefine.h"
#include "Stage01Scene.h"
#include "../../Library/Font/FontManager.h"
#include "../../Library/Camera/Camera/Orthographic/OrthographicCamera.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Model/SelfMade/Loader/ModelLoader.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LoadScene::C_LoadScene() :

        // �e�N�X�`���}�l�[�W���[
        pTextureManager_(Texture::C_TextureManager::s_GetInstance()),

        // �t�H���g�}�l�[�W���[
        pFontManager_(Font::C_FontManager::s_GetInstance()),

        // �v���~�e�B�u�o�b�t�@�}�l�[�W���[
        pPrimitiveBufferManager_(OpenGL::C_PrimitiveBufferManager::s_GetInstance()), 

        // OpenGL�}�l�[�W���[
        pOpenGlManager_(OpenGL::C_OpenGlManager::s_GetInstance()),

        // GLSL�I�u�W�F�N�g�}�l�[�W���[
        pGlslObjectManager_(Shader::GLSL::C_GlslObjectManager::s_GetInstance()),

        // �J�����}�l�[�W���[
        pCameraManager_(Camera::C_CameraManager::s_GetInstance()),

        // "Now Loading"�̕�����̈ʒu
        nowLoadingStringPosition_(850.0f, 700.0f, 0.0f)

    {
        // �I���̃t���O��������
        loadThreadData_.finishFlag_ = false;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LoadScene::~C_LoadScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_LoadScene::Initialize()
    {
        // "Now Loading"������̏���
        if (GetReadyLoadString() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        // �X���b�h���쐬
        loadThread_.Create([](void* pData)
        {
            auto pThreadData = reinterpret_cast<S_LoadThreadData*>(pData);

            if (pThreadData->pFunction)
            {
                if (pThreadData->pFunction() == false) return -1;
            }

            pThreadData->finishFlag_ = true;

            return 0;
        },
        "LoadThread",
        &loadThreadData_);

        return Scene::ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ���s    �FCONTINUATIOIN
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_LoadScene::Update()
    {
        if (loadThreadData_.finishFlag_ == true)
        {
            // �X���b�h�̏I����ҋ@
            if (loadThread_.Join() == -1) return Scene::ecSceneReturn::ERROR_TERMINATION;

            // �V�[����؂�ւ�
            if (ChangeNextScene() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;
        }

        // �J�E���g�A�b�v
        frameCounter_.CountUp();

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LoadScene::Draw()
    {
        if (frameCounter_.GetCount() % 100 < 50)
        {
            pOpenGlManager_->EnableBlend(true);
            pOpenGlManager_->SetBlendFunction(OpenGL::BlendFactor::s_SOURCE_ALPHA, OpenGL::BlendFactor::s_ONE_MINUS_SOURCE_ALPHA);

            // �e�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`�����o�C���h
            pTextureManager_->SetActiveUnit(0);
            pTextureManager_->Bind(Texture::Type::s_2D, pTextureData_->handle_);

            // �[�x�̃}�X�N��L����
            pOpenGlManager_->EnableDepthMask(true);

            pGlslObject_->Begin();

            // "Now Loading"��`��
            pOpenGlManager_->DrawPrimitive(OpenGL::Primitive::s_POINT, pRectangleData_->GetVertexArrayObjectHandle(), 1);

            pGlslObject_->End();

            pTextureManager_->Unbind(Texture::Type::s_2D);
            
            pOpenGlManager_->EnableDepthMask(false);
            pOpenGlManager_->EnableBlend(false);
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LoadScene::Finalize()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���[�h���ɗ��p����֐���ݒ肷��
     *  @param  ���[�h���ɗ��p����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LoadScene::SetLoadFunction(LoadFunction pLoadFunction)
    {
        loadThreadData_.pFunction = pLoadFunction;
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[����ID��ݒ�
     *  @param  ���̃V�[����ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LoadScene::SetNextSceneId(const std::string& rNextSceneId)
    {
        nextSceneId_ = rNextSceneId;
    }


    /*************************************************************//**
     *
     *  @brief  "Now Loading"�̕�����̏�������
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_LoadScene::GetReadyLoadString()
    {
        // "Now Loading"�Ƃ��������̕`�悷�邽�߂ɕK�v�ȃI�u�W�F�N�g���쐬
        if (!pTextureManager_->GetTextureData(ID::Texture::s_pLOAD))
        {
            // �t�H���g�����[�h���A�擾
            if (!pFontManager_->GetFont(Path::Font::s_pLOAD, fontSize_))
            {
               if (pFontManager_->Load(Path::Font::s_pLOAD, fontSize_) == false) return false;
            }

            auto pFont = pFontManager_->GetFont(Path::Font::s_pLOAD, fontSize_).get();

            // �e�N�X�`�����쐬
            if (pTextureManager_->Create2DFromFont(pFont, ID::Texture::s_pLOAD, "Now Loading", 255, 255, 255) == false) return false;
        }
        
        // �e�N�X�`���f�[�^���擾
        pTextureData_ = pTextureManager_->GetTextureData(ID::Texture::s_pLOAD).get();

        // �v���~�e�B�u���쐬���A�擾
        if (!pPrimitiveBufferManager_->GetPrimitiveBuffer(ID::Primitive::s_pLOAD))
        {
            uint32_t vertexAttributeElementCountList[] = { 3 };
            OpenGL::DataEnum vertexAttributeDataTypeList[] = { OpenGL::DataType::s_FLOAT };

            pRectangleData_ = OpenGL::C_PrimitiveBuffer::s_Create(&nowLoadingStringPosition_, 1, 1, vertexAttributeElementCountList, vertexAttributeDataTypeList, OpenGL::Modify::s_STATIC);

            pPrimitiveBufferManager_->Entry(pRectangleData_, ID::Primitive::s_pLOAD);
        }
        else
        {
            pRectangleData_ = pPrimitiveBufferManager_->GetPrimitiveBuffer(ID::Primitive::s_pLOAD).get();
        }

        // �J�������쐬���A�擾
        if (!pCameraManager_->GetCamera(ID::Camera::s_pUI))
        {
            assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
            auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

            auto pOrthograhicCamera = std::make_shared<Camera::C_OrthographicCamera>();
            pOrthograhicCamera->SetClipSpace(0.0f, static_cast<float>(pMainWindow->GetWidth()), static_cast<float>(pMainWindow->GetHeight()), 0.0f);

            pUiCamera_ = pOrthograhicCamera;
            pUiCamera_->Update();
            pCameraManager_->Entry(pUiCamera_, ID::Camera::s_pUI);
        }
        else
        {
            pUiCamera_ = pCameraManager_->GetCamera(ID::Camera::s_pUI).get();
        }

        // GLSL�I�u�W�F�N�g���쐬���A�擾
        if (!pGlslObjectManager_->GetGlslObject(ID::Shader::s_pLOAD))
        {
            pGlslObject_ = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject_->CompileFromFile("Projects/Shaders/GLSL/Load/Load.vert", Shader::GLSL::Type::s_VERTEX) == false) return false;
            if (pGlslObject_->CompileFromFile("Projects/Shaders/GLSL/Load/Load.geom", Shader::GLSL::Type::s_GEOMETRY) == false) return false;
            if (pGlslObject_->CompileFromFile("Projects/Shaders/GLSL/Load/Load.frag", Shader::GLSL::Type::s_FRAGMENT) == false) return false;
            if (pGlslObject_->Link() == false) return false;

            // ���j�t�H�[���ϐ���ݒ�
            pGlslObject_->Begin();

            pGlslObject_->SetUniform1f("Width", static_cast<float>(pTextureData_->width_));
            pGlslObject_->SetUniform1f("Height", static_cast<float>(pTextureData_->height_));
            pGlslObject_->SetUniformMatrix4x4("OrthographicProjectionMatrix" , pUiCamera_->GetProjectionMatrix());
            pGlslObject_->SetUniform1i("Texture", 0);

            pGlslObject_->End();

            pGlslObjectManager_->Entry(pGlslObject_, ID::Shader::s_pLOAD);
        }
        else
        {
            pGlslObject_ = pGlslObjectManager_->GetGlslObject(ID::Shader::s_pLOAD).get();
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[���֐؂�ւ����s��
     *  @param  �Ȃ�
     *  @return �؂�ւ������Ftrue
     *  @return �؂�ւ����s�Ffalse
     *
     ****************************************************************/
    bool C_LoadScene::ChangeNextScene()
    {
        if (nextSceneId_ == ID::Scene::s_pTITLE)
        {
            
        }
        else if (nextSceneId_ == ID::Scene::s_pSTAGE01)
        {
            GetSceneChanger()->ReplaceScene(newEx C_Stage01Scene);

            return true;
        }

        return false;
    }
}