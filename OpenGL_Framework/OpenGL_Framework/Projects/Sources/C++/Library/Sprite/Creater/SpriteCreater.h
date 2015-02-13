/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Camera/Manager/CameraManager.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Math/Vector/Vector4.h"
#include "../../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief �X�v���C�g
//! @brief �X�v���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sprite
{
    /* �O���錾 */
    class IC_SpriteCreater;


    /* �ʖ� */
    using Vector2 = Math::S_Vector2<float>;                                                                 // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                                                 // Vector3�^
    using Vector4 = Math::S_Vector4<float>;                                                                 // Vector4�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                             // Matrix4x4�^
    using SpriteCreaterWeakPtr = std::weak_ptr<IC_SpriteCreater>;                                           // SpriteCreaterWeakPtr�^


    /** �쐬�f�[�^ */
    struct S_CreateData
    {
        Vector3 position_;                                                                                  ///< @brief ���W
        Vector2 size_;                                                                                      ///< @brief �T�C�Y
        float angle_ = 0.0f;                                                                                ///< @brief �p�x
        Vector4 color_;                                                                                     ///< @brief �F
        Vector2 textureUpperLeft_;                                                                          ///< @brief �e�N�X�`���̍�����W
        Vector2 textureLowerRight_;                                                                         ///< @brief �e�N�X�`���̉E�����W

        S_CreateData() = default;                                                                           //!< @brief �f�t�H���g�R���X�g���N�^
        ~S_CreateData() = default;                                                                          //!< @brief �f�X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  ���W
         *  @param  �T�C�Y
         *  @param  �p�x
         *  @param  �F
         *  @param  �e�N�X�`���̍�����W
         *  @param  �e�N�X�`���̉E�����W
         *
         ****************************************************************/
        S_CreateData(const Vector3& rPosition,
                     const Vector2& rSize,
                     float angle,
                     const Vector4& rColor,
                     const Vector2& rTextureUpperLeft,
                     const Vector2& rTextureLowerRight) :

            position_(rPosition),
            size_(rSize),
            angle_(angle),
            color_(rColor),
            textureUpperLeft_(rTextureUpperLeft),
            textureLowerRight_(rTextureLowerRight)

        {
        }
    };


    /* �X�v���C�g�̒��_ */
    struct S_SpriteVertex
    {
        Vector3 position_;                                                                                  ///< @brief ���W
        Vector2 size_;                                                                                      ///< @brief �T�C�Y
        float angle_ = 0.0f;                                                                                ///< @brief �p�x
        Vector4 color_;                                                                                     ///< @brief �F
        Vector2 textureUpperLeft_;                                                                          ///< @brief �e�N�X�`���̍�����W
        Vector2 textureLowerRight_;                                                                         ///< @brief �e�N�X�`���̉E�����W
        Vector2 textureSize_;                                                                               ///< @brief �e�N�X�`���̃T�C�Y
    };


    namespace
    {
        /* �Œ� */
        namespace Fixed
        {
            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.vert";               ///< @brief ���_�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.geom";             ///< @brief �W�I���g���V�F�[�_�[�̃t�@�C���p�X
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.frag";             ///< @brief �t���O�����g�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGLSL_OBJECT_ID = "SpriteCreater";                                            ///< @brief �V�F�[�_�[�I�u�W�F�N�g��ID
            }

            /* �v���~�e�B�u */
            namespace Primitive
            {
                const char* s_pSPRITE_ID = "SpritePrimitive";                                               ///< @brief �X�v���C�g�p�̃v���~�e�B�uID
            }

            /* �e�N�X�`�� */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 28;                                                           ///< @brief ���j�b�g�ԍ�
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �X�v���C�g�N���G�C�^�[( �C���^�[�t�F�[�X )
    //! @brief �X�v���C�g�N���G�C�^�[�̃C���^�[�t�F�[�X�N���X
    //!
    //-------------------------------------------------------------
    class IC_SpriteCreater
    {
    public:
        IC_SpriteCreater() = default;                                                                       //!< @brief �R���X�g���N�^
        virtual ~IC_SpriteCreater() = default;                                                              //!< @brief �f�X�g���N�^
        virtual void Entry(const Vector3& rPosition,                                                        //!< @brief �o�^����
                           const Vector2& rSize,
                           float angle,
                           const Vector4& rColor,
                           const Vector2& rTextureUpperLeft,
                           const Vector2& rTextureLowerRight) = 0;
        virtual void Entry(const S_CreateData& rCreateData) = 0;                                            //!< @brief �o�^����
        virtual void SetAutoBillboardFlag(bool autoBillboardFlag = true) = 0;                               //!< @brief �r���{�[�h�̎�������������t���O��ݒ�
        virtual void SetCamera(const Camera::CameraPtr& prCamera) = 0;                                      //!< @brief �J������ݒ�
        virtual void SetCameraType(Camera::eType cameraType) = 0;                                           //!< @brief �J�����̎�ނ�ݒ�
    };


    //-------------------------------------------------------------
    //!
    //! @brief �X�v���C�g�N���G�C�^�[
    //! @brief �X�v���C�g�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_SpriteCreater : public IC_SpriteCreater
    {
    public:
        C_SpriteCreater();                                                                                  // �R���X�g���N�^
        virtual ~C_SpriteCreater() override;                                                                // �f�X�g���N�^
        bool Initialize(const Camera::CameraPtr& prCamera,                                                  // ����������
                        const Texture::TextureDataPtr& prTextureData,
                        uint32_t maxSpriteCount = 100);
        void Draw();                                                                                        // �`�揈��
        void Finalize();                                                                                    // �I������
        void Entry(const Vector3& rPosition,                                                                // �o�^����
                   const Vector2& rSize,                                   
                   float angle,                                            
                   const Vector4& rColor,                                  
                   const Vector2& rTextureUpperLeft,                       
                   const Vector2& rTextureLowerRight);                     
        void Entry(const S_CreateData& rCreateData);                                                        // �o�^����
        void SetAutoBillboardFlag(bool autoBillboardFlag = true);                                           // �r���{�[�h�̎�������������t���O��ݒ�
        void SetCamera(const Camera::CameraPtr& prCamera);                                                  // �J������ݒ�
        void SetCameraType(Camera::eType cameraType);                                                       // �J�����̎�ނ�ݒ�
    private:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                           ///< @brief GLSL�I�u�W�F�N�g
        Camera::CameraPtr pCamera_;                                                                         ///< @brief �J����
        Texture::TextureDataPtr pTextureData_;                                                              ///< @brief �e�N�X�`�����
        OpenGL::PrimitiveBufferPtr pPointDatas_;                                                            ///< @brief �_�̏��
        std::vector<S_SpriteVertex> vertices_;                                                              ///< @brief ���_
        uint32_t drawSpriteCount_ = 0;                                                                      ///< @brief �`�悷��X�v���C�g�̐�
        Matrix4x4 billboardMatrix_;                                                                         ///< @brief �r���{�[�h�s��
        bool autoBillboardFlag_ = true;                                                                     ///< @brief �r���{�[�h�̎�������������t���O
        int32_t subroutineIndices_[2];                                                                      ///< @brief �T�u���[�`���̃C���f�b�N�X
        Camera::eType cameraType_ = Camera::PERSPECTIVE;                                                    ///< @brief �J�����̎��

        void SetUniformVariable();                                                                          // ���j�t�H�[���ϐ���ݒ�
    };
}