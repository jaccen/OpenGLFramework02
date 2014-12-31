/* ヘッダファイル */
#include "KeyboardManager.h"
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
    //! @brief キーボードマネージャーインプリメント
    //! @brief キーボードマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_KeyboardManager::C_KeyboardManagerImpl
    {
    public:
        C_KeyboardManagerImpl();                                            // コンストラクタ
        ~C_KeyboardManagerImpl();                                           // デストラクタ
        void Initialize();                                                  // 初期化処理
        void Update();                                                      // 更新処理
        int32_t GetPressingCount(KeyCode keycode) const;                    // 押しているフレーム数を取得
        int32_t GetReleasingCount(KeyCode keycode) const;                   // 離しているフレーム数を取得
        const std::string& GetInputCharacter() const;                       // 入力した文字を取得
        void SetInputCharacter(const std::string& rInputCharacter);         // 入力した文字を設定
    private:
        int32_t count_ = 0;                                                 ///< @brief 数
        const uint8_t* pAllState_ = nullptr;                                ///< @brief すべての状態
        std::vector<int32_t> pressingCounts_;                               ///< @brief 押しているフレーム数のカウンタ
        std::vector<int32_t> releasingCounts_;                              ///< @brief 離しているフレーム数のカウンタ
        std::string inputCharacter_;                                        ///< @brief 入力した文字     
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_KeyboardManager::C_KeyboardManagerImpl::C_KeyboardManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_KeyboardManager::C_KeyboardManagerImpl::~C_KeyboardManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::Initialize()
    {
        // キーの数と状態を取得
        pAllState_ = ::SDL_GetKeyboardState(&count_);

        // 入力を管理するカウンタの配列のサイズを設定
        pressingCounts_.resize(count_, 0);
        releasingCounts_.resize(count_, 0);
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::Update()
    {
        for (int32_t i = 0; i < count_; ++i)
        {
            // 入力されている場合
            if (pAllState_[i] == 1)
            {
                // 離しているフレーム数をリセットし、
                // 押されているフレーム数を1増加
                if (releasingCounts_[i] > 0) releasingCounts_[i] = 0;

                ++pressingCounts_[i];
            }
            else
            {
                // 押されているフレーム数をリセットし、
                // 離されているフレーム数を1増加
                if (pressingCounts_[i] > 0) pressingCounts_[i] = 0;

                ++releasingCounts_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  押しているフレーム数を取得する
     *  @param  スキャンコード
     *  @return 押しているフレーム数
     *
     ****************************************************************/
    int32_t C_KeyboardManager::C_KeyboardManagerImpl::GetPressingCount(KeyCode keycode) const
    {
        return pressingCounts_.at(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  離しているフレーム数を取得する
     *  @param  スキャンコード
     *  @return 離しているフレーム数
     *
     ****************************************************************/
    int32_t C_KeyboardManager::C_KeyboardManagerImpl::GetReleasingCount(KeyCode keycode) const
    {
        return releasingCounts_.at(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  入力した文字を取得する
     *  @param  なし
     *  @return 入力した文字
     *
     ****************************************************************/
    const std::string& C_KeyboardManager::C_KeyboardManagerImpl::GetInputCharacter() const
    {
        return inputCharacter_;
    }


    /*************************************************************//**
     *
     *  @brief  入力した文字を設定する
     *  @param  入力した文字
     *  @return なし
     *
     ****************************************************************/
    void C_KeyboardManager::C_KeyboardManagerImpl::SetInputCharacter(const std::string& rInputCharacter)
    {
        inputCharacter_ = rInputCharacter;
    }
}