/* ヘッダファイル */
#include "ExitRing.h"
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
    C_ExitRing::C_ExitRing(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        // 各マテリアルを取得
        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC));
        pMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC).get();

        // 各ライトを取得
        assert(Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pSHELTER));
        pLight_ = Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pSHELTER).get();

        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pEXIT_RING));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pEXIT_RING).get();

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG).get();
        cameraSubroutineIndex_ =  pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "GetBackgroundViewProjectionMatrix");

        pGlslObject_->Begin();
        
        pGlslObject_->SetUniform1f("u_gamma", 2.2f);

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
    C_ExitRing::~C_ExitRing()
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
    void C_ExitRing::DoUpdate()
    {
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ExitRing::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);
        pGlslObject_->BindActiveSubroutine(cameraSubroutineIndex_, Shader::GLSL::Type::s_VERTEX);

        Matrix4x4 originOffset = Matrix4x4::s_CreateTranslation(-0.25f, 0.0f, 0.0f);
        modelMatrix_ = Matrix4x4::s_CreateTRS(position_, rotation_, scale_) * originOffset;
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        // ライトとマテリアルを設定
        SetLight(pLight_);
        SetMaterial(pMaterial_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
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
    bool C_ExitRing::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルを設定する
     *  @param  マテリアル
     *  @return なし
     *
     ****************************************************************/
    void C_ExitRing::SetMaterial(const Material::MaterialPtr& prMaterial)
    {
        auto pMaterial = std::static_pointer_cast<Material::S_PhongMaterial>(prMaterial);

        pGlslObject_->SetUniformVector3("u_material.diffuse", pMaterial->diffuse_);
        pGlslObject_->SetUniformVector3("u_material.ambient", pMaterial->ambient_);
        pGlslObject_->SetUniformVector3("u_material.specular", pMaterial->specular_);
        pGlslObject_->SetUniform1f("u_material.shininess", pMaterial->shininess_);
    }


    /*************************************************************//**
     *
     *  @brief  メインライトを設定する
     *  @param  ライト
     *  @return なし
     *
     ****************************************************************/
    void C_ExitRing::SetLight(const Light::LightPtr& prLight)
    {
        auto pLight = std::static_pointer_cast<Light::S_PointLight>(prLight);

        pGlslObject_->SetUniformVector3("u_light.position", pLight->position_);
        pGlslObject_->SetUniform1f("u_light.constantAttenuation", pLight->constantAttenuation_);
        pGlslObject_->SetUniform1f("u_light.linearAttenuation", pLight->linearAttenuation_);
        pGlslObject_->SetUniform1f("u_light.quadraticAttenuation", pLight->quadraticAttenuation_);
        pGlslObject_->SetUniformVector3("u_light.diffuse", pLight->diffuse_);
        pGlslObject_->SetUniformVector3("u_light.ambient", pLight->ambient_);
        pGlslObject_->SetUniformVector3("u_light.specular", pLight->specular_);
    }
}