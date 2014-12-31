/* �w�b�_�t�@�C�� */
#include "TextureManagerImpl.h"



//-------------------------------------------------------------
//!
//! @brief �e�N�X�`��
//! @brief �e�N�X�`���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Texture
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TextureManager::C_TextureManager() :

        // �������
        upImpl_(std::make_unique<C_TextureManagerImpl>(this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TextureManager::~C_TextureManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �t�@�C������2D�e�N�X�`���̍쐬���s��
     *  @param  �t�@�C���p�X
     *  @param  ID
     *  @param  �p�����[�^�ݒ���s���֐�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::Create2DFromFile(const std::string& rFilePath,
                                            const std::string& rId,
                                            const ParameterFunction& rParameterFunction)
    {
        if (rId == ID::s_pSAME_FILE_PATH)
        {
            if (upImpl_->Create2DFromFile(rFilePath, rFilePath, rParameterFunction) == false) return false;
        }
        else
        {
            if (upImpl_->Create2DFromFile(rFilePath, rId, rParameterFunction) == false) return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g����e�N�X�`���̍쐬���s��
     *  @param  �t�H���g
     *  @param  ID
     *  @param  ����
     *  @param  ��
     *  @param  ��
     *  @param  ��
     *  @param  �p�����[�^�ݒ���s���֐�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::Create2DFromFont(const Font::FontPtr& prFont,
                                            const std::string& rId,
                                            const std::string& rWords,
                                            uint8_t red,
                                            uint8_t green,
                                            uint8_t blue,
                                            const ParameterFunction& rParameterFunction)
    {
        if (upImpl_->Create2DFromFont(prFont, rId, rWords, red, green, blue, rParameterFunction) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �s�N�Z����񂩂�e�N�X�`���̍쐬���s��
     *  @param  �s�N�Z�����
     *  @param  �e�N�X�`���̕�
     *  @param  �e�N�X�`���̍���
     *  @param  �����t�H�[�}�b�g
     *  @param  �s�N�Z���t�H�[�}�b�g
     *  @param  �o�C�g���E
     *  @param  ID
     *  @param �p�����[�^�ݒ���s���֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::Create2DFromPixelData(void* pPixelDatas,
                                                 int32_t width,
                                                 int32_t height,
                                                 FormatType internalFormat,
                                                 FormatType pixelFormat,
                                                 int32_t byteBoundary,
                                                 const std::string& rId,
                                                 const ParameterFunction& rParameterFunction)
    {
        upImpl_->Create2DFromPixelData(pPixelDatas,
                                       width,
                                       height,
                                       internalFormat,
                                       pixelFormat,
                                       byteBoundary,
                                       rId,
                                       rParameterFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �t�@�C������L���[�u�}�b�v�e�N�X�`���̍쐬���s��
     *  @param  �f�B���N�g����
     *  @param  �t�@�C����
     *  @param  �^�[�Q�b�g�̎��
     *  @param  ID
     *  @param  �p�����[�^�ݒ���s���֐�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::CreateCubeMapFromFile(const std::string& rDirectoryName,
                                                 const std::array<std::string, 6>& rFileNames,
                                                 const std::array<TypeEnum, 6>& rTargetTypes,
                                                 const std::string& rId,
                                                 const ParameterFunction& rParameterFunction)
    {
        if (upImpl_->CreateCubeMapFromFile(rDirectoryName, rFileNames, rTargetTypes, rId, rParameterFunction) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���̔j�����s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::Destroy(const std::string& rFilePath)
    {
        upImpl_->Destroy(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`����S�Ĕj������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�u�ɂ���e�N�X�`�����j�b�g�̐ݒ���s��
     *  @param  �e�N�X�`�����j�b�g�̔ԍ�( 0 �` 31�܂� )
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::SetActiveUnit(uint32_t unitNumber)
    {
        assert(unitNumber >= 0 && unitNumber < 32);

        glActiveTexture(GL_TEXTURE0 + unitNumber);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���̃o�C���h���s��
     *  @param  �e�N�X�`���̎��
     *  @param  �e�N�X�`���n���h��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::Bind(TypeEnum type, TextureHandle handle)
    {
        ::glBindTexture(type, handle);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���̃A���o�C���h���s��
     *  @param  �e�N�X�`���̎��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::Unbind(TypeEnum type)
    {
        ::glBindTexture(type, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �p�����[�^�̐ݒ���s��
     *  @param  ���
     *  @param  �p�����[�^
     *  @param  �p�����[�^�̒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, int32_t parameterValue)
    {
        ::glTexParameteri(type, parameter, parameterValue);
    }


    /*************************************************************//**
     *
     *  @brief  �p�����[�^�̐ݒ���s��
     *  @param  ���
     *  @param  �p�����[�^
     *  @param  �p�����[�^�̒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, float parameterValue)
    {
        ::glTexParameterf(type, parameter, parameterValue);
    }


    /*************************************************************//**
     *
     *  @brief  �p�����[�^�̐ݒ���s��
     *  @param  ���
     *  @param  �p�����[�^
     *  @param  �p�����[�^�̒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, int32_t patameterValues[])
    {
        ::glTexParameteriv(type, parameter, patameterValues);
    }


    /*************************************************************//**
     *
     *  @brief  �p�����[�^�̐ݒ���s��
     *  @param  ���
     *  @param  �p�����[�^
     *  @param  �p�����[�^�̒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, float patameterValues[])
    {
        ::glTexParameterfv(type, parameter, patameterValues);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���f�[�^���擾����
     *  @param  ID
     *  @return �쐬����Ă����ꍇ  �F�e�N�X�`���f�[�^
     *  @return �쐬����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const TextureDataPtr&> C_TextureManager::GetTextureData(const std::string& rId) const
    {
        return upImpl_->GetTextureData(rId);
    }
}