/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �p�X
//! @brief �p�X�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Path
{
    //-------------------------------------------------------------
    //!
    //! @brief �p�X�A�i���C�U�[
    //! @brief �p�X�̉�͂��s���֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_PathAnalizer
    {
    public:
        static std::string s_GetExtension(const std::string& rFilePath);                        // �g���q���擾
        static std::string s_GetFileNameWithoutExtension(const std::string& rFilePath);         // �g���q�Ȃ��Ńt�@�C�������擾       
        static std::string s_GetFileName(const std::string& rFilePath);                         // �t�@�C�������擾       
        static std::string s_GetDirectoryName(const std::string& rFilePath);                    // �f�B���N�g�������擾
        static std::string s_GetAbsolutePath();                                                 // ��΃p�X���擾
    };
}