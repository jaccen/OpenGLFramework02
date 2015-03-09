/* ヘッダファイル */
#include "BaseShield.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ベースシールド
    //! @brief シールドの基底クラス
    //!
    //-------------------------------------------------------------
    class C_NormalShield : public C_BaseShield
    {
    public:
        C_NormalShield(const std::string& rId,                                              // コンストラクタ
                       int32_t type,
                       int32_t shooterType,
                       C_CollisionObject* pTarget);  
        ~C_NormalShield() override;                                                         // デストラクタ
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                                      ///< @brief スプライトクリエイター
        Sprite::S_CreateData spriteCreateData_;                                             ///< @brief スプライトの作成情報

        void DoDraw() override;                                                             // 非公開の描画処理
    };
}