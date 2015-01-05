/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../TextureDefine.h"
#include "../../Font/FontManager.h"
#include "../../OpenGL/OpenGlDefine.h"
#include <functional>
#include <array>


//-------------------------------------------------------------
//!
//! @brief テクスチャ
//! @brief テクスチャ関連の名前空間
//!
//-------------------------------------------------------------
namespace Texture
{
    /* 別名 */
    using ParameterFunction = std::function<void()>;                                                            // ParameterFunction型
    using TextureDataPtr = std::shared_ptr<S_TextureData>;                                                      // TextureDataPtr型


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pSAME_FILE_PATH = "SameFilePath";                                                     ///< @brief ファイルパスと同じ
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief テクスチャマネージャー
    //! @brief テクスチャを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_TextureManager : public Singleton::C_Singleton<C_TextureManager>
    {
        friend C_Singleton<C_TextureManager>;                                                                   // シングルトンクラスをフレンド化
    public:
        bool Create2DFromFile(const std::string& rFilePath,                                                     // ファイルから2Dテクスチャの作成
                              const std::string& rId = ID::s_pSAME_FILE_PATH,
                              const ParameterFunction& rParameterFunction = s_Default2DParameter);
        bool Create2DFromFont(const Font::FontPtr& prFont,                                                      // フォントから2Dテクスチャを作成
                              const std::string& rId,
                              const std::string& rWords,
                              uint8_t red = 0,
                              uint8_t green = 0,
                              uint8_t blue = 0,
                              const ParameterFunction& rParameterFunction = s_Default2DParameter);
        void Create2DFromPixelData(void* pPixelDatas,                                                           // ピクセル情報から2Dテクスチャを作成
                                   int32_t width,
                                   int32_t height,
                                   OpenGL::FormatType internalFormat,
                                   OpenGL::FormatType pixelFormat,
                                   int32_t byteBoundary,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction = s_Default2DParameter);
        bool CreateCubeMapFromFile(const std::string& rDirectoryName,                                          // ファイルからキューブマップテクスチャの作成
                                   const std::array<std::string, 6>& rFileNames,
                                   const std::array<TypeEnum, 6>& rTargetTypes,
                                   const std::string& rId,
                                   const ParameterFunction& rParameterFunction = s_DefaultCubeMapParameter);
        void Destroy(const std::string& rId);                                                                   // テクスチャの破棄
        void AllDestroy();                                                                                      // テクスチャを全て破棄
        void SetActiveUnit(uint32_t unitNumber = 0);                                                            // アクティブにするテクスチャユニットの設定
        void Bind(TypeEnum type, TextureHandle handle);                                                         // テクスチャをバインド
        void Unbind(TypeEnum type);                                                                             // テクスチャをアンバインド
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, int32_t patameterValue);               // パラメータの設定
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, float patameterValue);                 // パラメータの設定
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, int32_t patameterValues[]);            // パラメータの設定
        void SetTextureParameter(TypeEnum type, ParameterEnum patameter, float patameterValues[]);              // パラメータの設定
        boost::optional<const TextureDataPtr&> GetTextureData(const std::string& rId) const;                    // テクスチャデータを取得
    private:
        /* 前方宣言 */
        class C_TextureManagerImpl;

        std::unique_ptr<C_TextureManagerImpl> upImpl_;                                                          ///< @brief 実装情報

        C_TextureManager();                                                                                     // コンストラクタ
        ~C_TextureManager() override;                                                                           // デストラクタ
    };
}