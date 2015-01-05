/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../GlslDefine.h"
#include "../Uniform/UniformBuffer.h"
#include <vector>


/* �O���錾 */
namespace Math
{
    template<typename T>
    struct S_Vector2;
    
    template<typename T>
    struct S_Vector3;
    
    template<typename T>
    struct S_Vector4;
    
    template<typename T>
    struct S_Matrix3x3;

    template<typename T>
    struct S_Matrix4x4;
};


//-------------------------------------------------------------
//!
//! @brief �V�F�[�_�[
//! @brief �V�F�[�_�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /* �O���錾 */
        class C_GlslObject;


        /* �ʖ� */
        using GlslObjectPtr = std::shared_ptr<C_GlslObject>;                                        // GlslObjectPtr�^


        //-------------------------------------------------------------
        //!
        //! @brief GLSL�I�u�W�F�N�g
        //! @brief GLSL�f�[�^���������߂̃N���X
        //!
        //-------------------------------------------------------------
        class C_GlslObject
        {
        public:
            C_GlslObject();                                                                         // �R���X�g���N�^
            virtual ~C_GlslObject();                                                                // �f�X�g���N�^
            bool CompileFromFile(const std::string& rFilePath, TypeEnum type);                      // �t�@�C������R���p�C��
            bool CompileFromString(const std::string& rString, TypeEnum type);                      // �����񂩂�R���p�C��
            bool Link();                                                                            // �����N����
            void PrintActiveAttribute();                                                            // �A�N�e�B�u�ȑ������o��
            void PrintActiveUniform();                                                              // �A�N�e�B�u�ȃ��j�t�H�[���ϐ����o��
            void Begin();                                                                           // �g�p�J�n
            void BeginWithUnifomBuffer(UniformBufferObjectHandle uniformBufferObjectHandle,         // ���j�t�H�[���o�b�t�@�𗘗p���Ďg�p�J�n
                                       UniformBlockIndex uniformBlockIndex);       
            void End();                                                                             // �g�p�I��
            void Delete();                                                                          // �폜����
            bool SetUniform1i(const std::string& rName, int32_t value);                             // int�^�̒l�Ń��j�t�H�[���ϐ���ݒ�
            bool SetUniform1f(const std::string& rName, float value);                               // float�^�̒l�Ń��j�t�H�[���ϐ���ݒ�
            bool SetUniform1b(const std::string& rName, bool value);                                // bool�^�̒l�Ń��j�t�H�[���ϐ���ݒ�
            bool SetUniform2f(const std::string& rName,                                             // float�^��2�̒l�Ń��j�t�H�[���ϐ���ݒ�
                              float x,
                              float y);
            bool SetUniform3f(const std::string& rName,                                             // float�^��3�̒l�Ń��j�t�H�[���ϐ���ݒ�
                              float x,
                              float y,
                              float z);
            bool SetUniform4f(const std::string& rName,                                             // float�^��4�̒l�Ń��j�t�H�[���ϐ���ݒ�
                              float x,
                              float y,
                              float z,
                              float w);
            bool SetUniformVector2(const std::string& rName,                                        // 2D�x�N�g���Ń��j�t�H�[���ϐ���ݒ�
                                   const Math::S_Vector2<float>& rVector);
            bool SetUniformVector3(const std::string& rName,                                        // 3D�x�N�g���Ń��j�t�H�[���ϐ���ݒ�
                                   const Math::S_Vector3<float>& rVector);
            bool SetUniformVector4(const std::string& rName,                                        // 4D�x�N�g���Ń��j�t�H�[���ϐ���ݒ�
                                   const Math::S_Vector4<float>& rVector);
            bool SetUniformMatrix3x3(const std::string& rName,                                      // 3 * 3�̍s��Ń��j�t�H�[���ϐ���ݒ�
                                     const Math::S_Matrix3x3<float>& rMatrix,
                                     int32_t elementCount = 1);
            bool SetUniformMatrix4x4(const std::string& rName,                                      // 4 * 4�̍s��Ń��j�t�H�[���ϐ���ݒ�
                                     const Math::S_Matrix4x4<float>& rMatrix,
                                     int32_t elementCount = 1);
            SubroutineIndex GetSubroutineIndex(TypeEnum type, const std::string& rName);            // �T�u���[�`���̃C���f�b�N�X���擾
            void BindActiveSubroutine(SubroutineIndex index, TypeEnum type);                        // �A�N�e�B�u�ȃT�u���[�`�����o�C���h
            ProgramObjectHandle GetProgramObjectHandle() const;                                     // �v���O�����I�u�W�F�N�g�̃n���h�����擾
            bool IsLinkFlag() const;                                                                // �����N�ς݃t���O���擾

            static GlslObjectPtr s_Create();                                                        // ��������
        private:
            ProgramObjectHandle programObjectHandle_ = 0;                                           ///< @brief �v���O�����I�u�W�F�N�g�n���h��
            bool linkFlag_ = false;                                                                 ///< @brief �����N�ς݂����f����t���O

            void PrintCompileError(ShaderObjectHandle handle);                                      // �R���p�C�����̃G���[���o��
            void PrintLinkError(ProgramObjectHandle handle);                                        // �����N���̃G���[���o��
            int32_t GetUniformLocation(const std::string& rName)  const;                            // ���j�t�H�[���ϐ��̏ꏊ���擾
        };
    }
}
