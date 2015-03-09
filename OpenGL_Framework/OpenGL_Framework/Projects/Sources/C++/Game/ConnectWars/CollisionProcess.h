/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseShield;


    //-------------------------------------------------------------
    //!
    //! @brief コリジョンプロセス
    //! @brief 衝突時の処理を行う関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_CollisionProcess
    {
    public:
        static void s_PlayerAndPlayer(C_BasePlayer* pPlayer, C_BasePlayer* pAnotherPlayer);
        static void s_PlayerAndOption(C_BasePlayer* pPlayer, C_BaseOption* pOption);
        static void s_PlayerAndEnemy(C_BasePlayer* pPlayer, C_BaseEnemy* pEnemy);
        static void s_PlayerAndBullet(C_BasePlayer* pPlayer, C_BaseBullet* pBullet);
        static void s_PlayerAndObstacle(C_BasePlayer* pPlayer, C_BaseObstacle* pObstacle);
        static void s_PlayerAndBomb(C_BasePlayer* pPlayer, C_BaseBomb* pBomb);
        static void s_PlayerAndShield(C_BasePlayer* pPlayer, C_BaseShield* pShield);

        static void s_OptionAndOption(C_BaseOption* pOption, C_BaseOption* pAnotherOption);
        static void s_OptionAndEnemy(C_BaseOption* pOption, C_BaseEnemy* pEnemy);
        static void s_OptionAndBullet(C_BaseOption* pOption, C_BaseBullet* pBullet);
        static void s_OptionAndObstacle(C_BaseOption* pOption, C_BaseObstacle* pObstacle);
        static void s_OptionAndBomb(C_BaseOption* pOption, C_BaseBomb* pBomb);
        static void s_OptionAndShield(C_BaseOption* pOption, C_BaseShield* pShield);

        static void s_EnemyAndEnemy(C_BaseEnemy* pEnemy, C_BaseEnemy* pAnotherEnemy);
        static void s_EnemyAndBullet(C_BaseEnemy* pEnemy, C_BaseBullet* pBullet);
        static void s_EnemyAndObstacle(C_BaseEnemy* pEnemy, C_BaseObstacle* pObstacle);
        static void s_EnemyAndBomb(C_BaseEnemy* pEnemy, C_BaseBomb* pBomb);
        static void s_EnemyAndShield(C_BaseEnemy* pEnemy, C_BaseShield* pShield);

        static void s_BulletAndBullet(C_BaseBullet* pBullet, C_BaseBullet* pAnotherBullet);
        static void s_BulletAndObstale(C_BaseBullet* pBullet, C_BaseObstacle* pObstacle);
        static void s_BulletAndBomb(C_BaseBullet* pBullet, C_BaseBomb* pBomb);
        static void s_BulletAndShield(C_BaseBullet* pBullet, C_BaseShield* pShield);

        static void s_ObstacleAndObstacle(C_BaseObstacle* pObstacle, C_BaseObstacle* pAnotherObstacle);
        static void s_ObstacleAndBomb(C_BaseObstacle* pObstacle, C_BaseBomb* pBomb);
        static void s_ObstacleAndShield(C_BaseObstacle* pObstacle, C_BaseShield* pShield);

        static void s_BombAndBomb(C_BaseBomb* pBomb, C_BaseBomb* pAnotherBomb);
        static void s_BombAndShield(C_BaseBomb* pBomb, C_BaseShield* pShield);

        static void s_ShieldAndShield(C_BaseShield* pShield, C_BaseShield* pAnotherShield);
    };
}