/* ヘッダファイル */
#include "PathAnalizer.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief パス
//! @brief パス関連の名前空間
//!
//-------------------------------------------------------------
namespace Path
{
    /*************************************************************//**
    *
    *  @brief  拡張子を取得する
    *  @param  ファイルパス
    *  @return 拡張子
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetExtension(const std::string& rFilePath)
    {
        return rFilePath.substr(rFilePath.find_last_of('.') + 1);
    }


    /*************************************************************//**
    *
    *  @brief  拡張子なしでファイル名を取得する
    *  @param  ファイルパス
    *  @return 拡張子なしのファイル名
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetFileNameWithoutExtension(const std::string& rFilePath)
    {
        std::string fileNamePulsExtension = s_GetFileName(rFilePath);

        return fileNamePulsExtension.substr(0, rFilePath.find_last_of('.'));
    }


    /*************************************************************//**
    *
    *  @brief  ファイル名を取得する
    *  @param  ファイルパス
    *  @return ファイル名
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetFileName(const std::string& rFilePath)
    {
        return rFilePath.substr(std::max<int32_t>(rFilePath.find_last_of('/'), rFilePath.find_last_of('\\')) + 1);
    }


    /*************************************************************//**
    *
    *  @brief  ディレクトリ名を取得する
    *  @param  ファイルパス
    *  @return ディレクトリ名
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
    *  @brief  絶対パスを取得する
    *  @param  なし
    *  @return 絶対パス
    *
    ****************************************************************/
    std::string C_PathAnalizer::s_GetAbsolutePath()
    {
        char absolutePath[512] = "";

    /* Windows時 */
#ifdef _WIN32

        GetModuleFileName(nullptr, absolutePath, 512);

#endif

        return absolutePath;
    }
}