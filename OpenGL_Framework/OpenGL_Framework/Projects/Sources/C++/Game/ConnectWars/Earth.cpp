/* ヘッダファイル */
#include "Earth.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/Material/Material/Phong/PhongMaterial.h"
#include "../../Library/Light/Light/Point/PointLight.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_Earth::C_Earth(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE).get();

        // テクスチャデータを取得
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pEARTH));
        pTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pEARTH).get();

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE).get();

        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->End();

        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Earth::~C_Earth()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    void C_Earth::DoUpdate()
    {
        rotation_.x_ += static_cast<float>(Math::s_ONE_RADIAN * 0.01);
        rotation_.y_ += static_cast<float>(Math::s_ONE_RADIAN * 0.1);
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Earth::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        modelMatrix_ = Matrix4x4::s_CreateTRS(position_, rotation_, scale_);
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(0);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Earth::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}