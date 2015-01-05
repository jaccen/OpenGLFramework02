/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../TextureDefine.h"
#include "../../Font/FontManager.h"
#include "../../OpenGL/OpenGlDefine.h"
#include <functional>
#include <array>


//-------------------------------------------------------------
//!
//! @brief �e�N�X�`��
//! @brief �e�N�X�`���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Texture
{
    /* �ʖ� */
    using ParameterFunction = std::function<void()>;                                                            // ParameterFunction�^
    using TextureDataPtr = std::shared_ptr<S_TextureData>;                                                      // TextureDataPtr�^


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pSAME_FILE_PATH = "SameFilePath";                                                     ///< @brief �t�@�C���p�X�Ɠ���
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �e�N�X�`���}�l�[�W���[
    //! @brief �e�N�X�`�����Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_TextureManager : public Singleton::C_Singleton<C_TextureManager>
    {
        friend C_Singleton<C_TextureManager>;                                                                   // �V���O���g���N���X���t�����h��
    public:
        bool Create2DFromFile(const std::string& rFilePath,                                                     // �t�@�C������2D�e�N�X�`���̍쐬
                              const std::string& rId = ID::s_pSAME_FILE_PATH,
                              const ParameterFunction& rParameterFunction = s_Default2DParameter);
        bool Create2DFromFont(const Font::FontPtr& prFont,                                                      // �t�H���g����2D�e�N�X�`�����쐬
                              const std::string& rId,
                              const std::string& rWords,
                              uint8_t red = 0,
                              uint8_t green = 0,
                              uint8_t blue = 0,
                              const ParameterFunction& rParameterFunction = s_Default2DParameter);
        void Create2DFromPixelData(void* pPixelDatas,                                                           // �s�N�Z����񂩂�2D�e�N�X�`�����쐬
                                   int32_t width,
                                   int32_t height,
                                   OpenGL::FormatType internalFormat,
                                   OpenGL::FormatType pixelFormat,
                                   int32_t byteBoundary,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction = s_Default2DParameter);
        bool CreateCubeMapFromFile(const std::string& rDirectoryName,                                          // �t�@�C������L���[�u�}�b�v�e�N�X�`���̍쐬
                                   const std::array<std::string, 6>& rFileNames,
                                   const std::array<TypeEnum, 6>& rTargetTypes,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction = s_DefaultCubeMapParameter);
        void Destroy(const std::string& rId);                                                                   // �e�N�X�`���̔j��
        void AllDestroy();                                                                                      // �e�N�X�`����S�Ĕj��
        void SetActiveUnit(uint32_t unitNumber = 0);                                                            // �A�N�e�B�u�ɂ���e�N�X�`�����j�b�g�̐ݒ�
        void Bind(TypeEnum type, TextureHandle handle);                                                         // �e�N�X�`�����o�C���h
        void Unbind(TypeEnum type);                                                                             // �e�N�X�`�����A���o�C���h
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, int32_t patameterValue);               // �p�����[�^�̐ݒ�
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, float patameterValue);                 // �p�����[�^�̐ݒ�
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, int32_t patameterValues[]);            // �p�����[�^�̐ݒ�
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, float patameterValues[]);              // �p�����[�^�̐ݒ�
        boost::optional<const TextureDataPtr&> GetTextureData(const std::string& rId) const;                    // �e�N�X�`���f�[�^���擾
    private:
        /* �O���錾 */
        class C_TextureManagerImpl;

        std::unique_ptr<C_TextureManagerImpl> upImpl_;                                                          ///< @brief �������

        C_TextureManager();                                                                                     // �R���X�g���N�^
        ~C_TextureManager() override;                                                                           // �f�X�g���N�^
    };
}