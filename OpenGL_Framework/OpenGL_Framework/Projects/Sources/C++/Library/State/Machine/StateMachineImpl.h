//-------------------------------------------------------------
//!
//! @brief ステート
//! @brief 状態関連の名前空間
//!
//-------------------------------------------------------------
namespace State
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  オーナー
     *  @param  現在のステート
     *  @param  グローバルステート
     *
     ****************************************************************/
    template<typename T>
    C_StateMachine<T>::C_StateMachine(T* pOwner) :

        // オーナー
        pOwner_(pOwner)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    C_StateMachine<T>::~C_StateMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ステートの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::Update() const
    {
        // グローバルステートの更新処理
        if (pGlobalState_) pGlobalState_->Execute(pOwner_);

        // 現在のステートの更新処理
        if (pCurrentState_) pCurrentState_->Execute(pOwner_);
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  メッセージ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    template<typename T>
    bool C_StateMachine<T>::MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const
    {
        // 現在のステートへメッセージ処理
        if (pCurrentState_ && pCurrentState_->MessageProcess(pOwner_, rTelegram) == true) return true;

        // グローバルステートへメッセージ処理
        if (pGlobalState_ && pGlobalState_->MessageProcess(pOwner_, rTelegram) == true) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  新しいステートに変更する
     *  @param  新しいステート
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::ChangeState(StatePtr pNewState)
    {
        assert(pNewState);

        // 現在のステートを以前のステートにする
        pPreviousState_ = pCurrentState_;

        // 現在のステートの終了処理
        if (pCurrentState_) pCurrentState_->Exit(pOwner_);

        // 新しいステートに切り替える
        pCurrentState_ = pNewState;

        // 新しいステートの開始処理
        pCurrentState_->Enter(pOwner_);
    }


    /*************************************************************//**
     *
     *  @brief  以前のステートに変更する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::RevertToPreviousState()
    {
        ChangeState(pPreviousState_);
    }


    /*************************************************************//**
     *
     *  @brief  現在のステートを確認する
     *  @param  ステート
     *  @return 現在のステートと同じ：true
     *  @return 現在のステートを違う：false
     *
     ****************************************************************/
    template<typename T>
	bool C_StateMachine<T>::CheckCurrentState(StatePtr pState) const
    {
		return (typeid(*pCurrentState_) == typeid(*pState)) ? true : false;
    }


    /*************************************************************//**
     *
     *  @brief  現在のステートを取得する
     *  @param  なし
     *  @return 現在のステート
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetCurrentState() const
    {
        return pCurrentState_;
    }


    /*************************************************************//**
     *
     *  @brief  以前のステートを取得する
     *  @param  なし
     *  @return 以前のステート
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetPreviousState() const
    {
        return pPreviousState_;
    }


    /*************************************************************//**
     *
     *  @brief  グローバルステートを取得する
     *  @param  なし
     *  @return グローバルステート
     *
     ****************************************************************/
    template<typename T>
    typename C_StateMachine<T>::StatePtr C_StateMachine<T>::GetGlobalState() const
    {
        return pGlobalState_;
    }


    /*************************************************************//**
     *
     *  @brief  現在のステートを設定する
     *  @param  現在のステート
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetCurrentState(StatePtr pCurrentState)
    {
        pCurrentState_ = pCurrentState;
    }


    /*************************************************************//**
     *
     *  @brief  以前のステートを設定する
     *  @param  以前のステート
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetPreviousState(StatePtr pPreviousState)
    {
        pPreviousState_ = pPreviousState;
    }


    /*************************************************************//**
     *
     *  @brief  以前のステートを設定する
     *  @param  以前のステート
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_StateMachine<T>::SetGlobalState(StatePtr pGlobalState)
    {
        pGlobalState_ = pGlobalState;
    }
}