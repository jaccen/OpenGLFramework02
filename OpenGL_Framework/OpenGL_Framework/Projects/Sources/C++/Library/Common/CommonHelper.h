/* ��d�C���N���[�h�h�~ */
#pragma once


/* �}�N����` */
#define ShiftBit(x) (1 << (x))


//-------------------------------------------------------------
//!
//! @brief �R����
//! @brief ���ʊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Common
{
    //-------------------------------------------------------------
    //!
    //! @brief �R�����w���p�[
    //! @brief ���ʂŗ��p����֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_CommonHelper
    {
    public:
        /* ���S�ȃ������̉�� */
        template <typename T>
        static void s_SafeDelete(T*& prDeletePointer);

        /* ���S�Ȕz��p�̃������̉�� */
        template <typename T>
        static void s_SafeDeleteArray(T*& prDeletePointer);

        /* �J�X�^���f���[�^���^���_����make_unique */
        template<typename T, typename U>
        static std::unique_ptr<T, U> s_MakeCustomUnique(T* pObject, U function);

        /* ���b�Z�[�W�{�b�N�X��\�� */
        static bool s_ShowMessageBox(const std::string& rTitleName,
                                     const std::string& rText);

        /* Shift-JIS����UTF-8�ւ̕�����ɕϊ� */
        static std::string s_ConvertShiftJisToUtf8(const std::string& rShiftJisString);

        /* ������̑O��ɂ���w�肵����������菜�� */
        static std::string s_TrimString(const std::string& rString,
                                        const char* pTrimCharacterList = " \t\v\r\n");

        /* �t�@�C���̃T�C�Y���擾 */
        static uint32_t s_GetFileSize(std::ifstream* pInFile);

        /* �z�񐔂��擾 */
        template<typename T, std::size_t Size>
        static std::size_t s_ArraySize(const T(&)[Size]);

        /* �A���C�����g�ɑΉ������������̊��蓖�� */
        template<typename T, typename... Args>
        static T* s_AlignedNew(Args&&... args);

        /* �A���C�����g�ɑΉ������������̉�� */
        template<typename T>
        static void s_AlignedDelete(T*& prDeletePointer);
    };


    /*************************************************************//**
     *
     *  @brief  ���S�Ƀ|�C���^���������
     *  @param  ������郁�����̃|�C���^
     *  @return �Ȃ�
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
     *  @brief  ���S�ɔz��Ƃ��Ċm�ۂ����|�C���^���������
     *  @param  ������郁�����̃|�C���^
     *  @return �Ȃ�
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
     *  @brief  �J�X�^���f���[�^���^���_����make_unique
     *  @param  �I�u�W�F�N�g�̃|�C���^
     *  @param  delete�̑���ƂȂ�֐�
     *  @return �J�X�^���f���[�^���w�肵���I�u�W�F�N�g�̃|�C���^
     *
     ****************************************************************/
    template<typename T, typename U>
    std::unique_ptr<T, U> C_CommonHelper::s_MakeCustomUnique(T* pObject, U function)
    {
        return std::unique_ptr<T, U>(pObject, std::forward<U>(function));
    }


    /*************************************************************//**
     *
     *  @brief  �z��̗v�f�������߂�
     *  @param  �z��
     *  @return �v�f��
     *
     ****************************************************************/
    template<typename T, std::size_t Size>
    std::size_t C_CommonHelper::s_ArraySize(const T(&)[Size])
    {
        return Size;
    }


    /*************************************************************//**
     *
     *  @brief  �A���C�����g�ɑΉ������������̊��蓖�Ă��s��
     *  @param  �K�v���̈�����
     *  @return ���蓖�Ă�ꂽ�������̃|�C���^
     *
     ****************************************************************/
    template<typename T, typename... Args>
    T* C_CommonHelper::s_AlignedNew(Args&&... args)
    {
        return  new(::_aligned_malloc(sizeof(T), __alignof(T))) T(std::forward<Args>(args)...);
    }
    

    /*************************************************************//**
     *
     *  @brief  �A���C�����g�ɑΉ������������̉�����s��
     *  @param  ������郁�����̃|�C���^
     *  @return �Ȃ�
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