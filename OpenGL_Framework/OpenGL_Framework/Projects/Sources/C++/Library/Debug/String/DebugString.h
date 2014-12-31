/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../../Math/Vector/Vector3.h"


//-------------------------------------------------------------
//!
//! @brief �f�o�b�O
//! @brief �f�o�b�O�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Debug
{
    /* �ʖ� */
    using Vector3 = Math::S_Vector3<float>;                                                                         // Vector3�^


    namespace
    {
        /* �f�t�H���g */
        namespace Default
        {
            /* �t�H���g */
            namespace Font
            {
                const char* s_pFILE_PATH = "Projects/Fonts/�₳�����S�V�b�N/07�₳�����S�V�b�N.ttf";                ///< @brief �t�@�C���p�X
                const int32_t s_SIZE = 32;                                                                          ///< @brief �T�C�Y
            }
        }

        /* �Œ� */
        namespace Fixed
        {
            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.vert";                   ///< @brief ���_�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.geom";                 ///< @brief �W�I���g���V�F�[�_�[�̃t�@�C���p�X
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.frag";                 ///< @brief �t���O�����g�V�F�[�_�[�̃t�@�C���p�X
                const char* s_pGLSL_OBJECT_ID = "DebugString";                                                      ///< @brief �V�F�[�_�[�I�u�W�F�N�g��ID
            }

            /* �e�N�X�`�� */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 26;                                                                   ///< @brief ���j�b�g�ԍ�
            }
        }
    }


    /** �������� */
    enum class ecTypographicAlignment
    {
        LEFT,                                                                                                       ///< @brief ������
        RIGHT,                                                                                                      ///< @brief �E����
        CENTER,                                                                                                     ///< @brief ��������
    };


    //-------------------------------------------------------------
    //!
    //! @brief �f�o�b�O�X�g�����O
    //! @brief �f�o�b�O�p�̕�����`����s�����߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_DebugString : public Singleton::C_Singleton<C_DebugString>
    {
    public:
        C_DebugString();                                                                                            // �R���X�g���N�^
        ~C_DebugString() override;                                                                                  // �f�X�g���N�^
        bool Initialize(const std::string& rFontFilePath = Default::Font::s_pFILE_PATH,                             // ����������
                        int32_t fontSize = Default::Font::s_SIZE);
        void Draw(const std::string& rString,                                                                        // �`�揈��
                  const Vector3& rPosition,
                  float scale = 1.0f,
                  uint8_t red = 0,
                  uint8_t green = 0,
                  uint8_t blue = 0,
                  ecTypographicAlignment alignment = ecTypographicAlignment::LEFT);
        void Finalize();                                                                                            // �I������
    private:
        /* �O���錾 */
        class C_DebugStringImpl;

        std::unique_ptr<C_DebugStringImpl> upImpl_;                                                                 ///< brief �������
    };
}