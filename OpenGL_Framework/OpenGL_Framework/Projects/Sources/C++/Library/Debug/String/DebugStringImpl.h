/* �w�b�_�t�@�C�� */
#include "DebugString.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Font/FontManager.h"
#include "../../Math/Matrix/Matrix4x4.h"
#include "../Helper/DebugHelper.h"
#include "../../Window/Manager/WindowManager.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../OpenGL/Manager/OpenGlManager.h"
#include "../../Common/CommonHelper.h"


//-------------------------------------------------------------
//!
//! @brief �f�o�b�O
//! @brief �f�o�b�O�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Debug
{
    /* �ʖ� */
    using VertexArrayObjectHandle = GLuint;                                                     // VertexArrayObjectHandle�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                 // Matrix4x4�^


    //-------------------------------------------------------------
    //!
    //! @brief �f�o�b�O�X�g�����O�C���v�������g
    //! @brief �f�o�b�O�X�g�����O�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_DebugString::C_DebugStringImpl
    {
    public:
        C_DebugStringImpl();                                                                    // �R���X�g���N�^                                  
        ~C_DebugStringImpl();                                                                   // �f�X�g���N�^
        bool Initialize(const std::string& rFontFilePath,                                       // ����������
                        int32_t fontSize);
        void Draw(const std::string& rString,                                                     // �`�揈��
                  const Vector3& rPosition,
                  float scale,
                  uint8_t red,
                  uint8_t green,
                  uint8_t blue,
                  ecTypographicAlignment alignment);
        void Finalize();                                                                        // �I������
    private:
        Font::FontPtr pFont_;                                                                   ///< @brief �t�H���g
        std::string fontFilePath_;                                                              ///< @brief �t�H���g�̃t�@�C���p�X
        int32_t fontSize_ = 0;                                                                  ///< @brief �t�H���g�̃T�C�Y
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                               ///< @brief GLSL�I�u�W�F�N�g
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                   ///< @brief ���_�z��I�u�W�F�N�g�̃n���h��
        Matrix4x4 orthographicProjectionMatrix_;                                                ///< @brief �����e�̎ˉe�s��

        bool LoadFont(const std::string& rFilePath, int32_t size);                              // �t�H���g�̃��[�h����
        bool CreateAndEntryGlslObject();                                                        // GLSL�I�u�W�F�N�g�̍쐬�Ɠo�^
        void CreateVertexArrayObject();                                                         // ���_�z��I�u�W�F�N�g�̍쐬
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_DebugString::C_DebugStringImpl::C_DebugStringImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_DebugString::C_DebugStringImpl::~C_DebugStringImpl()
    {
        if (vertexArrayObjectHandle_ != 0) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �t�H���g�̃t�@�C���p�X
     *  @param  �t�H���g�̃T�C�Y
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::Initialize(const std::string& rFontFilePath,
                                                      int32_t fontSize)
    {
        // �t�H���g�̃��[�h����
        if (LoadFont(rFontFilePath, fontSize) == false) return false;

        // GLSL�I�u�W�F�N�g���쐬���A�o�^
        if (CreateAndEntryGlslObject() == false) return false;
        
        // ���_�z��I�u�W�F�N�g���쐬
        CreateVertexArrayObject();
        
        // ���j�t�H�[���ϐ���ݒ�
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("Texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        // �E�B���h�E�̃T�C�Y�Ő����e�̎ˉe�s����쐬
        assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
        auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();
        
        orthographicProjectionMatrix_ = Matrix4x4::s_CreateOrthographicProjection(0.0f,
                                                                                  static_cast<float>(pMainWindow->GetWidth()),
                                                                                  static_cast<float>(pMainWindow->GetHeight()), 
                                                                                  0.0f);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �f�o�b�N�t�H���g�̕`�揈�����s��
     *  @param  ������
     *  @param  ���W
     *  @param  �X�P�[��
     *  @param  ��
     *  @param  ��
     *  @param  ��
     *  @param  ��������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::Draw(const std::string& rString,
                                                const Vector3& rPosition,
                                                float scale,
                                                uint8_t red,
                                                uint8_t green,
                                                uint8_t blue,
                                                ecTypographicAlignment alignment)
    {
        // �A���t�@��L���ɂ���
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableBlend(true);
        OpenGL::C_OpenGlManager::s_GetInstance()->SetBlendFunction(OpenGL::BlendFactor::s_SOURCE_ALPHA, OpenGL::BlendFactor::s_ONE_MINUS_SOURCE_ALPHA);

        // �t�H���g����e�N�X�`�����쐬
        static const char* s_pFONT_ID = "DebugFontTexture";

        assert(!Texture::C_TextureManager::s_GetInstance()->GetTextureData(s_pFONT_ID));
        Texture::C_TextureManager::s_GetInstance()->Create2DFromFont(pFont_, s_pFONT_ID, Common::C_CommonHelper::s_ConvertShiftJisToUtf8(rString), red, green, blue);

        // �e�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`���̃o�C���h
        auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(s_pFONT_ID).get();

        Texture::C_TextureManager::s_GetInstance()->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        Texture::C_TextureManager::s_GetInstance()->Bind(Texture::Type::s_2D, pTextureData->handle_);

        // �[�x�̃}�X�N��L����
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableDepthMask(true);

        // �V�F�[�_�[�̎g�p�J�n
        pGlslObject_->Begin();

        // �e�N�X�`���̕��ƍ�����ݒ�
        pGlslObject_->SetUniform1f("Width", static_cast<float>(pTextureData->width_ * scale));
        pGlslObject_->SetUniform1f("Height", static_cast<float>(pTextureData->height_ * scale));
        pGlslObject_->SetUniformVector3("Position", rPosition);
        pGlslObject_->SetUniformMatrix4x4("OrthographicProjectionMatrix", orthographicProjectionMatrix_);
        pGlslObject_->SetUniform1i("Alignment", static_cast<int32_t>(alignment));

        // �X�v���C�g�̕`��
        const int32_t VERTEX_NUMBER = 1;
        const int32_t BYTE_OFFSET = 0;

        glBindVertexArray(vertexArrayObjectHandle_);
        glDrawArrays(GL_POINTS, BYTE_OFFSET, VERTEX_NUMBER);
        glBindVertexArray(0);

        // �V�F�[�_�[�̎g�p�I��
        pGlslObject_->End();

        // �e�N�X�`���̃A���o�C���h
        Texture::C_TextureManager::s_GetInstance()->Unbind(Texture::Type::s_2D);

        // �e�N�X�`����j��
        Texture::C_TextureManager::s_GetInstance()->Destroy(s_pFONT_ID);

        // �[�x�̃}�X�N�𖳌���
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableDepthMask(false);

        // �A���t�@�𖳌��ɂ���
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableBlend(false);
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::Finalize()
    {
        // �t�H���g�̉��
        if (Font::C_FontManager::s_GetInstance()->GetFont(fontFilePath_, fontSize_))
        {
            Font::C_FontManager::s_GetInstance()->Release(fontFilePath_, fontSize_);
        }

        pFont_.reset();

        // GLSL�I�u�W�F�N�g������
        if (Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Remove(Fixed::Shader::s_pGLSL_OBJECT_ID);
        }

        pGlslObject_.reset();

        // ���_�o�b�t�@�I�u�W�F�N�g�̍폜 
        const int32_t DELETE_VERTEX_ARRAY_OBJECT_NUMBER = 1;
        glDeleteVertexArrays(DELETE_VERTEX_ARRAY_OBJECT_NUMBER, &vertexArrayObjectHandle_);
        vertexArrayObjectHandle_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̃��[�h�������s��
     *  @param  
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::LoadFont(const std::string& rFilePath, int32_t size)
    {
        // �t�H���g�̃��[�h����
        if (!Font::C_FontManager::s_GetInstance()->GetFont(rFilePath, size))
        {
            if (Font::C_FontManager::s_GetInstance()->Load(rFilePath, size) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : �t�H���g�̃��[�h�����Ɏ��s���܂����B\n");

                return false;
            }
        }

        // �t�@�C���p�X�ƃt�H���g��ێ�
        fontFilePath_ = rFilePath;
        pFont_ = Font::C_FontManager::s_GetInstance()->GetFont(rFilePath, size).get();
        fontSize_ = size;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �V�F�[�_�[�̃R���p�C���ƃ����N���s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::CreateAndEntryGlslObject()
    {
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : ���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : �W�I���g���V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : �t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : �V�F�[�_�[�̃����N�Ɏ��s���܂����B\n");

                return false;
            }

            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, Fixed::Shader::s_pGLSL_OBJECT_ID);
            pGlslObject_ = pGlslObject;
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ���_�z��I�u�W�F�N�g���쐬����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::CreateVertexArrayObject()
    {
        // ���̍��W
        Vector3 tempPosition;

        // ���_�o�b�t�@���쐬���A�f�[�^��]��
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        const int32_t BUFFER_INDEX = 0;
        const int32_t VERTEX_ARRAY_OBJECT_NUMBER = 1;
        const int32_t NO_USE_BYTE_OFFSET = 0;
        const int32_t POSITION_BYTE_OFFSET = 0;

        // ���_�o�b�t�@�I�u�W�F�N�g�n���h��
        GLuint vertexBufferObjectHandle = 0;

        glGenBuffers(VERTEX_ARRAY_OBJECT_NUMBER, &vertexBufferObjectHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
        glBufferData(GL_ARRAY_BUFFER, POSITION_ELEMENT_NUMBER * sizeof(float), tempPosition.a_, GL_STATIC_DRAW);

        // ���_�z��I�u�W�F�N�g���쐬���A�o�C���h
        glGenVertexArrays(1, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);
        glEnableVertexAttribArray(BUFFER_INDEX);
        glVertexAttribPointer(BUFFER_INDEX, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, NO_USE_BYTE_OFFSET, reinterpret_cast<GLubyte*>(POSITION_BYTE_OFFSET));

        // �e�o�b�t�@���A���o�C���h
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // ���_�o�b�t�@�I�u�W�F�N�g���폜
        glDeleteBuffers(1, &vertexBufferObjectHandle);
    }
}