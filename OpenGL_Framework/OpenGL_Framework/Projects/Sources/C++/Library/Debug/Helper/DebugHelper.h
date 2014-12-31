/* ��d�C���N���[�h�h�~ */
#pragma once


/* �f�o�b�O�� */
#ifdef _DEBUG


/* Unicode�� */
#ifdef _UNICODE

    /** �f�o�b�O�E�B���h�E�ɏo�͂���}�N�� */
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

    /** �f�o�b�O�E�B���h�E�ɏo�͂���}�N�� */
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

    /** ���������[�N�̌��o�@�\�t��new���Z�q */
    #define newEx new(__FILE__, __LINE__)


/* �����[�X�� */
#else


    /** �f�o�b�O�E�B���h�E�ɏo�͂���}�N�� */
    #define OutputDebugStringEx(string, ...)

    /** ���������[�N�����o���Ă����new���Z�q */
    #define newEx new


#endif


/** ���O���o�͂���}�N�� */
#define PrintLog(string, ...)                               \
{                                                           \
    OutputDebugStringEx(string, __VA_ARGS__);               \
}                                                           


/** Release�ł��@�\����A�T�[�g */
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
//! @brief �f�o�b�O
//! @brief �f�o�b�O�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Debug
{
    //-------------------------------------------------------------
    //!
    //! @brief �f�o�b�O�w���p�[
    //! @brief �f�o�b�O�̏����ƂȂ�֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_DebugHelper
    {
    public:

/* Unicode�� */
#ifdef _UNICODE

        /* ��~���� */
        static void s_Halt(const std::wstring& rFilename, 
                           int32_t line, 
                           const std::wstring& rMessage,
                           const std::wstring& rTitle);

#else

        /* ��~���� */
        static void s_Halt(const std::string& rFilename,
                           int32_t line,
                           const std::string& rMessage,
                           const std::string& rTitle);

#endif

    };
}