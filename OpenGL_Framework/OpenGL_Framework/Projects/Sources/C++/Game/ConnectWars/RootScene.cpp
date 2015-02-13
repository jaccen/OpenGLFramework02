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
#include "../../Library/JSON/Object/JsonObject.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"
#include "../../Library/Camera/Camera/Orthographic/OrthographicCamera.h"
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

        // タスクの優先度を設定
        SetTaskPriority();

        // カメラを作成
        CreateCameras();

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
        // 次のシーンを追加
        PushNextScene();

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
        Camera::C_CameraManager::s_GetInstance()->AllRemove();
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
        static bool s_initializeFlag = false;

        assert(Lua::C_LuaStateManager::s_GetInstance()->GetState());
        auto pLuaState = Lua::C_LuaStateManager::s_GetInstance()->GetState().get();

        if (s_initializeFlag == false)
        {
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

            // 初期化済みフラグを立てる
            s_initializeFlag = true;
        }

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
     *  @brief  タスクの優先度を設定する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::SetTaskPriority()
    {
        // タスクの優先度データを取得
        auto taskPriorityData = JSON::JsonObject::s_CreateFromFile(Path::JSON::s_pTASK_PRIORITY_DATA);

        // 更新優先度を設定
        Priority::Task::Update::s_gameController = static_cast<float>(taskPriorityData["Priority"]["Update"]["GameController"].GetValue<JSON::Real>());
        Priority::Task::Update::s_player = static_cast<float>(taskPriorityData["Priority"]["Update"]["Player"].GetValue<JSON::Real>());
        Priority::Task::Update::s_option = static_cast<float>(taskPriorityData["Priority"]["Update"]["Option"].GetValue<JSON::Real>());
        Priority::Task::Update::s_enemy = static_cast<float>(taskPriorityData["Priority"]["Update"]["Enemy"].GetValue<JSON::Real>());
        Priority::Task::Update::s_bullet = static_cast<float>(taskPriorityData["Priority"]["Update"]["Bullet"].GetValue<JSON::Real>());
        Priority::Task::Update::s_bomb = static_cast<float>(taskPriorityData["Priority"]["Update"]["Bomb"].GetValue<JSON::Real>());
        Priority::Task::Update::s_obstacle = static_cast<float>(taskPriorityData["Priority"]["Update"]["Obstacle"].GetValue<JSON::Real>());
        Priority::Task::Update::s_effect = static_cast<float>(taskPriorityData["Priority"]["Update"]["Effect"].GetValue<JSON::Real>());
        Priority::Task::Update::s_background = static_cast<float>(taskPriorityData["Priority"]["Update"]["Background"].GetValue<JSON::Real>());

        // 描画優先度を設定
        Priority::Task::Draw::s_gameController = static_cast<float>(taskPriorityData["Priority"]["Draw"]["GameController"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_player = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Player"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_option = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Option"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_enemy = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Enemy"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_bullet = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Bullet"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_bomb = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Bomb"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_obstacle = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Obstacle"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_effect = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Effect"].GetValue<JSON::Real>());
        Priority::Task::Draw::s_background = static_cast<float>(taskPriorityData["Priority"]["Draw"]["Background"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  カメラの作成を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RootScene::CreateCameras()
    {
        // メインウィンドウを取得
        assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
        auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

        // メインカメラと背景用カメラを作成
        const char* pPerspectiveCameraIdList[] =
        {
            ID::Camera::s_pMAIN,
            ID::Camera::s_pBACKGROUND,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPerspectiveCameraIdList); i < arraySize; ++i)
        {
            if (!Camera::C_CameraManager::s_GetInstance()->GetCamera(pPerspectiveCameraIdList[i]))
            {
                auto cameraData = JSON::JsonObject::s_CreateFromFile(Path::JSON::s_pCAMERA);

#ifdef _DEBUG

                std::shared_ptr<Camera::C_PerspectiveCamera> pCamera;

                if (i == 0)
                {
                    pCamera = std::make_shared<Camera::C_PerspectiveCamera>();
                }
                else
                {
                    pCamera = std::make_shared<Camera::C_TestCamera>();
                }
#else

                auto pCamera = std::make_shared<Camera::C_PerspectiveCamera>();

#endif

                pCamera->SetEyePoint(Camera::Vector3(static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["EyePoint"][0].GetValue<JSON::Real>()),
                                                     static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["EyePoint"][1].GetValue<JSON::Real>()),
                                                     static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["EyePoint"][2].GetValue<JSON::Real>())));

                pCamera->SetTargetPoint(Camera::Vector3(static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["TargetPoint"][0].GetValue<JSON::Real>()),
                                                        static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["TargetPoint"][1].GetValue<JSON::Real>()),
                                                        static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["TargetPoint"][2].GetValue<JSON::Real>())));

                pCamera->SetFieldOfViewY(static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["FieldOfViewY"].GetValue<JSON::Real>()));
                pCamera->SetNearClippingPlane(static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["NearClippingPlane"].GetValue<JSON::Real>()));
                pCamera->SetFarClippingPlane(static_cast<float>(cameraData["CameraData"][pPerspectiveCameraIdList[i]]["FarClippngPlane"].GetValue<JSON::Real>()));
                pCamera->SetUpVector(Camera::Vector3::s_UP_DIRECTION);
                pCamera->SetAspectRatio(pMainWindow->GetAspectRatio<float>());
                pCamera->Update();

                Camera::C_CameraManager::s_GetInstance()->Entry(pCamera, pPerspectiveCameraIdList[i]);
            }
        }

        // 正投影カメラを作成
        auto pUiCamera = std::make_shared<Camera::C_OrthographicCamera>();
        pUiCamera->SetClipSpace(0.0f, static_cast<float>(pMainWindow->GetWidth()), static_cast<float>(pMainWindow->GetHeight()), 0.0f);
        pUiCamera->Update();
        Camera::C_CameraManager::s_GetInstance()->Entry(pUiCamera, ID::Camera::s_pUI);
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