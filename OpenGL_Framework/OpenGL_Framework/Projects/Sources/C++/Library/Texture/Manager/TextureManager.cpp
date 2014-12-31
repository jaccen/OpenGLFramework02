/* ヘッダファイル */
#include "TextureManagerImpl.h"



//-------------------------------------------------------------
//!
//! @brief テクスチャ
//! @brief テクスチャ関連の名前空間
//!
//-------------------------------------------------------------
namespace Texture
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TextureManager::C_TextureManager() :

        // 実装情報
        upImpl_(std::make_unique<C_TextureManagerImpl>(this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TextureManager::~C_TextureManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ファイルから2Dテクスチャの作成を行う
     *  @param  ファイルパス
     *  @param  ID
     *  @param  パラメータ設定を行う関数
     *  @return 正常終了：true
     *  @return 異常終了：false
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
     *  @brief  フォントからテクスチャの作成を行う
     *  @param  フォント
     *  @param  ID
     *  @param  文字
     *  @param  赤
     *  @param  緑
     *  @param  青
     *  @param  パラメータ設定を行う関数
     *  @return 正常終了：true
     *  @return 異常終了：false
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
     *  @brief  ピクセル情報からテクスチャの作成を行う
     *  @param  ピクセル情報
     *  @param  テクスチャの幅
     *  @param  テクスチャの高さ
     *  @param  内部フォーマット
     *  @param  ピクセルフォーマット
     *  @param  バイト境界
     *  @param  ID
     *  @param パラメータ設定を行う関数
     *  @return なし
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
     *  @brief  ファイルからキューブマップテクスチャの作成を行う
     *  @param  ディレクトリ名
     *  @param  ファイル名
     *  @param  ターゲットの種類
     *  @param  ID
     *  @param  パラメータ設定を行う関数
     *  @return 正常終了：true
     *  @return 異常終了：false
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
     *  @brief  テクスチャの破棄を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::Destroy(const std::string& rFilePath)
    {
        upImpl_->Destroy(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャを全て破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  アクティブにするテクスチャユニットの設定を行う
     *  @param  テクスチャユニットの番号( 0 ～ 31まで )
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::SetActiveUnit(uint32_t unitNumber)
    {
        assert(unitNumber >= 0 && unitNumber < 32);

        glActiveTexture(GL_TEXTURE0 + unitNumber);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャのバインドを行う
     *  @param  テクスチャの種類
     *  @param  テクスチャハンドル
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::Bind(TypeEnum type, TextureHandle handle)
    {
        ::glBindTexture(type, handle);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャのアンバインドを行う
     *  @param  テクスチャの種類
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::Unbind(TypeEnum type)
    {
        ::glBindTexture(type, 0);
    }


    /*************************************************************//**
     *
     *  @brief  パラメータの設定を行う
     *  @param  種類
     *  @param  パラメータ
     *  @param  パラメータの値
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, int32_t parameterValue)
    {
        ::glTexParameteri(type, parameter, parameterValue);
    }


    /*************************************************************//**
     *
     *  @brief  パラメータの設定を行う
     *  @param  種類
     *  @param  パラメータ
     *  @param  パラメータの値
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, float parameterValue)
    {
        ::glTexParameterf(type, parameter, parameterValue);
    }


    /*************************************************************//**
     *
     *  @brief  パラメータの設定を行う
     *  @param  種類
     *  @param  パラメータ
     *  @param  パラメータの値
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, int32_t patameterValues[])
    {
        ::glTexParameteriv(type, parameter, patameterValues);
    }


    /*************************************************************//**
     *
     *  @brief  パラメータの設定を行う
     *  @param  種類
     *  @param  パラメータ
     *  @param  パラメータの値
     *  @return なし
     *
     ****************************************************************/
    void C_TextureManager::SetTextureParameter(TypeEnum type, ParameterEnum parameter, float patameterValues[])
    {
        ::glTexParameterfv(type, parameter, patameterValues);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャデータを取得する
     *  @param  ID
     *  @return 作成されていた場合  ：テクスチャデータ
     *  @return 作成されていない場合：none
     *
     ****************************************************************/
    boost::optional<const TextureDataPtr&> C_TextureManager::GetTextureData(const std::string& rId) const
    {
        return upImpl_->GetTextureData(rId);
    }
}