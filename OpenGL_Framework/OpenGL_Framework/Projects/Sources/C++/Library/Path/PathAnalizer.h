/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief パス
//! @brief パス関連の名前空間
//!
//-------------------------------------------------------------
namespace Path
{
    //-------------------------------------------------------------
    //!
    //! @brief パスアナライザー
    //! @brief パスの解析を行う関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_PathAnalizer
    {
    public:
        static std::string s_GetExtension(const std::string& rFilePath);                        // 拡張子を取得
        static std::string s_GetFileNameWithoutExtension(const std::string& rFilePath);         // 拡張子なしでファイル名を取得       
        static std::string s_GetFileName(const std::string& rFilePath);                         // ファイル名を取得       
        static std::string s_GetDirectoryName(const std::string& rFilePath);                    // ディレクトリ名を取得
        static std::string s_GetAbsolutePath();                                                 // 絶対パスを取得
    };
}