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
        /* ���S�ȍ폜���� */
        template <typename T>
        static void s_SafeDelete(T*& prObject);

        /* ���S�Ȕz��̍폜���� */
        template <typename T>
        static void s_SafeDeleteArray(T*& prArrayObject);

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
    };


    /*************************************************************//**
     *
     *  @brief  �I�u�W�F�N�g�̍폜���s��
     *  @param  �I�u�W�F�N�g
     *  @return �Ȃ�
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
     *  @brief  �I�u�W�F�N�g�̔z��̍폜���s��
     *  @param  �I�u�W�F�N�g�̔z��
     *  @return �Ȃ�
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
}