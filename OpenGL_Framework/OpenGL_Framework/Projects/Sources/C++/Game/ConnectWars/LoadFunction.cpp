/* ヘッダファイル */
#include "LoadFunction.h"
#include "ConnectWarsDefine.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Model/SelfMade/Loader/Manager/ModelLoaderManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Material/Manager/MaterialManager.h"
#include "../../Library/Material/Material/Phong/PhongMaterial.h"
#include "../../Library/Light/Manager/LightManager.h"
#include "../../Library/Light/Light/Directional/DirectionalLight.h"
#include "../../Library/Common/CommonHelper.h"



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
     *  @brief  タイトルのデータのロード処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_LoadFunction::s_LoadTitleData()
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ステージ01のデータのロード処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_LoadFunction::s_LoadStage01Data()
    {

#pragma region モデルのロード


        const char* pPrimitiveIdList[] = 
        {
            ID::Primitive::s_pNORMAL_PLAYER,
            ID::Primitive::s_pBOX_ENEMY,
            ID::Primitive::s_pSPACE,
        };

        const char* pModelPathList[] =
        {
            Path::Model::s_pNORMAL_PLAYER,
            Path::Model::s_pBOX_ENEMY,
            Path::Model::s_pSPACE,
        };

        const char* pModelIdList[] =
        {
            ID::Model::s_pNORMAL_PLAYER,
            ID::Model::s_pBOX_ENEMY,
            ID::Model::s_pSPACE,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPrimitiveIdList); i < arraySize; ++i)
        {
            if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(pPrimitiveIdList[i]))
            {
                auto pModelLoader = Model::SelfMade::C_ModelLoader::s_Create();
                pModelLoader->LoadModel(pModelPathList[i]);

                Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->Entry(pModelLoader, pModelIdList[i]);
            }
        }


#pragma endregion


#pragma region JSONからデータをロード


        const char* pJsonIdList[] =
        {
            ID::JSON::s_pNORMAL_PLAYER,
            ID::JSON::s_pSPEED_UP_OPTION,
            ID::JSON::s_pPLAYER_BULLET,
            ID::JSON::s_pOPTION_BULLET,
            ID::JSON::s_pSMALL_BEAM_OPTION,
            ID::JSON::s_pSTAGE_01_ENEMY_DATA,
            ID::JSON::s_pSPACE,
        };


        const char* pJsonPathList[] =
        {
            Path::JSON::s_pNORMAL_PLAYER,
            Path::JSON::s_pSPEED_UP_OPTION,
            Path::JSON::s_pPLAYER_BULLET,
            Path::JSON::s_pOPTION_BULLET,
            Path::JSON::s_pSMALL_BEAM_OPTION,
            Path::JSON::s_pSTAGE_01_ENEMY_DATA,
            Path::JSON::s_pSPACE,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pJsonIdList); i < arraySize; ++i)
        {
            if (!JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(pJsonIdList[i]))
            {
                auto pJsonObject = JSON::JsonObject::s_CreatePointerFromFile(pJsonPathList[i]);
                JSON::C_JsonObjectManager::s_GetInstance()->Entry(pJsonObject, pJsonIdList[i]);
            }
        }


#pragma endregion


#pragma region マテリアルのロード


        const char* pPhongMaterialIdList[] =
        {
            ID::Material::s_pBASIC,
            ID::Material::s_pDAMAGE,
        };

        auto materialData = JSON::JsonObject::s_CreateFromFile(Path::JSON::s_pMATERIAL_DATA);

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPhongMaterialIdList); i < arraySize; ++i)
        {
            if (!Material::C_MaterialManager::s_GetInstance()->GetMaterial(pPhongMaterialIdList[i]))
            {
                std::shared_ptr<Material::S_PhongMaterial> spMaterial = std::make_shared<Material::S_PhongMaterial>();

                spMaterial->diffuse_.x_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Diffuse"][0].GetValue<JSON::Real>());
                spMaterial->diffuse_.y_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Diffuse"][1].GetValue<JSON::Real>());
                spMaterial->diffuse_.z_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Diffuse"][2].GetValue<JSON::Real>());

                spMaterial->ambient_.x_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Ambient"][0].GetValue<JSON::Real>());
                spMaterial->ambient_.y_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Ambient"][1].GetValue<JSON::Real>());
                spMaterial->ambient_.z_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Ambient"][2].GetValue<JSON::Real>());
                
                spMaterial->specular_.x_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Specular"][0].GetValue<JSON::Real>());
                spMaterial->specular_.y_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Specular"][1].GetValue<JSON::Real>());
                spMaterial->specular_.z_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Specular"][2].GetValue<JSON::Real>());

                spMaterial->emissive_.x_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Emissive"][0].GetValue<JSON::Real>());
                spMaterial->emissive_.y_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Emissive"][1].GetValue<JSON::Real>());
                spMaterial->emissive_.z_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Emissive"][2].GetValue<JSON::Real>());

                spMaterial->shininess_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Shininess"].GetValue<JSON::Real>());
                spMaterial->opacity_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Opacity"].GetValue<JSON::Real>());
                spMaterial->reflectivity_ = static_cast<float>(materialData["MaterialDatas"][pPhongMaterialIdList[i]]["Reflectivity"].GetValue<JSON::Real>());

                // マテリアルを登録
                Material::C_MaterialManager::s_GetInstance()->Entry(spMaterial, pPhongMaterialIdList[i]);
            }
        }


#pragma endregion


#pragma region ライトのロード


        const char* pDirectionalLightIdList[] =
        {
            ID::Light::s_pMAIN,
        };

        auto lightData = JSON::JsonObject::s_CreateFromFile(Path::JSON::s_pLIGHT_DATA);

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pDirectionalLightIdList); i < arraySize; ++i)
        {
            if (!Light::C_LightManager::s_GetInstance()->GetLight(pDirectionalLightIdList[i]))
            {
                std::shared_ptr<Light::S_DirectionalLight> spLight = std::make_shared<Light::S_DirectionalLight>();
                
                spLight->direction_.x_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Direction"][0].GetValue<JSON::Real>());
                spLight->direction_.y_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Direction"][1].GetValue<JSON::Real>());
                spLight->direction_.z_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Direction"][2].GetValue<JSON::Real>());

                spLight->diffuse_.x_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Diffuse"][0].GetValue<JSON::Real>());
                spLight->diffuse_.y_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Diffuse"][1].GetValue<JSON::Real>());
                spLight->diffuse_.z_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Diffuse"][2].GetValue<JSON::Real>());

                spLight->ambient_.x_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Ambient"][0].GetValue<JSON::Real>());
                spLight->ambient_.y_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Ambient"][1].GetValue<JSON::Real>());
                spLight->ambient_.z_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Ambient"][2].GetValue<JSON::Real>());
                
                spLight->specular_.x_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Specular"][0].GetValue<JSON::Real>());
                spLight->specular_.y_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Specular"][1].GetValue<JSON::Real>());
                spLight->specular_.z_ = static_cast<float>(lightData["LightDatas"][pDirectionalLightIdList[i]]["Specular"][2].GetValue<JSON::Real>());

                // ライトを登録
                Light::C_LightManager::s_GetInstance()->Entry(spLight, pDirectionalLightIdList[i]);
            }
        }


#pragma endregion

        return true;
    }
}