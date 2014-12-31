/* �w�b�_�t�@�C�� */
#include "DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �f�o�b�O
//! @brief �f�o�b�O�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Debug
{

/* Unicode�� */
#ifdef _UNICODE


    /*************************************************************//**
     *
     *  @brief  ��~�������s��
     *  @param  �t�@�C����
     *  @param  �s
     *  @param  ���b�Z�[�W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugHelper::s_Halt(const std::wstring& rFilename,
                               int32_t line, 
                               const std::wstring& rMessage,
                               const std::wstring& rTitle)
    {
        // �t�@�C�����A�s�A���b�Z�[�W�����킹��
        const int32_t BUFFER_NUMBER = 512;

        TCHAR mergeMessage[BUFFER_NUMBER];
        wsprintf(mergeMessage, TEXT("[ Line : %d ]\nFileName : %s\n Message : %s"), line, rFilename.c_str(), rMessage.c_str());

        // ���b�Z�[�W��\��
        MessageBox(nullptr, mergeMessage, rTitle.c_str(), MB_ICONHAND | MB_OK);

        // �����I��
        const int32_t STATUS_CODE = -1;

        std::exit(STATUS_CODE);
    }


#else


    /*************************************************************//**
     *
     *  @brief  ��~�������s��
     *  @param  �t�@�C����
     *  @param  �s
     *  @param  ���b�Z�[�W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugHelper::s_Halt(const std::string& rFilename,
                               int32_t line,
                               const std::string& rMessage,
                               const std::string& rTitle)
    {
        // �t�@�C�����A�s�A���b�Z�[�W�����킹��
        const int32_t BUFFER_NUMBER = 512;

        char mergeMessage[BUFFER_NUMBER];
        ::sprintf_s(mergeMessage, "[ Line : %d ]\nFileName : %s\n Message : %s", line, rFilename.c_str(), rMessage.c_str());

        // ���b�Z�[�W��\��
        MessageBox(nullptr, mergeMessage, rTitle.c_str(), MB_ICONHAND | MB_OK);

        // �����I��
        const int32_t STATUS_CODE = -1;

        std::exit(STATUS_CODE);
    }


#endif

}