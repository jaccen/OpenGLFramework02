/* �w�b�_�t�@�C�� */
#include "FigureDrawer.h"
#include "../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include <array>


//-------------------------------------------------------------
//!
//! @brief �t�B�M���A
//! @brief �}�`�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Figure
{
    /* �ʖ� */
    using VertexArrayObjectHandle = GLuint;                                                                                 // VertexArrayObjectHandle�^
    using VertexBufferObjectHandle = GLuint;                                                                                // VertexBufferObjectHandle�^
    

    /** �v���~�e�B�u�̎�� */
    enum ePrimitiveType
    {
        POINT,                                                                                                              ///< @brief �_
        LINE,                                                                                                               ///< @brief ��
        
        PRIMITIVE_TYPE_NUMBER,                                                                                              ///< @biref �v���~�e�B�u�̎�ނ̐�
    };


    /** ���_�̎�� */
    enum eVertexType
    {
        POSITION,                                                                                                           ///< @brief ���W
        COLOR,                                                                                                              ///< @brief �F

        VERTEX_TYPE_NUMBER,                                                                                                 ///< @brief ���_�̎�ނ̐�
    };


    //-------------------------------------------------------------
    //!
    //! @brief �t�B�M���A�h�����[�C���v�������g
    //! @brief �t�B�M���A�h�����[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_FigureDrawer::C_FigureDrawerImpl
    {
    public:
        C_FigureDrawerImpl();                                                                                               // �R���X�g���N�^
        ~C_FigureDrawerImpl();                                                                                              // �f�X�g���N�^
        bool Initialize();                                                                                                  // ����������
        void Finalize();                                                                                                    // �I������
        void DrawPoint(const Vector3& rPosition,                                                                            // �_�̕`��
                       const Vector4& rColor,
                       const Matrix4x4& rViewProjectionMatrix);                           
        void DrawLine(const Vector3& rStartPosition,                                                                        // ���̕`��
                      const Vector3& rEndPositiont, 
                      const Vector4& rColor,
                      const Matrix4x4& rViewProjectionMatrix);
        void SetPointSize(float pointSize);                                                                                 // �_�̃T�C�Y��ݒ�
    private:
        std::array<VertexArrayObjectHandle, PRIMITIVE_TYPE_NUMBER> vertexArrayObjectHandles_;                               ///< @brief ���_�z��I�u�W�F�N�g�n���h��
        std::array<VertexBufferObjectHandle, PRIMITIVE_TYPE_NUMBER> vertexBufferObjectHandles_;                             ///< @brief ���_�o�b�t�@�I�u�W�F�N�g�n���h��
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                                           ///< @brief GLSL�I�u�W�F�N�g
        int32_t subroutineIndices_[2];                                                                                      ///< @brief �T�u���[�`���̃C���f�b�N�X
        bool finalizeFlag_ = false;                                                                                         ///< @brief �I���������s���������f����t���O

        bool CreateAndEntryGlslObject();                                                                                    // GLSL�I�u�W�F�N�g�̍쐬�Ɠo�^
        void CreateVertexArrayObject(ePrimitiveType type, int32_t vertexCount);                                             // ���_�z��I�u�W�F�N�g���쐬
        void RewriteVertices(ePrimitiveType type, Vector3 positions[], const Vector4& rColor, int32_t vertexCount);         // ���_�̏�������    
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawerImpl::C_FigureDrawerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawerImpl::~C_FigureDrawerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    bool C_FigureDrawer::C_FigureDrawerImpl::Initialize()
    {
        // GLSL�I�u�W�F�N�g�̍쐬�Ɠo�^
        if (CreateAndEntryGlslObject() == false) return false;

        // �_�̃T�C�Y��ݒ�
        SetPointSize(1.0f);

        // ���_�z��I�u�W�F�N�g���쐬
        CreateVertexArrayObject(POINT, 1);
        CreateVertexArrayObject(LINE, 2);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::Finalize()
    {
        // ���_�o�b�t�@�I�u�W�F�N�g�ƒ��_�z��I�u�W�F�N�g�̍폜
        glDeleteBuffers(PRIMITIVE_TYPE_NUMBER, vertexBufferObjectHandles_.data());
        glDeleteVertexArrays(PRIMITIVE_TYPE_NUMBER, vertexArrayObjectHandles_.data());
        vertexBufferObjectHandles_.fill(0);
        vertexArrayObjectHandles_.fill(0);

        // GLSL�I�u�W�F�N�g������
        if (Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Remove(Fixed::Shader::s_pGLSL_OBJECT_ID);
        }

        pGlslObject_.reset();

        // �I�������ς݃t���O�𗧂Ă�
        finalizeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  �_�̕`����s��
     *  @param  ���W
     *  @param  �F
     *  @param  �r���[�v���W�F�N�V�����s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::DrawPoint(const Vector3& rPosition,
                                                       const Vector4& rColor,
                                                       const Matrix4x4& rViewProjectionMatrix)
    {
        Vector3 positions[] = { rPosition };

        // ���_�̏�������
        RewriteVertices(POINT, positions, rColor, 1);

        // ���_�z��I�u�W�F�N�g���o�C���h
        glBindVertexArray(vertexArrayObjectHandles_[POINT]);

        // �V�F�[�_�[�̎g�p�J�n
        pGlslObject_->Begin();

        // �T�u���[�`����ݒ�
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[POINT], Shader::GLSL::Type::s_VERTEX);

        // �r���[�v���W�F�N�V�����s���ݒ�
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", rViewProjectionMatrix);

        ::glDrawArrays(GL_POINTS, 0, 1);

        // �V�F�[�_�[�̎g�p�I��
        pGlslObject_->End();

        // ���_�z��I�u�W�F�N�g���A���o�C���h
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  ���̕`����s��
     *  @param  �J�n���W
     *  @param  �I�����W
     *  @param  �F
     *  @param  �r���[�v���W�F�N�V�����s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::DrawLine(const Vector3& rStartPosition,
                                                      const Vector3& rEndPosition,
                                                      const Vector4& rColor,
                                                      const Matrix4x4& rViewProjectionMatrix)
    {
        Vector3 positions[] = { rStartPosition, rEndPosition };

        // ���_�̏�������
        RewriteVertices(LINE, positions, rColor, 2);

        // ���_�z��I�u�W�F�N�g���o�C���h
        glBindVertexArray(vertexArrayObjectHandles_[LINE]);

        // �V�F�[�_�[�̎g�p�J�n
        pGlslObject_->Begin();

        // �T�u���[�`����ݒ�
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[LINE], Shader::GLSL::Type::s_VERTEX);

        // �r���[�v���W�F�N�V�����s���ݒ�
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", rViewProjectionMatrix);

        ::glDrawArrays(GL_LINES, 0, 2);

        // �V�F�[�_�[�̎g�p�I��
        pGlslObject_->End();

        // ���_�z��I�u�W�F�N�g���A���o�C���h
        glBindVertexArray(0);
    }


    
    /*************************************************************//**
     *
     *  @brief  �_�̃T�C�Y��ݒ肷��
     *  @param  �_�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::SetPointSize(float pointSize)
    {
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1f("pointSize", pointSize);
        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  GLSL�I�u�W�F�N�g�̍쐬�Ɠo�^���s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_FigureDrawer::C_FigureDrawerImpl::CreateAndEntryGlslObject()
    {
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : ���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : �t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : �V�F�[�_�[�̃����N�Ɏ��s���܂����B\n");

                return false;
            }

            // GLSL�I�u�W�F�N�g��o�^���A�ێ�
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, Fixed::Shader::s_pGLSL_OBJECT_ID);
            pGlslObject_ = pGlslObject;
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        // �T�u���[�`���̃C���f�b�N�X���擾
        subroutineIndices_[POINT] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "PointProcess");
        subroutineIndices_[LINE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "LineProcess");

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ���_�z��I�u�W�F�N�g�̍쐬���s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���_��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::CreateVertexArrayObject(ePrimitiveType type, int32_t vertexCount)
    {
        // ���̒��_
        struct Vertex 
        {
            Vector3 position_; 
            Vector4 color_; 
        };

        std::vector<Vertex> tempVertices;

        // ���_�o�b�t�@�I�u�W�F�N�g���쐬���A�o�C���h
        glGenBuffers(1, &vertexBufferObjectHandles_[type]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandles_[type]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, tempVertices.data(), GL_DYNAMIC_DRAW);

        // ���_�z��I�u�W�F�N�g���쐬���A�o�C���h
        glGenVertexArrays(1, &vertexArrayObjectHandles_[type]);
        glBindVertexArray(vertexArrayObjectHandles_[type]);
        
        // �o�C�g�I�t�Z�b�g���g�p���Ȃ��Ƃ��̒l
        const int32_t NO_USE_BYTE_OFFESET = 0;
        const int32_t BYTE_OFFSET = 0;

        // ���_�o�b�t�@�ɍ��W��]��
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLubyte*>(0));

        // ���_�o�b�t�@�ɐF��]��
        const int32_t COLOR_ElEMENT_NUMBER = 4;

        // ���_�z��I�u�W�F�N�g�Ƀo�C���h
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, COLOR_ElEMENT_NUMBER, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLubyte*>(12));

        // �e�I�u�W�F�N�g���A���o�C���h
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  ���_�̏����������s��
     *  @param  �v���~�e�B�u�̎��
     *  @param  ���W
     *  @param  �F
     *  @param  ���_�̐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::RewriteVertices(ePrimitiveType type, Vector3 positions[], const Vector4& rColor, int32_t vertexCount)
    {
        // ���_�o�b�t�@���o�C���h
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandles_[type]);

        // ���_�o�b�t�@���}�b�v
        float* pVertices = reinterpret_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        assert(pVertices);

        // ���_�o�b�t�@�̃f�[�^����������
        for (int32_t i = 0, vertexIndex = 0; i < vertexCount; ++i)
        {
            pVertices[vertexIndex] = positions[i].x_;
            pVertices[vertexIndex + 1] = positions[i].y_;
            pVertices[vertexIndex + 2] = positions[i].z_;
            pVertices[vertexIndex + 3] = rColor.red_;
            pVertices[vertexIndex + 4] = rColor.green_;
            pVertices[vertexIndex + 5] = rColor.blue_;
            pVertices[vertexIndex + 6] = rColor.alpha_;

            vertexIndex += 7;
        }

        // �o�b�t�@���A���}�b�v
        glUnmapBuffer(GL_ARRAY_BUFFER);

        // ���_�o�b�t�@���A���o�C���h
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}