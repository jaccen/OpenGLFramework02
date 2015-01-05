/* �w�b�_�t�@�C�� */
#include "TextureManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <SDL_image.h>
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �e�N�X�`��
//! @brief �e�N�X�`���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Texture
{
    //-------------------------------------------------------------
    //!
    //! @brief �e�N�X�`���}�l�[�W���[�C���v�������g
    //! @brief �e�N�X�`���}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_TextureManager::C_TextureManagerImpl
    {
    public:
        C_TextureManagerImpl(C_TextureManager* pTextureManager);                                        // �R���X�g���N�^
        ~C_TextureManagerImpl();                                                                        // �f�X�g���N�^
        bool Create2DFromFile(const std::string& rFilePath,                                             // �t�@�C������2D�e�N�X�`���̍쐬
                              const std::string& rId,
                              const ParameterFunction& rParameterFunction);
        bool Create2DFromFont(const Font::FontPtr& prFont,                                              // �t�H���g����e�N�X�`�����쐬
                              const std::string& rId,
                              const std::string& rWords,
                              uint8_t red,
                              uint8_t green,
                              uint8_t blue,
                              const ParameterFunction& rParameterFunction);
        void Create2DFromPixelData(void* pPixelDatas,                                                   // �s�N�Z����񂩂�e�N�X�`�����쐬
                                   int32_t width,
                                   int32_t height,
                                   OpenGL::FormatType internalFormat,
                                   OpenGL::FormatType pixelFormat,
                                   int32_t byteBoundary,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction);
         bool CreateCubeMapFromFile(const std::string& rDirectoryName,                                  // �t�@�C������L���[�u�}�b�v�e�N�X�`�����쐬
                                    const std::array<std::string, 6>& rFileNames,
                                    const std::array<TypeEnum, 6>& rTargetTypes,
                                    const std::string& rId,
                                    const ParameterFunction& rParameterFunction);
        void Destroy(const std::string& rId);                                                           // �e�N�X�`���̔j��
        void AllDestroy();                                                                              // �e�N�X�`����S�Ĕj��
        boost::optional<const TextureDataPtr&> GetTextureData(const std::string& rId) const;            // �e�N�X�`���f�[�^�[���擾
    private:
        /* �^�ϊ� */
        using Surface = SDL_Surface;                                                                    // Surface�^��錾
        using SurfacePtr = std::shared_ptr<Surface>;                                                    // SurfacePtr�^��錾

        std::unordered_map<std::string, TextureDataPtr> pTextureDatas_;                                 ///< @brief �e�N�X�`���f�[�^
        C_TextureManager* pTextureManager_ = nullptr;                                                   ///< @brief �e�N�X�`���}�l�[�W���[ 

        bool Create2DFromSurface(const SurfacePtr& prSurface,                                           // �T�[�t�F�X����2D�e�N�X�`�����쐬
                                 const std::string& rId,
                                 const ParameterFunction& rParameterFunction);
        bool CreateCubeMapFromSurface(const std::array<SurfacePtr, 6>& sprSurfaces,                     // �T�[�t�F�X����L���[�u�}�b�v�e�N�X�`�����쐬
                                      const std::array<TypeEnum, 6>& rTargets,
                                      const std::string& rId,
                                      const ParameterFunction& rParameterFunction);
        bool SetFormatFromSurface(const SurfacePtr& prSurface,                                          // �T�[�t�F�X����t�H�[�}�b�g��ݒ�
                                  int32_t* pInternalFormat,
                                  int32_t* pPixelFormat,
                                  int32_t* pByteBoundary);
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TextureManager::C_TextureManagerImpl::C_TextureManagerImpl(C_TextureManager* pTextureManager) :

        // �e�N�X�`���}�l�[�W���[
        pTextureManager_(pTextureManager)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TextureManager::C_TextureManagerImpl::~C_TextureManagerImpl()
    {
        if (pTextureDatas_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �t�@�C������2D�e�N�X�`���̍쐬���s��
     *  @param  �t�@�C���p�X
     *  @param  ID
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::Create2DFromFile(const std::string& rFilePath,
                                                                  const std::string& rId,
                                                                  const ParameterFunction& rParameterFunction)
    {
        // ���ɍ쐬���Ă���ꍇ
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::Create2DFromFile ] : ���ɓ����e�N�X�`�����쐬���Ă��܂��B" << std::endl;
            std::cout << "                              �t�@�C���p�X : " << rFilePath << std::endl;

            return true;
        }

        // �摜�����[�h
        SurfacePtr pTemporarySurface(::IMG_Load(rFilePath.c_str()),
                                     [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

        if (!pTemporarySurface)
        {
            PrintLog("[ C_TextureManagerImpl::Create2DFromFile ] : �摜�̃��[�h�Ɏ��s���܂����B\n");
            PrintLog("                              �t�@�C���p�X : %s\n", rFilePath.c_str());
            PrintLog("                                �G���[���e : %s\n", IMG_GetError());
            
            return false;
        }

        // �T�[�t�F�X����2D�e�N�X�`�����쐬
        if (Create2DFromSurface(pTemporarySurface, rId, rParameterFunction) == false)
        {
            PrintLog("[ C_TextureManagerImpl::Create2DFromFile ] : �e�N�X�`���̍쐬�Ɏ��s���܂����B\n");

            return false;
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
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::Create2DFromFont(const Font::FontPtr& prFont,
                                                                  const std::string& rId,
                                                                  const std::string& rWords,
                                                                  uint8_t red,
                                                                  uint8_t green,
                                                                  uint8_t blue,
                                                                  const ParameterFunction& rParameterFunction)
    {
        // ���ɍ쐬���Ă���ꍇ
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::Create2DFromFont ] : ���ɓ����t�H���g�p�̃e�N�X�`�����쐬���Ă��܂��B" << std::endl;
            std::cout << "                                      ���� : " << rWords << std::endl;

            return true;
        }

        // �t�H���g�̐F
        SDL_Color fontColor = { blue, green, red };

        // �t�H���g���牼�̃T�[�t�F�X���쐬
        SurfacePtr pTempSurface(::TTF_RenderUTF8_Blended(prFont.get(), rWords.c_str(), fontColor),
                                [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

        if (!pTempSurface)
        {

            std::cout << "[ C_TextureManagerImpl::Create2DFromFont ] : �T�[�t�F�X�̎擾�Ɏ��s���܂����B" << std::endl;
            std::cout << "                                �G���[���e : " << TTF_GetError() << std::endl;

            return false;
        }

        // �T�[�t�F�X����2D�e�N�X�`�����쐬
        if (Create2DFromSurface(pTempSurface, rId, rParameterFunction) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �s�N�Z����񂩂�e�N�X�`���̍쐬���s��
     *  @param  �s�N�Z�����
     *  @param  �e�N�X�`���̕�
     *  @param  �e�N�X�`���̍���
     *  @param  �����ŕێ�����t�H�[�}�b�g
     *  @param  �s�N�Z���t�H�[�}�b�g
     *  @param  �o�C�g���E
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::C_TextureManagerImpl::Create2DFromPixelData(void* pPixelDatas,
                                                                       int32_t width,
                                                                       int32_t height,
                                                                       OpenGL::FormatType internalFormat,
                                                                       OpenGL::FormatType pixelFormat,
                                                                       int32_t byteBoundary,
                                                                       const std::string& rId,
                                                                       const ParameterFunction& rParameterFunction)
    {
        // �� �����ł͊��ɍ쐬���Ă��邩�̔��f���s���Ă��Ȃ��̂�
        //    �O������Ăяo���ꍇ�͒��ӂ��邱��

        // �~�b�v�}�b�v���x��
        const int32_t MIPMAP_LEVEL = 0;

        // �e�N�X�`���̋��E�������݂��邩���f����t���O
        const int32_t BORDER_FLAG = 0;

        // �e�N�X�`���f�[�^�[�̗v�f��ǉ�
        pTextureDatas_.emplace(rId, std::make_shared<S_TextureData>(width, height));

        // �e�N�X�`�����o�C���h���A�L���ɂ���
        pTextureManager_->Bind(Type::s_2D, pTextureDatas_[rId]->textureHandle_);

        // �o�C�g���E��ݒ�
        ::glPixelStorei(GL_UNPACK_ALIGNMENT, byteBoundary);

        // �e�N�X�`���̐ݒ�
        rParameterFunction();

        // �e�N�X�`�����쐬
        ::glTexImage2D(Type::s_2D,
                       MIPMAP_LEVEL,
                       internalFormat,
                       width,
                       height,
                       BORDER_FLAG,
                       pixelFormat,
                       GL_UNSIGNED_BYTE,
                       pPixelDatas);

        // �e�N�X�`�����A���o�C���h
        pTextureManager_->Unbind(Type::s_2D);
    }


    /*************************************************************//**
     *
     *  @brief  �t�@�C������L���[�u�}�b�v�p�̃e�N�X�`���̍쐬���s��
     *  @param  �f�B���N�g����
     *  @param  �t�@�C����
     *  @param  �^�[�Q�b�g�̎��
     *  @param  ID
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::CreateCubeMapFromFile(const std::string& rDirectoryName,
                                                                       const std::array<std::string, 6>& rFileNames,
                                                                       const std::array<TypeEnum, 6>& rTargetTypes,
                                                                       const std::string& rId,
                                                                       const ParameterFunction& rParameterFunction)
    {
        // ���ɍ쐬���Ă���ꍇ
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::CreateCubeMapFromFile ] : ���ɓ����L���[�u�}�b�v�p�̃e�N�X�`�����쐬���Ă��܂��B" << std::endl;
            std::cout << "                                 �f�B���N�g���� : " << rDirectoryName << std::endl;

            return true;
        }

        // ���̃T�[�t�F�X
        std::array<SurfacePtr, 6> spTempSurfaces;

        for (int i = 0; i < 6; ++i)
        {
            // �t�@�C����
            std::string fileName = (rDirectoryName + rFileNames[i]);

            // �摜�����[�h
            spTempSurfaces[i].reset(::IMG_Load(fileName.c_str()),
                                    [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

            if (!spTempSurfaces[i])
            {
                PrintLog("[ C_TextureManagerImpl::CreateCubeMapFromFile ] : �摜�̃��[�h�Ɏ��s���܂����B\n");
                PrintLog("                                     �t�@�C���� : %s\n", fileName.c_str());
                PrintLog("                                     �G���[���e : %s\n", IMG_GetError());

                return false;
            }
        }

        // �T�[�t�F�X����e�N�X�`�����쐬
        if (CreateCubeMapFromSurface(spTempSurfaces, rTargetTypes, rId, rParameterFunction) == false)
        {
            PrintLog("[ C_TextureManagerImpl::CreateCubeMapFromFile ] : �L���[�u�}�b�v�e�N�X�`���̍쐬�Ɏ��s���܂����B\n");

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���̔j�����s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::C_TextureManagerImpl::Destroy(const std::string& rId)
    {
        // �e�N�X�`�����쐬����Ă��Ȃ��ꍇ
        if (pTextureDatas_.find(rId) == pTextureDatas_.end())
        {
            std::cout << "[ C_TextureManagerImpl::Destroy ] : �e�N�X�`�����쐬����Ă��܂���B" << std::endl;

            return;
        }

        // �v�f���폜
        pTextureDatas_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`����S�Ĕj������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TextureManager::C_TextureManagerImpl::AllDestroy()
    {
        pTextureDatas_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���f�[�^�̎擾����
     *  @param  ID
     *  @return �쐬����Ă����ꍇ      �F�e�N�X�`���f�[�^
     *  @return �쐬����Ă��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const TextureDataPtr&> C_TextureManager::C_TextureManagerImpl::GetTextureData(const std::string& rId) const
    {
        auto iterator = pTextureDatas_.find(rId);
        if (iterator == pTextureDatas_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  �T�[�t�F�X����e�N�X�`���̍쐬���s��
     *  @param  �T�[�t�F�X
     *  @param  ID
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::Create2DFromSurface(const C_TextureManager::C_TextureManagerImpl::SurfacePtr& prSurface,
                                                                     const std::string& rId,
                                                                     const ParameterFunction& rParameterFunction)
    {
        // �����ŕێ�����t�H�[�}�b�g
        int32_t internalFormat = 0;

        // �s�N�Z���t�H�[�}�b�g
        int32_t pixelFormat = 0;

        // �o�C�g���E
        int32_t byteBoundary = 0;

        // �T�[�t�F�X����t�H�[�}�b�g��ݒ�
        if (SetFormatFromSurface(prSurface, &internalFormat, &pixelFormat, &byteBoundary) == false)
        {
            PrintLog("[ C_TextureManagerImpl::CreateFromSurface ] : �T�[�t�F�X����t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B\n");

            return false;
        }

        // �s�N�Z����񂩂�e�N�X�`�����쐬
        Create2DFromPixelData(prSurface->pixels, prSurface->w, prSurface->h, internalFormat, pixelFormat, byteBoundary, rId, rParameterFunction);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�[�t�F�X����L���[�u�}�b�v�̍쐬���s��
     *  @param  �T�[�t�F�X
     *  @param  �^�[�Q�b�g�̎��
     *  @param  ID
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::CreateCubeMapFromSurface(const std::array<C_TextureManager::C_TextureManagerImpl::SurfacePtr, 6>& sprSurfaces,
                                                                          const std::array<TypeEnum, 6>& rTargetTypes,
                                                                          const std::string& rId,
                                                                          const ParameterFunction& rParameterFunction)
    {
        // �~�b�v�}�b�v���x��
        const int32_t MIPMAP_LEVEL = 0;

        // �e�N�X�`���̋��E�������݂��邩���f����t���O
        const int32_t BORDER_FLAG = 0;

        // �e�N�X�`���f�[�^�[�̗v�f��ǉ�
        pTextureDatas_.emplace(rId,
                               std::make_shared<S_TextureData>(sprSurfaces[0]->w, sprSurfaces[0]->h));

        // �����ŕێ�����t�H�[�}�b�g
        int32_t internalFormat = 0;

        // �s�N�Z���t�H�[�}�b�g
        int32_t pixelFormat = 0;

        // �o�C�g���E
        int32_t byteBoundary = 0;

        // �e�N�X�`�����o�C���h���A�L���ɂ���
        ::glBindTexture(Type::s_CUBE_MAP, pTextureDatas_[rId]->textureHandle_);

        // �e�N�X�`���̐ݒ�
        rParameterFunction();

        for (size_t i = 0; i < 6; ++i)
        {
            // �T�[�t�F�X����t�H�[�}�b�g��ݒ�
            if (SetFormatFromSurface(sprSurfaces[i], &internalFormat, &pixelFormat, &byteBoundary) == false)
            {
                PrintLog("[ C_TextureManager::CreateCubeMapFromSurface ] : �T�[�t�F�X����t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B\n");

                return false;
            }

            // �o�C�g���E��ݒ�
            ::glPixelStorei(GL_UNPACK_ALIGNMENT, byteBoundary);

            // �e�N�X�`�����쐬
            ::glTexImage2D(rTargetTypes[i],
                           MIPMAP_LEVEL,
                           internalFormat,
                           sprSurfaces[i]->w,
                           sprSurfaces[i]->h,
                           BORDER_FLAG,
                           pixelFormat,
                           GL_UNSIGNED_BYTE,
                           sprSurfaces[i]->pixels);
        }
        

        // �e�N�X�`�����A���o�C���h
        ::glBindTexture(Type::s_CUBE_MAP, 0);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �T�[�t�F�X����t�H�[�}�b�g�̐ݒ���s��
     *  @param  �T�[�t�F�X
     *  @param  �ݒ肷������ŕێ�����t�H�[�}�b�g
     *  @param  �ݒ肷��s�N�Z���t�H�[�}�b�g
     *  @param  �ݒ肷��o�C�g���E
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::SetFormatFromSurface(const C_TextureManager::C_TextureManagerImpl::SurfacePtr& prSurface,
                                                                      int32_t* pInternalFormat,
                                                                      int32_t* pPixelFormat,
                                                                      int32_t* pByteBoundary)
    {
        // 1��f������̃o�C�g����4�o�C�g�̏ꍇ
        if (prSurface->format->BytesPerPixel == 4)
        {
            // �����ŕێ�����t�H�[�}�b�g�ƃs�N�Z���t�H�[�}�b�g��ݒ�
            (*pInternalFormat) = OpenGL::Format::Internal::s_RGBA_8_UNORM;
            (*pPixelFormat) = OpenGL::Format::Pixel::s_RGBA;

            // �o�C�g���E��ݒ�
            (*pByteBoundary) = 4;
        }
        // 1��f������̃o�C�g����3�o�C�g�̏ꍇ
        else if (prSurface->format->BytesPerPixel == 3)
        {
            // �����ŕێ�����t�H�[�}�b�g�ƃs�N�Z���t�H�[�}�b�g��ݒ�
            (*pInternalFormat) = OpenGL::Format::Internal::s_RGB_8_UNORM;
            (*pPixelFormat) = OpenGL::Format::Pixel::s_RGB;

            // �o�C�g���E��ݒ�
            (*pByteBoundary) = 1;
        }
        else
        {
            // 1��f������̃o�C�g��
            int bytesPerPixel = prSurface->format->BytesPerPixel;

            PrintLog("[ C_TextureManagerImpl::SetFormatFromSurface ] : ����BPP�ɂ͑Ή����Ă��܂���B\n");
            PrintLog("                         1��f������̃o�C�g�� : %d\n", bytesPerPixel);

            return false;
        }

        return true;
    }
}