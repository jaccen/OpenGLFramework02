/* ヘッダファイル */
#include "TextureManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <SDL_image.h>
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief テクスチャ
//! @brief テクスチャ関連の名前空間
//!
//-------------------------------------------------------------
namespace Texture
{
    //-------------------------------------------------------------
    //!
    //! @brief テクスチャマネージャーインプリメント
    //! @brief テクスチャマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_TextureManager::C_TextureManagerImpl
    {
    public:
        C_TextureManagerImpl(C_TextureManager* pTextureManager);                                        // コンストラクタ
        ~C_TextureManagerImpl();                                                                        // デストラクタ
        bool Create2DFromFile(const std::string& rFilePath,                                             // ファイルから2Dテクスチャの作成
                              const std::string& rId,
                              const ParameterFunction& rParameterFunction);
        bool Create2DFromFont(const Font::FontPtr& prFont,                                              // フォントからテクスチャを作成
                              const std::string& rId,
                              const std::string& rWords,
                              uint8_t red,
                              uint8_t green,
                              uint8_t blue,
                              const ParameterFunction& rParameterFunction);
        void Create2DFromPixelData(void* pPixelDatas,                                                   // ピクセル情報からテクスチャを作成
                                   int32_t width,
                                   int32_t height,
                                   OpenGL::FormatType internalFormat,
                                   OpenGL::FormatType pixelFormat,
                                   int32_t byteBoundary,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction);
         bool CreateCubeMapFromFile(const std::string& rDirectoryName,                                  // ファイルからキューブマップテクスチャを作成
                                    const std::array<std::string, 6>& rFileNames,
                                    const std::array<TypeEnum, 6>& rTargetTypes,
                                    const std::string& rId,
                                    const ParameterFunction& rParameterFunction);
        void Destroy(const std::string& rId);                                                           // テクスチャの破棄
        void AllDestroy();                                                                              // テクスチャを全て破棄
        boost::optional<const TextureDataPtr&> GetTextureData(const std::string& rId) const;            // テクスチャデーターを取得
    private:
        /* 型変換 */
        using Surface = SDL_Surface;                                                                    // Surface型を宣言
        using SurfacePtr = std::shared_ptr<Surface>;                                                    // SurfacePtr型を宣言

        std::unordered_map<std::string, TextureDataPtr> pTextureDatas_;                                 ///< @brief テクスチャデータ
        C_TextureManager* pTextureManager_ = nullptr;                                                   ///< @brief テクスチャマネージャー 

        bool Create2DFromSurface(const SurfacePtr& prSurface,                                           // サーフェスから2Dテクスチャを作成
                                 const std::string& rId,
                                 const ParameterFunction& rParameterFunction);
        bool CreateCubeMapFromSurface(const std::array<SurfacePtr, 6>& sprSurfaces,                     // サーフェスからキューブマップテクスチャを作成
                                      const std::array<TypeEnum, 6>& rTargets,
                                      const std::string& rId,
                                      const ParameterFunction& rParameterFunction);
        bool SetFormatFromSurface(const SurfacePtr& prSurface,                                          // サーフェスからフォーマットを設定
                                  int32_t* pInternalFormat,
                                  int32_t* pPixelFormat,
                                  int32_t* pByteBoundary);
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TextureManager::C_TextureManagerImpl::C_TextureManagerImpl(C_TextureManager* pTextureManager) :

        // テクスチャマネージャー
        pTextureManager_(pTextureManager)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TextureManager::C_TextureManagerImpl::~C_TextureManagerImpl()
    {
        if (pTextureDatas_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  ファイルから2Dテクスチャの作成を行う
     *  @param  ファイルパス
     *  @param  ID
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::Create2DFromFile(const std::string& rFilePath,
                                                                  const std::string& rId,
                                                                  const ParameterFunction& rParameterFunction)
    {
        // 既に作成している場合
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::Create2DFromFile ] : 既に同じテクスチャを作成しています。" << std::endl;
            std::cout << "                              ファイルパス : " << rFilePath << std::endl;

            return true;
        }

        // 画像をロード
        SurfacePtr pTemporarySurface(::IMG_Load(rFilePath.c_str()),
                                     [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

        if (!pTemporarySurface)
        {
            PrintLog("[ C_TextureManagerImpl::Create2DFromFile ] : 画像のロードに失敗しました。\n");
            PrintLog("                              ファイルパス : %s\n", rFilePath.c_str());
            PrintLog("                                エラー内容 : %s\n", IMG_GetError());
            
            return false;
        }

        // サーフェスから2Dテクスチャを作成
        if (Create2DFromSurface(pTemporarySurface, rId, rParameterFunction) == false)
        {
            PrintLog("[ C_TextureManagerImpl::Create2DFromFile ] : テクスチャの作成に失敗しました。\n");

            return false;
        }

        return true;
    }


    


    /*************************************************************//**
     *
     *  @brief  フォントからテクスチャの作成を行う
     *  @param  フォント
     *  @param  ID
     *  @param  文字
     *  @param  赤
     *  @param  緑
     *  @param  青
     *  @return 正常終了：true
     *  @return 異常終了：false
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
        // 既に作成している場合
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::Create2DFromFont ] : 既に同じフォント用のテクスチャを作成しています。" << std::endl;
            std::cout << "                                      文字 : " << rWords << std::endl;

            return true;
        }

        // フォントの色
        SDL_Color fontColor = { blue, green, red };

        // フォントから仮のサーフェスを作成
        SurfacePtr pTempSurface(::TTF_RenderUTF8_Blended(prFont.get(), rWords.c_str(), fontColor),
                                [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

        if (!pTempSurface)
        {

            std::cout << "[ C_TextureManagerImpl::Create2DFromFont ] : サーフェスの取得に失敗しました。" << std::endl;
            std::cout << "                                エラー内容 : " << TTF_GetError() << std::endl;

            return false;
        }

        // サーフェスから2Dテクスチャを作成
        if (Create2DFromSurface(pTempSurface, rId, rParameterFunction) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ピクセル情報からテクスチャの作成を行う
     *  @param  ピクセル情報
     *  @param  テクスチャの幅
     *  @param  テクスチャの高さ
     *  @param  内部で保持するフォーマット
     *  @param  ピクセルフォーマット
     *  @param  バイト境界
     *  @param  ID
     *  @return なし
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
        // ※ ここでは既に作成しているかの判断を行っていないので
        //    外部から呼び出す場合は注意すること

        // ミップマップレベル
        const int32_t MIPMAP_LEVEL = 0;

        // テクスチャの境界幅が存在するか判断するフラグ
        const int32_t BORDER_FLAG = 0;

        // テクスチャデーターの要素を追加
        pTextureDatas_.emplace(rId, std::make_shared<S_TextureData>(width, height));

        // テクスチャをバインドし、有効にする
        pTextureManager_->Bind(Type::s_2D, pTextureDatas_[rId]->textureHandle_);

        // バイト境界を設定
        ::glPixelStorei(GL_UNPACK_ALIGNMENT, byteBoundary);

        // テクスチャの設定
        rParameterFunction();

        // テクスチャを作成
        ::glTexImage2D(Type::s_2D,
                       MIPMAP_LEVEL,
                       internalFormat,
                       width,
                       height,
                       BORDER_FLAG,
                       pixelFormat,
                       GL_UNSIGNED_BYTE,
                       pPixelDatas);

        // テクスチャをアンバインド
        pTextureManager_->Unbind(Type::s_2D);
    }


    /*************************************************************//**
     *
     *  @brief  ファイルからキューブマップ用のテクスチャの作成を行う
     *  @param  ディレクトリ名
     *  @param  ファイル名
     *  @param  ターゲットの種類
     *  @param  ID
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::CreateCubeMapFromFile(const std::string& rDirectoryName,
                                                                       const std::array<std::string, 6>& rFileNames,
                                                                       const std::array<TypeEnum, 6>& rTargetTypes,
                                                                       const std::string& rId,
                                                                       const ParameterFunction& rParameterFunction)
    {
        // 既に作成している場合
        if (pTextureDatas_.find(rId) != pTextureDatas_.end())
        {
            std::cout << "[ C_TexutreManagerImpl::CreateCubeMapFromFile ] : 既に同じキューブマップ用のテクスチャを作成しています。" << std::endl;
            std::cout << "                                 ディレクトリ名 : " << rDirectoryName << std::endl;

            return true;
        }

        // 仮のサーフェス
        std::array<SurfacePtr, 6> spTempSurfaces;

        for (int i = 0; i < 6; ++i)
        {
            // ファイル名
            std::string fileName = (rDirectoryName + rFileNames[i]);

            // 画像をロード
            spTempSurfaces[i].reset(::IMG_Load(fileName.c_str()),
                                    [](Surface* pSurface){ ::SDL_FreeSurface(pSurface); });

            if (!spTempSurfaces[i])
            {
                PrintLog("[ C_TextureManagerImpl::CreateCubeMapFromFile ] : 画像のロードに失敗しました。\n");
                PrintLog("                                     ファイル名 : %s\n", fileName.c_str());
                PrintLog("                                     エラー内容 : %s\n", IMG_GetError());

                return false;
            }
        }

        // サーフェスからテクスチャを作成
        if (CreateCubeMapFromSurface(spTempSurfaces, rTargetTypes, rId, rParameterFunction) == false)
        {
            PrintLog("[ C_TextureManagerImpl::CreateCubeMapFromFile ] : キューブマップテクスチャの作成に失敗しました。\n");

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャの破棄を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::C_TextureManagerImpl::Destroy(const std::string& rId)
    {
        // テクスチャが作成されていない場合
        if (pTextureDatas_.find(rId) == pTextureDatas_.end())
        {
            std::cout << "[ C_TextureManagerImpl::Destroy ] : テクスチャが作成されていません。" << std::endl;

            return;
        }

        // 要素を削除
        pTextureDatas_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャを全て破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::C_TextureManagerImpl::AllDestroy()
    {
        pTextureDatas_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャデータの取得する
     *  @param  ID
     *  @return 作成されていた場合      ：テクスチャデータ
     *  @return 作成されていなかった場合：none
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
     *  @brief  サーフェスからテクスチャの作成を行う
     *  @param  サーフェス
     *  @param  ID
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::Create2DFromSurface(const C_TextureManager::C_TextureManagerImpl::SurfacePtr& prSurface,
                                                                     const std::string& rId,
                                                                     const ParameterFunction& rParameterFunction)
    {
        // 内部で保持するフォーマット
        int32_t internalFormat = 0;

        // ピクセルフォーマット
        int32_t pixelFormat = 0;

        // バイト境界
        int32_t byteBoundary = 0;

        // サーフェスからフォーマットを設定
        if (SetFormatFromSurface(prSurface, &internalFormat, &pixelFormat, &byteBoundary) == false)
        {
            PrintLog("[ C_TextureManagerImpl::CreateFromSurface ] : サーフェスからフォーマットの設定に失敗しました。\n");

            return false;
        }

        // ピクセル情報からテクスチャを作成
        Create2DFromPixelData(prSurface->pixels, prSurface->w, prSurface->h, internalFormat, pixelFormat, byteBoundary, rId, rParameterFunction);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サーフェスからキューブマップの作成を行う
     *  @param  サーフェス
     *  @param  ターゲットの種類
     *  @param  ID
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::CreateCubeMapFromSurface(const std::array<C_TextureManager::C_TextureManagerImpl::SurfacePtr, 6>& sprSurfaces,
                                                                          const std::array<TypeEnum, 6>& rTargetTypes,
                                                                          const std::string& rId,
                                                                          const ParameterFunction& rParameterFunction)
    {
        // ミップマップレベル
        const int32_t MIPMAP_LEVEL = 0;

        // テクスチャの境界幅が存在するか判断するフラグ
        const int32_t BORDER_FLAG = 0;

        // テクスチャデーターの要素を追加
        pTextureDatas_.emplace(rId,
                               std::make_shared<S_TextureData>(sprSurfaces[0]->w, sprSurfaces[0]->h));

        // 内部で保持するフォーマット
        int32_t internalFormat = 0;

        // ピクセルフォーマット
        int32_t pixelFormat = 0;

        // バイト境界
        int32_t byteBoundary = 0;

        // テクスチャをバインドし、有効にする
        ::glBindTexture(Type::s_CUBE_MAP, pTextureDatas_[rId]->textureHandle_);

        // テクスチャの設定
        rParameterFunction();

        for (size_t i = 0; i < 6; ++i)
        {
            // サーフェスからフォーマットを設定
            if (SetFormatFromSurface(sprSurfaces[i], &internalFormat, &pixelFormat, &byteBoundary) == false)
            {
                PrintLog("[ C_TextureManager::CreateCubeMapFromSurface ] : サーフェスからフォーマットの設定に失敗しました。\n");

                return false;
            }

            // バイト境界を設定
            ::glPixelStorei(GL_UNPACK_ALIGNMENT, byteBoundary);

            // テクスチャを作成
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
        

        // テクスチャをアンバインド
        ::glBindTexture(Type::s_CUBE_MAP, 0);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サーフェスからフォーマットの設定を行う
     *  @param  サーフェス
     *  @param  設定する内部で保持するフォーマット
     *  @param  設定するピクセルフォーマット
     *  @param  設定するバイト境界
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TextureManager::C_TextureManagerImpl::SetFormatFromSurface(const C_TextureManager::C_TextureManagerImpl::SurfacePtr& prSurface,
                                                                      int32_t* pInternalFormat,
                                                                      int32_t* pPixelFormat,
                                                                      int32_t* pByteBoundary)
    {
        // 1画素あたりのバイト数が4バイトの場合
        if (prSurface->format->BytesPerPixel == 4)
        {
            // 内部で保持するフォーマットとピクセルフォーマットを設定
            (*pInternalFormat) = OpenGL::Format::Internal::s_RGBA_8_UNORM;
            (*pPixelFormat) = OpenGL::Format::Pixel::s_RGBA;

            // バイト境界を設定
            (*pByteBoundary) = 4;
        }
        // 1画素あたりのバイト数が3バイトの場合
        else if (prSurface->format->BytesPerPixel == 3)
        {
            // 内部で保持するフォーマットとピクセルフォーマットを設定
            (*pInternalFormat) = OpenGL::Format::Internal::s_RGB_8_UNORM;
            (*pPixelFormat) = OpenGL::Format::Pixel::s_RGB;

            // バイト境界を設定
            (*pByteBoundary) = 1;
        }
        else
        {
            // 1画素あたりのバイト数
            int bytesPerPixel = prSurface->format->BytesPerPixel;

            PrintLog("[ C_TextureManagerImpl::SetFormatFromSurface ] : このBPPには対応していません。\n");
            PrintLog("                         1画素あたりのバイト数 : %d\n", bytesPerPixel);

            return false;
        }

        return true;
    }
}