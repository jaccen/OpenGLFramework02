/* �w�b�_�t�@�C�� */
#include "PathAnalizer.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief �p�X
//! @brief �p�X�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Path
{
    /*************************************************************//**
    *
    *  @brief  �g���q���擾����
    *  @param  �t�@�C���p�X
    *  @return �g���q
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetExtension(const std::string& rFilePath)
    {
        return rFilePath.substr(rFilePath.find_last_of('.') + 1);
    }


    /*************************************************************//**
    *
    *  @brief  �g���q�Ȃ��Ńt�@�C�������擾����
    *  @param  �t�@�C���p�X
    *  @return �g���q�Ȃ��̃t�@�C����
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetFileNameWithoutExtension(const std::string& rFilePath)
    {
        std::string fileNamePulsExtension = s_GetFileName(rFilePath);

        return fileNamePulsExtension.substr(0, rFilePath.find_last_of('.'));
    }


    /*************************************************************//**
    *
    *  @brief  �t�@�C�������擾����
    *  @param  �t�@�C���p�X
    *  @return �t�@�C����
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetFileName(const std::string& rFilePath)
    {
        return rFilePath.substr(std::max<int32_t>(rFilePath.find_last_of('/'), rFilePath.find_last_of('\\')) + 1);
    }


    /*************************************************************//**
    *
    *  @brief  �f�B���N�g�������擾����
    *  @param  �t�@�C���p�X
    *  @return �f�B���N�g����
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetDirectoryName(const std::string& rFilePath)
    {
        std::string::size_type position = std::max<int32_t>(rFilePath.find_last_of('/'),
                                                            rFilePath.find_last_of('\\'));

        return (position == std::string::npos) ? std::string() : rFilePath.substr(0, position + 1);
    }


    /*************************************************************//**
    *
    *  @brief  ��΃p�X���擾����
    *  @param  �Ȃ�
    *  @return ��΃p�X
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetAbsolutePath()
    {
        char absolutePath[512] = "";

    /* Windows�� */
#ifdef _WIN32

        GetModuleFileName(nullptr, absolutePath, 512);

#endif

        return absolutePath;
    }
}