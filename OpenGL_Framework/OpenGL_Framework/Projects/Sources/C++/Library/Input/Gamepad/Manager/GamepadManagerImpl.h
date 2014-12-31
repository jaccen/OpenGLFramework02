/* ヘッダファイル */
#include "GamepadManager.h"
#include "../Factory/GamepadFactory.h"
#include <SDL.h>
#include <vector>


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief ゲームパッドマネージャーインプリメント
    //! @brief ゲームパッドマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_GamepadManager::C_GamepadManagerImpl
    {
    public:
        C_GamepadManagerImpl();                                                                                     // コンストラクタ
        ~C_GamepadManagerImpl();                                                                                    // デストラクタ
        void Initialize();                                                                                          // 初期化処理
        void Update();                                                                                              // 更新処理
        void Finalize();                                                                                            // 終了処理

        /* ゲッター */
        int GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const;                         // ボタンを押しているフレーム数を取得
        int GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const;                        // ボタンを離しているフレーム数を取得
        int GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const;                               // スティックのX成分を取得
        int GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const;                               // スティックのY成分を取得
        int GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const;                             // スティックを倒しているフレーム数を取得
        int GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const;                           // スティックを倒していないフレーム数を取得
    private:
        std::vector<std::unique_ptr<C_Gamepad>> upGamepads_;                                                        ///< @brief ゲームパッド
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GamepadManager::C_GamepadManagerImpl::C_GamepadManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GamepadManager::C_GamepadManagerImpl::~C_GamepadManagerImpl()
    {
        if (upGamepads_.empty() == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ゲームパッドの初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Initialize()
    {
        // 初期化されていない場合、初期化する
        if (::SDL_WasInit(SDL_INIT_JOYSTICK) == 0) ::SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        // 数を取得
        int32_t count = ::SDL_NumJoysticks();
        if (count == 0) return;

        // ゲームパッドのメモリを確保
        upGamepads_.reserve(count);

        // ファクトリを生成
        auto pFactory = std::make_unique<C_GamepadFactory>();

        for (int32_t i = 0; i < count; ++i)
        {
            // ゲームパッドの情報を取得
            GamepadData* pGamepadData = ::SDL_JoystickOpen(i);

            if (pGamepadData == nullptr)
            {
                std::cout << "[ C_GamepadManagerImpl::Initialize ] : ゲームパッドを開くのに失敗しました。" << std::endl;
                std::cout << "                          エラー内容 : " << ::SDL_GetError() << std::endl;

                break;
            }

            // 名前を取得し、ゲームパッドを生成
            const char* pNAME = ::SDL_JoystickName(pGamepadData);
            upGamepads_.emplace_back(pFactory->Create(pNAME, pGamepadData));

#ifdef _DEBUG

            // 情報を出力
            std::cout << "[ C_GamepadManagerImpl::Initialize ] : Name         : " << pNAME << std::endl;
            std::cout << "                                       AxesNumber   : " << ::SDL_JoystickNumAxes(pGamepadData) << std::endl;
            std::cout << "                                       ButtonNumber : " << ::SDL_JoystickNumButtons(pGamepadData ) << std::endl;
            std::cout << "                                       BallNumber   : " << ::SDL_JoystickNumBalls(pGamepadData) << std::endl;
            std::cout << "                                       HatNumber    : " << ::SDL_JoystickNumHats(pGamepadData) << std::endl;

#endif

        }

        // イベントのポーリングを無効にする
        if (::SDL_JoystickEventState(SDL_IGNORE) < 0)
        {
            std::cout << "[ C_GamepadManagerImpl::Initialize ] : イベントのポーリングの設定に失敗しました。" << std::endl;
            std::cout << "                          エラー内容 : " << ::SDL_GetError() << std::endl;
        }
    }


    /*************************************************************//**
     *
     *  @brief  ゲームパッドの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Update()
    {
        // 繋がれていない場合
        if (upGamepads_.size() == 0) return;

        // 入力状態を更新
        ::SDL_JoystickUpdate();

        // 更新処理
        for (auto& upGamepad : upGamepads_) upGamepad->Update();
    }


    /*************************************************************//**
     *
     *  @brief  ゲームパッドの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::C_GamepadManagerImpl::Finalize()
    {
        // 終了処理
        for (auto& upGamepad : upGamepads_) upGamepad->Finalize();

        // ゲームパッドを全て削除
        upGamepads_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを押しているフレーム数を取得する
     *  @param  ボタン
     *  @param  ゲームパッドの番号
     *  @return ボタンを押しているフレーム数
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetButtonPressingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを離しているフレーム数を取得する
     *  @param  ボタン
     *  @param  ゲームパッドの番号
     *  @return ボタンを離しているフレーム数
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetButtonReleasingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのX成分を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックのX成分
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickXComponent(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのY成分を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックのY成分
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickYComponent(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを倒しているフレーム数を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックを倒しているフレーム数
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickPushingCount(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを倒していないフレーム数を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックを倒していないフレーム数
     *
     ****************************************************************/
    int C_GamepadManager::C_GamepadManagerImpl::GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upGamepads_.at(number)->GetStickReleasingCount(stick);
    }
}