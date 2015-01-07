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
        /* 安全なメモリの解放 */
        template <typename T>
        static void s_SafeDelete(T*& prDeletePointer);

        /* 安全な配列用のメモリの解放 */
        template <typename T>
        static void s_SafeDeleteArray(T*& prDeletePointer);

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

        /* アライメントに対応したメモリの割り当て */
        template<typename T, typename... Args>
        static T* s_AlignedNew(Args&&... args);

        /* アライメントに対応したメモリの解放 */
        template<typename T>
        static void s_AlignedDelete(T*& prDeletePointer);
    };


    /*************************************************************//**
     *
     *  @brief  安全にポインタを解放する
     *  @param  解放するメモリのポインタ
     *  @return なし
     *
     ****************************************************************/
    template <typename T>
    void C_CommonHelper::s_SafeDelete(T*& prDeletePointer)
    {
        if (prDeletePointer)
        {
            delete prDeletePointer;
            prDeletePointer = nullptr;
        }
    }


    /*************************************************************//**
     *
     *  @brief  安全に配列として確保したポインタを解放する
     *  @param  解放するメモリのポインタ
     *  @return なし
     *
     ****************************************************************/
    template <typename T>
    void C_CommonHelper::s_SafeDeleteArray(T*& prDeletePointer)
    {
        if (prDeletePointer)
        {
            delete[] prDeletePointer;
            (prDeletePointer) = nullptr;
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


    /*************************************************************//**
     *
     *  @brief  アライメントに対応したメモリの割り当てを行う
     *  @param  必要分の引き数
     *  @return 割り当てられたメモリのポインタ
     *
     ****************************************************************/
    template<typename T, typename... Args>
    T* C_CommonHelper::s_AlignedNew(Args&&... args)
    {
        return  new(::_aligned_malloc(sizeof(T), __alignof(T))) T(std::forward<Args>(args)...);
    }
    

    /*************************************************************//**
     *
     *  @brief  アライメントに対応したメモリの解放を行う
     *  @param  解放するメモリのポインタ
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_CommonHelper::s_AlignedDelete(T*& prDeletePointer)
    {
        if (prDeletePointer)
        {
            prDeletePointer->~T();
            ::_aligned_free(prDeletePointer);
            prDeletePointer = nullptr;
        }
    }
}