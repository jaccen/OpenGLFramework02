/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Object/GlslObject.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Thread/Thread.h"
#include <atomic>


/* �O���錾 */
namespace Font
{
    class C_FontManager;
}

namespace Shader
{
    namespace GLSL
    {
        class C_GlslObjectManager;
    }
}


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �ʖ� */
    using LoadFunction = bool(*)();


    /* ���[�h�p�̃X���b�h�̏�� */
    struct S_LoadThreadData
    {
        std::atomic<bool> finishFlag_;                                                  ///< @brief �I���̃t���O
        LoadFunction pFunction = nullptr;                                               ///< @brief ���[�h���̊֐�
    };


    //-------------------------------------------------------------
    //!
    //! @brief ���[�h�V�[��
    //! @brief ���[�h��\���N���X
    //!
    //-------------------------------------------------------------
    class C_LoadScene : public Scene::C_BaseScene
    {
    public:
        C_LoadScene();                                                                  // �R���X�g���N�^
        ~C_LoadScene() override;                                                        // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                                     // ����������
        Scene::ecSceneReturn Update() override;                                         // �X�V����
        void Draw() override;                                                           // �`�揈��
        void Finalize() override;                                                       // �I������
    private:
        Texture::C_TextureManager* pTextureManager_ = nullptr;                          ///< @brief �e�N�X�`���}�l�[�W���[
        Texture::TextureDataPtr pTextureData_;                                          ///< @brief �e�N�X�`���f�[�^
        Font::C_FontManager* pFontManager_ = nullptr;                                   ///< @brief �t�H���g�}�l�[�W���[
        OpenGL::C_PrimitiveBufferManager* pPrimitiveBufferManager_ = nullptr;           ///< @brief �v���~�e�B�u�o�b�t�@�}�l�[�W���[
        OpenGL::C_OpenGlManager* pOpenGlManager_ = nullptr;                             ///< @brief OpenGL�}�l�[�W���[
        Shader::GLSL::C_GlslObjectManager* pGlslObjectManager_ = nullptr;               ///< @brief GLSL�I�u�W�F�N�g�}�l�[�W���[
        Camera::C_CameraManager* pCameraManager_ = nullptr;                             ///< @brief �J�����}�l�[�W���[
        int32_t fontSize_ = 32;                                                         ///< @brief �t�H���g�T�C�Y
        OpenGL::PrimitiveBufferPtr pRectangleData_;                                     ///< @brief ��`�f�[�^
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                       ///< @brief GLSL�I�u�W�F�N�g
        Camera::CameraPtr pUiCamera_;                                                   ///< @brief UI�J����
        Vector3 nowLoadingStringPosition_;                                              ///< @brief "NowLoading"�̕�����̈ʒu
        Timer::C_FrameCounter frameCounter_;                                            ///< @breif �t���[�����̃J�E���^
        Thread::C_Thread loadThread_;                                                   ///< @brief ���[�h�����p�̃X���b�h
        S_LoadThreadData loadThreadData_;                                               ///< @brief ���[�h�p�̃X���b�h�̏��
    };
}