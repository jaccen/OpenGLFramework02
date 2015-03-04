/* ヘッダファイル */
#include "Shelter.h"
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
    C_Shelter::C_Shelter(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        // 各マテリアルを取得
        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC));
        pMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC).get();

        // 各ライトを取得
        assert(Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pSHELTER));
        pLight_ = Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pSHELTER).get();

        // モデル情報を取得
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSHELTER));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSHELTER).get();

        // テクスチャデータを取得
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSHELTER));
        pTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSHELTER).get();

        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSHALTER_NORMAL));
        pNormalTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSHALTER_NORMAL).get();

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_NORMAL_TEXTURE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_NORMAL_TEXTURE).get();
        cameraSubroutineIndex_ =  pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "GetBackgroundViewProjectionMatrix");

        pGlslObject_->Begin();
        
        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->SetUniform1i("u_normalTexture", 1);
        pGlslObject_->SetUniform1f("u_gamma", 2.2f);

        pGlslObject_->End();

        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        // カメラを取得
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pBACKGROUND));
        pCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pBACKGROUND).get();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Shelter::~C_Shelter()
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
    void C_Shelter::DoUpdate()
    {
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Shelter::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);
        pGlslObject_->BindActiveSubroutine(cameraSubroutineIndex_, Shader::GLSL::Type::s_VERTEX);

        modelMatrix_ = Matrix4x4::s_CreateTRS(position_, rotation_, scale_);
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        Vector3 eyePoint = std::static_pointer_cast<Camera::C_PerspectiveCamera>(pCamera_)->GetEyePoint();
        pGlslObject_->SetUniformVector3("u_eyePosition", eyePoint);

        // ライトとマテリアルを設定
        SetLight(pLight_);
        SetMaterial(pMaterial_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        pOpenGlManager->EnableCulling(false);

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(0);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        pTextureManager->SetActiveUnit(1);
        pTextureManager->Bind(Texture::Type::s_2D, pNormalTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pOpenGlManager->EnableCulling(true);

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
    bool C_Shelter::DoMessageProcess(const Telegram& rTelegram)
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
    void C_Shelter::SetMaterial(const Material::MaterialPtr& prMaterial)
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
    void C_Shelter::SetLight(const Light::LightPtr& prLight)
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