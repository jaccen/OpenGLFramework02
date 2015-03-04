/* ヘッダファイル */
#include "BackgroundGenerator.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseBackground.h"
#include "BackgroundMoveLogic.h"


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
     *  @param  なし
     *
     ****************************************************************/
    C_BackgroundGenerator::C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BackgroundGenerator::~C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @param  回転量
     *  @param  拡大率
     *  @param  速度
     *  @param  加速度
     *  @param  回転速度
     *  @param  回転加速度
     *  @param  生存フレーム数
     *  @return 背景
     *
     ****************************************************************/
    BackgroundPtr C_BackgroundGenerator::Create(const std::string& rId,
                                                const Vector3& rPosition, 
                                                const Vector3& rRotation, 
                                                const Vector3& rScale,
                                                const Vector3& rVelocity,
                                                const Vector3& rAccelaration,
                                                const Vector3& rRotationVelocity,
                                                const Vector3& rRotationAccelaration,
                                                int32_t lifeFrame)
    {
        // 背景を生成し、座標を設定
        BackgroundPtr pBackground(pCreateFunctions_.at(rId)());
        pBackground->SetPosition(rPosition);
        pBackground->SetRotation(rRotation);
        pBackground->SetScale(rScale);
        pBackground->GetMoveLogic()->SetVelocity(rVelocity);
        pBackground->GetMoveLogic()->SetAccelaration(rAccelaration);
        pBackground->GetMoveLogic()->SetRotationVelocity(rRotationVelocity);
        pBackground->GetMoveLogic()->SetRotationAccelaration(rRotationAccelaration);
        pBackground->AddStringToId(std::to_string(number));
        pBackground->SetLifeFrame(lifeFrame);

        // タスクシステムに登録
        pTaskSystem_->Entry(pBackground, Priority::Task::Update::s_background, Priority::Task::Draw::s_background);

        ++number;
        
        return pBackground;
    }


    /*************************************************************//**
     *
     *  @brief  自動生成処理を行う
     *  @param  フレーム数
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::AutoCreate(int32_t frame)
    {
        while (autoCreateIndex_ < autoCreateMaxCount_ && (*pBackgroundData_)[autoCreateIndex_]["Frame"].GetValue<JSON::Integer>() <= frame)
        {
            std::string id = (*pBackgroundData_)[autoCreateIndex_]["Id"].GetValue<JSON::String>();
            
            Vector3 position = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Position"][0].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Position"][1].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Position"][2].GetValue<JSON::Real>()));

            Vector3 rotation = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Rotation"][0].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Rotation"][1].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Rotation"][2].GetValue<JSON::Real>()));

            Vector3 scale = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Scale"][0].GetValue<JSON::Real>()),
                                    static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Scale"][1].GetValue<JSON::Real>()),
                                    static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Scale"][2].GetValue<JSON::Real>()));

            Vector3 velocity = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Velocity"][0].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Velocity"][1].GetValue<JSON::Real>()),
                                       static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Velocity"][2].GetValue<JSON::Real>()));

            Vector3 accelaration = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Acceleration"][0].GetValue<JSON::Real>()),
                                           static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Acceleration"][1].GetValue<JSON::Real>()),
                                           static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["Acceleration"][2].GetValue<JSON::Real>()));

            Vector3 rotationVelocity = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationVelocity"][0].GetValue<JSON::Real>()),
                                               static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationVelocity"][1].GetValue<JSON::Real>()),
                                               static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationVelocity"][2].GetValue<JSON::Real>()));

            Vector3 rotationAccelaration = Vector3(static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationAcceleration"][0].GetValue<JSON::Real>()),
                                                   static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationAcceleration"][1].GetValue<JSON::Real>()),
                                                   static_cast<float>((*pBackgroundData_)[autoCreateIndex_]["RotationAcceleration"][2].GetValue<JSON::Real>()));

            int32_t lifeFrame = (*pBackgroundData_)[autoCreateIndex_]["LifeFrame"].GetValue<JSON::Integer>();

            Create(id, position, rotation, scale, velocity, accelaration, rotationVelocity, rotationAccelaration, lifeFrame);

            autoCreateIndex_++;
        }
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
    {
        pCreateFunctions_.emplace(rId, pCreateFunction);
    }


    /*************************************************************//**
     *
     *  @brief  タスクシステムを設定する
     *  @param  タスクシステム
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }


    /*************************************************************//**
     *
     *  @brief  背景データを設定する
     *  @param  背景データ
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetBackgroundData(JSON::JsonObject* pBackgroundData)
    {
        pBackgroundData_ = pBackgroundData;
    }


    /*************************************************************//**
     *
     *  @brief  自動生成の最大数を設定する
     *  @param  自動生成の最大数
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetAutoCreateMaxCount(int32_t autoCreateMaxCount)
    {
        autoCreateMaxCount_ = autoCreateMaxCount;
    }
}