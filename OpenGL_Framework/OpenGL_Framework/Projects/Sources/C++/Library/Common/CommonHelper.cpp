/* �w�b�_�t�@�C�� */
#include "CommonHelper.h"
#include <fstream>


//-------------------------------------------------------------
//!
//! @brief �R����
//! @brief ���ʊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Common
{
    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�{�b�N�X��\��
     *  @param  �^�C�g����
     *  @param  �e�L�X�g
     *  @param  �E�B���h�E�n���h��
     *  @return �͂����������ꍇ�Ftrue
     *  @return ���������������ꍇ�Ffalse
     *
     ****************************************************************/
    bool C_CommonHelper::s_ShowMessageBox(const std::string& rTitleName,
                                          const std::string& rText)
    {

/* Windows�� */
#ifdef _WIN32

        if (MessageBoxA(nullptr, rText.c_str(), rTitleName.c_str(), MB_YESNO | MB_ICONQUESTION) == IDNO)
        {
            return false;
        }

#endif

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  Shift-JIS�̕����񂩂�UTF-8������ւ̕ϊ����s��
     *  @param  Shift-JIS������
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    std::string C_CommonHelper::s_ConvertShiftJisToUtf8(const std::string& rShiftJisString)
    {
        assert(rShiftJisString.empty() == false);

/* Windows�� */
#ifdef _WIN32

        // Shift-JIS����Unicode�ւ̕ϊ��ɕK�v�ȃo�b�t�@�����m��
        int32_t unicodeStringBuffer = ::MultiByteToWideChar(CP_ACP, 0, rShiftJisString.c_str(), -1, nullptr, 0);

        if (unicodeStringBuffer == 0) return "";

        // Unicode������
        std::wstring unicodeString;

        // Unicode�ϊ��ɕK�v�ȃo�b�t�@���������e�ʂ��m��
        unicodeString.resize(unicodeStringBuffer);

        // Shift-JIS����Unicode�ւ̕ϊ�
        if (::MultiByteToWideChar(CP_ACP, 0, rShiftJisString.c_str(), -1, &unicodeString[0], unicodeStringBuffer) == 0) return "";

        // Unicode����UTF-8�ւ̕ϊ��ɕK�v�ȃo�b�t�@�����m��
        const int32_t utf8Buffer = ::WideCharToMultiByte(CP_UTF8, 0, unicodeString.c_str(), -1, nullptr, 0, nullptr, nullptr);

        if (utf8Buffer == 0) return "";

        // UTF-8������
        std::string utf8String;

        // UTF-8�ϊ��ɕK�v�ȃo�b�t�@���������e�ʂ��m��
        utf8String.resize(utf8Buffer);

        // Unicode����UTF-8�ւ̕ϊ�
        if (::WideCharToMultiByte(CP_UTF8, 0, unicodeString.c_str(), -1, &utf8String[0], utf8Buffer, nullptr, nullptr) == 0) return "";

#endif

        return utf8String;
    }


    /*************************************************************//**
     *
     *  @brief  ������̑O��ɂ���w�肵����������菜��
     *  @param  ������
     *  @param  �폜�Ώۂ̕���
     *  @return �Ȃ�
     *
     ****************************************************************/
    std::string C_CommonHelper::s_TrimString(const std::string& rString,
                                             const char* pTrimCharacterList)
    {
        std::string trimString = rString;

        // �폜�Ώۂ̕����Ɋ܂܂�Ȃ��������ŏ��Ɍ�����ʒu������
        size_t location = trimString.find_first_not_of(pTrimCharacterList);

        // �ŏ�������ꕶ���̂Ȃ��ʒu�܂ō폜
        trimString.erase(0, location);

        // �폜�Ώۂ̕����Ɋ܂܂�Ȃ��������Ō�Ɍ�����ʒu������
        location = trimString.find_last_not_of(pTrimCharacterList);

        // ���ꕶ���̂Ȃ��ʒu����1��̈ʒu���폜
        trimString.erase(location + 1);

        return trimString;
    }


    /*************************************************************//**
     *
     *  @brief  �t�@�C���̃T�C�Y���擾����
     *  @param  ���̓t�@�C��
     *  @return �t�@�C���̃T�C�Y
     *
     ****************************************************************/
    uint32_t C_CommonHelper::s_GetFileSize(std::ifstream* pInFile)
    {
        pInFile->seekg(0, std::ifstream::end);
        std::streamoff endPosition = pInFile->tellg();

        pInFile->clear();
        pInFile->seekg(0, std::ifstream::beg);
        std::streamoff beginPosition = pInFile->tellg();

        return static_cast<uint32_t>(endPosition - beginPosition);
    }
}