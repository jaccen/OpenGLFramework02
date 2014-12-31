//-------------------------------------------------------------
//!
//! @brief �V���O���g��
//! @brief �V���O���g���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Singleton
{

#pragma region �ÓI�����o�ϐ��̏�����


    /* �B��̃C���X�^���X */
    template<class T> T* C_AssertSingleton<T>::s_pInstance = nullptr;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<class T>
    inline C_AssertSingleton<T>::C_AssertSingleton()
    {
        assert(s_pInstance == nullptr && "[ C_AssertSingleton::C_AssertSingleton ] ������2�ȏ�̃C���X�^���X�͐����ł��܂���B");

        s_pInstance = static_cast<T*>(this);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<class T>
    inline C_AssertSingleton<T>::~C_AssertSingleton()
    {
        assert(s_pInstance && "[ C_AssertSingleton::~C_AssertSingleton ] �C���X�^���X�̓�d����ł��B");

        s_pInstance = nullptr;
    }


    /*************************************************************//**
     *
     *  @brief  �B��̃C���X�^���X���擾����
     *  @param  �Ȃ�
     *  @return �B��̃C���X�^���X
     *
     ****************************************************************/
    template<class T>
    inline T* C_AssertSingleton<T>::s_GetInstance()
    {
        return s_pInstance;
    }
}