/* 二重インクルード防止 */
#pragma once


/* マクロ定義 */
#define ShiftBit(x) (1 << (x))


//-------------------------------------------------------------
//!
//! @brief コモン
//! @brief 共通関連の名前空間
//!
//-------------------------------------------------------------
namespace Common
{
    //-------------------------------------------------------------
    //!
    //! @brief コモンヘルパー
    //! @brief 共通で利用する関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_CommonHelper
    {
    public:
        /* 安全な削除処理 */
        template <typename T>
        static void s_SafeDelete(T*& prObject);

        /* 安全な配列の削除処理 */
        template <typename T>
        static void s_SafeDeleteArray(T*& prArrayObject);

        /* カスタムデリータを型推論するmake_unique */
        template<typename T, typename U>
        static std::unique_ptr<T, U> s_MakeCustomUnique(T* pObject, U function);

        /* メッセージボックスを表示 */
        static bool s_ShowMessageBox(const std::string& rTitleName,
                                     const std::string& rText);

        /* Shift-JISからUTF-8への文字列に変換 */
        static std::string s_ConvertShiftJisToUtf8(const std::string& rShiftJisString);

        /* 文字列の前後にある指定した文字を取り除く */
        static std::string s_TrimString(const std::string& rString,
                                        const char* pTrimCharacterList = " \t\v\r\n");

        /* ファイルのサイズを取得 */
        static uint32_t s_GetFileSize(std::ifstream* pInFile);

        /* 配列数を取得 */
        template<typename T, std::size_t Size>
        static std::size_t s_ArraySize(const T(&)[Size]);
    };


    /*************************************************************//**
     *
     *  @brief  オブジェクトの削除を行う
     *  @param  オブジェクト
     *  @return なし
     *
     ****************************************************************/
    template <typename T>
    void C_CommonHelper::s_SafeDelete(T*& prObject)
    {
        if (prObject)
        {
            delete (prObject);
            (prObject) = nullptr;
        }
    }


    /*************************************************************//**
     *
     *  @brief  オブジェクトの配列の削除を行う
     *  @param  オブジェクトの配列
     *  @return なし
     *
     ****************************************************************/
    template <typename T>
    void C_CommonHelper::s_SafeDeleteArray(T*& prArrayObject)
    {
        if (prArrayObject)
        {
            delete[](prArrayObject);
            (prArrayObject) = nullptr;
        }
    }


    /*************************************************************//**
     *
     *  @brief  カスタムデリータを型推論するmake_unique
     *  @param  オブジェクトのポインタ
     *  @param  deleteの代わりとなる関数
     *  @return カスタムデリータを指定したオブジェクトのポインタ
     *
     ****************************************************************/
    template<typename T, typename U>
    std::unique_ptr<T, U> C_CommonHelper::s_MakeCustomUnique(T* pObject, U function)
    {
        return std::unique_ptr<T, U>(pObject, std::forward<U>(function));
    }


    /*************************************************************//**
     *
     *  @brief  配列の要素数を求める
     *  @param  配列
     *  @return 要素数
     *
     ****************************************************************/
    template<typename T, std::size_t Size>
    std::size_t C_CommonHelper::s_ArraySize(const T(&)[Size])
    {
        return Size;
    }
}