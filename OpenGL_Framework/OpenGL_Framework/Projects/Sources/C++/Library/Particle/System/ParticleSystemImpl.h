/* �w�b�_�t�@�C�� */
#include "ParticleSystem.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../Math/Matrix/Matrix4x4.h"
#include "../../Math/Easing/Easing.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../OpenGL/Manager/OpenGlManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../Camera/Camera/Perspective/PerspectiveCamera.h"
#include <vector>
#include <forward_list>


//-------------------------------------------------------------
//!
//! @brief �p�[�e�B�N��
//! @brief �p�[�e�B�N���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Particle
{
    /* �ʖ� */
    using VertexArrayObjectHandle = GLuint;                                                     // VertexArrayObjectHandle�^
    using VertexBufferObjectHandle = GLuint;                                                    // VertexBufferObjectHandle�^


    /** �p�[�e�B�N����� */
    struct S_ParticleInfo
    {
        int32_t lifeFrame_ = 0;                                                                 ///< @brief �����t���[����
        int32_t elapsedFrame_ = 0;                                                              ///< @brief �o�߃t���[����
        Vector3 position_;                                                                      ///< @brief ���W
        Vector3 velocity_;                                                                      ///< @brief ���x
        Vector3 acceleration_;                                                                  ///< @brief �����x
        Vector3 startAcceleration_;                                                             ///< @brief �J�n���̉����x
        Vector3 endAcceleration_;                                                               ///< @brief �I�����̉����x
        float angle_ = 0.0f;                                                                    ///< @brief �p�x
        float startAngle_ = 0.0f;                                                               ///< @brief �J�n���̊p�x
        float endAngle_ = 0.0f;                                                                 ///< @brief �I�����̊p�x
        float width_ = 0.0f;                                                                    ///< @brief ��
        float startWidth_ = 0.0f;                                                               ///< @brief �J�n���̕�
        float endWidth_ = 0.0f;                                                                 ///< @brief �I�����̕�
        float height_ = 0.0f;                                                                   ///< @brief ����
        float startHeight_ = 0.0f;                                                              ///< @brief �J�n���̍���
        float endHeight_ = 0.0f;                                                                ///< @brief �J�n���̍���
        Vector4 color_;                                                                         ///< @brief �F
        Vector4 startColor_;                                                                    ///< @brief �J�n���̐F
        Vector4 endColor_;                                                                      ///< @brief �I�����̐F

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �����t���[����
         *  @param  �o�߃t���[����
         *  @param  ���W
         *  @param  ���x
         *  @param  �����x
         *  @param  �J�n���̉����x
         *  @param  �I�����̉����x
         *  @param  �p�x
         *  @param  �J�n���̊p�x
         *  @param  �I�����̊p�x
         *  @param  �X�P�[��
         *  @param  �J�n���̃X�P�[��
         *  @param  �I�����̃X�P�[��
         *  @param  �F
         *  @param  �J�n���̐F
         *  @param  �I�����̐F
         *
         ****************************************************************/
        S_ParticleInfo(int32_t lifeFrame,
                       int32_t elapsedFrame,
                       const Vector3& rPosition,
                       const Vector3& rVelocity,
                       const Vector3& rAcceleration,
                       const Vector3& rStartAcceleration,
                       const Vector3& rEndAcceleration,
                       float angle,
                       float startAngle,
                       float endAngle,
                       float width,
                       float startWidth,
                       float endWidth,
                       float height,
                       float startHeight,
                       float endHeight,
                       const Vector4& rColor,
                       const Vector4& rStartColor,
                       const Vector4& rEndColor) :

                       // �e����ݒ�
                       lifeFrame_(lifeFrame),
                       elapsedFrame_(elapsedFrame),
                       position_(rPosition),
                       velocity_(rVelocity),
                       acceleration_(rAcceleration),
                       startAcceleration_(rStartAcceleration),
                       endAcceleration_(rEndAcceleration),
                       angle_(angle),
                       startAngle_(startAngle),
                       endAngle_(endAngle),
                       width_(width),
                       startWidth_(startWidth),
                       endWidth_(endWidth),
                       height_(height),
                       startHeight_(startHeight),
                       endHeight_(endHeight),
                       color_(rColor),
                       startColor_(rStartColor),
                       endColor_(rEndColor)
        {
        }
    };


    /** �p�[�e�B�N���̒��_��� */
    struct S_ParticleVertex
    {
        Vector3 position_;                                                                              ///< @brief ���W
        float angle_ = 0.0f;                                                                            ///< @brief �p�x
        float width_ = 0.0f;                                                                            ///< @brief ��
        float height_ = 0.0f;                                                                           ///< @brief ����
        Vector4 color_;                                                                                 ///< @brief �F
    };

    //-------------------------------------------------------------
    //!
    //! @brief �p�[�e�B�N���X�e���C���v�������g
    //! @brief �p�[�e�B�N�V�X�e���̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_ParticleSystem::C_ParticleSystemImpl
    {
    private:
        
    public:
        C_ParticleSystemImpl();                                                                         // �R���X�g���N�^  
        ~C_ParticleSystemImpl();                                                                        // �f�X�g���N�^
        bool Initialize(const Camera::CameraPtr& prCamera,                                              // ����������
                        Texture::TextureHandle textureHandle,
                        uint32_t maxParticleCount);
        void Update();                                                                                  // �X�V����
        void Draw();                                                                                    // �`�揈��
        void Finalize();                                                                                // �I������
        void Entry(const S_CreateDara& rCreateData);                                                    // �o�^����
        void SetMaxParticleCount(uint32_t maxParticleNumber);                                           // �p�[�e�B�N���̍ő吔��ݒ�
        void EnableModelMatrix(bool validFlag);                                                         // ���f���s���L����
        void EnableAutoBillboard(bool validFlag);                                                       // �r���{�[�h�̎�������L����
        void SetCamera(const Camera::CameraPtr& prCamera);                                              // �J������ݒ�
        void SetModelMatrix(const Matrix4x4& rModelMatrix);                                             // ���f���s���ݒ�
        void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix);                                     // �r���{�[�h�����邽�߂̍s���ݒ�
        void SetExternalPower(const Vector3& rExternalPower);                                           // �O���̗͂�ݒ�
        void SetTextureHandle(Texture::TextureHandle textureHandle);                                    // �e�N�X�`���n���h����ݒ�
        void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction);              // �����x�ɗp�����Ԋ֐���ݒ�
        void SetAngleInterpolationFunction(const InterpolationFunction& rFunction);                     // �p�x�ɗp�����Ԋ֐���ݒ�
        void SetScaleInterpolationFunction(const InterpolationFunction& rFunction);                     // �X�P�[���ɗp�����Ԋ֐���ݒ�
        void SetColorInterpolationFunction(const InterpolationFunction& rFunction);                     // �F�ɗp�����Ԋ֐���ݒ�
        virtual void SetTextureCoordUpperLeft(const Vector2& textureCoordUpperLeft);                    // �e�N�X�`�����W�̍����ݒ�
        virtual void SetTextureCoordLowerRight(const Vector2& textureCoordLowerRight);                  // �e�N�X�`�����W�̉E����ݒ�
    private:
        std::string id_;                                                                                ///< @brief ID
        std::forward_list<S_ParticleInfo> infoList_;                                                    ///< @brief ���̃��X�g
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                       ///< @brief GLSL�I�u�W�F�N�g
        Vector3 externalPower_;                                                                         ///< @brief �O���̗�
        std::vector<S_ParticleVertex> vertices_;                                                        ///< @brief ���_�f�[�^
        VertexBufferObjectHandle vertexBufferObjectHandle_ = 0;                                         ///< @brief ���_�o�b�t�@�I�u�W�F�N�g�n���h��
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                           ///< @brief ���_�z��I�u�W�F�N�g�n���h��
        Camera::CameraPtr pCamera_;                                                                     ///< @brief �J����
        Matrix4x4 modelMatrix_;                                                                         ///< @brief ���f���s��
        Matrix4x4 billboardMatrix_;                                                                     ///< @brief �r���{�[�h�����邽�߂̍s��
        bool autoBillboardFlag_ = true;                                                                 ///< @brief �r���{�[�h�̎�������������t���O
        Texture::TextureHandle textureHandle_ = 0;                                                      ///< @brief �e�N�X�`���n���h��
        uint32_t drawParticleCount_ = 0;                                                                ///< @brief �`�悷��p�[�e�B�N���̃J�E���^
        InterpolationFunction accelerationInterpolationFunction_ = Math::C_Easing<float>::s_Linear;     ///< @brief �����x�ɗp�����Ԋ֐�
        InterpolationFunction angleInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief �p�x�ɗp�����Ԋ֐�
        InterpolationFunction scaleInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief �X�P�[���ɗp�����Ԋ֐�
        InterpolationFunction colorInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief �F�ɗp�����Ԋ֐�
        Vector2 textureCoordUpperLeft_ = Vector2(0.0f);                                                 ///< @brief �e�N�X�`�����W�̍���
        Vector2 textureCoordLowerRight_ = Vector2(1.0f);                                                ///< @brief �e�N�X�`�����W�̉E��

        void CreateVertexArrayObject();                                                                 // ���_�z��I�u�W�F�N�g���쐬
        void DeleteVertexArrayObject();                                                                 // ���_�z��I�u�W�F�N�g��j��
        void RewriteVertex();                                                                           // ���_�f�[�^�̏�������
        void AddParticle(const Vector3& rPosition,                                                      // �p�[�e�B�N���̒ǉ�����
                         float angle,
                         float width,
                         float height,
                         const Vector4& rColor);
        void ResetParticle();                                                                           // �`�悷��p�[�e�B�N���̃��Z�b�g
        bool UpdateParticle(S_ParticleInfo& rInfo);                                                     // �p�[�e�B�N���̍X�V����
        void SetUniformVariable();                                                                      // ���j�t�H�[���ϐ���ݒ�
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystemImpl::C_ParticleSystemImpl() :

        // GLSL�I�u�W�F�N�g
        pGlslObject_(std::make_shared<Shader::GLSL::C_GlslObject>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystemImpl::~C_ParticleSystemImpl()
    {
        if (vertexArrayObjectHandle_ != 0) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �J����
     *  @param  �e�N�X�`���n���h��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_ParticleSystem::C_ParticleSystemImpl::Initialize(const Camera::CameraPtr& prCamera,
                                                            Texture::TextureHandle textureHandle,
                                                            uint32_t maxParticleCount)
    {
        // GLSL�I�u�W�F�N�g���쐬���A�o�^
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : ���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : �W�I���g���V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : �t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : �V�F�[�_�[�̃����N�Ɏ��s���܂����B\n");

                return false;
            }

            // GLSL�I�u�W�F�N�g��ێ����A�o�^
            pGlslObject_ = pGlslObject;
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject_, Fixed::Shader::s_pGLSL_OBJECT_ID);
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        // �e�N�X�`�����j�b�g��ݒ�
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        // ���_�z��I�u�W�F�N�g���쐬
        CreateVertexArrayObject();

        // �J�����ƃe�N�X�`���n���h����ݒ�
        SetCamera(prCamera);
        SetTextureHandle(textureHandle);

        // ���_�̗̈���m��
        vertices_.resize(maxParticleCount);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Update()
    {
        // �`�悷��p�[�e�B�N�������Z�b�g
        ResetParticle();

        // ���[�v�J�E���^
        int32_t loopCount = 0;

        // �C�e���[�^
        auto iterator = infoList_.begin();

        // �p�[�e�B�N���̍X�V
        while (iterator != infoList_.end())
        {
            if (UpdateParticle(*iterator) == false)
            {
                iterator = infoList_.erase_after(std::next(infoList_.before_begin(), loopCount));
                continue;
            }

            ++iterator;
            ++loopCount;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Draw()
    {
        // ���_�̏�������
        RewriteVertex();

        // �V�F�[�_�[�̎g�p�J�n
        pGlslObject_->Begin();

        // ���j�t�H�[���ϐ���ݒ�
        SetUniformVariable();

        // �e�N�X�`���}�l�[�W���[��OpenGL�}�l�[�W���[���擾
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();
        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        // �u�����h��L�������A�u�����h�Ɏg�p����֐���ݒ�
        pOpenGlManager->EnableBlend(true);
        pOpenGlManager->SetBlendFunction(OpenGL::BlendFactor::s_SOURCE_ALPHA, OpenGL::BlendFactor::s_ALL_ONE);

        // �J�����O�𖳌���
        pOpenGlManager->EnableCulling(false);

        // �[�x�̃}�X�N��L����
        pOpenGlManager->EnableDepthMask(true);

        // �A�N�e�B�u�ȃe�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`�����o�C���h
        pTextureManager->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        pTextureManager->Bind(Texture::Type::s_2D, textureHandle_);

        // �p�[�e�B�N����`��
        const int32_t BYTE_OFFSET = 0;

        glBindVertexArray(vertexArrayObjectHandle_);
        ::glDrawArrays(GL_POINTS, BYTE_OFFSET, drawParticleCount_);
        glBindVertexArray(0);


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
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Finalize()
    {
        // ���_�z��I�u�W�F�N�g��j��
        DeleteVertexArrayObject();

        // ���̃��X�g�ƒ��_���폜
        infoList_.clear();
        vertices_.clear();

        // �`�悷��p�[�e�B�N���̐������Z�b�g
        drawParticleCount_ = 0;

        // GLSL�I�u�W�F�N�g�̊Ǘ���j��
        pGlslObject_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Entry(const S_CreateDara& rCreateData)
    {
        // �ő吔�𒴂��Ă����ꍇ�͉������Ȃ�
        if (drawParticleCount_ >= vertices_.size()) return;

        // �������X�g�ɒǉ�
        const int32_t ELAPSED_FRAME = 0;

        infoList_.emplace_front(rCreateData.lifeFrame_,
                                ELAPSED_FRAME,
                                rCreateData.position_,
                                rCreateData.velocity_,
                                rCreateData.startAcceleration_,
                                rCreateData.startAcceleration_,
                                rCreateData.endAcceleration_,
                                rCreateData.startAngle_,
                                rCreateData.startAngle_,
                                rCreateData.endAngle_,
                                rCreateData.startWidth_,
                                rCreateData.startWidth_,
                                rCreateData.endWidth_,
                                rCreateData.startHeight_,
                                rCreateData.startHeight_,
                                rCreateData.endHeight_,
                                rCreateData.startColor_,
                                rCreateData.startColor_,
                                rCreateData.endColor_);

        // �p�[�e�B�N����ǉ�
        AddParticle(rCreateData.position_, rCreateData.startAngle_, rCreateData.startWidth_, rCreateData.startHeight_, rCreateData.startColor_);
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���̍ő吔�̐ݒ���s��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetMaxParticleCount(uint32_t maxParticleCount)
    {
        // ���_�̗̈���Ċm��
        vertices_.resize(maxParticleCount);

        // ���_�z��I�u�W�F�N�g���쐬������
        DeleteVertexArrayObject();
        CreateVertexArrayObject();

        // �X�V����
        Update();
    }


    /*************************************************************//**
     *
     *  @brief  �r���{�[�h�̎�������L��������
     *  @param  �L�����𔻒f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::EnableAutoBillboard(bool validFlag)
    {
        autoBillboardFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �J������ݒ肷��
     *  @param  �J����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetCamera(const Camera::CameraPtr& prCamera)
    {
        pCamera_ = prCamera;
    }


    /*************************************************************//**
     *
     *  @brief  ���f���s���ݒ肷��
     *  @param  ���f���s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetModelMatrix(const Matrix4x4& rModelMatrix)
    {
        modelMatrix_ = rModelMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �r���{�[�h�����邽�߂̍s���ݒ肷��
     *  @param  �r���{�[�h�����邽�߂̍s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetBillboardMatrix(const Matrix4x4& rBillboardMatrix)
    {
        billboardMatrix_ = rBillboardMatrix;
        autoBillboardFlag_ = false;
    }


    /*************************************************************//**
     *
     *  @brief  �O���̗͂�ݒ肷��
     *  @param  �O���̗�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetExternalPower(const Vector3& rExternalPower)
    {
        externalPower_ = rExternalPower;
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���n���h����ݒ肷��
     *  @param  �e�N�X�`���n���h��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureHandle(Texture::TextureHandle textureHandle)
    {
        textureHandle_ = textureHandle;
    }


    /*************************************************************//**
     *
     *  @brief  �����x�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �����x�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction)
    {
        accelerationInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  �p�x�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �p�x�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetAngleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        angleInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  �X�P�[���ɗp�����Ԋ֐���ݒ肷��
     *  @param  �X�P�[���ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetScaleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        scaleInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  �F�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �F�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetColorInterpolationFunction(const InterpolationFunction& rFunction)
    {
        colorInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`�����W�̍����ݒ�
     *  @param  �e�N�X�`�����W�̍���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft)
    {
        textureCoordUpperLeft_ = rTextureCoordUpperLeft;
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`�����W�̉E����ݒ�
     *  @param  �e�N�X�`�����W�̉E��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight)
    {
        textureCoordLowerRight_ = rTextureCoordLowerRight;
    }


    /*************************************************************//**
     *
     *  @brief  ���_�z��I�u�W�F�N�g���쐬����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::CreateVertexArrayObject()
    {
        // ���_�o�b�t�@�̃C���f�b�N�X
        GLuint vertexBufferIndex = 0;

        // �o�C�g�̑���
        const int32_t BYTE_TOTAL_NUMBER = sizeof(S_ParticleVertex);

        // ���_�o�b�t�@�I�u�W�F�N�g���쐬
        const int32_t CREATE_VERTEX_BUFFER_OBJECT_NUMBER = 1;
        glGenBuffers(CREATE_VERTEX_BUFFER_OBJECT_NUMBER, &vertexBufferObjectHandle_);

        // ���_�o�b�t�@���o�C���h���A�S�Ẵf�[�^��]��
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle_);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * BYTE_TOTAL_NUMBER, vertices_.data(), OpenGL::Modify::s_DYNAMIC);

        // ���_�z��I�u�W�F�N�g���쐬���A�o�C���h
        const int32_t CREATE_VERTEX_ARRAY_OBJECT_NUMBER = 1;
        glGenVertexArrays(CREATE_VERTEX_ARRAY_OBJECT_NUMBER, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);

        // ���_�z��I�u�W�F�N�g�ɍ��W���o�C���h
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        const int32_t POSITION_BYTE_OFFSET = 0;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(POSITION_BYTE_OFFSET));
        ++vertexBufferIndex;

        // ���_�z��I�u�W�F�N�g�Ɋp�x���o�C���h
        const int32_t ANGLE_ELEMENT_NUMBER = 1;
        const int32_t ANGLE_BYTE_OFFSET = sizeof(float)* POSITION_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, ANGLE_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(ANGLE_BYTE_OFFSET));
        ++vertexBufferIndex;

        // ���_�z��I�u�W�F�N�g�ɕ��ƍ������o�C���h
        const int32_t WIDTH_ELEMENT_NUMBER = 1;
        const int32_t WIDTH_BYTE_OFFSET = ANGLE_BYTE_OFFSET + sizeof(float)* ANGLE_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, WIDTH_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(WIDTH_BYTE_OFFSET));
        ++vertexBufferIndex;

        const int32_t HEIGHT_ELEMENT_NUMBER = 1;
        const int32_t HEIGHT_BYTE_OFFSET = WIDTH_BYTE_OFFSET + sizeof(float)* WIDTH_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, HEIGHT_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(HEIGHT_BYTE_OFFSET));
        ++vertexBufferIndex;

        // ���_�z��I�u�W�F�N�g�ɐF���o�C���h
        const int32_t COLOR_ELEMENT_NUMBER = 4;
        const int32_t COLOR_BYTE_OFFSET = HEIGHT_BYTE_OFFSET + sizeof(float)* HEIGHT_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, COLOR_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(COLOR_BYTE_OFFSET));

        // �e�I�u�W�F�N�g���A���o�C���h
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  ���_�z��I�u�W�F�N�g��j������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::DeleteVertexArrayObject()
    {
        // �e�o�b�t�@���폜
        glDeleteBuffers(1, &vertexBufferObjectHandle_);
        glDeleteVertexArrays(1, &vertexArrayObjectHandle_);

        vertexArrayObjectHandle_ = 0;
        vertexBufferObjectHandle_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  ���_�f�[�^�̏����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::RewriteVertex()
    {
        assert(vertexBufferObjectHandle_ != 0);

        // ���_�o�b�t�@�I�u�W�F�N�g���o�C���h���A�}�b�v
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle_);
        S_ParticleVertex* pVertices = reinterpret_cast<S_ParticleVertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        for (size_t i = 0; i < drawParticleCount_; ++i) pVertices[i] = vertices_[i];

        // ���_�o�b�t�@���A���}�b�v���A�A���o�C���h
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���̒ǉ����s��
     *  @param  ���W
     *  @param  �p�x
     *  @param  ��
     *  @param  ����
     *  @param  �F
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::AddParticle(const Vector3& rPosition,
                                                             float angle,
                                                             float width,
                                                             float height,
                                                             const Vector4& rColor)
    {
        // ���_����ݒ肵�A�`�悷��p�[�e�B�N���̐���1����
        auto& vertex = vertices_[drawParticleCount_];

        vertex.position_ = rPosition;
        vertex.angle_ = angle;
        vertex.width_ = width;
        vertex.height_ = height;
        vertex.color_ = rColor;

        ++drawParticleCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�悷��p�[�e�B�N�������Z�b�g����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::ResetParticle()
    {
        drawParticleCount_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���̍X�V�������s��
     *  @param  �p�[�e�B�N���̏��
     *  @return �p�[�e�B�N���𑱍s�Ftrue
     *  @return �p�[�e�B�N�����I���Ffalse
     *
     ****************************************************************/
    bool C_ParticleSystem::C_ParticleSystemImpl::UpdateParticle(S_ParticleInfo& rInfo)
    {
        // �o�߃t���[������1���₵�A�����t���[�����ɒB���Ă��Ȃ����m�F����
        ++rInfo.elapsedFrame_;
        if (rInfo.elapsedFrame_ > rInfo.lifeFrame_) return false;

        // ��ԌW�������߂�
        float coefficient = static_cast<float>(rInfo.elapsedFrame_) / static_cast<float>(rInfo.lifeFrame_);

        // ���x�ɉ����x�ƊO���̗͂�������
        rInfo.velocity_.x_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.x_, rInfo.endAcceleration_.x_, coefficient);
        rInfo.velocity_.y_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.y_, rInfo.endAcceleration_.y_, coefficient);
        rInfo.velocity_.z_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.z_, rInfo.endAcceleration_.z_, coefficient);
        rInfo.velocity_ += externalPower_;

        // ���W�ɑ��x��������
        rInfo.position_ += rInfo.velocity_;

        // �p�x�E���E���������߂�
        rInfo.angle_ = angleInterpolationFunction_(rInfo.startAngle_, rInfo.endAngle_, coefficient);
        rInfo.width_ = scaleInterpolationFunction_(rInfo.startWidth_, rInfo.endWidth_, coefficient);
        rInfo.height_ = scaleInterpolationFunction_(rInfo.startHeight_, rInfo.endHeight_, coefficient);

        // �F�����߂�
        rInfo.color_.red_ = colorInterpolationFunction_(rInfo.startColor_.red_, rInfo.endColor_.red_, coefficient);
        rInfo.color_.green_ = colorInterpolationFunction_(rInfo.startColor_.green_, rInfo.endColor_.green_, coefficient);
        rInfo.color_.blue_ = colorInterpolationFunction_(rInfo.startColor_.blue_, rInfo.endColor_.blue_, coefficient);
        rInfo.color_.alpha_ = colorInterpolationFunction_(rInfo.startColor_.alpha_, rInfo.endColor_.alpha_, coefficient);

        // �p�[�e�B�N����ǉ�
        AddParticle(rInfo.position_, rInfo.angle_, rInfo.width_, rInfo.height_, rInfo.color_);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t�H�[���ϐ��̐ݒ���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetUniformVariable()
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
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", modelMatrix_);
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", pCamera_->GetViewProjectionMatrix());
        pGlslObject_->SetUniformMatrix4x4("billboardMatrix", billboardMatrix_);
        pGlslObject_->SetUniformVector2("textureCoordUpperLeft", textureCoordUpperLeft_);
        pGlslObject_->SetUniformVector2("textureCoordLowerRight", textureCoordLowerRight_);
    }
}