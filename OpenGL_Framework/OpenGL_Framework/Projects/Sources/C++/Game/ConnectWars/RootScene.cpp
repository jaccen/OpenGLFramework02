/* ヘッダファイル */
#include "RootScene.h"
#include "ConnectWarsDefine.h"
#include "CollisionCallback.h"
#include "../../Library/Lua/LuaStateManager.h"
#include "../../Library/Particle/System/ParticleSystem.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Random/RandomGenerator.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Timer/Manager/TimeManager.h"
#include "../../Library/Common/CommonHelper.h"
#include "LoadScene.h"
#include "LoadFunction.h"


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
    C_RootScene::C_RootScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RootScene::~C_RootScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_RootScene::Initialize()
    {
        // 物理エンジンの設定
        SetPhysicsEngine();
        
        // Luaへのバインド
        BindToLua();
        
        // 次のシーンを追加
        PushNextScene();

        return Scene::ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return 続行    ：CONTINUATIOIN
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_RootScene::Update()
    {
        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::Draw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::Finalize()
    {
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの設定を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::SetPhysicsEngine()
    {
        // 1フレームのシミュレーション時間を設定
        Physics::C_PhysicsEngine::s_GetInstance()->SetFrameSimulationTime(1.0f / static_cast<float>(Timer::C_TimeManager::s_GetInstance()->GetFps()));

        // 衝突判定のコールバックを設定
        Physics::C_PhysicsEngine::s_GetInstance()->SetCollisionCallbackFunction(C_CollisionCallback::s_ContactProcess);
    }


    /*************************************************************//**
     *
     *  @brief  Luaへのバインド処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    bool C_RootScene::BindToLua()
    {
        assert(Lua::C_LuaStateManager::s_GetInstance()->GetState());
        auto pLuaState = Lua::C_LuaStateManager::s_GetInstance()->GetState().get();

        luabind::module(pLuaState.get())
        [
            // S_CreateDataをバインド
            luabind::class_<Particle::S_CreateDara>("S_ParticleCreateData")
            .def(luabind::constructor<>())
            .def_readwrite("lifeFrame_", &Particle::S_CreateDara::lifeFrame_)
            .def_readwrite("position_", &Particle::S_CreateDara::position_)
            .def_readwrite("velocity_", &Particle::S_CreateDara::velocity_)
            .def_readwrite("startAcceleration_", &Particle::S_CreateDara::startAcceleration_)
            .def_readwrite("endAcceleration_", &Particle::S_CreateDara::endAcceleration_)
            .def_readwrite("startAngle_", &Particle::S_CreateDara::startAngle_)
            .def_readwrite("endAngle_", &Particle::S_CreateDara::endAngle_)
            .def_readwrite("startWidth_", &Particle::S_CreateDara::startWidth_)
            .def_readwrite("endWidth_", &Particle::S_CreateDara::endWidth_)
            .def_readwrite("startHeight_", &Particle::S_CreateDara::startHeight_)
            .def_readwrite("endHeight_", &Particle::S_CreateDara::endHeight_)
            .def_readwrite("startColor_", &Particle::S_CreateDara::startColor_)
            .def_readwrite("endColor_", &Particle::S_CreateDara::endColor_),

            // IC_ParticleSystemをバインド
            luabind::class_<Particle::IC_ParticleSystem>("IC_ParticleSystem")
            .def("Entry", static_cast<void(Particle::IC_ParticleSystem::*)(const Particle::S_CreateDara&)>(&Particle::IC_ParticleSystem::Entry)),

            // S_Vector3をバインド
            luabind::class_<Vector3>("S_Vector3")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float>())
            .def(luabind::constructor<float, float, float>())
            .def(luabind::const_self + luabind::other<Vector3>())
            .def(luabind::const_self - luabind::other<Vector3>())
            .def(luabind::const_self *luabind::other<Vector3>())
            .def(luabind::const_self / luabind::other<Vector3>())
            .def_readwrite("x_", &Vector3::x_)
            .def_readwrite("y_", &Vector3::y_)
            .def_readwrite("z_", &Vector3::z_),

            // S_Vector4をバインド
            luabind::class_<Vector4>("S_Vector4")
            .def(luabind::constructor<>())
            .def(luabind::constructor<float>())
            .def(luabind::constructor<float, float, float, float>())
            .def(luabind::const_self + luabind::other<Vector4>())
            .def(luabind::const_self - luabind::other<Vector4>())
            .def(luabind::const_self *luabind::other<Vector4>())
            .def(luabind::const_self / luabind::other<Vector4>())
            .def_readwrite("x_", &Vector4::x_)
            .def_readwrite("y_", &Vector4::y_)
            .def_readwrite("z_", &Vector4::z_)
            .def_readwrite("w_", &Vector4::w_),

            // C_FrameCounterをバインド
            luabind::class_<Timer::C_FrameCounter>("C_FrameCounter")
            .def("GetCount", &Timer::C_FrameCounter::GetCount)
            .def("SetCount", &Timer::C_FrameCounter::SetCount)
            .def("Reset", &Timer::C_FrameCounter::Reset),

            // C_RandomGeneratorをバインド
            luabind::class_<Random::C_RandomGenerator>("C_RandomManager")
            .def("Random", static_cast<float(Random::C_RandomGenerator::*)(float, float)>(&Random::C_RandomGenerator::Random))
        ];

        const char* pLuaPathList[] =
        {
            Path::Lua::s_pBOMB_CHARGE_EFFECT,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pLuaPathList); i < arraySize; ++i)
        {
            if (luaL_dofile(pLuaState.get(), pLuaPathList[i]))
            {
                PrintLog("[ C_RootScene::BindToLua ] : Luaのファイルを開くのに失敗しました。");

                return false;
            }
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  次のシーンの追加を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::PushNextScene()
    {
        auto pNextScene = newEx C_LoadScene;

        pNextScene->SetLoadFunction(C_LoadFunction::s_LoadStage01Data);
        pNextScene->SetNextSceneId(ID::Scene::s_pSTAGE01);

        GetSceneChanger()->PushScene(pNextScene);
    }
}