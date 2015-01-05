/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"
#include "../Math/Vector/Vector4.h"
#include "../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief �t�B�M���A
//! @brief �}�`�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Figure
{
    /* �ʖ� */
    using Vector3 = Math::S_Vector3<float>;                                                         // Vector3�^
    using Vector4 = Math::S_Vector4<float>;                                                         // Vector4�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                     // Matrix4x4�^


    namespace
    {
        /* �Œ� */
        namespace Fixed
        {
            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Figure/Figure.vert";       ///< @brief ���_�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Figure/Figure.frag";     ///< @brief �t���O�����g�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGLSL_OBJECT_ID = "FigureDrawer";                                     ///< @brief �V�F�[�_�[�I�u�W�F�N�g��ID
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �t�B�M���A�h�����[
    //! @brief �}�`�`����s���N���X
    //!
    //-------------------------------------------------------------
    class C_FigureDrawer : public Singleton::C_Singleton<C_FigureDrawer>
    {
        friend C_Singleton<C_FigureDrawer>;                                                         // �V���O���g���N���X���t�����h��
    public:
        bool Initialize();                                                                          // ����������
        void Finalize();                                                                            // �I������
        void DrawPoint(const Vector3& rPosition,                                                    // �_�̕`��
                       const Vector4& rColor,
                       const Matrix4x4& rViewProjectionMatrix);               
        void DrawLine(const Vector3& rStartPosition,                                                // ���̕`��
                      const Vector3& rEndPositiont, 
                      const Vector4& rColor,
                      const Matrix4x4& rViewProjectionMatrix);
        void SetPointSize(float pointSize);                                                         // �_�̃T�C�Y��ݒ�
    private:
        /* �O���錾 */
        class C_FigureDrawerImpl;

        std::unique_ptr<C_FigureDrawerImpl> upImpl_;                                                ///< @brief �������

        C_FigureDrawer();                                                                           // �R���X�g���N�^
        ~C_FigureDrawer() override;                                                                 // �f�X�g���N�^
    };
}