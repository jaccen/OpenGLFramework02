/* �w�b�_�t�@�C�� */
#include "GlslObject.h"
#include "../../../Common/CommonHelper.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "../../../Math/MathAll.h"
#include <fstream>


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
        namespace
        {
            const int32_t s_UNIFORM_LOCATION_ERROR_VELUE = -1;              ///< @brief ���j�t�H�[���ϐ��̏ꏊ�̃G���[�l
        }

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_GlslObject::C_GlslObject()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_GlslObject::~C_GlslObject()
        {
            if (programObjectHandle_ != 0) Delete();
        }


        /*************************************************************//**
         *
         *  @brief  �t�@�C������V�F�[�_�[���R���p�C������
         *  @param  �t�@�C���p�X
         *  @param  �V�F�[�_�[�̎��
         *  @return ����I���Ftrue
         *  @return �ُ�I���Ffalse
         *
         ****************************************************************/
        bool C_GlslObject::CompileFromFile(const std::string& rFilePath, TypeEnum type)
        {
            // �t�@�C�����J��
            std::ifstream file(rFilePath);

            if (file.fail() == true)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : �t�@�C�����J���̂Ɏ��s���܂����B\n");
                PrintLog("                       �t�@�C���� : %s", rFilePath.c_str());

                return false;
            }

            // �T�C�Y���擾
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&file);

            if (fileSize == 0)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : �t�@�C���̒��g������܂���B\n");

                return false;
            }

            // �\�[�X�̃������̈���m�ۂ��A������\0������
            auto pSource = std::make_unique<char[]>(fileSize + 1);
            pSource[fileSize] = '\0';

            // �\�[�X�̃J�E���^
            size_t sourceCount = 0;

            while (true)
            {
                // �\�[�X��ǂݎ��
                pSource[sourceCount] = file.get();

                // �t�@�C���������̏ꍇ�̓��[�v�𔲂���
                if (file.eof() == true) break;

                // �J�E���^��1����
                ++sourceCount;
            }

            // �\�[�X�̖����ɍēx\0������
            pSource[sourceCount] = '\0';

            // �\�[�X���R���p�C��
            if (CompileFromString(pSource.get(), type) == false)
            {
                PrintLog("[ C_GlslObject::CompileFromFile ] : �V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                return false;
            }

            return true;
        }


        /*************************************************************//**
         *
         *  @brief  �����񂩂�V�F�[�_�[���R���p�C������
         *  @param  ������( �\�[�X )
         *  @param  �V�F�[�_�[�̎��
         *  @return ����I���Ftrue
         *  @return �ُ�I���Ffalse
         *
         ****************************************************************/
        bool C_GlslObject::CompileFromString(const std::string& rString, TypeEnum type)
        {
            assert(rString.empty() == false);

            // �V�F�[�_�[�I�u�W�F�N�g�n���h��
            ShaderObjectHandle shaderObjectHandle = 0;

            // �V�F�[�_�[�I�u�W�F�N�g���쐬
            shaderObjectHandle = glCreateShader(type);

            if (shaderObjectHandle == 0)
            {
                PrintLog("[ C_GlslObject::CompileFromString ] : �V�F�[�_�[�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B\n");

                return false;
            }

            // �V�F�[�_�[���܂Ƃ߂��z��
            const GLchar* pSourceArray[] = { rString.c_str() };

            // �V�F�[�_�[�I�u�W�F�N�g�n���h���Ƀ\�[�X���R�s�[
            const int32_t SHADER_COPY_NUMBER = 1;

            glShaderSource(shaderObjectHandle, SHADER_COPY_NUMBER, pSourceArray, nullptr);

            // �V�F�[�_�[�̃R���p�C��
            glCompileShader(shaderObjectHandle);

            // �R���p�C���̌���
            GLint compileResult = 0;

            // �V�F�[�_�[�̃X�e�[�^�X���擾
            glGetShaderiv(shaderObjectHandle, GL_COMPILE_STATUS, &compileResult);

            if (compileResult == GL_FALSE)
            {
                PrintLog("[ C_GlslObject::CompileFromString ] : �V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\n");

                // �G���[���o��
                PrintCompileError(shaderObjectHandle);

                return false;
            }

            // �v���O�����I�u�W�F�N�g���쐬����Ă��Ȃ��ꍇ�͍쐬
            if (programObjectHandle_ == 0)
            {
                programObjectHandle_ = glCreateProgram();

                if (programObjectHandle_ == 0)
                {
                    PrintLog("[ C_GlslObject::CompileFromString ] : �v���O�����I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B\n");

                    return false;
                }
            }

            // �V�F�[�_�[�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɉ����A�폜�t���O�𗧂Ă�
            glAttachShader(programObjectHandle_, shaderObjectHandle);
            glDeleteShader(programObjectHandle_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  �V�F�[�_�[�̃����N���s��
        *  @param  �Ȃ�
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::Link()
        {
            assert(programObjectHandle_ != 0);

            // �����N�ς݂̏ꍇ�͉������Ȃ�
            if (linkFlag_ == true) return true;

            // �v���O�����������N����
            glLinkProgram(programObjectHandle_);

            // �����N�̌���
            GLint linkResult = 0;

            // �v���O�����̃X�e�[�^�X���擾
            glGetProgramiv(programObjectHandle_, GL_LINK_STATUS, &linkResult);

            if (linkResult == GL_FALSE)
            {
                PrintLog("[ C_GlslObject::Link ] : �v���O�����̃����N�Ɏ��s���܂����B\n");

                // �G���[���o��
                PrintLinkError(programObjectHandle_);

                return false;
            }

            // �����N�ς݃t���O�𗧂Ă�
            linkFlag_ = true;

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  �A�N�e�B�u�ȑ������o�͂���
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::PrintActiveAttribute()
        {
            // �����̐��Ƒ����̖��O�̒���
            GLint attributeNumber = 0, attributeNameLength = 0;

            // �����̐��Ƒ����̖��O�̒������擾
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_ATTRIBUTES, &attributeNumber);
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeNameLength);

            // �����̖��O�̃������̈���m��
            auto pAttiributeName = std::make_unique<GLchar[]>(attributeNameLength);

            std::cout << "[ C_GlslObject::PrintActiveAttributes ] : ���_�V�F�[�_�[�̑����̏��" << std::endl;
            std::cout << " Location | Name" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (int32_t i = 0; i < attributeNumber; ++i)
            {
                // �������܂ꂽ��
                GLsizei writtenNumber = 0;

                // �T�C�Y
                GLint size = 0;

                // �^�C�v
                GLenum type;

                // �����ɂ��Ă̏����擾
                glGetActiveAttrib(programObjectHandle_, i, attributeNameLength, &writtenNumber, &size, &type, pAttiributeName.get());
                GLint location = glGetAttribLocation(programObjectHandle_, pAttiributeName.get());

                // �����ɂ��Ă̏����o��
                std::printf(" %-8d | %s\n", location, pAttiributeName.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  �A�N�e�B�u�ȃ��j�t�H�[���ϐ����o�͂���
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::PrintActiveUniform()
        {
            // ���j�t�H�[���ϐ��̐��ƃ��j�t�H�[���ϐ��̖��O�̒���
            GLint uniformNumber = 0, uniformNameLength = 0;

            // ���j�t�H�[���ϐ��̐����擾
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_UNIFORMS, &uniformNumber);

            // ���j�t�H�[���ϐ��̖��O�̒������擾
            glGetProgramiv(programObjectHandle_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameLength);

            // ���j�t�H�[���ϐ��̖��O���i�[���郁�����̈���m��
            auto pUniformName = std::make_unique<GLchar[]>(uniformNameLength);

            std::cout << "[ C_GlslObject::PrintActiveUniforms ] : ���j�t�H�[���ϐ��̏��" << std::endl;
            std::cout << " Location | Name" << std::endl;
            std::cout << "------------------------------------------------" << std::endl;

            for (int32_t i = 0; i < uniformNumber; ++i)
            {
                // �������܂ꂽ��
                GLsizei writtenNumber = 0;

                // �T�C�Y
                GLint size = 0;

                // �^�C�v
                GLenum type;

                // �����ɂ��Ă̏����擾
                glGetActiveUniform(programObjectHandle_, i, uniformNameLength, &writtenNumber, &size, &type, pUniformName.get());
                GLint location = glGetUniformLocation(programObjectHandle_, pUniformName.get());

                // �����ɂ��Ă̏����o��
                std::printf(" %-8d | %s\n", location, pUniformName.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  �V�F�[�_�[�̎g�p���J�n����
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::Begin()
        {
            assert(programObjectHandle_ != 0);

            glUseProgram(programObjectHandle_);
        }


        /*************************************************************//**
        *
        *  @brief  ���j�t�H�[���o�b�t�@���܂߂ăV�F�[�_�[�̎g�p���J�n����
        *  @param  ���j�t�H�[���o�b�t�@
        *          ���F( �V�F�[�_�[���p���ɔj������Ȃ��̈�ɍ쐬�������̂��g������ )
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::BeginWithUnifomBuffer(UniformBufferObjectHandle uniformBufferObjectHandle, 
                                                 UniformBlockIndex uniformBlockIndex)
        {
            // �V�F�[�_�[�̎g�p�J�n
            Begin();

            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���o�C���h
            glBindBufferBase(BufferType::s_UNIFORM, uniformBlockIndex, uniformBufferObjectHandle);
        }


        /*************************************************************//**
        *
        *  @brief  �V�F�[�_�[�̎g�p���I������
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::End()
        {
            glUseProgram(0);
        }


        /*************************************************************//**
        *
        *  @brief  �V�F�[�_�[�̍폜���s��
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::Delete()
        {
            // �v���O�����I�u�W�F�N�g�̍폜
            glDeleteProgram(programObjectHandle_);
            programObjectHandle_ = 0;

            // �����N�ς݂����f����t���O��������
            linkFlag_ = false;
        }


        /*************************************************************//**
        *
        *  @brief  int�^�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1i(const std::string& rName, int32_t value)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1i ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform1i(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float�^�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1f(const std::string& rName, float value)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1f ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform1f(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  bool�^�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform1b(const std::string& rName, bool value)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform1b ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform1i(location, value);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float�^��2�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l1
        *  @param  �l2
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform2f(const std::string& rName,
                                        float x,
                                        float y)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform2f ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform2f(location, x, y);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float�^��3�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l1
        *  @param  �l2
        *  @param  �l3
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform3f(const std::string& rName,
                                        float x,
                                        float y,
                                        float z)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform3f ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform3f(location, x, y, z);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  float�^��4�̒l�Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  �l1
        *  @param  �l2
        *  @param  �l3
        *  @param  �l4
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniform4f(const std::string& rName,
                                        float x,
                                        float y,
                                        float z,
                                        float w)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform4f ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform4f(location, x, y, z, w);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  2D�x�N�g���Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  2D�x�N�g��
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector2(const std::string& rName,
                                             const Math::S_Vector2<float>& rVector)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniform4f ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform2f(location, rVector.x_, rVector.y_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  3D�x�N�g���Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  3D�x�N�g��
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector3(const std::string& rName,
                                             const Math::S_Vector3<float>& rVector)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformVector3 ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform3f(location, rVector.x_, rVector.y_, rVector.z_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  4D�x�N�g���Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  4D�x�N�g��
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformVector4(const std::string& rName,
                                             const Math::S_Vector4<float>& rVector)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformVector4 ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniform4f(location, rVector.x_, rVector.y_, rVector.z_, rVector.w_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  3 * 3 �̍s��Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  3 * 3 �̍s��
        *  @param  �v�f��
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformMatrix3x3(const std::string& rName,
                                               const Math::S_Matrix3x3<float>& rMatrix,
                                               int32_t elementCount)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformMatrix3 ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniformMatrix3fv(location, elementCount, GL_FALSE, rMatrix.a_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  4 * 4 �̍s��Ń��j�t�H�[���ϐ���ݒ肷��
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @param  4 * 4 �̍s��
        *  @param  �v�f��
        *  @return ����I���Ftrue
        *  @return �ُ�I���Ffalse
        *
        ****************************************************************/
        bool C_GlslObject::SetUniformMatrix4x4(const std::string& rName,
                                               const Math::S_Matrix4x4<float>& rMatrix,
                                               int32_t elementCount)
        {
            // ���j�t�H�[���ϐ��̏ꏊ���擾
            int32_t location = GetUniformLocation(rName);

            if (location == s_UNIFORM_LOCATION_ERROR_VELUE)
            {
                PrintLog("[ C_GlslObject::SetUniformMatrix4 ] : ���j�t�H�[���ϐ��̏ꏊ�̎擾�Ɏ��s���܂����B\n");

                return false;
            }

            glUniformMatrix4fv(location, elementCount, GL_FALSE, rMatrix.a_);

            return true;
        }


        /*************************************************************//**
        *
        *  @brief  �T�u���[�`���̃C���f�b�N�X���擾����
        *  @param  �V�F�[�_�[�̎��
        *  @param  �T�u���[�`����
        *  @return �T�u���[�`���̃C���f�b�N�X
        *
        ****************************************************************/
        SubroutineIndex C_GlslObject::GetSubroutineIndex(TypeEnum type, const std::string& rName)
        {
            assert(programObjectHandle_ != 0);

            return glGetSubroutineIndex(programObjectHandle_, type, rName.c_str());
        }


        /*************************************************************//**
        *
        *  @brief  �A�N�e�B�u�ȃT�u���[�`�����o�C���h����
        *  @param  �T�u���[�`���̃C���f�b�N�X
        *  @param  �V�F�[�_�[�̎��
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::BindActiveSubroutine(SubroutineIndex index, TypeEnum type)
        {
            const int32_t BIND_SUBROUTINE_NUMBER = 1;

            glUniformSubroutinesuiv(type, BIND_SUBROUTINE_NUMBER, &index);
        }


        /*************************************************************//**
        *
        *  @brief  �v���O�����I�u�W�F�N�g���擾����
        *  @param  �Ȃ�
        *  @return �v���O�����I�u�W�F�N�g
        *
        ****************************************************************/
        ProgramObjectHandle C_GlslObject::GetProgramObject() const
        {
            assert(programObjectHandle_ != 0);

            return programObjectHandle_;
        }


        /*************************************************************//**
        *
        *  @brief  �����N�ς݃t���O���擾����
        *  @param  �Ȃ�
        *  @return �����N�ς݃t���O
        *
        ****************************************************************/
        bool C_GlslObject::IsLinkFlag() const
        {
            return linkFlag_;
        }


        /*************************************************************//**
        *
        *  @brief  �R���p�C�����̃G���[���o�͂���
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::PrintCompileError(ShaderObjectHandle handle)
        {
            // ���O�̒���
            GLint logLength = 0;

            // ���O�̒�����₢���킹��
            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                // ���O�̃������̈���m��
                auto pLog = std::make_unique<GLchar[]>(logLength);

                // �������܂ꂽ��
                GLsizei writtenNumber = 0;

                // ���O�̏����擾
                glGetShaderInfoLog(handle, logLength, &writtenNumber, pLog.get());

                PrintLog("                    �V�F�[�_�[���O : %s\n", pLog.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  �����N���̃G���[���o�͂���
        *  @param  �Ȃ�
        *  @return �Ȃ�
        *
        ****************************************************************/
        void C_GlslObject::PrintLinkError(ProgramObjectHandle handle)
        {
            // ���O�̒���
            GLint logLength = 0;

            // ���O�̒�����₢���킹��
            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                // ���O�̃������̈���m��
                auto pLog = std::make_unique<GLchar[]>(logLength);

                // �������܂ꂽ��
                GLsizei writtenNumber = 0;

                // ���O�̏����擾
                glGetProgramInfoLog(handle, logLength, &writtenNumber, pLog.get());

                PrintLog("          �v���O�������O : %s\n", pLog.get());
            }
        }


        /*************************************************************//**
        *
        *  @brief  ���j�t�H�[���ϐ��̏ꏊ���擾����
        *  @param  ���j�t�H�[���ϐ��̖��O
        *  @return �Ȃ�
        *
        ****************************************************************/
        int32_t C_GlslObject::GetUniformLocation(const std::string& rName) const
        {
            assert(programObjectHandle_ != 0);

            return glGetUniformLocation(programObjectHandle_, rName.c_str());
        }
    }
}