/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/Vector/Vector4.h"
#include "../../Texture/TextureDefine.h"


/* �O���錾 */
namespace Math
{
    template<typename T>
    struct S_Matrix4x4;
};

namespace Camera
{
    class C_PerspectiveCamera;
}


//-------------------------------------------------------------
//!
//! @brief �p�[�e�B�N��
//! @brief �p�[�e�B�N���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Particle
{
    /* �ʖ� */
    using Vector2 = Math::S_Vector2<float>;                                                 // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                                 // Vector3�^
    using Vector4 = Math::S_Vector4<float>;                                                 // Vector4�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                             // Matrix4x4�^
    using InterpolationFunction = std::function<float(float, float, float)>;                // InterpolationFunction�^


    /** �p�[�e�B�N���f�[�^ */
    struct S_CreateDara
    {
        int32_t lifeFrame_ = 0;                                                             ///< @brief �����t���[����
        Vector3 position_;                                                                  ///< @brief ���W
        Vector3 velocity_;                                                                  ///< @brief ���x
        Vector3 startAcceleration_;                                                         ///< @brief �J�n���̉����x
        Vector3 endAcceleration_;                                                           ///< @brief �I�����̉����x
        float startAngle_ = 0.0f;                                                           ///< @brief �J�n���̊p�x
        float endAngle_ = 0.0f;                                                             ///< @brief �I�����̊p�x
        float startWidth_ = 0.0f;                                                           ///< @brief �J�n���̕�
        float endWidth_ = 0.0f;                                                             ///< @brief �I�����̕�
        float startHeight_ = 0.0f;                                                          ///< @brief �J�n���̍���
        float endHeight_ = 0.0f;                                                            ///< @brief �I�����̍���
        Vector4 startColor_;                                                                ///< @brief �J�n���̐F
        Vector4 endColor_;                                                                  ///< @brief �I�����̐F

        S_CreateDara() = default;                                                           //!< @brief �f�t�H���g�R���X�g���N�^
        ~S_CreateDara() = default;                                                          //!< @brief �f�X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �����t���[����
         *  @param  ���W
         *  @param  ���x
         *  @param  �J�n���̉����x
         *  @param  �I�����̉����x
         *  @param  �J�n���̊p�x
         *  @param  �I�����̊p�x
         *  @param  �J�n���̃X�P�[��
         *  @param  �I�����̃X�P�[��
         *  @param  �J�n���̐F
         *  @param  �I�����̐F
         *
         ****************************************************************/
        S_CreateDara(int32_t lifeFrame,
                     const Vector3& rPosition,
                     const Vector3& rVelocity,
                     const Vector3& rStartAcceleration,
                     const Vector3& rEndAcceleration,
                     float startAngle,
                     float endAngle,
                     float startWidth,
                     float endWidth,
                     float startHeight,
                     float endHeight,
                     const Vector4& rStartColor,
                     const Vector4& rEndColor) :

            lifeFrame_(lifeFrame),
            position_(rPosition),
            velocity_(rVelocity),
            startAcceleration_(rStartAcceleration),
            endAcceleration_(rEndAcceleration),
            startAngle_(startAngle),
            endAngle_(endAngle),
            startWidth_(startWidth),
            endWidth_(endWidth),
            startHeight_(startHeight),
            endHeight_(endHeight),
            startColor_(rStartColor),
            endColor_(rEndColor)
        {
        }
    };

    namespace
    {
        /* �Œ� */
        namespace Fixed
        {
            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.vert";               ///< @brief ���_�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.geom";             ///< @brief �W�I���g���V�F�[�_�[�̃t�@�C���p�X
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.frag";             ///< @brief �t���O�����g�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGLSL_OBJECT_ID = "ParticleSystem";                                               ///< @brief �V�F�[�_�[�I�u�W�F�N�g��ID
            }

            /* �e�N�X�`�� */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 27;                                                               ///< @brief ���j�b�g�ԍ�
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �p�[�e�B�N���V�X�e��( �C���^�[�t�F�[�X )
    //! @brief �p�[�e�B�N���V�X�e���̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_ParticleSystem
    {
    public:
        IC_ParticleSystem() = default;                                                                          // �R���X�g���N�^
        virtual ~IC_ParticleSystem() = default;                                                                 // �f�X�g���N�^
        virtual void Entry(int32_t lifeFrame,                                                                   // �p�[�e�B�N����ǉ�
                           const Vector3& rPosition,
                           const Vector3& rVelocity,
                           const Vector3& rStartAcceleration,
                           const Vector3& rEndAcceleration,
                           float startAngle = 0.0f,
                           float endAngle = 0.0f,
                           float startWidht = 1.0f,
                           float endWidth = 1.0f,
                           float startHeight = 1.0f,
                           float endHeight = 1.0f,
                           const Vector4& rStartColor = Vector4(1.0f),
                           const Vector4& rEndColor = Vector4(1.0f)) = 0;
        virtual void Entry(const S_CreateDara& rCreateData) = 0;                                                // �p�[�e�B�N���̏�񂩂���p�[�e�B�N����ǉ�
        virtual void SetMaxParticleCount(uint32_t maxParticleCount) = 0;                                        // �p�[�e�B�N���̍ő吔��ݒ�
        virtual void EnableAutoBillboard(bool validFlag = true) = 0;                                            // �r���{�[�h�̎�������L����
        virtual void SetCamera(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera) = 0;              // �J������ݒ�
        virtual void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix) = 0;                                 // �r���{�[�h�����邽�߂̍s���ݒ�
        virtual void SetExternalPower(const Vector3& rExternalPower) = 0;                                       // �O���̗͂�ݒ�
        virtual void SetModelMatrix(const Matrix4x4& rModelMatrix) = 0;                                         // ���f���s���ݒ�
        virtual void SetTextureHandle(Texture::TextureHandle textureHandle) = 0;                                // �e�N�X�`���n���h����ݒ�
        virtual void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction) = 0;          // �����x�ɗp�����Ԋ֐���ݒ�
        virtual void SetAngleInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // �p�x�ɗp�����Ԋ֐���ݒ�
        virtual void SetScaleInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // �X�P�[���ɗp�����Ԋ֐���ݒ�
        virtual void SetColorInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // �F�ɗp�����Ԋ֐���ݒ�
        virtual void SetTextureCoordUpperLeft(const Vector2& textureCoordUpperLeft) = 0;                        // �e�N�X�`�����W�̍����ݒ�
        virtual void SetTextureCoordLowerRight(const Vector2& textureCoordLowerRight) = 0;                      // �e�N�X�`�����W�̉E����ݒ�
    };


    //-------------------------------------------------------------
    //!
    //! @brief �p�[�e�B�N���X�e��
    //! @brief �p�[�e�B�N���������s�����߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_ParticleSystem : public IC_ParticleSystem
    {
    public:
        C_ParticleSystem();                                                                                 // �R���X�g���N�^
        virtual ~C_ParticleSystem();                                                                        // �f�X�g���N�^
        bool Initialize(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera,                      // ����������
                        Texture::TextureHandle textureHandle,
                        uint32_t maxParticleNumber = 10000);
        void Update();                                                                                      // �X�V����
        void Draw();                                                                                        // �`�揈��
        void Finalize();                                                                                    // �I������
        void Entry(int32_t lifeFrame,                                                                       // �p�[�e�B�N����ǉ�
                   const Vector3& rPosition,
                   const Vector3& rVelocity,
                   const Vector3& rStartAcceleration,
                   const Vector3& rEndAcceleration,
                   float startAngle = 0.0f,
                   float endAngle = 0.0f,
                   float startWidht = 1.0f,
                   float endWidth = 1.0f,
                   float startHeight = 1.0f,
                   float endHeight = 1.0f,
                   const Vector4& rStartColor = Vector4(1.0f),
                   const Vector4& rEndColor = Vector4(1.0f)) override;
        void Entry(const S_CreateDara& rCreateData) override;                                               // �p�[�e�B�N���̏�񂩂���p�[�e�B�N����ǉ�
        void SetMaxParticleCount(uint32_t maxParticleNumber) override;                                      // �p�[�e�B�N���̍ő吔��ݒ�
        void EnableAutoBillboard(bool validFlag = true) override;                                           // �r���{�[�h�̎�������L����
        void SetCamera(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera) override;             // �J������ݒ�
        void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix) override;                                // �r���{�[�h�����邽�߂̍s���ݒ�
        void SetExternalPower(const Vector3& rExternalPower) override;                                      // �O���̗͂�ݒ�
        void SetModelMatrix(const Matrix4x4& rModelMatrix) override;                                        // ���f���s���ݒ�
        void SetTextureHandle(Texture::TextureHandle textureHandle);                                        // �e�N�X�`���n���h����ݒ�
        void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction);                  // �����x�ɗp�����Ԋ֐���ݒ�
        void SetAngleInterpolationFunction(const InterpolationFunction& rFunction);                         // �p�x�ɗp�����Ԋ֐���ݒ�
        void SetScaleInterpolationFunction(const InterpolationFunction& rFunction);                         // �X�P�[���ɗp�����Ԋ֐���ݒ�
        void SetColorInterpolationFunction(const InterpolationFunction& rFunction);                         // �F�ɗp�����Ԋ֐���ݒ�
        void SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft);                               // �e�N�X�`�����W�̍����ݒ�
        void SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight);                             // �e�N�X�`�����W�̉E����ݒ�
    private:
        /* �O���錾 */
        class C_ParticleSystemImpl;

        std::unique_ptr<C_ParticleSystemImpl> upImpl_;                                                      ///< @brief �������
    };
}