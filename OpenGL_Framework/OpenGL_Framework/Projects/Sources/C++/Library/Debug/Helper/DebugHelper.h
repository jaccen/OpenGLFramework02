/* 二重インクルード防止 */
#pragma once


/* デバッグ時 */
#ifdef _DEBUG


/* Unicode時 */
#ifdef _UNICODE

    /** デバッグウィンドウに出力するマクロ */
    #define OutputDebugStringEx(string, ...)                            \
    {                                                                   \
        const int32_t BUFFER_NUMBER = 256;                              \
                                                                        \
        TCHAR debugString[BUFFER_NUMBER];                               \
        wsprintf(debugString, string, __VA_ARGS__);                     \
                                                                        \
        OutputDebugString(debugString);                                 \
    }

#else

    /** デバッグウィンドウに出力するマクロ */
    #define OutputDebugStringEx(string, ...)                            \
    {                                                                   \
        const int32_t BUFFER_NUMBER = 256;                              \
                                                                        \
        char debugString[BUFFER_NUMBER];                                \
        sprintf_s(debugString, string, __VA_ARGS__);                    \
                                                                        \
        OutputDebugString(debugString);                                 \
    }

#endif

    /** メモリリークの検出機能付きnew演算子 */
    #define newEx new(__FILE__, __LINE__)


/* リリース時 */
#else


    /** デバッグウィンドウに出力するマクロ */
    #define OutputDebugStringEx(string, ...)

    /** メモリリークを検出してくれるnew演算子 */
    #define newEx new


#endif


/** ログを出力するマクロ */
#define PrintLog(string, ...)                               \
{                                                           \
    OutputDebugStringEx(string, __VA_ARGS__);               \
}                                                           


/** Releaseでも機能するアサート */
#define StrongAssert(expression)                            \
{                                                           \
    if (!(expression))                                      \
    {                                                       \
        Debug::C_DebugHelper::s_Halt(__FILE__,              \
                                     __LINE__,              \
                                     #expression,           \
                                     "StringAssert");       \
    }                                                       \
}


//-------------------------------------------------------------
//!
//! @brief デバッグ
//! @brief デバッグ関連の名前空間
//!
//-------------------------------------------------------------
namespace Debug
{
    //-------------------------------------------------------------
    //!
    //! @brief デバッグヘルパー
    //! @brief デバッグの助けとなる関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_DebugHelper
    {
    public:

/* Unicode時 */
#ifdef _UNICODE

        /* 停止処理 */
        static void s_Halt(const std::wstring& rFilename, 
                           int32_t line, 
                           const std::wstring& rMessage,
                           const std::wstring& rTitle);

#else

        /* 停止処理 */
        static void s_Halt(const std::string& rFilename,
                           int32_t line,
                           const std::string& rMessage,
                           const std::string& rTitle);

#endif

    };
}